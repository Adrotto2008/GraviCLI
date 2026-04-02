#ifndef INPUT_HPP
#define INPUT_HPP

#include "utilita.hpp"

/*------------CLASSE------------*/
class Input {
public:
    std::string stringa;
    char input = 0;

    void scan();      
    bool valido();
    TipoInput azione();
    TipoInput invio();
    TipoInput uscita();
    TipoInput cancella();
    TipoComando comando();

};
/*------------------------------*/

#endif