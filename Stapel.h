#include "KnotenRegulaer.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#pragma once //verhindert mehrfache inklusion

template<typename Typ>
class Stapel{
    public:
    Stapel() : aAnfang(nullptr){};
    ~Stapel() = default;

    //Sicherung mit Kopieregeln (nur Move-Semantik erlaubt!)
    Stapel(const Stapel&) = delete;
    Stapel& operator=(const Stapel&) = delete;

    bool istLeer() const {
        return aAnfang == nullptr;
    }

    void push(Typ pInhalt){
        auto neuerKnoten = std::make_shared<Knoten<Typ>>(pInhalt);
        
        if(aAnfang){ // Wenn Stapel nicht leer
            
            neuerKnoten->get().setzeNaechsten(aAnfang); // bisherigen Anfang als Nachfolger des neuem Knoten setzen
            
            aAnfang = neuerKnoten;  // neuen Knoten als Anfang setzen
        } else {    // erstes Element
            aAnfang = neuerKnoten;  // neuen Knoten als Anfang setzen
        }
    }

    Typ pop(){
        if (istLeer()) {
            throw std::out_of_range("Fehler: Der Stapel ist leer.");
        }
        
        auto aktuellerKnoten = aAnfang;  // shared_ptr kopieren
        
        // Wenn der Stack mehr als 1 Element hat, den Nachfolger zum neuen Anfang setzen
        if(aktuellerKnoten->get().gibNaechsten() != nullptr){
            auto nachfolgerKnoten = aktuellerKnoten->gibNaechsten();
            aAnfang = nachfolgerKnoten;  // Setze Nachfolger als neuen Top
        } else {
            aAnfang = nullptr;  // War nur das einzige Element, jetzt ist der Stack leer
        }
        
        return aktuellerKnoten->get().gibInhalt();  // Wert des aktuellem Knoten zurückgeben
    }

    Typ top() const {
        if (istLeer()) {
            throw std::out_of_range("Fehler: Der Stapel ist leer.");
        }
        return aAnfang->get().gibInhalt();
    }
    
    private:
    std::shared_ptr<Knoten<Typ>> aAnfang;  // shared_ptr statt unique_ptr!
};
