# Note di Documentazione (Italiano)

## Scopo

Note specifiche del fork macOS nel repository.

## Contesto release attuale

- Ultima release stabile: `v1.3.7`
- Target: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (sperimentale), Linux x86_64 AppImage

## Note build e runtime

### Output build

- `build/ft2.app/Contents/MacOS/ft2`
- eseguibili di supporto nello stesso bundle (`jt9`, `wsprd`)

### Memoria condivisa su macOS

- Il fork usa `SharedMemorySegment` con backend `mmap` su Darwin.
- Il flusso release non dipende piu' da tuning `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Hardening sicurezza/concorrenza e aggiornamenti UI/runtime (v1.3.7)

- Aggiunta gestione click contatti mappa con highlight marker e trasferimento DX call/grid.
- Aggiunta opzione configurabile click mappa (`Map: single click starts Tx`).
- Aggiunta persistenza stato visibilita' `View -> World Map`.
- Aggiunte nuove finestre strumenti: `Ionospheric Forecast` e `DX Cluster`.
- Migliorato rendering giorno/notte mappa e logica pulizia path a fine QSO.
- Migliorato comportamento controlli top in modalita' compatta/2 righe su display piccoli.
- Timestamp sequence-start decode ora acquisito prima dell'avvio decode per evitare disallineamenti in startup.
- Registrazione esplicita metatype Qt per `ModulatorState` per delivery cross-thread affidabile.
- Stile Qt predefinito impostato a `Fusion` per rendering macOS coerente.
- Rimossa sorgente hardcoded del suffisso revision legacy che contaminava `Using:` su PSKReporter.

### Artifact release

- `decodium3-ft2-<version>-<asset-suffix>.dmg`
- `decodium3-ft2-<version>-<asset-suffix>.zip`
- `decodium3-ft2-<version>-<asset-suffix>-sha256.txt`
- `decodium3-ft2-<version>-linux-x86_64.AppImage`
- `decodium3-ft2-<version>-linux-x86_64.AppImage.sha256.txt`

### Requisiti minimi Linux

- Architettura: `x86_64`
- CPU: dual-core 2.0 GHz o superiore
- RAM: minimo 4 GB
- Runtime: `glibc >= 2.35`, `libfuse2`/FUSE2, ALSA/PulseAudio/PipeWire

### Comando quarantena Gatekeeper

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Riferimenti

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.3.7.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.7.md`
- `doc/README.es.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
