//! YJX-CHIP HID protocol for Smailwolf RS7.
//!
//! Wire layout was recovered from usbmon captures and corroborated against
//! `software/mouse-RS7-1.2/DeviceDriver.exe` (FA multiplex @ `0x42cadb`) and
//! `YJXUI.dll` (`BatteryCtrl::SetBatteryInfo(percent, flags)` @ `0x1001fe50`).

pub const REPORT_SIZE: usize = 64;
pub const MAGIC_OUT: u8 = 0x55;
pub const MAGIC_IN: u8 = 0xAA;
pub const TAG_AE: u8 = 0xAE;

pub const CMD_GET_PROFILE: u8 = 0x0E;
pub const CMD_PROFILE: u8 = 0x0F;
pub const CMD_ACTIVE_SLOT: u8 = 0x22;
pub const CMD_POLL: u8 = 0x23;
pub const CMD_NOTIFY: u8 = 0xFA;
pub const CMD_SERIAL: u8 = 0xE6;
pub const CMD_LINK: u8 = 0xED;
/// GET button / key map for one profile index (`0..=5`).
pub const CMD_GET_BUTTONS: u8 = 0x08;
/// SET button / key map for one profile index (Apply uses `0..=4`).
pub const CMD_SET_BUTTONS: u8 = 0x09;
/// Macro firmware blob chunk (`FUN_0042ac40`); payload capacity `0x38` bytes.
pub const CMD_MACRO_CHUNK: u8 = 0x0D;
/// Post-macro commit / prep after `0x0D` chunks.
pub const CMD_MACRO_COMMIT: u8 = 0x10;
/// Bytes of macro blob carried per `0x0D` report (DeviceDriver chunk size).
pub const MACRO_CHUNK_CAPACITY: usize = 0x38;
pub const CMD_GET_INFO: u8 = 0x30;
pub const CMD_IDENT: u8 = 0x03;

/// Tag used by GET requests (`0x0E` / `0x08` / `0x30`) and some helpers (`0x09` / `0x10`).
pub const TAG_A5: u8 = 0xA5;

pub const NUM_DPI_SLOTS: usize = 6;
/// Physical mouse buttons exposed in `t_key_macro_data` / wire `0x08`/`0x09`.
pub const NUM_BUTTONS: usize = 9;
/// Profile indexes written on Apply (`0x09`×5). GET reads `0..=5` (index 5 often empty).
pub const NUM_BUTTON_PROFILES_APPLY: usize = 5;
pub const OFF_BUTTON0: usize = 8;

/// Wire `macro_type` values (DeviceDriver `FUN_00411ce0`).
pub const MACRO_TYPE_DISABLED: u8 = 0x00;
pub const MACRO_TYPE_KEYBOARD: u8 = 0x10;
pub const MACRO_TYPE_MOUSE_BTN: u8 = 0x20;
pub const MACRO_TYPE_SPECIAL: u8 = 0x21;
pub const MACRO_TYPE_MULTIMEDIA: u8 = 0x30;
pub const MACRO_TYPE_FIRE: u8 = 0x50; // Fire Key / rapid-fire (UI id 0x1b)
pub const MACRO_TYPE_MACRO: u8 = 0x70; // recorded macro index in `value`
pub const MACRO_TYPE_SHORTCUT: u8 = 0xF0;
pub const MACRO_VAL_DPI_LOOP: u8 = 0x55;
pub const MACRO_VAL_DPI_STEP: u8 = 0x38; // value2: +1 = DPI+, 0xFF = DPI-
pub const MACRO_VAL_DPI_AIM: u8 = 0xAA; // AIM key (UI id 10)
/// Special `0x21` values for UI types `0x0b` / `0x0c` (encoder @ `0x4118ee`).
/// Labels missing from `1033.lan` (ids 158/159 referenced in driver but absent) — soft.
pub const MACRO_VAL_SPECIAL_0x61: u8 = 0x61;
pub const MACRO_VAL_SPECIAL_0x62: u8 = 0x62;
/// `macro_type=0xF0` groups (`FUN_00411ce0` + encoder @ `0x411932`).
pub const SHORTCUT_GROUP_DPI: u8 = 1; // value2 1/2/3 = DPI+/−/Loop (lang 150–152)
pub const SHORTCUT_GROUP_POLL: u8 = 2; // value2 1/2/3 = Report Rate +/−/Loop (lang 153–155)
/// Consumer-page usages for `macro_type=0x30` (`FUN_00411ce0`).
pub const MEDIA_NEXT: u8 = 0xb5;
pub const MEDIA_PREV: u8 = 0xb6;
pub const MEDIA_STOP: u8 = 0xb7;
pub const MEDIA_PLAY_PAUSE: u8 = 0xcd;
pub const MEDIA_MUTE: u8 = 0xe2;
pub const MEDIA_VOL_UP: u8 = 0xe9;
pub const MEDIA_VOL_DOWN: u8 = 0xea;
pub const DPI_MIN: u16 = 200;
pub const DPI_MAX: u16 = 24_000;

pub const VID_WIRED: u16 = 0xA8A4;
pub const VID_RECEIVER: u16 = 0xA8A5;
pub const PID: u16 = 0x2255;
pub const CONFIG_INTERFACE: i32 = 2;
pub const USAGE_PAGE_VENDOR: u16 = 0xFF01;

/// Default DPI table from the driver's embedded SQLite defaults
/// (`dpi_group0..5_value`: 800/1600/2400/3200/6400/20000). Captures often show a
/// different live table — UI always prefers the GET `0x0E` response.
pub const DEFAULT_DPI: [u16; NUM_DPI_SLOTS] = [800, 1600, 2400, 3200, 6400, 20000];

/// Per-slot DPI indicator colors (`dpi_groupN_rgb`) as packed in Apply `0x0F`
/// (FUN_0042ba10). Observed in captures: R,B,Purple,G,Y,C.
pub const DEFAULT_RGB: [[u8; 3]; NUM_DPI_SLOTS] = [
    [0xff, 0x00, 0x00],
    [0x00, 0x00, 0xff],
    [0x80, 0x00, 0x80],
    [0x00, 0xff, 0x00],
    [0xff, 0xff, 0x00],
    [0x00, 0xff, 0xff],
];

/// One button binding: `macro_type` + `macro_value` / `value2` / `value3`
/// (SQLite `t_key_macro_data`, packed as 4 bytes on the wire).
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct ButtonBinding {
    pub macro_type: u8,
    pub value: u8,
    pub value2: u8,
    pub value3: u8,
}

impl ButtonBinding {
    pub const fn new(macro_type: u8, value: u8, value2: u8, value3: u8) -> Self {
        Self {
            macro_type,
            value,
            value2,
            value3,
        }
    }

    pub const fn mouse_btn(bit: u8) -> Self {
        Self::new(MACRO_TYPE_MOUSE_BTN, bit, 0, 0)
    }

    pub const fn disabled() -> Self {
        Self::new(0, 0, 0, 0)
    }

    pub fn label_short(self) -> &'static str {
        match (self.macro_type, self.value, self.value2) {
            (MACRO_TYPE_DISABLED, 0, _) | (0xff, 0xff, _) => "off",
            (MACRO_TYPE_MOUSE_BTN, 0x01, _) => "L-click",
            (MACRO_TYPE_MOUSE_BTN, 0x02, _) => "R-click",
            (MACRO_TYPE_MOUSE_BTN, 0x04, _) => "M-click",
            (MACRO_TYPE_MOUSE_BTN, 0x08, _) => "Back",
            (MACRO_TYPE_MOUSE_BTN, 0x10, _) => "Fwd",
            (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_LOOP, _) => "DPI loop",
            (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0x01) => "DPI+",
            (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0xff) => "DPI-",
            (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_AIM, _) => "AIM",
            (MACRO_TYPE_SPECIAL, MACRO_VAL_SPECIAL_0x61, _) => "special61",
            (MACRO_TYPE_SPECIAL, MACRO_VAL_SPECIAL_0x62, _) => "special62",
            (MACRO_TYPE_KEYBOARD, _, _) => "keyboard",
            (MACRO_TYPE_MULTIMEDIA, MEDIA_NEXT, _) => "next",
            (MACRO_TYPE_MULTIMEDIA, MEDIA_PREV, _) => "prev",
            (MACRO_TYPE_MULTIMEDIA, MEDIA_STOP, _) => "stop",
            (MACRO_TYPE_MULTIMEDIA, MEDIA_PLAY_PAUSE, _) => "play/pause",
            (MACRO_TYPE_MULTIMEDIA, MEDIA_MUTE, _) => "mute",
            (MACRO_TYPE_MULTIMEDIA, MEDIA_VOL_UP, _) => "vol+",
            (MACRO_TYPE_MULTIMEDIA, MEDIA_VOL_DOWN, _) => "vol-",
            (MACRO_TYPE_MULTIMEDIA, _, _) => "media",
            (MACRO_TYPE_FIRE, _, _) => "fire",
            (MACRO_TYPE_MACRO, _, _) => "macro",
            (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_DPI, 1) => "DPI+ (F0)",
            (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_DPI, 2) => "DPI- (F0)",
            (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_DPI, 3) => "DPI loop (F0)",
            (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 1) => "poll+",
            (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 2) => "poll-",
            (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 3) => "poll loop",
            (MACRO_TYPE_SHORTCUT, _, _) => "shortcut",
            _ => "custom",
        }
    }
}

/// Default 9-button map from Apply / GET captures (`open-software-in-vm.pcapng`).
/// Order: L, R, M, Back, Fwd, DPI loop, DPI+, DPI-, empty.
pub const DEFAULT_BUTTONS: [ButtonBinding; NUM_BUTTONS] = [
    ButtonBinding::mouse_btn(0x01),
    ButtonBinding::mouse_btn(0x02),
    ButtonBinding::mouse_btn(0x04),
    ButtonBinding::mouse_btn(0x08),
    ButtonBinding::mouse_btn(0x10),
    ButtonBinding::new(MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_LOOP, 0, 0),
    ButtonBinding::new(MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0x01, 0),
    ButtonBinding::new(MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0xff, 0),
    ButtonBinding::disabled(),
];

/// Fixed footer after extended flags (`0x0F`/`0x0E` `[49..64]`).
/// Identical on GET and Apply across all captures — device/firmware constant,
/// not computed per-field in `FUN_0042ba10` (builder memset + overlay leaves it).
const PROFILE_FOOTER: [u8; 15] = [
    0xff, 0x01, 0x0a, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
];

/// Fixed header byte at offset 4 in `0x0F` (majority of captures use `0x2E`).
const PROFILE_HDR: u8 = 0x2E;

/// Wire offsets inside the 64-byte `0x0F` / `0x0E` body (FUN_0042ba10).
pub const OFF_LIGHT_MODE: usize = 9;
pub const OFF_POLL: usize = 10;
pub const OFF_STAGES: usize = 11;
pub const OFF_ACTIVE_SLOT: usize = 12;
pub const OFF_DPI0: usize = 13;
pub const OFF_RGB0: usize = 25;
pub const OFF_SCROLL_FLAG: usize = 43;
pub const OFF_LIFTOFF: usize = 44;
pub const OFF_SENSOR_FLAG: usize = 45;
pub const OFF_BUTTON_RESPOND: usize = 46;
pub const OFF_SLEEP_LIGHT: usize = 47;
pub const OFF_ESPORTS_FLAG: usize = 48;

/// SQLite / host `sensor_flag` bits (`FUN_0041b2a0` checkbox pack).
#[allow(dead_code)]
pub const SENSOR_DB_RIPPLE: u32 = 0x04;
#[allow(dead_code)]
pub const SENSOR_DB_ANGLE_SNAP: u32 = 0x08;
#[allow(dead_code)]
pub const SENSOR_DB_MOTION_SYNC: u32 = 0x10;

/// Wire `sensor_flag` bits after [`sensor_flag_db_to_wire`] (`FUN_0042ba10`).
pub const SENSOR_WIRE_RIPPLE: u8 = 0x10;
pub const SENSOR_WIRE_ANGLE_SNAP: u8 = 0x01;
pub const SENSOR_WIRE_MOTION_SYNC: u8 = 0x20;

const SENSOR_WIRE_KNOWN: u8 =
    SENSOR_WIRE_RIPPLE | SENSOR_WIRE_ANGLE_SNAP | SENSOR_WIRE_MOTION_SYNC;

/// Pack SQLite `sensor_flag` bits into the wire byte (`FUN_0042ba10`).
///
/// UI checkboxes (`FUN_0041b2a0`): Ripple→DB`0x04`, Angle Snap→DB`0x08`,
/// Motion Sync→DB`0x10` (not “Sensor Linearity” — that string is section chrome).
#[allow(dead_code)]
pub fn sensor_flag_db_to_wire(db: u32) -> u8 {
    let mut w = 0u8;
    if db & SENSOR_DB_RIPPLE != 0 {
        w |= SENSOR_WIRE_RIPPLE;
    }
    if db & SENSOR_DB_ANGLE_SNAP != 0 {
        w |= SENSOR_WIRE_ANGLE_SNAP;
    }
    if db & SENSOR_DB_MOTION_SYNC != 0 {
        w |= SENSOR_WIRE_MOTION_SYNC;
    }
    w
}

/// Inverse of [`sensor_flag_db_to_wire`] (lossy for unknown bits).
#[allow(dead_code)]
pub fn sensor_flag_wire_to_db(wire: u8) -> u32 {
    let mut db = 0u32;
    if wire & SENSOR_WIRE_RIPPLE != 0 {
        db |= SENSOR_DB_RIPPLE;
    }
    if wire & SENSOR_WIRE_ANGLE_SNAP != 0 {
        db |= SENSOR_DB_ANGLE_SNAP;
    }
    if wire & SENSOR_WIRE_MOTION_SYNC != 0 {
        db |= SENSOR_DB_MOTION_SYNC;
    }
    db
}

/// Cycle the three known sensor wire bits (Angle / Ripple / Motion), keep others.
///
/// Index encoding: bit0=Angle Snap, bit1=Ripple, bit2=Motion Sync.
pub fn sensor_flag_wire_nudge(wire: u8, dir: i8) -> u8 {
    let mut idx = 0u8;
    if wire & SENSOR_WIRE_ANGLE_SNAP != 0 {
        idx |= 1;
    }
    if wire & SENSOR_WIRE_RIPPLE != 0 {
        idx |= 2;
    }
    if wire & SENSOR_WIRE_MOTION_SYNC != 0 {
        idx |= 4;
    }
    let idx = idx.wrapping_add(dir as u8) & 7;
    let mut w = wire & !SENSOR_WIRE_KNOWN;
    if idx & 1 != 0 {
        w |= SENSOR_WIRE_ANGLE_SNAP;
    }
    if idx & 2 != 0 {
        w |= SENSOR_WIRE_RIPPLE;
    }
    if idx & 4 != 0 {
        w |= SENSOR_WIRE_MOTION_SYNC;
    }
    w
}

/// Map a Windows virtual-key code to the HID usage stored in keyboard
/// `macro_type=0x10` bindings (`FUN_0043e570`). Returns `None` when the driver
/// leaves the usage as 0 (unmapped).
#[allow(dead_code)]
pub fn vk_to_hid_usage(vk: u32) -> Option<u8> {
    let usage = match vk {
        0x41..=0x5a => vk - 0x3d, // A–Z → 0x04–0x1d
        0x31..=0x39 => vk - 0x13, // 1–9 → 0x1e–0x26
        0x30 => 0x27,             // 0
        0x0d => 0x28,             // Enter
        0x1b => 0x29,             // Escape
        0x08 => 0x2a,             // Backspace
        0x09 => 0x2b,             // Tab
        0x20 => 0x2c,             // Space
        0xbd => 0x2d,             // -_
        0xbb => 0x2e,             // =+
        0xdb => 0x2f,             // [{
        0xdd => 0x30,             // ]}
        0xdc => 0x31,             // \|
        0x29a => 0x32,            // non-US #~ (driver quirk const)
        0xba => 0x33,             // ;:
        0xde => 0x34,             // '"
        0xc0 => 0x35,             // `~
        0xbc => 0x36,             // ,<
        0xbe => 0x37,             // .>
        0xbf => 0x38,             // /?
        0x14 => 0x39,             // Caps Lock
        0x70..=0x7b => 0x3a + (vk - 0x70), // F1–F12
        0x7c..=0x87 => 0x68 + (vk - 0x7c), // F13–F24
        0x2c => 0x46,             // Print Screen
        0x91 => 0x47,             // Scroll Lock
        0x13 => 0x48,             // Pause
        0x2d => 0x49,             // Insert
        0x24 => 0x4a,             // Home
        0x21 => 0x4b,             // Page Up
        0x2e => 0x4c,             // Delete
        0x23 => 0x4d,             // End
        0x22 => 0x4e,             // Page Down
        0x27 => 0x4f,             // Right
        0x25 => 0x50,             // Left
        0x28 => 0x51,             // Down
        0x26 => 0x52,             // Up
        0x90 => 0x53,             // Num Lock
        0x6f => 0x54,             // Numpad /
        0x6a => 0x55,             // Numpad *
        0x6d => 0x56,             // Numpad -
        0x6b => 0x57,             // Numpad +
        0x6c => 0x58,             // Numpad Enter
        0x61..=0x69 => 0x59 + (vk - 0x61), // Numpad 1–9
        0x60 => 0x62,             // Numpad 0
        0x6e => 0x63,             // Numpad .
        0xa2 => 0xe0,             // LCtrl
        0xa0 => 0xe1,             // LShift
        0xa4 => 0xe2,             // LAlt
        0x5b => 0xe3,             // LWin
        0xa3 => 0xe4,             // RCtrl
        0xa1 => 0xe5,             // RShift
        0xa5 => 0xe6,             // RAlt
        0x5c => 0xe7,             // RWin
        0x5d => 0x65,             // App
        0xfe => 0xaf,
        0xe2 => 0x64,             // non-US \ |
        0x88 | 0x89 | 0x8a | 0x8b => vk, // pass-through
        0x12d => 0xec,
        0x12e => 0xeb,
        _ => return None,
    };
    Some(usage as u8)
}

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
        self.label(crate::i18n::Locale::PtBr)
    }

    pub fn label(self, locale: crate::i18n::Locale) -> &'static str {
        crate::i18n::connection_label(self, locale)
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

    /// Wire encoding used by the official driver.
    /// 125→1, 250→2, 500→3, 1000→4 (matches DeviceDriver `report_rate` values).
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
    /// Per-slot DPI LED color (`dpi_groupN_rgb`), RGB order on the wire.
    pub rgb: [[u8; 3]; NUM_DPI_SLOTS],
    /// 1-based active slot (1..=6).
    pub active_slot: u8,
    pub poll: PollRate,
    /// Lighting preset index (`light_mode`); also notified via FA marker `0x11`.
    pub light_mode: u8,
    /// Scroll direction: `0` forward, nonzero = reverse (driver `scroll_flag`).
    pub scroll_flag: u8,
    /// LOD / liftoff (`liftoff_height`): UI Low≈1mm / High≈2mm.
    pub liftoff_height: u8,
    /// Raw **wire** `sensor_flag` byte (after driver remap from DB bits).
    /// DB→wire (`FUN_0042ba10` / `FUN_0041b2a0`): Ripple `0x04`→`0x10`,
    /// Angle Snap `0x08`→`0x01`, Motion Sync `0x10`→`0x20`.
    pub sensor_flag: u8,
    /// Debounce-ish (`button_respondtime`).
    pub button_respondtime: u8,
    /// Sleep lighting timeout unit (`sleep_light`, default 20 in driver DB).
    pub sleep_light: u8,
    /// `e-sports_flag`.
    pub e_sports_flag: u8,
    /// 9-button map written on Apply via `0x09`×5 (same table for indexes 0..=4).
    pub buttons: [ButtonBinding; NUM_BUTTONS],
}

impl Default for Profile {
    fn default() -> Self {
        Self {
            dpi: DEFAULT_DPI,
            rgb: DEFAULT_RGB,
            active_slot: 1,
            poll: PollRate::Hz500,
            light_mode: 0,
            scroll_flag: 0,
            liftoff_height: 0,
            sensor_flag: 0,
            button_respondtime: 0,
            sleep_light: 0,
            e_sports_flag: 0,
            buttons: DEFAULT_BUTTONS,
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

    pub fn active_rgb(&self) -> [u8; 3] {
        let idx = (self.active_slot.saturating_sub(1) as usize).min(NUM_DPI_SLOTS - 1);
        self.rgb[idx]
    }

    /// Parse DPI / RGB / flags from a `0x0F` write or `0x0E` GET response.
    ///
    /// Note: GET `0x0E` often zeros the RGB block — callers should keep prior RGB
    /// when the decoded table is all-zero.
    pub fn from_profile_report(packet: &Report) -> Option<Self> {
        if packet.len() < REPORT_SIZE {
            return None;
        }
        let cmd = packet[1];
        if cmd != CMD_PROFILE && cmd != CMD_GET_PROFILE {
            return None;
        }
        let stages = packet[OFF_STAGES];
        if stages != NUM_DPI_SLOTS as u8 {
            return None;
        }
        let active_slot = packet[OFF_ACTIVE_SLOT];
        if !(1..=NUM_DPI_SLOTS as u8).contains(&active_slot) {
            return None;
        }
        let poll = PollRate::from_poll_code(packet[OFF_POLL])?;
        let dpi = unpack_dpi_table(packet);
        if dpi.iter().any(|&d| d != 0 && !(DPI_MIN..=DPI_MAX).contains(&d)) {
            return None;
        }
        if dpi.iter().all(|&d| d == 0) {
            return None;
        }
        let rgb = unpack_rgb_table(packet);
        let rgb = if rgb.iter().all(|c| *c == [0, 0, 0]) {
            DEFAULT_RGB
        } else {
            rgb
        };
        Some(Self {
            dpi: dpi.map(Self::clamp_dpi),
            rgb,
            active_slot,
            poll,
            light_mode: packet[OFF_LIGHT_MODE],
            scroll_flag: packet[OFF_SCROLL_FLAG],
            liftoff_height: packet[OFF_LIFTOFF],
            sensor_flag: packet[OFF_SENSOR_FLAG],
            button_respondtime: packet[OFF_BUTTON_RESPOND],
            sleep_light: packet[OFF_SLEEP_LIGHT],
            e_sports_flag: packet[OFF_ESPORTS_FLAG],
            buttons: DEFAULT_BUTTONS,
        })
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct BatteryInfo {
    /// 0..=100 — DeviceDriver clamps with `cmova` against 100 before SetBatteryInfo.
    pub percent: u8,
    /// Second `SetBatteryInfo` argument. Captures: `0` idle, `1` likely charging.
    pub flags: u8,
}

impl BatteryInfo {
    pub fn charging(&self) -> bool {
        // Official UI treats any non-zero FLAGS as the charging/active path.
        // Captures: `0` = in use, `1` = charging (candidate).
        self.flags != 0
    }

    pub fn clamp_percent(raw: u8) -> u8 {
        raw.min(100)
    }
}

/// Where a battery sample came from on the wire.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum BatterySource {
    /// GET `0x30` reply `[8]`/`[9]` — poll/seed (useful on cable; noisy vs FA).
    GetInfo,
    /// Unsolicited FA marker `0xD0` — live reading (DeviceDriver path).
    Fa,
}

/// Filters battery samples like DeviceDriver: FA wins over GET `0x30`, ~200 ms
/// throttle, and ±1% FA flicker needs a repeated sample before it sticks.
#[derive(Debug, Default)]
pub struct BatteryTracker {
    current: Option<BatteryInfo>,
    last_accept: Option<std::time::Instant>,
    saw_fa: bool,
    pending: Option<BatteryInfo>,
}

impl BatteryTracker {
    /// DeviceDriver FA dispatcher gate: `GetTickCount` delta > 199 ms.
    pub const THROTTLE: std::time::Duration = std::time::Duration::from_millis(200);

    pub fn current(&self) -> Option<&BatteryInfo> {
        self.current.as_ref()
    }

    /// Returns `Some` when the displayed battery should change.
    pub fn observe(&mut self, info: BatteryInfo, source: BatterySource) -> Option<BatteryInfo> {
        // After the first live FA, ignore GET 0x30 — it often differs by 1–2% and
        // causes the UI to jump on every open/refresh prelude.
        if source == BatterySource::GetInfo && self.saw_fa {
            return None;
        }
        // On cable, GET 0x30 frequently answers `100%` even when SOC is lower;
        // the real level shows up again on 2.4G FA. Do not seed the UI with that.
        if source == BatterySource::GetInfo && info.percent >= 100 && !self.saw_fa {
            return None;
        }
        if source == BatterySource::Fa {
            self.saw_fa = true;
        }

        if let Some(prev) = self.last_accept {
            if prev.elapsed() < Self::THROTTLE && self.current.is_some() {
                return None;
            }
        }

        if let Some(cur) = self.current {
            if info == cur {
                self.pending = None;
                return None;
            }
            // Captures oscillate 80↔81 on consecutive FAs; require confirmation
            // for a 1% move when charge-state is unchanged.
            if source == BatterySource::Fa
                && info.flags == cur.flags
                && (info.percent as i16 - cur.percent as i16).unsigned_abs() == 1
            {
                if self.pending.as_ref() == Some(&info) {
                    self.pending = None;
                } else {
                    self.pending = Some(info);
                    return None;
                }
            } else {
                self.pending = None;
            }
        }

        self.current = Some(info.clone());
        self.last_accept = Some(std::time::Instant::now());
        Some(info)
    }
}

/// Unsolicited `0xFA` when the hardware DPI button changes the active stage.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ActiveStageInfo {
    /// 1-based slot (1..=6).
    pub active_slot: u8,
    /// Same poll_code map as profile (`1..=4`).
    pub poll_code: u8,
}

/// FA marker `0x11` — DeviceDriver writes `light_mode` (value clamped to ≤6).
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct LightModeInfo {
    pub mode: u8,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum DeviceEvent {
    Battery {
        info: BatteryInfo,
        source: BatterySource,
    },
    /// Hardware DPI button (or firmware) changed the active stage.
    ActiveStage(ActiveStageInfo),
    LightMode(LightModeInfo),
    /// FA markers `0x50` / `0x60` — status/notify codes (not battery).
    Notify { marker: u8, code: u8 },
    /// Button / key map from GET `0x08` (or echo of SET `0x09`).
    Buttons {
        profile_index: u8,
        bindings: [ButtonBinding; NUM_BUTTONS],
    },
    Serial(String),
    Link,
    Echo { cmd: u8 },
    Unknown { cmd: u8 },
}

/// Marker byte at offset 8 in unsolicited `0xFA` reports (DeviceDriver @ `0x42cb09`).
pub const FA_MARKER_BATTERY: u8 = 0xD0;
pub const FA_MARKER_STAGE: u8 = 0x10;
pub const FA_MARKER_LIGHT: u8 = 0x11;
pub const FA_MARKER_NOTIFY_A: u8 = 0x50;
pub const FA_MARKER_NOTIFY_B: u8 = 0x60;
/// Header byte at offset 4 — battery family uses `0x38`, stage uses `0x0A`.
/// Documented for capture matching; FA dispatch keys off the marker, not these.
#[allow(dead_code)]
pub const FA_HDR_BATTERY: u8 = 0x38;
#[allow(dead_code)]
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

/// Empty-macro `0x0D` chunk pair from Apply captures (`FUN_0042ac40` with no
/// `t_macrorecord` payload — still uploads a 0x40-byte header region as two
/// chunks of capacity [`MACRO_CHUNK_CAPACITY`]).
pub fn build_empty_macro_chunks() -> [Report; 2] {
    // Wire headers from captures (chunk framing still partially opaque):
    //   55 0d 00 38 38 …   then   55 0d 00 40 08 38 …
    let pkts = [
        hex_to_report(
            "550d0038380000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        ),
        hex_to_report(
            "550d0040083800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        ),
    ];
    debug_assert_eq!(pkts[0][1], CMD_MACRO_CHUNK);
    debug_assert_eq!(pkts[1][1], CMD_MACRO_CHUNK);
    debug_assert_eq!(MACRO_CHUNK_CAPACITY, 0x38);
    pkts
}

pub fn helper_init_packets() -> [Report; 2] {
    build_empty_macro_chunks()
}

/// Post-macro [`CMD_MACRO_COMMIT`] prep (`FUN_0042ac40` trailer).
pub fn helper_prep_packet() -> Report {
    let pkt = hex_to_report(
        "5510a500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    );
    debug_assert_eq!(pkt[1], CMD_MACRO_COMMIT);
    pkt
}

/// Pack / unpack the 9×4-byte button table that lives at wire offset 8.
pub fn pack_button_table(buttons: &[ButtonBinding; NUM_BUTTONS], packet: &mut Report) {
    for (i, b) in buttons.iter().enumerate() {
        let off = OFF_BUTTON0 + i * 4;
        packet[off] = b.macro_type;
        packet[off + 1] = b.value;
        packet[off + 2] = b.value2;
        packet[off + 3] = b.value3;
    }
}

pub fn unpack_button_table(packet: &Report) -> [ButtonBinding; NUM_BUTTONS] {
    let mut out = [ButtonBinding::disabled(); NUM_BUTTONS];
    for (i, slot) in out.iter_mut().enumerate() {
        let off = OFF_BUTTON0 + i * 4;
        *slot = ButtonBinding::new(
            packet[off],
            packet[off + 1],
            packet[off + 2],
            packet[off + 3],
        );
    }
    out
}

/// SET button map (`0x09`) for profile index `0..=4` (Apply) or `0..=5`.
pub fn build_set_buttons_packet(
    profile_index: u8,
    buttons: &[ButtonBinding; NUM_BUTTONS],
) -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_SET_BUTTONS;
    pkt[2] = TAG_A5;
    pkt[4] = 0x20;
    pkt[7] = profile_index;
    pack_button_table(buttons, &mut pkt);
    apply_checksum(&mut pkt);
    pkt
}

/// Five `0x09` button-map blocks (profile indexes `0..=4`).
pub fn helper_block_packets_with(
    buttons: &[ButtonBinding; NUM_BUTTONS],
) -> [Report; NUM_BUTTON_PROFILES_APPLY] {
    std::array::from_fn(|i| build_set_buttons_packet(i as u8, buttons))
}

#[allow(dead_code)]
pub fn helper_block_packets() -> [Report; NUM_BUTTON_PROFILES_APPLY] {
    helper_block_packets_with(&DEFAULT_BUTTONS)
}

pub fn build_profile_packet(profile: &Profile) -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_PROFILE;
    pkt[2] = TAG_AE;
    pkt[4] = PROFILE_HDR;
    pkt[OFF_LIGHT_MODE] = profile.light_mode;
    pkt[OFF_POLL] = profile.poll.poll_code();
    pkt[OFF_STAGES] = NUM_DPI_SLOTS as u8;
    pkt[OFF_ACTIVE_SLOT] = profile.active_slot;
    for (i, &dpi) in profile.dpi.iter().enumerate() {
        let off = OFF_DPI0 + i * 2;
        let le = dpi.to_le_bytes();
        pkt[off] = le[0];
        pkt[off + 1] = le[1];
    }
    for (i, rgb) in profile.rgb.iter().enumerate() {
        let off = OFF_RGB0 + i * 3;
        pkt[off] = rgb[0];
        pkt[off + 1] = rgb[1];
        pkt[off + 2] = rgb[2];
    }
    pkt[OFF_SCROLL_FLAG] = profile.scroll_flag;
    pkt[OFF_LIFTOFF] = profile.liftoff_height;
    pkt[OFF_SENSOR_FLAG] = profile.sensor_flag;
    pkt[OFF_BUTTON_RESPOND] = profile.button_respondtime;
    pkt[OFF_SLEEP_LIGHT] = profile.sleep_light;
    pkt[OFF_ESPORTS_FLAG] = profile.e_sports_flag;
    pkt[49..64].copy_from_slice(&PROFILE_FOOTER);
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
    seq.extend(helper_block_packets_with(&profile.buttons));
    seq.push(build_profile_packet(profile));
    seq.push(build_active_slot_packet(profile));
    seq.push(build_poll_packet(profile));
    seq
}

/// GET profile request (`0x0E`), captured when the official software opens.
pub fn build_get_profile_packet() -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_GET_PROFILE;
    pkt[2] = TAG_A5;
    pkt[4] = PROFILE_HDR;
    apply_checksum(&mut pkt);
    pkt
}

/// GET info (`0x30`) — first request in the official open sequence.
pub fn build_get_info_packet() -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_GET_INFO;
    pkt[2] = TAG_A5;
    pkt[4] = PROFILE_HDR;
    apply_checksum(&mut pkt);
    pkt
}

/// GET button map (`0x08`) — six packets with profile index `0x00..=0x05`.
/// Empty body; checksum = `sum([4:])` = `0x20 + index` (matches open captures).
pub fn build_get_aux_packet(index: u8) -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_GET_BUTTONS;
    pkt[2] = TAG_A5;
    pkt[4] = 0x20;
    pkt[7] = index;
    apply_checksum(&mut pkt);
    pkt
}

/// Parse a GET `0x08` / SET `0x09` report into (profile_index, bindings).
pub fn parse_button_map_report(packet: &Report) -> Option<(u8, [ButtonBinding; NUM_BUTTONS])> {
    let cmd = packet[1];
    if cmd != CMD_GET_BUTTONS && cmd != CMD_SET_BUTTONS {
        return None;
    }
    if packet[2] != TAG_A5 || packet[4] != 0x20 {
        return None;
    }
    Some((packet[7], unpack_button_table(packet)))
}

/// Ident probe (`0x03`) — last open packet; response carries ASCII like `YJX.co.m`.
pub fn build_ident_packet() -> Report {
    let mut pkt = blank_report();
    pkt[0] = MAGIC_OUT;
    pkt[1] = CMD_IDENT;
    pkt
}

/// Official open/read prelude before GET profile (from `open-software-in-vm.pcapng`).
pub fn build_open_prelude() -> Vec<Report> {
    let mut seq = Vec::with_capacity(8);
    seq.push(build_get_info_packet());
    for i in 0..6u8 {
        seq.push(build_get_aux_packet(i));
    }
    seq.push(build_ident_packet());
    seq
}

pub fn unpack_dpi_table(packet: &[u8; REPORT_SIZE]) -> [u16; NUM_DPI_SLOTS] {
    let mut dpi = [0u16; NUM_DPI_SLOTS];
    for i in 0..NUM_DPI_SLOTS {
        let off = OFF_DPI0 + i * 2;
        dpi[i] = u16::from_le_bytes([packet[off], packet[off + 1]]);
    }
    dpi
}

pub fn unpack_rgb_table(packet: &[u8; REPORT_SIZE]) -> [[u8; 3]; NUM_DPI_SLOTS] {
    let mut rgb = [[0u8; 3]; NUM_DPI_SLOTS];
    for i in 0..NUM_DPI_SLOTS {
        let off = OFF_RGB0 + i * 3;
        rgb[i] = [packet[off], packet[off + 1], packet[off + 2]];
    }
    rgb
}

pub fn parse_inbound(packet: &[u8]) -> Option<DeviceEvent> {
    if packet.len() < REPORT_SIZE || packet[0] != MAGIC_IN {
        return None;
    }
    let cmd = packet[1];
    match cmd {
        CMD_NOTIFY => parse_fa_report(packet),
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
        CMD_IDENT => {
            let ascii: String = packet[8..]
                .iter()
                .copied()
                .take_while(|&b| b != 0)
                .filter(|&b| b.is_ascii_graphic() || b == b'.' || b == b' ')
                .map(char::from)
                .collect();
            if ascii.is_empty() {
                Some(DeviceEvent::Echo { cmd })
            } else {
                Some(DeviceEvent::Serial(ascii))
            }
        }
        CMD_GET_BUTTONS | CMD_SET_BUTTONS => {
            let mut report = blank_report();
            report.copy_from_slice(&packet[..REPORT_SIZE]);
            parse_button_map_report(&report).map(|(profile_index, bindings)| {
                DeviceEvent::Buttons {
                    profile_index,
                    bindings,
                }
            })
        }
        // Official open GET 0x30: driver feeds [8]/[9] into SetBatteryInfo.
        // Prefer FA `0xD0` for live UI (see `BatteryTracker`); this is a seed.
        CMD_GET_INFO => {
            let percent = packet[8];
            let flags = packet[9];
            if percent == 0 && flags == 0 {
                Some(DeviceEvent::Echo { cmd })
            } else {
                Some(DeviceEvent::Battery {
                    info: BatteryInfo {
                        percent: BatteryInfo::clamp_percent(percent),
                        flags,
                    },
                    source: BatterySource::GetInfo,
                })
            }
        }
        _ => Some(DeviceEvent::Echo { cmd }),
    }
}

/// `0xFA` multiplex — matches DeviceDriver.exe dispatch at `0x42cb09`..`0x42cd23`:
///
/// | marker `[8]` | meaning | `[9]` | `[10]` |
/// |--------------|---------|-------|--------|
/// | `0x50`/`0x60` | notify/status (NOT battery) | code | — |
/// | `0xD0` | battery → SetBatteryInfo | percent | flags |
/// | `0x10` | active DPI stage | slot | poll_code |
/// | `0x11` | light_mode | mode (≤6) | — |
///
/// Important: do **not** treat header `0x38` alone as battery — that mis-parses
/// notify frames and surfaces bogus percentages (classic 1%–6% / status-code bug).
fn parse_fa_report(packet: &[u8]) -> Option<DeviceEvent> {
    let marker = packet[8];
    let b9 = packet[9];
    let b10 = packet[10];

    match marker {
        FA_MARKER_NOTIFY_A | FA_MARKER_NOTIFY_B => Some(DeviceEvent::Notify {
            marker,
            code: b9,
        }),
        FA_MARKER_BATTERY => Some(DeviceEvent::Battery {
            info: BatteryInfo {
                percent: BatteryInfo::clamp_percent(b9),
                flags: b10,
            },
            source: BatterySource::Fa,
        }),
        FA_MARKER_STAGE => {
            let slot = b9;
            if !(1..=NUM_DPI_SLOTS as u8).contains(&slot) {
                return Some(DeviceEvent::Unknown { cmd: CMD_NOTIFY });
            }
            Some(DeviceEvent::ActiveStage(ActiveStageInfo {
                active_slot: slot,
                poll_code: b10,
            }))
        }
        FA_MARKER_LIGHT => Some(DeviceEvent::LightMode(LightModeInfo {
            mode: b9.min(6),
        })),
        _ => Some(DeviceEvent::Unknown { cmd: CMD_NOTIFY }),
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
            ..Profile::default()
        };
        let built = build_profile_packet(&profile);
        assert_eq!(built, captured);
        assert_eq!(unpack_rgb_table(&built), DEFAULT_RGB);
    }

    #[test]
    fn checksum_matches_captured_0x0f_slot2() {
        let profile = Profile {
            dpi: [800, 2000, 3200, 800, 2400, 3200],
            active_slot: 2,
            poll: PollRate::Hz500,
            ..Profile::default()
        };
        let built = build_profile_packet(&profile);
        let captured = hex_to_report(
            "550faed82e00000000000306022003d007800c20036009800cff00000000ff80008000ff00ffff0000ffff000000000000ff010affff00000000000000000000",
        );
        assert_eq!(built, captured);
    }

    #[test]
    fn rgb_roundtrip_custom() {
        let mut profile = Profile::default();
        profile.rgb[0] = [1, 2, 3];
        profile.rgb[5] = [10, 20, 30];
        profile.scroll_flag = 1;
        profile.liftoff_height = 2;
        profile.light_mode = 3;
        let pkt = build_profile_packet(&profile);
        let parsed = Profile::from_profile_report(&pkt).unwrap();
        assert_eq!(parsed.rgb[0], [1, 2, 3]);
        assert_eq!(parsed.rgb[5], [10, 20, 30]);
        assert_eq!(parsed.scroll_flag, 1);
        assert_eq!(parsed.liftoff_height, 2);
        assert_eq!(parsed.light_mode, 3);
    }

    #[test]
    fn button_map_set_matches_apply_capture() {
        let built = build_set_buttons_packet(0, &DEFAULT_BUTTONS);
        let captured = hex_to_report(
            "5509a50720000000200100002002000020040000200800002010000021550000213801002138ff00000000000000000000000000000000000000000000000000",
        );
        assert_eq!(built, captured);
        let (idx, buttons) = parse_button_map_report(&built).unwrap();
        assert_eq!(idx, 0);
        assert_eq!(buttons, DEFAULT_BUTTONS);
        assert_eq!(buttons[0].label_short(), "L-click");
        assert_eq!(buttons[5].label_short(), "DPI loop");
        assert_eq!(buttons[7].label_short(), "DPI-");
    }

    #[test]
    fn button_map_get_request_matches_open_capture() {
        let built = build_get_aux_packet(0);
        let captured = hex_to_report(
            "5508a520200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        assert_eq!(built, captured);
        let built5 = build_get_aux_packet(5);
        assert_eq!(built5[3], 0x25);
        assert_eq!(built5[7], 5);
    }

    #[test]
    fn helper_blocks_are_default_button_maps() {
        let blocks = helper_block_packets();
        for (i, pkt) in blocks.iter().enumerate() {
            assert_eq!(pkt[1], CMD_SET_BUTTONS);
            assert_eq!(pkt[7], i as u8);
            assert_eq!(unpack_button_table(pkt), DEFAULT_BUTTONS);
        }
    }

    #[test]
    fn sensor_flag_db_wire_roundtrip_known_bits() {
        assert_eq!(sensor_flag_db_to_wire(0), 0);
        assert_eq!(sensor_flag_db_to_wire(SENSOR_DB_RIPPLE), SENSOR_WIRE_RIPPLE);
        assert_eq!(
            sensor_flag_db_to_wire(SENSOR_DB_ANGLE_SNAP),
            SENSOR_WIRE_ANGLE_SNAP
        );
        assert_eq!(
            sensor_flag_db_to_wire(SENSOR_DB_MOTION_SYNC),
            SENSOR_WIRE_MOTION_SYNC
        );
        assert_eq!(
            sensor_flag_db_to_wire(
                SENSOR_DB_RIPPLE | SENSOR_DB_ANGLE_SNAP | SENSOR_DB_MOTION_SYNC
            ),
            0x31
        );
        assert_eq!(
            sensor_flag_wire_to_db(0x31),
            SENSOR_DB_RIPPLE | SENSOR_DB_ANGLE_SNAP | SENSOR_DB_MOTION_SYNC
        );
        assert_eq!(sensor_flag_wire_nudge(0, 1), SENSOR_WIRE_ANGLE_SNAP);
        assert_eq!(
            sensor_flag_wire_nudge(SENSOR_WIRE_ANGLE_SNAP, 1),
            SENSOR_WIRE_RIPPLE
        );
        assert_eq!(
            sensor_flag_wire_nudge(SENSOR_WIRE_RIPPLE, -1),
            SENSOR_WIRE_ANGLE_SNAP
        );
    }

    #[test]
    fn vk_to_hid_usage_basic() {
        assert_eq!(vk_to_hid_usage(0x41), Some(0x04)); // A
        assert_eq!(vk_to_hid_usage(0x5a), Some(0x1d)); // Z
        assert_eq!(vk_to_hid_usage(0x31), Some(0x1e)); // 1
        assert_eq!(vk_to_hid_usage(0x30), Some(0x27)); // 0
        assert_eq!(vk_to_hid_usage(0x70), Some(0x3a)); // F1
        assert_eq!(vk_to_hid_usage(0x26), Some(0x52)); // Up
        assert_eq!(vk_to_hid_usage(0xa2), Some(0xe0)); // LCtrl
        assert_eq!(vk_to_hid_usage(0x01), None);
    }

    #[test]
    fn get_info_0x30_response_is_battery() {
        let resp = hex_to_report(
            "aa30a52e0a0000005000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        match parse_inbound(&resp) {
            Some(DeviceEvent::Battery {
                info: b,
                source: BatterySource::GetInfo,
            }) => {
                assert_eq!(b.percent, 80);
                assert_eq!(b.flags, 0);
            }
            other => panic!("expected battery from 0x30, got {other:?}"),
        }
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
            ..Default::default()
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
            ..Default::default()
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
            dpi: [800, 2400, 3200, 800, 2400, 3200],
            active_slot: 1,
            poll: PollRate::Hz500,
            ..Default::default()
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
    fn parse_battery_fa_matches_driver() {
        // idle-turn-on / open-software: aa fa ae .. 38 01 01 01 d0 50 00 → 80%
        let mut pkt = blank_report();
        pkt[0] = MAGIC_IN;
        pkt[1] = CMD_NOTIFY;
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
            DeviceEvent::Battery {
                info: b,
                source: BatterySource::Fa,
            } => {
                assert_eq!(b.percent, 80);
                assert!(!b.charging());
            }
            other => panic!("unexpected {other:?}"),
        }
    }

    #[test]
    fn parse_battery_clamps_like_driver() {
        let mut pkt = blank_report();
        pkt[0] = MAGIC_IN;
        pkt[1] = CMD_NOTIFY;
        pkt[8] = FA_MARKER_BATTERY;
        pkt[9] = 255;
        pkt[10] = 1;
        match parse_inbound(&pkt).unwrap() {
            DeviceEvent::Battery {
                info: b,
                source: BatterySource::Fa,
            } => {
                assert_eq!(b.percent, 100);
                assert!(b.charging());
            }
            other => panic!("unexpected {other:?}"),
        }
    }

    #[test]
    fn battery_tracker_rejects_cable_getinfo_full_charge_stub() {
        let mut tr = BatteryTracker::default();
        assert_eq!(
            tr.observe(
                BatteryInfo {
                    percent: 100,
                    flags: 1,
                },
                BatterySource::GetInfo
            ),
            None
        );
        let fa = BatteryInfo {
            percent: 67,
            flags: 0,
        };
        assert_eq!(tr.observe(fa.clone(), BatterySource::Fa), Some(fa));
        // Later cable GET 0x30 must not wipe FA SOC.
        assert_eq!(
            tr.observe(
                BatteryInfo {
                    percent: 100,
                    flags: 1,
                },
                BatterySource::GetInfo
            ),
            None
        );
        assert_eq!(tr.current().map(|b| b.percent), Some(67));
    }

    #[test]
    fn battery_tracker_ignores_getinfo_after_fa_and_one_percent_flicker() {
        let mut tr = BatteryTracker::default();
        let seed = BatteryInfo {
            percent: 90,
            flags: 0,
        };
        assert_eq!(
            tr.observe(seed.clone(), BatterySource::GetInfo),
            Some(seed.clone())
        );
        let fa = BatteryInfo {
            percent: 90,
            flags: 0,
        };
        // Same percent after seed — no change.
        assert_eq!(tr.observe(fa.clone(), BatterySource::Fa), None);
        // First 1% flicker is held pending.
        let flick = BatteryInfo {
            percent: 92,
            flags: 0,
        };
        // 2% moves apply immediately (not flicker).
        std::thread::sleep(BatteryTracker::THROTTLE + std::time::Duration::from_millis(5));
        assert_eq!(
            tr.observe(flick.clone(), BatterySource::Fa),
            Some(flick.clone())
        );
        // GET 0x30 must not override live FA.
        assert_eq!(
            tr.observe(
                BatteryInfo {
                    percent: 80,
                    flags: 0
                },
                BatterySource::GetInfo
            ),
            None
        );
        assert_eq!(tr.current().map(|b| b.percent), Some(92));

        // ±1% needs two matching samples.
        std::thread::sleep(BatteryTracker::THROTTLE + std::time::Duration::from_millis(5));
        let one = BatteryInfo {
            percent: 91,
            flags: 0,
        };
        assert_eq!(tr.observe(one.clone(), BatterySource::Fa), None);
        std::thread::sleep(BatteryTracker::THROTTLE + std::time::Duration::from_millis(5));
        assert_eq!(tr.observe(one.clone(), BatterySource::Fa), Some(one));
    }

    #[test]
    fn hdr_38_alone_is_not_battery() {
        // Regression: old TUI treated any [4]=0x38 as battery and showed notify codes as %.
        let mut pkt = blank_report();
        pkt[0] = MAGIC_IN;
        pkt[1] = CMD_NOTIFY;
        pkt[4] = FA_HDR_BATTERY;
        pkt[8] = FA_MARKER_NOTIFY_A; // 0x50
        pkt[9] = 3;
        pkt[10] = 0;
        match parse_inbound(&pkt).unwrap() {
            DeviceEvent::Notify { marker, code } => {
                assert_eq!(marker, 0x50);
                assert_eq!(code, 3);
            }
            other => panic!("notify misparsed as {other:?}"),
        }
    }

    #[test]
    fn parse_active_stage_fa_not_battery() {
        let mut pkt = blank_report();
        pkt[0] = MAGIC_IN;
        pkt[1] = CMD_NOTIFY;
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
    }

    #[test]
    fn parse_light_mode_fa() {
        let mut pkt = blank_report();
        pkt[0] = MAGIC_IN;
        pkt[1] = CMD_NOTIFY;
        pkt[8] = FA_MARKER_LIGHT;
        pkt[9] = 9; // driver clamps to 6
        match parse_inbound(&pkt).unwrap() {
            DeviceEvent::LightMode(l) => assert_eq!(l.mode, 6),
            other => panic!("unexpected {other:?}"),
        }
    }

    #[test]
    fn helpers_match_capture_magic() {
        let inits = helper_init_packets();
        assert_eq!(&inits[0][..6], &[0x55, 0x0D, 0x00, 0x38, 0x38, 0x00]);
        assert_eq!(&inits[1][..6], &[0x55, 0x0D, 0x00, 0x40, 0x08, 0x38]);
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
    fn get_info_matches_open_capture() {
        let built = build_get_info_packet();
        let captured = hex_to_report(
            "5530a52e2e0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        );
        assert_eq!(built, captured);
    }

    #[test]
    fn get_aux0_matches_open_capture() {
        let built = build_get_aux_packet(0);
        assert_eq!(&built[..8], &[0x55, 0x08, 0xA5, 0x20, 0x20, 0x00, 0x00, 0x00]);
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

    #[test]
    fn open_prelude_cmd_order() {
        let cmds: Vec<u8> = build_open_prelude().iter().map(|p| p[1]).collect();
        assert_eq!(cmds, vec![0x30, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03]);
    }
}
