# Release Notes / Note di Rilascio / Notas de Lanzamiento - Fork 1.6.1

Scope: update cycle from `1.6.0` to `1.6.1`.

## English

`1.6.1` focuses on finishing the maintained native C++ migration of the legacy JT runtime, removing the last active-path Fortran and legacy-ABI residues from JT/Q65/WSPR/Echo, fixing Linux build/startup regressions, and hardening macOS/Linux release packaging.

### Detailed Changes (`1.6.0 -> 1.6.1`)

- completed the maintained native C++ migration of the active legacy JT runtime, covering JT4, JT9 narrow/wide/fast, and JT65 decode/runtime paths.
- removed the remaining active production dependencies on the legacy Fortran JT decoder-orchestrator sources; the old JT reference path now stays isolated to compare/reference targets only.
- promoted Q65 and WSPR active runtime paths to Fortran-free native implementations.
- completed the Echo runtime/tool migration to native C++ and removed obsolete Echo Fortran sources and utilities from the maintained tree.
- removed the remaining active-path legacy ABI naming from the maintained runtime surface, including the historical FFT `four2a` naming and related legacy compatibility exports.
- cleaned obsolete Fortran sources and compatibility files from `lib/`, `qmap/libqmap/`, `map65/libm65/`, and legacy Echo tooling.
- updated `map65/libm65` legacy Makefile builds to use `wsjt_fft_compat` and removed `four2a.f90` from that tree.
- fixed Linux x86_64 build failures in `mainwindow.cpp` caused by a broken deferred lambda path and mismatched symbols after the legacy JT migration work.
- fixed Linux startup/shutdown regressions around deferred `MessageClient` / `NtpClient` initialization, `QSocketNotifier` warning handling, and Qt logging teardown.
- fixed GNU ld link failures in legacy compare/sim targets such as `jt9sim`, `jt65_compare`, `jt65_sync_compare`, and `jt65_symspec_compare`.
- replaced the macOS `.icns` generation path with a deterministic Python helper to eliminate the `wsjtx.iconset: Invalid Iconset` release blocker.
- kept `build-arm-output/` excluded permanently from source staging and git tracking.
- aligned local version metadata, workflow defaults, readmes, docs, changelog, release notes, repository description, and GitHub release body to `1.6.1`.

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

To avoid issues caused by the AppImage read-only filesystem, it is recommended to start Decodium by extracting the AppImage first and then running the program from the extracted directory.

Run the following commands in a terminal:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Italiano

`1.6.1` e' focalizzata nel completare la migrazione nativa C++ mantenuta del runtime JT legacy, nel rimuovere gli ultimi residui Fortran e legacy-ABI del path attivo da JT/Q65/WSPR/Echo, nel correggere regressioni Linux di build/startup e nel rafforzare il packaging release macOS/Linux.

### Modifiche Dettagliate (`1.6.0 -> 1.6.1`)

- completata la migrazione nativa C++ mantenuta del runtime JT legacy attivo, coprendo i path decode/runtime JT4, JT9 narrow/wide/fast e JT65.
- rimosse dal path di produzione attivo le dipendenze residue dai vecchi sorgenti Fortran orchestrator dei decoder JT legacy; il vecchio path reference resta ora isolato solo nei target compare/reference.
- promossi a implementazioni native Fortran-free i path runtime attivi Q65 e WSPR.
- completata la migrazione a C++ nativo del runtime/tool path Echo e rimossi dal tree mantenuto i vecchi sorgenti e utility Echo in Fortran.
- rimosso dalla superficie runtime mantenuta il naming legacy ABI residuo del path attivo, incluso lo storico naming FFT `four2a` e gli export legacy correlati.
- ripuliti sorgenti Fortran obsoleti e file di compatibilita' da `lib/`, `qmap/libqmap/`, `map65/libm65/` e dal vecchio tooling Echo.
- aggiornate le build legacy Makefile di `map65/libm65` per usare `wsjt_fft_compat` e rimosso `four2a.f90` da quel tree.
- corretti i fallimenti build Linux x86_64 in `mainwindow.cpp` causati da un path lambda differito rotto e da simboli non coerenti dopo il lavoro di migrazione JT legacy.
- corrette regressioni Linux in startup/chiusura legate all'inizializzazione differita di `MessageClient` / `NtpClient`, alla gestione del warning `QSocketNotifier` e al teardown del logging Qt.
- corrette le rotture GNU ld nei target legacy compare/sim come `jt9sim`, `jt65_compare`, `jt65_sync_compare` e `jt65_symspec_compare`.
- sostituito il path di generazione `.icns` macOS con un helper Python deterministico, eliminando il blocco release `wsjtx.iconset: Invalid Iconset`.
- mantenuta l'esclusione permanente di `build-arm-output/` dallo staging sorgenti e dal tracking git.
- allineati a `1.6.1` metadati versione locali, default workflow, readme, documentazione, changelog, note release, descrizione repository e body GitHub.

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

`1.6.1` se centra en completar la migracion nativa C++ mantenida del runtime JT legacy, eliminar los ultimos residuos Fortran y legacy-ABI del camino activo de JT/Q65/WSPR/Echo, corregir regresiones Linux de build/startup y reforzar el packaging release macOS/Linux.

### Cambios Detallados (`1.6.0 -> 1.6.1`)

- completada la migracion nativa C++ mantenida del runtime JT legacy activo, cubriendo los caminos decode/runtime JT4, JT9 narrow/wide/fast y JT65.
- eliminadas del camino de produccion activo las dependencias restantes de las viejas fuentes Fortran orchestrator de los decoders JT legacy; el viejo camino reference queda ahora aislado solo en los targets compare/reference.
- promovidos a implementaciones nativas Fortran-free los caminos runtime activos Q65 y WSPR.
- completada la migracion del runtime/tool path Echo a C++ nativo y eliminadas del arbol mantenido las viejas fuentes y utilidades Echo Fortran.
- eliminado de la superficie runtime mantenida el naming legacy ABI restante del camino activo, incluido el historico naming FFT `four2a` y los exports legacy relacionados.
- limpiadas fuentes Fortran obsoletas y ficheros de compatibilidad de `lib/`, `qmap/libqmap/`, `map65/libm65/` y del viejo tooling Echo.
- actualizadas las builds legacy Makefile de `map65/libm65` para usar `wsjt_fft_compat` y eliminado `four2a.f90` de ese arbol.
- corregidos los fallos de build Linux x86_64 en `mainwindow.cpp` causados por un camino lambda diferido roto y simbolos incoherentes tras el trabajo de migracion JT legacy.
- corregidas regresiones Linux de arranque/cierre ligadas a la inicializacion diferida de `MessageClient` / `NtpClient`, al manejo del warning `QSocketNotifier` y al teardown del logging Qt.
- corregidos los fallos GNU ld en los targets legacy compare/sim como `jt9sim`, `jt65_compare`, `jt65_sync_compare` y `jt65_symspec_compare`.
- sustituido el camino de generacion `.icns` macOS por un helper Python determinista, eliminando el bloqueo release `wsjtx.iconset: Invalid Iconset`.
- mantenida la exclusion permanente de `build-arm-output/` del staging de fuentes y del tracking git.
- alineados con `1.6.1` metadatos locales de version, defaults de workflow, readmes, documentacion, changelog, notas release, descripcion del repositorio y body GitHub.

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
