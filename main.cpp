#include "include/input.hpp"
#include "include/campo.hpp"

int main(void) {

    Campo campo;
    Input input;
    GRAVITA gravita = GRAVITA::DESTRA;
    COORD posizione = {2, 2};
    short movimento;

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
                        if (gravita != GRAVITA::SINISTRA) gravita = GRAVITA::DESTRA;
                        break;

                    case TipoComando::SINISTRA:
                        if (gravita != GRAVITA::DESTRA) gravita = GRAVITA::SINISTRA;
                        break;

                    case TipoComando::SU:
                        if (gravita != GRAVITA::GIU) gravita = GRAVITA::SU;
                        break;

                    case TipoComando::GIU:
                        if (gravita != GRAVITA::SU) gravita = GRAVITA::GIU;
                        break;

                    case TipoComando::SKIP:
                        movimento = 3;
                        goto SKIP;
                        break;

                    default:
                        break;
                }
            } else if (azione == TipoInput::BACKSPACE) {



                GRAVITA g2 = static_cast<GRAVITA>((static_cast<int>(gravita) + 2) % 4);

                if (campo.collisione(posizione, g2, movimento) == TipoScritta::COLLISIONE) {

                    if (input.stringa.length() > 0) input.stringa.pop_back();

                    campo.set_casella(posizione.Y, posizione.X, ' ', TipoScritta::LIBERO);
                    posizione_cursore(posizione);
                    printf(" ");

                    // i segni sono invertiti
                    switch (gravita) {
                        case GRAVITA::DESTRA:
                            posizione.X -= movimento;
                            break;

                        case GRAVITA::SINISTRA:
                            posizione.X += movimento;
                            break;

                        case GRAVITA::SU:
                            posizione.Y += movimento;
                            break;

                        case GRAVITA::GIU:
                            posizione.Y -= movimento;
                            break;
                    }
                }

            } else if (input.valido()) {

                SKIP:

                if (campo.collisione(posizione, gravita, movimento) != TipoScritta::LIBERO) {
                    input.stringa.erase(input.stringa.length() - 2, 1);
                    //rendi rosso il carattere?
                }else {
                    switch (gravita) {
                        case GRAVITA::DESTRA:
                            posizione.X += movimento;
                            break;

                        case GRAVITA::SINISTRA:
                            posizione.X -= movimento;
                            break;

                        case GRAVITA::SU:
                            posizione.Y -= movimento;
                            break;

                        case GRAVITA::GIU:
                            posizione.Y += movimento;
                            break;
                    }
                }

                campo.set_casella(posizione.Y, posizione.X, input.input, TipoScritta::COLLISIONE);

                posizione_cursore(posizione);

                printf("%c", input.input);

            }

            // debug della stringa
            cursore_manuale(1, 20);
            printf("Stringa: %-*s", static_cast<int>(input.stringa.length()) + 1, input.stringa.c_str());


        }

    }

    printf(CURSORE_VISIBILE);
    printf(RESET);
    
    return 0;

}
