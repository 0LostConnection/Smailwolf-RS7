# Handoff — Smailwolf RS7

**Data:** 2026-11-07 (sessão RE loop RGB/macro/sensor interrompida sob pedido de handoff)  
**Repo:** `/home/lost/Projects/Smailwolf-RS7` — workspace `rs7-core` + `rs7-tui` + `rs7-gui` + `PROTOCOL.md` + `captures/` + `software/`  
**Branch:** `main` (dirty; **não commitado** nesta sessão)

---

## Onde paramos (resume aqui)

Workspace UI entregue sob pedido do usuário (*GUI GPUI + TUI + i18n pt_BR/en_US*):

1. **`crates/rs7-core`** — protocolo, HID worker, `i18n`, `actions` (ex.: `cycle_button5`)  
2. **`crates/rs7-tui`** — Ratatui; tecla `l` alterna idioma  
3. **`crates/rs7-gui`** — GPUI Kit (`gpui-kit` 0.9 crates.io); botão de idioma + Apply/Refresh  
4. Achados RE anteriores (sensor/scroll/e-sports/empty-0x0D/VK/media/`0xF0`) permanecem

**Testes agora:** `cargo test --workspace` → **27/27 OK**; `cargo check -p rs7-gui` OK.

---

## Estado git (não commitado)

```
M  Cargo.toml Cargo.lock HANDOFF.md PROTOCOL.md README.md
D  src/*                       # monólito removido
?? crates/rs7-core/ rs7-tui/ rs7-gui/
?? graphify-out/
?? software/                   # blobs oficiais + rea-out + Ghidra leftovers
```

Não fazer commit a menos que o usuário peça.

---

## Como retomar (ordem obrigatória)

1. **Graphify primeiro** (regra do workspace) antes de Grep/Read amplo:
   ```bash
   graphify query "sensor_flag macro 0x0D Apply 0x0F"
   graphify explain "sensor_flag"
   # após editar código:
   graphify update .
   ```
2. Canônico de protocolo: **`PROTOCOL.md`** (mais atual que este handoff em detalhes de offsets).
3. Código: `crates/rs7-core/src/protocol.rs` (wire) + `device.rs` (hidapi) + `i18n.rs` / `actions.rs`; UIs em `crates/rs7-tui` e `crates/rs7-gui`.
4. Decompiles: `software/rea-out/*.c` (Ghidra headless; REA MCP costuma timeout).
5. Binário: `software/mouse-RS7-1.2/DeviceDriver.exe` (image base `0x400000`).
6. UI strings: `software/mouse-RS7-1.2/language/1033.lan` (**UTF-16 LE**).
7. Capturas: `captures/*.pcapng` — filtro `usb.endpoint_address == 0x03 || usb.endpoint_address == 0x83`.

### Ghidra headless (padrão desta sessão)

```bash
# RS7.gpr às vezes LockException → usar /tmp project fresco
/opt/ghidra/support/analyzeHeadless /tmp/rs7-ghidraN RS7tmpN \
  -import software/mouse-RS7-1.2/DeviceDriver.exe \
  -scriptPath /tmp -postScript DecompXxx.java -deleteProject
```

PE map útil: `.text` file `0x400` → VA `0x401000`.

---

## Achados fechados nesta sessão (não reabrir sem evidência nova)

### `sensor_flag` @ `0x0F[45]`

Checkboxes `FUN_0041b2a0` (`this+0x458/45c/460`) + remap Apply `FUN_0042ba10`:

| UI (1033.lan) | DB bit | Wire |
|---------------|--------|------|
| Ripple | `0x04` | `0x10` |
| Angle Snap | `0x08` | `0x01` |
| Motion Sync | `0x10` | `0x20` |

“Sensor Linearity” (string `573`) = chrome de seção, **não** bit.  
Helpers: `sensor_flag_db_to_wire` / `wire_to_db` / `wire_nudge`. TUI Focus `SensorFlag`.

### Scroll @ `[43]`

`FUN_0041b000`: radio Forward (`this+0x470`) checked → SQLite `"0"`; unchecked → `"1"`.  
Wire: **0 = frente, 1 = invertido** (já na TUI).

### E-Sports @ `[48]`

`FUN_0041b150`: On radio (`this+0x484`) checked → `"2"`, unchecked → `"1"`.  
Factory GET/Apply ainda mostra **0**. TUI cicla 0/1/2.

### Empty macro `0x0D` (`FUN_0042ac40`)

Blob mínimo/header **`0x40`** → 2 chunks de capacidade **`0x38`**:

| Chunk | Prefixo observado |
|-------|-------------------|
| 0 | `55 0d 00 38 38 00…` |
| 1 | `55 0d 00 40 08 38…` |

`build_empty_macro_chunks()` = byte-exact. Eventos começam no offset `0x40` do blob.  
**Ainda falta:** captura Apply com macro **não-vazia** para validar payload + headers com size > `0x40`.

### Keyboard / media

- `vk_to_hid_usage` ← `FUN_0043e570` (VK Windows → HID usage em `macro_type=0x10`).
- `value2` modifiers: `1` Ctrl, `2` Shift, `4` Alt, `8` Win.
- Media `0x30`: `B5` next, `B6` prev, `B7` stop, `CD` play/pause, `E2` mute, `E9`/`EA` vol±.
- Shortcut `0xF0`: pares `(value,value2)` → preset UI `0x0F…0x15` (labels 187+ no `.lan` — pareamento soft).
- Special `0x21` / `0x61` → UI type `0x0b` (soft: Report Rate family).

### Light FX

Só `light_mode` no fio (`0x0F[9]` + FA `0x11`). Brightness/speed/direction ficam no SQLite `t_light_data` / YJXUI — **sem** comando HID dedicado encontrado.

---

## TUI / GUI — estado

Focus cycle (TUI): DPI slots → active → poll → scroll → LOD → light → **sensor → e-sports → debounce → sleep** → Apply → log.

| Tecla / UI | Ação |
|------------|------|
| Ctrl+S / Apply | sequência oficial |
| `r` / Refresh | GET `0x0E` |
| `b` / Button 5 | cicla: DPI loop → AIM → DPI± → poll shortcuts → media → off |
| `[]{} ,.` | RGB ±16 (TUI) |
| `l` / Language | pt_BR ↔ en_US |
| ←→ | nudge no focus (TUI) |

`hid_write` = **`[0x00]` + 64 bytes** (Report ID 0).  
GUI: `cargo run -p rs7-gui` (`gpui-kit` from crates.io).

---

## Decompiles úteis em `software/rea-out/`

| Arquivo | Função |
|---------|--------|
| `FUN_0042ba10.c` / `profile-builder.c` | builder `0x0F` |
| `FUN_0042ac40.c` | chunks `0x0D` + event types |
| `FUN_00411ce0.c` | decoder `macro_type` |
| `FUN_0043e570-scancode.c` | VK→HID |
| `FUN_0041b2a0-sensor-pack.c` | sensor checkboxes |
| `FUN_0041b000-esports-pack.c` | na verdade **scroll** pack |
| `FUN_0041b150-esports.c` | e-sports pack |
| `FUN_00412d90-sensor-ui.c` | UI init labels sensor |
| `FUN_004298c0-apply-orch.c` | orquestração Apply |

REA MCP (`rea` namespace) falha com timeout com frequência → preferir Ghidra headless.

---

## Backlog (próximo agente)

Prioridade sugerida:

1. **Captura usbmon Apply com macro gravada não-vazia** → fechar payload `0x0D` após header `0x40`.
2. **Special `0x61`/`0x62`** — achar labels (lang 158/159 faltam no `1033.lan`; checar Skin/outros locales).
3. Opcional: captura `poll_code=1` (125 Hz); FLAGS bateria em carga; modo cabo `a8a4`.
4. Remap editor completo de 9 botões (hoje: defaults + btn5 cycle).
5. Debounce: range real da UI além do clamp TUI 0..=20.

**Fechado no resume:** footer constante; `0xF0` grupo1=DPI host, grupo2=Report Rate; encoder UI→wire @ `0x411866`.

---

## Hardware / run

| Modo | VID:PID |
|------|---------|
| Cabo | `a8a4:2255` |
| 2.4G | `a8a5:2255` |

Config = **MI_02**, Usage Page `0xFF01`, 64 B reports.

```bash
sudo cp udev/99-smailwolf-rs7.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
cargo run -p rs7-tui --release   # Ctrl+S Apply · r refresh · l idioma · q quit
cargo run -p rs7-gui --release   # GPUI · idioma / Apply / Refresh
```

Captura: VM Windows com passthrough **só** do receptor; cabo do mouse **fora**; `usbmon` no host sem capture filter.

---

## Mensagem curta para o próximo agente

> Graphify antes de explorar. Wire: `PROTOCOL.md` + `crates/rs7-core/src/protocol.rs`. UIs: `rs7-tui` / `rs7-gui` (pt_BR+en_US). RE backlog: (1) captura macro não-vazia `0x0D`, (2) labels special `0x61`/`0x62`. `cargo test` 27/27. Não commitiar sem pedido. REA timeout → Ghidra `/tmp` headless.
