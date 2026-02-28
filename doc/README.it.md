# Note di Documentazione (Italiano)

## Scopo

Note specifiche del fork macOS nel repository.

## Contesto release attuale

- Ultima release stabile: `v1.3.4`
- Target: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (sperimentale), Linux x86_64 AppImage

## Note build e runtime

### Output build

- `build/ft2.app/Contents/MacOS/ft2`
- eseguibili di supporto nello stesso bundle (`jt9`, `wsprd`)

### Memoria condivisa su macOS

- Il fork usa `SharedMemorySegment` con backend `mmap` su Darwin.
- Il flusso release non dipende piu' da tuning `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Hardening sicurezza/concorrenza e aggiornamenti UI/runtime (v1.3.4)

- Parser frame binari TCI con validazione dimensione header/payload prima dell'accesso.
- Attese pseudo-sync TCI senza loop annidati `QEventLoop::exec()`.
- Percorso TX `foxcom_.wave` con snapshot protetti tra thread UI/audio.
- Boundary audio TCI con clamp `kin` e scritture buffer limitate lato C++/Fortran.
- Gestione audio macOS migliorata su comportamento Sequoia (stop/underrun).
- TOTP allineato a sorgente tempo corretta NTP.

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
- `RELEASE_NOTES_v1.3.4.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.4.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
