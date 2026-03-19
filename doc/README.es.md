# Notas de Documentacion (Espanol) - 1.5.1

Este indice agrupa la documentacion orientada a release del ciclo actual del fork.

- Release actual: `1.5.1`
- Ciclo de actualizacion: `1.5.0 -> 1.5.1`
- Foco principal: updater interno, correccion late-signoff FT2/FT4/FT8, endurecimiento AutoCQ en respuestas directas, limpieza de mapa y alineacion PSK Reporter.

## Cambios Tecnicos Principales (`1.5.0 -> 1.5.1`)

- verificador interno de updates GitHub con seleccion directa del asset correcto para macOS/Linux.
- recovery late-signoff FT2/FT4/FT8 para que `73/RR73` retrasados todavia puedan ir a log.
- fix AutoCQ en callers directos al salir de CQ y armar inmediatamente `Tx2`.
- fix del reporte obsoleto en el primer reply FT2 directo.
- limpieza del mapa en CQ y alineacion de la cadena de titulo usada hacia PSK Reporter.

## Artefactos Release

- `decodium3-ft2-1.5.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.1-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.1-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.1-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.1-linux-x86_64.AppImage.sha256.txt`

## Requisitos Minimos Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM 4 GB minimo (8 GB recomendado)
- 500 MB libres en disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guia de Arranque

macOS quarantine:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage extract-run:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Ficheros Relacionados

- [README.md](../README.md)
- [README.en-GB.md](../README.en-GB.md)
- [README.it.md](../README.it.md)
- [README.es.md](../README.es.md)
- [RELEASE_NOTES_1.5.1.md](../RELEASE_NOTES_1.5.1.md)
- [doc/GITHUB_RELEASE_BODY_1.5.1.md](./GITHUB_RELEASE_BODY_1.5.1.md)
- [CHANGELOG.md](../CHANGELOG.md)
