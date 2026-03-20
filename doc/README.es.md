# Notas de Documentacion (Espanol) - 1.5.2

Este indice agrupa la documentacion de release del ciclo actual del fork.

- Release actual: `1.5.2`
- Ciclo de actualizacion: `1.5.1 -> 1.5.2`
- Foco principal: actualizaciones decoder/protocolo FT2, correccion AutoCQ y Wait Features, recuperacion de audio al arranque, paridad web app, traducciones UI completas y alineacion version/release.

## Cambios Tecnicos Principales (`1.5.1 -> 1.5.2`)

- refresh decoder FT2 con path LDPC FT2 dedicado upstream y soporte bitmetrics FT2 actualizado.
- finalizacion del flow FT2 `Quick QSO` / `2 msg / 3 msg / 5 msg` con manejo TU mixed-mode.
- restauracion del lock QSO activo `Wait Features + AutoSeq` para FT4/FT8.
- recuperacion RX-audio al arranque y al wake ligada a la activacion real del monitor.
- extension de la paridad web app/dashboard con Manual TX, Speedy, D-CW, async, Quick QSO y controles 2/3/5 mensajes.
- finalizacion de traducciones UI bundle y eliminacion de tags async FT2 visibles en las decode panes.
- centralizacion del versionado release mediante `fork_release_version.txt`.

## Artefactos Release

- `decodium3-ft2-1.5.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage.sha256.txt`

## Requisitos Minimos Linux

- `x86_64`, dual-core 2.0 GHz+, 4 GB RAM minima, 500 MB libres
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guia de Arranque

Cuarentena macOS:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Flujo Linux AppImage extract-run:

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
- [RELEASE_NOTES_1.5.2.md](../RELEASE_NOTES_1.5.2.md)
- [doc/GITHUB_RELEASE_BODY_1.5.2.md](./GITHUB_RELEASE_BODY_1.5.2.md)
- [CHANGELOG.md](../CHANGELOG.md)
