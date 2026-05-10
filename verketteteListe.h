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
    if(aktuellerKnoten.gibNaechsten() == nullptr && pIndex > i){
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

        std::unique_ptr<Knoten<Typ>> aktuellerKnoten = std::move(aAnfang);
        std::unique_ptr<Knoten<Typ>> zielKnoten = nullptr;

        for(int i = 0; i < pIndex; i++){ //For-loop endet, wenn aktuellerKnoten auf den Ziel-Knoten gesetz wurde 
            
            //Falls der Index zu groß ist
            indexZuGrossTester(pIndex, i, aktuellerKnoten); 
            aktuellerKnoten.setzeNaechsten(aktuellerKnoten.gibNaechsten()); //aktuellen Knoten auf nächsten Knoten setzen
        
        }
        

        zielKnoten = aktuellerKnoten;
        
        return zielKnoten;

    }

    bool istLeer() const {
        return aAnfang.get() == nullptr;
    }

    int anzahlElemente(){
        int anzahl = 0;
        std::unique_ptr<Knoten<Typ>> aktuellerZeiger = std::move(aAnfang);
        while(aktuellerZeiger->gibNaechsten() != nullptr){
            aktuellerZeiger = aktuellerZeiger->gibNaechsten();
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
        std::unique_ptr<Knoten<Typ>> aktuellerKnoten = std::move(knotenWaehler(pIndex));

        return aktuellerKnoten->gibInhalt(); //gibt den Inhalt an der Stelle von pIndex zurück
    }

    void ersetzen(int pIndex, Typ pInhalt){
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        std::unique_ptr<Knoten<Typ>> derKnoten = std::move(knotenWaehler(pIndex));
        derKnoten->setzeInhalt(pInhalt);
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
       

        std::unique_ptr<Knoten<Typ>> voherigerKnoten = std::move(knotenWaehler(pIndex-1));
        voherigerKnoten->setzeNaechsten(zeigerZuNeuemKnoten);


        if(pIndex < anzahlElemente()){
            std::unique_ptr<Knoten<Typ>> nachfolgenderKnoten = std::move(knotenWaehler(pIndex));
            zeigerZuNeuemKnoten->setzeNaechsten(nachfolgenderKnoten);
        }else if(pIndex == anzahlElemente()){
            voherigerKnoten->setzeNaechsten(zeigerZuNeuemKnoten);
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
            Typ tmpInhalt = aAnfang.gibInhalt();
            aAnfang = std::move(aAnfang.gibNaechsten());
            return tmpInhalt;
        }

        std::unique_ptr voherigerKnoten = std::move(knotenWaehler(pIndex-1));
        std::unique_ptr rueckgabeKnoten = std::move(knotenWaehler(pIndex));

        //Zeiger "aNaechster" vom voherigen Knoten vom Rückgabe-Knoten entfernen
        if(rueckgabeKnoten.gibNaechsten() != nullptr){
            std::unique_ptr folgeKnoten = std::move(knotenWaehler(pIndex+1));
            voherigerKnoten.setzeNaechsten(folgeKnoten);
        }else{
            voherigerKnoten.setzeNaechsten(nullptr);
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
        
        std::unique_ptr<Knoten<Typ>> aktuellerZeiger = std::move(aAnfang);
        Knoten<Typ> aktuellerKnoten = aktuellerZeiger;

        while(aktuellerZeiger.get() != nullptr){
            aktuellerZeiger = aktuellerKnoten.gibNaechsten();
            aktuellerKnoten = aktuellerZeiger;
            if(aktuellerKnoten.gibInhalt() == pInhalt){
                return true;
            }
        }
        return false;
    }

    void entfernenElement(Typ pInhalt){
        std::unique_ptr<Knoten<Typ>> aktuellerZeiger = std::move(aAnfang);
        std::unique_ptr<Knoten<Typ>> voherigerZeiger;

        int zaehler = 0;

        while(aktuellerZeiger.get() != nullptr){
            if(aktuellerZeiger.gibInhalt() == pInhalt){
                voherigerZeiger.setzeNaechsten(aktuellerZeiger.gibNaechsten());
            }
            voherigerZeiger = std::move(aktuellerZeiger);
            aktuellerZeiger = aktuellerZeiger.gibNaechsten();

            zaehler++;
        }
    }
    
    private:
    std::unique_ptr<Knoten<Typ>> aAnfang;
};
