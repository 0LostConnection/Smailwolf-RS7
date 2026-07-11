fn main() {
    let api = hidapi::HidApi::new().expect("hidapi");
    for d in api.device_list() {
        let vid = d.vendor_id();
        let pid = d.product_id();
        if pid == 0x2255 && (vid == 0xa8a4 || vid == 0xa8a5) {
            println!(
                "vid={:04x} pid={:04x} iface={:?} usage_page={:04x} usage={:04x} path={}",
                vid,
                pid,
                d.interface_number(),
                d.usage_page(),
                d.usage(),
                d.path().to_string_lossy()
            );
        }
    }
}
