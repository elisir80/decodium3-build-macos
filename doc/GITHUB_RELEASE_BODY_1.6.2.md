# Decodium 1.6.2 (Fork 9H1SR)

## English

Release highlights (`1.6.1 -> 1.6.2`):

- hardened UDP multicast delivery for LAN logger workflows with better interface resolution, protocol-aware filtering, and default-route fallback.
- improved TCI startup behavior for asynchronous SunSDR / ExpertSDR3 style radios so Decodium no longer fails too early while waiting for ready/power state.
- improved intermittent startup audio recovery when CAT is disconnected or Qt audio devices briefly resolve as null at launch.
- completed the maintained `qmap/libqmap` migration to native C++ and removed the last active cross-platform CMake Fortran backend.
- completed the maintained astronomy/ephemeris migration to native C++ and removed the old active Fortran astronomy chain from the maintained build.
- cleaned additional obsolete Fortran and archival WSPR/JT/QSO50 sources while keeping `map65/libm65` Windows-only in CMake.
- kept `build-arm-output/` excluded permanently from git tracking and source staging.
- aligned local version metadata, workflow defaults, readmes, docs, changelog, release notes, repository description, and GitHub release body to semantic version `1.6.2`.

Release assets:

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage.sha256.txt`

Linux minimum requirements:

- `x86_64` with SSE2 or `aarch64` / ARM64 64-bit CPU
- 4 GB RAM minimum, 500 MB free disk
- 64-bit Linux desktop session on X11 or Wayland able to run Qt5 AppImages
- `glibc >= 2.35` for Linux `x86_64`
- `glibc >= 2.38` for Linux `aarch64` *(Debian Trixie baseline)*
- `libfuse2`, ALSA/PulseAudio/PipeWire, and serial/USB permissions as needed

If macOS blocks startup:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage, si consiglia di avviare Decodium estraendo prima l'AppImage e poi eseguendo il programma dalla cartella estratta.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

No `.pkg` installers are produced.

## Italiano

Punti principali (`1.6.1 -> 1.6.2`):

- irrobustita la consegna UDP multicast per i workflow logger LAN con migliore risoluzione interfacce, filtro protocollo e fallback sulla route di default.
- migliorato lo startup TCI per radio asincrone stile SunSDR / ExpertSDR3, cosi' Decodium non fallisce piu' troppo presto mentre attende ready/power.
- migliorato il recupero audio intermittente all'avvio quando il CAT e' scollegato o i device audio Qt tornano temporaneamente nulli.
- completata la migrazione nativa C++ mantenuta di `qmap/libqmap` e rimosso l'ultimo backend Fortran CMake attivo cross-platform.
- completata la migrazione mantenuta astronomia/effemeridi a C++ nativo e rimossa dal build mantenuto la vecchia catena astronomica Fortran attiva.
- ripuliti ulteriori sorgenti Fortran obsoleti e archivi WSPR/JT/QSO50, mantenendo `map65/libm65` solo Windows in CMake.
- mantenuta l'esclusione permanente di `build-arm-output/` dal tracking git e dallo staging sorgenti.
- allineati alla semver `1.6.2` metadati versione locali, default workflow, readme, documentazione, changelog, note release, descrizione repository e body GitHub.

Asset release:

- `decodium3-ft2-1.6.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.2-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.2-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.2-linux-aarch64.AppImage.sha256.txt`

Requisiti minimi Linux:

- `x86_64` con SSE2 oppure CPU `aarch64` / ARM64 64-bit
- minimo 4 GB RAM, 500 MB liberi su disco
- distribuzione Linux 64-bit con sessione desktop X11 o Wayland capace di eseguire AppImage Qt5
- `glibc >= 2.35` per Linux `x86_64`
- `glibc >= 2.38` per Linux `aarch64` *(baseline Debian Trixie)*
- `libfuse2`, ALSA/PulseAudio/PipeWire e permessi seriale/USB secondo necessita'

Se macOS blocca l'avvio:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage, si consiglia di avviare Decodium estraendo prima l'AppImage e poi eseguendo il programma dalla cartella estratta.

Eseguire i seguenti comandi nel terminale:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

Non vengono prodotti installer `.pkg`.

## Espanol

Resumen (`1.6.1 -> 1.6.2`):

- reforzada la entrega UDP multicast para workflows logger LAN con mejor resolucion de interfaces, filtrado por protocolo y fallback a la ruta por defecto.
- mejorado el arranque TCI para radios asincronas tipo SunSDR / ExpertSDR3, de modo que Decodium ya no falle demasiado pronto mientras espera ready/power.
- mejorada la recuperacion de audio intermitente al arranque cuando CAT esta desconectado o los dispositivos de audio Qt se resuelven temporalmente como nulos.
- completada la migracion nativa C++ mantenida de `qmap/libqmap` y eliminado el ultimo backend Fortran CMake activo cross-platform.
- completada la migracion mantenida de astronomia/efemerides a C++ nativo y eliminada del build mantenido la vieja cadena astronomica Fortran activa.
- limpiadas fuentes Fortran obsoletas adicionales y archivos WSPR/JT/QSO50, manteniendo `map65/libm65` solo Windows en CMake.
- mantenida la exclusion permanente de `build-arm-output/` del tracking git y del staging de fuentes.
- alineados con la semver `1.6.2` metadatos locales de version, defaults de workflow, readmes, documentacion, changelog, notas release, descripcion del repositorio y body GitHub.

Artefactos release:

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

Requisitos minimos Linux:

- `x86_64` con SSE2 o CPU `aarch64` / ARM64 64-bit
- minimo 4 GB RAM, 500 MB libres en disco
- distribucion Linux 64-bit con sesion de escritorio X11 o Wayland capaz de ejecutar AppImage Qt5
- `glibc >= 2.35` para Linux `x86_64`
- `glibc >= 2.38` para Linux `aarch64` *(baseline Debian Trixie)*
- `libfuse2`, ALSA/PulseAudio/PipeWire y permisos serie/USB segun necesidad

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

No se generan instaladores `.pkg`.
