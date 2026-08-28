// Da die KLasse Knoten von mehreren Datenstrkturen benötigt wird, tue ich sie mal fürs ganze Projekt schreiben.
// Sie ist sehr nah an den Klassendiagram orientiert, das wir im Unterricht verwendet haben.

#pragma once // Verhindert, dass die Klasse mehrfach inklusiert wird
#include <memory>
#include <utility>


template<typename Typ>
class Knoten{
    public:
    //Konstruktor
    Knoten() : aNaechster(nullptr){};
    Knoten(Typ pInhalt) : aNaechster(nullptr) {
        aInhalt = std::move(pInhalt);
    };

    //Destruktor
    ~Knoten(){};

    //Schutz gegen simples Kopieren, um zukünftige Fehler verzubeugen
    Knoten(const Knoten&) = delete;
    Knoten& operator=(const Knoten&) = delete;

    // set und get Methoden:
    void setzeNaechsten(std::shared_ptr<Knoten<Typ>> pNaechster){
        aNaechster = pNaechster;
    };

    void setzeInhalt(Typ pInhalt){
        aInhalt = std::move(pInhalt);
    };
    Typ gibInhalt() const{
        return aInhalt;
    };
    private:
    std::shared_ptr<Knoten<Typ>> aNaechster; // Folge-Knoten
    Typ aInhalt; //Daten, die in der Datenstruktur organisiert werden

    public:
    std::shared_ptr<Knoten<Typ>> gibNaechsten(){
        return aNaechster;
    };

};
