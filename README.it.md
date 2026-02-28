# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.3.0 (Italiano)

Per la versione bilingue completa (English + Italiano), vedere [README.md](README.md).

## Sintesi italiana

Questa release fork (`v1.3.0`) e' basata su Decodium v3.0 SE Raptor upstream e introduce hardening operativo specifico per macOS:

- migrazione runtime stabile su `ft2.app` / `ft2`;
- fix path sottoprocessi (`jt9`) nel bundle;
- robustezza TX/PTT/audio in cicli FT2 ripetuti;
- persistenza piu affidabile di periferiche audio/radio;
- strategia DT/NTP robusta con weak-sync, conferme e filtro salti su set server sparsi.

## Comando macOS (quarantena)

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentazione

- [RELEASE_NOTES_v1.3.0.md](RELEASE_NOTES_v1.3.0.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
- [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
