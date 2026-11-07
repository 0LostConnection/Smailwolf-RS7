//! Shared protocol, HID worker, i18n, and profile helpers for RS7 tools.

pub mod actions;
pub mod device;
pub mod i18n;
pub mod protocol;

pub use actions::{cycle_button5, merge_profile_rgb, set_active_slot, set_dpi};
pub use device::{DeviceError, DeviceInfo, DeviceToHost, DeviceWorker, HostToDevice};
pub use i18n::{
    connection_label, esports_label, lod_label, scroll_label, Locale, Msg, t,
};
pub use protocol::*;
