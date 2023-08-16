#include "lexico.h"

Lexico::Lexico() {
    ind = 0;
}

void Lexico::entrada(string cadena) {
    ind = 0;
    this->cadena = cadena;
}