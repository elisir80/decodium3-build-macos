# Changelog / Registro Modifiche

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
