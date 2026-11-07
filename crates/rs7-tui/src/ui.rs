//! Terminal UI for Smailwolf RS7 (pt_BR / en_US).

use rs7_core::actions::cycle_button5;
use rs7_core::device::{DeviceInfo, DeviceToHost, DeviceWorker};
use rs7_core::i18n::{esports_label, lod_label, scroll_label, t, Locale, Msg};
use rs7_core::protocol::{
    sensor_flag_wire_nudge, BatteryInfo, BatteryTracker, ConnectionMode, DeviceEvent, PollRate,
    Profile, DPI_MAX, DPI_MIN, NUM_DPI_SLOTS, SENSOR_WIRE_ANGLE_SNAP, SENSOR_WIRE_MOTION_SYNC,
    SENSOR_WIRE_RIPPLE,
};
use crossterm::event::{self, Event, KeyCode, KeyEvent, KeyEventKind, KeyModifiers};
use ratatui::layout::{Constraint, Direction, Layout, Rect};
use ratatui::style::{Color, Modifier, Style};
use ratatui::text::{Line, Span};
use ratatui::widgets::{Block, Borders, Clear, Gauge, List, ListItem, Paragraph, Wrap};
use ratatui::{DefaultTerminal, Frame};
use std::time::{Duration, Instant};

const MAX_LOG: usize = 80;
const BRAND: &str = "Smailwolf RS7";

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Focus {
    DpiSlot(usize),
    ActiveSlot,
    PollRate,
    ScrollFlag,
    Liftoff,
    LightMode,
    SensorFlag,
    EsportsFlag,
    Debounce,
    SleepLight,
    Apply,
    Log,
}

impl Focus {
    fn next(self) -> Self {
        match self {
            Self::DpiSlot(i) if i + 1 < NUM_DPI_SLOTS => Self::DpiSlot(i + 1),
            Self::DpiSlot(_) => Self::ActiveSlot,
            Self::ActiveSlot => Self::PollRate,
            Self::PollRate => Self::ScrollFlag,
            Self::ScrollFlag => Self::Liftoff,
            Self::Liftoff => Self::LightMode,
            Self::LightMode => Self::SensorFlag,
            Self::SensorFlag => Self::EsportsFlag,
            Self::EsportsFlag => Self::Debounce,
            Self::Debounce => Self::SleepLight,
            Self::SleepLight => Self::Apply,
            Self::Apply => Self::Log,
            Self::Log => Self::DpiSlot(0),
        }
    }

    fn prev(self) -> Self {
        match self {
            Self::DpiSlot(0) => Self::Log,
            Self::DpiSlot(i) => Self::DpiSlot(i - 1),
            Self::ActiveSlot => Self::DpiSlot(NUM_DPI_SLOTS - 1),
            Self::PollRate => Self::ActiveSlot,
            Self::ScrollFlag => Self::PollRate,
            Self::Liftoff => Self::ScrollFlag,
            Self::LightMode => Self::Liftoff,
            Self::SensorFlag => Self::LightMode,
            Self::EsportsFlag => Self::SensorFlag,
            Self::Debounce => Self::EsportsFlag,
            Self::SleepLight => Self::Debounce,
            Self::Apply => Self::SleepLight,
            Self::Log => Self::Apply,
        }
    }
}

pub struct App {
    profile: Profile,
    focus: Focus,
    editing: bool,
    edit_buf: String,
    connected: Option<DeviceInfo>,
    battery: Option<BatteryInfo>,
    battery_tracker: BatteryTracker,
    light_mode: Option<u8>,
    serial: Option<String>,
    logs: Vec<String>,
    status: String,
    applying: bool,
    should_quit: bool,
    locale: Locale,
    worker: DeviceWorker,
}

impl App {
    pub fn new() -> Self {
        let mut app = Self {
            profile: Profile::default(),
            focus: Focus::DpiSlot(0),
            editing: false,
            edit_buf: String::new(),
            connected: None,
            battery: None,
            battery_tracker: BatteryTracker::default(),
            light_mode: None,
            serial: None,
            logs: Vec::new(),
            status: t(Msg::SearchingDevice, Locale::PtBr).into(),
            applying: false,
            should_quit: false,
            locale: Locale::PtBr,
            worker: DeviceWorker::spawn(),
        };
        app.bootstrap_logs();
        app
    }

    fn bootstrap_logs(&mut self) {
        self.log(t(Msg::HelpTui, self.locale));
        self.log(t(Msg::HelpRgb, self.locale));
        self.log(t(Msg::HelpBtn5, self.locale));
        self.log(t(Msg::HelpSensor, self.locale));
        self.log(t(Msg::HelpLang, self.locale));
    }

    fn toggle_locale(&mut self) {
        self.locale = self.locale.toggle();
        self.status = t(Msg::LanguageSwitched, self.locale).into();
        self.log(format!("{} → {}", t(Msg::Language, self.locale), self.locale.label()));
    }

    pub fn run(mut self, terminal: &mut DefaultTerminal) -> std::io::Result<()> {
        let tick = Duration::from_millis(50);
        let mut last = Instant::now();
        while !self.should_quit {
            terminal.draw(|f| self.draw(f))?;
            self.drain_device();

            let timeout = tick.saturating_sub(last.elapsed());
            if event::poll(timeout)? {
                if let Event::Key(key) = event::read()? {
                    if key.kind == KeyEventKind::Press {
                        self.on_key(key);
                    }
                }
            }
            if last.elapsed() >= tick {
                last = Instant::now();
            }
        }
        Ok(())
    }

    fn log(&mut self, msg: impl Into<String>) {
        let stamp = chrono_lite();
        self.logs.push(format!("[{stamp}] {}", msg.into()));
        if self.logs.len() > MAX_LOG {
            let skip = self.logs.len() - MAX_LOG;
            self.logs.drain(0..skip);
        }
    }

    fn drain_device(&mut self) {
        loop {
            match self.worker.try_recv() {
                Ok(DeviceToHost::Opened(info)) => {
                    // Keep last FA battery across cable↔dongle (cable GET 0x30
                    // often lies with 100%).
                    let mode = info.mode.label(self.locale);
                    self.status = format!("{mode} — {}", info.product);
                    self.log(format!("{mode} / {}", info.path));
                    self.connected = Some(info);
                }
                Ok(DeviceToHost::Disconnected) => {
                    self.connected = None;
                    self.battery = None;
                    self.battery_tracker = BatteryTracker::default();
                    self.status = t(Msg::SearchingDevice, self.locale).into();
                    self.log(t(Msg::Disconnected, self.locale));
                }
                Ok(DeviceToHost::Profile(mut profile)) => {
                    // GET 0x0E often blanks RGB; keep any custom colors already in the UI.
                    if profile.rgb == rs7_core::protocol::DEFAULT_RGB
                        && self.profile.rgb != rs7_core::protocol::DEFAULT_RGB
                    {
                        profile.rgb = self.profile.rgb;
                    }
                    // Button maps come from GET 0x08, not 0x0E — keep what open prelude filled.
                    profile.buttons = self.profile.buttons;
                    self.profile = profile;
                    self.log(format!(
                        "Perfil lido: slot {} · {} · DPI {:?} · RGB[0]={:?}",
                        self.profile.active_slot,
                        self.profile.poll.label(),
                        self.profile.dpi,
                        self.profile.rgb[0]
                    ));
                    self.status = format!(
                        "{} — slot {} @ {}.",
                        t(Msg::ConfigLoaded, self.locale),
                        self.profile.active_slot,
                        self.profile.poll.label()
                    );
                }
                Ok(DeviceToHost::Event(ev)) => self.on_device_event(ev),
                Ok(DeviceToHost::ApplyOk) => {
                    self.applying = false;
                    self.status = t(Msg::ApplyOk, self.locale).into();
                    self.log("Apply OK — 0x0D/0x10/0x09/0x0F/0x22/0x23.");
                }
                Ok(DeviceToHost::ApplyErr(err)) => {
                    self.applying = false;
                    self.status = format!("{}: {err}", t(Msg::ApplyFailed, self.locale));
                    self.log(format!("{}: {err}", t(Msg::ApplyFailed, self.locale)));
                }
                Ok(DeviceToHost::Status(msg)) => {
                    self.status = msg.clone();
                    self.log(msg);
                }
                Ok(DeviceToHost::Fatal(msg)) => {
                    self.status = format!("{}: {msg}", t(Msg::FatalError, self.locale));
                    self.log(format!("{}: {msg}", t(Msg::FatalError, self.locale)));
                }
                Err(std::sync::mpsc::TryRecvError::Empty) => break,
                Err(std::sync::mpsc::TryRecvError::Disconnected) => {
                    self.log(t(Msg::WorkerDisconnected, self.locale));
                    break;
                }
            }
        }
    }

    fn on_device_event(&mut self, ev: DeviceEvent) {
        match ev {
            DeviceEvent::Battery { info, source } => {
                if let Some(b) = self.battery_tracker.observe(info, source) {
                    let charge = if b.charging() {
                        t(Msg::BatteryCharging, self.locale)
                    } else {
                        t(Msg::BatteryInUse, self.locale)
                    };
                    self.battery = Some(b.clone());
                    self.log(format!(
                        "{}: {}% ({})",
                        t(Msg::Battery, self.locale),
                        b.percent,
                        charge
                    ));
                }
            }
            DeviceEvent::ActiveStage(stage) => {
                let prev = self.profile.active_slot;
                self.profile.active_slot = stage.active_slot;
                if let Some(poll) = PollRate::from_poll_code(stage.poll_code) {
                    self.profile.poll = poll;
                }
                if prev != stage.active_slot {
                    self.log(format!(
                        "{}: {} → {} (poll_code={})",
                        t(Msg::SlotSelectedHw, self.locale),
                        prev,
                        stage.active_slot,
                        stage.poll_code
                    ));
                    self.status = format!(
                        "{} {}.",
                        t(Msg::SlotSelectedDpi, self.locale),
                        stage.active_slot
                    );
                }
            }
            DeviceEvent::LightMode(l) => {
                self.light_mode = Some(l.mode);
                self.profile.light_mode = l.mode;
                self.log(format!("light_mode = {}", l.mode));
            }
            DeviceEvent::Notify { marker, code } => {
                self.log(format!("Notify FA marker=0x{marker:02X} code={code}"));
            }
            DeviceEvent::Serial(s) => {
                if !s.is_empty() {
                    self.log(format!("Serial/ID: {s}"));
                    self.serial = Some(s);
                }
            }
            DeviceEvent::Link => self.log("Link/status (0xED) recebido."),
            DeviceEvent::Buttons {
                profile_index,
                bindings,
            } => {
                if profile_index == 0 {
                    self.profile.buttons = bindings;
                }
                if profile_index == 0
                    || bindings != rs7_core::protocol::DEFAULT_BUTTONS
                {
                    let summary: String = bindings
                        .iter()
                        .map(|b| b.label_short())
                        .collect::<Vec<_>>()
                        .join(", ");
                    self.log(format!(
                        "{} p{profile_index}: {summary}",
                        t(Msg::ButtonsProfile, self.locale)
                    ));
                }
            }
            DeviceEvent::Echo { cmd } => {
                if !self.applying {
                    self.log(format!("Eco cmd 0x{cmd:02X}"));
                }
            }
            DeviceEvent::Unknown { cmd } => self.log(format!("IN desconhecido 0x{cmd:02X}")),
        }
    }

    fn on_key(&mut self, key: KeyEvent) {
        if key.modifiers.contains(KeyModifiers::CONTROL)
            && matches!(key.code, KeyCode::Char('s') | KeyCode::Char('S'))
        {
            if self.editing {
                self.commit_edit();
            }
            self.do_apply();
            return;
        }

        if self.editing {
            self.on_edit_key(key.code);
            return;
        }
        match key.code {
            KeyCode::Char('q') | KeyCode::Esc => self.should_quit = true,
            KeyCode::Char('r') => self.do_refresh(),
            KeyCode::Tab | KeyCode::Down => self.focus = self.focus.next(),
            KeyCode::BackTab | KeyCode::Up => self.focus = self.focus.prev(),
            KeyCode::Left => self.nudge(-1),
            KeyCode::Right => self.nudge(1),
            KeyCode::Enter | KeyCode::Char(' ') => self.activate(),
            KeyCode::Char('+') | KeyCode::Char('=') => self.nudge_dpi(100),
            KeyCode::Char('-') | KeyCode::Char('_') => self.nudge_dpi(-100),
            // RGB per focused DPI slot: [ ] R · { } G · , . B  (±16)
            KeyCode::Char('[') => self.nudge_rgb(0, -1),
            KeyCode::Char(']') => self.nudge_rgb(0, 1),
            KeyCode::Char('{') => self.nudge_rgb(1, -1),
            KeyCode::Char('}') => self.nudge_rgb(1, 1),
            KeyCode::Char(',') => self.nudge_rgb(2, -1),
            KeyCode::Char('.') => self.nudge_rgb(2, 1),
            KeyCode::Char('b') => self.cycle_dpi_button(),
            KeyCode::Char('l') => self.toggle_locale(),
            _ => {}
        }
    }

    /// Cycle physical button 5 through DPI specials + common media bindings.
    fn cycle_dpi_button(&mut self) {
        let next = cycle_button5(&mut self.profile);
        self.log(format!("{} → {}", t(Msg::Button5, self.locale), next.label_short()));
    }

    fn on_edit_key(&mut self, code: KeyCode) {
        match code {
            KeyCode::Esc => {
                self.editing = false;
                self.edit_buf.clear();
            }
            KeyCode::Enter => self.commit_edit(),
            KeyCode::Backspace => {
                self.edit_buf.pop();
            }
            KeyCode::Char(c) if c.is_ascii_digit() => {
                if self.edit_buf.len() < 5 {
                    self.edit_buf.push(c);
                }
            }
            _ => {}
        }
    }

    fn nudge(&mut self, dir: i8) {
        match self.focus {
            Focus::ActiveSlot => {
                let slot = self.profile.active_slot as i8 + dir;
                self.profile.active_slot = slot.clamp(1, NUM_DPI_SLOTS as i8) as u8;
            }
            Focus::PollRate => {
                self.profile.poll = if dir > 0 {
                    self.profile.poll.next()
                } else {
                    self.profile.poll.prev()
                };
            }
            Focus::ScrollFlag => {
                self.profile.scroll_flag = if dir > 0 { 1 } else { 0 };
            }
            Focus::Liftoff => {
                let v = self.profile.liftoff_height as i8 + dir;
                self.profile.liftoff_height = v.clamp(0, 2) as u8;
            }
            Focus::LightMode => {
                let v = self.profile.light_mode as i8 + dir;
                self.profile.light_mode = v.clamp(0, 6) as u8;
            }
            Focus::SensorFlag => {
                self.profile.sensor_flag = sensor_flag_wire_nudge(self.profile.sensor_flag, dir);
            }
            Focus::EsportsFlag => {
                // Driver UI writes "1"=Off / "2"=On (`FUN_0041b150`); factory GET often 0.
                let v = self.profile.e_sports_flag as i8 + dir;
                self.profile.e_sports_flag = v.clamp(0, 2) as u8;
            }
            Focus::Debounce => {
                let v = self.profile.button_respondtime as i16 + dir as i16;
                self.profile.button_respondtime = v.clamp(0, 20) as u8;
            }
            Focus::SleepLight => {
                // Driver SQLite default 20 (“SleepTime”); 0 ≈ not sleep.
                let v = self.profile.sleep_light as i16 + dir as i16;
                self.profile.sleep_light = v.clamp(0, 60) as u8;
            }
            Focus::DpiSlot(i) => {
                // Left/Right = DPI ±100; with Shift held elsewhere — RGB ±16 on R via `[`/`]`.
                let step = 100i32 * dir as i32;
                let v = self.profile.dpi[i] as i32 + step;
                self.profile.dpi[i] = Profile::clamp_dpi(v.clamp(0, u16::MAX as i32) as u16);
            }
            Focus::Apply => {
                if dir != 0 {
                    self.do_apply();
                }
            }
            Focus::Log => {}
        }
    }

    fn nudge_rgb(&mut self, channel: usize, dir: i8) {
        if let Focus::DpiSlot(i) = self.focus {
            let ch = channel.min(2);
            let v = self.profile.rgb[i][ch] as i16 + (16 * dir as i16);
            self.profile.rgb[i][ch] = v.clamp(0, 255) as u8;
        }
    }

    fn nudge_dpi(&mut self, delta: i32) {
        if let Focus::DpiSlot(i) = self.focus {
            let v = self.profile.dpi[i] as i32 + delta;
            self.profile.dpi[i] = Profile::clamp_dpi(v.clamp(0, u16::MAX as i32) as u16);
        }
    }

    fn activate(&mut self) {
        match self.focus {
            Focus::DpiSlot(i) => {
                self.editing = true;
                self.edit_buf = self.profile.dpi[i].to_string();
            }
            Focus::ActiveSlot => {
                self.profile.active_slot = if self.profile.active_slot >= NUM_DPI_SLOTS as u8 {
                    1
                } else {
                    self.profile.active_slot + 1
                };
            }
            Focus::PollRate => self.profile.poll = self.profile.poll.next(),
            Focus::ScrollFlag => {
                self.profile.scroll_flag = if self.profile.scroll_flag == 0 { 1 } else { 0 };
            }
            Focus::Liftoff => {
                self.profile.liftoff_height = (self.profile.liftoff_height + 1) % 3;
            }
            Focus::LightMode => {
                self.profile.light_mode = (self.profile.light_mode + 1) % 7;
            }
            Focus::SensorFlag => {
                self.profile.sensor_flag = sensor_flag_wire_nudge(self.profile.sensor_flag, 1);
            }
            Focus::EsportsFlag => {
                self.profile.e_sports_flag = (self.profile.e_sports_flag + 1) % 3;
            }
            Focus::Debounce => {
                self.profile.button_respondtime = (self.profile.button_respondtime + 1) % 21;
            }
            Focus::SleepLight => {
                self.profile.sleep_light = (self.profile.sleep_light + 1) % 61;
            }
            Focus::Apply => self.do_apply(),
            Focus::Log => {}
        }
    }

    fn commit_edit(&mut self) {
        if let Focus::DpiSlot(i) = self.focus {
            if let Ok(v) = self.edit_buf.parse::<u16>() {
                self.profile.dpi[i] = Profile::clamp_dpi(v);
                self.log(format!(
                    "Slot {} = {} DPI",
                    i + 1,
                    self.profile.dpi[i]
                ));
            } else {
                self.log(format!(
                    "{} '{}'. {}–{}.",
                    t(Msg::InvalidDpi, self.locale),
                    self.edit_buf,
                    DPI_MIN,
                    DPI_MAX
                ));
            }
        }
        self.editing = false;
        self.edit_buf.clear();
    }

    fn do_apply(&mut self) {
        if self.applying {
            return;
        }
        if self.connected.is_none() {
            self.status = t(Msg::DeviceNotFound, self.locale).into();
            self.log(t(Msg::ApplyIgnoredNoDevice, self.locale));
            return;
        }
        self.applying = true;
        self.status = t(Msg::Applying, self.locale).into();
        self.log(format!(
            "Apply: slot ativo={}, poll={}, dpi={:?}",
            self.profile.active_slot,
            self.profile.poll.label(),
            self.profile.dpi
        ));
        if let Err(err) = self.worker.apply(self.profile.clone()) {
            self.applying = false;
            self.status = err.to_string();
            self.log(err.to_string());
        }
    }

    fn do_refresh(&mut self) {
        if self.connected.is_none() {
            self.status = t(Msg::DeviceNotFound, self.locale).into();
            self.log(t(Msg::RefreshIgnoredNoDevice, self.locale));
            return;
        }
        self.status = t(Msg::Refreshing, self.locale).into();
        self.log("Open prelude + GET 0x0E — DPI / poll / slot.");
        if let Err(err) = self.worker.refresh() {
            self.status = err.to_string();
            self.log(err.to_string());
        }
    }

    fn draw(&self, frame: &mut Frame) {
        let area = frame.area();
        let root = Layout::default()
            .direction(Direction::Vertical)
            .constraints([
                Constraint::Length(3),
                Constraint::Length(7),
                Constraint::Min(12),
                Constraint::Length(3),
                Constraint::Length(9),
                Constraint::Length(1),
            ])
            .split(area);

        self.draw_header(frame, root[0]);
        self.draw_status(frame, root[1]);
        self.draw_controls(frame, root[2]);
        self.draw_apply(frame, root[3]);
        self.draw_log(frame, root[4]);
        self.draw_footer(frame, root[5]);

        if self.editing {
            self.draw_edit_popup(frame, area);
        }
    }

    fn draw_header(&self, frame: &mut Frame, area: Rect) {
        let title = Paragraph::new(Line::from(vec![
            Span::styled(
                BRAND,
                Style::default()
                    .fg(Color::Cyan)
                    .add_modifier(Modifier::BOLD),
            ),
            Span::raw(format!("  ·  {}", t(Msg::AppSubtitle, self.locale))),
        ]))
        .block(
            Block::default()
                .borders(Borders::ALL)
                .border_style(Style::default().fg(Color::DarkGray)),
        );
        frame.render_widget(title, area);
    }

    fn draw_status(&self, frame: &mut Frame, area: Rect) {
        let block = Block::default()
            .title(format!(" {} ", t(Msg::Status, self.locale)))
            .borders(Borders::ALL)
            .border_style(Style::default().fg(Color::DarkGray));
        let inner = block.inner(area);
        frame.render_widget(block, area);

        let rows = Layout::default()
            .direction(Direction::Vertical)
            .constraints([
                Constraint::Length(1),
                Constraint::Length(1),
                Constraint::Length(1),
                Constraint::Min(1),
            ])
            .split(inner);

        let mode = self
            .connected
            .as_ref()
            .map(|c| c.mode.label(self.locale))
            .unwrap_or("—");
        let serial = self.serial.as_deref().unwrap_or("—");
        let light = self
            .light_mode
            .map(|m| m.to_string())
            .unwrap_or_else(|| "—".into());
        let conn = if self.connected.is_some() {
            Span::styled(t(Msg::DeviceOnline, self.locale), Style::default().fg(Color::Green))
        } else {
            Span::styled(t(Msg::DeviceOffline, self.locale), Style::default().fg(Color::Red))
        };

        let wired = matches!(
            self.connected.as_ref().map(|c| c.mode),
            Some(ConnectionMode::Wired)
        );

        let meta = Paragraph::new(Line::from(vec![
            Span::raw(format!("{}: ", t(Msg::State, self.locale))),
            conn,
            Span::raw(format!("   {}: ", t(Msg::Mode, self.locale))),
            Span::styled(mode, Style::default().fg(Color::Yellow)),
            Span::raw("   ID: "),
            Span::raw(serial),
            Span::raw("   light_mode: "),
            Span::raw(light),
        ]));
        frame.render_widget(meta, rows[0]);

        // Battery gauge — FA 0xD0 on 2.4G; GET 0x30 (+ USB charging) on cable.
        let (ratio, label, color) = match &self.battery {
            Some(b) => {
                let charging = b.charging() || wired;
                let label = format!(
                    "{} {}% · {}",
                    t(Msg::Battery, self.locale),
                    b.percent,
                    if charging {
                        t(Msg::BatteryCharging, self.locale)
                    } else {
                        t(Msg::BatteryInUse, self.locale)
                    }
                );
                let color = if charging {
                    Color::Cyan
                } else if b.percent <= 15 {
                    Color::Red
                } else if b.percent <= 30 {
                    Color::Yellow
                } else {
                    Color::Green
                };
                (f64::from(b.percent) / 100.0, label, color)
            }
            None if wired => (0.0, t(Msg::BatteryWiredNa, self.locale).into(), Color::Cyan),
            None => (0.0, t(Msg::BatteryWaiting, self.locale).into(), Color::DarkGray),
        };
        let gauge = Gauge::default()
            .gauge_style(Style::default().fg(color).bg(Color::Black))
            .ratio(ratio.clamp(0.0, 1.0))
            .label(label);
        frame.render_widget(gauge, rows[1]);

        let status = Paragraph::new(Span::styled(
            self.status.as_str(),
            Style::default().fg(Color::Gray),
        ));
        frame.render_widget(status, rows[2]);
    }

    fn draw_controls(&self, frame: &mut Frame, area: Rect) {
        let cols = Layout::default()
            .direction(Direction::Horizontal)
            .constraints([Constraint::Percentage(55), Constraint::Percentage(45)])
            .split(area);

        self.draw_dpi(frame, cols[0]);
        self.draw_side(frame, cols[1]);
    }

    fn draw_dpi(&self, frame: &mut Frame, area: Rect) {
        let items: Vec<ListItem> = self
            .profile
            .dpi
            .iter()
            .enumerate()
            .map(|(i, &dpi)| {
                let focused = self.focus == Focus::DpiSlot(i);
                let active = self.profile.active_slot as usize == i + 1;
                let marker = if active { "▶" } else { " " };
                let rgb = self.profile.rgb[i];
                let label = if focused && self.editing {
                    format!(
                        "{marker} {} {}  {:>5} → [{}]  #{:02X}{:02X}{:02X}",
                        t(Msg::Level, self.locale),
                        i + 1,
                        dpi,
                        self.edit_buf,
                        rgb[0],
                        rgb[1],
                        rgb[2]
                    )
                } else {
                    format!(
                        "{marker} {} {}  {:>5} DPI  #{:02X}{:02X}{:02X}",
                        t(Msg::Level, self.locale),
                        i + 1,
                        dpi,
                        rgb[0],
                        rgb[1],
                        rgb[2]
                    )
                };
                let style = if focused {
                    Style::default()
                        .fg(Color::Black)
                        .bg(Color::Cyan)
                        .add_modifier(Modifier::BOLD)
                } else if active {
                    Style::default().fg(Color::Cyan)
                } else {
                    Style::default()
                };
                ListItem::new(Line::from(Span::styled(label, style)))
            })
            .collect();

        let list = List::new(items).block(
            Block::default()
                .title(format!(" {} ", t(Msg::DpiSlots, self.locale)))
                .borders(Borders::ALL)
                .border_style(focus_border(matches!(self.focus, Focus::DpiSlot(_)))),
        );
        frame.render_widget(list, area);
    }

    fn draw_side(&self, frame: &mut Frame, area: Rect) {
        let rows = Layout::default()
            .direction(Direction::Vertical)
            .constraints([
                Constraint::Length(5),
                Constraint::Length(5),
                Constraint::Min(3),
            ])
            .split(area);

        let active_focus = self.focus == Focus::ActiveSlot;
        let active = Paragraph::new(Line::from(vec![
            Span::raw(format!("{}: ", t(Msg::ActiveSlot, self.locale))),
            Span::styled(
                format!("{}", self.profile.active_slot),
                Style::default()
                    .fg(if active_focus {
                        Color::Black
                    } else {
                        Color::Yellow
                    })
                    .bg(if active_focus {
                        Color::Cyan
                    } else {
                        Color::Reset
                    })
                    .add_modifier(Modifier::BOLD),
            ),
            Span::raw(format!("  ({} DPI)", self.profile.active_dpi())),
            Span::raw("  "),
            {
                let rgb = self.profile.active_rgb();
                Span::styled(
                    format!("#{:02X}{:02X}{:02X}", rgb[0], rgb[1], rgb[2]),
                    Style::default().fg(Color::Magenta),
                )
            },
        ]))
        .block(
            Block::default()
                .title(format!(" {} ", t(Msg::Selection, self.locale)))
                .borders(Borders::ALL)
                .border_style(focus_border(active_focus)),
        );
        frame.render_widget(active, rows[0]);

        let poll_focus = self.focus == Focus::PollRate;
        let rates: Vec<Span> = PollRate::ALL
            .iter()
            .flat_map(|r| {
                let selected = *r == self.profile.poll;
                let style = if selected && poll_focus {
                    Style::default()
                        .fg(Color::Black)
                        .bg(Color::Cyan)
                        .add_modifier(Modifier::BOLD)
                } else if selected {
                    Style::default()
                        .fg(Color::Yellow)
                        .add_modifier(Modifier::BOLD)
                } else {
                    Style::default().fg(Color::DarkGray)
                };
                [
                    Span::styled(format!(" {} ", r.hz()), style),
                    Span::raw(" "),
                ]
            })
            .collect();
        let poll = Paragraph::new(Line::from(rates)).block(
            Block::default()
                .title(format!(" {} ", t(Msg::ReportRate, self.locale)))
                .borders(Borders::ALL)
                .border_style(focus_border(poll_focus)),
        );
        frame.render_widget(poll, rows[1]);

        let scroll_focus = self.focus == Focus::ScrollFlag;
        let lift_focus = self.focus == Focus::Liftoff;
        let light_focus = self.focus == Focus::LightMode;
        let sensor_focus = self.focus == Focus::SensorFlag;
        let esports_focus = self.focus == Focus::EsportsFlag;
        let debounce_focus = self.focus == Focus::Debounce;
        let sleep_focus = self.focus == Focus::SleepLight;
        let scroll_txt = scroll_label(self.profile.scroll_flag, self.locale);
        let esports_owned = esports_label(self.profile.e_sports_flag, self.locale);
        let lift_owned = lod_label(self.profile.liftoff_height, self.locale);
        let sf = self.profile.sensor_flag;
        let on = |bit: u8| if sf & bit != 0 { "on" } else { "off" };
        let misc = Paragraph::new(vec![
            Line::from(vec![
                Span::raw(format!("{}: ", t(Msg::Scroll, self.locale))),
                Span::styled(
                    scroll_txt,
                    Style::default()
                        .fg(if scroll_focus { Color::Black } else { Color::Yellow })
                        .bg(if scroll_focus { Color::Cyan } else { Color::Reset }),
                ),
            ]),
            Line::from(vec![
                Span::raw(format!("{}: ", t(Msg::Lod, self.locale))),
                Span::styled(
                    lift_owned.as_str(),
                    Style::default()
                        .fg(if lift_focus { Color::Black } else { Color::Yellow })
                        .bg(if lift_focus { Color::Cyan } else { Color::Reset }),
                ),
            ]),
            Line::from(vec![
                Span::raw(format!("{}: ", t(Msg::LightMode, self.locale))),
                Span::styled(
                    format!("{}", self.profile.light_mode),
                    Style::default()
                        .fg(if light_focus { Color::Black } else { Color::Yellow })
                        .bg(if light_focus { Color::Cyan } else { Color::Reset }),
                ),
            ]),
            Line::from(vec![
                Span::raw(format!("{}: ", t(Msg::Sensor, self.locale))),
                Span::styled(
                    format!(
                        "A={} R={} M={}  (0x{sf:02X})",
                        on(SENSOR_WIRE_ANGLE_SNAP),
                        on(SENSOR_WIRE_RIPPLE),
                        on(SENSOR_WIRE_MOTION_SYNC),
                    ),
                    Style::default()
                        .fg(if sensor_focus {
                            Color::Black
                        } else {
                            Color::Yellow
                        })
                        .bg(if sensor_focus {
                            Color::Cyan
                        } else {
                            Color::Reset
                        }),
                ),
            ]),
            Line::from(vec![
                Span::raw(format!("{}: ", t(Msg::Esports, self.locale))),
                Span::styled(
                    esports_owned.as_str(),
                    Style::default()
                        .fg(if esports_focus {
                            Color::Black
                        } else {
                            Color::Yellow
                        })
                        .bg(if esports_focus {
                            Color::Cyan
                        } else {
                            Color::Reset
                        }),
                ),
            ]),
            Line::from(vec![
                Span::raw(format!("{}: ", t(Msg::Debounce, self.locale))),
                Span::styled(
                    format!("{}", self.profile.button_respondtime),
                    Style::default()
                        .fg(if debounce_focus {
                            Color::Black
                        } else {
                            Color::Yellow
                        })
                        .bg(if debounce_focus {
                            Color::Cyan
                        } else {
                            Color::Reset
                        }),
                ),
                Span::raw(format!("  {}: ", t(Msg::Sleep, self.locale))),
                Span::styled(
                    format!("{}", self.profile.sleep_light),
                    Style::default()
                        .fg(if sleep_focus {
                            Color::Black
                        } else {
                            Color::Yellow
                        })
                        .bg(if sleep_focus {
                            Color::Cyan
                        } else {
                            Color::Reset
                        }),
                ),
            ]),
            Line::from(Span::styled(
                format!(
                    "btn5={}  ({})",
                    self.profile.buttons[5].label_short(),
                    t(Msg::CycleBtn5, self.locale)
                ),
                Style::default().fg(Color::DarkGray),
            )),
        ])
        .block(
            Block::default()
                .title(format!(" {} ", t(Msg::MiscPanel, self.locale)))
                .borders(Borders::ALL)
                .border_style(focus_border(
                    scroll_focus
                        || lift_focus
                        || light_focus
                        || sensor_focus
                        || esports_focus
                        || debounce_focus
                        || sleep_focus,
                )),
        );
        frame.render_widget(misc, rows[2]);
    }

    fn draw_apply(&self, frame: &mut Frame, area: Rect) {
        let focused = self.focus == Focus::Apply;
        let label = if self.applying {
            format!("  {}  ", t(Msg::Applying, self.locale))
        } else {
            format!("  [ Ctrl+S / Enter ] {}  ", t(Msg::ApplyHint, self.locale))
        };
        let style = if focused {
            Style::default()
                .fg(Color::Black)
                .bg(Color::Green)
                .add_modifier(Modifier::BOLD)
        } else {
            Style::default().fg(Color::Green)
        };
        let widget = Paragraph::new(Line::from(Span::styled(label, style)))
            .alignment(ratatui::layout::Alignment::Center)
            .block(
                Block::default()
                    .borders(Borders::ALL)
                    .border_style(focus_border(focused)),
            );
        frame.render_widget(widget, area);
    }

    fn draw_log(&self, frame: &mut Frame, area: Rect) {
        let focused = self.focus == Focus::Log;
        let items: Vec<ListItem> = self
            .logs
            .iter()
            .rev()
            .take(area.height.saturating_sub(2) as usize)
            .map(|l| ListItem::new(l.as_str()))
            .collect::<Vec<_>>()
            .into_iter()
            .rev()
            .collect();
        let list = List::new(items).block(
            Block::default()
                .title(format!(" {} ", t(Msg::Log, self.locale)))
                .borders(Borders::ALL)
                .border_style(focus_border(focused)),
        );
        frame.render_widget(list, area);
    }

    fn draw_footer(&self, frame: &mut Frame, area: Rect) {
        let help = Paragraph::new(t(Msg::HelpTui, self.locale))
            .style(Style::default().fg(Color::DarkGray));
        frame.render_widget(help, area);
    }

    fn draw_edit_popup(&self, frame: &mut Frame, area: Rect) {
        let slot = match self.focus {
            Focus::DpiSlot(i) => i + 1,
            _ => 0,
        };
        let popup = centered_rect(40, 5, area);
        let text = Paragraph::new(vec![
            Line::from(format!("{} {slot} DPI", t(Msg::EditDpiTitle, self.locale))),
            Line::from(format!("> {}_", self.edit_buf)),
            Line::from(format!(
                "{DPI_MIN}–{DPI_MAX}  {}",
                t(Msg::EditDpiRange, self.locale)
            )),
        ])
        .block(
            Block::default()
                .title(format!(" {} ", t(Msg::EditTitle, self.locale)))
                .borders(Borders::ALL)
                .border_style(Style::default().fg(Color::Cyan)),
        )
        .wrap(Wrap { trim: true });
        frame.render_widget(Clear, popup);
        frame.render_widget(text, popup);
    }
}

fn focus_border(focused: bool) -> Style {
    if focused {
        Style::default().fg(Color::Cyan)
    } else {
        Style::default().fg(Color::DarkGray)
    }
}

fn centered_rect(percent_x: u16, height: u16, area: Rect) -> Rect {
    let popup_layout = Layout::default()
        .direction(Direction::Vertical)
        .constraints([
            Constraint::Fill(1),
            Constraint::Length(height),
            Constraint::Fill(1),
        ])
        .split(area);
    Layout::default()
        .direction(Direction::Horizontal)
        .constraints([
            Constraint::Percentage((100 - percent_x) / 2),
            Constraint::Percentage(percent_x),
            Constraint::Percentage((100 - percent_x) / 2),
        ])
        .split(popup_layout[1])[1]
}

fn chrono_lite() -> String {
    use std::time::{SystemTime, UNIX_EPOCH};
    let secs = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .map(|d| d.as_secs() % 86_400)
        .unwrap_or(0);
    let h = secs / 3600;
    let m = (secs % 3600) / 60;
    let s = secs % 60;
    format!("{h:02}:{m:02}:{s:02}")
}
