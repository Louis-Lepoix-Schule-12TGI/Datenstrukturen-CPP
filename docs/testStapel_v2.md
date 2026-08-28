# `testStapel_v2.cpp`

Testprogramm für `Stapel.h` (Version 2, überarbeitete Fassung). Ebenfalls eine Template-Hilfsfunktion (`run_stapel_test<T>`), diesmal ohne `reinterpret_cast`. Der Testablauf ist vollständiger als in Version 1.

## Was wird getestet?

1. Anfangszustand prüfen (leer)
2. Drei Elemente pushen (`std::string` und `int`)
3. `top()` prüfen (muss zuletzt gepushtes Element sein)
4. Zwei Elemente poppen und LIFO-Reihenfolge verifizieren
5. `top()` des verbliebenen Elements prüfen
6. Exception bei `pop()` auf leerem Stapel
7. Exception bei `top()` auf leerem Stapel
8. Endzustand prüfen (leer)

## Kompilieren und Ausführen

```bash
g++ -std=c++17 -o testStapel testStapel_v2.cpp && ./testStapel
```

## Erwartete Ausgabe

Für jeden der 8 Schritte wird `[PASS]` oder `[FAIL]` ausgegeben, ergänzt durch `[INFO]`-Zeilen für die gepushten Werte. Am Ende muss `[PASS] Final state: Stack is correctly reported as empty.` erscheinen.
