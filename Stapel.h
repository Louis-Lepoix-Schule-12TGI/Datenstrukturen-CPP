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
            
            neuerKnoten->setzeNaechsten(aAnfang);
            
            aAnfang = neuerKnoten;  // Bestehenden Stack zum neuen Knoten hinzufügen
        } else {    // First Element
            aAnfang = neuerKnoten;  // Shared_ptr übernehmen
        }
    }

    Typ pop(){
        if (istLeer()) {
            throw std::out_of_range("Fehler: Der Stapel ist leer.");
        }
        
        auto aktuellerKnoten = aAnfang;  // shared_ptr kopieren (nicht move!)
        
        // Wenn der Stack mehr als 1 Element hat, Bewahre den Nachfolger als neuen aAnfang!
        if(aktuellerKnoten->gibNaechsten() != nullptr){
            auto nachfolgerKnoten = aktuellerKnoten->gibNaechsten();
            aAnfang = nachfolgerKnoten;  // Setze Nachfolger als neuen Top
        } else {
            aAnfang = nullptr;  // War nur das einzige Element, jetzt ist der Stack leer!
        }
        
        return aktuellerKnoten->gibInhalt();  // Wert aus aktuellem Knoten holen!
    }

    Typ top() const {
        if (istLeer()) {
            throw std::out_of_range("Fehler: Der Stapel ist leer.");
        }
        return aAnfang->gibInhalt();
    }
    
    private:
    std::shared_ptr<Knoten<Typ>> aAnfang;  // shared_ptr statt unique_ptr!
};
