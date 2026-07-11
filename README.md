# Smailwolf RS7

TUI Linux para configurar o mouse **Smailwolf RS7** (chip YJX), com o protocolo HID documentado em [`PROTOCOL.md`](PROTOCOL.md).

Não há suporte em Piper / libratbag / OpenRGB ainda.

## O que faz

- Detecta cabo (`a8a4:2255`) ou receptor 2.4G (`a8a5:2255`) na **interface MI_02**
- Ao abrir, **lê o perfil atual** com GET `0x0E` (DPI / poll / slot ativo)
- Mostra bateria e troca de slot via `0xFA` não solicitado
- Edita 6 slots de DPI (200–24000), slot ativo e report rate (125/250/500/1000 Hz)
- **Ctrl+S** aplica a sequência do software oficial: `0x0D`×2 → `0x10` → `0x09`×5 → `0x0F` → `0x22` → `0x23`

## Aviso

**Não envie pacotes HID aleatórios.** Só templates observados em captura, com checksum correto. Spam inventado pode corromper o perfil — tenha o driver Windows à mão se precisar resetar.

## Build / run

```bash
# udev (obrigatório)
sudo cp udev/99-smailwolf-rs7.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
# replug o dongle; mouse NÃO pode estar em passthrough na VM

cargo test
cargo run --release
# binário: target/release/rs7-tui
```

## Atalhos

| Tecla | Ação |
|-------|------|
| `Tab` / `↑` `↓` | Navegar |
| `←` `→` | Ajustar valor focado |
| `Enter` | Editar DPI / focar Aplicar |
| **`Ctrl+S`** | **Salvar / aplicar no mouse** |
| `r` | Reler perfil (`0x0E`) |
| `+` `-` | DPI ±100 |
| `[` `]` | DPI ±50 |
| `q` / `Esc` | Sair |

## Layout do repo

| Path | Conteúdo |
|------|----------|
| `src/` | TUI (`protocol`, `device`, `ui`) |
| `udev/` | Regra hidraw |
| `PROTOCOL.md` | Mapa do protocolo YJX |
| `captures/` | usbmon / pcapng da engenharia reversa |
| `docs/` | Screenshot da UI oficial |
| `HANDOFF.md` | Contexto para continuar o trabalho |
| `reference/` | *(local, gitignored)* instalador Windows / app extraído |

## Nota técnica (Linux)

Writes HID usam prefixo **Report ID `0x00`** + 64 bytes. Sem isso o kernel trata `0x55` como Report ID e o Apply “passa” sem efeito.

## Limitações

- RGB, macros, LOD, scroll reverse: ainda não mapeados
- `FLAGS` de carga em `0xFA`: candidato (falta captura carregando)
- Report rate 125 Hz: na UI; captura `poll_code=1` pendente
