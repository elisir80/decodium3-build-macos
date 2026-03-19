# Decodium 3 FT2 (Fork macOS/Linux) - 1.5.0

Este fork empaqueta Decodium 3 FT2 para macOS y Linux AppImage, con trabajo especifico en Quick QSO FT2, fixes de secuenciacion de QSO, endurecimiento de AutoCQ, actualizaciones del decoder y tooling de certificados Decodium mantenidos en este repositorio.

Release estable actual: `1.5.0`.

## Cambios en 1.5.0 (`1.4.9 -> 1.5.0`)

- Startup audio:
- anadida recuperacion automatica RX cuando los dispositivos estan seleccionados correctamente pero el audio sigue mudo al arrancar.
- la reapertura de streams y el rearme del monitor replican el flujo manual "Preferencias Audio -> OK".
- Flujo QSO y log:
- corregido el `73` final en FT8, FT4 y FT2 estandar de 5 mensajes cuando la otra estacion envia antes `RR73` o `73`.
- corregidos varios paths de log en FT2 Quick QSO, incluido el fallback "log despues de mi 73".
- el mapa DX y los campos DX activos ahora se limpian correctamente cuando la app vuelve a CQ con el QSO cerrado.
- AutoCQ:
- la proteccion recent-worked bloquea ahora los retrabajos inmediatos del mismo callsign en todos los paths de seleccion.
- el cambio al siguiente caller reinicia retry, reportes y estado QSO antes de arrancar el nuevo contacto.
- en FT8 el timeout de retry cuenta ahora solo periodos realmente perdidos.
- `debug.txt` registra ahora cambios de partner, inicio de cola, handoff, progreso de retry y saltos de callsigns recien trabajados.
- Protocolo/runtime FT2:
- importado el fix upstream del watchdog rescue.
- anadido el decoder LDPC dedicado FT2 y conectado el triggered decode FT2 a ese path.
- alineados los decoders LDPC compartidos al refresh upstream Normalized Min-Sum.
- Quick QSO:
- anadido el boton `Quick QSO` como alias UI del perfil FT2 `2 msg`.
- el flow Quick QSO actual se ha alineado al esquema corto pedido para FT2 manteniendo backward compatibility para variantes `TU` antiguas.
- Certificados/tooling:
- anadidos loader/autoload de certificados Decodium e indicador de estado en la ventana principal.
- anadido `tools/generate_cert.py` para generar ficheros `.decodium`.

## Artefactos Release

- `decodium3-ft2-1.5.0-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage.sha256.txt`

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
- acceso a red recomendado para NTP, DX Cluster y workflows online

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
- [RELEASE_NOTES_1.5.0.md](RELEASE_NOTES_1.5.0.md)
- [doc/GITHUB_RELEASE_BODY_1.5.0.md](doc/GITHUB_RELEASE_BODY_1.5.0.md)
- [CHANGELOG.md](CHANGELOG.md)
