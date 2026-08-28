# `testVerketteteListe.cpp`

Smoke-Test (manueller Schnelltest) für `verketteteListe.h`. Testet eine Liste vom Typ `int` mit grundlegenden Operationen.

## Was wird getestet?

- Einfügen an Index 0 (`einfuegen(0, 37)`)
- Inhaltsabfrage (`inhalt(0)`)
- Anzahl der Elemente (`anzahlElemente()`)
- Anhängen (`anhaengen(88)`)
- Erneute Abfrage von Inhalt und Anzahl
- Bestätigung des erfolgreichen Durchlaufs

## Kompilieren und Ausführen

```bash
g++ -std=c++17 -o testListe testVerketteteListe.cpp && ./testListe
```

## Erwartete Ausgabe

```
37
1
2
37
Das Programm lief bis zum Ende!
```
