# Smailwolf RS7 — Protocolo HID (YJX-CHIP)

Engenharia reversa do software oficial Windows (`DeviceDriver.exe` / `YJXUI.dll`) via captura USB (`usbmon`) com o mouse no receptor 2.4G.

Última atualização: 2026-07-11

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

Os comandos `0x0D` / `0x10` / `0x09` ainda não foram totalmente decodificados; para reaplicar DPI/polling, o núcleo útil é **`0x0F` + `0x22` + `0x23`** (idealmente reproduzindo a sequência completa como o software faz).

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

## Comando `0x0F` — perfil (DPI + poll)

```
Offset  Campo
------  -----
10      poll_code
11      num_stages (sempre 6 nas capturas)
12      active_slot (1..6, 1-based)
13+     6 × uint16 little-endian = DPI de cada slot
```

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

O device envia reports **não solicitados** no EP `0x83` — **não há OUT** pedindo. O **mesmo CMD `0xFA`** carrega dois layouts distintos; discrimine pelo byte `[8]` (ou `[4]`).

| Variante | `[4]` | `[8]` | `[9]` | `[10]` |
|----------|-------|-------|-------|--------|
| **Bateria** | `0x38` | `0xD0` | percent 0–100 | FLAGS (0 = não carregando) |
| **Stage/slot ativo** | `0x0A` | `0x10` | `active_slot` 1–6 | `poll_code` |

### Bateria (`… 38 … d0 PCT FLAGS`)

O software mostra ícone de bateria no modo 2.4G (`BatteryCtrl` / `SetBatteryInfo(int, int)` no `YJXUI.dll`).

```
aa fa ae CKSUM 38 01 01 01 d0 PCT FLAGS 00...
│  │  │  │     │           │  │   └─ 0 = em uso (não carregando)
│  │  │  │     │           │  └─ percent 0–100
│  │  │  │     │           └─ marker 0xD0
│  │  │  │     └─ header fixo observado (38 01 01 01)
│  │  │  └─ checksum = sum([4:64]) & 0xFF
│  │  └─ tag 0xAE
│  └─ cmd 0xFA
└─ magic IN
```

Confirmado em `captures/idle-turn-on-on-receiver-mode.pcapng` (UI “cheia” ≈ ~80%+):

| t (s) | Payload (início) | PCT | FLAGS |
|-------|------------------|-----|-------|
| 8.484 | `aa fa ae 5b … d0 50 00` | **80** | 0 |
| 9.234 | `aa fa ae 5c … d0 51 00` | **81** | 0 |

Outros (`captures/dpi-2400.pcapng`): `d0 50 00` (80), `d0 48 00` (72), `d0 48 01` (72, FLAGS=1 candidato a charging).

Captura com mouse **carregando** ainda é útil para cravar `FLAGS`.

### Stage ativo — botão DPI (`… 0a … 10 SLOT POLL`)

Ao ciclar o botão DPI no mouse, o firmware notifica o stage atual **no mesmo CMD `0xFA`**, sem Apply do host:

```
aa fa ae CKSUM 0a 01 01 01 10 SLOT POLL 00...
│                    │  │    │    └─ poll_code (mesmo mapa do 0x0F/0x23)
│                    │  │    └─ active_slot 1..6
│                    │  └─ marker 0x10
│                    └─ header 0x0A
```

Exemplos observados (strace no `rs7-tui` enquanto ciclava o botão):

| Payload (início) | Slot | poll_code |
|------------------|------|-----------|
| `aa fa ae 21 0a 01 01 01 10 01 03` | 1 | 3 (500 Hz) |
| `aa fa ae 22 … 10 02 03` | 2 | 3 |
| `aa fa ae 26 … 10 06 03` | 6 | 3 |

**Bug clássico:** tratar todo `0xFA` como bateria faz o indicador mostrar `1%`…`6%` (o slot) e a UI não atualizar o nível ativo.

### Power-on no receptor (mesma captura idle)

Ao emparelhar/ligar em 2.4G, ordem observada:

| CMD | Papel |
|-----|--------|
| `0xE6` | Identidade/serial (ASCII: `ID`, `S5E98=5E98`, `B-66`, …) |
| `0xED` | Status de link / sessão |
| `0xFA` | Bateria (logo em seguida, ~0.6–0.7 s) |

---

## Software oficial (referência)

Instalador/app Windows em `reference/` (local, gitignored):

- `DeviceDriver.exe` — usa `HidD_SetFeature` / `WriteFile` + SetupAPI
- `YJXUI.dll` — UI
- `config.xml` — VID/PID e `MI_02`

IDs internos observados nas strings: `dpi_groupN_value`, `dpi_index`, `report_rate`, `liftoff_height`, `light_mode`, etc. (RGB / LOD / macros ainda não mapeados no fio).

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
| Bateria (`0xFA` + marker `0xD0`) | **Confirmado** percent em `[9]`; `FLAGS` charging ainda candidato |
| Stage ativo via botão DPI (`0xFA` + marker `0x10`) | **Confirmado** slot em `[9]`, poll_code em `[10]` |
| Checksum `0x0F/22/23` (+ `0xFA`) / GET `0xA5` | Confirmado |
| Scroll direction | Na UI; protocolo pendente |
| RGB / lighting | Pendente |
| Remapeamento de botões / macros | Pendente |
| LOD / angle / debounce | Pendente |
| Modo cabo (`a8a4`) | Mesma interface esperada; não validado nas capturas |

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
