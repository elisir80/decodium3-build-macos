# Decodium 1.6.1 (Fork 9H1SR)

## English

Release highlights (`1.6.0 -> 1.6.1`):

- completed the maintained native C++ migration of the active legacy JT runtime across JT4, JT9, and JT65.
- promoted Q65 and WSPR active runtime paths to Fortran-free native implementations and finished the Echo runtime/tool migration to native C++.
- removed the remaining active-path legacy ABI naming, including the historical FFT `four2a` compatibility naming, and cleaned obsolete Fortran sources from `lib/`, `qmap/libqmap/`, and `map65/libm65/`.
- fixed Linux build/startup regressions involving `mainwindow.cpp`, deferred client initialization, `QSocketNotifier`, Qt logging teardown, and GNU ld linkage in compare/sim targets.
- replaced the fragile macOS `iconutil` path with deterministic `.icns` generation, removing the `Invalid Iconset` release blocker.
- kept `build-arm-output/` excluded permanently from git tracking and source staging.
- aligned local version metadata, workflow defaults, readmes, docs, changelog, release notes, repository description, and GitHub release body to semantic version `1.6.1`.

Release assets:

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.zip` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, if generated)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage.sha256.txt`

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

To avoid issues caused by the AppImage read-only filesystem, it is recommended to start Decodium by extracting the AppImage first and then running the program from the extracted directory.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

No `.pkg` installers are produced.

## Italiano

Punti principali (`1.6.0 -> 1.6.1`):

- completata la migrazione nativa C++ mantenuta del runtime JT legacy attivo su JT4, JT9 e JT65.
- promossi a implementazioni native Fortran-free i path runtime attivi Q65 e WSPR e completata la migrazione a C++ nativo del runtime/tool path Echo.
- rimosso il naming legacy ABI residuo del path attivo, incluso lo storico naming FFT `four2a`, e ripuliti sorgenti Fortran obsoleti da `lib/`, `qmap/libqmap/` e `map65/libm65/`.
- corrette regressioni Linux di build/startup che coinvolgevano `mainwindow.cpp`, inizializzazione differita client, `QSocketNotifier`, teardown logging Qt e linkage GNU ld dei target compare/sim.
- sostituito il fragile path macOS `iconutil` con generazione `.icns` deterministica, eliminando il blocco release `Invalid Iconset`.
- mantenuta l'esclusione permanente di `build-arm-output/` dal tracking git e dallo staging dei sorgenti.
- allineati alla semver `1.6.1` metadati versione locali, default workflow, readme, documentazione, changelog, note release, descrizione repository e body GitHub.

Asset release:

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage.sha256.txt`

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

Resumen (`1.6.0 -> 1.6.1`):

- completada la migracion nativa C++ mantenida del runtime JT legacy activo en JT4, JT9 y JT65.
- promovidos a implementaciones nativas Fortran-free los caminos runtime activos Q65 y WSPR y completada la migracion del runtime/tool path Echo a C++ nativo.
- eliminado el naming legacy ABI restante del camino activo, incluido el historico naming FFT `four2a`, y limpiadas fuentes Fortran obsoletas de `lib/`, `qmap/libqmap/` y `map65/libm65/`.
- corregidas regresiones Linux de build/startup que involucraban `mainwindow.cpp`, inicializacion diferida de clientes, `QSocketNotifier`, teardown del logging Qt y enlace GNU ld de targets compare/sim.
- sustituido el fragil camino macOS `iconutil` por generacion `.icns` determinista, eliminando el bloqueo release `Invalid Iconset`.
- mantenida la exclusion permanente de `build-arm-output/` del tracking git y del staging de fuentes.
- alineados con la semver `1.6.1` metadatos locales de version, defaults de workflow, readmes, documentacion, changelog, notas release, descripcion del repositorio y body GitHub.

Artefactos release:

- `decodium3-ft2-1.6.1-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.6.1-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.6.1-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.dmg` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64.zip` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.1-macos-monterey-x86_64-sha256.txt` *(best effort/experimental, si se genera)*
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage`
- `decodium3-ft2-1.6.1-linux-x86_64.AppImage.sha256.txt`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage`
- `decodium3-ft2-1.6.1-linux-aarch64.AppImage.sha256.txt`

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
