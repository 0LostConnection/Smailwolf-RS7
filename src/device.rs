//! HID device access for Smailwolf RS7 config interface (MI_02).

use crate::protocol::{
    self, build_apply_sequence, build_get_profile_packet, parse_inbound, ConnectionMode,
    DeviceEvent, Profile, Report, PID, CONFIG_INTERFACE, USAGE_PAGE_VENDOR, VID_RECEIVER,
    VID_WIRED, CMD_GET_PROFILE, MAGIC_IN,
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

fn worker_loop(cmd_rx: Receiver<HostToDevice>, evt_tx: Sender<DeviceToHost>) -> Result<(), DeviceError> {
    let mut api = HidApi::new().map_err(|e| DeviceError::Hid(e.to_string()))?;
    let mut device: Option<HidDevice> = None;
    let mut buf = [0u8; protocol::REPORT_SIZE + 1];
    let mut need_profile_load = false;

    loop {
        // (Re)open config interface if needed.
        if device.is_none() {
            match try_open_config(&mut api) {
                Ok((info, dev)) => {
                    let _ = evt_tx.send(DeviceToHost::Opened(info));
                    let _ = dev.set_blocking_mode(false);
                    device = Some(dev);
                    need_profile_load = true;
                }
                Err(err) => {
                    let _ = evt_tx.send(DeviceToHost::Status(err.to_string()));
                }
            }
        }

        if need_profile_load {
            if let Some(dev) = device.as_ref() {
                match send_get_profile(dev, &evt_tx) {
                    Ok(profile) => {
                        let _ = evt_tx.send(DeviceToHost::Profile(profile));
                        need_profile_load = false;
                    }
                    Err(err) => {
                        let _ = evt_tx.send(DeviceToHost::Status(format!(
                            "falha ao ler perfil do mouse: {err}"
                        )));
                        // Retry on next loop after a short pause; don't hammer.
                        thread::sleep(Duration::from_millis(300));
                        if matches!(
                            err,
                            DeviceError::Busy
                                | DeviceError::PermissionDenied
                                | DeviceError::WriteFailed
                        ) {
                            device = None;
                            need_profile_load = false;
                        }
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
                        // Force reopen on hard read errors.
                        device = None;
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
                        if matches!(err, DeviceError::Busy | DeviceError::PermissionDenied | DeviceError::WriteFailed) {
                            device = None;
                        }
                    }
                }
            }
            Err(TryRecvError::Empty) => {}
            Err(TryRecvError::Disconnected) => return Ok(()),
        }
    }
}

fn try_open_config(api: &mut HidApi) -> Result<(DeviceInfo, HidDevice), DeviceError> {
    let _ = api.refresh_devices();
    let info = find_config_device(api)?;
    let device = open_by_path(api, &info.path)?;
    Ok((info, device))
}

fn find_config_device(api: &HidApi) -> Result<DeviceInfo, DeviceError> {
    // Refresh enumeration in case the device appeared after start.
    // HidApi::new already enumerated; re-create for a fresh list if needed.
    let mut candidates: Vec<_> = api
        .device_list()
        .filter(|d| {
            let vid = d.vendor_id();
            let pid = d.product_id();
            pid == PID && (vid == VID_WIRED || vid == VID_RECEIVER)
        })
        .collect();

    if candidates.is_empty() {
        return Err(DeviceError::NotFound);
    }

    // Prefer MI_02 / vendor usage page.
    candidates.sort_by_key(|d| {
        let iface_ok = d.interface_number() == CONFIG_INTERFACE;
        let usage_ok = d.usage_page() == USAGE_PAGE_VENDOR;
        (!iface_ok, !usage_ok)
    });

    let d = candidates
        .into_iter()
        .find(|d| d.interface_number() == CONFIG_INTERFACE || d.usage_page() == USAGE_PAGE_VENDOR)
        .ok_or(DeviceError::NotFound)?;

    let mode = ConnectionMode::from_vid(d.vendor_id()).ok_or(DeviceError::NotFound)?;
    Ok(DeviceInfo {
        mode,
        path: d.path().to_string_lossy().into_owned(),
        product: d.product_string().unwrap_or("YJX-CHIP").to_string(),
    })
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
                if report[0] == MAGIC_IN && report[1] == cmd {
                    return Ok(report);
                }
                if let Some(tx) = evt_tx {
                    if let Some(ev) = parse_inbound(&report) {
                        let _ = tx.send(DeviceToHost::Event(ev));
                    }
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
