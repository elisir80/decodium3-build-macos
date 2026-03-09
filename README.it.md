# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.4.2 (Italiano)

Per la versione bilingue completa (English + Italiano), vedere [README.md](README.md).

## Sintesi italiana (v1.4.2)

Questa release copre il ciclo `v1.4.1 -> v1.4.2`:

- Hardening sicurezza LotW:
  - richieste LotW con credenziali spostate da GET URL a POST HTTPS,
  - rimozione logging URL con credenziali,
  - redirect policy stretta per richieste con credenziali (HTTPS + host atteso).
- Hardening web remota:
  - bind LAN/WAN rifiutato con token sotto 12 caratteri,
  - avviso esplicito su traffico HTTP/WS in chiaro quando il bind e' esposto.
- Fix stabilita' Linux:
  - dialog impostazioni clampato alla geometria schermo (pulsanti sempre raggiungibili),
  - decode async su thread pool dedicato con stack controllato + guardie anti-overlap.
- Coerenza controlli FT2:
  - Async L2 ON di default entrando in FT2 e OFF automatico fuori FT2,
  - `Blocca la Freq Tx` e `Tx pari/1°` nascosti (e forzati OFF) in FT2.
- Ripristino finestre strumenti:
  - azioni `View -> Ionospheric Forecast` e `View -> DX Cluster` ripristinate.
- Dashboard web RX/TX:
  - eventi TX preservati nei refresh e prima transizione TX ora mostrata correttamente.
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

- [RELEASE_NOTES_v1.4.2.md](RELEASE_NOTES_v1.4.2.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.2.md](doc/GITHUB_RELEASE_BODY_v1.4.2.md)
- [doc/README.it.md](doc/README.it.md)
- [doc/WEBAPP_SETUP_GUIDE.it.md](doc/WEBAPP_SETUP_GUIDE.it.md)
- [doc/WEBAPP_SETUP_GUIDE.en-GB.md](doc/WEBAPP_SETUP_GUIDE.en-GB.md)
- [doc/WEBAPP_SETUP_GUIDE.es.md](doc/WEBAPP_SETUP_GUIDE.es.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
