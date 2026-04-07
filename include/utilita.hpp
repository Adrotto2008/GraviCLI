#ifndef UTILITA_HPP
#define UTILITA_HPP

#include "costanti.hpp"

struct Casella;

#ifndef __linux__

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <conio.h>

#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif



#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <thread>
#include <random>



// --- Countdown ---
void countdown_input(int tempo);
void countdown_caduta(int tempo);

// --- Terminale/Console (compatibilità Linux) ---
void cmd_type();
void disabilita_echo();
void ripristina_echo();

// --- Output e cursore ---
void scritta(int dormi, const std::string& testo);
void cursore_manuale(short x, short y);
void posizione_cursore(COORD coord_posizione);
void cursore_alto(COORD* coord_posizione, short delta);
void cursore_basso(COORD* coord_posizione, short delta);
void cursore_sinistra(COORD* coord_posizione, short delta);
void cursore_destra(COORD* coord_posizione, short delta);
COORD posizione_attuale();
void nascondi_cursore();
void mostra_cursore();
void pulisci();
void cmd_grande();
short lunghezza_terminale_x();
short lunghezza_terminale_y();

#ifdef __linux__
// --- Input ---
int _getch();
bool kbhit();
#endif


// --- Random ---
int numero_casuale(int min, int max);
GRAVITA controllo_gravita(GRAVITA gravita, char stringa[]);
void controllo_colori_testo(Casella casella);
void controllo_colori_sfondo(Casella casella);

std::string string_to_upper(std::string str);

#endif // UTILITA_HPP
