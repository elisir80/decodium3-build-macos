# Notas de Documentacion (Espanol) - v1.4.7

Este indice agrupa la documentacion orientada a release del ciclo actual del fork.

- Release actual: `v1.4.7`
- Ciclo de actualizacion: `v1.4.6 -> v1.4.7`
- Foco principal: hardening runtime/decode FT2, continuidad AutoCQ, integracion AutoSpot/DX Cluster y alineacion release.

## Cambios Tecnicos Principales (`v1.4.6 -> v1.4.7`)

- guardia async Tx FT2 subida a `300 ms`.
- filtro false decode FT2 ampliado con validacion de prefijos `cty.dat`.
- renderizado FT2 `TΔ` y normalizacion de marcador reforzados para preservar alineacion de columnas.
- estabilizados lock de pareja / reintentos / retorno a CQ tras `73` confirmado en AutoCQ.
- ajustes con nueva seccion para endpoint AutoSpot y flag enable.
- ventana DX Cluster ahora consulta un endpoint DxSpider configurable con manejo telnet/prompt mas robusto.
- dashboard web con toggle AutoSpot, mejor feedback de comandos y presets de modo mas estables.
- estado del menu `Datos Astronomicos` ahora sigue el cierre real de la ventana.

## Artefactos de Release

- `decodium3-ft2-v1.4.7-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.7-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.7-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.7-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.7-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.7-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-v1.4.7-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.7-linux-x86_64.AppImage.sha256.txt`

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
- [RELEASE_NOTES_v1.4.7.md](../RELEASE_NOTES_v1.4.7.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.7.md](./GITHUB_RELEASE_BODY_v1.4.7.md)
- [CHANGELOG.md](../CHANGELOG.md)
