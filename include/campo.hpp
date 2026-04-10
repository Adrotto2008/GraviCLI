#ifndef GRAVICLI_CAMPO_H
#define GRAVICLI_CAMPO_H

#include "costanti.hpp"
#include "utilita.hpp"
#include <vector>
#include <algorithm>
#include <fstream>

struct Casella {

    char testo;
    Colore coloreTesto;
    Colore coloreSfondo;
    TipoScritta tipo;

};

class Campo {

    public:

        std::vector<std::vector<Casella>> caselle;

        void carica_campo(std::string nomeFile);
        void inizializza();
        void stampa(short y, short x);
        void stampa_campo();

        void set_casella(short y, short x, char testo, TipoScritta tipo, Colore colore_sfondo, Colore colore_testo);
        TipoScritta collisione(COORD posizione, GRAVITA gravita, short movimento);

};


#endif //GRAVICLI_CAMPO_H