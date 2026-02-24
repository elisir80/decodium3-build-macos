# Changelog

All notable changes for the Decodium 3 FT2 macOS fork are documented here.

## v1.1.0 - 2026-02-24

### English (UK)

- Added automatic audio output rebind recovery (`AudioRebind`) when runtime output errors occur.
- Added throttled auto-recovery attempts and improved output-device selection fallback (preferred/configured/default).
- Changed output underrun handling to recoverable status (no immediate fatal invalidation of the selected output device).
- Improved UDP/network interface handling:
  selected interfaces remain visible in Settings even when temporarily unavailable;
  loopback/multicast state details are shown in tooltips;
  stale selected interfaces are preserved as disabled entries instead of disappearing.
- Hardened internal NTP client behavior:
  proper sync-cycle resets, stale DNS lookup filtering, deduplicated query targets,
  NTPv4 transmit timestamp handling, echoed-originate validation, improved failure signaling,
  and clearer HTTP fallback state transitions.
- Added NTP status-bar enhancements:
  display now includes offset plus last sync age,
  periodic age refresh,
  clearer OFF/no-sync/waiting/synced states and richer tooltips.
- Added configurable DT clock-compensation limits for remote operation:
  dedicated checkable block in `Settings -> Advanced`,
  separate clamp values for NTP-synced and unsynced states,
  persisted settings and immediate runtime reload after closing Settings.
- Updated release/build baseline to fork tag `v1.1.0`.
- Release target remains dual architecture:
  Apple Silicon (Sequoia/Tahoe) and Intel (Sequoia).
- macOS launch fallback command to keep in release notes/troubleshooting:
  `xattr -r -d com.apple.quarantine /Applications/ft2.app`

### Italiano

- Aggiunto recupero automatico auto-rebind dell'uscita audio (`AudioRebind`) quando si verificano errori runtime di output.
- Aggiunti tentativi di recupero con throttling e migliorato fallback selezione device (preferito/configurato/default).
- Modificata la gestione underrun output come condizione recuperabile (senza invalidazione fatal immediata del device selezionato).
- Migliorata la gestione UDP/interfacce di rete:
  le interfacce selezionate restano visibili nelle Impostazioni anche se temporaneamente non disponibili;
  i dettagli loopback/multicast sono mostrati nei tooltip;
  le interfacce selezionate ma non rilevate vengono preservate come voci disabilitate invece di sparire.
- Rafforzato il comportamento del client NTP interno:
  reset corretti del ciclo sync, filtro lookup DNS stale, deduplicazione target query,
  gestione timestamp NTPv4, validazione originate echoed, segnalazione errori migliorata
  e transizioni stato fallback HTTP piu' coerenti.
- Aggiunti miglioramenti alla status bar NTP:
  la visualizzazione ora include offset + eta' ultima sincronizzazione,
  refresh periodico dell'eta',
  stati OFF/no-sync/in attesa/synced piu' chiari con tooltip piu' ricchi.
- Aggiunti limiti di compensazione clock DT configurabili per operazioni remote:
  blocco dedicato e checkable in `Impostazioni -> Avanzate`,
  valori clamp separati per stato NTP synced/unsynced,
  persistenza impostazioni e ricarica runtime immediata dopo chiusura Impostazioni.
- Aggiornata la baseline release/build al tag fork `v1.1.0`.
- Target release confermato dual architecture:
  Apple Silicon (Sequoia/Tahoe) e Intel (Sequoia).
- Comando fallback macOS da mantenere sempre in note release/troubleshooting:
  `xattr -r -d com.apple.quarantine /Applications/ft2.app`

## v1.0.9 - 2026-02-23

### English (UK)

- Added a third integrated panel in the main UI: `Live World Map`.
- Added world texture background + geographic overlay + day/night rendering.
- Added active-area auto-zoom with smooth viewport motion.
- Implemented directional path roles and legend:
  `IN->ME` (incoming to operator), `ME->DX` (outgoing from operator), `BAND` (station seen in band only).
- Corrected directed decode semantics (`CALL_TO CALL_FROM GRID`) so locator ownership maps to the right callsign.
- Fixed Maidenhead 6-character positioning (`JM75FV` etc.) and added robust call-to-grid fallback lookup (`CALL3.TXT`, AD1CCty).
- During TX, map now displays only the active `ME->DX` path with slowed animation timing based on mode (FT2/FT4/FT8).
- Added post-TX incoming-callers queue rendering window and removed stale outgoing arrows after TX ends.
- Reduced label clutter: smaller label font and capped visible labels for readability.
- Clarified bottom-left counters: `active paths` now excludes `BAND` markers, shown separately as `in band`.
- Updated release baseline/tag/version references to `v1.0.9`.
- Kept release pipeline compatible for macOS Sequoia/Tahoe on Apple Silicon and Sequoia on Intel (`x86_64`).

### Italiano

- Aggiunto il terzo pannello integrato nella UI principale: `Live World Map`.
- Aggiunto sfondo mappa reale + overlay geografico + rendering giorno/notte.
- Introdotto zoom automatico area attiva con movimento viewport fluido.
- Implementati ruoli direzionali e legenda:
  `IN->ME` (in ingresso verso operatore), `ME->DX` (in uscita dall'operatore), `BAND` (stazione solo presente in banda).
- Corrette le semantiche dei messaggi diretti (`CALL_TO CALL_FROM GRID`) per associare il locator al nominativo corretto.
- Corretto il posizionamento Maidenhead a 6 caratteri (`JM75FV` ecc.) e aggiunto fallback robusto call->grid (`CALL3.TXT`, AD1CCty).
- Durante la TX, la mappa mostra solo il percorso attivo `ME->DX` con animazione rallentata in base al modo (FT2/FT4/FT8).
- Aggiunta finestra post-TX per mostrare la coda chiamanti in ingresso ed eliminazione frecce outgoing residue a fine TX.
- Ridotta la congestione etichette: font piu' piccolo e limite etichette visibili.
- Chiariti i contatori in basso a sinistra: `active paths` esclude ora i marker `BAND`, mostrati separatamente in `in band`.
- Aggiornata la baseline release/tag/versione a `v1.0.9`.
- Mantenuta compatibilita' pipeline release per macOS Sequoia/Tahoe Apple Silicon e Sequoia Intel (`x86_64`).

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
