# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.3.1

English and Italian documentation for this fork is included in this repository.

## English

Fork release `v1.3.1` is based on upstream `iu8lmc/Decodium-3.0-Codename-Raptor` and adds macOS-focused operational hardening.

- Upstream base: Decodium v3.0 SE "Raptor"
- Fork release: `v1.3.1`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- License: GPLv3

### What this fork adds

- Stable macOS runtime migration to `ft2.app` (including subprocess path/layout fixes).
- TX/PTT/audio robustness improvements for repeated FT2 operation.
- Persistent audio/radio behavior and safer settings restore on macOS.
- Startup microphone permission preflight to avoid delayed popup during operation.
- Robust DT/NTP strategy (weak-sync + deadband + confirmations + sparse jump guard + hold mode).
- Shared-memory path on macOS migrated to `mmap` backend; `.pkg` sysctl bootstrap is no longer required in standard release artifacts.
- Raptor baseline maintained with fork integrations from previous 1.1.x work.

### Build (macOS)

```bash
cmake -B build-raptor-port -G "Unix Makefiles" \
  -DCMAKE_BUILD_TYPE=Release \
  -DWSJT_GENERATE_DOCS=OFF \
  -DWSJT_SKIP_MANPAGES=ON \
  -DWSJT_BUILD_UTILS=OFF

cmake --build build-raptor-port --target wsjtx -j8
```

Run:

```bash
/Users/salvo/Desktop/ft2/decodium3-raptor-merge/build-raptor-port/ft2.app/Contents/MacOS/ft2
```

### macOS quarantine

If macOS blocks app startup, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

### Documentation

- Release notes (EN/IT): [RELEASE_NOTES_v1.3.1.md](RELEASE_NOTES_v1.3.1.md)
- Changelog (EN/IT): [CHANGELOG.md](CHANGELOG.md)
- Security and bug analysis report: [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
- macOS porting details (EN/IT): [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- DT/NTP architecture (EN/IT): [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
- GitHub release body template (EN/IT): [doc/GITHUB_RELEASE_BODY_v1.3.1.md](doc/GITHUB_RELEASE_BODY_v1.3.1.md)

### CI release targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Linux x86_64 AppImage

### Linux minimum requirements

- Architecture: `x86_64` (64-bit)
- CPU: dual-core 2.0 GHz or better
- RAM: 4 GB minimum (8 GB recommended)
- Storage: at least 500 MB free for AppImage + logs/settings
- OS/runtime:
  - Linux with `glibc >= 2.35` (Ubuntu 22.04 class or newer)
  - `FUSE 2` support (`libfuse2`) or an AppImage-compatible launcher/runtime
  - ALSA/PulseAudio/PipeWire audio stack available
- Radio integration: CAT/audio interface hardware as required by station setup

## Italiano

La release fork `v1.3.1` e' basata su `iu8lmc/Decodium-3.0-Codename-Raptor` e aggiunge hardening operativo specifico per macOS.

- Base upstream: Decodium v3.0 SE "Raptor"
- Versione fork: `v1.3.1`
- Bundle/eseguibile su macOS: `ft2.app` / `ft2`
- Licenza: GPLv3

### Cosa aggiunge questo fork

- Migrazione runtime stabile su macOS verso `ft2.app` (con fix su path/layout dei sottoprocessi).
- Miglioramenti di robustezza TX/PTT/audio in uso FT2 ripetuto.
- Persistenza piu affidabile di audio/radio e ripristino impostazioni su macOS.
- Preflight permesso microfono all'avvio per evitare popup tardivo durante l'uso.
- Strategia DT/NTP robusta (weak-sync + deadband + conferme + filtro sparse jump + hold mode).
- Path shared memory su macOS migrato a backend `mmap`; bootstrap sysctl via `.pkg` non piu' richiesto negli artifact release standard.
- Baseline Raptor mantenuta con integrazioni fork ereditate dal lavoro 1.1.x.

### Compilazione (macOS)

```bash
cmake -B build-raptor-port -G "Unix Makefiles" \
  -DCMAKE_BUILD_TYPE=Release \
  -DWSJT_GENERATE_DOCS=OFF \
  -DWSJT_SKIP_MANPAGES=ON \
  -DWSJT_BUILD_UTILS=OFF

cmake --build build-raptor-port --target wsjtx -j8
```

Esecuzione:

```bash
/Users/salvo/Desktop/ft2/decodium3-raptor-merge/build-raptor-port/ft2.app/Contents/MacOS/ft2
```

### Quarantena macOS

Se macOS blocca l'avvio dell'app, eseguire:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

### Documentazione

- Note di rilascio (EN/IT): [RELEASE_NOTES_v1.3.1.md](RELEASE_NOTES_v1.3.1.md)
- Changelog (EN/IT): [CHANGELOG.md](CHANGELOG.md)
- Report analisi sicurezza e bug: [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
- Porting macOS (EN/IT): [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- Architettura DT/NTP (EN/IT): [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
- Template release GitHub (EN/IT): [doc/GITHUB_RELEASE_BODY_v1.3.1.md](doc/GITHUB_RELEASE_BODY_v1.3.1.md)

### Target CI release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Linux x86_64 AppImage

### Requisiti minimi Linux

- Architettura: `x86_64` (64 bit)
- CPU: dual-core 2.0 GHz o superiore
- RAM: minimo 4 GB (consigliati 8 GB)
- Spazio disco: almeno 500 MB liberi per AppImage + log/impostazioni
- OS/runtime:
  - Linux con `glibc >= 2.35` (classe Ubuntu 22.04 o successiva)
  - supporto `FUSE 2` (`libfuse2`) o launcher/runtime compatibile AppImage
  - stack audio ALSA/PulseAudio/PipeWire disponibile
- Integrazione radio: hardware CAT/interfaccia audio secondo setup stazione

## Credits

- WSJT-X by Joe Taylor K1JT and the WSJT Development Group
- Decodium v3.0 SE Raptor by IU8LMC
- Fork integration and macOS porting by Salvatore Raccampo 9H1SR
