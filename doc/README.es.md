# Notas de Documentacion (Espanol) - 1.6.1

- Release actual: `1.6.1`
- Ciclo de actualizacion: `1.6.0 -> 1.6.1`

## Cambios Tecnicos Principales (`1.6.0 -> 1.6.1`)

- Los caminos runtime activos JT4, JT9 y JT65 se mantienen ahora sobre el stack decode nativo C++.
- Los caminos runtime activos Q65 y WSPR son Fortran-free, y Echo funciona ahora sobre el runtime/tool path nativo C++.
- La superficie runtime mantenida ya no lleva el historico naming FFT `four2a` ni los residuos relacionados del cleanup ABI legacy.
- Eliminadas fuentes Fortran obsoletas de `lib/`, `qmap/libqmap/`, `map65/libm65/` y del viejo arbol de herramientas Echo.
- Anadidos fixes Linux de build/startup para `mainwindow.cpp`, inicializacion diferida de clientes, `QSocketNotifier`, teardown del logging Qt y enlace GNU ld de herramientas compare.
- El packaging release macOS genera ahora `.icns` mediante un helper Python determinista.
- Metadatos de version, defaults de workflow, documentos release y notas GitHub quedan alineados a `1.6.1`.

## Artefactos Release

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort / experimental, si se genera)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`

## Requisitos Minimos Linux

- CPU `x86_64` con SSE2 o CPU `aarch64` / ARM64 64-bit
- minimo 4 GB RAM, 500 MB libres en disco
- distribucion Linux 64-bit con sesion de escritorio X11 o Wayland capaz de ejecutar AppImage Qt5
- `glibc >= 2.35` para Linux `x86_64`
- `glibc >= 2.38` para Linux `aarch64` *(baseline Debian Trixie)*
- `libfuse2`, ALSA/PulseAudio/PipeWire y permisos serie/USB segun necesidad

## Guia de Arranque

Workaround de cuarentena macOS:

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

- [README.es.md](../README.es.md)
- [RELEASE_NOTES_1.6.1.md](../RELEASE_NOTES_1.6.1.md)
- [doc/GITHUB_RELEASE_BODY_1.6.1.md](./GITHUB_RELEASE_BODY_1.6.1.md)
