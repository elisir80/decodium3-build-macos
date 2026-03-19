# Note di Documentazione (Italiano) - 1.5.0

Questo indice raccoglie la documentazione release-oriented del ciclo corrente del fork.

- Release corrente: `1.5.0`
- Ciclo aggiornamento: `1.4.9 -> 1.5.0`
- Focus principale: recovery audio all'avvio, correttezza QSO FT8/FT4/FT2, stabilita' AutoCQ, Quick QSO FT2, sync decoder e tooling certificati.

## Cambi Tecnici Principali (`1.4.9 -> 1.5.0`)

- recovery automatico RX audio all'avvio quando le periferiche salvate sono presenti ma l'RX resta muto.
- fix del `73` finale in FT8, FT4 e FT2 standard.
- refactor FT2 Quick QSO e bottone `Quick QSO` agganciato a FT2 `2 msg`.
- prevenzione duplicate-rework AutoCQ, reset stato queue e conteggio retry su periodi reali.
- decoder LDPC dedicato FT2 e allineamento decoder condivisi Normalized Min-Sum.
- supporto certificati Decodium e tool `tools/generate_cert.py`.

## Artifact Release

- `decodium3-ft2-1.5.0-macos-tahoe-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64.zip`
- `decodium3-ft2-1.5.0-macos-tahoe-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-arm64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.dmg`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64.zip`
- `decodium3-ft2-1.5.0-macos-sequoia-x86_64-sha256.txt`
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.dmg` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64.zip` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.0-macos-monterey-x86_64-sha256.txt` *(best effort/sperimentale, se generato)*
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage`
- `decodium3-ft2-1.5.0-linux-x86_64.AppImage.sha256.txt`

## Requisiti Minimi Linux

- CPU `x86_64`, dual-core 2.0 GHz+
- RAM minima 4 GB (consigliati 8 GB)
- 500 MB liberi su disco
- `glibc >= 2.35`
- `libfuse2` / FUSE2
- ALSA, PulseAudio o PipeWire

## Guida Avvio

macOS quarantine:

```bash
sudo xattr -r -d com.apple.quarantine /Applications/ft2.app
```

Linux AppImage extract-run:

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
- [RELEASE_NOTES_1.5.0.md](../RELEASE_NOTES_1.5.0.md)
- [doc/GITHUB_RELEASE_BODY_1.5.0.md](./GITHUB_RELEASE_BODY_1.5.0.md)
- [CHANGELOG.md](../CHANGELOG.md)
