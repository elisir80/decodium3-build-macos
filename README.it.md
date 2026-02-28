# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.3.1 (Italiano)

Per la versione bilingue completa (English + Italiano), vedere [README.md](README.md).

## Sintesi italiana

Questa release fork (`v1.3.1`) e' basata su Decodium v3.0 SE Raptor upstream e introduce hardening operativo specifico per macOS:

- migrazione runtime stabile su `ft2.app` / `ft2`;
- fix path sottoprocessi (`jt9`) nel bundle;
- robustezza TX/PTT/audio in cicli FT2 ripetuti;
- persistenza piu affidabile di periferiche audio/radio;
- strategia DT/NTP robusta con weak-sync, conferme e filtro salti su set server sparsi.

## Target release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Linux x86_64 AppImage

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

## Comando macOS (quarantena)

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentazione

- [RELEASE_NOTES_v1.3.1.md](RELEASE_NOTES_v1.3.1.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
- [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
