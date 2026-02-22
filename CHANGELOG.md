# Changelog

All notable changes for the Decodium 3 FT2 macOS fork are documented here.

## v1.0.7 - 2026-02-22

### English (UK)

- Updated main window title format to include fork attribution and fork release version.
- Added `FORK_RELEASE_VERSION` build parameter and wired release automation to pass the tag version to the app title.
- Cleaned macOS DMG root contents by removing legacy WSJT-X installer files and adding FT2-specific package notes.
- Added clearer Skip Tx1 discoverability (tooltips + status messages) to speed up reply sequencing.
- Kept Sequoia/Tahoe compatibility release flow on `macos-15`.

### Italiano

- Aggiornato il formato del titolo finestra principale con attribuzione fork e versione release del fork.
- Aggiunto il parametro build `FORK_RELEASE_VERSION` e collegata l'automazione release per passare il tag alla UI.
- Puliti i contenuti della root DMG macOS rimuovendo file legacy WSJT-X e aggiungendo note package specifiche FT2.
- Migliorata la visibilita' dello Skip Tx1 (tooltip + messaggi stato) per velocizzare la sequenza di risposta.
- Mantenuto il flusso release compatibile Sequoia/Tahoe su runner `macos-15`.

## v1.0.6 - 2026-02-22

### English (UK)

- Fixed startup fatal path: FT2 no longer aborts when a lingering `jt9`
  shared-memory segment is still reusable.
- Startup now reuses an existing valid segment and keeps a hard failure only
  when segment size is smaller than `sizeof(dec_data)`.
- Compatibility pipeline re-verified for Sequoia/Tahoe release builds.

### Italiano

- Corretto il percorso di errore fatale in avvio: FT2 non termina piu' quando
  un segmento condiviso `jt9` residuo e' ancora riusabile.
- L'avvio ora riusa un segmento valido esistente e mantiene un blocco fatale
  solo se la dimensione e' inferiore a `sizeof(dec_data)`.
- Pipeline di compatibilita' riverificata per build release Sequoia/Tahoe.

## v1.0.5 - 2026-02-22

### English (UK)

- Updated macOS signing verification flow in release packaging to avoid false
  CI failures on macOS 15 runners.
- Kept integrity checks for bundled Mach-O binaries while stabilising release
  generation.

### Italiano

- Aggiornato il flusso di verifica firma macOS nel packaging release per
  evitare falsi fallimenti CI su runner macOS 15.
- Mantenuti i controlli di integrita' dei binari Mach-O nel bundle,
  stabilizzando la generazione release.

## v1.0.4 - 2026-02-22

### English (UK)

- Added Sequoia-targeted release workflow (`macos-15`) to produce artifacts
  intended to run on both Sequoia and Tahoe.
- Tightened bundle dependency/deployment checks and reduced CI breakage by
  disabling docs/manpages in release CI configure.

### Italiano

- Aggiunta workflow release target Sequoia (`macos-15`) per produrre artifact
  pensati per funzionare sia su Sequoia sia su Tahoe.
- Rafforzati i controlli su dipendenze/deployment del bundle e ridotti i
  problemi CI disabilitando docs/manpages nella configurazione release CI.

## v1.0.3 - 2026-02-21

### English (UK)

- Added macOS `.pkg` installer generation in release process.
- Added post-install sysctl setup for FT2/JTDX shared-memory coexistence.
- Added bilingual Gatekeeper instructions for blocked pkg launch.

### Italiano

- Aggiunta generazione installer macOS `.pkg` nel processo di release.
- Aggiunta configurazione sysctl post-install per coesistenza FT2/JTDX su
  memoria condivisa.
- Aggiunte istruzioni Gatekeeper bilingue per avvio pkg bloccato.

## v1.0.2 - 2026-02-21

### English (UK)

- Consolidation release around GA baseline tag alignment for the fork.

### Italiano

- Release di consolidamento per allineamento ai tag baseline GA del fork.

## v1.0.1 - 2026-02-21

### English (UK)

- Added bilingual repository documentation (`README.en-GB.md`, `README.it.md`,
  `doc/README.en-GB.md`, `doc/README.it.md`).

### Italiano

- Aggiunta documentazione repository bilingue (`README.en-GB.md`,
  `README.it.md`, `doc/README.en-GB.md`, `doc/README.it.md`).

## v1.0 - 2026-02-21

### English (UK)

- Initial macOS fork release baseline.

### Italiano

- Baseline iniziale della release del fork macOS.
