# `Stapel.h`

Implementiert einen generischen Stapel (`Stapel<Typ>`) nach dem LIFO-Prinzip. Intern wird eine einfach verkettete Liste mit einem `aAnfang`-Zeiger (Top) verwendet. Kopieren des Stapels ist deaktiviert.

## Objekt erstellen

```cpp
#include "Stapel.h"

Stapel<int> meinStapel;
Stapel<std::string> textStapel;
```

## Methoden

| Methode | Argumente | Rückgabe | Beschreibung / Exception |
|---|---|---|---|
| `push` | `Typ pInhalt` | `void` | Legt ein neues Element oben auf den Stapel. |
| `pop` | – | `Typ` | Entfernt das oberste Element und gibt seinen Inhalt zurück. Wirft `std::out_of_range`, wenn leer. |
| `top` | – | `Typ` | Gibt den Inhalt des obersten Elements zurück, ohne es zu entfernen. Wirft `std::out_of_range`, wenn leer. |
| `istLeer` | – | `bool` | `true`, wenn der Stapel keine Elemente enthält. |

## Beispiel

```cpp
#include <iostream>
#include <string>
#include "Stapel.h"

int main() {
    Stapel<int> s;

    s.push(5);
    s.push(10);

    std::cout << s.top() << std::endl; // 10

    int wert = s.pop(); // 10
    std::cout << wert << std::endl;

    std::cout << s.istLeer() << std::endl; // false
    s.pop();
    std::cout << s.istLeer() << std::endl; // true
}
```
