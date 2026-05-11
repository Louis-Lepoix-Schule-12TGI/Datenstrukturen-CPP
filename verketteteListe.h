#include "KnotenRegulaer.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#pragma once //verhindert mehrfache inklusion

template<typename Typ>
class verketteteListe{
    public:
    verketteteListe() : aAnfang(nullptr) {};
    ~verketteteListe() = default;

    //Sicherung mit Kopieregeln
    verketteteListe(const verketteteListe&) = delete;
    verketteteListe& operator=(const verketteteListe&) = delete;


    void indexZuGrossTester(int pIndex, int& i, std::shared_ptr<Knoten<Typ>>& aktuellerKnoten){
    if(aktuellerKnoten->get().gibNaechsten() == nullptr && pIndex > i){
        //Error werfen - wir sind am Ende und haben den Index noch nicht erreicht
        std::string errorNachricht = "Fehler: Der Index ist zu groß. Gegebenen Index: " + 
                                      std::to_string(pIndex) + ". Höchster Index: " + 
                                      std::to_string(i);
        throw std::out_of_range(errorNachricht);
    }
}



    std::shared_ptr<Knoten<Typ>> knotenWaehler(int pIndex){
        /*
        Tut einen Pointer, welcher zum Knoten an der Stelle pIndex zeigt, zurückgeben 
        */

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index ausgewaehlt werden");
        }

        std::shared_ptr<Knoten<Typ>> aktuellerKnoten = aAnfang;

        for(int i = 0; i < pIndex; i++){ //For-loop endet, wenn aktuellerKnoten auf den Ziel-Knoten gesetz wurde 
            
            //Falls der Index zu groß ist
            indexZuGrossTester(pIndex, i, aktuellerKnoten); 

            aktuellerKnoten = aktuellerKnoten->get().gibNaechsten(); //aktuellen Knoten auf nächsten Knoten setzen
        
        }
        
        return aktuellerKnoten;

    }

    bool istLeer() const {
        return aAnfang == nullptr;
    }

    int anzahlElemente(){
        if(istLeer()) return 0;
    
        int anzahl = 1;  // Start bei 1 (weil wir aAnfang nicht zählen)
        std::shared_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang->get();
    
        while(aktuellerZeiger->get().gibNaechsten() != nullptr){
            aktuellerZeiger = aktuellerZeiger->get().gibNaechsten();
            anzahl++;
        }
        return anzahl;
    }

    Typ inhalt(int pIndex) {
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        std::shared_ptr<Knoten<Typ>> aktuellerKnoten = knotenWaehler(pIndex);
        
        return aktuellerKnoten->get().gibInhalt(); //gibt den Inhalt an der Stelle von pIndex zurück

    }

    void ersetzen(int pIndex, Typ pInhalt){
        if(pIndex < 0){ 
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        std::shared_ptr<Knoten<Typ>> derKnoten = knotenWaehler(pIndex);
        derKnoten->get().setzeInhalt(pInhalt);
    };

    void einfuegen(int pIndex, Typ pInhalt){
        std::shared_ptr zeigerZuNeuemKnoten = std::make_shared<Knoten<Typ>>(pInhalt); 

        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }else if(pIndex == 0){
            aAnfang = zeigerZuNeuemKnoten;
            return;
        }

        if(pIndex > anzahlElemente()){
            throw std::invalid_argument("Fehler: Der Index ist zu gross.");
        }
       

        std::shared_ptr<Knoten<Typ>> voherigerKnoten = knotenWaehler(pIndex-1);
        voherigerKnoten->get().setzeNaechsten(std::move(zeigerZuNeuemKnoten));


        if(pIndex < anzahlElemente()){
            std::shared_ptr<Knoten<Typ>> nachfolgenderKnoten = knotenWaehler(pIndex);
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
        if(pIndex >= anzahlElemente()){
            throw std::invalid_argument("Fehler: Der Index ist zu gross.");
        }

        // Edge Case: Erstes Element
        if(pIndex == 0) { 
            Typ tmpInhalt = aAnfang->get().gibInhalt();
            auto nachfolgerKnoten = aAnfang->get().gibNaechsten();
            aAnfang = std::move(nachfolgerKnoten);
            return tmpInhalt;
        }

        // Edge Case: Letztes Element
        if(pIndex + 1 >= anzahlElemente()){
            auto voherigerKnoten = knotenWaehler(pIndex-1);
            Typ tmpInhalt = voherigerKnoten->get().gibNaechsten();
            voherigerKnoten->get().setzeNaechsten(nullptr);
            return tmpInhalt;
        }

        // Normaler Fall: Mittleres Element
        auto voherigerKnoten = knotenWaehler(pIndex-1);
        auto rueckgabeKnoten = voherigerKnoten->get().gibNaechsten();
    
        if(rueckgabeKnoten->get().gibNaechsten() != nullptr){
            Typ folgeInhalt = voherigerKnoten->get().gibNaechsten();
            voherigerKnoten->get().setzeNaechsten(folgeInhalt);
        }else{
            voherigerKnoten->get().setzeNaechsten(nullptr);
        }

        return rueckgabeKnoten->get().gibInhalt();  // Inhalt zurückgeben
    }

    Typ entfernenVorne(){
        if (istLeer()) {
            throw std::logic_error("Fehler: Der Stapel ist leer. Es gibt nichts zum entfernen");
        }

        Typ tmpInhalt = aAnfang->get().gibInhalt(); //Inhalt speichern

        aAnfang = aAnfang->get().gibNaechsten();  // aAnfang auf Nachfolger setzen

        return tmpInhalt;
    }

    bool enthaelt(Typ pInhalt){
        if (istLeer()) {
            return false;
        }
        
        std::shared_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang;

        while(aktuellerZeiger){
            if(aktuellerZeiger->get().gibInhalt() == pInhalt){
                return true;
            }
            aktuellerZeiger = aktuellerZeiger->get().gibNaechsten();
        }
        return false;
    }

    void entfernenElement(Typ pInhalt){
        auto aktuellerZeiger = aAnfang;
        std::shared_ptr<Knoten<Typ>> voherigerZeiger  = nullptr;

        while(aktuellerZeiger) {  // Schleife endet wenn die ganze verkettete liste durchlaufen wurde
            if(aktuellerZeiger->get().gibInhalt() == pInhalt){
                std::shared_ptr<Knoten<Typ>> naechsterKnoten = aktuellerZeiger->get().gibNaechsten();
            
                if (voherigerZeiger) {
                    voherigerZeiger->get().setzeNaechsten(naechsterKnoten);
                } else {
                    aAnfang = naechsterKnoten;  // Edge Case: Erstes Element
                }
            }
            voherigerZeiger = aktuellerZeiger;
            aktuellerZeiger = aktuellerZeiger->get().gibNaechsten(); 
        }
    }
    
    private:
    std::shared_ptr<Knoten<Typ>> aAnfang;
};
