//! Smailwolf RS7 — TUI HID configurator.

mod ui;

use std::io;
use ui::App;

fn main() -> io::Result<()> {
    let mut terminal = ratatui::init();
    let result = App::new().run(&mut terminal);
    ratatui::restore();
    result
}
