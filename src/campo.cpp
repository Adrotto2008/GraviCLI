#include "../include/campo.hpp"

void Campo::carica_campo(std::string nomeFile) {

    std::ifstream fp("livelli/" + nomeFile, std::ios::binary);
    if (!fp.is_open()) {
        printf("errore");
        return;
    }

    auto normalizza_riga = [](std::string& riga, bool primaRiga) {
        if (!riga.empty() && riga.back() == '\r') {
            riga.pop_back();
        }

        if (primaRiga && riga.size() >= 3) {
            unsigned char b0 = static_cast<unsigned char>(riga[0]);
            unsigned char b1 = static_cast<unsigned char>(riga[1]);
            unsigned char b2 = static_cast<unsigned char>(riga[2]);
            if (b0 == 0xEF && b1 == 0xBB && b2 == 0xBF) {
                riga.erase(0, 3);
            }
        }
    };

    int righeLette = 0;
    int maxColonne = 0;
    std::string riga;

    while (std::getline(fp, riga)) {
        normalizza_riga(riga, righeLette == 0);
        maxColonne = (std::max)(maxColonne, static_cast<int>(riga.size()));
        righeLette++;
    }

    MAX_Y = righeLette;
    MAX_X = (std::max)(maxColonne, 1);

    caselle.assign(MAX_Y, std::vector<Casella>(MAX_X));

    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            caselle[i][j].testo = ' ';
        }
    }

    fp.clear();
    fp.seekg(0, std::ios::beg);
    if (!fp.good()) {
        return;
    }

    for (int i = 0; i < MAX_Y; i++) {
        if (!std::getline(fp, riga)) {
            break;
        }

        normalizza_riga(riga, i == 0);

        int j = 0;
        for (; j < MAX_X && j < static_cast<int>(riga.size()); j++) {
            caselle[i][j].testo = riga[j];
        }

        for (; j < MAX_X; j++) {
            caselle[i][j].testo = ' ';
        }
    }
}




// se è ' ' allora è un testo libero
// se è # allora è uno sfondo e ha una collisione permanente
// se è qualsiasi altra cosa è un testo con una collisione rimovibile con backspace

void Campo::inizializza(){

    for(int i = 0; i < MAX_Y; i++){
        for(int j = 0; j < MAX_X; j++){
            if(caselle[i][j].testo == ' '){
                caselle[i][j].tipo = TipoScritta::LIBERO;
                caselle[i][j].coloreTesto = Colore::bianco;
            } else if(caselle[i][j].testo == '#'){
                caselle[i][j].tipo = TipoScritta::SFONDO;
                caselle[i][j].coloreTesto = Colore::grigio_chiaro;
            } else {
                caselle[i][j].tipo = TipoScritta:: COLLISIONE;
                caselle[i][j].coloreTesto = Colore::bianco;
            }
        }
    }

}




void Campo::stampa(short y, short x) {

    y += TELECAMERA_Y;
    x += TELECAMERA_X;

    controllo_colori_sfondo(caselle[y][x]);
    controllo_colori_testo(caselle[y][x]);
    printf("%c", caselle[y][x].testo);

}

void Campo::stampa_campo() {
    pulisci();
    cursore_manuale(0, 0);
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            stampa(i, j);
        }
        printf("\n");
    }
}

void Campo::set_casella(short y, short x, char c, TipoScritta tipo) {
    caselle[y][x].testo = c;
    caselle[y][x].tipo = tipo;
}

TipoScritta Campo::collisione(COORD posizione, GRAVITA gravita, short movimento) {

    if (movimento == 0) return TipoScritta::COLLISIONE;

    for (int i = 0; i < movimento; i++) {

        switch (gravita) {
            case GRAVITA::DESTRA:
                posizione.X += 1;
                break;

            case GRAVITA::SINISTRA:
                posizione.X -= 1;
                break;

            case GRAVITA::SU:
                posizione.Y -= 1;
                break;

            case GRAVITA::GIU:
                posizione.Y += 1;
                break;
        }

        if ((movimento == 1 || i == movimento - 1) && caselle[posizione.Y][posizione.X].tipo != TipoScritta::LIBERO) return caselle[posizione.Y][posizione.X].tipo;
        if (movimento > 1 && caselle[posizione.Y][posizione.X].tipo == TipoScritta::SFONDO) return TipoScritta::SFONDO;
    }


    return TipoScritta::LIBERO;

}
