#include "verketteteListe.h"
#include <iostream>

int main(){
    
    verketteteListe<int> meineVerketteteListe;

    //mit Knoten befüllen
    meineVerketteteListe.einfuegen(0,37);

    // Inhalt an Stelle 0 ausgeben
    std::cout << meineVerketteteListe.inhalt(0) << "\n";
    // Anzahl der Elemente ausgeben
    std::cout << meineVerketteteListe.anzahlElemente() << "\n";

    //Element anhängen (zu Stelle 1)
    meineVerketteteListe.anhaengen(88);

    // Anzahl der Elemente ausgeben
    std::cout << meineVerketteteListe.anzahlElemente() << "\n";
    // Inhalt an Stelle 1 ausgeben
    std::cout << meineVerketteteListe.inhalt(0) << "\n";

    std::cout << "Das Programm lief bis zum Ende! \n";
}