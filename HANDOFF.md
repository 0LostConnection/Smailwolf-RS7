# Handoff — Smailwolf RS7

**Data:** 2026-07-11  
**Repo:** TUI Rust na raiz (`Cargo.toml` / `src/`) + protocolo + capturas.  
**Objetivo:** configurar DPI / report rate / bateria no Linux; protocolo YJX documentado.

---

## Estado atual (resumo)

| Item | Status |
|------|--------|
| TUI | **OK** — lê perfil ao abrir (`0x0E`), Apply (`Ctrl+S`), slot via botão DPI (`0xFA`), bateria |
| Testes | `cargo test` **14/14** |
| Protocolo | [`PROTOCOL.md`](PROTOCOL.md) — Apply + GET + `0xFA` multiplexado |
| Capturas | [`captures/`](captures/) |
| Windows blobs | `reference/` **local / gitignored** (instalador + app Wine) |

**Não** há suporte em Piper/libratbag/OpenRGB.

---

## Hardware

| Modo | VID:PID | Nome |
|------|---------|------|
| Cabo | `a8a4:2255` | YJX-CHIP USB MOUSE |
| Receptor 2.4G | `a8a5:2255` | YJX-CHIP USB Receiver |

- Config = **USB interface MI_02** (hidraw Usage Page `0xFF01`, 64 bytes IN/OUT).
- UI oficial: **6 slots DPI** (200–24000), poll **125/250/500/1000**, scroll/RGB/macros pendentes.
- Screenshot: `docs/rs7-dpi-ui.png`.

---

## Protocolo (atalho)

Arquivo canônico: **`PROTOCOL.md`**.

| Direção | EP | Magic |
|---------|-----|-------|
| Host → device | OUT `0x03` | `0x55` |
| Device → host | IN `0x83` | `0xAA` |

Checksum (tags `0xAE` / `0xA5`): `packet[3] = sum(packet[4:64]) & 0xFF`.

### Ler ao abrir

| CMD | Tag | Função |
|-----|-----|--------|
| **`0x0E`** | `0xA5` | GET perfil — **mesmo layout** do `0x0F` |

### Apply

`0x0D`×2 → `0x10` → `0x09`×5 → **`0x0F`** → **`0x22`** → **`0x23`**

| CMD | Função |
|-----|--------|
| `0x0F` | poll_code, stages=6, active_slot, 6×u16 LE DPI |
| `0x22` | Confirma slot + DPI |
| `0x23` | Confirma poll_code |

`poll_code`: 125→1, 250→2, 500→3, 1000→4.

### `0xFA` multiplexado (IN não solicitado)

| Marker `[8]` | Significado | `[9]` | `[10]` |
|--------------|-------------|-------|--------|
| `0xD0` (`[4]=0x38`) | Bateria | percent | FLAGS |
| `0x10` (`[4]=0x0A`) | Stage (botão DPI) | slot 1–6 | poll_code |

**Bug clássico (já corrigido):** tratar todo `0xFA` como bateria → UI mostra `1%`…`6%` (o slot).

### Linux write

`hid_write` = **`[0x00]` + 64 bytes**. Sem Report ID 0 o kernel trunca e o Apply não grava.

---

## Como rodar

```bash
sudo cp udev/99-smailwolf-rs7.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
# replug dongle; sem passthrough na VM

cargo run --release
# Ctrl+S = Apply · r = reler perfil · q = sair
```

---

## Capturas

| Arquivo | Conteúdo |
|---------|----------|
| `captures/dpi-slot1-from-800-to-1600.pcapng` | Apply DPI (achou o protocolo) |
| `captures/slot1-1600-to-800.pcapng` | Slot 1 → 800 |
| `captures/slot2-2400-to-2000.pcapng` | Slot 2 → 2000 |
| `captures/pooling-500-to-1000.pcapng` | Poll → 1000 |
| `captures/pooling-1000-to-250.pcapng` | Poll → 250 |
| `captures/idle-turn-on-on-receiver-mode.pcapng` | Power-on + bateria ~80% |
| `captures/open-software-in-vm.pcapng` | Open oficial → GET **`0x0E`** |
| `captures/dpi-2400.pcapng` | Early / pouco útil p/ Apply |

Filtro Wireshark: `usb.endpoint_address == 0x03 || usb.endpoint_address == 0x83`

---

## TUI — módulos

| Arquivo | Papel |
|---------|-------|
| `src/protocol.rs` | encode/decode + testes vs capturas |
| `src/device.rs` | hidapi worker (open → GET `0x0E` → events / Apply) |
| `src/ui.rs` | ratatui (PT), Ctrl+S, `r` refresh |
| `src/main.rs` | entrada |

Atalhos: **Ctrl+S** salva, **`r`** relê, Enter edita DPI.

---

## Limitações / próximos passos

1. Captura **poll 500→125** → cravar `poll_code=1`.
2. Captura **bateria carregando** → cravar `FLAGS`.
3. Mapear **scroll** e **RGB**.
4. Opcional: driver **libratbag** a partir de `PROTOCOL.md` + `protocol.rs`.
5. GET auxiliares no open (`0x08`, `0x30`) — pouco usados na TUI.

---

## Ambiente

- CachyOS, usuário `lost`; VM `win10` QEMU (`libvirt`) para capturas com passthrough.
- Wireshark: grupo `wireshark` + ACL `/dev/usbmon*`.
- Para config 2.4G: **só dongle** no host, cabo do mouse desconectado.

---

## Mensagem curta para o próximo agente

> Repo = TUI na raiz. Protocolo em `PROTOCOL.md`, evidência em `captures/`. Ao abrir: GET `0x0E` (tag `A5`). Apply: sequência oficial; write HID **Report ID 0**. `0xFA` é bateria **ou** stage — discriminar por `[8]`. Ctrl+S aplica. `reference/` e `.wine/` são locais. Próximo: 125 Hz, charging flag, RGB/scroll.
