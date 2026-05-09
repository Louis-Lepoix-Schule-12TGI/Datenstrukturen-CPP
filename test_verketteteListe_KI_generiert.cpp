#include "verketteteListe.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// Einfache Assert-Makros für Tests
#define ASSERT_EQ(expected, actual) do { \
    if ((expected) != (actual)) { \
        cout << "TEST FAIL: Erwartet: " << (expected) << ", aber erhalten: " << (actual) << endl; \
        exit(1); \
    } \
} while(0)

#define ASSERT_FALSE(condition) do { \
    if (!(condition)) { \
        cout << "TEST FAIL: Bedingung sollte falsch sein, war aber wahr!" << endl; \
        exit(1); \
    } \
} while(0)

#define ASSERT_TRUE(condition) do { \
    if (condition) { \
        cout << "TEST FAIL: Bedingung sollte wahr sein, war aber falsch!" << endl; \
        exit(1); \
    } \
} while(0)

int main() {
    cout << "=== Test suite für verketteteListe ===" << endl;
    cout << endl;

    // -----------------------------------------------------------
    // Test 1: Einfache Anhängen-Operation
    // -----------------------------------------------------------
    cout << "--- Test: Anhängen von Elementen ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(10);
        liste.anhaengen(20);
        liste.anhaengen(30);
        
        ASSERT_EQ(3, liste.anzahlElemente());
        ASSERT_EQ(10, liste.inhalt(0));
        ASSERT_EQ(20, liste.inhalt(1));
        ASSERT_EQ(30, liste.inhalt(2));
        
        cout << "✓ Test Anhängen erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 2: Einfügen an bestimmten Position
    // -----------------------------------------------------------
    cout << "--- Test: Einfügen an Position ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(1);
        liste.anhaengen(2);
        liste.anhaengen(3);
        ASSERT_EQ(3, liste.anzahlElemente());
        ASSERT_EQ(1, liste.inhalt(0));
        ASSERT_EQ(2, liste.inhalt(1));
        ASSERT_EQ(3, liste.inhalt(2));
        
        // Einfügen an Position 1 (zwischen 1 und 2)
        liste.einfuegen(1, 99);
        
        ASSERT_EQ(4, liste.anzahlElemente());
        ASSERT_EQ(1, liste.inhalt(0));
        ASSERT_EQ(99, liste.inhalt(1));
        ASSERT_EQ(2, liste.inhalt(2));
        ASSERT_EQ(3, liste.inhalt(3));
        
        cout << "✓ Test Einfügen an Position erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 3: Einfügen vorne (einfuegenVorne)
    // -----------------------------------------------------------
    cout << "--- Test: Einfügen vorne ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(1);
        liste.anhaengen(2);
        ASSERT_EQ(2, liste.anzahlElemente());
        ASSERT_EQ(1, liste.inhalt(0));
        ASSERT_EQ(2, liste.inhalt(1));
        
        liste.einfuegenVorne(99);
        
        ASSERT_EQ(3, liste.anzahlElemente());
        ASSERT_EQ(99, liste.inhalt(0));
        ASSERT_EQ(1, liste.inhalt(1));
        ASSERT_EQ(2, liste.inhalt(2));
        
        cout << "✓ Test Einfügen vorne erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 4: Ersetzen von Elementen
    // -----------------------------------------------------------
    cout << "--- Test: Ersetzen von Elementen ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(10);
        liste.anhaengen(20);
        liste.anhaengen(30);
        
        ASSERT_EQ(10, liste.inhalt(1));
        liste.ersetzen(1, 999);
        ASSERT_EQ(999, liste.inhalt(1));
        
        cout << "✓ Test Ersetzen erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 5: Entfernen von Element (durch Index)
    // -----------------------------------------------------------
    cout << "--- Test: Entfernen durch Index ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(10);
        liste.anhaengen(20);
        liste.anhaengen(30);
        
        ASSERT_EQ(3, liste.anzahlElemente());
        
        // Entferne Element an Index 1 (Wert 20)
        int entfernterWert = liste.entfernen(1);
        ASSERT_EQ(20, entfernterWert);
        ASSERT_EQ(2, liste.anzahlElemente());
        ASSERT_EQ(10, liste.inhalt(0));
        ASSERT_EQ(30, liste.inhalt(1));
        
        cout << "✓ Test Entfernen durch Index erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 6: Entfernen vorne (entfernenVorne)
    // -----------------------------------------------------------
    cout << "--- Test: Entfernen vorne ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(10);
        liste.anhaengen(20);
        liste.anhaengen(30);
        
        ASSERT_EQ(3, liste.anzahlElemente());
        ASSERT_EQ(10, liste.inhalt(0));
        
        int entfernterWert = liste.entfernenVorne();
        ASSERT_EQ(10, entfernterWert);
        ASSERT_EQ(2, liste.anzahlElemente());
        ASSERT_EQ(20, liste.inhalt(0));
        ASSERT_EQ(30, liste.inhalt(1));
        
        cout << "✓ Test Entfernen vorne erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 7: Enthält-Operation
    // -----------------------------------------------------------
    cout << "--- Test: Enthält-Operation ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(10);
        liste.anhaengen(20);
        liste.anhaengen(30);
        
        ASSERT_TRUE(liste.enthaelt(20));
        ASSERT_FALSE(liste.enthaelt(5));
        ASSERT_TRUE(liste.enthaelt(10));
        
        cout << "✓ Test Enthält-Operation erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 8: Entfernen nach Inhalt (entfernenElement)
    // -----------------------------------------------------------
    cout << "--- Test: Entfernen nach Inhalt ---" << endl;
    {
        verketteteListe<int> liste;
        
        liste.anhaengen(10);
        liste.anhaengen(20);
        liste.anhaengen(30);
        liste.anhaengen(20); // Zweite 20 hinzufügen
        
        ASSERT_EQ(4, liste.anzahlElemente());
        liste.entfernenElement(20); // Entferne eine der 20er
        
        ASSERT_EQ(3, liste.anzahlElemente());
        
        cout << "✓ Test Entfernen nach Inhalt erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Test 9: Leere Liste
    // -----------------------------------------------------------
    cout << "--- Test: Leere Liste ---" << endl;
    {
        verketteteListe<int> liste;
        
        ASSERT_TRUE(liste.istLeer());
        ASSERT_EQ(0, liste.anzahlElemente());
        
        cout << "✓ Test Leere Liste erfolgreich" << endl;
    }
    cout << endl;

    // -----------------------------------------------------------
    // Alle Tests bestanden!
    // -----------------------------------------------------------
    cout << "=========================================================" << endl;
    cout << "Alle Tests für verketteteListe erfolgreich abgeschlossen!" << endl;
    cout << "=========================================================" << endl;
    
    return 0;
}
