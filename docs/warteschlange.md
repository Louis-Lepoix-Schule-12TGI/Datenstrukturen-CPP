# `warteschlange.h`

Implementiert eine generische Warteschlange (`Warteschlange<Typ>`) nach dem FIFO-Prinzip. Diese Datei enthält eine eigene lokale `Knoten`-Klasse mit rohen Zeigern (`Knoten<Typ>*`) sowie die Warteschlange mit zwei Zeigern `kopf` und `ende`.

## Objekt erstellen

```cpp
#include "warteschlange.h"

Warteschlange<int> warteschlange;
```

## Methoden

| Methode | Argumente | Rückgabe | Beschreibung / Hinweis |
|---|---|---|---|
| `enqueue` | `Typ pInhalt` | `void` | Fügt ein neues Element am Ende ein. |
| `dequeue` | – | `Typ` | Entfernt das vorderste Element und gibt seinen Inhalt zurück. |
| `istLeer` | – | `bool` | `true`, wenn `kopf` null ist; sonst `false`. |
| `anzahlElemente` | – | `int` | Aktuell immer `0` (nicht vollständig implementiert). |

## Beispiel

```cpp
#include <iostream>
#include "warteschlange.h"

int main() {
    Warteschlange<int> w;

    w.enqueue(1);
    w.enqueue(2);
    w.enqueue(3);

    while (!w.istLeer()) {
        std::cout << w.dequeue() << std::endl; // 1, 2, 3
    }
}
```
