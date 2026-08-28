# `verketteteListe.h`

Generische einfach verkettete Liste (`verketteteListe<Typ>`). Unterstützt indexbasierten Zugriff, Einfügen und Löschen an beliebigen Positionen sowie Suche nach Inhalt. Kopieren ist deaktiviert.

## Objekt erstellen

```cpp
#include "verketteteListe.h"

verketteteListe<int> liste;
verketteteListe<std::string> textListe;
```

## Methoden

| Methode | Argumente | Rückgabe | Beschreibung / Exception |
|---|---|---|---|
| `einfuegen` | `int pIndex`, `Typ pInhalt` | `void` | Fügt an Index `pIndex` ein. Wirft `std::invalid_argument` bei negativem Index oder zu großem Index. |
| `einfuegenVorne` | `Typ pInhalt` | `void` | Kurzform für `einfuegen(0, ...)`. |
| `anhaengen` | `Typ pInhalt` | `void` | Fügt am Ende ein. |
| `entfernen` | `int pIndex` | `Typ` | Entfernt das Element am Index und gibt seinen Inhalt zurück. Wirft `std::invalid_argument` bei ungültigem Index. |
| `entfernenVorne` | – | `Typ` | Entfernt das erste Element und gibt seinen Inhalt zurück. Wirft `std::logic_error`, wenn leer. |
| `entfernenElement` | `Typ pInhalt` | `void` | Entfernt alle Knoten mit dem gegebenen Inhalt. |
| `inhalt` | `int pIndex` | `Typ` | Gibt den Inhalt am Index zurück. Wirft `std::invalid_argument` oder `std::logic_error`. |
| `ersetzen` | `int pIndex`, `Typ pInhalt` | `void` | Überschreibt den Inhalt am Index. Wirft `std::invalid_argument` oder `std::logic_error`. |
| `anzahlElemente` | – | `int` | Aktuelle Anzahl der Elemente. |
| `enthaelt` | `Typ pInhalt` | `bool` | `true`, wenn das Element existiert. |
| `istLeer` | – | `bool` | `true`, wenn leer. |

## Beispiel

```cpp
#include <iostream>
#include "verketteteListe.h"

int main() {
    verketteteListe<int> liste;

    liste.einfuegenVorne(10);
    liste.anhaengen(20);

    std::cout << liste.inhalt(0) << std::endl; // 10
    std::cout << liste.anzahlElemente() << std::endl; // 2

    liste.entfernenVorne();
    std::cout << liste.inhalt(0) << std::endl; // 20
}
```
