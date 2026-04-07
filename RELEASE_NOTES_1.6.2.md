# Release Notes / Note di Rilascio / Notas de Lanzamiento - Fork 1.6.2

Scope: update cycle from `1.6.1` to `1.6.2`.

## English

`1.6.2` focuses on hardening multicast/TCI/audio startup reliability in the field, removing the last active cross-platform CMake Fortran backend, and continuing the maintained cleanup of obsolete Fortran sources from the repository tree.

### Detailed Changes (`1.6.1 -> 1.6.2`)

- hardened UDP multicast delivery for LAN logger workflows by resolving interface identifiers more flexibly, filtering multicast interfaces by protocol, and falling back to the default multicast route when interface-forced delivery fails.
- improved TCI startup handling for asynchronous radios such as SunSDR / ExpertSDR3 by waiting for the actual ready/power state instead of failing too early with `TCI SDR is not switched on`.
- improved intermittent startup audio recovery when CAT is disconnected or Qt audio devices are still enumerating, by refreshing cached device state and retrying monitor/audio startup.
- completed the maintained `qmap/libqmap` migration to native C++ and removed the final active cross-platform CMake Fortran backend from the macOS/Linux app surface.
- completed the maintained astronomy/ephemeris migration to native C++ and removed the old active Fortran astronomy chain from the maintained build.
- kept `map65/libm65` as a Windows-only CMake subtree and clarified the non-Windows build surface.
- cleaned additional obsolete or archival Fortran/WSPR/JT/QSO50 sources from the maintained tree while preserving the Windows-only legacy material still needed outside the active macOS/Linux build.
- kept `build-arm-output/` excluded permanently from source staging and git tracking.
- aligned local version metadata, workflow defaults, readmes, docs, changelog, release notes, repository description, and GitHub release body to `1.6.2`.

### Release Targets

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / experimental)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(Debian Trixie baseline)*

### Linux Minimum Requirements

Hardware:

- `x86_64` CPU with SSE2, or `aarch64` / ARM64 64-bit CPU
- dual-core 2.0 GHz or better, or equivalent modern ARM64 SoC
- 4 GB RAM minimum (8 GB recommended)
- 500 MB free disk space
- audio/CAT/serial/USB hardware suitable for weak-signal operation

Software:

- 64-bit Linux distribution with a Qt5-capable X11 or Wayland desktop session
- Linux `x86_64` AppImage: `glibc >= 2.35`
- Linux `aarch64` AppImage: `glibc >= 2.38` *(Debian Trixie baseline)*
- `libfuse2` / FUSE2 for direct AppImage mounting
- ALSA, PulseAudio, or PipeWire
- serial/USB permissions as required by CAT and radio hardware

### Startup Guidance

macOS quarantine workaround:

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

## Italiano

`1.6.2` e' focalizzata nel rafforzare l'affidabilita' sul campo di multicast/TCI/audio startup, nel rimuovere l'ultimo backend Fortran CMake attivo cross-platform e nel proseguire la pulizia mantenuta dei sorgenti Fortran obsoleti dal tree repository.

### Modifiche Dettagliate (`1.6.1 -> 1.6.2`)

- irrobustita la consegna UDP multicast per i workflow logger LAN risolvendo gli identificatori interfaccia in modo piu' flessibile, filtrando le interfacce multicast per protocollo e aggiungendo il fallback sulla route multicast di default quando l'invio forzato per interfaccia fallisce.
- migliorata la gestione startup TCI per radio asincrone come SunSDR / ExpertSDR3, aspettando lo stato ready/power reale invece di fallire troppo presto con `TCI SDR is not switched on`.
- migliorato il recupero audio intermittente all'avvio quando il CAT e' scollegato o i device audio Qt sono ancora in enumerazione, forzando refresh della cache device e retry di monitor/audio startup.
- completata la migrazione nativa C++ mantenuta di `qmap/libqmap` e rimosso dalla superficie app macOS/Linux l'ultimo backend Fortran CMake attivo cross-platform.
- completata la migrazione mantenuta astronomia/effemeridi a C++ nativo e rimossa dal build mantenuto la vecchia catena astronomica Fortran attiva.
- mantenuto `map65/libm65` come subtree CMake solo Windows e chiarita la superficie build non-Windows.
- ripuliti dal tree mantenuto ulteriori sorgenti Fortran/WSPR/JT/QSO50 obsoleti o archivistici, preservando solo il materiale legacy Windows-only ancora richiesto fuori dal build macOS/Linux attivo.
- mantenuta l'esclusione permanente di `build-arm-output/` dallo staging sorgenti e dal tracking git.
- allineati a `1.6.2` metadati versione locali, default workflow, readme, documentazione, changelog, note release, descrizione repository e body GitHub.

### Target Release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / sperimentale)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(baseline Debian Trixie)*

### Requisiti Minimi Linux

Hardware:

- CPU `x86_64` con SSE2, oppure CPU `aarch64` / ARM64 64-bit
- dual-core 2.0 GHz o meglio, oppure SoC ARM64 moderno equivalente
- minimo 4 GB RAM (8 GB raccomandati)
- 500 MB liberi su disco
- hardware audio/CAT/seriale/USB adatto al weak-signal

Software:

- distribuzione Linux 64-bit con sessione desktop Qt5 su X11 o Wayland
- AppImage Linux `x86_64`: `glibc >= 2.35`
- AppImage Linux `aarch64`: `glibc >= 2.38` *(baseline Debian Trixie)*
- `libfuse2` / FUSE2 per montare direttamente l'AppImage
- ALSA, PulseAudio o PipeWire
- permessi seriale/USB richiesti dall'hardware CAT/radio

### Guida Avvio

Workaround quarantena macOS:

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

## Espanol

`1.6.2` se centra en reforzar la fiabilidad en campo de multicast/TCI/audio al arranque, eliminar el ultimo backend Fortran CMake activo cross-platform y continuar la limpieza mantenida de fuentes Fortran obsoletas del arbol del repositorio.

### Cambios Detallados (`1.6.1 -> 1.6.2`)

- reforzada la entrega UDP multicast para workflows logger LAN resolviendo los identificadores de interfaz con mas flexibilidad, filtrando las interfaces multicast por protocolo y anadiendo fallback a la ruta multicast por defecto cuando falla el envio forzado por interfaz.
- mejorado el manejo del arranque TCI para radios asincronas como SunSDR / ExpertSDR3, esperando el estado ready/power real en vez de fallar demasiado pronto con `TCI SDR is not switched on`.
- mejorada la recuperacion de audio intermitente al arranque cuando CAT esta desconectado o los dispositivos de audio Qt siguen enumerandose, forzando refresh de la cache y retry del arranque monitor/audio.
- completada la migracion nativa C++ mantenida de `qmap/libqmap` y eliminado de la superficie app macOS/Linux el ultimo backend Fortran CMake activo cross-platform.
- completada la migracion mantenida de astronomia/efemerides a C++ nativo y eliminada del build mantenido la vieja cadena astronomica Fortran activa.
- mantenido `map65/libm65` como subtree CMake solo Windows y aclarada la superficie de build no-Windows.
- limpiadas fuentes Fortran/WSPR/JT/QSO50 obsoletas o archivisticas adicionales del arbol mantenido, preservando solo el material legacy Windows-only aun requerido fuera del build macOS/Linux activo.
- mantenida la exclusion permanente de `build-arm-output/` del staging de fuentes y del tracking git.
- alineados con `1.6.2` metadatos locales de version, defaults de workflow, readmes, documentacion, changelog, notas release, descripcion del repositorio y body GitHub.

### Targets Release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey *(best effort / experimental)*
- Linux x86_64 AppImage
- Linux aarch64 AppImage *(baseline Debian Trixie)*

### Requisitos Minimos Linux

Hardware:

- CPU `x86_64` con SSE2, o CPU `aarch64` / ARM64 64-bit
- dual-core 2.0 GHz o mejor, o SoC ARM64 moderno equivalente
- minimo 4 GB RAM (8 GB recomendados)
- 500 MB libres en disco
- hardware de audio/CAT/serie/USB adecuado para weak-signal

Software:

- distribucion Linux 64-bit con sesion de escritorio Qt5 sobre X11 o Wayland
- AppImage Linux `x86_64`: `glibc >= 2.35`
- AppImage Linux `aarch64`: `glibc >= 2.38` *(baseline Debian Trixie)*
- `libfuse2` / FUSE2 para montar directamente la AppImage
- ALSA, PulseAudio o PipeWire
- permisos serie/USB requeridos por el hardware CAT/radio

### Guia de Arranque

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
