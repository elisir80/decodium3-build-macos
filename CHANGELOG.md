# Changelog / Registro Modifiche

## [1.5.3] - 2026-03-22

### English

Release focused on CQRLOG interoperability, FT4/FT8 Wait Features behaviour, local version propagation, and new bundled German/French translations.

#### Added

- Added bundled German (`de`) and French (`fr`) UI translation packs.
- Added the helper `tools/generate_ts_translations.py` to rebuild missing TS bundles from the English base.

#### Changed

- The language menu now exposes only translations that are actually bundled in the app and falls back safely to English if a saved language is no longer available.
- Release defaults and documentation are aligned to semantic version `1.5.3`, including the experimental Hamlib Linux build default.

#### Fixed

- Fixed Linux `CQRLOG wsjtx remote` interoperability by restoring the historical UDP listen-port behaviour and using `WSJTX` as the compatibility client id.
- Fixed local rebuild version drift so changing `fork_release_version.txt` propagates to the compiled app after rebuild/reconfigure.
- Fixed FT4/FT8 `Wait Features + AutoSeq` so a busy or late partner reply now pauses the current TX cycle instead of transmitting over an active QSO.

### Italiano

Release focalizzata su interoperabilita' CQRLOG, comportamento `Wait Features` in FT4/FT8, propagazione versione locale e nuove traduzioni bundle in tedesco/francese.

#### Aggiunto

- Aggiunti i pacchetti traduzione UI bundle tedesco (`de`) e francese (`fr`).
- Aggiunto l'helper `tools/generate_ts_translations.py` per rigenerare i bundle TS mancanti a partire dalla base inglese.

#### Modificato

- Il menu lingue mostra ora solo traduzioni realmente incluse nell'app e ripiega in sicurezza sull'inglese se la lingua salvata non e' piu' disponibile.
- Default release e documentazione sono allineati alla semver `1.5.3`, incluso il default del build Linux sperimentale Hamlib.

#### Corretto

- Corretta l'interoperabilita' Linux con `CQRLOG wsjtx remote` ripristinando il comportamento storico della listen port UDP e usando `WSJTX` come client id di compatibilita'.
- Corretto il drift della versione nelle build locali, cosi' un cambio in `fork_release_version.txt` si propaga davvero all'app compilata dopo rebuild/reconfigure.
- Corretto `Wait Features + AutoSeq` in FT4/FT8: una risposta tardiva o una stazione occupata mette ora in pausa il ciclo TX corrente invece di trasmettere sopra un QSO attivo.

### Espanol

Release centrada en interoperabilidad CQRLOG, comportamiento `Wait Features` en FT4/FT8, propagacion de version local y nuevas traducciones bundle en aleman/frances.

#### Anadido

- Anadidos los paquetes de traduccion UI bundle aleman (`de`) y frances (`fr`).
- Anadido el helper `tools/generate_ts_translations.py` para regenerar los bundles TS ausentes a partir de la base inglesa.

#### Cambios

- El menu de idiomas muestra ahora solo traducciones realmente incluidas en la app y vuelve de forma segura a ingles si la lengua guardada ya no esta disponible.
- Los defaults de release y la documentacion quedan alineados a la semver `1.5.3`, incluido el default del build Linux experimental Hamlib.

#### Corregido

- Corregida la interoperabilidad Linux con `CQRLOG wsjtx remote` restaurando el comportamiento historico de la listen port UDP y usando `WSJTX` como client id de compatibilidad.
- Corregido el desfase de version en builds locales para que un cambio en `fork_release_version.txt` se propague de verdad a la app compilada tras rebuild/reconfigure.
- Corregido `Wait Features + AutoSeq` en FT4/FT8: una respuesta tardia o una estacion ocupada pausa ahora el ciclo TX actual en lugar de transmitir sobre un QSO activo.

## [1.5.1] - 2026-03-19

### English

Release focused on in-app update discovery, FT2/FT4/FT8 late-signoff correctness, AutoCQ direct-reply state-machine hardening, map cleanup while transmitting CQ, and PSK Reporter identity alignment.

#### Added

- Added in-app update checks against the GitHub Releases feed.
- Added a manual `Help > Check for updates...` action.
- Added direct asset selection for the updater so macOS and Linux users are taken to the best matching download.

#### Changed

- PSK Reporter program information now uses the exact application title-bar string.
- macOS/Linux release workflows and release documentation are aligned to semantic version `1.5.1`.
- macOS release helper script now defaults to publishing against `elisir80/decodium3-build-macos`.

#### Fixed

- Fixed late `73/RR73` handling after local signoff so completed QSOs log instead of repeating `73/RR73`.
- Fixed timeout-abandon paths so delayed final acknowledgements from the active partner can still recover and log correctly.
- Fixed stale DX partner reuse after returning to CQ.
- Fixed direct-caller transitions that decoded the caller but kept transmitting CQ instead of arming `Tx2`.
- Fixed the first direct FT2 reply reusing a stale report from the previous QSO instead of the current caller SNR.
- Fixed the live world map showing a false active QSO path while transmitting plain CQ.

### Italiano

Release focalizzata su updater interno, correttezza late-signoff FT2/FT4/FT8, hardening della state machine AutoCQ sulle direct reply, pulizia mappa durante il CQ e allineamento identita' PSK Reporter.

#### Aggiunto

- Aggiunto controllo aggiornamenti interno contro il feed GitHub Releases.
- Aggiunta voce manuale `Help > Check for updates...`.
- Aggiunta selezione diretta dell'asset corretto nell'updater per macOS e Linux.

#### Modificato

- Le informazioni programma inviate a PSK Reporter usano ora esattamente la stringa della barra del titolo.
- Workflow release macOS/Linux e documentazione release sono ora allineati alla semver `1.5.1`.
- Lo script helper release macOS usa ora di default il repo `elisir80/decodium3-build-macos`.

#### Corretto

- Corretto il trattamento dei `73/RR73` tardivi dopo il signoff locale, cosi' i QSO chiusi vanno a log invece di ripetere `73/RR73`.
- Corretti i path di abbandono per timeout, cosi' i final ack ritardati del partner attivo possono ancora essere recuperati e loggati.
- Corretto il riuso di partner DX stantii dopo il ritorno a CQ.
- Corretti i passaggi caller-diretto in cui il decode era valido ma l'app continuava a trasmettere CQ invece di armare `Tx2`.
- Corretto il primo reply FT2 diretto che riusava un report stantio del QSO precedente invece dell'SNR del caller corrente.
- Corretta la live world map che mostrava un falso collegamento attivo durante il CQ puro.

### Espanol

Release centrada en updater interno, correccion late-signoff FT2/FT4/FT8, endurecimiento de la maquina de estados AutoCQ sobre respuestas directas, limpieza del mapa durante CQ y alineacion de identidad PSK Reporter.

#### Anadido

- Anadida comprobacion de updates contra el feed GitHub Releases.
- Anadida accion manual `Help > Check for updates...`.
- Anadida seleccion directa del asset correcto en el updater para macOS y Linux.

#### Cambios

- La informacion de programa enviada a PSK Reporter usa ahora exactamente la cadena de la barra de titulo.
- Workflows release macOS/Linux y documentacion release alineados ahora con la semver `1.5.1`.
- El script helper de release macOS publica ahora por defecto contra `elisir80/decodium3-build-macos`.

#### Corregido

- Corregido el tratamiento de `73/RR73` tardios tras el signoff local para que los QSO completados vayan a log en lugar de repetir `73/RR73`.
- Corregidos los paths de abandono por timeout para que los final ack retrasados del partner activo todavia puedan recuperarse y logearse.
- Corregido el reuso de partner DX obsoleto tras volver a CQ.
- Corregidos los pasos de caller directo donde el decode era valido pero la app seguia transmitiendo CQ en vez de armar `Tx2`.
- Corregido el primer reply FT2 directo que reutilizaba un reporte obsoleto del QSO anterior en vez del SNR del caller actual.
- Corregido el live world map que mostraba un enlace activo falso durante CQ puro.

## [1.5.0] - 2026-03-19

### English

Release focused on FT8/FT4/FT2 QSO correctness, AutoCQ stability, FT2 Quick QSO evolution, startup audio recovery, decoder sync from upstream, and initial Decodium certificate infrastructure.

#### Added

- Added startup RX-audio recovery logic that can reopen configured audio streams and re-arm monitor state automatically.
- Added `lib/ft2/decode174_91_ft2.f90` and moved FT2 triggered decode to the dedicated FT2 LDPC decoder path.
- Added the `Quick QSO` UI toggle as an alias for FT2 `2 msg`.
- Added AutoCQ diagnostic tracing to `debug.txt`.
- Added Decodium certificate loading/autoload/status integration in the main window.
- Added `tools/generate_cert.py` to generate `.decodium` certificate files.

#### Changed

- Local UI version, release workflows, and GitHub release naming are now aligned to semantic version `1.5.0`.
- Shared LDPC decoders were aligned to the upstream Normalized Min-Sum refresh.
- FT2 Quick QSO flow was refactored to the current short schema with mixed-mode and backward-compatibility handling.
- Linux and macOS release documentation now covers Tahoe/Sequoia/Monterey/AppImage targets with startup guidance and platform requirements.

#### Fixed

- Fixed startup cases where audio devices were selected correctly but RX audio only started after reopening Audio Preferences.
- Fixed standard 5-message FT8/FT4/FT2 QSOs skipping the local final `73` when the other station sent `RR73`/`73` first.
- Fixed FT2 Quick QSO log timing, including missed log-after-own-73 paths.
- Fixed multiple AutoCQ duplicate-rework cases where the app could immediately call the same station again after a completed QSO.
- Fixed queue handoff carrying stale retry counters, reports, or DX state into the next caller.
- Fixed FT8 retry timeouts overcounting decode passes instead of real missed periods.
- Fixed world map / DX context staying on the last QSO after returning to CQ.

### Italiano

Release focalizzata su correttezza QSO FT8/FT4/FT2, stabilita' AutoCQ, evoluzione Quick QSO FT2, recovery audio all'avvio, sync decoder da upstream e infrastruttura iniziale certificati Decodium.

#### Aggiunto

- Aggiunta logica di recovery RX-audio all'avvio che puo' riaprire automaticamente gli stream configurati e riarmare il monitor.
- Aggiunto `lib/ft2/decode174_91_ft2.f90` e spostato il triggered decode FT2 sul decoder LDPC dedicato FT2.
- Aggiunto il toggle UI `Quick QSO` come alias del profilo FT2 `2 msg`.
- Aggiunto tracing diagnostico AutoCQ in `debug.txt`.
- Aggiunta integrazione certificati Decodium con load/autoload/stato nella finestra principale.
- Aggiunto `tools/generate_cert.py` per generare file certificato `.decodium`.

#### Modificato

- Versione UI locale, workflow release e naming release GitHub ora allineati alla semver `1.5.0`.
- Decoder LDPC condivisi allineati al refresh upstream Normalized Min-Sum.
- Il flow FT2 Quick QSO e' stato rifattorizzato nello schema corto corrente con gestione mixed-mode e backward compatibility.
- La documentazione release macOS/Linux ora copre target Tahoe/Sequoia/Monterey/AppImage con istruzioni avvio e requisiti piattaforma.

#### Corretto

- Corretti i casi di avvio in cui le periferiche audio erano selezionate correttamente ma l'RX partiva solo dopo aver riaperto Preferenze Audio.
- Corretti i QSO standard a 5 messaggi FT8/FT4/FT2 che saltavano il `73` finale locale quando il corrispondente mandava prima `RR73`/`73`.
- Corretti i tempi di log FT2 Quick QSO, inclusi i path che perdevano il log dopo il proprio `73`.
- Corretti molteplici casi AutoCQ di retrigger duplicato in cui l'app poteva richiamare subito lo stesso nominativo appena lavorato.
- Corretto l'handoff della queue che portava retry, report o stato DX sporchi nel caller successivo.
- Corretto il timeout retry FT8 che sovracontava i passaggi decode invece dei periodi realmente persi.
- Corretta la persistenza mappa mondo / contesto DX sull'ultimo QSO dopo il ritorno a CQ.

### Espanol

Release centrada en correccion de QSO FT8/FT4/FT2, estabilidad AutoCQ, evolucion Quick QSO FT2, recuperacion audio al arrancar, sincronizacion de decoders desde upstream e infraestructura inicial de certificados Decodium.

#### Anadido

- Anadida logica de recuperacion RX-audio al arranque capaz de reabrir automaticamente streams configurados y rearmar el monitor.
- Anadido `lib/ft2/decode174_91_ft2.f90` y movido el triggered decode FT2 al path LDPC dedicado FT2.
- Anadido el toggle UI `Quick QSO` como alias del perfil FT2 `2 msg`.
- Anadido tracing diagnostico AutoCQ en `debug.txt`.
- Anadida integracion de certificados Decodium con load/autoload/estado en la ventana principal.
- Anadido `tools/generate_cert.py` para generar ficheros `.decodium`.

#### Cambios

- Version UI local, workflows release y naming release GitHub alineados ahora con la semver `1.5.0`.
- Decoders LDPC compartidos alineados al refresh upstream Normalized Min-Sum.
- El flow FT2 Quick QSO fue refactorizado al esquema corto actual con manejo mixed-mode y backward compatibility.
- La documentacion release macOS/Linux cubre ahora Tahoe/Sequoia/Monterey/AppImage con guia de arranque y requisitos de plataforma.

#### Corregido

- Corregidos casos de arranque donde los dispositivos de audio estaban bien seleccionados pero RX solo empezaba tras reabrir Preferencias Audio.
- Corregidos QSO estandar de 5 mensajes FT8/FT4/FT2 que saltaban el `73` final local cuando la otra estacion enviaba antes `RR73`/`73`.
- Corregidos tiempos de log FT2 Quick QSO, incluidos paths que perdian el log tras el propio `73`.
- Corregidos varios casos AutoCQ de retrabajo duplicado en los que la app podia volver a llamar enseguida al mismo callsign.
- Corregido el handoff de cola que arrastraba retry, reportes o estado DX sucios al siguiente caller.
- Corregido el timeout retry FT8 que sobrecontaba pasadas decode en vez de periodos realmente perdidos.
- Corregida la persistencia del mapa mundo / contexto DX sobre el ultimo QSO despues de volver a CQ.

## [1.4.9] - 2026-03-17

Previous stable cycle. See the historical release notes for the prior detailed changelog.
