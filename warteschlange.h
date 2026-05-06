#include <iostream>
template <typename Typ>
class Knoten {
   private:
   Knoten<Typ>* naechster;
   Typ inhalt;
   public:
   Knoten<Typ>(Typ pInhalt) {
       inhalt = pInhalt;
   }
   void setzeNaechsten(Knoten<Typ>* pKn) {
       naechster = pKn;
   }
   Knoten<Typ>* gibNaechsten() {
       return naechster;
   }
   Typ gibInhalt() {
       return inhalt;
   }
};
template <typename Typ>
class Warteschlange {
   private:
   Knoten<Typ>* kopf;
   Knoten<Typ>* ende;
   public:
   Warteschlange<Typ>() {
   }
   bool istLeer() {
       if (kopf == NULL) return 1;
       return 0;
   }
   void enqueue(Typ pInhalt) {
       Knoten<Typ>* k = new Knoten{pInhalt};
       if(istLeer()) {
           kopf = k;
           ende = k;
       } else {
           ende->setzeNaechsten(k);
           ende = ende->gibNaechsten();
       }
   }
   Typ dequeue() {
       Typ tempInhalt = kopf->gibInhalt();
       kopf = kopf->gibNaechsten();
       return tempInhalt;
   }
   int anzahlElemente() {
       return 0;
   }
};
