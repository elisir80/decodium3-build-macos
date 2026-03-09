# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.4.2 (Espanol)

Para la version completa bilingue (English + Italiano), ver [README.md](README.md).

## Resumen (v1.4.2)

Esta version cubre el ciclo `v1.4.1 -> v1.4.2`:

- Hardening de seguridad LotW:
  - peticiones LotW con credenciales movidas de GET URL a POST HTTPS,
  - eliminado logging tipo URL con credenciales,
  - politica estricta de redirect para peticiones con credenciales (HTTPS + host esperado).
- Hardening web remota:
  - bind LAN/WAN rechazado con token menor de 12 caracteres,
  - aviso explicito de trafico HTTP/WS en claro cuando el bind se expone.
- Fixes de estabilidad Linux:
  - dialogo de ajustes ajustado a la geometria de pantalla (botones siempre accesibles),
  - decode async en thread pool dedicado con stack controlado + guardas anti-solapamiento.
- Consistencia de controles FT2:
  - Async L2 ON por defecto al entrar en FT2 y OFF automatico fuera de FT2,
  - `Bloquear Freq Tx` y `Tx par/1°` ocultos (y forzados OFF) en FT2.
- Restauracion de ventanas de herramientas:
  - acciones `View -> Ionospheric Forecast` y `View -> DX Cluster` restauradas.
- Dashboard web RX/TX:
  - eventos TX preservados en refresh y primera transicion TX mostrada correctamente.
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

- [RELEASE_NOTES_v1.4.2.md](RELEASE_NOTES_v1.4.2.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.2.md](doc/GITHUB_RELEASE_BODY_v1.4.2.md)
- [doc/README.es.md](doc/README.es.md)
- [doc/WEBAPP_SETUP_GUIDE.es.md](doc/WEBAPP_SETUP_GUIDE.es.md)
- [doc/WEBAPP_SETUP_GUIDE.en-GB.md](doc/WEBAPP_SETUP_GUIDE.en-GB.md)
- [doc/WEBAPP_SETUP_GUIDE.it.md](doc/WEBAPP_SETUP_GUIDE.it.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
