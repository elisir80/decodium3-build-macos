# Decodium 3 FT2 (Fork macOS/Linux) - 1.5.1

Este fork empaqueta Decodium 3 FT2 para macOS y Linux AppImage, con fixes de cierre de QSO FT2/FT4/FT8, endurecimiento de la maquina de estados AutoCQ, comprobacion interna de actualizaciones, sync de decoders desde upstream y tooling de certificados Decodium mantenidos en este repositorio.

Release estable actual: `1.5.1`.

## Cambios en 1.5.1 (`1.5.0 -> 1.5.1`)

- Actualizaciones internas:
- anadida comprobacion de updates contra GitHub Releases al arrancar.
- anadida accion manual `Help > Check for updates...`.
- el updater abre ahora directamente el asset correcto para la plataforma actual en lugar de solo la pagina release generica.
- Flujo QSO y log:
- corregidos varios paths tardios FT2/FT4/FT8 donde la app podia seguir enviando `73/RR73`, perder el log final o no recuperar un cierre retardado.
- corregido el caso donde el `73/RR73` final del corresponsal llegaba despues de que la estacion local ya hubiera enviado su propio signoff.
- mejorado el recovery del final-ack tardio tras timeout, de modo que un `73/RR73` retrasado todavia puede ir a log correctamente.
- AutoCQ:
- corregido el reuso de partner obsoleto despues de volver a CQ.
- corregidos casos de caller directo bien decodificado pero con la app manteniendo CQ en vez de armar `Tx2`.
- corregido el primer reply FT2 directo que podia usar un reporte obsoleto del QSO anterior en lugar del SNR real del caller actual.
- ampliada la supresion recent-work y abandoned-partner para reducir retrabajos duplicados tras cierres diferidos.
- Mapa e identidad:
- corregido el live world map que podia mostrar un enlace activo falso mientras solo estabas transmitiendo CQ.
- alineado el identificador de software enviado a PSK Reporter exactamente con la cadena mostrada en la barra de titulo.
- Diagnostica/proceso:
- ampliado `debug.txt` con mas trazas para armado de caller directo, limpieza de partner obsoleto, recovery late signoff y seleccion de assets del updater.
- version UI local, defaults de workflow y documentacion release alineados ahora con la semver `1.5.1`.

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

Hardware:

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM 4 GB minimo (8 GB recomendado)
- al menos 500 MB libres en disco
- pantalla 1280x800 o superior recomendada
- hardware radio/CAT/audio segun la estacion

Software:

- Linux `x86_64` con `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire
- entorno de escritorio capaz de ejecutar AppImage Qt5
- acceso a red recomendado para NTP, DX Cluster y PSK Reporter

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

## Ficheros Relacionados

- [README.md](README.md)
- [README.en-GB.md](README.en-GB.md)
- [README.it.md](README.it.md)
- [RELEASE_NOTES_1.5.1.md](RELEASE_NOTES_1.5.1.md)
- [doc/GITHUB_RELEASE_BODY_1.5.1.md](doc/GITHUB_RELEASE_BODY_1.5.1.md)
- [CHANGELOG.md](CHANGELOG.md)
