# Note di Documentazione (Italiano) - 1.5.2

Questo indice raccoglie la documentazione di rilascio del ciclo corrente del fork.

- Release corrente: `1.5.2`
- Ciclo aggiornamento: `1.5.1 -> 1.5.2`
- Focus principale: aggiornamenti decoder/protocollo FT2, correttezza AutoCQ e Wait Features, recovery audio all'avvio, parita' web app, traduzioni UI complete e allineamento versione/release.

## Cambi Tecnici Principali (`1.5.1 -> 1.5.2`)

- refresh decoder FT2 con path LDPC FT2 dedicato upstream e supporto bitmetrics FT2 aggiornato.
- completamento flow FT2 `Quick QSO` / `2 msg / 3 msg / 5 msg` con gestione TU mixed-mode.
- ripristino lock QSO attivo `Wait Features + AutoSeq` per FT4/FT8.
- recovery RX-audio all'avvio e al wake agganciato alla reale attivazione del monitor.
- estensione parita' web app/dashboard con Manual TX, Speedy, D-CW, async, Quick QSO e controlli 2/3/5 messaggi.
- completamento traduzioni UI bundle e rimozione dei tag async FT2 visibili dalle decode panes.
- centralizzazione versioning release tramite `fork_release_version.txt`.

## Artifact Release

- `decodium3-ft2-1.5.2-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.2-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.2-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.2-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.2-linux-x86_64.AppImage.sha256.txt`

## Requisiti Minimi Linux

- `x86_64`, dual-core 2.0 GHz+, 4 GB RAM minima, 500 MB liberi
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guida Avvio

Quarantena macOS:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Flusso Linux AppImage extract-run:

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
- [RELEASE_NOTES_1.5.2.md](../RELEASE_NOTES_1.5.2.md)
- [doc/GITHUB_RELEASE_BODY_1.5.2.md](./GITHUB_RELEASE_BODY_1.5.2.md)
- [CHANGELOG.md](../CHANGELOG.md)
