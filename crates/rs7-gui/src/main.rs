//! Smailwolf RS7 — GPUI desktop configurator (pt_BR / en_US).

use std::time::Duration;

use gpui_kit::component::button::*;
use gpui_kit::component::color_picker::{ColorPickerEvent, ColorPickerState, ColorSelect};
use gpui_kit::component::progress::Progress;
use gpui_kit::component::radio::Radio;
use gpui_kit::component::*;
use gpui_kit::prelude::FluentBuilder as _;
use gpui_kit::*;
use rs7_core::actions::{cycle_button5, merge_profile_rgb, set_active_slot, set_dpi};
use rs7_core::device::{DeviceInfo, DeviceToHost, DeviceWorker};
use rs7_core::i18n::{esports_label, lod_label, scroll_label, t, Locale, Msg};
use rs7_core::protocol::{
    sensor_flag_wire_nudge, BatteryInfo, BatteryTracker, ConnectionMode, DeviceEvent, PollRate,
    Profile, DEFAULT_BUTTONS, DEFAULT_RGB, DPI_MAX, DPI_MIN, NUM_DPI_SLOTS, SENSOR_WIRE_ANGLE_SNAP,
    SENSOR_WIRE_MOTION_SYNC, SENSOR_WIRE_RIPPLE,
};
use smol::Timer;

actions!(rs7_gui, [Quit, SaveProfile, RefreshDevice, OpenLogs]);

const POLL_INTERVAL: Duration = Duration::from_millis(50);
const ACCENT_CHARGE: Hsla = hsla(152. / 360., 0.72, 0.48, 1.);
const ACCENT_LOW: Hsla = hsla(28. / 360., 0.92, 0.55, 1.);
const ACCENT_ACTIVE: Hsla = hsla(168. / 360., 0.78, 0.46, 1.);

struct Rs7App {
    profile: Profile,
    connected: Option<DeviceInfo>,
    battery: Option<BatteryInfo>,
    battery_tracker: BatteryTracker,
    light_mode: Option<u8>,
    serial: Option<String>,
    status: String,
    applying: bool,
    locale: Locale,
    logs: Vec<String>,
    worker: DeviceWorker,
    color_pickers: Vec<Entity<ColorPickerState>>,
    colors_dirty: bool,
    focus_handle: FocusHandle,
}

impl Rs7App {
    fn new(window: &mut Window, cx: &mut Context<Self>) -> Self {
        let locale = Locale::PtBr;
        let profile = Profile::default();
        let mut color_pickers = Vec::with_capacity(NUM_DPI_SLOTS);
        for slot in 0..NUM_DPI_SLOTS {
            let initial = rgb_to_hsla(profile.rgb[slot]);
            let state =
                cx.new(|cx| ColorPickerState::new(window, cx).default_value(initial));
            cx.observe(&state, |_, _, cx| cx.notify()).detach();
            cx.subscribe(&state, move |this, _picker, event: &ColorPickerEvent, cx| {
                if let ColorPickerEvent::Change(Some(color)) = event {
                    this.profile.rgb[slot] = hsla_to_rgb(*color);
                    cx.notify();
                }
            })
            .detach();
            color_pickers.push(state);
        }

        let focus_handle = cx.focus_handle();
        focus_handle.focus(window, cx);

        let mut app = Self {
            profile,
            connected: None,
            battery: None,
            battery_tracker: BatteryTracker::default(),
            light_mode: None,
            serial: None,
            status: t(Msg::SearchingDevice, locale).into(),
            applying: false,
            locale,
            logs: Vec::new(),
            worker: DeviceWorker::spawn(),
            color_pickers,
            colors_dirty: true,
            focus_handle,
        };
        app.push_log(t(Msg::HelpRgb, locale));
        app.push_log(t(Msg::HelpBtn5, locale));
        app.push_log(t(Msg::HelpSensor, locale));
        app.push_log(t(Msg::HelpLang, locale));
        app.push_log(t(Msg::TipSaveShortcut, locale));

        cx.spawn(async move |this, cx| {
            loop {
                Timer::after(POLL_INTERVAL).await;
                let ok = this.update(cx, |this, cx| {
                    this.drain_device();
                    cx.notify();
                });
                if ok.is_err() {
                    break;
                }
            }
        })
        .detach();

        app
    }

    fn push_log(&mut self, msg: impl Into<String>) {
        self.logs.push(msg.into());
        if self.logs.len() > 200 {
            let skip = self.logs.len() - 200;
            self.logs.drain(0..skip);
        }
    }

    fn toggle_locale(&mut self, cx: &mut Context<Self>) {
        self.locale = self.locale.toggle();
        self.status = t(Msg::LanguageSwitched, self.locale).into();
        self.push_log(format!(
            "{} → {}",
            t(Msg::Language, self.locale),
            self.locale.label()
        ));
        cx.notify();
    }

    fn sync_color_pickers(&mut self, window: &mut Window, cx: &mut Context<Self>) {
        for slot in 0..NUM_DPI_SLOTS {
            let color = rgb_to_hsla(self.profile.rgb[slot]);
            self.color_pickers[slot].update(cx, |state, cx| {
                state.set_value(color, window, cx);
                state.sync_pending_value(window, cx);
            });
        }
        self.colors_dirty = false;
    }

    fn drain_device(&mut self) {
        loop {
            match self.worker.try_recv() {
                Ok(DeviceToHost::Opened(info)) => {
                    // Keep last FA battery across cable↔dongle — GET 0x30 on
                    // cable often reports a fake 100% that must not wipe SOC.
                    let mode = info.mode.label(self.locale);
                    self.status = format!("{mode} — {}", info.product);
                    self.push_log(format!("{mode} / {}", info.path));
                    self.connected = Some(info);
                }
                Ok(DeviceToHost::Disconnected) => {
                    self.connected = None;
                    self.battery = None;
                    self.battery_tracker = BatteryTracker::default();
                    self.status = t(Msg::SearchingDevice, self.locale).into();
                    self.push_log(t(Msg::Disconnected, self.locale));
                }
                Ok(DeviceToHost::Profile(mut profile)) => {
                    merge_profile_rgb(&self.profile, &mut profile);
                    if profile.rgb == DEFAULT_RGB && self.profile.rgb != DEFAULT_RGB {
                        profile.rgb = self.profile.rgb;
                    }
                    profile.buttons = self.profile.buttons;
                    self.profile = profile;
                    self.colors_dirty = true;
                    self.status = format!(
                        "{} — slot {} @ {}.",
                        t(Msg::ConfigLoaded, self.locale),
                        self.profile.active_slot,
                        self.profile.poll.label()
                    );
                    self.push_log(format!(
                        "slot {} · {} · DPI {:?}",
                        self.profile.active_slot,
                        self.profile.poll.label(),
                        self.profile.dpi
                    ));
                }
                Ok(DeviceToHost::Event(ev)) => self.on_device_event(ev),
                Ok(DeviceToHost::ApplyOk) => {
                    self.applying = false;
                    self.status = t(Msg::ApplyOk, self.locale).into();
                    self.push_log("Apply OK");
                }
                Ok(DeviceToHost::ApplyErr(err)) => {
                    self.applying = false;
                    self.status = format!("{}: {err}", t(Msg::ApplyFailed, self.locale));
                    self.push_log(self.status.clone());
                }
                Ok(DeviceToHost::Status(msg)) => {
                    self.status = msg.clone();
                    self.push_log(msg);
                }
                Ok(DeviceToHost::Fatal(msg)) => {
                    self.status = format!("{}: {msg}", t(Msg::FatalError, self.locale));
                    self.push_log(self.status.clone());
                }
                Err(std::sync::mpsc::TryRecvError::Empty) => break,
                Err(std::sync::mpsc::TryRecvError::Disconnected) => {
                    self.push_log(t(Msg::WorkerDisconnected, self.locale));
                    break;
                }
            }
        }
    }

    fn on_device_event(&mut self, ev: DeviceEvent) {
        match ev {
            DeviceEvent::Battery { info, source } => {
                if let Some(b) = self.battery_tracker.observe(info, source) {
                    self.battery = Some(b);
                    let charge = if b.charging() {
                        t(Msg::BatteryCharging, self.locale)
                    } else {
                        t(Msg::BatteryInUse, self.locale)
                    };
                    self.push_log(format!(
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
            }
            DeviceEvent::Serial(s) if !s.is_empty() => {
                self.serial = Some(s.clone());
                self.push_log(format!("ID: {s}"));
            }
            DeviceEvent::Buttons {
                profile_index,
                bindings,
            } => {
                if profile_index == 0 {
                    self.profile.buttons = bindings;
                }
                if profile_index == 0 || bindings != DEFAULT_BUTTONS {
                    let summary: String = bindings
                        .iter()
                        .map(|b| b.label_short())
                        .collect::<Vec<_>>()
                        .join(", ");
                    self.push_log(format!(
                        "{} p{profile_index}: {summary}",
                        t(Msg::ButtonsProfile, self.locale)
                    ));
                }
            }
            DeviceEvent::Notify { .. }
            | DeviceEvent::Link
            | DeviceEvent::Echo { .. }
            | DeviceEvent::Unknown { .. }
            | DeviceEvent::Serial(_) => {}
        }
    }

    fn do_apply(&mut self, cx: &mut Context<Self>) {
        if self.applying {
            return;
        }
        if self.connected.is_none() {
            self.status = t(Msg::DeviceNotFound, self.locale).into();
            self.push_log(t(Msg::ApplyIgnoredNoDevice, self.locale));
            cx.notify();
            return;
        }
        self.applying = true;
        self.status = t(Msg::Applying, self.locale).into();
        if let Err(err) = self.worker.apply(self.profile.clone()) {
            self.applying = false;
            self.status = err.message(self.locale);
            self.push_log(self.status.clone());
        }
        cx.notify();
    }

    fn do_refresh(&mut self, cx: &mut Context<Self>) {
        if self.connected.is_none() {
            self.status = t(Msg::DeviceNotFound, self.locale).into();
            self.push_log(t(Msg::RefreshIgnoredNoDevice, self.locale));
            cx.notify();
            return;
        }
        self.status = t(Msg::Refreshing, self.locale).into();
        if let Err(err) = self.worker.refresh() {
            self.status = err.message(self.locale);
            self.push_log(self.status.clone());
        }
        cx.notify();
    }

    fn open_logs(&mut self, window: &mut Window, cx: &mut Context<Self>) {
        let entity = cx.entity();
        let locale = self.locale;
        window.open_sheet(cx, move |sheet, _, cx| {
            let app = entity.read(cx);
            let mut list = v_flex().gap_2().w_full().pb_4();
            if app.logs.is_empty() {
                list = list.child(
                    div()
                        .text_sm()
                        .text_color(cx.theme().muted_foreground)
                        .child("—"),
                );
            } else {
                for (i, line) in app.logs.iter().rev().enumerate() {
                    list = list.child(
                        div()
                            .id(("log-line", i))
                            .px_3()
                            .py_2()
                            .rounded_md()
                            .bg(cx.theme().muted.opacity(0.45))
                            .text_sm()
                            .font_family("ui-monospace")
                            .text_color(cx.theme().foreground)
                            .child(line.clone()),
                    );
                }
            }
            sheet
                .title(t(Msg::Log, locale))
                .size(px(460.))
                .overlay(true)
                .overlay_closable(true)
                .child(
                    div()
                        .id("logs-scroll")
                        .w_full()
                        .h_full()
                        .px_2()
                        .overflow_y_scroll()
                        .child(list),
                )
        });
    }

    fn section_label(&self, label: &str, cx: &Context<Self>) -> impl IntoElement {
        div()
            .text_xs()
            .font_semibold()
            .text_color(cx.theme().muted_foreground)
            .child(label.to_uppercase())
    }

    fn title_bar(&self, cx: &mut Context<Self>) -> impl IntoElement {
        let locale = self.locale;
        TitleBar::new()
            .child(
                h_flex()
                    .w_full()
                    .items_center()
                    .justify_between()
                    .px_3()
                    .gap_3()
                    .child(
                        h_flex()
                            .items_baseline()
                            .gap_2()
                            .child(
                                div()
                                    .text_sm()
                                    .font_semibold()
                                    .child(t(Msg::AppTitle, locale)),
                            )
                            .child(
                                div()
                                    .text_xs()
                                    .text_color(cx.theme().muted_foreground)
                                    .child(t(Msg::AppSubtitle, locale)),
                            ),
                    )
                    .child(
                        h_flex()
                            .gap_2()
                            .items_center()
                            .child(
                                Button::new("lang")
                                    .ghost()
                                    .small()
                                    .label(locale.label())
                                    .tooltip(t(Msg::TipLanguage, locale))
                                    .on_click(cx.listener(|this, _, _, cx| this.toggle_locale(cx))),
                            )
                            .child(
                                Button::new("logs")
                                    .outline()
                                    .small()
                                    .label(t(Msg::ViewLogs, locale))
                                    .tooltip(t(Msg::TipViewLogs, locale))
                                    .on_click(cx.listener(|this, _, window, cx| {
                                        this.open_logs(window, cx)
                                    })),
                            )
                            .child(
                                Button::new("refresh")
                                    .outline()
                                    .small()
                                    .label(t(Msg::Refresh, locale))
                                    .tooltip(t(Msg::TipRefresh, locale))
                                    .on_click(
                                        cx.listener(|this, _, _, cx| this.do_refresh(cx)),
                                    ),
                            )
                            .child(
                                Button::new("save")
                                    .primary()
                                    .small()
                                    .label(if self.applying {
                                        t(Msg::Applying, locale)
                                    } else {
                                        t(Msg::Save, locale)
                                    })
                                    .tooltip(format!(
                                        "{}\n{}",
                                        t(Msg::TipApply, locale),
                                        t(Msg::TipSaveShortcut, locale)
                                    ))
                                    .disabled(self.applying)
                                    .on_click(cx.listener(|this, _, _, cx| this.do_apply(cx))),
                            ),
                    ),
            )
    }

    fn connection_hero(&self, cx: &Context<Self>) -> impl IntoElement {
        let locale = self.locale;
        let online = self.connected.is_some();
        let wired = matches!(
            self.connected.as_ref().map(|c| c.mode),
            Some(ConnectionMode::Wired)
        );
        let mode = self
            .connected
            .as_ref()
            .map(|c| c.mode.label(locale))
            .unwrap_or("—");
        let serial = self.serial.as_deref().unwrap_or("—");
        let light = self
            .light_mode
            .map(|m| m.to_string())
            .unwrap_or_else(|| "—".into());

        let (bat_label, bat_value, bat_color, bat_loading) = match &self.battery {
            Some(b) => {
                // USB power ⇒ charging even when FLAGS is still 0 on some firmware.
                let charging = b.charging() || wired;
                let state = if charging {
                    t(Msg::BatteryCharging, locale)
                } else {
                    t(Msg::BatteryInUse, locale)
                };
                let color = if charging {
                    ACCENT_CHARGE
                } else if b.percent <= 20 {
                    ACCENT_LOW
                } else {
                    ACCENT_ACTIVE
                };
                (
                    format!("{} · {state}", t(Msg::Battery, locale)),
                    f32::from(b.percent),
                    Some(color),
                    false,
                )
            }
            None if wired => (
                t(Msg::BatteryWiredNa, locale).into(),
                0.0_f32,
                Some(ACCENT_CHARGE),
                true,
            ),
            None if online => (
                t(Msg::BatteryWaiting, locale).into(),
                0.0_f32,
                None,
                true,
            ),
            None => (
                t(Msg::OfflineHint, locale).into(),
                0.0_f32,
                None,
                false,
            ),
        };

        let mut progress = Progress::new("battery-bar")
            .w_full()
            .large()
            .value(bat_value)
            .loading(bat_loading)
            .accessibility_label(t(Msg::TipBattery, locale));
        if let Some(color) = bat_color {
            progress = progress.color(color);
        }

        v_flex()
            .w_full()
            .gap_3()
            .p_5()
            .rounded_xl()
            .bg(cx.theme().secondary)
            .border_1()
            .border_color(cx.theme().border.opacity(0.7))
            .child(
                h_flex()
                    .w_full()
                    .items_start()
                    .justify_between()
                    .gap_4()
                    .child(
                        v_flex()
                            .gap_1()
                            .child(self.section_label(t(Msg::SectionConnection, locale), cx))
                            .child(
                                h_flex()
                                    .items_center()
                                    .gap_2()
                                    .child(
                                        div()
                                            .size_2()
                                            .rounded_full()
                                            .bg(if online {
                                                ACCENT_CHARGE
                                            } else {
                                                cx.theme().muted_foreground
                                            }),
                                    )
                                    .child(
                                        div().text_lg().font_semibold().child(if online {
                                            t(Msg::DeviceOnline, locale)
                                        } else {
                                            t(Msg::DeviceOffline, locale)
                                        }),
                                    )
                                    .child(
                                        div()
                                            .text_sm()
                                            .text_color(cx.theme().muted_foreground)
                                            .child(format!("· {mode}")),
                                    ),
                            )
                            .child(
                                div()
                                    .text_sm()
                                    .text_color(cx.theme().muted_foreground)
                                    .child(format!("ID {serial} · {} {light}", t(Msg::LightMode, locale))),
                            ),
                    )
                    .child(
                        v_flex()
                            .items_end()
                            .gap_1()
                            .min_w(px(180.))
                            .max_w(px(280.))
                            .w(relative(0.38))
                            .child(
                                h_flex()
                                    .w_full()
                                    .items_center()
                                    .justify_between()
                                    .gap_2()
                                    .child(
                                        div()
                                            .text_xs()
                                            .text_color(cx.theme().muted_foreground)
                                            .child(bat_label),
                                    )
                                    .child(
                                        div().text_sm().font_semibold().child(
                                            if let Some(b) = &self.battery {
                                                format!("{}%", b.percent)
                                            } else if wired {
                                                "USB".into()
                                            } else if bat_loading {
                                                "…".into()
                                            } else {
                                                "—".into()
                                            },
                                        ),
                                    ),
                            )
                            .child(progress),
                    ),
            )
            .child(
                div()
                    .text_sm()
                    .text_color(cx.theme().foreground.opacity(0.85))
                    .child(self.status.clone()),
            )
    }

    fn dpi_section(&self, window: &mut Window, cx: &mut Context<Self>) -> impl IntoElement {
        let locale = self.locale;
        let mut grid = h_flex().w_full().gap_3().flex_wrap().items_stretch();

        for i in 0..NUM_DPI_SLOTS {
            let dpi = self.profile.dpi[i];
            let active = self.profile.active_slot as usize == i + 1;
            let slot = i;
            let swatch = rgb_to_hsla(self.profile.rgb[i]);
            self.color_pickers[i].update(cx, |state, cx| state.sync_pending_value(window, cx));

            grid = grid.child(
                v_flex()
                    .id(("dpi-card", i))
                    .flex_1()
                    .min_w(px(220.))
                    .gap_3()
                    .p_4()
                    .rounded_xl()
                    .bg(cx.theme().background)
                    .border_1()
                    .border_color(if active {
                        ACCENT_ACTIVE
                    } else {
                        cx.theme().border
                    })
                    .shadow_sm()
                    .when(active, |el| el.bg(cx.theme().secondary))
                    .child(
                        h_flex()
                            .w_full()
                            .items_center()
                            .justify_between()
                            .gap_2()
                            .child(
                                Radio::new(("dpi-radio", i))
                                    .checked(active)
                                    .label(format!("{} {}", t(Msg::Level, locale), i + 1))
                                    .tooltip(t(Msg::TipActiveSlot, locale))
                                    .on_click(cx.listener(move |this, selected: &bool, _, cx| {
                                        if !*selected {
                                            return;
                                        }
                                        let next = (slot + 1) as u8;
                                        if this.profile.active_slot == next {
                                            return;
                                        }
                                        set_active_slot(&mut this.profile, next);
                                        this.do_apply(cx);
                                    })),
                            )
                            .child(
                                div()
                                    .size_3()
                                    .rounded_full()
                                    .bg(swatch)
                                    .border_1()
                                    .border_color(cx.theme().border),
                            ),
                    )
                    .child(
                        h_flex()
                            .w_full()
                            .items_center()
                            .justify_center()
                            .gap_3()
                            .child(
                                Button::new(("dpi-dec", i))
                                    .outline()
                                    .label("−")
                                    .tooltip(t(Msg::TipDpiDec, locale))
                                    .on_click(cx.listener(move |this, _, _, cx| {
                                        let v = this.profile.dpi[slot].saturating_sub(100);
                                        set_dpi(&mut this.profile, slot, v);
                                        cx.notify();
                                    })),
                            )
                            .child(
                                v_flex()
                                    .items_center()
                                    .child(
                                        div()
                                            .text_2xl()
                                            .font_semibold()
                                            .child(format!("{dpi}")),
                                    )
                                    .child(
                                        div()
                                            .text_xs()
                                            .text_color(cx.theme().muted_foreground)
                                            .child(t(Msg::DpiValueLabel, locale)),
                                    ),
                            )
                            .child(
                                Button::new(("dpi-inc", i))
                                    .outline()
                                    .label("+")
                                    .tooltip(t(Msg::TipDpiInc, locale))
                                    .on_click(cx.listener(move |this, _, _, cx| {
                                        let v = this.profile.dpi[slot]
                                            .saturating_add(100)
                                            .min(DPI_MAX);
                                        set_dpi(&mut this.profile, slot, v.max(DPI_MIN));
                                        cx.notify();
                                    })),
                            ),
                    )
                    .child(
                        v_flex()
                            .w_full()
                            .gap_1()
                            .child(
                                div()
                                    .text_xs()
                                    .text_color(cx.theme().muted_foreground)
                                    .child(t(Msg::ColorLabel, locale)),
                            )
                            .child(
                                ColorSelect::new(&self.color_pickers[i])
                                    .accessibility_label(t(Msg::TipSlotColor, locale))
                                    .placeholder("#RRGGBB"),
                            ),
                    ),
            );
        }

        v_flex()
            .w_full()
            .gap_3()
            .child(self.section_label(t(Msg::SectionDpi, locale), cx))
            .child(grid)
    }

    fn settings_section(&self, cx: &mut Context<Self>) -> impl IntoElement {
        let locale = self.locale;

        let mut poll_row = h_flex()
            .w_full()
            .gap_2()
            .flex_wrap()
            .child(
                div()
                    .text_sm()
                    .text_color(cx.theme().muted_foreground)
                    .min_w(px(96.))
                    .child(format!("{}:", t(Msg::ReportRate, locale))),
            );
        for rate in PollRate::ALL {
            let selected = self.profile.poll == rate;
            poll_row = poll_row.child(
                Button::new(("poll", rate.hz() as usize))
                    .when(selected, |b| b.primary())
                    .when(!selected, |b| b.outline())
                    .small()
                    .label(format!("{} Hz", rate.hz()))
                    .tooltip(t(Msg::TipPollRate, locale))
                    .on_click(cx.listener(move |this, _, _, cx| {
                        this.profile.poll = rate;
                        cx.notify();
                    })),
            );
        }

        let chip = |id: &'static str,
                    label: String,
                    tip: &'static str,
                    cx: &mut Context<Self>,
                    on: fn(&mut Rs7App)| {
            Button::new(id)
                .outline()
                .small()
                .label(label)
                .tooltip(tip)
                .on_click(cx.listener(move |this, _, _, cx| {
                    on(this);
                    cx.notify();
                }))
        };

        v_flex()
            .w_full()
            .gap_3()
            .p_5()
            .rounded_xl()
            .bg(cx.theme().secondary)
            .border_1()
            .border_color(cx.theme().border.opacity(0.7))
            .child(self.section_label(t(Msg::SectionMouse, locale), cx))
            .child(poll_row)
            .child(
                h_flex()
                    .w_full()
                    .gap_2()
                    .flex_wrap()
                    .child(chip(
                        "scroll",
                        format!(
                            "{}: {}",
                            t(Msg::Scroll, locale),
                            scroll_label(self.profile.scroll_flag, locale)
                        ),
                        t(Msg::TipScroll, locale),
                        cx,
                        |this| {
                            this.profile.scroll_flag = if this.profile.scroll_flag == 0 {
                                1
                            } else {
                                0
                            };
                        },
                    ))
                    .child(chip(
                        "lod",
                        format!(
                            "{}: {}",
                            t(Msg::Lod, locale),
                            lod_label(self.profile.liftoff_height, locale)
                        ),
                        t(Msg::TipLod, locale),
                        cx,
                        |this| {
                            this.profile.liftoff_height = (this.profile.liftoff_height + 1) % 3;
                        },
                    ))
                    .child(chip(
                        "light",
                        format!(
                            "{}: {}",
                            t(Msg::LightMode, locale),
                            self.profile.light_mode
                        ),
                        t(Msg::TipLightMode, locale),
                        cx,
                        |this| {
                            this.profile.light_mode = (this.profile.light_mode + 1) % 7;
                        },
                    ))
                    .child(chip(
                        "sensor",
                        {
                            let sf = self.profile.sensor_flag;
                            let on = |bit: u8| if sf & bit != 0 { "on" } else { "off" };
                            format!(
                                "{} A={} R={} M={}",
                                t(Msg::Sensor, locale),
                                on(SENSOR_WIRE_ANGLE_SNAP),
                                on(SENSOR_WIRE_RIPPLE),
                                on(SENSOR_WIRE_MOTION_SYNC),
                            )
                        },
                        t(Msg::TipSensor, locale),
                        cx,
                        |this| {
                            this.profile.sensor_flag =
                                sensor_flag_wire_nudge(this.profile.sensor_flag, 1);
                        },
                    ))
                    .child(chip(
                        "esports",
                        format!(
                            "{}: {}",
                            t(Msg::Esports, locale),
                            esports_label(self.profile.e_sports_flag, locale)
                        ),
                        t(Msg::TipEsports, locale),
                        cx,
                        |this| {
                            this.profile.e_sports_flag = (this.profile.e_sports_flag + 1) % 3;
                        },
                    ))
                    .child(chip(
                        "debounce",
                        format!(
                            "{}: {}",
                            t(Msg::Debounce, locale),
                            self.profile.button_respondtime
                        ),
                        t(Msg::TipDebounce, locale),
                        cx,
                        |this| {
                            this.profile.button_respondtime =
                                (this.profile.button_respondtime + 1) % 21;
                        },
                    ))
                    .child(chip(
                        "sleep",
                        format!(
                            "{}: {}",
                            t(Msg::Sleep, locale),
                            self.profile.sleep_light
                        ),
                        t(Msg::TipSleep, locale),
                        cx,
                        |this| {
                            this.profile.sleep_light = (this.profile.sleep_light + 1) % 61;
                        },
                    ))
                    .child(
                        Button::new("btn5")
                            .outline()
                            .small()
                            .label(format!(
                                "{}: {}",
                                t(Msg::Button5, locale),
                                self.profile.buttons[5].label_short()
                            ))
                            .tooltip(t(Msg::TipButton5, locale))
                            .on_click(cx.listener(|this, _, _, cx| {
                                let next = cycle_button5(&mut this.profile);
                                this.push_log(format!(
                                    "{} → {}",
                                    t(Msg::Button5, this.locale),
                                    next.label_short()
                                ));
                                cx.notify();
                            })),
                    ),
            )
    }

    fn footer_hint(&self, cx: &Context<Self>) -> impl IntoElement {
        h_flex()
            .w_full()
            .px_4()
            .py_2()
            .items_center()
            .justify_between()
            .border_t_1()
            .border_color(cx.theme().border)
            .bg(cx.theme().title_bar)
            .child(
                div()
                    .text_xs()
                    .text_color(cx.theme().muted_foreground)
                    .child(t(Msg::TipSaveShortcut, self.locale)),
            )
            .child(
                div()
                    .text_xs()
                    .text_color(cx.theme().muted_foreground)
                    .child(format!(
                        "{} · {}",
                        self.locale.label(),
                        if self.applying {
                            t(Msg::Applying, self.locale)
                        } else {
                            t(Msg::Status, self.locale)
                        }
                    )),
            )
    }
}

impl Focusable for Rs7App {
    fn focus_handle(&self, _: &App) -> FocusHandle {
        self.focus_handle.clone()
    }
}

impl Render for Rs7App {
    fn render(&mut self, window: &mut Window, cx: &mut Context<Self>) -> impl IntoElement {
        if self.colors_dirty {
            self.sync_color_pickers(window, cx);
        }

        v_flex()
            .id("rs7-app")
            .key_context("Rs7")
            .track_focus(&self.focus_handle)
            .size_full()
            .bg(cx.theme().background)
            .text_color(cx.theme().foreground)
            .on_action(cx.listener(|this, _: &SaveProfile, _, cx| this.do_apply(cx)))
            .on_action(cx.listener(|this, _: &RefreshDevice, _, cx| this.do_refresh(cx)))
            .on_action(cx.listener(|this, _: &OpenLogs, window, cx| {
                this.open_logs(window, cx)
            }))
            .child(self.title_bar(cx))
            .child(
                div()
                    .id("rs7-body")
                    .flex_1()
                    .w_full()
                    .min_h_0()
                    .overflow_y_scroll()
                    .child(
                        v_flex()
                            .w_full()
                            .gap_5()
                            .px_5()
                            .py_5()
                            .child(self.connection_hero(cx))
                            .child(self.dpi_section(window, cx))
                            .child(self.settings_section(cx)),
                    ),
            )
            .child(self.footer_hint(cx))
    }
}

fn rgb_to_hsla(rgb: [u8; 3]) -> Hsla {
    Rgba {
        r: f32::from(rgb[0]) / 255.0,
        g: f32::from(rgb[1]) / 255.0,
        b: f32::from(rgb[2]) / 255.0,
        a: 1.0,
    }
    .into()
}

fn hsla_to_rgb(color: Hsla) -> [u8; 3] {
    let rgba = Rgba::from(color);
    [
        (rgba.r.clamp(0.0, 1.0) * 255.0).round() as u8,
        (rgba.g.clamp(0.0, 1.0) * 255.0).round() as u8,
        (rgba.b.clamp(0.0, 1.0) * 255.0).round() as u8,
    ]
}

fn main() {
    // Wayland first when WAYLAND_DISPLAY is set; X11 if only DISPLAY is set
    // (common under `sudo`, which often drops Wayland env vars).
    #[cfg(all(target_os = "linux", not(target_env = "ohos")))]
    let app = gpui_kit::platform::linux(WindowingModes::WAYLAND | WindowingModes::X11)
        .with_assets(gpui_kit::assets::Assets);
    #[cfg(not(all(target_os = "linux", not(target_env = "ohos"))))]
    let app = gpui_kit::application().with_assets(gpui_kit::assets::Assets);
    app.run(move |cx| {
        gpui_kit::init(cx);

        cx.bind_keys([
            KeyBinding::new("alt-f4", Quit, None),
            KeyBinding::new("ctrl-s", SaveProfile, None),
            KeyBinding::new("ctrl-r", RefreshDevice, None),
            KeyBinding::new("ctrl-l", OpenLogs, None),
        ]);
        cx.on_action(|_: &Quit, cx: &mut App| {
            cx.quit();
        });

        let window_options = WindowOptions {
            window_bounds: Some(WindowBounds::centered(size(px(1120.), px(780.)), cx)),
            ..TitleBar::window_options()
        };

        gpui_kit::open_window(window_options, cx, |window, cx| {
            window.activate_window();
            window.set_window_title("Smailwolf RS7");
            Theme::change(ThemeMode::Dark, Some(window), cx);
            cx.new(|cx| Rs7App::new(window, cx))
        })
        .expect("failed to open window");
    });
}
