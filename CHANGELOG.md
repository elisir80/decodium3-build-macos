# Changelog / Registro Modifiche

## [1.3.3] - 2026-02-28

### English

Release focused on upstream feature import from the original Raptor repository plus fork UI/runtime refinements.

#### Changed

- Imported upstream Raptor feature set:
  - B4 strikethrough in Band Activity for worked-on-band stations.
  - Auto CQ caller FIFO queue (max 20) with automatic next-caller processing after QSO completion.
  - TX slot red bracket overlay (`[ ]`) on waterfall for FT2/FT8/FT4.
  - Automatic `cty.dat` refresh/download at startup when missing or older than 30 days.
  - FT2 decoder tuning updates (`syncmin` adaptive profile, extended AP types for Tx3/Tx4, deep-search threshold relaxations).
- Added responsive top-controls layout for small displays with automatic 2-row split.
- Updated release/build metadata to installer build tag `2602281900`.
- Release artifacts remain DMG/ZIP/SHA256 for macOS and AppImage/SHA256 for Linux (no `.pkg`), with added best-effort Intel Monterey target in GitHub workflows.

#### Fixed

- Startup mode/frequency mismatch on CAT initialization by using full-list mode auto-alignment.
- Light-theme progress/seconds bar visibility in status area.
- Small-screen control overlap/truncation in top action row.

### Italiano

Release focalizzata su import feature upstream dal repository Raptor originale e rifiniture UI/runtime del fork.

#### Modificato

- Importato il set feature upstream Raptor:
  - Testo barrato B4 in Band Activity per stazioni gia' lavorate in banda.
  - Coda FIFO Auto CQ chiamanti (max 20) con passaggio automatico al prossimo chiamante a fine QSO.
  - Overlay waterfall con parentesi rosse (`[ ]`) sullo slot TX per FT2/FT8/FT4.
  - Refresh/download automatico `cty.dat` all'avvio se mancante o piu' vecchio di 30 giorni.
  - Tuning decoder FT2 (`syncmin` adattivo, AP esteso su Tx3/Tx4, soglie deep-search rilassate).
- Aggiunto layout controlli top responsivo per schermi piccoli con split automatico su 2 righe.
- Aggiornati metadati build/release al build tag installer `2602281900`.
- Artifact release invariati: DMG/ZIP/SHA256 su macOS e AppImage/SHA256 su Linux (nessun `.pkg`), con target Intel Monterey best-effort aggiunto nei workflow GitHub.

#### Corretto

- Mismatch modalita'/frequenza all'avvio con CAT tramite auto-allineamento modalita' su lista completa frequenze.
- Visibilita' barra progressi/secondi nel tema chiaro in status bar.
- Sovrapposizioni/troncamenti controlli su display piccoli nella riga azioni superiore.

## [1.3.2] - 2026-02-28

### English

Patch release focused on startup hang mitigation and startup data-file hardening.

#### Changed

- Startup file loads now run asynchronously for `wsjtx.log`, `ignore.list`, `ALLCALL7.TXT`, and old-audio cleanup tasks.
- `WorkedBefore` reload flow now avoids overlapping reload races.
- Release/documentation baseline updated to `v1.3.2` (EN/IT) for macOS + Linux AppImage targets.
- macOS release flow remains DMG/ZIP/SHA256 (no `.pkg` required after shared-memory mmap migration).

#### Fixed

- Reduced startup UI hangs/beachball risks by moving expensive file I/O off the main thread.
- Hardened `CTY.DAT` loading with size guards, parser validation, fallback recovery, and safer reload behavior.
- Added defensive bounds checks for `grid.dat`, `sat.dat`, and `comments.txt` startup parsing.

### Italiano

Patch release focalizzata su mitigazione hang in avvio e hardening dei file dati caricati allo startup.

#### Modificato

- I caricamenti file in avvio ora sono asincroni per `wsjtx.log`, `ignore.list`, `ALLCALL7.TXT` e cleanup dei vecchi file audio.
- Flusso di reload `WorkedBefore` aggiornato per evitare race da reload sovrapposti.
- Baseline release/documentazione aggiornata a `v1.3.2` (EN/IT) per target macOS + Linux AppImage.
- Il flusso release macOS resta DMG/ZIP/SHA256 (nessun `.pkg` richiesto dopo migrazione shared memory a mmap).

#### Corretto

- Ridotto il rischio di hang/beachball in avvio spostando I/O pesante fuori dal main thread UI.
- Loader `CTY.DAT` irrobustito con limiti dimensione, validazione parser, recovery fallback e reload piu' sicuro.
- Aggiunte guardie difensive su parsing startup di `grid.dat`, `sat.dat` e `comments.txt`.

## [1.3.1] - 2026-02-28

### English

Patch release focused on version alignment, Linux CI/release completion, and cross-platform packaging consistency.

#### Changed

- Program title release identifier now sourced from `FORK_RELEASE_VERSION` instead of hardcoded legacy text.
- Release documentation updated to `v1.3.1` in English and Italian.
- Added Linux x86_64 AppImage release flow alongside existing macOS matrices.

#### Fixed

- Linux build compatibility with Hamlib variants lacking `rig_get_conf2` (fallback to `rig_get_conf`).
- Linux CI link issues by adding missing `libudev` development/runtime dependencies.
- Linux CI verify/package steps now target `ft2` executable (not legacy `wsjtx` path).
- Tahoe macOS release compatibility target aligned to `26.0` for bundled dependency checks.

### Italiano

Patch release focalizzata su allineamento versione, completamento CI/release Linux e coerenza packaging multipiattaforma.

#### Modificato

- Identificativo release nel titolo programma ora letto da `FORK_RELEASE_VERSION` invece che hardcoded legacy.
- Documentazione release aggiornata a `v1.3.1` in inglese e italiano.
- Aggiunto flusso release Linux x86_64 AppImage insieme alle matrici macOS esistenti.

#### Corretto

- Compatibilita' build Linux con varianti Hamlib senza `rig_get_conf2` (fallback a `rig_get_conf`).
- Problemi di link Linux CI risolti aggiungendo dipendenze `libudev` development/runtime.
- Step verify/package Linux CI ora puntano all'eseguibile `ft2` (non al path legacy `wsjtx`).
- Target compatibilita' release macOS Tahoe allineato a `26.0` per i controlli dipendenze bundle.

## [1.3.0] - 2026-02-28

### English

Release focused on security hardening, macOS shared-memory stability, CAT resilience,
and DT/NTP behavior tuning.

#### Changed

- macOS shared memory migrated to `SharedMemorySegment` with Darwin `mmap` backend.
- Release flow updated to generate platform-specific DMG/ZIP/SHA256 assets:
  - Tahoe arm64
  - Sequoia arm64
  - Sequoia x86_64
- `.pkg` generation removed from standard release path (no longer required for shm sysctl bootstrap).
- FT2/FT4/FT8 mode-specific NTP and DT sampling tuning refined.

#### Fixed

- CAT reconnect instability when external bridge/logger state changed at runtime.
- Startup mode mismatch when rig frequency implied a different digital mode.
- Multiple NTP edge cases (sample quality filtering, sparse-set handling, fallback coherence).
- DT status presentation now aligned with effective timing context.

### Italiano

Release focalizzata su hardening sicurezza, stabilita' shared memory su macOS, resilienza CAT
e tuning del comportamento DT/NTP.

#### Modificato

- Memoria condivisa macOS migrata a `SharedMemorySegment` con backend Darwin `mmap`.
- Flusso release aggiornato con asset DMG/ZIP/SHA256 specifici per piattaforma:
  - Tahoe arm64
  - Sequoia arm64
  - Sequoia x86_64
- Generazione `.pkg` rimossa dal percorso release standard (non piu' necessaria per bootstrap sysctl shm).
- Rifinito il tuning NTP e campionamento DT per FT2/FT4/FT8.

#### Corretto

- Instabilita' CAT in riconnessione quando lo stato del bridge/logger esterno cambiava a runtime.
- Mismatch modalita' all'avvio quando la frequenza radio implicava un modo digitale differente.
- Diversi edge case NTP (filtro qualita' campioni, gestione set server sparsi, coerenza fallback).
- Presentazione DT in status bar allineata al contesto temporale effettivo.

## [1.2.1] - 2026-02-27

### English

Maintenance release focused on UI cleanliness and map accuracy.

#### Changed

- Removed soundcard drift display/alternation in status bar and Time Sync panel; drift measurement disabled in Detector.
- Shortened world map contact lifetime to 2 minutes to prevent stale call popups.
- Program title updated to fork `v1.2.1`.

#### Fixed

- Prevented SC drift label from reappearing via legacy code path.

### Italiano

Release di manutenzione focalizzata su pulizia UI e correttezza mappa.

#### Modificato

- Rimossa la visualizzazione/alternanza del drift scheda audio in status bar e pannello Time Sync; misura di drift disabilitata nel Detector.
- Durata contatti mappa ridotta a 2 minuti per evitare chiamate fantasma.
- Titolo programma aggiornato alla fork `v1.2.1`.

#### Corretto

- Evitata la ricomparsa dell’etichetta SC drift tramite codice legacy.

## [1.2.0] - 2026-02-26

### English

Fork release based on Decodium v3.0 SE Raptor with macOS-focused runtime stabilization and robust DT/NTP timing control.

#### Added

- Fork release identity `v1.2.0` in title/release metadata.
- `tx-support.log` for TX/PTT/audio troubleshooting.
- Startup microphone preflight on macOS.
- NTP robust sync controls:
  - weak-sync deadband + confirmations,
  - cluster/coherence filtering,
  - sparse-server jump confirmation,
  - lock hold behavior during temporary outages.

#### Changed

- App namespace and bundle path standardized to `ft2.app` / `ft2`.
- macOS subprocess layout fixed (`jt9` colocated in bundle runtime path).
- TX start/stop sequencing hardened for CAT/PTT lag and races.
- Audio settings restore made more defensive for channels/devices.
- FT2 band defaults auto-merged for legacy profiles missing FT2 entries.
- Graph windows branding aligned to Decodium.

#### Fixed

- `execve` failures caused by legacy `wsjtx.app` assumptions.
- Intermittent "PTT active but no modulation" cases in repeated FT2 cycles.
- Late microphone popup appearing during active operation.
- Invalid persisted channel states causing silent TX/RX.

### Italiano

Release fork basata su Decodium v3.0 SE Raptor con stabilizzazione runtime su macOS e controllo temporale DT/NTP robusto.

#### Aggiunto

- Identita release fork `v1.2.0` in titolo/metadati release.
- `tx-support.log` per diagnostica TX/PTT/audio.
- Preflight permesso microfono all'avvio su macOS.
- Controlli sync NTP robusti:
  - deadband weak-sync + conferme,
  - filtro cluster/coerenza,
  - conferma salti con pochi server,
  - comportamento hold del lock su outage temporanei.

#### Modificato

- Namespace app e path bundle standardizzati su `ft2.app` / `ft2`.
- Layout sottoprocesso macOS corretto (`jt9` co-locato nel runtime bundle).
- Sequenza start/stop TX resa piu robusta contro lag/race CAT/PTT.
- Ripristino impostazioni audio reso piu difensivo per canali/device.
- Default banda FT2 auto-merge per profili legacy senza voci FT2.
- Branding finestre grafico allineato a Decodium.

#### Corretto

- Errori `execve` causati da assunzioni legacy su `wsjtx.app`.
- Casi intermittenti "PTT attivo ma senza modulazione" nei cicli FT2 ripetuti.
- Popup microfono tardivo durante l'operativita.
- Stati canale persistiti non validi che causavano TX/RX muta.

### CI/Build

- Release matrix macOS su:
  - Apple Silicon Tahoe
  - Apple Silicon Sequoia
  - Apple Intel Sequoia
- Artifact naming allineato a `v1.2.0`.
