// Da die KLasse Knoten von mehreren Datenstrkturen benötigt wird, tue ich sie mal fürs ganze Projekt schreiben.
// Sie ist sehr nah an den Klassendiagram orientiert, das wir im Unterricht verwendet haben.

#pragma once // Verhindert, dass die Klasse mehrfach inklusiert wird
#include <memory>
#include <utility>


template<typename Typ>
class Knoten{
    public:
    //Konstruktor
    Knoten(){};
    Knoten(Typ pInhalt){
        aInhalt = std::move(pInhalt);
    };

    //Destruktor
    ~Knoten(){};

    //Schutz gegen simples Kopieren, um zukünftige Fehler verzubeugen
    Knoten(const Knoten&) = delete;
    Knoten& operator=(const Knoten&) = delete;

    // set und get Methoden:
    void setzeNaechsten(std::unique_ptr<Knoten<Typ>> pNaechster){
        aNaechster = std::move(pNaechster);
    };
    std::unique_ptr<Knoten<Typ>> gibNaechsten(){
        return aNaechster;
    };

    void setzeInhalt(Typ pInhalt){
        aInhalt = std::move(pInhalt);
    };
    Typ gibInhalt() const{
        return aInhalt;
    };

    std::unique_ptr<Knoten<Typ>> aNaechster; // Folge-Knoten
    private:
    Typ aInhalt; //Daten, die in der Datenstruktur organisiert werden


};
