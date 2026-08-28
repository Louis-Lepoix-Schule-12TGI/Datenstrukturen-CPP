# Datenstrukturen-CPP

In diesem Repo werden alle Datenstrukturen, die wir im Unterricht behandelt haben, in C++ umgesetzt. Da wir diese im Unterricht nur als Pseudocode behandeln, wird dies eine gute Übung sein.

> **Hinweis:** Ein großer Teil der Implementierung und Tests wurde mit KI-Unterstützung erstellt und überarbeitet.

---

## Dokumentation

Die detaillierte Dokumentation zu jeder Datei befindet sich im Ordner `docs/`:

- [KnotenRegulaer.h](docs/KnotenRegulaer.md)
- [Stapel.h](docs/Stapel.md)
- [verketteteListe.h](docs/verketteteListe.md)
- [warteschlange.h](docs/warteschlange.md)
- [testVerketteteListe.cpp](docs/testVerketteteListe.md)
- [stapel_test_v1.cpp](docs/stapel_test_v1.md)
- [testStapel_v2.cpp](docs/testStapel_v2.md)

---

## Kompilieren & Ausführen

```bash
g++ -std=c++17 -o testStapel testStapel_v2.cpp && ./testStapel
g++ -std=c++17 -o testStapel testStapel_v1.cpp && ./testStapel
g++ -std=c++17 -o testListe testVerketteteListe.cpp && ./testListe
```

Es wird mindestens **C++17** benötigt.

---

## Konventionen

- **Sprache:** Methoden- und Variablennamen folgen der unseren Schulkonvention zur Namensgebung (z.B. `gibInhalt`, `setzeNaechsten`, `istLeer`).
- **Speicherverwaltung:** Bevorzugt werden `std::shared_ptr` und Move-Semantik; Kopier-Konstruktoren werden wo sinnvoll deaktiviert.
- **Fehlerbehandlung:** Ungültige Operationen werfen C++-Standardausnahmen (`std::out_of_range`, `std::invalid_argument`, `std::logic_error`).
