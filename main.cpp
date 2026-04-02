#include "include/input.hpp"
#include "include/campo.hpp"

int main(void) {

    Campo campo;
    Input input;
    short movimento;
    std::vector<GRAVITA> gravita;
    std::vector<COORD> posizione;

    gravita.push_back(GRAVITA::DESTRA);
    posizione.push_back(COORD{2, 2});

    campo.carica_campo("prova.txt");
    campo.inizializza();

    pulisci();
    cmd_type();

    printf(CURSORE_INVISIBILE);
    printf(RESET);

    campo.stampa_campo();


    while (true) {

        if (kbhit()){
            input.scan();

            movimento = 1;

            TipoInput azione = input.azione();

            if (azione == TipoInput::INVIO) {
                switch (input.comando()) {
                    case TipoComando::DESTRA:
                        if (gravita.back() != GRAVITA::SINISTRA && gravita.back() != GRAVITA::DESTRA) gravita.push_back(GRAVITA::DESTRA);
                        break;

                    case TipoComando::SINISTRA:
                        if (gravita.back() != GRAVITA::DESTRA && gravita.back() != GRAVITA::SINISTRA) gravita.push_back(
                            GRAVITA::SINISTRA);
                        break;

                    case TipoComando::SU:
                        if (gravita.back() != GRAVITA::GIU && gravita.back() != GRAVITA::SU) gravita.push_back(GRAVITA::SU);
                        break;

                    case TipoComando::GIU:
                        if (gravita.back() != GRAVITA::SU && gravita.back() != GRAVITA::GIU) gravita.push_back(GRAVITA::GIU);
                        break;

                    case TipoComando::SKIP:
                        movimento = 5;
                        goto SKIP;
                        break;

                    default:
                        break;
                }
            } else if (azione == TipoInput::BACKSPACE) {

                if (posizione.size() > 1) {

                    GRAVITA g2 = static_cast<GRAVITA>((static_cast<int>(gravita.back()) + 2) % 4);

                    if (campo.collisione(posizione.back(), g2, movimento) == TipoScritta::LIBERO) {
                        if (gravita.size() > 1) gravita.pop_back();
                    }

                    if (input.stringa.length() > 0) input.stringa.pop_back();

                    campo.set_casella(posizione.back().Y, posizione.back().X, ' ', TipoScritta::LIBERO);
                    posizione_cursore(posizione.back());
                    campo.stampa(posizione.back().Y, posizione.back().X);

                    posizione.pop_back();
                }




            } else if (input.valido()) {

                SKIP:

                if (campo.collisione(posizione.back(), gravita.back(), movimento) != TipoScritta::LIBERO) {
                    input.stringa.erase(input.stringa.length() - 2, 1);
                    //rendi rosso il carattere?
                }else {
                    COORD pos = posizione.back();
                    switch (gravita.back()) {
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
                    posizione.push_back(pos);
                }

                campo.set_casella(posizione.back().Y, posizione.back().X, input.input, TipoScritta::COLLISIONE);

                posizione_cursore(posizione.back());

                campo.stampa(posizione.back().Y, posizione.back().X);

            }

            // debug della stringa
            cursore_manuale(50, 0);
            printf("Stringa: %-*s", static_cast<int>(input.stringa.length()) + 1, input.stringa.c_str());


        }

    }

    printf(CURSORE_VISIBILE);
    printf(RESET);
    
    return 0;

}
