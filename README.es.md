# Decodium (Fork macOS/Linux) - 1.6.2

- Release estable actual: `1.6.2`
- Ciclo de actualizacion: `1.6.1 -> 1.6.2`

## Cambios en 1.6.2 (`1.6.1 -> 1.6.2`)

- reforzada la entrega UDP multicast para integraciones de logger LAN, mejorando la resolucion de interfaces multicast y anadiendo fallback a la ruta por defecto cuando falla el envio forzado por interfaz.
- mejorado el arranque TCI para radios asincronas tipo SunSDR / ExpertSDR3, de modo que Decodium ya no falla demasiado pronto mientras espera el estado ready/power.
- mejorada la recuperacion de audio intermitente al arranque cuando CAT esta desconectado o la cache de dispositivos de audio Qt se resuelve temporalmente como nula.
- completada la migracion nativa C++ mantenida de `qmap/libqmap` y eliminado el ultimo backend Fortran CMake activo cross-platform.
- completada la migracion de astronomia/efemerides usada por el camino activo de la aplicacion y eliminada del build CMake la vieja cadena astronomica Fortran activa.
- limpiadas fuentes Fortran obsoletas adicionales y arboles archivisticos WSPR/JT/QSO50, manteniendo `map65/libm65` limitado a las builds CMake Windows.
- mantenida la exclusion permanente de `build-arm-output/` del staging de fuentes y del tracking git.
- alineados metadatos locales de version, defaults de workflow, documentos release y notas GitHub con la semver `1.6.2`.

## Targets Release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / experimental)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(baseline Debian Trixie)*

## Artefactos Release

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage.sha256.txt`

## Requisitos Minimos Linux

Hardware:

- CPU `x86_64` con SSE2 o CPU `aarch64` / ARM64 64-bit
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
- permisos serie/USB requeridos por CAT y radios externas

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
- [RELEASE_NOTES_1.6.2.md](RELEASE_NOTES_1.6.2.md)
- [doc/GITHUB_RELEASE_BODY_1.6.2.md](doc/GITHUB_RELEASE_BODY_1.6.2.md)
