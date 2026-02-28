# Note di Documentazione (Italiano)

## Scopo

Note specifiche del fork macOS nel repository.

## Contesto release attuale

- Ultima release stabile: `v1.3.3`
- Target: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Linux x86_64 AppImage

## Note build e runtime

### Output build

- `build/ft2.app/Contents/MacOS/ft2`
- eseguibili di supporto nello stesso bundle (`jt9`, `wsprd`)

### Memoria condivisa su macOS

- Il fork usa `SharedMemorySegment` con backend `mmap` su Darwin.
- Il flusso release non dipende piu' da tuning `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Hardening I/O startup e aggiornamenti UI/runtime (v1.3.3)

- Le letture file pesanti in avvio sono state spostate fuori dal thread UI per evitare hang.
- `CTY.DAT`, `grid.dat`, `sat.dat`, `comments.txt`, `wsjtx.log` e file correlati ora hanno guardie su dimensione e parsing.

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
- `RELEASE_NOTES_v1.3.3.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.3.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
