# Changelog / Registro Modifiche

## [1.4.8] - 2026-03-15

### English

Release focused on FT2 timing/operator refinements, FT2 signoff correctness, remote-web hardening, bounded string safety, and stronger release packaging robustness.

#### Added

- Added FT2 `Speedy`, `D-CW`, and `TX NOW` operator workflow support.
- Added WebSocket `Origin` validation for the remote dashboard/server channel.

#### Changed

- FT2 symbol count aligned from `105` to `103`.
- FT2 Tx duration margin reduced from `0.5 s` to `0.2 s` above waveform duration.
- FT2 auto-sequence now uses an FT2-specific enable path even when the legacy AutoSeq checkbox is hidden.
- macOS release packaging now tolerates leftover CPack DMG mounts when staged output is already valid.
- Release/build/workflow defaults aligned to `v1.4.8`.

#### Fixed

- Fixed premature FT2 auto-log before a real partner final `73/RR73` acknowledgment.
- Fixed FT2 signoff retry exhaustion so the QSO stops cleanly without being logged.
- Fixed FT2 duplicate same-payload hypotheses appearing multiple times across nearby audio bins.
- Fixed non-loopback remote server exposure without token or with too-short token.
- Fixed permissive wildcard CORS on the remote HTTP API.
- Fixed concrete COM port formatting overflow risk in `lib/ptt.c`.
- Fixed related unsafe formatting in `lib/ft2`, `map65` PTT, device-info, status-label, and astronomical text paths.

### Italiano

Release focalizzata su rifiniture timing/operator FT2, correttezza signoff FT2, hardening remote web, sicurezza bounded sulle stringhe e maggiore robustezza del packaging release.

#### Aggiunto

- Aggiunto supporto workflow operatore FT2 `Speedy`, `D-CW` e `TX NOW`.
- Aggiunta validazione `Origin` WebSocket per il canale dashboard/server remoto.

#### Modificato

- Conteggio simboli FT2 allineato da `105` a `103`.
- Margine durata Tx FT2 ridotto da `0.5 s` a `0.2 s` sopra la durata d'onda.
- Auto-sequence FT2 ora usa un path dedicato FT2 anche con checkbox AutoSeq legacy nascosta.
- Il packaging release macOS tollera ora mount DMG residui di CPack quando lo staging e' gia' valido.
- Default release/build/workflow allineati a `v1.4.8`.

#### Corretto

- Corretto auto-log FT2 anticipato prima di un vero ack finale `73/RR73` del partner.
- Corretto esaurimento retry signoff FT2: il QSO si ferma pulito senza essere loggato.
- Corrette ipotesi duplicate FT2 con stesso payload su bin audio vicini.
- Corretta esposizione del server remoto non-loopback senza token o con token troppo corto.
- Corretto wildcard CORS permissivo sull'API HTTP remota.
- Corretto rischio concreto di overflow nella formattazione porta COM in `lib/ptt.c`.
- Corretta formattazione unsafe correlata in `lib/ft2`, PTT `map65`, device-info, label di stato e testo astronomico.

### Espanol

Release centrada en refinamientos timing/operator FT2, correccion signoff FT2, hardening remote web, seguridad bounded de cadenas y mas robustez del packaging release.

#### Anadido

- Anadido soporte de workflow operador FT2 `Speedy`, `D-CW` y `TX NOW`.
- Anadida validacion `Origin` WebSocket para el canal remoto dashboard/server.

#### Cambios

- Conteo de simbolos FT2 alineado de `105` a `103`.
- Margen de duracion Tx FT2 reducido de `0.5 s` a `0.2 s` sobre la duracion de onda.
- Auto-sequence FT2 usa ahora una ruta dedicada FT2 incluso con la checkbox AutoSeq legacy oculta.
- El packaging release macOS tolera ahora mounts DMG residuales de CPack cuando el staging ya es valido.
- Defaults de release/build/workflows alineados a `v1.4.8`.

#### Corregido

- Corregido auto-log FT2 prematuro antes de un verdadero ack final `73/RR73` de la pareja.
- Corregido agotamiento de reintentos signoff FT2: el QSO se detiene limpio sin quedar en log.
- Corregidas hipotesis duplicadas FT2 con el mismo payload en bins de audio cercanos.
- Corregida exposicion del servidor remoto non-loopback sin token o con token demasiado corto.
- Corregido wildcard CORS permisivo en el API HTTP remoto.
- Corregido riesgo concreto de overflow en el formateo de puerto COM en `lib/ptt.c`.
- Corregido formateo unsafe relacionado en `lib/ft2`, PTT `map65`, device-info, labels de estado y texto astronomico.

## [1.4.7] - 2026-03-15

Previous stable cycle. See tag `v1.4.7` and release notes for the prior detailed changelog.
