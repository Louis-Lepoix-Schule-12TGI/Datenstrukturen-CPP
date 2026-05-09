#include "KnotenRegulaer.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#pragma once //verhindert mehrfache inklusion

template<typename Typ>
class verketteteListe{
    public:
    verketteteListe() = default;
    ~verketteteListe() = default;

    //Sicherung mit Kopieregeln
    verketteteListe(const verketteteListe&) = delete;
    verketteteListe& operator=(const verketteteListe&) = delete;


    void indexZuGrossTester(int pIndex, int& i, std::unique_ptr<Knoten<Typ>>& aktuellerKnoten){
    if(aktuellerKnoten->get().gibNaechsten() == nullptr && pIndex > i){
        //Error werfen - wir sind am Ende und haben den Index noch nicht erreicht
        std::string errorNachricht = "Fehler: Der Index ist zu groß. Gegebenen Index: " + 
                                      std::to_string(pIndex) + ". Höchster Index: " + 
                                      std::to_string(i);
        throw std::out_of_range(errorNachricht);
    }
}



    std::unique_ptr<Knoten<Typ>> knotenWaehler(int pIndex){
        /*
        Tut einen Pointer, welcher zum Knoten an der Stelle pIndex zeigt, zurückgeben 
        */

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index ausgewaehlt werden");
        }

        std::unique_ptr<Knoten<Typ>> aktuellerKnoten = aAnfang;
        std::unique_ptr<Knoten<Typ>> zielKnoten = nullptr;

        for(int i = 0; i < pIndex; i++){ //For-loop endet, wenn aktuellerKnoten auf den Ziel-Knoten gesetz wurde 
            
            //Falls der Index zu groß ist
            indexZuGrossTester(pIndex, i, aktuellerKnoten); 
            aktuellerKnoten->get().setzeNaechsten(aktuellerKnoten->get().gibNaechsten()); //aktuellen Knoten auf nächsten Knoten setzen
        
        }
        

        zielKnoten = aktuellerKnoten;
        
        return zielKnoten;

    }

    bool istLeer() const {
        return aAnfang.get() == nullptr;
    }

    int anzahlElemente(){
        int anzahl = 0;
        std::unique_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang;
        Knoten<Typ> aktuellerKnoten = aktuellerZeiger->get();
        while(aktuellerZeiger.get() != nullptr){
            aktuellerZeiger = aktuellerKnoten.gibNaechsten();
            aktuellerKnoten = aktuellerZeiger->get();
            anzahl++;
        }
        return anzahl;
    }

    Typ inhalt(int pIndex) const{
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        std::unique_ptr<Knoten<Typ>> aktuellerKnoten = knotenWaehler(pIndex);

        return aktuellerKnoten->get().gibInhalt(); //gibt den Inhalt an der Stelle von pIndex zurück
    }

    void ersetzen(int pIndex, Typ pInhalt){
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        std::unique_ptr<Knoten<Typ>> derKnoten = knotenWaehler(pIndex);
        derKnoten->get().setzeInhalt(pInhalt);
    };

    void einfuegen(int pIndex, Typ pInhalt){
        auto zeigerZuNeuemKnoten = std::make_unique<Knoten<Typ>>(pInhalt); 

        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }else if(pIndex == 0){
            aAnfang = std::move(zeigerZuNeuemKnoten);
            return;
        }

        if(pIndex > anzahlElemente()){
            throw std::invalid_argument("Fehler: Der Index ist zu gross.");
        }
       

        std::unique_ptr<Knoten<Typ>> voherigerKnoten = knotenWaehler(pIndex-1);
        voherigerKnoten->get().setzeNaechsten(zeigerZuNeuemKnoten);


        if(pIndex < anzahlElemente()){
            std::unique_ptr<Knoten<Typ>> nachfolgenderKnoten = knotenWaehler(pIndex);
            zeigerZuNeuemKnoten->get().setzeNaechsten(nachfolgenderKnoten);
        }else if(pIndex == anzahlElemente()){
            voherigerKnoten->get().setzeNaechsten(zeigerZuNeuemKnoten);
        }
        
    };

    void einfuegenVorne(Typ pInhalt){
        einfuegen(0, pInhalt);
    };

    void anhaengen(Typ pInhalt){
        einfuegen(anzahlElemente(), pInhalt);
    }

    Typ entfernen(int pIndex){
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(pIndex >= anzahlElemente()){
            throw std::invalid_argument("Fehler: Der Index ist zu gross.");
        }

        if(pIndex == 0){ //edgecase
            Typ tmpInhalt = aAnfang->get().gibInhalt();
            aAnfang = std::move(aAnfang->get().gibNaechsten());
            return tmpInhalt;
        }

        std::unique_ptr voherigerKnoten = knotenWaehler(pIndex-1);
        std::unique_ptr rueckgabeKnoten = knotenWaehler(pIndex);

        //Zeiger "aNaechster" vom voherigen Knoten vom Rückgabe-Knoten entfernen
        if(rueckgabeKnoten->get().gibNaechsten() != nullptr){
            std::unique_ptr folgeKnoten = knotenWaehler(pIndex+1);
            voherigerKnoten->get().setzeNaechsten(folgeKnoten);
        }else{
            voherigerKnoten->get().setzeNaechsten(nullptr);
        }

        return rueckgabeKnoten;
    };

    Typ entfernenVorne(){
        if (istLeer()) {
            throw std::logic_error("Fehler: Der Stapel ist leer. Es gibt nichts zum entfernen");
        }
        Typ rueckgabe = aAnfang->gibInhalt();

        aAnfang = std::move(aAnfang->aNaechster);
        
        return rueckgabe;
    }

    bool enthaelt(Typ pInhalt){
        if (istLeer()) {
            return false;
        }
        
        std::unique_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang;
        Knoten<Typ> aktuellerKnoten = aktuellerZeiger->get();

        while(aktuellerZeiger.get() != nullptr){
            aktuellerZeiger = aktuellerKnoten.gibNaechsten();
            aktuellerKnoten = aktuellerZeiger->get();
            if(aktuellerKnoten.gibInhalt() == pInhalt){
                return true;
            }
        }
        return false;
    }

    void entfernenElement(Typ pInhalt){
        std::unique_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang;
        std::unique_ptr<Knoten<Typ>> voherigerZeiger;

        int zaehler = 0;

        while(aktuellerZeiger.get() != nullptr){
            if(aktuellerZeiger->get().gibInhalt() == pInhalt){
                voherigerZeiger->get().setzeNaechsten(aktuellerZeiger->get().gibNaechsten());
            }
            voherigerZeiger = aktuellerZeiger;
            aktuellerZeiger = aktuellerZeiger->get().gibNaechsten();

            zaehler++;
        }
    }
    
    private:
    std::unique_ptr<Knoten<Typ>> aAnfang;
};
