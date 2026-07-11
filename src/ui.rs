//! Terminal UI for Smailwolf RS7 (Portuguese labels).

use crate::device::{DeviceInfo, DeviceToHost, DeviceWorker};
use crate::protocol::{BatteryInfo, DeviceEvent, PollRate, Profile, DPI_MAX, DPI_MIN, NUM_DPI_SLOTS};
use crossterm::event::{self, Event, KeyCode, KeyEvent, KeyEventKind, KeyModifiers};
use ratatui::layout::{Constraint, Direction, Layout, Rect};
use ratatui::style::{Color, Modifier, Style};
use ratatui::text::{Line, Span};
use ratatui::widgets::{Block, Borders, Clear, List, ListItem, Paragraph, Wrap};
use ratatui::{DefaultTerminal, Frame};
use std::time::{Duration, Instant};

const MAX_LOG: usize = 80;
const BRAND: &str = "Smailwolf RS7";

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Focus {
    DpiSlot(usize),
    ActiveSlot,
    PollRate,
    Apply,
    Log,
}

impl Focus {
    fn next(self) -> Self {
        match self {
            Self::DpiSlot(i) if i + 1 < NUM_DPI_SLOTS => Self::DpiSlot(i + 1),
            Self::DpiSlot(_) => Self::ActiveSlot,
            Self::ActiveSlot => Self::PollRate,
            Self::PollRate => Self::Apply,
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
            Self::Apply => Self::PollRate,
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
    serial: Option<String>,
    logs: Vec<String>,
    status: String,
    applying: bool,
    should_quit: bool,
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
            serial: None,
            logs: Vec::new(),
            status: "Procurando dispositivo…".into(),
            applying: false,
            should_quit: false,
            worker: DeviceWorker::spawn(),
        };
        app.log("TUI iniciada. Tab/↑↓ navegar · Enter editar · Ctrl+S salvar · r reler · q sair.");
        app.log("Aviso: envie apenas a sequência Apply — não dispare pacotes aleatórios.");
        app
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
                    self.status = format!(
                        "Conectado — {} ({})",
                        info.mode.label_pt(),
                        info.product
                    );
                    self.log(format!(
                        "Dispositivo aberto: {} / {}",
                        info.mode.label_pt(),
                        info.path
                    ));
                    self.connected = Some(info);
                }
                Ok(DeviceToHost::Profile(profile)) => {
                    self.profile = profile;
                    self.log(format!(
                        "Perfil lido do mouse: slot {} · {} · DPI {:?}",
                        self.profile.active_slot,
                        self.profile.poll.label(),
                        self.profile.dpi
                    ));
                    self.status = format!(
                        "Configuração carregada — slot {} @ {}.",
                        self.profile.active_slot,
                        self.profile.poll.label()
                    );
                }
                Ok(DeviceToHost::Event(ev)) => self.on_device_event(ev),
                Ok(DeviceToHost::ApplyOk) => {
                    self.applying = false;
                    self.status = "Perfil aplicado com sucesso.".into();
                    self.log("Apply OK — sequência 0x0D/0x10/0x09/0x0F/0x22/0x23 enviada.");
                }
                Ok(DeviceToHost::ApplyErr(err)) => {
                    self.applying = false;
                    self.status = format!("Falha no Apply: {err}");
                    self.log(format!("Erro Apply: {err}"));
                }
                Ok(DeviceToHost::Status(msg)) => {
                    self.status = msg.clone();
                    self.log(msg);
                }
                Ok(DeviceToHost::Fatal(msg)) => {
                    self.status = format!("Erro fatal: {msg}");
                    self.log(format!("Fatal: {msg}"));
                }
                Err(std::sync::mpsc::TryRecvError::Empty) => break,
                Err(std::sync::mpsc::TryRecvError::Disconnected) => {
                    self.log("Worker HID desconectado.");
                    break;
                }
            }
        }
    }

    fn on_device_event(&mut self, ev: DeviceEvent) {
        match ev {
            DeviceEvent::Battery(b) => {
                let charge = if b.charging() {
                    "carregando?"
                } else {
                    "em uso"
                };
                self.log(format!("Bateria: {}% ({})", b.percent, charge));
                self.battery = Some(b);
            }
            DeviceEvent::ActiveStage(stage) => {
                let prev = self.profile.active_slot;
                self.profile.active_slot = stage.active_slot;
                if let Some(poll) = PollRate::from_poll_code(stage.poll_code) {
                    self.profile.poll = poll;
                }
                if prev != stage.active_slot {
                    self.log(format!(
                        "Slot ativo (hardware): {} → {} (poll_code={})",
                        prev, stage.active_slot, stage.poll_code
                    ));
                    self.status = format!(
                        "Slot DPI {} selecionado no mouse.",
                        stage.active_slot
                    );
                }
            }
            DeviceEvent::Serial(s) => {
                if !s.is_empty() {
                    self.log(format!("Serial/ID: {s}"));
                    self.serial = Some(s);
                }
            }
            DeviceEvent::Link => self.log("Link/status (0xED) recebido."),
            DeviceEvent::Echo { cmd } => {
                // Keep log quiet for apply echoes unless debugging.
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
            KeyCode::Char('[') => self.nudge_dpi(-50),
            KeyCode::Char(']') => self.nudge_dpi(50),
            _ => {}
        }
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
            Focus::DpiSlot(i) => {
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
                    "Valor inválido '{}'. Use {}–{}.",
                    self.edit_buf, DPI_MIN, DPI_MAX
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
            self.status = "dispositivo não encontrado".into();
            self.log("Apply ignorado: nenhum dispositivo na interface MI_02.");
            return;
        }
        self.applying = true;
        self.status = "Enviando sequência Apply…".into();
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
            self.status = "dispositivo não encontrado".into();
            self.log("Refresh ignorado: nenhum dispositivo na interface MI_02.");
            return;
        }
        self.status = "Lendo perfil do mouse…".into();
        self.log("GET 0x0E — relendo DPI / poll / slot ativo.");
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
                Constraint::Length(5),
                Constraint::Min(12),
                Constraint::Length(3),
                Constraint::Length(10),
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
            Span::raw("  ·  configurador HID (YJX)"),
        ]))
        .block(
            Block::default()
                .borders(Borders::ALL)
                .border_style(Style::default().fg(Color::DarkGray)),
        );
        frame.render_widget(title, area);
    }

    fn draw_status(&self, frame: &mut Frame, area: Rect) {
        let mode = self
            .connected
            .as_ref()
            .map(|c| c.mode.label_pt())
            .unwrap_or("—");
        let batt = match &self.battery {
            Some(b) => {
                let flag = if b.charging() { " ⚡" } else { "" };
                format!("{}%{flag}", b.percent)
            }
            None => "—".into(),
        };
        let serial = self.serial.as_deref().unwrap_or("—");
        let conn = if self.connected.is_some() {
            Span::styled("ONLINE", Style::default().fg(Color::Green))
        } else {
            Span::styled("OFFLINE", Style::default().fg(Color::Red))
        };

        let text = vec![
            Line::from(vec![
                Span::raw("Estado: "),
                conn,
                Span::raw("   Modo: "),
                Span::styled(mode, Style::default().fg(Color::Yellow)),
                Span::raw("   Bateria: "),
                Span::styled(batt, Style::default().fg(Color::Green)),
            ]),
            Line::from(format!("ID: {serial}")),
            Line::from(Span::styled(
                &self.status,
                Style::default().fg(Color::Gray),
            )),
        ];
        let widget = Paragraph::new(text).block(
            Block::default()
                .title(" Dispositivo ")
                .borders(Borders::ALL)
                .border_style(Style::default().fg(Color::DarkGray)),
        );
        frame.render_widget(widget, area);
    }

    fn draw_controls(&self, frame: &mut Frame, area: Rect) {
        let cols = Layout::default()
            .direction(Direction::Horizontal)
            .constraints([
                Constraint::Percentage(55),
                Constraint::Percentage(45),
            ])
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
                let label = format!("{marker} Nível {}  {:>5} DPI", i + 1, dpi);
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
                .title(" Slots DPI (200–24000) ")
                .borders(Borders::ALL)
                .border_style(focus_border(matches!(self.focus, Focus::DpiSlot(_)))),
        );
        frame.render_widget(list, area);
    }

    fn draw_side(&self, frame: &mut Frame, area: Rect) {
        let rows = Layout::default()
            .direction(Direction::Vertical)
            .constraints([Constraint::Length(5), Constraint::Min(3)])
            .split(area);

        let active_focus = self.focus == Focus::ActiveSlot;
        let active = Paragraph::new(Line::from(vec![
            Span::raw("Slot ativo: "),
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
        ]))
        .block(
            Block::default()
                .title(" Seleção ")
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
                .title(" Report rate (Hz) ")
                .borders(Borders::ALL)
                .border_style(focus_border(poll_focus)),
        );
        frame.render_widget(poll, rows[1]);
    }

    fn draw_apply(&self, frame: &mut Frame, area: Rect) {
        let focused = self.focus == Focus::Apply;
        let label = if self.applying {
            "  Aplicando…  "
        } else {
            "  [ Ctrl+S / Enter ] Aplicar perfil no mouse  "
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
                .title(" Log ")
                .borders(Borders::ALL)
                .border_style(focus_border(focused)),
        );
        frame.render_widget(list, area);
    }

    fn draw_footer(&self, frame: &mut Frame, area: Rect) {
        let help = Paragraph::new(
            "Tab/↑↓ navegar  ·  ←→ ajustar  ·  Enter editar  ·  Ctrl+S salvar  ·  r reler  ·  +/- DPI  ·  q sair",
        )
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
            Line::from(format!("Editar Nível {slot} DPI")),
            Line::from(format!("> {}_", self.edit_buf)),
            Line::from(format!("Faixa {DPI_MIN}–{DPI_MAX}  (Enter confirma, Esc cancela)")),
        ])
        .block(
            Block::default()
                .title(" Edição ")
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
