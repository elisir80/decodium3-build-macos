# Note di Documentazione (Italiano) - v1.4.8

Questo indice raccoglie la documentazione release-oriented del ciclo corrente del fork.

- Release corrente: `v1.4.8`
- Ciclo aggiornamento: `v1.4.7 -> v1.4.8`
- Focus principale: rifiniture timing/operator FT2, correttezza signoff FT2, hardening remoto web, fix bounded stringhe e robustezza release.

## Cambi Tecnici Principali (`v1.4.7 -> v1.4.8`)

- FT2 portato a `103` simboli con margine Tx ridotto a `0.2 s`.
- aggiunto supporto FT2 `Speedy`, `D-CW` e `TX NOW`.
- FT2 ora attende l'ack finale partner prima del log e interrompe pulito senza log se i retry finiscono.
- dedupe async FT2 piu' robusto contro ipotesi duplicate su bin vicini.
- remote web con token obbligatorio fuori loopback, niente wildcard CORS e validazione `Origin` WebSocket.
- fix bounded-formatting in `lib/ptt.c`, `lib/ft2` e diversi path `map65`.
- packaging release macOS piu' robusto contro mount DMG CPack residui.

## Artifact Release

- `decodium3-ft2-v1.4.8-macos-tahoe-arm64.dmg`
- `decodium3-ft2-v1.4.8-macos-tahoe-arm64.zip`
- `decodium3-ft2-v1.4.8-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64.dmg`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64.zip`
- `decodium3-ft2-v1.4.8-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64.zip`
- `decodium3-ft2-v1.4.8-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.8-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-v1.4.8-linux-x86_64.AppImage`
- `decodium3-ft2-v1.4.8-linux-x86_64.AppImage.sha256.txt`

## Requisiti Minimi Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM minima 4 GB (consigliati 8 GB)
- 500 MB liberi su disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guida Avvio

macOS quarantena:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage estrai-ed-esegui:

```bash
chmod +x /path/to/Decodium.AppImage
/path/to/Decodium.AppImage --appimage-extract
cd squashfs-root
./AppRun
```

## File Collegati

- [README.md](../README.md)
- [README.en-GB.md](../README.en-GB.md)
- [README.it.md](../README.it.md)
- [README.es.md](../README.es.md)
- [RELEASE_NOTES_v1.4.8.md](../RELEASE_NOTES_v1.4.8.md)
- [doc/GITHUB_RELEASE_BODY_v1.4.8.md](./GITHUB_RELEASE_BODY_v1.4.8.md)
- [CHANGELOG.md](../CHANGELOG.md)
