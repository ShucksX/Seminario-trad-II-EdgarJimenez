#pragma once

#ifndef _LEXICO
#define _LEXICO

#include <iostream>
#include <string>
using namespace std;

class Lexico {
private:
    string cadena;
    int ind;
    bool continuar;
    int estado;
    char sigCaracter();
    bool esLetra(char c);
    bool esDigito(char c);
    bool esEspacio(char c);
    void volver();

public:
    char ch;
    string token;
    string simbolo;
    int tipo;
    Lexico();
    void entrada(char cadena [200]);
    bool fin();
    void sigSimbolo();
};

#endif
