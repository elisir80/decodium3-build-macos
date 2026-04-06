# Decodium (Fork macOS/Linux) - 1.6.1

- Release estable actual: `1.6.1`
- Ciclo de actualizacion: `1.6.0 -> 1.6.1`

## Cambios en 1.6.1 (`1.6.0 -> 1.6.1`)

- completada la migracion nativa C++ mantenida del runtime JT legacy activo, cubriendo los caminos decode JT4, JT9 y JT65.
- promovidos a implementaciones nativas Fortran-free los caminos runtime activos Q65 y WSPR y completada la migracion del runtime/tool path Echo a C++ nativo.
- eliminado de la superficie app/runtime mantenida el naming legacy ABI restante del camino activo, incluido el historico naming FFT `four2a`.
- limpiadas fuentes Fortran obsoletas y ficheros de compatibilidad de `lib/`, `qmap/libqmap/`, `map65/libm65/` y del viejo camino de herramientas Echo.
- corregidas regresiones Linux de build/startup en `mainwindow.cpp`, en la inicializacion diferida de clientes de red, en el manejo `QSocketNotifier`, en el teardown del logging Qt y en el enlace GNU ld de targets compare/sim.
- corregido el bloqueo packaging macOS `Invalid Iconset` generando el fichero `.icns` con un helper Python determinista.
- mantenida la exclusion permanente de `build-arm-output/` del staging de fuentes y del tracking git.
- alineados metadatos locales de version, defaults de workflow, documentacion release y notas GitHub con la semver `1.6.1`.

## Targets Release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / experimental)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(baseline Debian Trixie)*

## Artefactos Release

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage.sha256.txt`

## Requisitos Minimos Linux

Hardware:

- CPU `x86_64` con SSE2, o CPU `aarch64` / ARM64 64-bit
- dual-core 2.0 GHz o mejor, o SoC ARM64 moderno equivalente
- minimo 4 GB RAM (8 GB recomendados)
- al menos 500 MB libres en disco
- hardware de audio/CAT/serie/USB adecuado para weak-signal

Software:

- distribucion Linux 64-bit con sesion de escritorio X11 o Wayland capaz de ejecutar AppImage Qt5
- AppImage Linux `x86_64`: `glibc >= 2.35`
- AppImage Linux `aarch64`: `glibc >= 2.38` *(baseline Debian Trixie)*
- `libfuse2` / FUSE2 para montar directamente la AppImage
- ALSA, PulseAudio o PipeWire
- permisos de acceso serie/USB para CAT o dispositivos externos

## Guia de Arranque

Si macOS bloquea el inicio:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Para evitar problemas debidos al sistema de archivos de solo lectura de las AppImage, se recomienda iniciar Decodium extrayendo primero la AppImage y ejecutando despues el programa desde la carpeta extraida.

Ejecutar los siguientes comandos en la terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Archivos Relacionados

- [README.md](README.md)
- [README.en-GB.md](README.en-GB.md)
- [README.it.md](README.it.md)
- [RELEASE_NOTES_1.6.1.md](RELEASE_NOTES_1.6.1.md)
- [doc/GITHUB_RELEASE_BODY_1.6.1.md](doc/GITHUB_RELEASE_BODY_1.6.1.md)
