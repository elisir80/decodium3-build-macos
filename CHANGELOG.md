# Changelog / Registro Modifiche

## [1.4.9] - 2026-03-17

### English

Release focused on FT2 decoder improvements under fading conditions, FT2 async visual/runtime refinement, FT2 startup and AutoCQ correctness, Linux astronomical-data portability, and UI/language usability improvements.

#### Added

- Added `lib/ft2/ft2_channel_est.f90` for adaptive FT2 channel estimation.
- Added the FT2 async visualizer widget.
- Added a main-menu `Language` selector with persistent UI language storage.

#### Changed

- FT2 triggered-decode LLR scaling raised from `2.83` to `3.2`.
- All three FT2 LLR branches are now normalized before LDPC decode.
- FT2 async polling reduced from `750 ms` to `100 ms`.
- DX Cluster columns are now interactive/resizable and their header state is persisted.
- Astronomical `JPLEPH` lookup now covers AppImage, Linux share paths, working directory, and `CMAKE_SOURCE_DIR`.
- Linux AppImage workflow now bundles `JPLEPH` into `usr/share/wsjtx`.
- Release/build/workflow defaults aligned to `v1.4.9`.

#### Fixed

- Fixed startup forcing FT2 mode even when a different saved mode/frequency should be restored.
- Fixed FT2 missing the first immediate directed reply while CQ was active.
- Fixed stale AutoCQ retry/miss counters causing premature partner switching.
- Fixed FT2 async line handling trimming away fixed-column formatting/timestamps.
- Fixed astronomical diagnostics so searched `JPLEPH` paths are shown explicitly.

### Italiano

Release focalizzata su miglioramenti decoder FT2 in fading, rifiniture visual/runtime FT2 async, correttezza startup e AutoCQ FT2, portabilita' Linux dei dati astronomici e miglioramenti di usabilita' UI/lingua.

#### Aggiunto

- Aggiunto `lib/ft2/ft2_channel_est.f90` per la channel estimation adattiva FT2.
- Aggiunto il visualizzatore FT2 async.
- Aggiunto un selettore `Language` nel menu principale con persistenza della lingua UI.

#### Modificato

- Scalatura LLR del triggered decode FT2 alzata da `2.83` a `3.2`.
- Tutti e tre i rami LLR FT2 vengono ora normalizzati prima del decode LDPC.
- Polling async FT2 ridotto da `750 ms` a `100 ms`.
- Le colonne DX Cluster sono ora interattive/ridimensionabili e lo stato header viene persistito.
- Il lookup astronomico `JPLEPH` copre ora AppImage, path share Linux, working directory e `CMAKE_SOURCE_DIR`.
- Il workflow Linux AppImage include ora `JPLEPH` in `usr/share/wsjtx`.
- Default release/build/workflow allineati a `v1.4.9`.

#### Corretto

- Corretto l'avvio che forzava FT2 anche quando andava ripristinato un modo/frequenza salvato diverso.
- Corretta la perdita della prima risposta diretta FT2 mentre CQ era attivo.
- Corretti contatori retry/miss AutoCQ sporchi che causavano cambi partner prematuri.
- Corretta la gestione righe FT2 async che faceva trim della formattazione a colonne fisse/timestamp.
- Corretto il diagnostico astronomico mostrando esplicitamente i path `JPLEPH` cercati.

### Espanol

Release centrada en mejoras del decoder FT2 en fading, refinamientos visual/runtime FT2 async, correccion startup y AutoCQ FT2, portabilidad Linux de datos astronomicos y mejoras de usabilidad UI/idioma.

#### Anadido

- Anadido `lib/ft2/ft2_channel_est.f90` para channel estimation adaptativa FT2.
- Anadido el visualizador FT2 async.
- Anadido selector `Language` en el menu principal con persistencia del idioma UI.

#### Cambios

- Escalado LLR del triggered decode FT2 subido de `2.83` a `3.2`.
- Las tres ramas LLR FT2 se normalizan ahora antes del decode LDPC.
- Polling async FT2 reducido de `750 ms` a `100 ms`.
- Las columnas DX Cluster son ahora interactivas/redimensionables y el estado del header se persiste.
- El lookup astronomico `JPLEPH` cubre ahora AppImage, paths share Linux, working directory y `CMAKE_SOURCE_DIR`.
- El workflow Linux AppImage incluye ahora `JPLEPH` en `usr/share/wsjtx`.
- Defaults de release/build/workflows alineados a `v1.4.9`.

#### Corregido

- Corregido el arranque que forzaba FT2 incluso cuando debia restaurarse un modo/frecuencia guardado distinto.
- Corregida la perdida de la primera respuesta dirigida FT2 mientras CQ estaba activo.
- Corregidos contadores retry/miss AutoCQ sucios que provocaban cambios prematuros de partner.
- Corregida la gestion de lineas FT2 async que hacia trim de la formateacion de columnas fijas/timestamp.
- Corregido el diagnostico astronomico mostrando explicitamente los paths `JPLEPH` buscados.

## [1.4.8] - 2026-03-15

Previous stable cycle. See tag `v1.4.8` and release notes for the prior detailed changelog.
