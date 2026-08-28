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
    if(aktuellerKnoten->gibNaechsten() == nullptr && pIndex > i){
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

            aktuellerKnoten = aktuellerKnoten->gibNaechsten(); //aktuellen Knoten auf nächsten Knoten setzen
        
        }
        
        return aktuellerKnoten;

    }

    bool istLeer() const {
        return aAnfang == nullptr;
    }

    int anzahlElemente(){
        if(istLeer()) return 0;
    
        int anzahl = 0;
        std::shared_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang;
    
        while(aktuellerZeiger != nullptr){
            anzahl++;
            aktuellerZeiger = aktuellerZeiger->gibNaechsten();
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
        
        return aktuellerKnoten->gibInhalt(); //gibt den Inhalt an der Stelle von pIndex zurück

    }

    void ersetzen(int pIndex, Typ pInhalt){
        if(pIndex < 0){ 
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer()){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        std::shared_ptr<Knoten<Typ>> derKnoten = knotenWaehler(pIndex);
        derKnoten->setzeInhalt(pInhalt);
    };

    void einfuegen(int pIndex, Typ pInhalt){
        std::shared_ptr<Knoten<Typ>> zeigerZuNeuemKnoten = std::make_shared<Knoten<Typ>>(pInhalt); 

        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }else if(pIndex == 0){
            zeigerZuNeuemKnoten->setzeNaechsten(aAnfang);
            aAnfang = zeigerZuNeuemKnoten;
            return;
        }

        if(pIndex > anzahlElemente()){
            throw std::invalid_argument("Fehler: Der Index ist zu gross.");
        }
       

        std::shared_ptr<Knoten<Typ>> voherigerKnoten = knotenWaehler(pIndex-1);
        std::shared_ptr<Knoten<Typ>> nachfolgerKnoten = voherigerKnoten->gibNaechsten();
        zeigerZuNeuemKnoten->setzeNaechsten(nachfolgerKnoten);
        voherigerKnoten->setzeNaechsten(zeigerZuNeuemKnoten);
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
            Typ tmpInhalt = aAnfang->gibInhalt();
            auto nachfolgerKnoten = aAnfang->gibNaechsten();
            aAnfang = nachfolgerKnoten;
            return tmpInhalt;
        }

        // Edge Case: Letztes Element
        if(pIndex + 1 >= anzahlElemente()){
            auto voherigerKnoten = knotenWaehler(pIndex-1);
            auto zuEntfernen = voherigerKnoten->gibNaechsten();
            Typ tmpInhalt = zuEntfernen->gibInhalt();
            voherigerKnoten->setzeNaechsten(nullptr);
            return tmpInhalt;
        }

        // Normaler Fall: Mittleres Element
        auto voherigerKnoten = knotenWaehler(pIndex-1);
        auto rueckgabeKnoten = voherigerKnoten->gibNaechsten();
        auto folgeKnoten = rueckgabeKnoten->gibNaechsten();
        voherigerKnoten->setzeNaechsten(folgeKnoten);
    
        return rueckgabeKnoten->gibInhalt();
    }

    Typ entfernenVorne(){
        if (istLeer()) {
            throw std::logic_error("Fehler: Der Stapel ist leer. Es gibt nichts zum entfernen");
        }

        Typ tmpInhalt = aAnfang->gibInhalt(); //Inhalt speichern

        aAnfang = aAnfang->gibNaechsten();  // aAnfang auf Nachfolger setzen

        return tmpInhalt;
    }

    bool enthaelt(Typ pInhalt){
        if (istLeer()) {
            return false;
        }
        
        std::shared_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang;

        while(aktuellerZeiger){
            if(aktuellerZeiger->gibInhalt() == pInhalt){
                return true;
            }
            aktuellerZeiger = aktuellerZeiger->gibNaechsten();
        }
        return false;
    }

    void entfernenElement(Typ pInhalt){
        auto aktuellerZeiger = aAnfang;
        std::shared_ptr<Knoten<Typ>> voherigerZeiger  = nullptr;

        while(aktuellerZeiger) {  // Schleife endet wenn die ganze verkettete liste durchlaufen wurde
            if(aktuellerZeiger->gibInhalt() == pInhalt){
                std::shared_ptr<Knoten<Typ>> naechsterKnoten = aktuellerZeiger->gibNaechsten();
            
                if (voherigerZeiger) {
                    voherigerZeiger->setzeNaechsten(naechsterKnoten);
                } else {
                    aAnfang = naechsterKnoten;  // Edge Case: Erstes Element
                }
                aktuellerZeiger = naechsterKnoten;
            } else {
                voherigerZeiger = aktuellerZeiger;
                aktuellerZeiger = aktuellerZeiger->gibNaechsten(); 
            }
        }
    }
    
    private:
    std::shared_ptr<Knoten<Typ>> aAnfang;
};
