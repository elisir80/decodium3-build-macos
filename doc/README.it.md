# Note di Documentazione (Italiano)

## Scopo

Note specifiche del fork macOS nel repository.

## Contesto release attuale

- Ultima release stabile: `v1.4.3`
- Target: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (sperimentale), Linux x86_64 AppImage

## Note build e runtime

### Output build

- `build/ft2.app/Contents/MacOS/ft2`
- eseguibili di supporto nello stesso bundle (`jt9`, `wsprd`)

### Memoria condivisa su macOS

- Il fork usa `SharedMemorySegment` con backend `mmap` su Darwin.
- Il flusso release non dipende da tuning `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Evidenze consolidate v1.4.3

- Hardening crash Linux FT2 Async L2:
  - limiti rigidi output Fortran async (`ndecodes/nout <= 100`);
  - parsing C++ righe async sicuro a lunghezza fissa;
  - reset esplicito buffer async/contatori su ciclo decode e toggle.
- Lock QSO attivo con Wait Features + AutoSeq irrigidito:
  - partner runtime (`m_hisCall`) usato come sorgente lock primaria;
  - lock attivo da `REPLYING` fino a `SIGNOFF`.
- L'hardening v1.4.2 resta incluso in v1.4.3:
  LotW POST + redirect stretti, token minimo bind remoto, clamp geometria Linux, visibilita' controlli FT2, ripristino finestre View, continuita' eventi TX dashboard remota.

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

### Avvio consigliato AppImage

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

### Comando quarantena Gatekeeper

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Riferimenti

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.4.3.md`
- `doc/GITHUB_RELEASE_BODY_v1.4.3.md`
- `doc/WEBAPP_SETUP_GUIDE.it.md`
- `doc/WEBAPP_SETUP_GUIDE.en-GB.md`
- `doc/WEBAPP_SETUP_GUIDE.es.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
