use rs7_core::protocol::{
    build_get_profile_packet, build_open_prelude, parse_inbound, ConnectionMode, Profile, PID,
    CONFIG_INTERFACE, USAGE_PAGE_VENDOR, VID_RECEIVER, VID_WIRED, REPORT_SIZE,
};
use hidapi::HidApi;
use std::time::{Duration, Instant};

fn main() {
    let api = HidApi::new().expect("hidapi");
    println!("=== enumeration ===");
    let mut targets = Vec::new();
    for d in api.device_list() {
        let vid = d.vendor_id();
        let pid = d.product_id();
        if pid != PID || (vid != VID_WIRED && vid != VID_RECEIVER) {
            continue;
        }
        if d.interface_number() != CONFIG_INTERFACE && d.usage_page() != USAGE_PAGE_VENDOR {
            continue;
        }
        // Dedup by path
        let path = d.path().to_string_lossy().into_owned();
        if targets.iter().any(|(_, p, _, _)| p == &path) {
            continue;
        }
        let mode = ConnectionMode::from_vid(vid).unwrap();
        println!(
            "{:?} iface={} up={:04x} path={path}",
            mode,
            d.interface_number(),
            d.usage_page()
        );
        targets.push((vid, path, d.interface_number(), d.usage_page()));
    }

    // Current finder preference
    let mut sorted = targets.clone();
    sorted.sort_by_key(|(_, _, iface, up)| {
        let iface_ok = *iface == CONFIG_INTERFACE;
        let usage_ok = *up == USAGE_PAGE_VENDOR;
        (!iface_ok, !usage_ok)
    });
    println!("current pick would be: {:?}", sorted.first());

    for (vid, path, _, _) in targets {
        let mode = ConnectionMode::from_vid(vid).unwrap();
        print!("\n=== try {mode:?} {path} ===\n");
        let Some(dinfo) = api.device_list().find(|d| d.path().to_string_lossy() == path) else {
            println!("path vanished");
            continue;
        };
        let dev = match dinfo.open_device(&api) {
            Ok(d) => d,
            Err(e) => {
                println!("open FAIL: {e}");
                continue;
            }
        };
        let _ = dev.set_blocking_mode(false);
        for pkt in build_open_prelude() {
            let mut out = Vec::with_capacity(REPORT_SIZE + 1);
            out.push(0);
            out.extend_from_slice(&pkt);
            match dev.write(&out) {
                Ok(n) => println!("prelude cmd=0x{:02x} wrote {n}", pkt[1]),
                Err(e) => println!("prelude cmd=0x{:02x} WRITE FAIL: {e}", pkt[1]),
            }
            drain(&dev, Duration::from_millis(80));
        }
        let pkt = build_get_profile_packet();
        let mut out = Vec::with_capacity(REPORT_SIZE + 1);
        out.push(0);
        out.extend_from_slice(&pkt);
        match dev.write(&out) {
            Ok(n) => println!("GET 0x0E wrote {n}"),
            Err(e) => {
                println!("GET 0x0E WRITE FAIL: {e}");
                continue;
            }
        }
        let deadline = Instant::now() + Duration::from_millis(500);
        let mut got = false;
        while Instant::now() < deadline {
            let mut buf = [0u8; REPORT_SIZE + 1];
            match dev.read_timeout(&mut buf, 50) {
                Ok(n) if n > 0 => {
                    let report = if n == REPORT_SIZE + 1 && buf[0] == 0 {
                        buf[1..].try_into().unwrap()
                    } else {
                        let mut r = [0u8; REPORT_SIZE];
                        r[..n.min(REPORT_SIZE)].copy_from_slice(&buf[..n.min(REPORT_SIZE)]);
                        r
                    };
                    println!("IN magic=0x{:02x} cmd=0x{:02x}", report[0], report[1]);
                    if let Some(p) = Profile::from_profile_report(&report) {
                        println!(
                            "PROFILE OK slot={} poll={:?} dpi={:?}",
                            p.active_slot, p.poll, p.dpi
                        );
                        got = true;
                        break;
                    }
                    if let Some(ev) = parse_inbound(&report) {
                        println!("event: {ev:?}");
                    }
                }
                _ => {}
            }
        }
        if !got {
            println!("NO PROFILE RESPONSE");
        }
    }
}

fn drain(dev: &hidapi::HidDevice, for_ms: Duration) {
    let deadline = Instant::now() + for_ms;
    while Instant::now() < deadline {
        let mut buf = [0u8; REPORT_SIZE + 1];
        match dev.read_timeout(&mut buf, 20) {
            Ok(n) if n > 0 => {
                let cmd = if n == REPORT_SIZE + 1 && buf[0] == 0 { buf[2] } else { buf[1] };
                println!("  drain cmd=0x{cmd:02x} n={n}");
            }
            _ => break,
        }
    }
}
