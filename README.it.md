# Decodium 3 FT2 (Fork macOS) - v1.4.8

Fork mantenuto da **Salvatore Raccampo 9H1SR**.

Per la panoramica bilingue, vedere [README.md](README.md).

## Novita' v1.4.8 (`v1.4.7 -> v1.4.8`)

- FT2 timing e workflow operatore:
- `NUM_FT2_SYMBOLS` allineato da `105` a `103` e margine Tx FT2 ridotto da `0.5 s` a `0.2 s` sopra la durata d'onda.
- aggiunto supporto FT2 per workflow `Speedy`, `D-CW` e pulsante `TX NOW` per invio immediato o pre-caricato.
- la logica AutoSeq FT2 resta coerente anche quando la checkbox AutoSeq standard e' nascosta nell'interfaccia FT2.
- Correttezza QSO/signoff FT2:
- FT2 non manda piu' il QSO a log prima che il `73` locale sia stato effettivamente trasmesso e il partner abbia inviato l'ack finale.
- se FT2 esaurisce il budget retry su `RR73/73` senza ack finale del partner, la trasmissione viene fermata senza log automatico.
- la gestione di `RR73/73` del partner non salta piu' il `73` locale nelle sequenze FT2 AutoCQ/auto-sequence.
- il dedupe async FT2 ora sopprime ipotesi duplicate con lo stesso payload anche su bin audio vicini, evitando scambi sdoppiati nel flow decode.
- Hardening Remote Web / dashboard:
- RemoteCommandServer ora viene bloccato su bind non-loopback se manca il token di accesso.
- su bind non-loopback il token deve avere almeno `12` caratteri.
- rimosso il wildcard CORS dall'API HTTP remota.
- le connessioni WebSocket ora richiedono un `Origin` same-origin ammesso, invece di accettare origini browser arbitrarie.
- Sicurezza stringhe/buffer:
- corretto il rischio concreto di overflow nella formattazione porta COM in `lib/ptt.c`.
- applicata formattazione bounded anche ai moduli PTT correlati in `lib/ft2` e `map65`.
- induriti i path `map65` per device-info, label di stato e testo astronomico.
- Pipeline release/build:
- il packaging macOS ora tollera mount DMG residui di CPack senza fallire l'intera release se lo staging e' valido.

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
- [RELEASE_NOTES_v1.4.8.md](RELEASE_NOTES_v1.4.8.md)
- [CHANGELOG.md](CHANGELOG.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.8.md](doc/GITHUB_RELEASE_BODY_v1.4.8.md)
- [doc/README.it.md](doc/README.it.md)
