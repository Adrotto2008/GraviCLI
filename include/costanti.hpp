#ifndef COSTANTI_HPP
#define COSTANTI_HPP

#include <iostream>
#include <array>
#include <string>


/*-----------COSTANTI----------------*/
/*------------CORDINATE---------*/
extern int MAX_Y; // 14 // 100
extern int MAX_X; // 50 // 200

extern int MAX_Y_TERMINALE; // 14 // 100
extern int MAX_X_TERMINALE; // 50 // 200

extern int TELECAMERA_Y; // 14 // 100
extern int TELECAMERA_X; // 50 // 200

/*------------COLORI------------*/
#define RESET   "\033[0m" //
#define TESTO_NERO    "\033[30m" //
#define TESTO_ROSSO   "\033[31m" //
#define TESTO_VERDE   "\033[32m" //
#define TESTO_GIALLO  "\033[33m" //
#define TESTO_BLU     "\033[34m" //
#define TESTO_MAGENTA "\033[35m" //
#define TESTO_CIANO   "\033[36m" //
#define TESTO_BIANCO  "\033[37m" //
#define TESTO_ARANCIONE "\033[38;5;208m"
#define TESTO_VIOLA "\033[38;5;129m"
#define TESTO_GRIGIO "\033[38;5;245m" //
#define TESTO_MARRONE "\033[38;5;94m"

#define TESTO_BLU_CHIARO "\033[38;5;123m"
#define TESTO_VERDE_CHIARO "\033[38;5;82m"
#define TESTO_GIALLO_CHIARO "\033[38;5;226m"
#define TESTO_ROSSO_CHIARO "\033[38;5;196m"
#define TESTO_VERDE_SCURO "\033[38;5;34m"
#define TESTO_GIALLO_SCURO "\033[38;5;220m"
#define TESTO_BLU_SCURO "\033[38;5;24m"
#define TESTO_MAGENTA_CHIARO "\033[38;5;201m"
#define TESTO_CIANO_CHIARO "\033[38;5;51m"
#define TESTO_GRIGIO_CHIARO "\033[38;5;250m"
#define TESTO_VIOLA_CHIARO "\033[38;5;135m"
#define TESTO_LIGHT_RED "\033[38;5;9m"
#define TESTO_LIGHT_GREEN "\033[38;5;10m"
#define TESTO_LIGHT_YELLOW "\033[38;5;11m"
#define TESTO_LIGHT_BLUE "\033[38;5;12m"
#define TESTO_LIGHT_MAGENTA "\033[38;5;13m"
#define TESTO_LIGHT_CYAN "\033[38;5;14m"
#define TESTO_DARK_GRAY "\033[38;5;8m"

#define SFONDO_NERO    "\033[40m"
#define SFONDO_ROSSO   "\033[41m"
#define SFONDO_VERDE   "\033[42m"
#define SFONDO_GIALLO  "\033[43m"
#define SFONDO_BLU     "\033[44m"
#define SFONDO_MAGENTA "\033[45m"
#define SFONDO_CIANO   "\033[46m"
#define SFONDO_BIANCO  "\033[47m"
#define SFONDO_ARANCIONE "\033[48;5;208m"
#define SFONDO_VIOLA "\033[48;5;129m"
#define SFONDO_GRIGIO "\033[48;5;245m"
#define SFONDO_MARRONE "\033[48;5;94m"

#define SFONDO_BLU_CHIARO "\033[48;5;123m"
#define SFONDO_VERDE_CHIARO "\033[48;5;82m"
#define SFONDO_GIALLO_CHIARO "\033[48;5;226m"
#define SFONDO_ROSSO_CHIARO "\033[48;5;196m"
#define SFONDO_VERDE_SCURO "\033[48;5;34m"
#define SFONDO_GIALLO_SCURO "\033[48;5;220m"
#define SFONDO_BLU_SCURO "\033[48;5;24m"
#define SFONDO_MAGENTA_CHIARO "\033[48;5;201m"
#define SFONDO_CIANO_CHIARO "\033[48;5;51m"
#define SFONDO_GRIGIO_CHIARO "\033[48;5;250m"
#define SFONDO_VIOLA_CHIARO "\033[48;5;135m"
#define SFONDO_LIGHT_RED "\033[48;5;9m"
#define SFONDO_LIGHT_GREEN "\033[48;5;10m"
#define SFONDO_LIGHT_YELLOW "\033[48;5;11m"
#define SFONDO_LIGHT_BLUE "\033[48;5;12m"
#define SFONDO_LIGHT_MAGENTA "\033[48;5;13m"
#define SFONDO_LIGHT_CYAN "\033[48;5;14m"
#define SFONDO_DARK_GRAY "\033[48;5;8m"


#if !defined(_WIN32)
// ---- Struct compatibile con COORD ----
struct COORD {
    short X;
    short Y;
};

#else

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#endif

/*-----------CURSORE-------------*/
#define CURSORE_INVISIBILE "\033[?25l"
#define CURSORE_VISIBILE "\033[?25h"
/*------------------------------*/

/*--------------ENUMS----------------*/

enum class GRAVITA{

    SU,
    SINISTRA,
    GIU,
    DESTRA

};

enum class TipoScritta {

    SFONDO,
    LIBERO,
    COLLISIONE

};

/*------------COLORI------------*/
enum class Colore {
    rosso        = -1,
    ciano        = -2,
    blu          = -3,
    arancione    = -4,
    giallo       = -5,
    verde        = -6,
    magenta_chiaro = -7,
    
    marrone      = -8,
    light_green  = -9,
    blu_scuro    = -10,
    ciano_chiaro = -11,
    light_yellow = -12,
    magenta      = -13,
    bianco       = -14,

    grigio_chiaro = -15,
    nero = -16,
    reset = -17,
    neutro = -18
};

/*------------INPUT------------*/

enum class TipoInput{
    INVIO,
    ESCI,
    BACKSPACE,
    DEBUG,
    NULLA
};

enum class TipoComando {
    NULLA,
    SU,
    GIU,
    SINISTRA,
    DESTRA,
    SKIP,
    SPARO
};

#define NUMERO_COMANDI 6
extern const std::string COMANDI[NUMERO_COMANDI];

/*-------------VARIABILI GLOBALI DI IMPOSTAZIONI-----------*/

/*------------INPUT-------------*/
extern std::array<char, 79> CARATTERI_POSSIBILI;
extern std::array<char, 1> INVIO;
extern std::array<char, 2> BACKSPACE;
extern std::array<char, 1> DEBUG;
extern std::array<char, 1> ESCI;  


#endif