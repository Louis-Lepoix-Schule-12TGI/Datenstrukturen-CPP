#include "KnotenRegulaer.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#pragma once //verhindert mehrfache inklusion

template<typename Typ>
class Stapel{
    public:
    Stapel() = default;
    ~Stapel() = default;

    //Sicherung mit Kopieregeln
    Stapel(const Stapel&) = delete;
    Stapel& operator=(const Stapel&) = delete;

    bool istLeer() const {
        return aAnfang.get() == nullptr;
    }

    void push(Typ pInhalt){
        auto neuerKnoten = std::make_unique<Knoten<Typ>>(pInhalt);
        if(aAnfang){
            neuerKnoten->setzeNaechsten(std::move(aAnfang));
        }
        aAnfang = std::move(neuerKnoten);
    }

    Typ pop(){
        if (istLeer()) {
            throw std::out_of_range("Fehler: Der Stapel ist leer.");
        }
        Typ rueckgabe = aAnfang->gibInhalt();
        aAnfang = std::move(aAnfang->gibNaechsten());
        return rueckgabe;
    }

    Typ top() const {
        if (istLeer()) {
            throw std::out_of_range("Fehler: Der Stapel ist leer.");
        }
        return aAnfang->gibInhalt();
    }
    private:
    std::unique_ptr<Knoten<Typ>> aAnfang;
};
