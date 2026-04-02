#include "../include/campo.hpp"
#include "../include/utilita.hpp"

void Campo::carica_campo(std::string nomeFile) {

    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            caselle[i][j].testo = ' ';
        }
    }

    FILE* fp = fopen(("livelli/" + nomeFile).c_str(), "rb");
    if (!fp) {
        printf("errore");
        return;
    }

    char buffer[MAX_X + 4];

    for (int i = 0; i < MAX_Y; i++) {
        if (!fgets(buffer, sizeof(buffer), fp)) {
            break;
        }

        int src = 0;
        if (i == 0) {
            unsigned char b0 = static_cast<unsigned char>(buffer[0]);
            unsigned char b1 = static_cast<unsigned char>(buffer[1]);
            unsigned char b2 = static_cast<unsigned char>(buffer[2]);
            if (b0 == 0xEF && b1 == 0xBB && b2 == 0xBF) {
                src = 3;
            }
        }

        int j = 0;
        for (; j < MAX_X; j++, src++) {
            if (buffer[src] == '\0' || buffer[src] == '\n' || buffer[src] == '\r') {
                break;
            }
            caselle[i][j].testo = buffer[src];
        }

        for (; j < MAX_X; j++) {
            caselle[i][j].testo = ' ';
        }
    }

    fclose(fp);
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

    controllo_colori_sfondo(caselle[y][x]);
    controllo_colori_testo(caselle[y][x]);
    printf("%c", caselle[y][x].testo);

}

void Campo::stampa_campo() {
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

        if (caselle[posizione.Y][posizione.X].tipo != TipoScritta::LIBERO) {
            return caselle[posizione.Y][posizione.X].tipo;
        }


    }

    return TipoScritta::LIBERO;

}
