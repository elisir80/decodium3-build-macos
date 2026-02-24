# Decodium 3 FT2 (Fork macOS)

Fork mantenuto da **Salvatore Raccampo 9H1SR**.

## Descrizione del progetto

Questo progetto e' un fork orientato a macOS del codice Decodium 3 FT2 /
derivazione WSJT-X. Include correzioni pratiche per build e runtime su macOS
moderni:

- miglioramenti di diagnostica e affidabilita' della memoria condivisa;
- packaging dei sottoprocessi (`jt9`, `wsprd`) dentro `ft2.app`;
- supporto alla coesistenza FT2 + JTDX su macOS;
- automazione release con artifact compatibili Sequoia/Tahoe.

## Baseline attuale

- Branch sorgente: `master`
- Ultima release stabile: `v1.1.0`
- Target compatibilita': macOS Sequoia (15.x), Tahoe (26.x), e Intel Sequoia (15.x)

## Novita' in v1.1.0

- Aggiunto recupero automatico auto-rebind dell'uscita audio su errori runtime transitori.
- Migliorata la stabilita' periferica audio in uscita trattando gli underrun come recuperabili.
- Migliorata la gestione UDP/interfacce di rete mantenendo visibili le interfacce selezionate anche se temporaneamente non disponibili.
- NTP reso piu' robusto (de-duplicazione query, validazione timestamp, filtro DNS stale, fallback piu' coerente).
- Aggiunta visualizzazione "eta' ultima sync" nella status bar NTP con tooltip stato piu' chiaro.
- Aggiunti limiti di compensazione clock DT configurabili per operazioni remote in `Impostazioni -> Avanzate`.
- Mantenuta automazione release dual-architecture (arm64 + x86_64 Intel).

## Avvio rapido (macOS)

```bash
cmake -S . -B build
cmake --build build -j8
open build/ft2.app
```

## Automazione Release

Usa lo script locale di release:

```bash
scripts/release-macos.sh v1.1.0 --publish --repo elisir80/decodium3-build-macos
```

Per avere un solo DMG compatibile sia con macOS Sequoia (15.x) sia con Tahoe
(26.x), esegui la build con:

```bash
scripts/release-macos.sh v1.1.0 --compat-macos 15.0
```

Importante: se compili in locale su Tahoe con librerie Homebrew compilate con
`minos 26.0`, il controllo compatibilita' puo' fallire intenzionalmente. In
questo caso usa la workflow GitHub `Release macOS (Sequoia+Tahoe)` (runner
`macos-15`) per generare DMG e PKG cross-versione.

La procedura di release genera:

- `decodium3-ft2-<version>-macos-<arch>.dmg`
- `decodium3-ft2-<version>-macos-<arch>.zip`
- `decodium3-ft2-<version>-macos-<arch>.pkg`
- `decodium3-ft2-<version>-sha256.txt`

Il pacchetto installer macOS (`.pkg`) installa `ft2.app` e configura
automaticamente i valori sysctl della memoria condivisa (`shmmax`/`shmall`)
necessari per FT2/JTDX.

## Se macOS blocca il PKG

Se Gatekeeper blocca l'installer (`non puo' essere aperto perche' Apple non
puo' verificarlo`), fai cosi':

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
xattr -dr com.apple.quarantine /percorso/decodium3-ft2-<version>-macos-arm64.pkg
open /percorso/decodium3-ft2-<version>-macos-arm64.pkg
```

Se `ft2.app` non si avvia dopo l'installazione, esegui:

```bash
xattr -r -d com.apple.quarantine /Applications/ft2.app
```

## Memoria condivisa su macOS

Se compaiono errori legati ai limiti della memoria condivisa, controlla:

```bash
sysctl kern.sysv.shmmax kern.sysv.shmall
```

Profilo consigliato per coesistenza FT2 + JTDX:

- `kern.sysv.shmmax=104857600`
- `kern.sysv.shmall=51200`

File di riferimento:

- `Darwin/com.ft2.jtdx.sysctl.plist`
- `Darwin/ReadMe_FT2_JTDX.txt`
- `Darwin/ft2-pkg-postinstall.sh`

## Changelog

Vedi `CHANGELOG.md`.

## Documentazione

Note dettagliate disponibili in:

- `doc/README.en-GB.md`
- `doc/README.it.md`

## Licenza

Il progetto mantiene i termini GPLv3 ereditati dai componenti WSJT-X/Decodium
upstream. Vedi i materiali di licenza presenti nel sorgente.
