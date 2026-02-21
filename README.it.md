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
scripts/release-macos.sh v1.0.1 --publish --repo elisir80/decodium3-build-macos
```

## Memoria condivisa su macOS

Se compaiono errori legati ai limiti della memoria condivisa, controlla:

```bash
sysctl kern.sysv.shmmax kern.sysv.shmall
```

Per usare insieme FT2 e JTDX, usa i file forniti:

- `Darwin/com.ft2.jtdx.sysctl.plist`
- `Darwin/ReadMe_FT2_JTDX.txt`

## Documentazione

Note dettagliate disponibili in:

- `doc/README.en-GB.md`
- `doc/README.it.md`

## Licenza

Il progetto mantiene i termini GPLv3 ereditati dai componenti WSJT-X/Decodium
upstream. Vedi i materiali di licenza presenti nel sorgente.
