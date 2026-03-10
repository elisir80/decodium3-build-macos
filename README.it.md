# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.4.3 (Italiano)

Per la versione bilingue completa (English + Italiano), vedere [README.md](README.md).

## Sintesi italiana (v1.4.3)

Questa release copre il ciclo `v1.4.2 -> v1.4.3`:

- Hardening crash Linux FT2 Async L2:
  - aggiunti limiti rigidi output Fortran (`ndecodes/nout <= 100`) nel decode triggered,
  - parsing righe async C++ reso sicuro a lunghezza fissa,
  - reset esplicito buffer async e contatori a ogni ciclo decode/toggle.
- Protezione QSO attivo con Wait Features + AutoSeq:
  - lock partner ora usa con priorita' il partner runtime (`m_hisCall`),
  - lock attivato prima (`REPLYING` fino a `SIGNOFF`) quando Wait Features + AutoSeq sono attivi.
- Comportamento runtime:
  - eliminati casi di testo "sporco" e over-read al primo decode con Async L2 su Linux.
- Allineamento release/documentazione:
  - metadati fork e documentazione aggiornati a `v1.4.3`.
- Resta incluso tutto l'hardening `v1.4.2` (LotW POST + redirect policy, token minimo bind remoto, regole visibilita' controlli FT2, restore finestre strumenti/mappa, safeguard geometria Linux).
- `.pkg` non necessario: release solo DMG/ZIP/SHA256 (macOS) e AppImage/SHA256 (Linux).

## Target release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (12.x, sperimentale/best-effort)
- Linux x86_64 AppImage

## Hamlib nelle build release

- Su macOS i workflow eseguono `brew update` + `brew upgrade hamlib` prima della compilazione.
- Su Linux i workflow compilano Hamlib dall'ultima release ufficiale GitHub e lo installano in `/usr/local` prima di compilare `ft2`.
- I log CI riportano sempre la versione effettiva usata (`rigctl --version`, `pkg-config --modversion hamlib`).

## Requisiti minimi Linux

- Architettura: `x86_64` (64 bit)
- CPU: dual-core 2.0 GHz o superiore
- RAM: minimo 4 GB (consigliati 8 GB)
- Spazio disco: almeno 500 MB liberi (AppImage + log + impostazioni)
- Runtime:
  - Linux con `glibc >= 2.35` (classe Ubuntu 22.04 o successiva)
  - supporto `libfuse2` / FUSE2 per avvio AppImage
  - stack audio ALSA, PulseAudio o PipeWire
- Integrazione stazione: hardware CAT/audio secondo setup radio

## Avvio consigliato AppImage su Linux

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Comando macOS (quarantena)

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentazione

- [RELEASE_NOTES_v1.4.3.md](RELEASE_NOTES_v1.4.3.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.3.md](doc/GITHUB_RELEASE_BODY_v1.4.3.md)
- [doc/README.it.md](doc/README.it.md)
- [doc/WEBAPP_SETUP_GUIDE.it.md](doc/WEBAPP_SETUP_GUIDE.it.md)
- [doc/WEBAPP_SETUP_GUIDE.en-GB.md](doc/WEBAPP_SETUP_GUIDE.en-GB.md)
- [doc/WEBAPP_SETUP_GUIDE.es.md](doc/WEBAPP_SETUP_GUIDE.es.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
