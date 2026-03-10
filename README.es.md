# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.4.3 (Espanol)

Para la version completa bilingue (English + Italiano), ver [README.md](README.md).

## Resumen (v1.4.3)

Esta version cubre el ciclo `v1.4.2 -> v1.4.3`:

- Hardening del crash Linux FT2 Async L2:
  - limites estrictos de salida Fortran (`ndecodes/nout <= 100`) en decode triggered,
  - parsing de filas async en C++ ahora seguro con longitud fija,
  - reset explicito de buffers async y contadores por ciclo decode/toggle.
- Proteccion de QSO activo con Wait Features + AutoSeq:
  - el lock de pareja prioriza la pareja runtime (`m_hisCall`),
  - lock activo antes (`REPLYING` hasta `SIGNOFF`) cuando Wait Features + AutoSeq estan habilitados.
- Comportamiento runtime:
  - eliminados casos de texto basura y over-read en primer decode con Async L2 en Linux.
- Alineacion release/documentacion:
  - metadatos fork y documentacion actualizados a `v1.4.3`.
- Se mantiene todo el hardening de `v1.4.2` (LotW POST + redirect policy, token minimo para bind remoto, reglas de visibilidad FT2, restauracion de ventanas de herramientas/mapa, safeguards de geometria Linux).
- `.pkg` no necesario: releases solo DMG/ZIP/SHA256 (macOS) y AppImage/SHA256 (Linux).

## Objetivos de release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (12.x, experimental/best-effort)
- Linux x86_64 AppImage

## Hamlib en builds de release

- En macOS los workflows ejecutan `brew update` + `brew upgrade hamlib` antes de compilar.
- En Linux los workflows compilan Hamlib desde la ultima release oficial de GitHub e instalan en `/usr/local` antes de compilar `ft2`.
- Los logs CI muestran siempre la version efectiva usada (`rigctl --version`, `pkg-config --modversion hamlib`).

## Requisitos minimos Linux

- Arquitectura: `x86_64` (64 bits)
- CPU: dual-core 2.0 GHz o superior
- RAM: 4 GB minimo (8 GB recomendado)
- Disco: al menos 500 MB libres (AppImage + logs + configuracion)
- Runtime:
  - Linux con `glibc >= 2.35`
  - `libfuse2` / FUSE2 para ejecutar AppImage
  - audio ALSA, PulseAudio o PipeWire
- Integracion de estacion: hardware CAT/audio segun configuracion de radio

## Recomendacion de arranque AppImage en Linux

Para evitar problemas por el sistema de archivos de solo lectura de AppImage:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Comando macOS (cuarentena)

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentacion

- [RELEASE_NOTES_v1.4.3.md](RELEASE_NOTES_v1.4.3.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.3.md](doc/GITHUB_RELEASE_BODY_v1.4.3.md)
- [doc/README.es.md](doc/README.es.md)
- [doc/WEBAPP_SETUP_GUIDE.es.md](doc/WEBAPP_SETUP_GUIDE.es.md)
- [doc/WEBAPP_SETUP_GUIDE.en-GB.md](doc/WEBAPP_SETUP_GUIDE.en-GB.md)
- [doc/WEBAPP_SETUP_GUIDE.it.md](doc/WEBAPP_SETUP_GUIDE.it.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
