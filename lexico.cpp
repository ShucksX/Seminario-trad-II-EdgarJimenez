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
    tipo = -1;
    simbolo = "";
    //Inicia el automata
    while (continuar) {
        ch = sigCaracter();
        switch (estado) {
            case 0:
             if (ch == 'i') {
                    estado = 11;
                    token += ch;
             }
             else if (ch == 'w') {
                 estado = 15;
                 token += ch;
             }
             else if (ch == 'r') {
                 estado = 20;
                 token += ch;
             }
             else if (ch == 'e') {
                 estado = 26;
                 token += ch;
             }
             else if (ch == 'f') {
                 estado = 30;
                 token += ch;
             }
                else if (esLetra(ch)) {
                    estado = 1; 
                    token += ch;
                }
                  else if (esDigito(ch)) {
                    estado = 2; 
                    token += ch;
                  }
                  else if (esSuma(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 1;
                    simbolo = "opSuma";
                  }
                  else if (esMul(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 6;
                    simbolo = "opMul";
                }

                  else if (esPuntoyComa(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 12;
                    simbolo = "Punto y coma";
                }

                  else if (esParentesis(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 14;
                    simbolo = "Parentesis";
                }
                  else if (esLlave(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 16;
                    simbolo = "Llave";
                }
                  else if (esRelacion(ch)) {
                    token += ch;
                    estado = 6;
                }
                  else if (esOr(ch)) {
                    token += ch;
                    estado = 7;
                }
                  else if (esAnd(ch)) {
                    token += ch;
                    estado = 8;
                }
                  else if (esNot(ch)) {
                    token += ch;
                    estado = 9;
                }
                  else if (esIgual(ch)) {
                    token += ch;
                    estado = 10;
                }
                  else if (esEspacio(ch)) {
                        //No se hace nada en realidad, solo sigue consumiendo
                  }
                  else if(ch== '$'){
                    token += ch;
                    tipo = 2;
                    simbolo = "Fin de entrada";
                    continuar = false;
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
                else if (esPunto(ch)) {
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
                tipo = 9999; //TODO ESTA CAMBIADO PARA EL SINTACTICO INICIAL
                simbolo = "Entero";
                }
                break;
            case 3: //Cadenas de error
                if (esEspacio(ch) || ch == '$') {
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
            case 5: //Reales 
                if (esDigito(ch)) {
                    token += ch;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 9999; //TODO ESTO CAMBIA EN SINTACTICO COMPLETO
                    simbolo = "Real";
                }
                else {
                    volver();
                    tipo = 9999; //TODO ESTO CAMBIA EN SINTACTICO COMPLETO
                    simbolo = "Real";
                }
                break;
            case 6: //OpRelac
                if (esIgual(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 7;
                    simbolo = "OpRelac";
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 7;
                    simbolo = "OpRelac";
                }
                else {
                    volver();
                    tipo = 7;
                    simbolo = "OpRelac";
                }
                break;
            case 7: //OpOr
                if (esOr(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 8;
                    simbolo = "OpOr";
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
            case 8: //OpAnd
                if (esAnd(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 9;
                    simbolo = "OpAnd";
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
            case 9: //OpNot o OpIgualdad
                if (esIgual(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 11;
                    simbolo = "OpIgualdad";
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 10;
                    simbolo = "OpNot";
                }
                else {
                    volver();
                    tipo = 10;
                    simbolo = "OpNot";
                }
                break;
            case 10: //Igual o OpIgualdad
                if (esIgual(ch)) {
                    token += ch;
                    continuar = false;
                    tipo = 11;
                    simbolo = "OpIgualdad";
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 18;
                    simbolo = "Igual";
                }
                else {
                    volver();
                    tipo = 18;
                    simbolo = "Igual";
                }
                break;
            case 11: //if o int
                if (ch == 'f') {
                    token += ch;
                    estado = 12;
                }
                else if (ch == 'n') {
                    token += ch;
                    estado = 13;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 12: //check that its not an identifier starting with if
                if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 19;
                    simbolo = "if";
                }
                else if (esLetra(ch) || esDigito(ch)) {
                    token += ch;
                    estado = 1;
                }
                else {
                    volver();
                    tipo = 19;
                    simbolo = "if";
                }
                break;
            case 13: //in
                if (ch == 't') {
                    token += ch;
                    estado = 14;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 14: //check that its not an identifier starting with int
                if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 4;
                    simbolo = "Tipo";
                }
                else if (esLetra(ch) || esDigito(ch)) {
                    token += ch;
                    estado = 1;
                }
                else {
                    volver();
                    tipo = 4;
                    simbolo = "Tipo";
                }
                break;
            case 15: //While
                if (ch == 'h') {
                    token += ch;
                    estado = 16;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 16: //Wh
                if (ch == 'i') {
                    token += ch;
                    estado = 17;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 17: //Whi
                if (ch == 'l') {
                    token += ch;
                    estado = 18;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 18: //Whil
                if (ch == 'e') {
                    token += ch;
                    estado = 19;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 19: //check that its not an identifier starting with while
                if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 20;
                    simbolo = "While";
                }
                else if (esLetra(ch) || esDigito(ch)) {
                    token += ch;
                    estado = 1;
                }
                else {
                    volver();
                    tipo = 20;
                    simbolo = "While";
                }
                break;
            case 20: //Return
                if (ch == 'e') {
                    token += ch;
                    estado = 21;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 21: //Re
                if (ch == 't') {
                    token += ch;
                    estado = 22;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 22: //Ret
                if (ch == 'u') {
                    token += ch;
                    estado = 23;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 23: //Retu
                if (ch == 'r') {
                    token += ch;
                    estado = 24;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 24: //Retur
                if (ch == 'n') {
                    token += ch;
                    estado = 25;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 25: //check that its not an identifier starting with return
                if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 21;
                    simbolo = "Return";
                }
                else if (esLetra(ch) || esDigito(ch)) {
                    token += ch;
                    estado = 1;
                }
                else {
                    volver();
                    tipo = 21;
                    simbolo = "Return";
                }
                break;
            case 26: //Else
                if (ch == 'l') {
                    token += ch;
                    estado = 27;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 27: //El
                if (ch == 's') {
                    token += ch;
                    estado = 28;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 28: //Els
                if (ch == 'e') {
                    token += ch;
                    estado = 29;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 29: //check that its not an identifier starting with else
                if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 22;
                    simbolo = "Else";
                }
                else if (esLetra(ch) || esDigito(ch)) {
                    token += ch;
                    estado = 1;
                }
                else {
                    volver();
                    tipo = 22;
                    simbolo = "Else";
                }
                break;
            case 30: //Float
                if (ch == 'l') {
                    token += ch;
                    estado = 31;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 31: //Fl
                if (ch == 'o') {
                    token += ch;
                    estado = 32;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 32: //Flo
                if (ch == 'a') {
                    token += ch;
                    estado = 33;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 33: //Floa
                if (ch == 't') {
                    token += ch;
                    estado = 34;
                }
                else if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 0;
                    simbolo = "Identificador";
                }
                else {
                    ind--;
                    estado = 1;
                }
                break;
            case 34: //check that its not an identifier starting with float
                if (esEspacio(ch) || ch == '$') {
                    continuar = false;
                    tipo = 4;
                    simbolo = "Tipo";
                }
                else if (esLetra(ch) || esDigito(ch)) {
                    token += ch;
                    estado = 1;
                }
                else {
                    volver();
                    tipo = 4;
                    simbolo = "Tipo";
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

bool Lexico::esPunto(char c) {
    return c == '.';
}

bool Lexico::esEspacio(char c) {
    return c == ' ' || c == '\t';
}

bool Lexico::esSuma(char c) {
    return c == '+' || c == '-';
}

bool Lexico::esMul(char c) {
    return c == '*' || c == '/';
}

bool Lexico::esRelacion(char c) {
    return c == '<' || c == '>';
}

bool Lexico::esIgual(char c) {
    return c == '=';
}

bool Lexico::esNot(char c) {
    return c == '!';
}

bool Lexico::esAnd(char c) {
    return c == '&';
}

bool Lexico::esOr(char c) {
    return c == '|';
}

bool Lexico::esParentesis(char c) {
    return c == '(' || c == ')';
}

bool Lexico::esLlave(char c) {
    return c == '{' || c =='}';
}

bool Lexico::esPuntoyComa(char c) {
    return c == ';';
}


void Lexico::volver() {
    ind--;
    continuar = false;
}

string  Lexico::getCadenaFromInd() {
    return cadena.substr(ind);
}