#include "verketteteListe.h"
#include <iostream>

int main(){
    
    verketteteListe<int> meineVerketteteListe;

    //mit Knoten befüllen
    meineVerketteteListe.einfuegen(0,37);

    // Inhalt an Stelle 0 ausgeben
    std::cout << meineVerketteteListe.inhalt(0) << "\n";
    // Anzahl der Elemente ausgeben
    std::cout << meineVerketteteListe.inhalt(0) << "\n";

    meineVerketteteListe.anhaengen(88);

    std::cout << "Das Programm lief bis zum Ende! \n";
}