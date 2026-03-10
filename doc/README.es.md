# Notas de Documentacion (Espanol)

## Alcance

Notas especificas del fork macOS dentro de este repositorio.

## Contexto de release actual

- Ultima release estable: `v1.4.3`
- Objetivos: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (experimental), Linux x86_64 AppImage

## Notas de build y runtime

### Salida de compilacion

- `build/ft2.app/Contents/MacOS/ft2`
- ejecutables auxiliares en el mismo bundle (`jt9`, `wsprd`)

### Memoria compartida en macOS

- Este fork usa `SharedMemorySegment` con backend `mmap` en Darwin.
- El flujo de release no depende de ajustes `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Resumen consolidado v1.4.3

- Hardening del crash Linux FT2 Async L2:
  - limites estrictos de filas Fortran async (`ndecodes/nout <= 100`);
  - parsing C++ de filas async seguro con longitud fija;
  - reset explicito de buffers/counters async por ciclo decode y toggle.
- Lock de QSO activo con Wait Features + AutoSeq reforzado:
  - pareja runtime (`m_hisCall`) ahora es fuente primaria de lock;
  - lock activo desde `REPLYING` hasta `SIGNOFF`.
- El hardening v1.4.2 sigue incluido en v1.4.3:
  LotW POST + redirects estrictos, token minimo para bind remoto, clamp de geometria Linux, visibilidad de controles FT2, restauracion de ventanas View y continuidad de eventos TX remotos.

### Artefactos de release

- `decodium3-ft2-<version>-<asset-suffix>.dmg`
- `decodium3-ft2-<version>-<asset-suffix>.zip`
- `decodium3-ft2-<version>-<asset-suffix>-sha256.txt`
- `decodium3-ft2-<version>-linux-x86_64.AppImage`
- `decodium3-ft2-<version>-linux-x86_64.AppImage.sha256.txt`

### Requisitos minimos Linux

- Arquitectura: `x86_64`
- CPU: dual-core 2.0 GHz o superior
- RAM: 4 GB minimo
- Runtime: `glibc >= 2.35`, `libfuse2`/FUSE2, ALSA/PulseAudio/PipeWire

### Recomendacion AppImage

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

### Comando cuarentena Gatekeeper

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Referencias

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.4.3.md`
- `doc/GITHUB_RELEASE_BODY_v1.4.3.md`
- `doc/WEBAPP_SETUP_GUIDE.es.md`
- `doc/WEBAPP_SETUP_GUIDE.en-GB.md`
- `doc/WEBAPP_SETUP_GUIDE.it.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
