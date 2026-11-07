//! HID device access for Smailwolf RS7 config interface (MI_02).

use crate::i18n::{t, Locale, Msg};
use crate::protocol::{
    self, build_apply_sequence, build_get_info_packet, build_get_profile_packet,
    build_open_prelude, parse_inbound, ConnectionMode, DeviceEvent, Profile, Report, PID,
    CONFIG_INTERFACE, USAGE_PAGE_VENDOR, VID_RECEIVER, VID_WIRED, CMD_GET_INFO, CMD_GET_PROFILE,
    MAGIC_IN,
};
use hidapi::{HidApi, HidDevice};
use std::sync::mpsc::{self, Receiver, Sender, TryRecvError};
use std::thread::{self, JoinHandle};
use std::time::Duration;
use thiserror::Error;

#[derive(Debug, Error)]
pub enum DeviceError {
    #[error("dispositivo não encontrado (VID A8A4/A8A5 PID 2255, interface MI_02)")]
    NotFound,
    #[error("permissão negada ao abrir o HID — verifique a regra udev / grupo plugdev")]
    PermissionDenied,
    #[error(
        "dispositivo ocupado ou inacessível (passthrough para VM? feche o driver Windows / devolva o USB)"
    )]
    Busy,
    #[error("erro HID: {0}")]
    Hid(String),
    #[error("falha ao escrever relatório HID")]
    WriteFailed,
    #[error("dispositivo já desconectado")]
    Disconnected,
}

impl DeviceError {
    pub fn message(&self, locale: Locale) -> String {
        match self {
            Self::NotFound => t(Msg::DeviceNotFound, locale).to_string(),
            Self::PermissionDenied => t(Msg::PermissionDenied, locale).to_string(),
            Self::Busy => t(Msg::DeviceBusy, locale).to_string(),
            Self::Hid(s) => format!("{}: {s}", t(Msg::HidError, locale)),
            Self::WriteFailed => t(Msg::WriteFailed, locale).to_string(),
            Self::Disconnected => t(Msg::Disconnected, locale).to_string(),
        }
    }

    fn from_open(err: hidapi::HidError) -> Self {
        let msg = err.to_string().to_lowercase();
        if msg.contains("permission") || msg.contains("access denied") || msg.contains("eacces") {
            Self::PermissionDenied
        } else if msg.contains("busy")
            || msg.contains("resource busy")
            || msg.contains("ebusy")
            || msg.contains("in use")
            || msg.contains("claimed")
        {
            Self::Busy
        } else {
            Self::Hid(err.to_string())
        }
    }
}

#[derive(Debug, Clone)]
pub struct DeviceInfo {
    pub mode: ConnectionMode,
    pub path: String,
    pub product: String,
}

pub enum HostToDevice {
    Apply(Profile),
    /// Re-read DPI / poll / active slot from the mouse (`0x0E`).
    Refresh,
    Shutdown,
}

pub enum DeviceToHost {
    Opened(DeviceInfo),
    /// Config interface gone / switching — UI should clear "online".
    Disconnected,
    /// Current on-device profile (after open or Refresh).
    Profile(Profile),
    Event(DeviceEvent),
    ApplyOk,
    ApplyErr(String),
    Status(String),
    Fatal(String),
}

pub struct DeviceWorker {
    pub tx: Sender<HostToDevice>,
    pub rx: Receiver<DeviceToHost>,
    handle: Option<JoinHandle<()>>,
}

impl DeviceWorker {
    pub fn spawn() -> Self {
        let (cmd_tx, cmd_rx) = mpsc::channel::<HostToDevice>();
        let (evt_tx, evt_rx) = mpsc::channel::<DeviceToHost>();

        let handle = thread::spawn(move || {
            if let Err(err) = worker_loop(cmd_rx, evt_tx.clone()) {
                let _ = evt_tx.send(DeviceToHost::Fatal(err.to_string()));
            }
        });

        Self {
            tx: cmd_tx,
            rx: evt_rx,
            handle: Some(handle),
        }
    }

    pub fn try_recv(&self) -> Result<DeviceToHost, TryRecvError> {
        self.rx.try_recv()
    }

    pub fn apply(&self, profile: Profile) -> Result<(), DeviceError> {
        self.tx
            .send(HostToDevice::Apply(profile))
            .map_err(|_| DeviceError::Disconnected)
    }

    pub fn refresh(&self) -> Result<(), DeviceError> {
        self.tx
            .send(HostToDevice::Refresh)
            .map_err(|_| DeviceError::Disconnected)
    }
}

impl Drop for DeviceWorker {
    fn drop(&mut self) {
        let _ = self.tx.send(HostToDevice::Shutdown);
        if let Some(handle) = self.handle.take() {
            let _ = handle.join();
        }
    }
}

/// How often to rescan USB for cable↔dongle while a config iface is open.
const REPROBE_EVERY: Duration = Duration::from_millis(1500);

fn worker_loop(cmd_rx: Receiver<HostToDevice>, evt_tx: Sender<DeviceToHost>) -> Result<(), DeviceError> {
    let mut api = HidApi::new().map_err(|e| DeviceError::Hid(e.to_string()))?;
    let mut device: Option<HidDevice> = None;
    let mut current_info: Option<DeviceInfo> = None;
    let mut buf = [0u8; protocol::REPORT_SIZE + 1];
    let mut need_profile_load = false;
    let mut last_reprobe = std::time::Instant::now()
        .checked_sub(REPROBE_EVERY)
        .unwrap_or_else(std::time::Instant::now);

    loop {
        // (Re)open config interface if needed.
        if device.is_none() {
            match try_open_responding_config(&mut api, &evt_tx) {
                Ok((info, dev, profile)) => {
                    current_info = Some(info.clone());
                    let _ = evt_tx.send(DeviceToHost::Opened(info));
                    let _ = evt_tx.send(DeviceToHost::Profile(profile));
                    device = Some(dev);
                    need_profile_load = false;
                    last_reprobe = std::time::Instant::now();
                }
                Err(err) => {
                    let _ = evt_tx.send(DeviceToHost::Status(err.to_string()));
                }
            }
        } else if last_reprobe.elapsed() >= REPROBE_EVERY {
            last_reprobe = std::time::Instant::now();
            match reprobe_connection(&mut api, &mut device, &mut current_info, &evt_tx) {
                Reprobe::Switched => need_profile_load = false,
                Reprobe::Dropped => {
                    need_profile_load = false;
                    let _ = evt_tx.send(DeviceToHost::Disconnected);
                }
                Reprobe::Unchanged => {}
            }
        }

        if need_profile_load {
            // Refresh asked for a re-read on the already-open handle. If it fails,
            // drop and re-probe (covers cable↔dongle swaps).
            if let Some(dev) = device.as_ref() {
                let _ = send_open_prelude(dev, &evt_tx);
                match send_get_profile(dev, &evt_tx) {
                    Ok(profile) => {
                        let _ = evt_tx.send(DeviceToHost::Profile(profile));
                        need_profile_load = false;
                    }
                    Err(err) => {
                        let _ = evt_tx.send(DeviceToHost::Status(format!(
                            "falha ao ler perfil do mouse: {err}"
                        )));
                        thread::sleep(Duration::from_millis(300));
                        drop_connection(&mut device, &mut current_info, &evt_tx);
                        need_profile_load = false;
                    }
                }
            }
        }

        if let Some(dev) = device.as_ref() {
            match dev.read_timeout(&mut buf, 20) {
                Ok(n) if n > 0 => {
                    let report = normalize_read(&buf[..n]);
                    if let Some(ev) = parse_inbound(&report) {
                        let _ = evt_tx.send(DeviceToHost::Event(ev));
                    }
                }
                Ok(_) => {}
                Err(err) => {
                    let msg = err.to_string().to_lowercase();
                    if !(msg.contains("timeout") || msg.contains("timed out")) {
                        let _ = evt_tx.send(DeviceToHost::Status(format!("leitura HID: {err}")));
                        drop_connection(&mut device, &mut current_info, &evt_tx);
                    }
                }
            }
        } else {
            thread::sleep(Duration::from_millis(200));
            let _ = api.refresh_devices();
        }

        match cmd_rx.try_recv() {
            Ok(HostToDevice::Shutdown) => return Ok(()),
            Ok(HostToDevice::Refresh) => {
                need_profile_load = true;
            }
            Ok(HostToDevice::Apply(profile)) => {
                let Some(dev) = device.as_ref() else {
                    let _ = evt_tx.send(DeviceToHost::ApplyErr(
                        "dispositivo não aberto (permissão udev / MI_02?)".into(),
                    ));
                    continue;
                };
                match send_apply(dev, &profile) {
                    Ok(()) => {
                        let _ = evt_tx.send(DeviceToHost::ApplyOk);
                    }
                    Err(err) => {
                        let _ = evt_tx.send(DeviceToHost::ApplyErr(err.to_string()));
                        // Re-open next loop if the handle went bad.
                        if matches!(
                            err,
                            DeviceError::Busy
                                | DeviceError::PermissionDenied
                                | DeviceError::WriteFailed
                        ) {
                            drop_connection(&mut device, &mut current_info, &evt_tx);
                        }
                    }
                }
            }
            Err(TryRecvError::Empty) => {}
            Err(TryRecvError::Disconnected) => return Ok(()),
        }
    }
}

enum Reprobe {
    Unchanged,
    Switched,
    Dropped,
}

fn drop_connection(
    device: &mut Option<HidDevice>,
    current_info: &mut Option<DeviceInfo>,
    evt_tx: &Sender<DeviceToHost>,
) {
    if device.is_some() || current_info.is_some() {
        *device = None;
        *current_info = None;
        let _ = evt_tx.send(DeviceToHost::Disconnected);
    }
}

/// Prefer wired when it answers GET `0x0E`; otherwise keep/use the receiver.
///
/// With both USB ends plugged, the idle path still shows MI_02 but will not
/// return a profile — so we only switch when the preferred candidate answers.
fn reprobe_connection(
    api: &mut HidApi,
    device: &mut Option<HidDevice>,
    current_info: &mut Option<DeviceInfo>,
    evt_tx: &Sender<DeviceToHost>,
) -> Reprobe {
    let _ = api.refresh_devices();
    let candidates = list_config_candidates(api);
    let Some(cur) = current_info.clone() else {
        *device = None;
        return Reprobe::Dropped;
    };

    let still_present = candidates.iter().any(|c| c.path == cur.path);
    if !still_present {
        let _ = evt_tx.send(DeviceToHost::Status(format!(
            "{} sumiu — procurando de novo…",
            match cur.mode {
                ConnectionMode::Wired => "cabo",
                ConnectionMode::Receiver24G => "receptor",
            }
        )));
        *device = None;
        *current_info = None;
        return Reprobe::Dropped;
    }

    let Some(preferred) = candidates.first() else {
        *device = None;
        *current_info = None;
        return Reprobe::Dropped;
    };

    // Higher-priority interface appeared (usually cable while on dongle).
    if preferred.path != cur.path {
        match try_open_candidate(api, preferred, evt_tx) {
            Ok((info, dev, profile)) => {
                let _ = evt_tx.send(DeviceToHost::Status(format!(
                    "trocou para {} — {}",
                    match info.mode {
                        ConnectionMode::Wired => "cabo",
                        ConnectionMode::Receiver24G => "receptor",
                    },
                    info.product
                )));
                *current_info = Some(info.clone());
                *device = Some(dev);
                let _ = evt_tx.send(DeviceToHost::Opened(info));
                let _ = evt_tx.send(DeviceToHost::Profile(profile));
                return Reprobe::Switched;
            }
            Err(_) => {
                // Preferred is enumerated but not answering yet (mid-plug). Keep
                // the current link; the next reprobe retries.
            }
        }
    } else if cur.mode == ConnectionMode::Wired {
        // Cable rarely emits FA 0xD0; re-seed battery via GET 0x30 (official path).
        if let Some(dev) = device.as_ref() {
            let _ = poll_battery_info(dev, evt_tx);
        }
    }

    Reprobe::Unchanged
}

fn poll_battery_info(
    device: &HidDevice,
    evt_tx: &Sender<DeviceToHost>,
) -> Result<(), DeviceError> {
    let pkt = build_get_info_packet();
    write_report(device, &pkt)?;
    let _ = wait_for_cmd(device, CMD_GET_INFO, Duration::from_millis(250), Some(evt_tx))?;
    Ok(())
}

/// Open the first config interface that answers GET `0x0E`.
///
/// Wired (`a8a4`) is tried before the 2.4G receiver (`a8a5`). With both USB
/// devices plugged, the idle dongle still exposes MI_02 but will not return a
/// profile while the mouse is on cable — so open alone is not enough.
fn try_open_responding_config(
    api: &mut HidApi,
    evt_tx: &Sender<DeviceToHost>,
) -> Result<(DeviceInfo, HidDevice, Profile), DeviceError> {
    let _ = api.refresh_devices();
    let candidates = list_config_candidates(api);
    if candidates.is_empty() {
        return Err(DeviceError::NotFound);
    }

    let mut last_err = DeviceError::NotFound;
    for info in candidates {
        match try_open_candidate(api, &info, evt_tx) {
            Ok(opened) => return Ok(opened),
            Err(err) => {
                let _ = evt_tx.send(DeviceToHost::Status(format!(
                    "{} ({}): {err}",
                    match info.mode {
                        ConnectionMode::Wired => "cabo",
                        ConnectionMode::Receiver24G => "receptor",
                    },
                    info.path
                )));
                last_err = err;
            }
        }
    }
    Err(last_err)
}

fn try_open_candidate(
    api: &HidApi,
    info: &DeviceInfo,
    evt_tx: &Sender<DeviceToHost>,
) -> Result<(DeviceInfo, HidDevice, Profile), DeviceError> {
    let device = open_by_path(api, &info.path)?;
    let _ = device.set_blocking_mode(false);
    let _ = send_open_prelude(&device, evt_tx);
    let profile = send_get_profile(&device, evt_tx)?;
    Ok((info.clone(), device, profile))
}

/// Unique MI_02 / vendor-page config interfaces, wired first then receiver.
fn list_config_candidates(api: &HidApi) -> Vec<DeviceInfo> {
    let mut candidates: Vec<DeviceInfo> = Vec::new();
    for d in api.device_list() {
        let vid = d.vendor_id();
        let pid = d.product_id();
        if pid != PID || (vid != VID_WIRED && vid != VID_RECEIVER) {
            continue;
        }
        let iface_ok = d.interface_number() == CONFIG_INTERFACE;
        let usage_ok = d.usage_page() == USAGE_PAGE_VENDOR;
        if !(iface_ok || usage_ok) {
            continue;
        }
        let path = d.path().to_string_lossy().into_owned();
        if candidates.iter().any(|c| c.path == path) {
            continue;
        }
        let Some(mode) = ConnectionMode::from_vid(vid) else {
            continue;
        };
        candidates.push(DeviceInfo {
            mode,
            path,
            product: d.product_string().unwrap_or("YJX-CHIP").to_string(),
        });
    }

    candidates.sort_by_key(|c| {
        let wired_rank = match c.mode {
            ConnectionMode::Wired => 0u8,
            ConnectionMode::Receiver24G => 1u8,
        };
        (wired_rank, c.path.clone())
    });
    candidates
}

fn open_by_path(api: &HidApi, path: &str) -> Result<HidDevice, DeviceError> {
    // hidapi path is a CString-ish platform path; use device_list open.
    for d in api.device_list() {
        if d.path().to_string_lossy() == path {
            return d.open_device(api).map_err(DeviceError::from_open);
        }
    }
    Err(DeviceError::NotFound)
}

fn normalize_read(data: &[u8]) -> Report {
    let mut report = [0u8; protocol::REPORT_SIZE];
    // Some backends prepend a report ID (0x00). Config iface has no report ID,
    // but be defensive if length is 65.
    let src = if data.len() == protocol::REPORT_SIZE + 1 && data[0] == 0 {
        &data[1..]
    } else {
        data
    };
    let n = src.len().min(protocol::REPORT_SIZE);
    report[..n].copy_from_slice(&src[..n]);
    report
}

fn send_apply(device: &HidDevice, profile: &Profile) -> Result<(), DeviceError> {
    for pkt in build_apply_sequence(profile) {
        write_report(device, &pkt)?;
        // Official driver waits for the 0xAA echo before the next OUT.
        // Soft-timeout: some hosts drop echoes; still proceed like the previous TUI.
        let _ = wait_for_cmd(device, pkt[1], Duration::from_millis(150), None);
    }
    Ok(())
}

fn send_open_prelude(
    device: &HidDevice,
    evt_tx: &Sender<DeviceToHost>,
) -> Result<(), DeviceError> {
    for pkt in build_open_prelude() {
        write_report(device, &pkt)?;
        // Soft-wait for echo; forward any interleaved battery/stage FA.
        let _ = wait_for_cmd(device, pkt[1], Duration::from_millis(120), Some(evt_tx));
    }
    Ok(())
}

fn send_get_profile(
    device: &HidDevice,
    evt_tx: &Sender<DeviceToHost>,
) -> Result<Profile, DeviceError> {
    let pkt = build_get_profile_packet();
    write_report(device, &pkt)?;
    let resp = wait_for_cmd(
        device,
        CMD_GET_PROFILE,
        Duration::from_millis(400),
        Some(evt_tx),
    )?;
    Profile::from_profile_report(&resp).ok_or_else(|| {
        DeviceError::Hid("resposta 0x0E sem perfil DPI válido".into())
    })
}

fn write_report(device: &HidDevice, report: &Report) -> Result<(), DeviceError> {
    // Linux hidraw/hidapi: byte 0 MUST be the Report ID.
    // This config interface has no numbered reports → prefix 0x00, then 64 payload bytes.
    // Writing raw 64 bytes makes 0x55 look like a Report ID and truncates the packet.
    let mut buf = [0u8; protocol::REPORT_SIZE + 1];
    buf[0] = 0x00;
    buf[1..].copy_from_slice(report);
    match device.write(&buf) {
        Ok(n) if n >= protocol::REPORT_SIZE => Ok(()),
        Ok(_n) => Err(DeviceError::WriteFailed),
        Err(err) => Err(DeviceError::from_open(err)),
    }
}

/// Wait for an IN report with `magic=0xAA` and matching `cmd`.
/// Side-channel events (battery / stage / serial) are forwarded when `evt_tx` is set.
fn wait_for_cmd(
    device: &HidDevice,
    cmd: u8,
    timeout: Duration,
    evt_tx: Option<&Sender<DeviceToHost>>,
) -> Result<Report, DeviceError> {
    let deadline = std::time::Instant::now() + timeout;
    let mut buf = [0u8; protocol::REPORT_SIZE + 1];
    while std::time::Instant::now() < deadline {
        let remaining = deadline.saturating_duration_since(std::time::Instant::now());
        let ms = remaining.as_millis().min(50) as i32;
        match device.read_timeout(&mut buf, ms.max(1)) {
            Ok(n) if n > 0 => {
                let report = normalize_read(&buf[..n]);
                // Forward side-channel parses for BOTH matched replies and
                // interleaved FA/etc. Matching GET `0x30` carries battery in
                // [8]/[9] — if we only return it, the UI never sees charging
                // on cable (FA 0xD0 is mostly a 2.4G path).
                if let Some(tx) = evt_tx {
                    if let Some(ev) = parse_inbound(&report) {
                        let _ = tx.send(DeviceToHost::Event(ev));
                    }
                }
                if report[0] == MAGIC_IN && report[1] == cmd {
                    return Ok(report);
                }
            }
            Ok(_) => {}
            Err(err) => {
                let msg = err.to_string().to_lowercase();
                if !(msg.contains("timeout") || msg.contains("timed out")) {
                    return Err(DeviceError::from_open(err));
                }
            }
        }
    }
    Err(DeviceError::Hid(format!(
        "timeout aguardando resposta cmd 0x{cmd:02X}"
    )))
}
