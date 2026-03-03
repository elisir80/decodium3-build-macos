# Decodium v3.0 SE "Raptor" - Fork 9H1SR v1.3.7 (Espanol)

Para la version completa bilingue (English + Italiano), ver [README.md](README.md).

## Resumen (v1.3.7)

Esta version del fork incluye, respecto a `v1.3.6`:

- seleccion de contactos directamente desde el mapamundi con resaltado visual y carga de indicativo/cuadricula DX;
- nueva opcion de configuracion `Map: single click starts Tx` para elegir la logica click simple/doble en el mapa;
- persistencia del estado `View -> World Map` entre reinicios;
- nueva ventana `Ionospheric Forecast` (datos HamQSL + imagen solar, refresco periodico);
- nueva ventana `DX Cluster` (spots en vivo con filtro por modo y banda actual);
- renderizado dia/noche del mapa mejorado y limpieza de lineas antiguas al terminar QSO;
- mejora del layout de controles superiores en modo compacto/2 filas para pantallas pequenas;
- correccion de sincronizacion de decode al arranque (timestamp de secuencia capturado antes del decode);
- mejora de fiabilidad de senales Qt entre hilos para `ModulatorState` (metatype registrado);
- estilo visual por defecto cambiado a `Fusion` para mayor consistencia en macOS;
- eliminada la fuente hardcoded del sufijo legacy de revision: en PSKReporter `Using:` ya no aparece `mod by IU8LMC...`.

## Objetivos de release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (12.x, experimental/best-effort)
- Linux x86_64 AppImage

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

## Comando macOS (cuarentena)

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Documentacion

- [RELEASE_NOTES_v1.3.7.md](RELEASE_NOTES_v1.3.7.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.3.7.md](doc/GITHUB_RELEASE_BODY_v1.3.7.md)
- [doc/README.es.md](doc/README.es.md)
- [doc/SECURITY_BUG_ANALYSIS_REPORT.md](doc/SECURITY_BUG_ANALYSIS_REPORT.md)
