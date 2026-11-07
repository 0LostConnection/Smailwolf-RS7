# Smailwolf RS7

TUI + GUI Linux tools to configure the **Smailwolf RS7** mouse (YJX chip). Protocol notes live in [`PROTOCOL.md`](PROTOCOL.md).

No Piper / libratbag / OpenRGB support yet.

## What it does

- Detects cable (`a8a4:2255`) or 2.4G receiver (`a8a5:2255`) on **MI_02**
- On open, mirrors the official software prelude (`0x30` / `0x08`×6 / GET `0x0E` / `0x03`)
- Shows battery (FA marker **`0xD0`**) and hardware slot changes (marker `0x10`)
- Edits 6 DPI slots (200–24000), active slot, report rate, scroll/LOD/sensor/e-sports, button 5 cycle
- Apply sends the official sequence: `0x0D`×2 → `0x10` → `0x09`×5 → `0x0F` → `0x22` → `0x23`
- UI languages: **pt_BR** and **en_US** (TUI: `l` · GUI: language button)

## Warning

**Do not send random HID packets.** Only observed templates with a correct checksum. Invented spam can corrupt the profile — keep the Windows driver handy if you need a reset.

## Build / run

```bash
# udev (required)
sudo cp udev/99-smailwolf-rs7.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
# replug the dongle; mouse must NOT be passed through to a VM

cargo test
cargo run -p rs7-tui --release   # terminal UI → target/release/rs7-tui
cargo run -p rs7-gui --release   # GPUI desktop → target/release/rs7-gui
```

## TUI shortcuts

| Key | Action |
|-----|--------|
| `Tab` / `↑` `↓` | Navigate |
| `←` `→` | Adjust focused value |
| `Enter` | Edit DPI / activate |
| **`Ctrl+S`** | **Apply profile to mouse** |
| `r` | Refresh profile (`0x0E`) |
| `+` `-` | DPI ±100 |
| `[` `]` `{` `}` `,` `.` | RGB ±16 |
| `b` | Cycle button 5 |
| `l` | Toggle pt_BR / en_US |
| `q` / `Esc` | Quit |

## Layout

| Path | Contents |
|------|----------|
| `crates/rs7-core/` | Shared protocol, HID worker, i18n, profile helpers |
| `crates/rs7-tui/` | Ratatui terminal UI |
| `crates/rs7-gui/` | GPUI Kit desktop UI |
| `udev/` | hidraw udev rule |
| `PROTOCOL.md` | YJX protocol map |
| `captures/` | usbmon / pcapng from RE |
| `docs/` | Official UI screenshot |
| `HANDOFF.md` | Continuity notes |
| `software/mouse-RS7-1.2/` | Official Windows app |
| `software/RS7.gpr` | Local Ghidra project |

## Linux note

HID writes use report ID prefix **`0x00`** + 64 bytes. Without it the kernel treats `0x55` as the report ID and Apply appears to succeed with no effect.
