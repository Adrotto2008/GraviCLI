#include "../include/utilita.hpp"
#include "../include/campo.hpp"

#if !defined(_WIN32)
#include <sys/ioctl.h>
#endif

using namespace std;
using namespace chrono;
using namespace chrono_literals;

int timer_input;
int timer_input_origine = 1000;
int timer_caduta;
int timer_caduta_origine = 300;
int timer_scambio = 15000;

#if !defined(_WIN32)
termios term_originale;

// ---------------- Console ----------------

void cmd_type(){
    return;
}

void disabilita_echo() {
    tcgetattr(STDIN_FILENO, &term_originale); // salva lo stato originale
    termios nuovo = term_originale;
    nuovo.c_lflag &= ~(ICANON | ECHO); // disabilita canonica e echo
    tcsetattr(STDIN_FILENO, TCSANOW, &nuovo);
}

void ripristina_echo() {
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void scritta(int dormi, const std::string& testo) {
    for (char c : testo) {
        cout << c << flush;
        disabilita_echo();
        std::this_thread::sleep_for(std::chrono::milliseconds(dormi));
        if (kbhit()) { _getch(); dormi = 0; }//getch
    }
}

void pulisci() { cout << "\033[2J\033[H" << flush; }
void cursore_manuale(short x, short y) { cout << "\033[" << y+1 << ";" << x+1 << "H" << flush; }
void posizione_cursore(COORD c) { cursore_manuale(c.X, c.Y); }
void cursore_alto(COORD* c, short d) { c->Y -= d; posizione_cursore(*c); }
void cursore_basso(COORD* c, short d) { c->Y += d; posizione_cursore(*c); }
void cursore_sinistra(COORD* c, short d) { c->X -= d; posizione_cursore(*c); }
void cursore_destra(COORD* c, short d) { c->X += d; posizione_cursore(*c); }
COORD posizione_attuale() {

    COORD posizione;

//    posizione.X = ;
//    posizione.Y = ;

    return posizione;

}
void nascondi_cursore() { cout << "\033[?25l" << flush; }
void mostra_cursore()   { cout << "\033[?25h" << flush; }
void cmd_grande() { /* non esiste su Linux → no-op */ }

// ---------------- Input ----------------

int _getch() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

bool kbhit() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}
#else

// ---------------- Terminale/Console (compatibilità POSIX) ----------------

void cmd_type(){
    // Imposta la console a UTF-8 (SOLO la code page)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Abilita le sequenze ANSI (VT100) su console Windows moderne.
    auto abilita_vt = [](DWORD stdHandleId) {
        HANDLE h = GetStdHandle(stdHandleId);
        if (h == INVALID_HANDLE_VALUE || h == nullptr) return;

        DWORD mode = 0;
        if (!GetConsoleMode(h, &mode)) return;

        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(h, mode);
    };

    abilita_vt(STD_OUTPUT_HANDLE);
    abilita_vt(STD_ERROR_HANDLE);
}

void disabilita_echo() {
    // Su Windows l'echo è gestito diversamente, ma manteniamo la funzione vuota
    // per compatibilità con il codice Linux
}

void ripristina_echo() {
    // Su Windows l'echo è gestito diversamente, ma manteniamo la funzione vuota
    // per compatibilità con il codice Linux
}

// ---------------- Output e cursore ----------------

void scritta(int dormi, const std::string& testo) {
    for (char c : testo) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(dormi));
        if (_kbhit()) { _getch(); dormi = 0; }
    }
}

void pulisci() { system("cls"); }

void cursore_manuale(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord_posizione = {x, y};
    SetConsoleCursorPosition(hConsole, coord_posizione);
}

void posizione_cursore(COORD c) { cursore_manuale(c.X, c.Y); }

void cursore_alto(COORD* c, short d) { c->Y -= d; posizione_cursore(*c); }
void cursore_basso(COORD* c, short d) { c->Y += d; posizione_cursore(*c); }
void cursore_sinistra(COORD* c, short d) { c->X -= d; posizione_cursore(*c); }
void cursore_destra(COORD* c, short d) { c->X += d; posizione_cursore(*c); }

COORD posizione_attuale() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void nascondi_cursore() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void mostra_cursore() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void cmd_grande() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, NULL);
}

// ---------------- Input ----------------
/*
int _getch() {
    return ::_getch();  // chiama la versione di conio.h
}

bool kbhit() {
    return ::_kbhit() != 0;  // chiama la versione di conio.h
}
*/
void countdown_input(int tempo) {
    this_thread::sleep_for(milliseconds(tempo));
    timer_input = 0;
}

void countdown_caduta(int tempo) {
    this_thread::sleep_for(milliseconds(tempo));
    timer_caduta = 0;
}

#endif

short lunghezza_terminale_x() {
#if !defined(_WIN32)
    winsize ws{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0) {
        return static_cast<short>(ws.ws_col);
    }

    const char* colonne = std::getenv("COLUMNS");
    if (colonne != nullptr) {
        int valore = std::atoi(colonne);
        if (valore > 0) return static_cast<short>(valore);
    }

    return 80;
#else
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE && hConsole != nullptr) {
        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            int larghezza = static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1);
            if (larghezza > 0) return static_cast<short>(larghezza);
        }
    }

    const char* colonne = std::getenv("COLUMNS");
    if (colonne != nullptr) {
        int valore = std::atoi(colonne);
        if (valore > 0) return static_cast<short>(valore);
    }

    return 80;
#endif
}

short lunghezza_terminale_y() {
#if !defined(_WIN32)
    winsize ws{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_row > 0) {
        return static_cast<short>(ws.ws_row);
    }

    const char* righe = std::getenv("LINES");
    if (righe != nullptr) {
        int valore = std::atoi(righe);
        if (valore > 0) return static_cast<short>(valore);
    }

    return 24;
#else
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE && hConsole != nullptr) {
        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            int altezza = static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
            if (altezza > 0) return static_cast<short>(altezza);
        }
    }

    const char* righe = std::getenv("LINES");
    if (righe != nullptr) {
        int valore = std::atoi(righe);
        if (valore > 0) return static_cast<short>(valore);
    }

    return 24;
#endif
}

// ---------------- Random ----------------

int numero_casuale(int min, int max) {
    // Controllo per evitare intervallo non valido
    if (min > max) {
        std::swap(min, max);
    }
    
    // Usa l'orologio di sistema come seed
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> distrib(min, max);
    
    return distrib(gen);
}

//funzioni utili

GRAVITA controllo_gravita(GRAVITA gravita, char stringa[]){

    char stringhe[4][20] = {"su\0", "sinistra\0", "giu\0", "destra\0"};

    for(int i = 0; i < 4; i++){
        if(strstr(stringa, stringhe[i]) != NULL){
            if(gravita == static_cast<GRAVITA>((i+2) % 4)){

            }else{
                gravita = static_cast<GRAVITA>(i % 4);
                for(int j = 0; j < strlen(stringa); j++) stringa[j] = ' ';
            }
        }
    }

    return gravita;

}

void controllo_colori_testo(Casella casella) {
    switch (casella.coloreTesto) {
        case Colore::rosso:
            printf(TESTO_ROSSO);
            break;

        case Colore::ciano:
            printf(TESTO_CIANO);
            break;

        case Colore::blu:
            printf(TESTO_BLU);
            break;

        case Colore::arancione:
            printf(TESTO_ARANCIONE);
            break;

        case Colore::giallo:
            printf(TESTO_GIALLO);
            break;

        case Colore::verde:
            printf(TESTO_VERDE);
            break;

        case Colore::magenta_chiaro:
            printf(TESTO_MAGENTA_CHIARO);
            break;

        case Colore::marrone:
            printf(TESTO_MARRONE);
            break;

        case Colore::light_green:
            printf(TESTO_LIGHT_GREEN);
            break;

        case Colore::blu_scuro:
            printf(TESTO_BLU_SCURO);
            break;

        case Colore::ciano_chiaro:
            printf(TESTO_CIANO_CHIARO);
            break;

        case Colore::light_yellow:
            printf(TESTO_LIGHT_YELLOW);
            break;

        case Colore::magenta:
            printf(TESTO_MAGENTA);
            break;

        case Colore::bianco:
            printf(TESTO_BIANCO);
            break;

        case Colore::grigio_chiaro:
            printf(TESTO_GRIGIO);
            break;

        case Colore::nero:
            printf(TESTO_NERO);
            break;

        case Colore::reset:
            printf(RESET);
            break;

        default:
            break;
    }
}


void controllo_colori_sfondo(Casella casella) {
    switch (casella.coloreSfondo) {
        case Colore::rosso:
            printf(SFONDO_ROSSO);
            break;

        case Colore::ciano:
            printf(SFONDO_CIANO);
            break;

        case Colore::blu:
            printf(SFONDO_BLU);
            break;

        case Colore::arancione:
            printf(SFONDO_ARANCIONE);
            break;

        case Colore::giallo:
            printf(SFONDO_GIALLO);
            break;

        case Colore::verde:
            printf(SFONDO_VERDE);
            break;

        case Colore::magenta_chiaro:
            printf(SFONDO_MAGENTA_CHIARO);
            break;

        case Colore::marrone:
            printf(SFONDO_MARRONE);
            break;

        case Colore::light_green:
            printf(SFONDO_LIGHT_GREEN);
            break;

        case Colore::blu_scuro:
            printf(SFONDO_BLU_SCURO);
            break;

        case Colore::ciano_chiaro:
            printf(SFONDO_CIANO_CHIARO);
            break;

        case Colore::light_yellow:
            printf(SFONDO_LIGHT_YELLOW);
            break;

        case Colore::magenta:
            printf(SFONDO_MAGENTA);
            break;

        case Colore::bianco:
            printf(SFONDO_BIANCO);
            break;

        case Colore::grigio_chiaro:
            printf(SFONDO_GRIGIO_CHIARO);
            break;

        case Colore::nero:
            printf(SFONDO_NERO);
            break;

        case Colore::reset:
            printf(RESET);
            break;

        default:
            break;
    }
}

std::string string_to_upper(std::string stringa) {
    std::ranges::transform(stringa, stringa.begin(),
        [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return stringa;
}
