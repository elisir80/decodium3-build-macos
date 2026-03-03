# Notas de Documentacion (Espanol)

## Alcance

Notas especificas del fork macOS dentro de este repositorio.

## Contexto de release actual

- Ultima release estable: `v1.3.7`
- Objetivos: macOS Tahoe ARM64, Sequoia ARM64, Sequoia Intel, Monterey Intel (experimental), Linux x86_64 AppImage

## Notas de build y runtime

### Salida de compilacion

- `build/ft2.app/Contents/MacOS/ft2`
- ejecutables auxiliares en el mismo bundle (`jt9`, `wsprd`)

### Memoria compartida en macOS

- Este fork usa `SharedMemorySegment` con backend `mmap` en Darwin.
- El flujo de release ya no depende de ajustes `sysctl` System V (`kern.sysv.shmmax/shmall`).

### Actualizaciones UI/runtime y robustez (v1.3.7)

- Seleccion de contactos desde mapa con propagacion de call/grid al panel principal.
- Nueva opcion de configuracion para iniciar TX con click simple en mapa.
- Nueva ventana de pronostico ionosferico (HamQSL) con refresco periodico.
- Nueva ventana DX Cluster con filtro por modo y contexto de banda.
- Renderizado dia/noche del mapa mejorado y limpieza de lineas stale de QSO.
- Mejoras de layout para pantallas pequenas (modo compacto/2 filas).
- Fiabilidad de decode al arranque mejorada por ajuste del timestamp de secuencia.
- Registro explicito de metatype para `ModulatorState` en senales cross-thread.
- UI por defecto `Fusion` para consistencia visual en macOS.
- Cadena `Using:` de PSKReporter limpia (sin sufijo legacy `mod by IU8LMC...`).

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

### Comando cuarentena Gatekeeper

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Referencias

- `CHANGELOG.md`
- `RELEASE_NOTES_v1.3.7.md`
- `doc/GITHUB_RELEASE_BODY_v1.3.7.md`
- `doc/SECURITY_BUG_ANALYSIS_REPORT.md`
