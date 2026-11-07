# Smailwolf RS7 — Protocolo HID (YJX-CHIP)

Engenharia reversa do software oficial Windows (`DeviceDriver.exe` / `YJXUI.dll`) via captura USB (`usbmon`) com o mouse no receptor 2.4G.

Última atualização: 2026-11-07

## Capacidades (UI oficial)

Confirmado no software *mouse RS7* (aba DPI):

| Feature | Valores |
|---------|---------|
| Slots de DPI | **6** (Levels1 … Levels6) |
| Faixa de DPI | **200 – 24000** (slider; uint16 no fio cabe até 65535) |
| Report rate | **125 / 250 / 500 / 1000 Hz** |
| Scroll direction | Forward / Reverse (ainda não mapeado no protocolo) |

Screenshot de referência: `docs/rs7-dpi-ui.png`.

## Identificação USB

| Modo | VID:PID | Produto | Interface de config |
|------|---------|---------|---------------------|
| Cabo | `a8a4:2255` | YJX-CHIP USB MOUSE | **MI_02** |
| Receptor 2.4G | `a8a5:2255` | YJX-CHIP USB Receiver | **MI_02** |

Fonte: `reference/windows-app/app/config.xml` (local; `device_type="101"`).

No Linux (receptor), a interface 2 aparece como `hidraw` com Usage Page vendor `0xFF01`, reports de **64 bytes** IN/OUT (sem Report ID).

## Transporte

| Direção | Endpoint | Primeiro byte |
|---------|----------|---------------|
| Host → device | Interrupt **OUT `0x03`** | `0x55` |
| Device → host | Interrupt **IN `0x83`** | `0xAA` (eco do comando) |

Pacote sempre com **64 bytes**.

```
Offset  Size  Campo
------  ----  -----
0       1     Magic: 0x55 (host) / 0xAA (device)
1       1     Command ID
2       1     Tag / família (0xAE nos cmds de perfil)
3       1     Checksum
4..63   60    Payload (+ padding 0x00)
```

### Checksum

Para os comandos de perfil (`0x0F`, `0x22`, `0x23`) com tag `0xAE`:

```text
checksum = sum(packet[4:64]) & 0xFF
```

O byte `[2]` fica `0xAE`. O device ecoa o pacote inteiro com magic `0xAA`.

## Sequência de Apply (software oficial)

Ao clicar Apply no driver, a sequência observada é:

| # | CMD | Função observada |
|---|-----|------------------|
| 1 | `0x0D` | Init / handshake |
| 2 | `0x0D` | Init (segundo pacote) |
| 3 | `0x10` | Preparação |
| 4–8 | `0x09` | Blocos auxiliares (5 pacotes) |
| 9 | **`0x0F`** | Escreve perfil (DPI + polling) |
| 10 | **`0x22`** | Confirma slot ativo + DPI desse slot |
| 11 | **`0x23`** | Confirma polling |

### Sequência Apply (DeviceDriver `FUN_004298c0` job 6)

| # | CMD | Builder | Papel |
|---|-----|---------|-------|
| 1..N | **`0x0D`** | `FUN_0042ac40` | **Upload de macros gravadas** — blob fatiado em chunks de **`0x38` (56) bytes** (`size/0x38` + resto); buffer mínimo / só-header = **`0x40`** → sempre **2** chunks vazios nas capturas Apply |
| N+1 | **`0x10`** | fim de `FUN_0042ac40` | commit/prep (`55 10 a5 …`) |
| +5 | **`0x09`** | `FUN_0042b470` | mapas de botões ×5 (abaixo) |
| +1 | **`0x0F`** | `FUN_0042ba10` | perfil DPI/RGB/flags |
| +1 | **`0x22`** | `FUN_0042b6b0` | slot ativo |
| +1 | **`0x23`** | `FUN_0042b8d0` | poll |

**Framing `0x0D` (vazio, byte-exact nas capturas Apply):**

| Chunk | Hex (prefixo) | Notas (`FUN_0042ac40`) |
|-------|---------------|------------------------|
| 0 | `55 0d 00 38 38 00…` | capacidade `0x38`; offset 0 |
| 1 | `55 0d 00 40 08 38…` | total `0x40`; resto `0x40%0x38=8` no último chunk |

Eventos `t_macrorecord.type` → blob (`FUN_0042ac40`); cada evento normal ocupa **4 bytes** no buffer (começa em offset `0x40`):

| type | Encoding (resumo) |
|------|-------------------|
| 1 | Delay — avança cursor pelo `delay_time`; último evento OR `0x80` no byte+2 |
| 2 | Key down — flags em +2 (`0x40` + bit1/bit2 para faixa scancode); scancode via `FUN_0043e570` em +3 |
| 3 | Key up — similar sem `0x40` |
| 4/5 | Mouse/scroll com valor; "Scroll Up/Down" → `0x0144` / `0xFF44` |
| 6/7 | Scroll Up / Down fixos |
| 8–0xB | Byte `0x46` + valor |
| 0xC | `0x46` + nibbles empacotados; flags `0x40`/`0x80` em +1 |

Binding no botão: `macro_type=0x70`, `value` = índice da macro. Captura Apply com macro **não-vazia** ainda útil para validar o payload após o header `0x40` (headers de chunk vazios já batem com o helper).

---

## Comando `0x0E` — ler perfil (GET)

Quando o software oficial **abre**, ele lê a config atual do mouse (não só escreve no Apply).

| Direção | CMD | Tag | Papel |
|---------|-----|-----|-------|
| OUT | `0x0E` | `0xA5` | Pedido de leitura |
| IN | `0x0E` | `0xA5` | Resposta com o mesmo layout de dados do `0x0F` |

### Pedido (captura `captures/open-software-in-vm.pcapng`)

```text
55 0e a5 2e 2e 00 00 00 00 00 00 00 00 00 …
│  │  │  │  └─ hdr 0x2E (mesmo do write 0x0F)
│  │  │  └─ checksum = sum([4:64]) & 0xFF
│  │  └─ tag 0xA5 (família GET / helpers)
│  └─ cmd GET profile
└─ magic OUT
```

### Resposta — layout idêntico ao `0x0F`

```
Offset  Campo
------  -----
10      poll_code
11      num_stages (6)
12      active_slot (1..6)
13+     6 × uint16 LE = DPI de cada slot
```

Exemplo da mesma captura (slot 4 ativo, poll 500 Hz):

```text
aa 0e a5 73 2e 00 00 00 00 00 03 06 04 20 03 60 09 80 0c 20 03 60 09 80 …
                           │  │  │  └─ DPI [800, 2400, 3200, 800, 2400, 3200]
                           │  │  └─ active_slot = 4
                           │  └─ stages = 6
                           └─ poll_code = 3 (500 Hz)
```

Padrão geral observado no open: **GET = CMD write − 1** com tag `0xA5`
(`0x0F`↔`0x0E` perfil; `0x09`↔`0x08` blocos auxiliares; também há GET `0x30`).

O TUI (`cargo run --release`) envia `0x0E` ao abrir o HID e preenche a UI com a resposta.

---

## Comandos `0x08` / `0x09` — mapa de botões (macros por tecla)

GET = `0x08`, SET = `0x09`, tag `0xA5`. Layout idêntico (confirmado em `open-software-in-vm.pcapng` e nos Apply).

```
Offset  Campo
------  -----
0       magic (55 OUT / AA IN)
1       cmd 0x08 GET / 0x09 SET
2       tag 0xA5
3       checksum = sum([4:64]) & 0xFF
4       hdr 0x20
5–6     0
7       profile_index (GET 0..=5; Apply SET usa 0..=4)
8+      9 × 4 bytes = (macro_type, value, value2, value3)
```

Defaults no fio (Apply / GET índices 0–4):

| Botão | Bytes | Significado (UI 1033.lan) |
|-------|-------|---------------------------|
| 0 | `20 01 00 00` | Left-Click (`macro_type=0x20`, HID bit 1) |
| 1 | `20 02 00 00` | Right-Click |
| 2 | `20 04 00 00` | Middle-Click |
| 3 | `20 08 00 00` | Backward |
| 4 | `20 10 00 00` | Forward |
| 5 | `21 55 00 00` | DPI Loop (`macro_type=0x21`) |
| 6 | `21 38 01 00` | DPI + (`value2=0x01`) |
| 7 | `21 38 ff 00` | DPI − (`value2=0xFF`) |
| 8 | `00 00 00 00` | Disabled |

`macro_type` (decoder `FUN_00411ce0` @ `0x411ce0`):

| type | Papel |
|------|-------|
| `0x00` / `FF FF` | Disabled |
| `0x10` | Keyboard (+ modifiers em `value2` bits Shift/Ctrl/Alt/Win) |
| `0x20` | Mouse button (`value` = bit HID 1/2/4/8/16) |
| `0x21` | Special (encoder `0x411866`): DPI± (`0x38`+`value2`), DPI Loop (`0x55`), AIM (`0xAA`), + `0x61`/`0x62` → UI types `0x0b`/`0x0c` (rótulos ausentes no `1033.lan`) |
| `0x30` | Multimedia — `value` = HID Consumer Page: `0xB5` next, `0xB6` prev, `0xB7` stop, `0xCD` play/pause, `0xE2` mute, `0xE9`/`0xEA` vol± (`FUN_00411ce0`) |
| `0x50` | Fire Key — `value` = parâmetro (cps/delay; UI id `0x1b`); AIM é `0x21`/`0xAA` |
| `0x70` | Macro gravada — `value` = índice na lista `t_macro_data` |
| `0xF0` | Atalhos (`value`=grupo, `value2`=1..3). **Grupo 1** = DPI +/−/Loop (lang 150–152). **Grupo 2** = Report Rate +/−/Loop (lang 153–155). Encoder @ `0x411932` / decode `FUN_00411ce0` |

Keyboard (`0x10`): `value` = HID usage from Windows VK via `FUN_0043e570` (A–Z→`0x04`–`0x1d`, `1`–`0`→`0x1e`–`0x27`, F1–F12→`0x3a`–`0x45`, arrows→`0x4f`–`0x52`, modifiers→`0xe0`–`0xe7`, … — helper `vk_to_hid_usage`). `value2` modifier bits (`FUN_00411ce0`): `1` Ctrl, `2` Shift, `4` Alt, `8` Win.

SQLite: `t_key_macro_data` (binding por botão) + `t_macro_data` / `t_macrorecord` (eventos gravados). O **binding** sobe no `0x09`; o upload da sequência gravada para o firmware ainda não foi isolado numa captura dedicada.

O open prelude faz **`0x08`×6**; o índice 5 costuma voltar lixo/`acac…`. Apply reescreve **`0x09`×5**.

---

## Comando `0x0F` — perfil (DPI + RGB + flags + poll)

```
Offset  Campo
------  -----
9       light_mode
10      poll_code
11      num_stages (sempre 6 nas capturas)
12      active_slot (1..6, 1-based)
13–24   6 × uint16 LE = DPI (`dpi_groupN_value`)
25–42   6 × RGB (`dpi_groupN_rgb`, 3 bytes cada, ordem R,G,B)
43      scroll_flag (0 = frente / Forward radio, 1 = invertido / Reverse — `FUN_0041b000`)
44      liftoff_height (LOD; UI Low≈1 / High≈2)
45      sensor_flag (wire; ver remap abaixo)
46      button_respondtime (debounce)
47      sleep_light
48      e-sports_flag
49–63   footer fixo `ff 01 0a ff ff 00…` — **igual** em GET `0x0E` e Apply `0x0F` (constante de firmware; TUI ecoa `PROFILE_FOOTER`)
```


**`sensor_flag` remap** (`FUN_0042ba10` pack + `FUN_0041b2a0` checkboxes): o valor no SQLite não é igual ao byte no fio.

| UI (1033.lan) | Bit SQLite | → wire |
|---------------|------------|--------|
| Ripple / Ripple Control | `0x04` | `0x10` |
| Angle Snap | `0x08` | `0x01` |
| Motion Sync | `0x10` | `0x20` |

“Sensor Linearity” (string `573`) é só título/chrome da seção — **não** é um bit. Os três toggles reais escrevem DB `0x04|0x08|0x10` e o Apply remapeia para o byte `[45]` do `0x0F`.

### Exemplo (slot 1 = 1600, poll 500 Hz)

```text
55 0f ae 8c 2e 00 00 00 00 00 03 06 01 40 06 60 09 80 0c 20 03 60 09 80 0c ...
                           │  │  │  └──────── 6× DPI LE ────────┘
                           │  │  └─ active_slot = 1
                           │  └─ stages = 6
                           └─ poll_code = 3 (500 Hz)
```

DPI decodificados: `[1600, 2400, 3200, 800, 2400, 3200]`

### Slots de DPI

A UI expõe exatamente **6 levels**. Cada um é um `uint16` LE (valores observados de 800 até 10200; UI permite **200–24000**).

| Slot (UI) | Índice no pacote | Offset do uint16 |
|-----------|------------------|------------------|
| Levels1 | `active_slot=1` / 1º valor | 13–14 |
| Levels2 | `active_slot=2` / 2º valor | 15–16 |
| Levels3 | 3º valor | 17–18 |
| Levels4 | 4º valor | 19–20 |
| Levels5 | 5º valor | 21–22 |
| Levels6 | 6º valor | 23–24 |

O Apply reescreve a **tabela inteira** de 6 DPI; o slot editado também aparece em `active_slot` e no comando `0x22`.

### Capturas que confirmaram DPI

| Captura | Mudança | Resultado em `0x0F` |
|---------|---------|---------------------|
| `captures/dpi-slot1-from-800-to-1600.pcapng` | Slot 1 → 1600 | `[1600, 2400, 3200, 800, 2400, 3200]`, active=1 |
| `captures/slot1-1600-to-800.pcapng` | Slot 1 → 800 | `[800, 2400, 3200, 800, 2400, 3200]`, active=1 |
| `captures/slot2-2400-to-2000.pcapng` | Slot 2 → 2000 | `[800, 2000, 3200, 800, 2400, 3200]`, active=2 |

---

## Polling (report rate)

A UI oferece só estes quatro valores: **125 / 250 / 500 / 1000 Hz**.

Campo no fio: `0x0F[10]` e também `0x23[10]`.

| Hz (UI) | `poll_code` | Status |
|---------|-------------|--------|
| 125 | `1` | Na UI; no fio inferido (`Hz/250`), captura pendente |
| 250 | `2` | Confirmado (`captures/pooling-1000-to-250.pcapng`) |
| 500 | `3` | Confirmado (capturas de DPI com poll inalterado) |
| 1000 | `4` | Confirmado (`captures/pooling-500-to-1000.pcapng`) |

Fórmula:

```text
poll_code = report_rate_hz / 250
```

### Capturas que confirmaram polling

| Captura | Mudança | `poll_code` final |
|---------|---------|-------------------|
| `captures/pooling-500-to-1000.pcapng` | 500 → 1000 | `4` |
| `captures/pooling-1000-to-250.pcapng` | 1000 → 250 | `2` |

---

## Comando `0x22` — slot ativo

```
Offset  Campo
------  -----
10      active_slot (1..6)
11–12   DPI desse slot (uint16 LE)
```

Exemplos:

| Ação | Payload relevante |
|------|-------------------|
| Slot 1 = 800 | `01 20 03` |
| Slot 1 = 1600 | `01 40 06` |
| Slot 2 = 2000 | `02 d0 07` |

## Comando `0x23` — polling

```
Offset  Campo
------  -----
10      poll_code (mesmo mapa do 0x0F)
```

Exemplos: `03` = 500 Hz, `04` = 1000 Hz, `02` = 250 Hz.

---

## Comando `0xFA` (device → host) — multiplexado

O device envia reports **não solicitados** no EP `0x83` — **não há OUT** pedindo. O **mesmo CMD `0xFA`** carrega vários layouts; discrimine **somente** pelo marker `[8]` (não pelo header `[4]`).

Confirmado no driver oficial `DeviceDriver.exe` (dispatch em VA `0x42cadb`, build 1.2 / SHA-256 `a7064d35…119df`) e UI `YJXUI.dll!BatteryCtrl::SetBatteryInfo(int,int)` @ `0x1001fe50`.

| Variante | Marker `[8]` | `[9]` | `[10]` | Ação no driver |
|----------|--------------|-------|--------|----------------|
| **Notify** | `0x50` / `0x60` | código de status | — | **não** é bateria |
| **Bateria** | `0xD0` | percent (clamp ≤100) | FLAGS | `SetBatteryInfo(pct, flags)` |
| **Stage/slot** | `0x10` | `active_slot` 1–6 | `poll_code` | atualiza `dpi_index` + `report_rate` |
| **Light** | `0x11` | `light_mode` (clamp ≤6) | — | grava `light_mode` |

O driver ainda exige magic `0xAA` + cmd `0xFA` e aplica um throttle de ~200 ms entre processamentos FA.

### Bateria (`… d0 PCT FLAGS`)

```
aa fa ae CKSUM 38 01 01 01 d0 PCT FLAGS 00...
│  │  │  │     │           │  │   └─ 0 = em uso; ≠0 ≈ carregando (candidato)
│  │  │  │     │           │  └─ percent 0–100 (driver: min(raw, 100))
│  │  │  │     │           └─ marker 0xD0  ← critério oficial
│  │  │  │     └─ header frequente 0x38 (NÃO usar sozinho como discriminante)
│  │  │  └─ checksum = sum([4:64]) & 0xFF
│  │  └─ tag 0xAE
│  └─ cmd 0xFA
└─ magic IN
```

Confirmado em `captures/idle-turn-on-on-receiver-mode.pcapng` e `open-software-in-vm.pcapng`:

| Payload (início) | PCT | FLAGS |
|------------------|-----|-------|
| `aa fa ae 5b … d0 50 00` | **80** | 0 |
| `aa fa ae 5c … d0 51 00` | **81** | 0 |
| `… d0 48 01` (`dpi-2400`) | **72** | 1 (charging?) |

Capturas também mostram jitter FA **80↔81**. O UI filtra com o mesmo throttle ~200 ms do driver, prioriza FA `0xD0` sobre GET `0x30`, e exige confirmação para oscilação de ±1%.

**Bug clássico (TUI antiga):** tratar `header==0x38` **ou** qualquer `0xFA` como bateria. Markers `0x50`/`0x60` (notify) e `0x10` (slot) então viram “porcentagem” falsa (1%…6% = slot, ou códigos de notify).

### Stage ativo — botão DPI (`… 10 SLOT POLL`)

```
aa fa ae CKSUM 0a 01 01 01 10 SLOT POLL 00...
│                    │  │    │    └─ poll_code (mesmo mapa do 0x0F/0x23)
│                    │  │    └─ active_slot 1..6
│                    │  └─ marker 0x10
│                    └─ header 0x0A
```

Exemplos (strace / botão DPI):

| Payload (início) | Slot | poll_code |
|------------------|------|-----------|
| `aa fa ae 21 0a 01 01 01 10 01 03` | 1 | 3 (500 Hz) |
| `aa fa ae 22 … 10 02 03` | 2 | 3 |
| `aa fa ae 26 … 10 06 03` | 6 | 3 |

### Power-on no receptor (mesma captura idle)

Ao emparelhar/ligar em 2.4G, ordem observada:

| CMD | Papel |
|-----|--------|
| `0xE6` | Serial TLV-ish: após hdr, campos ASCII separados por `00` (`ID`, `S5E98=5E98`, `B-66`, …) |
| `0xED` | Link/sessão — tag `AE`; `[8]` observado `01`/`02` entre estados |
| `0xFA` | Bateria (logo em seguida, ~0.6–0.7 s) |
| `0x03` | Ident (open): ASCII desde `[8]` — `YJX.co.mouse…` + datas de build |

---

## Software oficial (referência)

Cópia analisada em `software/mouse-RS7-1.2/` (versão **1.2.2** no `config.xml`; projeto Ghidra local `software/RS7.gpr`):

- `DeviceDriver.exe` — protocolo HID (`HidD_*` / `WriteFile`); defaults embutidos (`report_rate=3`, `dpi_group0..5_value`, `scroll_flag`, `liftoff_height`, `light_mode`, …)
- `YJXUI.dll` — UI (`BatteryCtrl::SetBatteryInfo`, `DPIControl`, …)
- `config.xml` — VID/PID e `MI_02`

### Sequência de abertura (oficial)

De `captures/open-software-in-vm.pcapng`:

`0x30` → `0x08`×6 → **`0x0E`** (perfil) → `0x03` (ident; resposta ASCII tipo `YJX.co.m`)

A bateria `0xFA`/`0xD0` já aparece **antes** desses GETs (não solicitada). O TUI agora espelha o prelude + GET `0x0E`.

### GET `0x30` — info / bateria solicitada

Pedido (tag `A5`, hdr `0x2E`): `55 30 a5 2e 2e …`

Resposta observada: `aa 30 a5 2e 0a 00 00 00 **50** 00 …` — DeviceDriver trata `[8]`/`[9]` como `SetBatteryInfo(percent, flags)` (`FUN_0042a1d0` / `FUN_0042c720`). Aqui `0x50` = 80%, alinhado às FA `0xD0` do mesmo boot. Ou seja, **`0x30` também lê bateria** (além de “info”); byte `[4]=0x0A` ainda sem mapa completo.

## Como capturar (resumo)

1. Host: `usbmon` + Wireshark (`sg wireshark -c wireshark`)
2. VM Windows com passthrough só do receptor (`a8a5:2255`)
3. Cabo USB do mouse **desconectado**
4. Capturar `usbmonN` do bus do dongle, **sem capture filter**
5. Mudar **uma** opção → Apply → salvar `.pcapng`
6. Filtrar depois: `usb.endpoint_address == 0x03 || usb.endpoint_address == 0x83`

## Status do mapa

| Feature | Status |
|---------|--------|
| 6 slots de DPI (Levels1–6) | Confirmado (UI + fio) |
| Faixa DPI 200–24000 | Confirmado (UI); fio usa uint16 LE |
| Slot ativo | Confirmado |
| **Ler perfil (`0x0E` GET)** | **Confirmado** (`captures/open-software-in-vm.pcapng`) — mesmo layout do `0x0F` |
| Report rate 250/500/1000 | Confirmado no fio |
| Report rate 125 | Na UI; captura `poll_code=1` pendente |
| Bateria (`0xFA` + marker `0xD0`) | **Confirmado** (2.4G unsolicited); GET **`0x30`** `[8]`/`[9]` também alimenta `SetBatteryInfo` (poll sob demanda — candidato a cabo) |
| Notify FA (`0x50`/`0x60`) | **Confirmado** no driver — **não** é bateria |
| Light mode FA (`0x11`) + perfil `[9]` | **Confirmado**; TUI edita `light_mode` 0..=6 |
| Stage ativo via botão DPI (`0xFA` + marker `0x10`) | **Confirmado** slot em `[9]`, poll_code em `[10]` |
| Open prelude `0x30`/`0x08`/`0x03` | **Confirmado** (`open-software-in-vm.pcapng`) |
| Checksum `0x0F/22/23` (+ `0xFA`) / GET `0xA5` | Confirmado |
| Scroll direction (`scroll_flag` @ `[43]`) | **Confirmado** no `0x0F` + TUI |
| RGB por slot DPI (`dpi_groupN_rgb` @ `[25..]`) | **Confirmado** no `0x0F` / Apply; GET `0x0E` muitas vezes zera RGB |
| Light mode no perfil (`[9]` + FA `0x11`) | **Confirmado** |
| Remapeamento de botões (`0x08`/`0x09`, 9×4) | **Confirmado** + tabela `macro_type` (`FUN_00411ce0`) |
| Macro gravada | Binding `0x70` no `0x09` + upload blob via **`0x0D` chunks** (`FUN_0042ac40`) **confirmados**; layout interno do blob precisa captura com macro real |
| Light FX (brightness/speed/direction) | Só `light_mode` no `0x0F`/`FA 0x11`; params ricos ficam no SQLite `t_light_data` — wire dedicado **pendente** |
| LOD (`liftoff_height` @ `[44]`) | **Confirmado** no perfil |
| `sensor_flag` (Ripple / Angle Snap / Motion Sync) | **Confirmado** DB↔wire + UI checkboxes (`FUN_0041b2a0`/`FUN_0042ba10`); TUI edita os 3 bits no `[45]` |
| debounce (`button_respondtime`) | Byte `[46]` no `0x0F`; UI “Debounce Time” (valor livre → atoi); capturas default `0`; TUI 0..=20 |
| e-sports (`e-sports_flag`) | Byte `[48]`; radio On (`FUN_0041b150`) grava SQLite `"2"` / Off `"1"` → atoi no fio; GET/Apply de fábrica ainda `0`. TUI cicla 0/1/2. Branch firmware `device_rev < 0xC9` altera paths Apply |
| `sleep_light` | Byte `[47]`; UI “SleepTime” / “Not Sleep”; default SQLite `20` |
| `leftbtn_lock` | Só SQLite/XML (host UI lock); **não** aparece no builder `0x0F` |
| Modo cabo (`a8a4`) | Mesma MI_02/`0xFF01`; com cabo+dongle plugados, preferir `a8a4` e exigir resposta GET `0x0E` (dongle ocioso não responde) |

## Arquivos de captura

| Arquivo | Conteúdo |
|---------|----------|
| `captures/dpi-slot1-from-800-to-1600.pcapng` | Slot 1 → 1600 |
| `captures/slot1-1600-to-800.pcapng` | Slot 1 → 800 |
| `captures/slot2-2400-to-2000.pcapng` | Slot 2 → 2000 |
| `captures/pooling-500-to-1000.pcapng` | Poll → 1000 Hz |
| `captures/pooling-1000-to-250.pcapng` | Poll → 250 Hz (slot 2 = 10200 no mesmo Apply) |
| `captures/idle-turn-on-on-receiver-mode.pcapng` | Power-on 2.4G: `E6`/`ED`/`FA` (80–81%, UI cheia) |
| `captures/open-software-in-vm.pcapng` | Abertura do software oficial: GET `0x0E` (perfil), `0x08`/`0x30` |
| `docs/rs7-dpi-ui.png` | Screenshot da aba DPI do software oficial |

## Notas

- O valor **10200** no Levels2 é válido na UI (dentro de 200–24000) e apareceu no fio em `captures/pooling-1000-to-250.pcapng` — não é corrupção de pacote.
- Não enviar pacotes inventados em massa: risco de corromper perfil. Preferir espelhar a sequência do software e ter o driver Windows à mão para reset.
- Destino natural depois do CLI próprio: driver em [libratbag](https://github.com/libratbag/libratbag) / Piper, se a comunidade quiser.
- TUI Linux: raiz do repo (`cargo run --release`) (`cargo run --release`).
