# `stapel_test_v1.cpp`

Testprogramm für `Stapel.h` (Version 1). Verwendet eine Template-Hilfsfunktion `run_test<T>`, die den Stapel mit `std::string` und `int` testet. Diese Version enthält einen Sonderfall für `int`-Typen mit `reinterpret_cast`.

## Was wird getestet?

1. Anfangszustand (Stapel muss leer sein)
2. Push mehrerer Elemente (`std::string` und `int`)
3. `top()`-Überprüfung
4. LIFO-Pop-Zyklus
5. Exception bei `pop()` auf leerem Stapel (`std::out_of_range`)
6. Exception bei `top()` auf leerem Stapel (`std::out_of_range`)
7. Abschließende Leer-Überprüfung

## Kompilieren und Ausführen

```bash
g++ -std=c++17 -o testStapel stapel_test_v1.cpp && ./testStapel
```

## Erwartete Ausgabe

Für jeden Testschritt wird `[PASS]` oder `[FAIL]` ausgegeben. Am Ende sollte für beide Typen (`string`, `int`) der Stapel als leer bestätigt werden und alle Exception-Tests als `[PASS]` markiert sein.
