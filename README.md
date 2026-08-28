# Datenstrukturen-CPP

In diesem Repo werden alle Datenstrukturen, die wir im Unterricht behandelt haben, in C++ umgesetzt. Da wir diese im Unterricht nur als Pseudocode behandeln, wird dies eine gute Übung sein.

> **Hinweis:** Ein großer Teil der Implementierung und Tests wurde mit KI-Unterstützung erstellt und überarbeitet.

---

## Inhaltsverzeichnis

- [Projektübersicht](#projektübersicht)
- [Dateiübersicht](#dateiübersicht)
  - [KnotenRegulaer.h](#knotenregulaerh)
  - [Stapel.h](#stapelh)
  - [verketteteListe.h](#verkettetelisteh)
  - [warteschlange.h](#warteschlangeh)
  - [testVerketteteListe.cpp](#testverkettetelistecpp)
  - [stapel_test_v1.cpp](#stapel_test_v1cpp)
  - [testStapel_v2.cpp](#teststapel_v2cpp)
- [Kompilieren & Ausführen](#kompilieren--ausführen)
- [Konventionen](#konventionen)

---

## Projektübersicht

Dieses Projekt ist eine Schulübung der Klasse 12TGI. Ziel ist es, die im Unterricht als Pseudocode vorgestellten klassischen Datenstrukturen in echtem C++-Code umzusetzen. Ein großer Teil des Codes wurde mit KI-Unterstützung erstellt und anschließend manuell korrigiert und getestet. Alle Implementierungen sind als **Header-Only-Bibliotheken** (`.h`) ausgeführt und nutzen moderne C++-Features wie Templates, Smart Pointer (`std::shared_ptr`) und Move-Semantik.

Folgende Datenstrukturen sind aktuell enthalten:

| Datenstruktur       | Datei                  | Prinzip       |
|---------------------|------------------------|---------------|
| Knoten (Hilfklasse) | `KnotenRegulaer.h`     | –             |
| Stapel (Stack)      | `Stapel.h`             | LIFO          |
| Verkettete Liste    | `verketteteListe.h`    | Sequenziell   |
| Warteschlange       | `warteschlange.h`      | FIFO          |

---

## Dateiübersicht

### `KnotenRegulaer.h`

Diese Datei definiert die generische Hilfsklasse `Knoten<Typ>`, die als Grundbaustein für alle anderen Datenstrukturen dient. Da ein Knoten von mehreren Datenstrukturen (Stapel, verkettete Liste usw.) benötigt wird, wurde er einmal zentral für das gesamte Projekt geschrieben.

Die Klasse ist eng am Klassendiagramm aus dem Unterricht orientiert und bietet:

- **Konstruktoren:** Standard-Konstruktor (leerer Knoten) und ein Konstruktor mit Inhalt.
- **Kopier-Schutz:** Kopier-Konstruktor und Kopier-Zuweisungsoperator sind explizit als `delete` markiert, um unbeabsichtigtes Kopieren und damit verbundene Fehler zu verhindern. Nur Move-Semantik ist erlaubt.
- **Getter/Setter:** `setzeInhalt`, `gibInhalt`, `setzeNaechsten`, `gibNaechsten` – orientiert an der deutschen Schulkonvention.
- **Speicherverwaltung:** Der Zeiger auf den Nachfolge-Knoten ist als `std::shared_ptr<Knoten<Typ>>` realisiert, was automatisches Speichermanagement ermöglicht.

`#pragma once` verhindert Mehrfach-Inklusion.

---

### `Stapel.h`

Implementiert einen generischen **Stapel** (Stack) nach dem **LIFO-Prinzip** (Last In, First Out). Die Klasse `Stapel<Typ>` baut intern auf `KnotenRegulaer.h` auf und verwaltet die Elemente als einfach verkettete Liste mit einem `aAnfang`-Zeiger (Top des Stapels).

Wichtige Methoden:

| Methode        | Beschreibung                                                       |
|----------------|--------------------------------------------------------------------|
| `push(inhalt)` | Legt ein neues Element oben auf den Stapel.                        |
| `pop()`        | Entfernt das oberste Element und gibt seinen Inhalt zurück. Wirft `std::out_of_range`, wenn der Stapel leer ist. |
| `top()`        | Gibt den Inhalt des obersten Elements zurück, ohne es zu entfernen. Wirft `std::out_of_range` bei leerem Stapel. |
| `istLeer()`    | Gibt `true` zurück, wenn der Stapel keine Elemente enthält.        |

Auch hier ist das Kopieren des Stapels per `delete` deaktiviert.

---

### `verketteteListe.h`

Die umfangreichste Implementierung im Projekt: eine generische **einfach verkettete Liste** (`verketteteListe<Typ>`), ebenfalls aufbauend auf `KnotenRegulaer.h`. Sie unterstützt indexbasierte Zugriffe, Einfüge- und Löschoperationen an beliebigen Positionen sowie eine Suche nach Inhalt.

Wichtige Methoden:

| Methode                     | Beschreibung                                                                    |
|-----------------------------|---------------------------------------------------------------------------------|
| `einfuegen(index, inhalt)`  | Fügt ein Element an der angegebenen Position ein.                               |
| `einfuegenVorne(inhalt)`    | Fügt ein Element am Anfang der Liste ein (Kurzform für `einfuegen(0, ...)`).    |
| `anhaengen(inhalt)`         | Hängt ein Element ans Ende der Liste.                                           |
| `entfernen(index)`          | Entfernt das Element am gegebenen Index und gibt seinen Inhalt zurück.          |
| `entfernenVorne()`          | Entfernt das erste Element und gibt seinen Inhalt zurück.                       |
| `entfernenElement(inhalt)`  | Entfernt alle Knoten mit dem gegebenen Inhalt aus der Liste.                    |
| `inhalt(index)`             | Gibt den Inhalt an der angegebenen Position zurück.                             |
| `ersetzen(index, inhalt)`   | Überschreibt den Inhalt an der angegebenen Position.                            |
| `anzahlElemente()`          | Gibt die aktuelle Anzahl der Elemente zurück.                                   |
| `enthaelt(inhalt)`          | Gibt `true` zurück, wenn ein Element mit dem gegebenen Inhalt existiert.        |
| `istLeer()`                 | Gibt `true` zurück, wenn die Liste keine Elemente enthält.                      |

Ungültige Indexzugriffe werden mit `std::out_of_range` bzw. `std::invalid_argument` quittiert.

---

### `warteschlange.h`

Implementiert eine generische **Warteschlange** (Queue) nach dem **FIFO-Prinzip** (First In, First Out). Diese Datei enthält eine eigene lokale `Knoten`-Klasse (mit rohen Zeigern statt Smart Pointern) sowie die eigentliche Klasse `Warteschlange<Typ>`.

Die Warteschlange verwaltet intern zwei Zeiger: `kopf` (vorne) und `ende` (hinten). Der Destruktor löscht alle verbleibenden Knoten korrekt.

Wichtige Methoden:

| Methode            | Beschreibung                                                              |
|--------------------|---------------------------------------------------------------------------|
| `enqueue(inhalt)`  | Fügt ein neues Element am Ende der Warteschlange ein.                     |
| `dequeue()`        | Entfernt das vorderste Element und gibt seinen Inhalt zurück.             |
| `istLeer()`        | Gibt `true` zurück, wenn die Warteschlange leer ist (prüft `kopf`).       |
| `anzahlElemente()` | Gibt die aktuelle Anzahl der Elemente zurück.                             |

---

### `testVerketteteListe.cpp`

Ein einfaches, manuell geschriebenes Testprogramm für `verketteteListe.h`. Es legt eine Liste vom Typ `int` an und demonstriert die grundlegenden Operationen:

- Ein Element an Index 0 einfügen und dessen Inhalt ausgeben.
- Die Anzahl der Elemente abfragen.
- Ein weiteres Element anhängen und erneut die Anzahl sowie einen Inhalt ausgeben.
- Abschließende Bestätigung, dass das Programm erfolgreich durchgelaufen ist.

Dieses File dient primär als schneller Rauchtest ("Smoke Test") der Implementierung.

---

### `stapel_test_v1.cpp`

Testprogramm für `Stapel.h` (Version 1). Es enthält eine Template-Hilfsfunktion `run_test<T>`, die den Stapel mit zwei verschiedenen Typen (`std::string` und `int`) vollständig testet:

1. Überprüfung des Anfangszustands (Stapel muss leer sein).
2. Push mehrerer Elemente.
3. `top()`-Überprüfung (korrektes oberstes Element).
4. LIFO-Pop-Zyklus mit Vergleich der erwarteten Werte.
5. Exception-Handling: `pop()` auf leerem Stapel muss `std::out_of_range` werfen.
6. Exception-Handling: `top()` auf leerem Stapel muss `std::out_of_range` werfen.
7. Abschließende Leer-Überprüfung.

Jeder Test gibt `[PASS]` oder `[FAIL]` aus. Zu beachten: Diese Version enthält einen Sonderfall für `int`-Typen mit `reinterpret_cast`, der in neueren Versionen verbessert wurde.

---

### `testStapel_v2.cpp`

Testprogramm für `Stapel.h` (Version 2, überarbeitete Fassung). Ebenfalls eine Template-Hilfsfunktion (`run_stapel_test<T>`), diesmal mit korrekter direkter Integer-Initialisierung (kein `reinterpret_cast`). Der Testablauf ist noch vollständiger als in Version 1:

1. Anfangszustand prüfen (leer).
2. Drei Elemente pushen (statt zwei).
3. `top()` prüfen (muss das zuletzt gepushte Element sein).
4. Zwei Elemente poppen und LIFO-Reihenfolge verifizieren.
5. `top()` des verbliebenen Elements prüfen.
6. Exception bei `pop()` auf (jetzt) leerem Stapel.
7. Exception bei `top()` auf leerem Stapel.
8. Endzustand prüfen (leer).

Getestet werden `std::string` und `int`. Diese Version ist konsistenter und besser lesbar als die erste.

---

## Kompilieren & Ausführen

Da alle Datenstrukturen als Header-Only-Bibliotheken vorliegen, genügt es, die jeweilige Testdatei zusammen mit den benötigten Headern zu kompilieren. Beispiel mit g++:

```bash
# Stapel testen (Version 2)
g++ -std=c++17 -o testStapel testStapel_v2.cpp && ./testStapel

# Stapel testen (Version 1)
g++ -std=c++17 -o testStapel testStapel_v1.cpp && ./testStapel

# Verkettete Liste testen
g++ -std=c++17 -o testListe testVerketteteListe.cpp && ./testListe
```

Es wird mindestens **C++17** benötigt.

---

## Konventionen

- **Sprache:** Methoden- und Variablennamen folgen der unseren Schulkonvention zur Namensgebung (z.B. `gibInhalt`, `setzeNaechsten`, `istLeer`).
- **Speicherverwaltung:** Bevorzugt werden `std::shared_ptr` und Move-Semantik; Kopier-Konstruktoren werden wo sinnvoll deaktiviert.
- **Fehlerbehandlung:** Ungültige Operationen werfen C++-Standardausnahmen (`std::out_of_range`, `std::invalid_argument`, `std::logic_error`).
- **KI-Einfluss:** Ein großer Teil des Codes und der Tests wurde mit KI-Unterstützung erstellt und anschließend manuell geprüft und korrigiert.
