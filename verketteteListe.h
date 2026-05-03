#include "KnotenRegulaer.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#pragma once //verhindert mehrfache inklusion

//noch nicht fertig Link zum Klassendiagram: https://llsbad.sharepoint.com/:b:/s/TG_24_27/IQCMCj7fIKkhR6wBARU3raoLAQpBkhulJrSSbk4A_vLNU8o?e=yTXY9b Seite 2

template<typename Typ>
class verketteteListe{
    public:
    verketteteListe() = default;
    ~verketteteListe() = default;

    //Sicherung mit Kopieregeln
    verketteteListe(const verketteteListe&) = delete;
    verketteteListe& operator=(const verketteteListe&) = delete;

    bool istLeer() const {
        return aAnfang.get() == nullptr;
    }

    Typ entfernenVorne(){
        if (istLeer()) {
            throw std::logic_error("Fehler: Der Stapel ist leer. Es gibt nichts zum entfernen");
        }
        Typ rueckgabe = aAnfang->gibInhalt();

        aAnfang = std::move(aAnfang->aNaechster);
        
        return rueckgabe;
    }

    int anzahlElemente(){
        int anzahl = 0;
        std::unique_ptr<Knoten<Typ>> aktuellerZeiger = aAnfang;
        while(aktuellerZeiger.get() != nullptr){
            anzahl++;
        }
        return anzahl;
    }

    Typ inhalt(int pIndex){
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer())){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        Knoten<Typ> aktuellerKnoten = *aAnfang.get();

        for(int i = 0; i < pIndex; i++){ //For-loop endet, wenn aktuellerKnoten auf den Ziel-Knoten gesetz wurde 
            
            //Falls der Index zu groß ist
            if(aktuellerKnoten.gibNaechsten().get() == nullptr && pIndex > i){

                //Error Nachricht schreiben
                std::string errorNachricht = "Fehler: Es exestiert kein Elemnt beim gegebenen Index: " + 
                                            static_cast<std::string>>(pIndex) + 
                                            " .  Hoehster Index:" +
                                            static_cast<std::string>(anzahlElemente()-1);
    
                    throw std::out_of_range(errorNachricht); //Error werfen
            }else{
                aktuellerKnoten = *aktuellerKnoten.get() //aktuellen Knoten auf nächsten Knoten setzen
            }
        }

        return aktuellerKnoten.gibInhalt(); //gibt den Inhalt an der Stelle von pIndex zurück
    }

    void ersetzen(int pIndex, Typ pInhalt){
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        if(istLeer())){
            throw std::logic_error("Fehler: Der Stapel ist leer. Es kann Nichts am Index existieren");
        }
        Knoten<Typ> aktuellerKnoten = *aAnfang.get();

        for(int i = 0; i < pIndex; i++){ //For-loop endet, wenn aktuellerKnoten auf den Ziel-Knoten gesetz wurde 
            
            //Falls der Index zu groß ist
            if(aktuellerKnoten.gibNaechsten().get() == nullptr && pIndex > i){

                //Error Nachricht schreiben
                std::string errorNachricht = "Fehler: Es exestiert kein Elemnt beim gegebenen Index: " + 
                                            static_cast<std::string>>(pIndex) + 
                                            " .  Hoehster Index:" +
                                            static_cast<std::string>(anzahlElemente()-1);
    
                    throw std::out_of_range(errorNachricht); //Error werfen
            }else{
                aktuellerKnoten = *aktuellerKnoten.get() //aktuellen Knoten auf nächsten Knoten setzen
            }
        }
        aktuellerKnoten.setzeInhalt(pInhalt);
    };

    void einfuegen(int pIndex, Typ pInhalt){
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        Knoten<Typ> aktuellerKnoten = *aAnfang.get();
        
        //ACHTUNG: For-loop andes als bei ersetzen() und inhalt()
        for(int i = 0; i < (pIndex-1); i++){ //For-loop endet, wenn aktuellerKnoten auf den Vorgänger des Ziel-Knoten gesetz wurde (fängt bei 0 erst gar nicht an)
            
            //Falls der Index zu groß ist
            if(aktuellerKnoten.gibNaechsten().get() == nullptr && pIndex > (i+1){ //Änderung von den Anderen: Index darf 1 größer sein falls ein Element angehangen wird

                //Error Nachricht schreiben
                std::string errorNachricht = "Fehler: Es exestiert kein Elemnt beim gegebenen Index: " + 
                                            static_cast<std::string>>(pIndex) + 
                                            " .  Hoehster Index:" +
                                            static_cast<std::string>(anzahlElemente()-1);
    
                    throw std::out_of_range(errorNachricht); //Error werfen
            }else{
                aktuellerKnoten = *aktuellerKnoten.get() //aktuellen Knoten auf nächsten Knoten setzen
            }
        }

    };

    void einfuegenVorne(Typ pInhalt){
        if(pIndex < 0){
            throw std::invalid_argument("Fehler: Der Index muss 0 oder hoeher sein!");
        }

        einfuegen(0, pInhalt);
    };

    void anhaengen(Typ pInhalt){
        einfuegen(anzahlElemente(); pInhalt);
    }
    

    
    private:
    std::unique_ptr<Knoten<Typ>> aAnfang;
};
