# Notas de Documentacion (Espanol) - v1.4.9

Este indice agrupa la documentacion orientada a release del ciclo actual del fork.

- Release actual: `v1.4.9`
- Ciclo de actualizacion: `v1.4.8 -> v1.4.9`
- Foco principal: mejoras del decoder FT2, feedback visual async FT2, correccion startup/AutoCQ FT2, packaging de datos astronomicos Linux y mejoras UI de idioma/cluster.

## Cambios Tecnicos Principales (`v1.4.8 -> v1.4.9`)

- El triggered decode FT2 usa ahora escalado LLR `3.2` y normalizacion explicita de las tres ramas LLR FT2.
- anadida channel estimation adaptativa FT2 con metricas MMSE-equalized mediante `ft2_channel_est.f90`.
- nuevo visualizador dedicado FT2 async, con S-meter actualizado desde el decode real y polling a `100 ms`.
- el arranque FT2 ya no se fuerza; se respetan modo/frecuencia guardados.
- la respuesta dirigida inmediata FT2 y el reset de contadores retry AutoCQ reducen primeros callers perdidos y cambios prematuros de partner.
- nuevo menu `Language` persistente en settings y recargado desde `main.cpp`.
- columnas DX Cluster redimensionables y estado del header persistente.
- lookup `JPLEPH` extendido a AppImage, paths share Linux, directorio de trabajo y `CMAKE_SOURCE_DIR`, con packaging AppImage que ahora incluye el fichero.

## Artefactos de Release

- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.9-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.9-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.9-linux-x86_64.AppImage.sha256.txt`

## Requisitos Minimos Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM 4 GB minimo (8 GB recomendado)
- 500 MB libres en disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guia de Inicio

macOS cuarentena:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage extraer-y-ejecutar:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Archivos Relacionados

- [README.md](../README.md)
- [README.en-GB.md](../README.en-GB.md)
- [README.it.md](../README.it.md)
- [README.es.md](../README.es.md)
- [RELEASE_NOTES_v1.4.9.md](../RELEASE_NOTES_v1.4.9.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.9.md](./GITHUB_RELEASE_BODY_v1.4.9.md)
- [CHANGELOG.md](../CHANGELOG.md)
