//! Minimal pt_BR / en_US string table for TUI and GUI.

#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum Locale {
    #[default]
    PtBr,
    EnUs,
}

impl Locale {
    pub const ALL: [Locale; 2] = [Locale::PtBr, Locale::EnUs];

    pub fn label(self) -> &'static str {
        match self {
            Self::PtBr => "pt_BR",
            Self::EnUs => "en_US",
        }
    }

    pub fn toggle(self) -> Self {
        match self {
            Self::PtBr => Self::EnUs,
            Self::EnUs => Self::PtBr,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Msg {
    AppTitle,
    AppSubtitle,
    SearchingDevice,
    DeviceNotFound,
    DeviceOnline,
    DeviceOffline,
    ConfigLoaded,
    ApplyOk,
    ApplyFailed,
    Applying,
    ApplyHint,
    ApplyIgnoredNoDevice,
    Refresh,
    Refreshing,
    RefreshIgnoredNoDevice,
    Quit,
    Language,
    LanguageSwitched,
    Battery,
    BatteryCharging,
    BatteryInUse,
    BatteryWiredNa,
    BatteryWaiting,
    ConnectedWired,
    ConnectedReceiver,
    DpiSlots,
    ActiveSlot,
    ReportRate,
    Scroll,
    ScrollForward,
    ScrollReverse,
    Lod,
    LodDefault,
    LodLow,
    LodHigh,
    LightMode,
    Sensor,
    Esports,
    EsportsDefault,
    EsportsOff,
    EsportsOn,
    Debounce,
    Sleep,
    Buttons,
    Button5,
    CycleBtn5,
    Log,
    Status,
    State,
    Mode,
    Selection,
    MiscPanel,
    HelpTui,
    HelpRgb,
    HelpBtn5,
    HelpSensor,
    HelpLang,
    Level,
    InvalidDpi,
    SlotSelectedHw,
    SlotSelectedDpi,
    LightModeSet,
    ButtonsProfile,
    EditDpiTitle,
    EditDpiRange,
    EditTitle,
    PermissionDenied,
    DeviceBusy,
    WriteFailed,
    Disconnected,
    HidError,
    WorkerDisconnected,
    FatalError,
    // GUI tooltips / labels
    TipLanguage,
    TipRefresh,
    TipApply,
    TipDpiDec,
    TipDpiInc,
    TipActiveSlot,
    TipSlotColor,
    TipPollRate,
    TipScroll,
    TipLod,
    TipLightMode,
    TipSensor,
    TipEsports,
    TipDebounce,
    TipSleep,
    TipButton5,
    TipBattery,
    ColorLabel,
    DpiValueLabel,
    ViewLogs,
    TipViewLogs,
    TipSaveShortcut,
    SectionDpi,
    SectionConnection,
    SectionMouse,
    OfflineHint,
    Save,
}

pub fn t(msg: Msg, locale: Locale) -> &'static str {
    match (msg, locale) {
        (Msg::AppTitle, _) => "Smailwolf RS7",

        (Msg::AppSubtitle, Locale::PtBr) => "configurador HID (YJX / DeviceDriver 1.2)",
        (Msg::AppSubtitle, Locale::EnUs) => "HID configurator (YJX / DeviceDriver 1.2)",

        (Msg::SearchingDevice, Locale::PtBr) => "Procurando dispositivo…",
        (Msg::SearchingDevice, Locale::EnUs) => "Searching for device…",

        (Msg::DeviceNotFound, Locale::PtBr) => "dispositivo não encontrado",
        (Msg::DeviceNotFound, Locale::EnUs) => "device not found",

        (Msg::DeviceOnline, _) => "ONLINE",
        (Msg::DeviceOffline, _) => "OFFLINE",

        (Msg::ConfigLoaded, Locale::PtBr) => "Configuração carregada",
        (Msg::ConfigLoaded, Locale::EnUs) => "Configuration loaded",

        (Msg::ApplyOk, Locale::PtBr) => "Perfil aplicado com sucesso.",
        (Msg::ApplyOk, Locale::EnUs) => "Profile applied successfully.",

        (Msg::ApplyFailed, Locale::PtBr) => "Falha ao aplicar",
        (Msg::ApplyFailed, Locale::EnUs) => "Apply failed",

        (Msg::Applying, Locale::PtBr) => "Aplicando…",
        (Msg::Applying, Locale::EnUs) => "Applying…",

        (Msg::ApplyHint, Locale::PtBr) => "Aplicar perfil no mouse",
        (Msg::ApplyHint, Locale::EnUs) => "Apply profile to mouse",

        (Msg::ApplyIgnoredNoDevice, Locale::PtBr) => {
            "Apply ignorado: nenhum dispositivo na interface MI_02."
        }
        (Msg::ApplyIgnoredNoDevice, Locale::EnUs) => {
            "Apply ignored: no device on MI_02 interface."
        }

        (Msg::Refresh, Locale::PtBr) => "Reler",
        (Msg::Refresh, Locale::EnUs) => "Refresh",

        (Msg::Refreshing, Locale::PtBr) => "Lendo perfil do mouse…",
        (Msg::Refreshing, Locale::EnUs) => "Reading profile from mouse…",

        (Msg::RefreshIgnoredNoDevice, Locale::PtBr) => {
            "Refresh ignorado: nenhum dispositivo na interface MI_02."
        }
        (Msg::RefreshIgnoredNoDevice, Locale::EnUs) => {
            "Refresh ignored: no device on MI_02 interface."
        }

        (Msg::Quit, Locale::PtBr) => "Sair",
        (Msg::Quit, Locale::EnUs) => "Quit",

        (Msg::Language, Locale::PtBr) => "Idioma",
        (Msg::Language, Locale::EnUs) => "Language",

        (Msg::LanguageSwitched, Locale::PtBr) => "Idioma alterado.",
        (Msg::LanguageSwitched, Locale::EnUs) => "Language switched.",

        (Msg::Battery, Locale::PtBr) => "Bateria",
        (Msg::Battery, Locale::EnUs) => "Battery",

        (Msg::BatteryCharging, Locale::PtBr) => "carregando",
        (Msg::BatteryCharging, Locale::EnUs) => "charging",

        (Msg::BatteryInUse, Locale::PtBr) => "em uso",
        (Msg::BatteryInUse, Locale::EnUs) => "in use",

        (Msg::BatteryWiredNa, Locale::PtBr) => "USB · carregando",
        (Msg::BatteryWiredNa, Locale::EnUs) => "USB · charging",

        (Msg::BatteryWaiting, Locale::PtBr) => "Bateria: aguardando FA 0xD0…",
        (Msg::BatteryWaiting, Locale::EnUs) => "Battery: waiting for FA 0xD0…",

        (Msg::ConnectedWired, Locale::PtBr) => "Cabo (USB)",
        (Msg::ConnectedWired, Locale::EnUs) => "Wired (USB)",

        (Msg::ConnectedReceiver, Locale::PtBr) => "Receptor 2.4G",
        (Msg::ConnectedReceiver, Locale::EnUs) => "2.4G receiver",

        (Msg::DpiSlots, Locale::PtBr) => "Slots DPI (200–24000)",
        (Msg::DpiSlots, Locale::EnUs) => "DPI slots (200–24000)",

        // TUI status line: "Nível: 3" — GUI uses a radio control instead.
        (Msg::ActiveSlot, Locale::PtBr) => "Nível",
        (Msg::ActiveSlot, Locale::EnUs) => "Level",

        (Msg::ReportRate, Locale::PtBr) => "Report rate (Hz)",
        (Msg::ReportRate, Locale::EnUs) => "Report rate (Hz)",

        (Msg::Scroll, Locale::PtBr) => "Scroll",
        (Msg::Scroll, Locale::EnUs) => "Scroll",

        (Msg::ScrollForward, Locale::PtBr) => "frente",
        (Msg::ScrollForward, Locale::EnUs) => "forward",

        (Msg::ScrollReverse, Locale::PtBr) => "invertido",
        (Msg::ScrollReverse, Locale::EnUs) => "reverse",

        (Msg::Lod, Locale::PtBr) => "LOD",
        (Msg::Lod, Locale::EnUs) => "LOD",

        (Msg::LodDefault, Locale::PtBr) => "padrão",
        (Msg::LodDefault, Locale::EnUs) => "default",

        (Msg::LodLow, Locale::PtBr) => "baixo (~1mm)",
        (Msg::LodLow, Locale::EnUs) => "low (~1mm)",

        (Msg::LodHigh, Locale::PtBr) => "alto (~2mm)",
        (Msg::LodHigh, Locale::EnUs) => "high (~2mm)",

        (Msg::LightMode, Locale::PtBr) => "light_mode",
        (Msg::LightMode, Locale::EnUs) => "light_mode",

        (Msg::Sensor, Locale::PtBr) => "Sensor",
        (Msg::Sensor, Locale::EnUs) => "Sensor",

        (Msg::Esports, Locale::PtBr) => "E-Sports",
        (Msg::Esports, Locale::EnUs) => "E-Sports",

        (Msg::EsportsDefault, Locale::PtBr) => "default(0)",
        (Msg::EsportsDefault, Locale::EnUs) => "default(0)",

        (Msg::EsportsOff, Locale::PtBr) => "off(1)",
        (Msg::EsportsOff, Locale::EnUs) => "off(1)",

        (Msg::EsportsOn, Locale::PtBr) => "on(2)",
        (Msg::EsportsOn, Locale::EnUs) => "on(2)",

        (Msg::Debounce, Locale::PtBr) => "Debounce",
        (Msg::Debounce, Locale::EnUs) => "Debounce",

        (Msg::Sleep, Locale::PtBr) => "Sleep",
        (Msg::Sleep, Locale::EnUs) => "Sleep",

        (Msg::Buttons, Locale::PtBr) => "Botões",
        (Msg::Buttons, Locale::EnUs) => "Buttons",

        (Msg::Button5, Locale::PtBr) => "Botão 5",
        (Msg::Button5, Locale::EnUs) => "Button 5",

        (Msg::CycleBtn5, Locale::PtBr) => "b cicla",
        (Msg::CycleBtn5, Locale::EnUs) => "b cycles",

        (Msg::Log, Locale::PtBr) => "Log",
        (Msg::Log, Locale::EnUs) => "Log",

        (Msg::Status, Locale::PtBr) => "Status",
        (Msg::Status, Locale::EnUs) => "Status",

        (Msg::State, Locale::PtBr) => "Estado",
        (Msg::State, Locale::EnUs) => "State",

        (Msg::Mode, Locale::PtBr) => "Modo",
        (Msg::Mode, Locale::EnUs) => "Mode",

        (Msg::Selection, Locale::PtBr) => "Seleção",
        (Msg::Selection, Locale::EnUs) => "Selection",

        (Msg::MiscPanel, Locale::PtBr) => "Scroll / LOD / Light / Sensor",
        (Msg::MiscPanel, Locale::EnUs) => "Scroll / LOD / Light / Sensor",

        (Msg::HelpTui, Locale::PtBr) => {
            "Tab/↑↓  ·  ←→  ·  Enter  ·  Ctrl+S  ·  r  ·  +/- DPI  ·  []{} ,. RGB  ·  l idioma  ·  q"
        }
        (Msg::HelpTui, Locale::EnUs) => {
            "Tab/↑↓  ·  ←→  ·  Enter  ·  Ctrl+S  ·  r  ·  +/- DPI  ·  []{} ,. RGB  ·  l language  ·  q"
        }

        (Msg::HelpRgb, Locale::PtBr) => {
            "RGB no slot DPI: [ ] R · { } G · , . B (±16). Scroll/LOD/Light/Sensor: ←→."
        }
        (Msg::HelpRgb, Locale::EnUs) => {
            "DPI-slot RGB: [ ] R · { } G · , . B (±16). Scroll/LOD/Light/Sensor: ←→."
        }

        (Msg::HelpBtn5, Locale::PtBr) => {
            "b cicla botão 5 (DPI/poll/media). Apply manda 0x0D+0x09+0x0F…"
        }
        (Msg::HelpBtn5, Locale::EnUs) => {
            "b cycles button 5 (DPI/poll/media). Apply sends 0x0D+0x09+0x0F…"
        }

        (Msg::HelpSensor, Locale::PtBr) => {
            "Sensor: Angle Snap / Ripple / Motion Sync (bits no 0x0F[45])."
        }
        (Msg::HelpSensor, Locale::EnUs) => {
            "Sensor: Angle Snap / Ripple / Motion Sync (bits in 0x0F[45])."
        }

        (Msg::HelpLang, Locale::PtBr) => "l alterna pt_BR / en_US.",
        (Msg::HelpLang, Locale::EnUs) => "l toggles pt_BR / en_US.",

        (Msg::Level, Locale::PtBr) => "Nível",
        (Msg::Level, Locale::EnUs) => "Level",

        (Msg::InvalidDpi, Locale::PtBr) => "Valor inválido",
        (Msg::InvalidDpi, Locale::EnUs) => "Invalid value",

        (Msg::SlotSelectedHw, Locale::PtBr) => "Nível em uso (hardware)",
        (Msg::SlotSelectedHw, Locale::EnUs) => "Level in use (hardware)",

        (Msg::SlotSelectedDpi, Locale::PtBr) => "Nível DPI em uso no mouse",
        (Msg::SlotSelectedDpi, Locale::EnUs) => "DPI level in use on mouse",

        (Msg::LightModeSet, Locale::PtBr) => "light_mode =",
        (Msg::LightModeSet, Locale::EnUs) => "light_mode =",

        (Msg::ButtonsProfile, Locale::PtBr) => "Botões",
        (Msg::ButtonsProfile, Locale::EnUs) => "Buttons",

        (Msg::EditDpiTitle, Locale::PtBr) => "Editar Nível",
        (Msg::EditDpiTitle, Locale::EnUs) => "Edit Level",

        (Msg::EditDpiRange, Locale::PtBr) => "Faixa (Enter confirma, Esc cancela)",
        (Msg::EditDpiRange, Locale::EnUs) => "Range (Enter confirms, Esc cancels)",

        (Msg::EditTitle, Locale::PtBr) => "Edição",
        (Msg::EditTitle, Locale::EnUs) => "Edit",

        (Msg::PermissionDenied, Locale::PtBr) => {
            "permissão negada ao abrir o HID — verifique a regra udev / grupo plugdev"
        }
        (Msg::PermissionDenied, Locale::EnUs) => {
            "permission denied opening HID — check udev rule / plugdev group"
        }

        (Msg::DeviceBusy, Locale::PtBr) => {
            "dispositivo ocupado ou inacessível (passthrough para VM? feche o driver Windows / devolva o USB)"
        }
        (Msg::DeviceBusy, Locale::EnUs) => {
            "device busy or inaccessible (VM passthrough? close Windows driver / return USB)"
        }

        (Msg::WriteFailed, Locale::PtBr) => "falha ao escrever relatório HID",
        (Msg::WriteFailed, Locale::EnUs) => "failed to write HID report",

        (Msg::Disconnected, Locale::PtBr) => "dispositivo já desconectado",
        (Msg::Disconnected, Locale::EnUs) => "device already disconnected",

        (Msg::HidError, Locale::PtBr) => "erro HID",
        (Msg::HidError, Locale::EnUs) => "HID error",

        (Msg::WorkerDisconnected, Locale::PtBr) => "Worker HID desconectado.",
        (Msg::WorkerDisconnected, Locale::EnUs) => "HID worker disconnected.",

        (Msg::FatalError, Locale::PtBr) => "Erro fatal",
        (Msg::FatalError, Locale::EnUs) => "Fatal error",

        (Msg::TipLanguage, Locale::PtBr) => "Alterna os textos da interface entre pt_BR e en_US.",
        (Msg::TipLanguage, Locale::EnUs) => "Switches the interface language between pt_BR and en_US.",

        (Msg::TipRefresh, Locale::PtBr) => {
            "Lê de novo o perfil no mouse (prelude + GET 0x0E)."
        }
        (Msg::TipRefresh, Locale::EnUs) => {
            "Reads the profile from the mouse again (prelude + GET 0x0E)."
        }

        (Msg::TipApply, Locale::PtBr) => {
            "Grava DPI, poll, RGB, sensor e botões no mouse com a sequência oficial de Apply."
        }
        (Msg::TipApply, Locale::EnUs) => {
            "Writes DPI, poll, RGB, sensor, and buttons to the mouse with the official Apply sequence."
        }

        (Msg::TipDpiDec, Locale::PtBr) => "Diminui este slot em 100 DPI (mínimo 200).",
        (Msg::TipDpiDec, Locale::EnUs) => "Lowers this slot by 100 DPI (minimum 200).",

        (Msg::TipDpiInc, Locale::PtBr) => "Aumenta este slot em 100 DPI (máximo 24000).",
        (Msg::TipDpiInc, Locale::EnUs) => "Raises this slot by 100 DPI (maximum 24000).",

        (Msg::TipActiveSlot, Locale::PtBr) => {
            "Seleciona este nível de DPI e aplica no mouse na hora."
        }
        (Msg::TipActiveSlot, Locale::EnUs) => {
            "Select this DPI level and apply it to the mouse immediately."
        }

        (Msg::TipSlotColor, Locale::PtBr) => {
            "Cor RGB deste nível de DPI. Digite #RRGGBB ou escolha na paleta. Vai no pacote 0x0F."
        }
        (Msg::TipSlotColor, Locale::EnUs) => {
            "RGB color for this DPI level. Type #RRGGBB or pick from the palette. Stored in the 0x0F packet."
        }

        (Msg::TipPollRate, Locale::PtBr) => {
            "Frequência de report USB em Hz (125 / 250 / 500 / 1000)."
        }
        (Msg::TipPollRate, Locale::EnUs) => {
            "USB report rate in Hz (125 / 250 / 500 / 1000)."
        }

        (Msg::TipScroll, Locale::PtBr) => {
            "Direção da roda: frente (0) ou invertida (1) no perfil."
        }
        (Msg::TipScroll, Locale::EnUs) => {
            "Scroll wheel direction: forward (0) or reversed (1) in the profile."
        }

        (Msg::TipLod, Locale::PtBr) => {
            "Lift-off distance do sensor: padrão, baixo (~1 mm) ou alto (~2 mm)."
        }
        (Msg::TipLod, Locale::EnUs) => {
            "Sensor lift-off distance: default, low (~1 mm), or high (~2 mm)."
        }

        (Msg::TipLightMode, Locale::PtBr) => {
            "Modo de efeito de luz no firmware (0–6). Brilho e velocidade ficam só no app Windows."
        }
        (Msg::TipLightMode, Locale::EnUs) => {
            "Firmware light effect mode (0–6). Brightness and speed stay in the Windows app only."
        }

        (Msg::TipSensor, Locale::PtBr) => {
            "Bits do sensor no 0x0F: Angle Snap, Ripple Control e Motion Sync."
        }
        (Msg::TipSensor, Locale::EnUs) => {
            "Sensor bits in 0x0F: Angle Snap, Ripple Control, and Motion Sync."
        }

        (Msg::TipEsports, Locale::PtBr) => {
            "Flag e-sports do driver: 0=padrão, 1=off, 2=on."
        }
        (Msg::TipEsports, Locale::EnUs) => {
            "Driver e-sports flag: 0=default, 1=off, 2=on."
        }

        (Msg::TipDebounce, Locale::PtBr) => {
            "Tempo de debounce dos botões (0–20), escrito no perfil."
        }
        (Msg::TipDebounce, Locale::EnUs) => {
            "Button debounce time (0–20), written into the profile."
        }

        (Msg::TipSleep, Locale::PtBr) => {
            "Tempo até o sleep da luz (0–60). 0 costuma significar sem sleep."
        }
        (Msg::TipSleep, Locale::EnUs) => {
            "Light sleep delay (0–60). 0 usually means no sleep."
        }

        (Msg::TipButton5, Locale::PtBr) => {
            "Cicla o botão físico 5: DPI loop/AIM/passo, atalho de poll e mídia."
        }
        (Msg::TipButton5, Locale::EnUs) => {
            "Cycles physical button 5 through DPI loop/AIM/step, poll shortcut, and media."
        }

        (Msg::TipBattery, Locale::PtBr) => {
            "2.4G: FA 0xD0. Cabo: GET 0x30 (+ USB = carregando)."
        }
        (Msg::TipBattery, Locale::EnUs) => {
            "2.4G: FA 0xD0. Cable: GET 0x30 (+ USB = charging)."
        }

        (Msg::ColorLabel, Locale::PtBr) => "Cor",
        (Msg::ColorLabel, Locale::EnUs) => "Color",

        (Msg::DpiValueLabel, Locale::PtBr) => "DPI",
        (Msg::DpiValueLabel, Locale::EnUs) => "DPI",

        (Msg::ViewLogs, Locale::PtBr) => "Logs",
        (Msg::ViewLogs, Locale::EnUs) => "Logs",

        (Msg::TipViewLogs, Locale::PtBr) => "Abre o painel lateral com o histórico de eventos HID.",
        (Msg::TipViewLogs, Locale::EnUs) => "Opens the side panel with the HID event history.",

        (Msg::TipSaveShortcut, Locale::PtBr) => "Atalhos: Ctrl+S salva · Ctrl+R relê.",
        (Msg::TipSaveShortcut, Locale::EnUs) => "Shortcuts: Ctrl+S saves · Ctrl+R reloads.",

        (Msg::SectionDpi, Locale::PtBr) => "Níveis de DPI",
        (Msg::SectionDpi, Locale::EnUs) => "DPI levels",

        (Msg::SectionConnection, Locale::PtBr) => "Conexão",
        (Msg::SectionConnection, Locale::EnUs) => "Connection",

        (Msg::SectionMouse, Locale::PtBr) => "Mouse",
        (Msg::SectionMouse, Locale::EnUs) => "Mouse",

        (Msg::OfflineHint, Locale::PtBr) => "Conecte o receptor ou o cabo (MI_02) para ler o perfil.",
        (Msg::OfflineHint, Locale::EnUs) => "Connect the receiver or cable (MI_02) to read the profile.",

        (Msg::Save, Locale::PtBr) => "Salvar no mouse",
        (Msg::Save, Locale::EnUs) => "Save to mouse",
    }
}

pub fn lod_label(height: u8, locale: Locale) -> String {
    match height {
        0 => t(Msg::LodDefault, locale).to_string(),
        1 => t(Msg::LodLow, locale).to_string(),
        2 => t(Msg::LodHigh, locale).to_string(),
        n => format!("raw {n}"),
    }
}

pub fn esports_label(flag: u8, locale: Locale) -> String {
    match flag {
        0 => t(Msg::EsportsDefault, locale).to_string(),
        1 => t(Msg::EsportsOff, locale).to_string(),
        2 => t(Msg::EsportsOn, locale).to_string(),
        n => format!("raw({n})"),
    }
}

pub fn scroll_label(flag: u8, locale: Locale) -> &'static str {
    if flag == 0 {
        t(Msg::ScrollForward, locale)
    } else {
        t(Msg::ScrollReverse, locale)
    }
}

pub fn connection_label(mode: crate::protocol::ConnectionMode, locale: Locale) -> &'static str {
    match mode {
        crate::protocol::ConnectionMode::Wired => t(Msg::ConnectedWired, locale),
        crate::protocol::ConnectionMode::Receiver24G => t(Msg::ConnectedReceiver, locale),
    }
}
