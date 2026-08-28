# `KnotenRegulaer.h`

Generische Hilfsklasse `Knoten<Typ>`, die als Grundbaustein für alle verketteten Datenstrukturen dient. Der Knoten verwaltet einen Inhalt (`Typ`) und einen Zeiger auf den Nachfolger (`std::shared_ptr`). Kopieren ist explizit deaktiviert; nur Move-Semantik ist erlaubt.

## Objekt erstellen

```cpp
#include "KnotenRegulaer.h"

Knoten<int> knotenLeer;          // Standard-Konstruktor
Knoten<int> knotenMitInhalt(42); // Konstruktor mit Inhalt
```

## Methoden

| Methode | Argumente | Rückgabe | Beschreibung |
|---|---|---|---|
| `setzeInhalt` | `Typ pInhalt` | `void` | Überschreibt den gespeicherten Inhalt. |
| `gibInhalt` | – | `Typ` | Gibt den aktuellen Inhalt zurück. |
| `setzeNaechsten` | `std::shared_ptr<Knoten<Typ>> pNaechster` | `void` | Setzt den Zeiger auf den Nachfolger. |
| `gibNaechsten` | – | `std::shared_ptr<Knoten<Typ>>` | Gibt den Zeiger auf den Nachfolger zurück. |

## Beispiel

```cpp
#include <iostream>
#include "KnotenRegulaer.h"

int main() {
    auto erster = std::make_shared<Knoten<int>>(10);
    auto zweiter = std::make_shared<Knoten<int>>(20);

    erster->setzeNaechsten(zweiter);

    std::cout << erster->gibInhalt() << std::endl; // 10
    std::cout << erster->gibNaechsten()->gibInhalt() << std::endl; // 20
}
```
