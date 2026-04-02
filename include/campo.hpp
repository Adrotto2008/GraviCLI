#ifndef GRAVICLI_CAMPO_H
#define GRAVICLI_CAMPO_H

#include "costanti.hpp"

struct Casella {

    char testo;
    Colore coloreTesto;
    Colore coloreSfondo;
    TipoScritta tipo;

};

class Campo {

    public:

        Casella caselle[MAX_Y][MAX_X];

        void carica_campo(std::string nomeFile);
        void inizializza();
        void stampa(short y, short x);
        void stampa_campo();

        void set_casella(short y, short x, char testo, TipoScritta tipo);
        TipoScritta collisione(COORD posizione, GRAVITA gravita, short movimento);

};


#endif //GRAVICLI_CAMPO_H