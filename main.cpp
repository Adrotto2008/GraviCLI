#include "include/inventario.hpp"
#include "include/input.hpp"
#include "include/campo.hpp"

COORD posizione_iniziale_livelli(std::string livello)
{
    COORD posizione_iniziale = {0, 0};

    if (livello == "livello1.txt") {
        posizione_iniziale = {2, 2};
    } else if (livello == "livello2.txt") {
        posizione_iniziale = {2, 2};
    } else if (livello == "livello3.txt") {
        posizione_iniziale = {2, 2};
    } else if (livello == "livello4.txt") {
        posizione_iniziale = {2, 2};
    } else if (livello == "livello5.txt") {
        posizione_iniziale = {2, 1};
    } else if (livello == "livello6.txt") {
        posizione_iniziale = {2, 2};
    } else if (livello == "livello7.txt") {
        posizione_iniziale = {2, 2};
    } else if (livello == "livello8.txt") {
        posizione_iniziale = {2, 2};
    } else if (livello == "livello9.txt") {
        posizione_iniziale = {2, 2};
    } else
    {
        posizione_iniziale = {2, 2};
    }

    return posizione_iniziale;
}

COORD spostamento(const short movimento, const GRAVITA gravita, COORD pos) {
    switch (gravita) {
        case GRAVITA::DESTRA:
            pos.X += movimento;
            break;

        case GRAVITA::SINISTRA:
            pos.X -= movimento;
            break;

        case GRAVITA::SU:
            pos.Y -= movimento;
            break;

        case GRAVITA::GIU:
            pos.Y += movimento;
            break;
    }
    return pos;
}

void rimuovi_freccia(Campo campo, COORD posizione_freccia) {
    posizione_cursore(posizione_freccia);
    campo.stampa(posizione_freccia.Y, posizione_freccia.X);
}

void mostra_freccia(COORD posizione_freccia, const char carattere_freccia) {
    printf(TESTO_VERDE);
    posizione_cursore(posizione_freccia);
    printf("%c", carattere_freccia);
}

COORD calcola_posizione_freccia(const COORD posizione, GRAVITA gravita){
    COORD posizione_freccia = posizione;

    switch (gravita) {
        case GRAVITA::DESTRA:
            posizione_freccia.X++;
            break;

        case GRAVITA::SINISTRA:
            posizione_freccia.X--;
            break;

        case GRAVITA::SU:
            posizione_freccia.Y--;
            break;

        case GRAVITA::GIU:
            posizione_freccia.Y++;
            break;
    }

    return posizione_freccia;
}

char calcola_carattere_freccia(GRAVITA gravita) {
    switch (gravita) {
        case GRAVITA::DESTRA:
            return '>';

        case GRAVITA::SINISTRA:
            return '<';

        case GRAVITA::SU:
            return '^';

        case GRAVITA::GIU:
            return 'v';
    }

    return 0;
}

int main(int argc, char* argv[]) {

    Inventario inventario;
    Campo campo;
    Input input;
    short movimento;
    std::vector<GRAVITA> gravita;
    std::vector<COORD> posizione;
    std::vector<COORD> posizione_cambio_gravita;
    std::string livello;
    if (argc == 2)
    {
        livello = argv[1];
    } else
    {
        livello = "livello2.txt";
    }
    COORD posizione_freccia = posizione_iniziale_livelli(livello);
    bool skip = false;
    bool uscita = false;
    short movimento_skip = 4;
    COORD posizione_skip = {};
    char carattere_freccia = 0;

    gravita.push_back(GRAVITA::DESTRA);
    posizione.push_back(posizione_freccia);
    posizione_cambio_gravita.push_back(posizione_freccia);

    campo.carica_campo(livello);
    campo.inizializza();

    pulisci();
    cmd_type();

    printf(CURSORE_INVISIBILE);
    printf(RESET);

    campo.stampa_campo();


    while (!uscita) {

        if (!kbhit()) {
            continue;
        }

        rimuovi_freccia(campo, posizione_freccia);

        input.scan();

        movimento = 1;

        TipoInput azione = input.azione();

        if (azione == TipoInput::INVIO) {
            switch (input.comando()) {
                case TipoComando::DESTRA:
                    if (inventario.destra)
                        if (gravita.back() != GRAVITA::SINISTRA && gravita.back() != GRAVITA::DESTRA){ gravita.push_back(GRAVITA::DESTRA); posizione_cambio_gravita.push_back(posizione.back()); }
                    break;

                case TipoComando::SINISTRA:
                    if (inventario.sinistra)
                        if (gravita.back() != GRAVITA::DESTRA && gravita.back() != GRAVITA::SINISTRA){ gravita.push_back(GRAVITA::SINISTRA); posizione_cambio_gravita.push_back(posizione.back()); }
                    break;

                case TipoComando::SU:
                    if (inventario.su)
                        if (gravita.back() != GRAVITA::GIU && gravita.back() != GRAVITA::SU){ gravita.push_back(GRAVITA::SU); posizione_cambio_gravita.push_back(posizione.back()); }
                    break;

                case TipoComando::GIU:
                    if (inventario.giu)
                        if (gravita.back() != GRAVITA::SU && gravita.back() != GRAVITA::GIU){ gravita.push_back(GRAVITA::GIU); posizione_cambio_gravita.push_back(posizione.back()); }
                    break;

                case TipoComando::SKIP:
                    if (inventario.skip)
                        skip = true;
                    break;
                case TipoComando::SPARO:
                    if (inventario.proiettili == 0)
                        break;

                    inventario.proiettili--;
                    for (short i = 1; i < 5; i++) {
                        if (campo.collisione(posizione.back(), gravita.back(), i) != TipoScritta::COLLISIONE)
                            continue;

                        COORD pos = spostamento(i, gravita.back(), posizione.back());
                        campo.set_casella(pos.Y, pos.X, ' ', TipoScritta::LIBERO, Colore::reset, Colore::bianco);
                        posizione_cursore(pos);
                        campo.stampa(pos.Y, pos.X);
                        // suono
                        break;

                    }

                    break;


                default:
                    break;
            }
        } else if (azione == TipoInput::BACKSPACE) {

            if (posizione.size() == 1)
                continue;

            if (posizione.back().X == posizione_cambio_gravita.back().X && posizione.back().Y == posizione_cambio_gravita.back().Y) {
                if (gravita.size() > 1) gravita.pop_back();
                if (posizione_cambio_gravita.size() > 1) posizione_cambio_gravita.pop_back();
            }

            if (!input.stringa.empty()) input.stringa.pop_back();

            campo.set_casella(posizione.back().Y, posizione.back().X, ' ', TipoScritta::LIBERO, Colore::reset, Colore::bianco);
            posizione_cursore(posizione.back());
            campo.stampa(posizione.back().Y, posizione.back().X);

            posizione.pop_back();

            posizione_freccia = calcola_posizione_freccia(posizione.back(), gravita.back());
            carattere_freccia = calcola_carattere_freccia(gravita.back());



        } else if (azione == TipoInput::DEBUG) {
            campo.stampa_campo();
        } else if (azione == TipoInput::ESCI) {
            uscita = true;
        }

        if (skip) {
            if (campo.collisione(posizione.back(), gravita.back(), movimento_skip) != TipoScritta::LIBERO) {
                //errore
                skip = false;
            }else {
                posizione_skip = spostamento(movimento_skip - 1, gravita.back(), posizione.back());
            }
        }

        if (input.valido()) {

            if (skip) {//aggiusta
                posizione.push_back(spostamento(movimento, gravita.back(), posizione_skip));
            }else {
                if (campo.collisione(posizione.back(), gravita.back(), movimento) != TipoScritta::LIBERO) {
                    input.stringa.erase(input.stringa.length() - 2, 1);
                    //rendi rosso il carattere?
                }else {
                    posizione.push_back(spostamento(movimento, gravita.back(), posizione.back()));
                }
            }

            // controllo ottenuta proiettile

            if (campo.caselle[posizione.back().Y][posizione.back().X].testo == '.') {
                inventario.proiettili++;
            }

            // CONDIZIONE USCITA

            if (campo.caselle[posizione.back().Y][posizione.back().X].testo == '!'){
                uscita = true;
            }

            campo.set_casella(posizione.back().Y, posizione.back().X, input.input, TipoScritta::COLLISIONE, Colore::reset, Colore::bianco);

            posizione_cursore(posizione.back());

            campo.stampa(posizione.back().Y, posizione.back().X);


            // TELECAMERA


            skip = false;

        }

        // Freccia grafica di posizione

        posizione_freccia = calcola_posizione_freccia(posizione.back(), gravita.back());
        carattere_freccia = calcola_carattere_freccia(gravita.back());

        if (campo.caselle[posizione_freccia.Y][posizione_freccia.X].tipo == TipoScritta::LIBERO) {
            mostra_freccia(posizione_freccia, carattere_freccia);
        } else {
            campo.caselle[posizione.back().Y][posizione.back().X].coloreTesto = Colore::rosso;
            posizione_cursore(posizione.back());
            campo.stampa(posizione.back().Y, posizione.back().X);
        }




        // debug della stringa
        // cursore_manuale(0, MAX_Y + 1);
        // printf("stringa: %-*s", static_cast<int>(input.stringa.length()) + 1, input.stringa.c_str());
        // debug dei proiettili
        cursore_manuale(0, MAX_Y + 2);
        printf("proiettili: %d", inventario.proiettili);



    }

    printf(CURSORE_VISIBILE);
    printf(RESET);
    
    return 0;

}
