# Decodium 3 FT2 (Fork macOS)

Fork mantenuto da **Salvatore Raccampo 9H1SR**.

## Descrizione del progetto

Questo progetto e' un fork orientato a macOS del codice Decodium 3 FT2 /
derivazione WSJT-X. Include correzioni pratiche per build e runtime su macOS
moderni:

- miglioramenti su diagnostica e stabilita' della memoria condivisa;
- packaging dei sottoprocessi (`jt9`, `wsprd`) dentro `ft2.app`;
- file e istruzioni per la coesistenza FT2 + JTDX su macOS.

## Baseline attuale

- Branch sorgente: `master`
- Prima baseline taggata in questo fork: `v1.0`

## Avvio rapido (macOS)

```bash
cmake -S . -B build
cmake --build build -j8
open build/ft2.app
```

## Automazione Release

Usa lo script locale di release:

```bash
scripts/release-macos.sh v1.0.3 --publish --repo elisir80/decodium3-build-macos
```

Per avere un solo DMG compatibile sia con macOS Sequoia (15.x) sia con Tahoe
(26.x), esegui la build con:

```bash
scripts/release-macos.sh v1.0.3 --compat-macos 15.0
```

Importante: se compili in locale su Tahoe con librerie Homebrew compilate con
`minos 26.0`, il controllo compatibilita' fallira' intenzionalmente. In questo
caso usa la workflow GitHub `Release macOS (Sequoia+Tahoe)` (runner `macos-15`)
per generare un DMG cross-versione.

La procedura di release ora genera anche un pacchetto installer macOS (`.pkg`) che:

- installa `ft2.app` in `/Applications`;
- installa e carica `com.ft2.jtdx.sysctl.plist` in `/Library/LaunchDaemons`;
- applica i valori sysctl della memoria condivisa richiesti da FT2 (`shmmax`/`shmall`).

## Se macOS blocca il PKG

Se Gatekeeper blocca l'installer (`non puo' essere aperto perche' Apple non puo'
verificarlo`), fai cosi':

1. Apri `Impostazioni di Sistema` -> `Privacy e sicurezza`.
2. Scorri nella sezione Sicurezza e trova il messaggio relativo al pkg bloccato.
3. Clicca `Apri comunque`.
4. Conferma con password/Touch ID.
5. Riapri il file pkg.

Metodo alternativo:

1. In Finder, fai click destro sul file `.pkg`.
2. Clicca `Apri`.
3. Conferma `Apri` nel messaggio di avviso.

Fallback da terminale (solo utenti esperti):

```bash
xattr -dr com.apple.quarantine /percorso/decodium3-ft2-v1.0.3-macos-arm64.pkg
open /percorso/decodium3-ft2-v1.0.3-macos-arm64.pkg
```

## Memoria condivisa su macOS

Se compaiono errori legati ai limiti della memoria condivisa, controlla:

```bash
sysctl kern.sysv.shmmax kern.sysv.shmall
```

Per usare insieme FT2 e JTDX, usa i file forniti:

- `Darwin/com.ft2.jtdx.sysctl.plist`
- `Darwin/ReadMe_FT2_JTDX.txt`
- `Darwin/ft2-pkg-postinstall.sh`

## Documentazione

Note dettagliate disponibili in:

- `doc/README.en-GB.md`
- `doc/README.it.md`

## Licenza

Il progetto mantiene i termini GPLv3 ereditati dai componenti WSJT-X/Decodium
upstream. Vedi i materiali di licenza presenti nel sorgente.
