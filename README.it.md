# Decodium 3 FT2 (Fork macOS) - v1.4.7

Fork mantenuto da **Salvatore Raccampo 9H1SR**.

Per la panoramica bilingue, vedere [README.md](README.md).

## Novita' v1.4.7 (`v1.4.6 -> v1.4.7`)

- Hardening runtime/decode FT2:
- guardia async Tx FT2 aumentata da `100 ms` a `300 ms`.
- aggiunto filtro false decode FT2 basato su validazione prefissi `cty.dat`.
- rendering FT2 `TΔ` riscritto con parsing strutturato, cosi' le colonne restano allineate anche con righe packed e marker variabili.
- normalizzazione marker FT2 mantenuta coerente quando nel flow compare `~`.
- Sequenziamento AutoCQ/QSO:
- lock partner attivo piu' rigoroso, per evitare takeover da altri caller durante QSO in corso.
- logica periodi mancati allineata al budget reale di `5` retry.
- stato stale dei periodi mancati azzerato non appena una risposta valida del caller/partner fa avanzare il QSO.
- dopo `73` confermato dal partner, AutoCQ torna a CQ invece di ritrasmettere un `RR73` extra.
- AutoSpot / DX Cluster / dashboard web:
- nuova sezione impostazioni per endpoint AutoSpot (`host`, `porta`, flag enable).
- finestra DX Cluster ora interrogata via nodo DxSpider telnet configurabile, non piu' tramite feed HamQTH fisso.
- migliorata gestione prompt telnet, fetch silenzioso `UNSET/DX`, fallback login e diagnostica submit/verify in `autospot.log`.
- dashboard/web app aggiornata con toggle AutoSpot, feedback comandi/auth piu' chiaro e preset per modo piu' stabili in save/apply.
- Correzioni desktop/runtime:
- la voce menu `Dati Astronomici` si deseleziona quando la finestra viene chiusa con la `X`.
- il dialogo impostazioni Linux mantiene scrollabili le pagine tab troppo alte, con pulsanti azione sempre raggiungibili.

## Target release

- Apple Silicon Tahoe
- Apple Silicon Sequoia
- Apple Intel Sequoia
- Apple Intel Monterey (sperimentale / best effort)
- Linux x86_64 AppImage

## Requisiti minimi Linux

- Architettura: `x86_64` (64 bit)
- CPU: dual-core 2.0 GHz o superiore
- RAM: minimo 4 GB (consigliati 8 GB)
- Spazio disco: almeno 500 MB liberi (AppImage + log + impostazioni)
- Runtime/software:
- Linux con `glibc >= 2.35` (classe Ubuntu 22.04 o successiva)
- supporto `libfuse2` / FUSE2
- stack audio ALSA, PulseAudio o PipeWire
- Integrazione stazione: hardware CAT/audio secondo setup radio

## Avvio consigliato AppImage su Linux

Per evitare problemi dovuti al filesystem in sola lettura delle AppImage, si consiglia di avviare Decodium estraendo prima l'AppImage e poi eseguendo il programma dalla cartella estratta.

Eseguire i seguenti comandi nel terminale:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## Comando macOS (quarantena)

Se Gatekeeper blocca l'avvio, eseguire:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Build locale

```bash
cmake --build build -j6
./build/ft2.app/Contents/MacOS/ft2
```

## Documentazione

- [README.en-GB.md](README.en-GB.md)
- [README.es.md](README.es.md)
- [RELEASE_NOTES_v1.4.7.md](RELEASE_NOTES_v1.4.7.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.7.md](doc/GITHUB_RELEASE_BODY_v1.4.7.md)
- [doc/README.it.md](doc/README.it.md)
