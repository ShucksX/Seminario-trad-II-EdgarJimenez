#include "lexico.h"

Lexico::Lexico() {
    ind = 0;
    estado = 0;
    tipo = 0;
    ch = 'd';
    continuar = true;
}

void Lexico::entrada(char cadena [200]) {
    ind = 0;
    this->cadena = cadena;

}

bool Lexico::fin() {
    if (ind < cadena.size()) {
        return false;
    }
    else
        return true;
}

void Lexico::sigSimbolo() {
    estado = 0;
    continuar = true;
    token = "";
    //Inicia el automata
    while (continuar) {
        ch = sigCaracter();
        switch (estado) {
            case 0: if (esLetra(ch)) {
                estado = 1; //Estado para aceptar letras y numeros
                token += ch;
            }
                  else if (esDigito(ch)) {
                    estado = 2; //Estado para numeros
                    token += ch;
            }
                  else if (esEspacio(ch)) {
                        //No se hace nada en realidad, solo sigue consumiendo
                  }
                  else if(ch== '$'){
                    return;
                  }
                  else {
                  estado = 3; //Estado para cadenas de error
                  token += ch;
            }
            break;

            case 1: //Identificador
                if (esLetra(ch) || esDigito(ch)) {
                token += ch;
                }
                  else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                  }
                  else {
                    volver();
                    tipo = 0;
                    simbolo = "Identificador";
                  }
            break;

            case 2: //Enteros
                if (esDigito(ch)) {
                token += ch;
                }
                else if (ch == '.') {
                estado = 4; //Estado de punto decimal
                token += ch;
                }
                  else if (esEspacio(ch) || ch == '$') {
                continuar = false;
                tipo = 1;
                simbolo = "Entero";
                }
                  else {
                volver();
                tipo = 1;
                simbolo = "Entero";
                }
                break;
            case 3: //Cadenas de error
                if (esLetra(ch) || esDigito(ch)) {
                    volver();
                    tipo = -1;
                    simbolo = "Error";
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = -1;
                    simbolo = "Error";
                }
                else {
                    token += ch;
                }
            break;

            case 4: //punto decimal
                if (esDigito(ch)) {
                    token += ch;
                    estado = 5; //Estado para numeros reales
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = -1;
                    simbolo = "Error";
                }
                else {
                    volver();
                    tipo = -1;
                    simbolo = "Error";
                }
                break;
            case 5:
                if (esDigito(ch)) {
                    token += ch;
                    estado = 5; //Estado para numeros reales
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 2;
                    simbolo = "Real";
                }
                else {
                    volver();
                    tipo = 2;
                    simbolo = "Real";
                }
                break;
        }
    }
}

char Lexico::sigCaracter() {
    if (fin()) {
        return '$';
    }
    else {
        return cadena[ind++];
    }
}

bool Lexico::esLetra(char c) {
    return isalpha(c) || c == '_';
}


bool Lexico::esDigito(char c) {
    return isdigit(c);
}

bool Lexico::esEspacio(char c) {
    return c == ' ' || c == '\t';
}


void Lexico::volver() {
    ind--;
    continuar = false;
}