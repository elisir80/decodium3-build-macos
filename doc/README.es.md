# Notas de Documentacion (Espanol) - 1.6.2

- Release actual: `1.6.2`
- Ciclo de actualizacion: `1.6.1 -> 1.6.2`

## Cambios Tecnicos Principales (`1.6.1 -> 1.6.2`)

- La entrega UDP multicast es mas robusta para workflows LAN logger gracias a mejor resolucion de interfaces, filtrado por protocolo y fallback a la ruta por defecto.
- El arranque TCI ahora tolera radios asincronas tipo SunSDR / ExpertSDR3 que publican ready/power con retraso.
- La recuperacion de audio al arranque ahora reintenta tras refrescar la cache de dispositivos de audio Qt cuando CAT esta desconectado o la enumeracion compite con la UI.
- `qmap/libqmap` ha sido migrado completamente a C++ nativo, eliminando el ultimo backend Fortran CMake activo cross-platform.
- El camino activo de astronomia/efemerides ha sido migrado a C++ nativo y la vieja cadena astronomica Fortran activa se ha eliminado del build mantenido.
- Se han eliminado fuentes Fortran obsoletas adicionales y arboles archivisticos WSPR/JT/QSO50, mientras `map65/libm65` sigue siendo solo Windows en CMake.
- Metadatos de version, defaults de workflow, documentos release y notas GitHub quedan alineados a `1.6.2`.

## Artefactos Release

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort / experimental, si se genera)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`

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
- [RELEASE_NOTES_1.6.2.md](../RELEASE_NOTES_1.6.2.md)
- [doc/GITHUB_RELEASE_BODY_1.6.2.md](./GITHUB_RELEASE_BODY_1.6.2.md)
