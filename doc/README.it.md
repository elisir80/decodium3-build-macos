# Note di Documentazione (Italiano)

## Scopo

Note specifiche del fork macOS nel repository.

## Contesto release attuale

- Ultima release stabile: `v1.3.0`
- Target: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel

## Note build e runtime

### Output build

- `build/ft2.app/Contents/MacOS/ft2`
- eseguibili di supporto nello stesso bundle (`jt9`, `wsprd`)

### Memoria condivisa su macOS

- Il fork usa `SharedMemorySegment` con backend `mmap` su Darwin.
- Il flusso release non dipende piu' da tuning `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Artifact release

- `decodium3-ft2-<version>-<asset-suffix>.dmg`
- `decodium3-ft2-<version>-<asset-suffix>.zip`
- `decodium3-ft2-<version>-<asset-suffix>-sha256.txt`

### Comando quarantena Gatekeeper

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Riferimenti

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.3.0.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.0.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
