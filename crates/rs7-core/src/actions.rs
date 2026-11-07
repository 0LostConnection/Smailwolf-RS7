//! Profile mutations shared by TUI and GUI.

use crate::protocol::{
    sensor_flag_wire_nudge, ButtonBinding, Profile, MACRO_TYPE_MULTIMEDIA, MACRO_TYPE_SHORTCUT,
    MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_AIM, MACRO_VAL_DPI_LOOP, MACRO_VAL_DPI_STEP, MEDIA_MUTE,
    MEDIA_PLAY_PAUSE, MEDIA_VOL_DOWN, MEDIA_VOL_UP, NUM_DPI_SLOTS, SHORTCUT_GROUP_POLL,
};

/// Cycle physical button 5 through DPI specials, poll shortcuts, and media.
pub fn cycle_button5(profile: &mut Profile) -> ButtonBinding {
    const IDX: usize = 5;
    let cur = profile.buttons[IDX];
    let next = match (cur.macro_type, cur.value, cur.value2) {
        (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_LOOP, _) => {
            ButtonBinding::new(MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_AIM, 0, 0)
        }
        (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_AIM, _) => {
            ButtonBinding::new(MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0x01, 0)
        }
        (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0x01) => {
            ButtonBinding::new(MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0xff, 0)
        }
        (MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_STEP, 0xff) => {
            ButtonBinding::new(MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 1, 0)
        }
        (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 1) => {
            ButtonBinding::new(MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 2, 0)
        }
        (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 2) => {
            ButtonBinding::new(MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 3, 0)
        }
        (MACRO_TYPE_SHORTCUT, SHORTCUT_GROUP_POLL, 3) => {
            ButtonBinding::new(MACRO_TYPE_MULTIMEDIA, MEDIA_PLAY_PAUSE, 0, 0)
        }
        (MACRO_TYPE_MULTIMEDIA, MEDIA_PLAY_PAUSE, _) => {
            ButtonBinding::new(MACRO_TYPE_MULTIMEDIA, MEDIA_MUTE, 0, 0)
        }
        (MACRO_TYPE_MULTIMEDIA, MEDIA_MUTE, _) => {
            ButtonBinding::new(MACRO_TYPE_MULTIMEDIA, MEDIA_VOL_UP, 0, 0)
        }
        (MACRO_TYPE_MULTIMEDIA, MEDIA_VOL_UP, _) => {
            ButtonBinding::new(MACRO_TYPE_MULTIMEDIA, MEDIA_VOL_DOWN, 0, 0)
        }
        (MACRO_TYPE_MULTIMEDIA, MEDIA_VOL_DOWN, _) => ButtonBinding::disabled(),
        _ => ButtonBinding::new(MACRO_TYPE_SPECIAL, MACRO_VAL_DPI_LOOP, 0, 0),
    };
    profile.buttons[IDX] = next;
    next
}

pub fn set_dpi(profile: &mut Profile, slot: usize, value: u16) {
    let idx = slot.min(NUM_DPI_SLOTS - 1);
    profile.dpi[idx] = Profile::clamp_dpi(value);
}

pub fn set_active_slot(profile: &mut Profile, slot: u8) {
    profile.active_slot = slot.clamp(1, NUM_DPI_SLOTS as u8);
}

pub fn nudge_sensor(profile: &mut Profile, dir: i8) {
    profile.sensor_flag = sensor_flag_wire_nudge(profile.sensor_flag, dir);
}

/// Prefer non-black RGB from `incoming` when the device GET blanks colors.
pub fn merge_profile_rgb(current: &Profile, incoming: &mut Profile) {
    for i in 0..NUM_DPI_SLOTS {
        let rgb = incoming.rgb[i];
        if rgb == [0, 0, 0] {
            incoming.rgb[i] = current.rgb[i];
        }
    }
}
