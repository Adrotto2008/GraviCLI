#include "../include/costanti.hpp"

// inizializzo gli array contenenti gli input

std::array<char, 80> CARATTERI_POSSIBILI = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '_', '(', ')', '[', ']', '{', '}', '<', '>',
    '.', ',', '!', '?', ';', ':', '/', '\\', '|'
};

const std::string COMANDI[NUMERO_COMANDI] = {"su", "giu", "sinistra", "destra", "skip"};

std::array<char, 1> INVIO = {13};
std::array<char, 2> BACKSPACE = {'\b', 127};
std::array<char, 1> DEBUG = {'+'};
std::array<char, 1> ESCI = {'-'};

