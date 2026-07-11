//! YJX-CHIP HID protocol for Smailwolf RS7 (see PROTOCOL.md).

pub const REPORT_SIZE: usize = 64;
pub const MAGIC_OUT: u8 = 0x55;
pub const MAGIC_IN: u8 = 0xAA;
pub const TAG_AE: u8 = 0xAE;

pub const CMD_GET_PROFILE: u8 = 0x0E;
pub const CMD_PROFILE: u8 = 0x0F;
pub const CMD_ACTIVE_SLOT: u8 = 0x22;
pub const CMD_POLL: u8 = 0x23;
pub const CMD_BATTERY: u8 = 0xFA;
pub const CMD_SERIAL: u8 = 0xE6;
pub const CMD_LINK: u8 = 0xED;

/// Tag used by GET requests (`0x0E` / `0x08` / `0x30`) and some helpers (`0x09` / `0x10`).
pub const TAG_A5: u8 = 0xA5;

pub const NUM_DPI_SLOTS: usize = 6;
pub const DPI_MIN: u16 = 200;
pub const DPI_MAX: u16 = 24_000;

pub const VID_WIRED: u16 = 0xA8A4;
pub const VID_RECEIVER: u16 = 0xA8A5;
pub const PID: u16 = 0x2255;
pub const CONFIG_INTERFACE: i32 = 2;
pub const USAGE_PAGE_VENDOR: u16 = 0xFF01;

/// Default DPI table observed in captures.
pub const DEFAULT_DPI: [u16; NUM_DPI_SLOTS] = [800, 2400, 3200, 800, 2400, 3200];

/// Trailing bytes after the 6 DPI values in captured `0x0F` packets.
const PROFILE_TRAILING: [u8; 39] = [
    0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x80, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x0a, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
];

/// Fixed header byte at offset 4 in `0x0F` (majority of captures use `0x2E`).
const PROFILE_HDR: u8 = 0x2E;

/// Fixed header byte at offset 4 in `0x22` / `0x23`.
const CONFIRM_HDR: u8 = 0x03;

pub type Report = [u8; REPORT_SIZE];

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ConnectionMode {
    Wired,
    Receiver24G,
}

impl ConnectionMode {
    pub fn label_pt(self) -> &'static str {
        match self {
            Self::Wired => "Cabo (USB)",
            Self::Receiver24G => "Receptor 2.4G",
        }
    }

    pub fn from_vid(vid: u16) -> Option<Self> {
        match vid {
            VID_WIRED => Some(Self::Wired),
            VID_RECEIVER => Some(Self::Receiver24G),
            _ => None,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PollRate {
    Hz125 = 125,
    Hz250 = 250,
    Hz500 = 500,
    Hz1000 = 1000,
}

impl PollRate {
    pub const ALL: [PollRate; 4] = [
        PollRate::Hz125,
        PollRate::Hz250,
        PollRate::Hz500,
        PollRate::Hz1000,
    ];

    pub fn hz(self) -> u16 {
        self as u16
    }

    /// Wire encoding used by the official driver (not plain Hz/250 for all rates).
    /// 125→1, 250→2, 500→3, 1000→4.
    pub fn poll_code(self) -> u8 {
        match self {
            Self::Hz125 => 1,
            Self::Hz250 => 2,
            Self::Hz500 => 3,
            Self::Hz1000 => 4,
        }
    }

    pub fn from_poll_code(code: u8) -> Option<Self> {
        match code {
            1 => Some(Self::Hz125),
            2 => Some(Self::Hz250),
            3 => Some(Self::Hz500),
            4 => Some(Self::Hz1000),
            _ => None,
        }
    }

    pub fn label(self) -> String {
        format!("{} Hz", self.hz())
    }

    pub fn next(self) -> Self {
        match self {
            Self::Hz125 => Self::Hz250,
            Self::Hz250 => Self::Hz500,
            Self::Hz500 => Self::Hz1000,
            Self::Hz1000 => Self::Hz125,
        }
    }

    pub fn prev(self) -> Self {
        match self {
            Self::Hz125 => Self::Hz1000,
            Self::Hz250 => Self::Hz125,
            Self::Hz500 => Self::Hz250,
            Self::Hz1000 => Self::Hz500,
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Profile {
    pub dpi: [u16; NUM_DPI_SLOTS],
    /// 1-based active slot (1..=6).
    pub active_slot: u8,
    pub poll: PollRate,
}

impl Default for Profile {
    fn default() -> Self {
        Self {
            dpi: DEFAULT_DPI,
            active_slot: 1,
            poll: PollRate::Hz500,
        }
    }
}

impl Profile {
    pub fn clamp_dpi(value: u16) -> u16 {
        value.clamp(DPI_MIN, DPI_MAX)
    }

    pub fn active_dpi(&self) -> u16 {
        let idx = (self.active_slot.saturating_sub(1) as usize).min(NUM_DPI_SLOTS - 1);
        self.dpi[idx]
    }

    /// Parse DPI table / active slot / poll from a `0x0F` write or `0x0E` GET response.
    pub fn from_profile_report(packet: &Report) -> Option<Self> {
        if packet.len() < REPORT_SIZE {
            return None;
        }
        let cmd = packet[1];
        if cmd != CMD_PROFILE && cmd != CMD_GET_PROFILE {
            return None;
        }
        let stages = packet[11];
        if stages != NUM_DPI_SLOTS as u8 {
            return None;
        }
        let active_slot = packet[12];
        if !(1..=NUM_DPI_SLOTS as u8).contains(&active_slot) {
            return None;
        }
        let poll = PollRate::from_poll_code(packet[10])?;
        let dpi = unpack_dpi_table(packet);
        // Reject clearly garbage DPI (all zero / out of UI range extremes).
        if dpi.iter().any(|&d| d != 0 && !(DPI_MIN..=DPI_MAX).contains(&d)) {
            return None;
        }
        if dpi.iter().all(|&d| d == 0) {
            return None;
        }
        Some(Self {
            dpi: dpi.map(Self::clamp_dpi),
            active_slot,
            poll,
        })
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct BatteryInfo {
    pub percent: u8,
    /// 0 = not charging; 1 = maybe charging (candidate from captures).
    pub flags: u8,
}

impl BatteryInfo {
    pub fn charging(&self) -> bool {
        self.flags != 0
    }
}

/// Unsolicited `0xFA` when the hardware DPI button changes the active stage.
///
/// Same command ID as battery, distinguished by marker `[8]`:
/// - battery: `[4]=0x38`, `[8]=0xD0`, `[9]=percent`
/// - stage:   `[4]=0x0A`, `[8]=0x10`, `[9]=active_slot`, `[10]=poll_code`
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ActiveStageInfo {
    /// 1-based slot (1..=6).
    pub active_slot: u8,
    /// Same poll_code map as profile (`Hz/250` style).
    pub poll_code: u8,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum DeviceEvent {
    Battery(BatteryInfo),
    /// Hardware DPI button (or firmware) changed the active stage.
    ActiveStage(ActiveStageInfo),
    Serial(String),
    Link,
    Echo { cmd: u8 },
    Unknown { cmd: u8 },
}

/// Marker byte at offset 8 in unsolicited `0xFA` reports.
pub const FA_MARKER_BATTERY: u8 = 0xD0;
pub const FA_MARKER_STAGE: u8 = 0x10;
/// Header byte at offset 4.
pub const FA_HDR_BATTERY: u8 = 0x38;
pub const FA_HDR_STAGE: u8 = 0x0A;

/// AE-family checksum: `sum(packet[4..64]) & 0xFF`.
pub fn checksum_ae(packet: &[u8; REPORT_SIZE]) -> u8 {
    packet[4..].iter().fold(0u8, |acc, &b| acc.wrapping_add(b))
}

pub fn apply_checksum_ae(packet: &mut [u8; REPORT_SIZE]) {
    packet[2] = TAG_AE;
    packet[3] = checksum_ae(packet);
}

/// Checksum byte only (keeps existing tag — used by A5 GET family).
pub fn apply_checksum(packet: &mut [u8; REPORT_SIZE]) {
    packet[3] = checksum_ae(packet);
}

fn blank_report() -> Report {
    [0u8; REPORT_SIZE]
}

fn hex_to_report(hex: &str) -> Report {
    debug_assert_eq!(hex.len(), REPORT_SIZE * 2);
    let mut out = blank_report();
    for (i, chunk) in hex.as_bytes().chunks(2).enumerate() {
        let s = std::str::from_utf8(chunk).expect("hex ascii");
        out[i] = u8::from_str_radix(s, 16).expect("hex byte");
    }
    out
}

/// Exact helper templates from `slot1-1600-to-800.pcapng` apply sequence.
pub fn helper_init_packets() -> [Report; 2] {
    [
        hex_to_report(
            "550d0038380000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        ),
        hex_to_report(
            "550d0040083800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        ),
    ]
}

pub fn helper_prep_packet() -> Report {
    hex_to_report(
        "5510a500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    )
}

/// Five `0x09` blocks (indexes 0x07..=0x0B) from apply captures.
pub fn helper_block_packets() -> [Report; 5] {
    [
        hex_to_report(
            "5509a50720000000200100002002000020040000200800002010000021550000213801002138ff00000000000000000000000000000000000000000000000000",
        ),
        hex_to_report(
            "5509a50820000001200100002002000020040000200800002010000021550000213801002138ff00000000000000000000000000000000000000000000000000",
        ),
        hex_to_report(
            "5509a50920000002200100002002000020040000200800002010000021550000213801002138ff00000000000000000000000000000000000000000000000000",
        ),
        hex_to_report(
            "5509a50a20000003200100002002000020040000200800002010000021550000213801002138ff00000000000000000000000000000000000000000000000000",
        ),
        hex_to_report(
            "5509a50b20000004200100002002000020040000200800002010000021550000213801002138ff00000000000000000000000000000000000000000000000000",
        ),
    ]
}

pub fn build_profile_packet(profile: &Profile) -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_PROFILE;
    pkt[2] = TAG_AE;
    pkt[4] = PROFILE_HDR;
    pkt[10] = profile.poll.poll_code();
    pkt[11] = NUM_DPI_SLOTS as u8;
    pkt[12] = profile.active_slot;
    for (i, &dpi) in profile.dpi.iter().enumerate() {
        let off = 13 + i * 2;
        let le = dpi.to_le_bytes();
        pkt[off] = le[0];
        pkt[off + 1] = le[1];
    }
    pkt[25..].copy_from_slice(&PROFILE_TRAILING);
    apply_checksum_ae(&mut pkt);
    pkt
}

pub fn build_active_slot_packet(profile: &Profile) -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_ACTIVE_SLOT;
    pkt[2] = TAG_AE;
    pkt[4] = CONFIRM_HDR;
    pkt[10] = profile.active_slot;
    let dpi = profile.active_dpi().to_le_bytes();
    pkt[11] = dpi[0];
    pkt[12] = dpi[1];
    apply_checksum_ae(&mut pkt);
    pkt
}

pub fn build_poll_packet(profile: &Profile) -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_POLL;
    pkt[2] = TAG_AE;
    pkt[4] = CONFIRM_HDR;
    pkt[10] = profile.poll.poll_code();
    apply_checksum_ae(&mut pkt);
    pkt
}

/// Full Apply sequence mirroring the official Windows driver.
pub fn build_apply_sequence(profile: &Profile) -> Vec<Report> {
    let mut seq = Vec::with_capacity(11);
    seq.extend(helper_init_packets());
    seq.push(helper_prep_packet());
    seq.extend(helper_block_packets());
    seq.push(build_profile_packet(profile));
    seq.push(build_active_slot_packet(profile));
    seq.push(build_poll_packet(profile));
    seq
}

/// GET profile request (`0x0E`), captured when the official software opens.
///
/// Same payload layout as `0x0F` on the response; request is mostly empty with hdr `0x2E`.
pub fn build_get_profile_packet() -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_GET_PROFILE;
    pkt[2] = TAG_A5;
    pkt[4] = PROFILE_HDR;
    apply_checksum(&mut pkt);
    pkt
}

pub fn unpack_dpi_table(packet: &[u8; REPORT_SIZE]) -> [u16; NUM_DPI_SLOTS] {
    let mut dpi = [0u16; NUM_DPI_SLOTS];
    for i in 0..NUM_DPI_SLOTS {
        let off = 13 + i * 2;
        dpi[i] = u16::from_le_bytes([packet[off], packet[off + 1]]);
    }
    dpi
}

pub fn parse_inbound(packet: &[u8]) -> Option<DeviceEvent> {
    if packet.len() < REPORT_SIZE || packet[0] != MAGIC_IN {
        return None;
    }
    let cmd = packet[1];
    match cmd {
        CMD_BATTERY => parse_fa_report(packet),
        CMD_SERIAL => {
            let ascii: String = packet[4..]
                .iter()
                .copied()
                .take_while(|&b| b != 0)
                .filter(|&b| b.is_ascii_graphic() || b == b' ')
                .map(char::from)
                .collect();
            Some(DeviceEvent::Serial(ascii))
        }
        CMD_LINK => Some(DeviceEvent::Link),
        _ => {
            if packet[0] == MAGIC_IN {
                Some(DeviceEvent::Echo { cmd })
            } else {
                Some(DeviceEvent::Unknown { cmd })
            }
        }
    }
}

/// `0xFA` is multiplexed: battery (`… d0 PCT FLAGS`) vs active stage (`… 10 SLOT POLL`).
fn parse_fa_report(packet: &[u8]) -> Option<DeviceEvent> {
    let marker = packet[8];
    let hdr = packet[4];
    if marker == FA_MARKER_BATTERY || hdr == FA_HDR_BATTERY {
        Some(DeviceEvent::Battery(BatteryInfo {
            percent: packet[9],
            flags: packet[10],
        }))
    } else if marker == FA_MARKER_STAGE || hdr == FA_HDR_STAGE {
        let slot = packet[9];
        if !(1..=NUM_DPI_SLOTS as u8).contains(&slot) {
            return Some(DeviceEvent::Unknown { cmd: CMD_BATTERY });
        }
        Some(DeviceEvent::ActiveStage(ActiveStageInfo {
            active_slot: slot,
            poll_code: packet[10],
        }))
    } else {
        Some(DeviceEvent::Unknown { cmd: CMD_BATTERY })
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    #[test]
    fn checksum_matches_captured_0x22() {
        let mut pkt = hex_to_report(
            "5522ae27030000000000012003000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        let expected = pkt[3];
        pkt[3] = 0;
        apply_checksum_ae(&mut pkt);
        assert_eq!(pkt[3], expected);
        assert_eq!(pkt[3], 0x27);
    }

    #[test]
    fn checksum_matches_captured_0x23() {
        let mut pkt = hex_to_report(
            "5523ae06030000000000030000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        let expected = pkt[3];
        pkt[3] = 0;
        apply_checksum_ae(&mut pkt);
        assert_eq!(pkt[3], expected);
        assert_eq!(pkt[3], 0x06);
    }

    #[test]
    fn checksum_matches_captured_0x0f_1600() {
        let captured = hex_to_report(
            "550fae8c2e000000000003060140066009800c20036009800cff00000000ff80008000ff00ffff0000ffff000000000000ff010affff00000000000000000000",
        );
        assert_eq!(checksum_ae(&captured), 0x8c);
        assert_eq!(captured[3], 0x8c);

        let profile = Profile {
            dpi: [1600, 2400, 3200, 800, 2400, 3200],
            active_slot: 1,
            poll: PollRate::Hz500,
        };
        let built = build_profile_packet(&profile);
        assert_eq!(built, captured);
    }

    #[test]
    fn checksum_matches_captured_0x0f_slot2() {
        let profile = Profile {
            dpi: [800, 2000, 3200, 800, 2400, 3200],
            active_slot: 2,
            poll: PollRate::Hz500,
        };
        let built = build_profile_packet(&profile);
        let captured = hex_to_report(
            "550faed82e00000000000306022003d007800c20036009800cff00000000ff80008000ff00ffff0000ffff000000000000ff010affff00000000000000000000",
        );
        assert_eq!(built, captured);
    }

    #[test]
    fn poll_code_mapping() {
        assert_eq!(PollRate::Hz125.poll_code(), 1);
        assert_eq!(PollRate::Hz250.poll_code(), 2);
        assert_eq!(PollRate::Hz500.poll_code(), 3);
        assert_eq!(PollRate::Hz1000.poll_code(), 4);
        assert_eq!(PollRate::from_poll_code(4), Some(PollRate::Hz1000));
        assert_eq!(PollRate::from_poll_code(9), None);
    }

    #[test]
    fn dpi_pack_unpack_roundtrip() {
        let profile = Profile {
            dpi: [200, 800, 1600, 3200, 6400, 24000],
            active_slot: 3,
            poll: PollRate::Hz1000,
        };
        let pkt = build_profile_packet(&profile);
        assert_eq!(unpack_dpi_table(&pkt), profile.dpi);
        assert_eq!(pkt[10], 4);
        assert_eq!(pkt[11], 6);
        assert_eq!(pkt[12], 3);
    }

    #[test]
    fn active_slot_packet_matches_capture() {
        let profile = Profile {
            dpi: [800, 2400, 3200, 800, 2400, 3200],
            active_slot: 1,
            poll: PollRate::Hz500,
        };
        let built = build_active_slot_packet(&profile);
        let captured = hex_to_report(
            "5522ae27030000000000012003000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        assert_eq!(built, captured);
    }

    #[test]
    fn poll_packet_matches_capture() {
        let profile = Profile {
            dpi: DEFAULT_DPI,
            active_slot: 1,
            poll: PollRate::Hz500,
        };
        let built = build_poll_packet(&profile);
        let captured = hex_to_report(
            "5523ae06030000000000030000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        assert_eq!(built, captured);
    }

    #[test]
    fn apply_sequence_length_and_cmds() {
        let seq = build_apply_sequence(&Profile::default());
        assert_eq!(seq.len(), 11);
        let cmds: Vec<u8> = seq.iter().map(|p| p[1]).collect();
        assert_eq!(
            cmds,
            vec![
                0x0D, 0x0D, 0x10, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F, 0x22, 0x23
            ]
        );
        assert_eq!(seq[0][0], MAGIC_OUT);
        assert_eq!(seq[8][2], TAG_AE);
    }

    #[test]
    fn parse_battery_fa() {
        let mut pkt = blank_report();
        pkt[0] = MAGIC_IN;
        pkt[1] = CMD_BATTERY;
        pkt[2] = TAG_AE;
        pkt[4] = FA_HDR_BATTERY;
        pkt[5] = 0x01;
        pkt[6] = 0x01;
        pkt[7] = 0x01;
        pkt[8] = FA_MARKER_BATTERY;
        pkt[9] = 80;
        pkt[10] = 0;
        apply_checksum_ae(&mut pkt);

        match parse_inbound(&pkt).unwrap() {
            DeviceEvent::Battery(b) => {
                assert_eq!(b.percent, 80);
                assert!(!b.charging());
            }
            other => panic!("unexpected {other:?}"),
        }
    }

    #[test]
    fn parse_active_stage_fa_not_battery() {
        // Captured via strace while cycling the hardware DPI button:
        // aa fa ae 21 0a 01 01 01 10 01 03 …
        let mut pkt = blank_report();
        pkt[0] = MAGIC_IN;
        pkt[1] = CMD_BATTERY;
        pkt[4] = FA_HDR_STAGE;
        pkt[5] = 0x01;
        pkt[6] = 0x01;
        pkt[7] = 0x01;
        pkt[8] = FA_MARKER_STAGE;
        pkt[9] = 1;
        pkt[10] = 3;
        apply_checksum_ae(&mut pkt);
        assert_eq!(pkt[3], 0x21);

        match parse_inbound(&pkt).unwrap() {
            DeviceEvent::ActiveStage(s) => {
                assert_eq!(s.active_slot, 1);
                assert_eq!(s.poll_code, 3);
            }
            other => panic!("slot notify misparsed as {other:?}"),
        }

        pkt[9] = 6;
        apply_checksum_ae(&mut pkt);
        match parse_inbound(&pkt).unwrap() {
            DeviceEvent::ActiveStage(s) => assert_eq!(s.active_slot, 6),
            other => panic!("unexpected {other:?}"),
        }
    }

    #[test]
    fn helpers_match_capture_magic() {
        let inits = helper_init_packets();
        assert_eq!(&inits[0][..4], &[0x55, 0x0D, 0x00, 0x38]);
        assert_eq!(&inits[1][..4], &[0x55, 0x0D, 0x00, 0x40]);
        let prep = helper_prep_packet();
        assert_eq!(&prep[..4], &[0x55, 0x10, 0xA5, 0x00]);
        let blocks = helper_block_packets();
        for (i, blk) in blocks.iter().enumerate() {
            assert_eq!(blk[0], 0x55);
            assert_eq!(blk[1], 0x09);
            assert_eq!(blk[2], 0xA5);
            assert_eq!(blk[3], 0x07 + i as u8);
        }
    }

    #[test]
    fn get_profile_request_matches_open_capture() {
        let built = build_get_profile_packet();
        let captured = hex_to_report(
            "550ea52e2e0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        assert_eq!(built, captured);
        assert_eq!(built[2], TAG_A5);
        assert_eq!(built[3], checksum_ae(&built));
    }

    #[test]
    fn parse_get_profile_response_from_open_capture() {
        let resp = hex_to_report(
            "aa0ea5732e000000000003060420036009800c20036009800c000000000000000000000000000000000000000000000000ff010affff00000000000000000000",
        );
        assert_eq!(checksum_ae(&resp), 0x73);
        let profile = Profile::from_profile_report(&resp).expect("parse profile");
        assert_eq!(profile.poll, PollRate::Hz500);
        assert_eq!(profile.active_slot, 4);
        assert_eq!(profile.dpi, [800, 2400, 3200, 800, 2400, 3200]);
    }
}
