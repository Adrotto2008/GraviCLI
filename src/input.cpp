#include "../include/input.hpp"



// classe dell'input 

void Input::scan(){
    input = 0;
    input = _getch();
    #ifdef __linux__
    if (input == 27){

        if (kbhit()){
        
            char input_2 = _getch();
            char input_3 = _getch();
            if (input_2 == '['){
                switch (input_3){

                case 'A':
                    input = 72;
                    break;
                case 'B':
                    input = 80;
                    break;
                case 'C':
                    input = 77;
                    break;
                case 'D':
                    input = 75;
                    break;

                }
            }

        }
        
    }

    if (input == '\n')  input = 13;
    

    #else
    if(input == 0 || input == 224)  input = _getch();
    #endif

    
}

bool Input::valido(){
    
    for (char c : CARATTERI_POSSIBILI){
        if(c == input)
            return true;
    }
    
    return false;

}

TipoInput Input::azione(){

    if(invio() == TipoInput::INVIO){
        return TipoInput::INVIO;
    }

    if(cancella() == TipoInput::BACKSPACE){
        return TipoInput::BACKSPACE;
    }

    if(uscita() != TipoInput::NULLA){
        return uscita();
    }

    if (!valido()) {
        return TipoInput::NULLA;
    }

    stringa += input;

    if (stringa.length() > 20) {
        stringa.erase(0, 1);
    }

    return TipoInput::NULLA;

}

TipoInput Input::invio(){
    for(char c : INVIO){
        if(input == c){
            return TipoInput::INVIO;
        }
            
    }
    return TipoInput::NULLA;
}

TipoInput Input::uscita(){
    for(char c : ESCI){
        if(input == c){
            return TipoInput::ESCI;
        }
    }
    return TipoInput::NULLA;
}

TipoInput Input::cancella(){
    for(char c : BACKSPACE){
        if(input == c){
            return TipoInput::BACKSPACE;
        }
    }
    return TipoInput::NULLA;
}

TipoComando Input::comando() {
    const std::string input_upper = string_to_upper(stringa);

    for (size_t i = 0; i < NUMERO_COMANDI; ++i) {
        const std::string comando_upper = string_to_upper(COMANDI[i]);
        if (input_upper.ends_with(comando_upper)) {
            // L'enum parte da NULLA=0, quindi i comandi reali iniziano da 1.
            return static_cast<TipoComando>(i + 1);
        }

    }

    return TipoComando::NULLA;


}