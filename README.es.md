# Decodium 3 FT2 (Fork macOS/Linux) - 1.5.2

Este fork empaqueta Decodium 3 FT2 para macOS y Linux AppImage, con fixes de cierre de QSO FT2/FT4/FT8, endurecimiento AutoCQ, actualizaciones de decoder FT2 desde upstream, recuperacion de audio al arrancar, soporte updater, controles web app alineados, traducciones UI completas y tooling de certificados Decodium mantenidos en este repositorio.

Release estable actual: `1.5.2`.

## Cambios en 1.5.2 (`1.5.1 -> 1.5.2`)

- Correccion runtime FT2 / FT4 / FT8:
- endurecidos los paths estandar de late-signoff, late-final-ack, partner obsoleto, retry y direct-reply para que los QSO completados vayan a log correctamente y no queden en bucle sobre `73` / `RR73`.
- restaurado el lock de QSO activo usado por `Wait Features + AutoSeq` en FT4/FT8 para que un QSO en marcha no sea interrumpido por la logica de llamada en cola.
- corregido el reuso de callsign y reporte obsoleto cuando AutoCQ pasa de CQ a un nuevo caller directo o de una estacion en cola a la siguiente.
- Protocolo FT2 y decoder:
- alineado el codigo decoder FT2 al path LDPC FT2 dedicado de upstream y actualizado el soporte bitmetrics FT2.
- completado el flow FT2 `2 msg / 3 msg / 5 msg`, incluidos `Quick QSO`, manejo TU mixed-mode y routing del QSO corto FT2 actual.
- ocultados los tags decoder FT2 async/triggered (`T`, `aN`) de las ventanas decode y colapsados los duplicados async/sync en un solo decode logico.
- Audio / UI / control remoto:
- reforzada la recuperacion RX-audio al arranque y al wake: monitor-on arma ahora health-check y reopen automatico de streams si el audio sigue mudo.
- acercada la web app a la paridad desktop con `Manual TX`, `Speedy`, `D-CW`, tarjeta async, `Quick QSO` y `2/3/5 msg`.
- completados todos los ficheros de traduccion UI bundle para que menus, popup y cadenas internas ya no salgan con huecos `unfinished`.
- Plataforma / tooling:
- anadidos load/autoload/estado de certificados Decodium mas el generador local `tools/generate_cert.py`.
- mantenido el updater interno y refinada la apertura directa del asset macOS/Linux mas adecuado.
- centralizado el versionado release mediante `fork_release_version.txt`, para que builds locales, workflows y releases GitHub permanezcan alineados.
- Mapa e identidad:
- corregidos enlaces live-map obsoletos o falsos durante la vuelta a CQ o el CQ puro.
- alineada la identidad PSK Reporter exactamente con la cadena del titulo de la aplicacion.

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
- acceso a red recomendado para NTP, DX Cluster, PSK Reporter, updater y funciones online

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
- [RELEASE_NOTES_1.5.2.md](RELEASE_NOTES_1.5.2.md)
- [doc/GITHUB_RELEASE_BODY_1.5.2.md](doc/GITHUB_RELEASE_BODY_1.5.2.md)
- [CHANGELOG.md](CHANGELOG.md)
