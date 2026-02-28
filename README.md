# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.3.4

English and Italian documentation for this fork is included in this repository.

## English

Fork release `v1.3.4` is based on upstream `iu8lmc/Decodium-3.0-Codename-Raptor` and adds macOS-focused operational hardening.

- Upstream base: Decodium v3.0 SE "Raptor"
- Fork release: `v1.3.4`
- App bundle/executable on macOS: `ft2.app` / `ft2`
- License: GPLv3

### What this fork adds

- Stable macOS runtime migration to `ft2.app` (including subprocess path/layout fixes).
- TX/PTT/audio robustness improvements for repeated FT2 operation.
- Persistent audio/radio behavior and safer settings restore on macOS.
- Startup microphone permission preflight to avoid delayed popup during operation.
- Robust DT/NTP strategy (weak-sync + deadband + confirmations + sparse jump guard + hold mode).
- Shared-memory path on macOS migrated to `mmap` backend; `.pkg` sysctl bootstrap is no longer required in standard release artifacts.
- Startup freeze/hang mitigation by moving heavy startup file I/O off the UI thread.
- CTY/grid/satellite/comments data loaders hardened with size limits, parser guards, and fallback recovery.
- Raptor baseline maintained with fork integrations from previous 1.1.x work.
- Imported upstream Raptor features:
  - B4 strikethrough in Band Activity for worked-on-band calls.
  - Auto CQ caller FIFO queue (max 20) with auto-continue on QSO completion.
  - TX slot red bracket overlay on waterfall (FT2/FT8/FT4).
  - Auto `cty.dat` refresh at startup when missing or older than 30 days.
  - FT2 decoder updates: adaptive `syncmin` (`0.90/0.85/0.80`), extended AP types for Tx3/Tx4, relaxed deep-search thresholds, OSD depth boost near `nfqso`.
- Fork `v1.3.4` UI/runtime refinements:
  - Startup mode auto-selection now scans full frequency list (fixes FT8/FT2 mismatch on launch).
  - Responsive top controls with automatic 2-row layout on small displays.
  - Light-theme progress/seconds bar rendering fixed for clear visibility.
- Fork `v1.3.4` security/concurrency hardening:
  - TCI binary frame parser now validates header/payload lengths before access (malformed frame drop).
  - TCI pseudo-sync nested event loops removed from `mysleep1..8` (no `QEventLoop::exec()` path).
  - `foxcom_.wave` transmission path hardened with guarded snapshot reads across UI/audio threads.
  - TCI C++/Fortran audio boundary hardened with `kin` clamps and bounded writes.
  - TOTP generation aligned to NTP-corrected time source.
  - `QRegExp` migration completed in critical runtime/network paths (`mainwindow`, `wsprnet`).

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
./build-raptor-port/ft2.app/Contents/MacOS/ft2
```

### macOS quarantine

If macOS blocks app startup, run:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

### Documentation

- Release notes (EN/IT): [RELEASE_NOTES_v1.3.4.md](RELEASE_NOTES_v1.3.4.md)
- Changelog (EN/IT): [CHANGELOG.md](CHANGELOG.md)
- Security and bug analysis report: [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
- macOS porting details (EN/IT): [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- DT/NTP architecture (EN/IT): [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
- GitHub release body template (EN/IT): [doc/GITHUB_RELEASE_BODY_v1.3.4.md](doc/GITHUB_RELEASE_BODY_v1.3.4.md)

### CI release targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (experimental / best effort)
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

La release fork `v1.3.4` e' basata su `iu8lmc/Decodium-3.0-Codename-Raptor` e aggiunge hardening operativo specifico per macOS.

- Base upstream: Decodium v3.0 SE "Raptor"
- Versione fork: `v1.3.4`
- Bundle/eseguibile su macOS: `ft2.app` / `ft2`
- Licenza: GPLv3

### Cosa aggiunge questo fork

- Migrazione runtime stabile su macOS verso `ft2.app` (con fix su path/layout dei sottoprocessi).
- Miglioramenti di robustezza TX/PTT/audio in uso FT2 ripetuto.
- Persistenza piu affidabile di audio/radio e ripristino impostazioni su macOS.
- Preflight permesso microfono all'avvio per evitare popup tardivo durante l'uso.
- Strategia DT/NTP robusta (weak-sync + deadband + conferme + filtro sparse jump + hold mode).
- Path shared memory su macOS migrato a backend `mmap`; bootstrap sysctl via `.pkg` non piu' richiesto negli artifact release standard.
- Mitigazione freeze/hang in avvio spostando I/O pesante di startup fuori dal thread UI.
- Loader dati CTY/grid/satellite/comments irrobustiti con limiti di dimensione, guardie parser e recovery fallback.
- Baseline Raptor mantenuta con integrazioni fork ereditate dal lavoro 1.1.x.
- Funzionalita' Raptor upstream integrate:
  - Testo barrato B4 in Band Activity per stazioni gia' lavorate in banda.
  - Coda FIFO Auto CQ (max 20) con prosecuzione automatica a fine QSO.
  - Overlay waterfall con parentesi rosse sullo slot TX (FT2/FT8/FT4).
  - Aggiornamento automatico `cty.dat` all'avvio se mancante o piu vecchio di 30 giorni.
  - Aggiornamenti decoder FT2: `syncmin` adattivo (`0.90/0.85/0.80`), AP esteso su Tx3/Tx4, soglie deep-search rilassate, OSD potenziato vicino a `nfqso`.
- Rifiniture fork `v1.3.4` su UI/runtime:
  - Auto-selezione modalita' all'avvio basata su lista frequenze completa (fix mismatch FT8/FT2).
  - Controlli top responsivi con passaggio automatico a 2 righe su schermi piccoli.
  - Rendering barra progressi/secondi corretto nel tema chiaro.
- Hardening sicurezza/concorrenza fork `v1.3.4`:
  - Parser frame binari TCI con validazione completa header/payload prima dell'accesso (drop frame malformati).
  - Rimossi loop annidati pseudo-sync in `mysleep1..8` (eliminato il percorso `QEventLoop::exec()`).
  - Percorso TX `foxcom_.wave` irrobustito con snapshot protetti tra thread UI/audio.
  - Boundary audio TCI C++/Fortran irrobustito con clamp `kin` e scritture limitate.
  - Generazione TOTP allineata a sorgente tempo corretta NTP.
  - Migrazione `QRegExp` completata nei percorsi runtime/network critici (`mainwindow`, `wsprnet`).

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
./build-raptor-port/ft2.app/Contents/MacOS/ft2
```

### Quarantena macOS

Se macOS blocca l'avvio dell'app, eseguire:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

### Documentazione

- Note di rilascio (EN/IT): [RELEASE_NOTES_v1.3.4.md](RELEASE_NOTES_v1.3.4.md)
- Changelog (EN/IT): [CHANGELOG.md](CHANGELOG.md)
- Report analisi sicurezza e bug: [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
- Porting macOS (EN/IT): [doc/MACOS_PORTING_v1.2.0.md](doc/MACOS_PORTING_v1.2.0.md)
- Architettura DT/NTP (EN/IT): [doc/DT_NTP_ROBUST_SYNC_v1.2.0.md](doc/DT_NTP_ROBUST_SYNC_v1.2.0.md)
- Template release GitHub (EN/IT): [doc/GITHUB_RELEASE_BODY_v1.3.4.md](doc/GITHUB_RELEASE_BODY_v1.3.4.md)

### Target CI release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (sperimentale / best effort)
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
