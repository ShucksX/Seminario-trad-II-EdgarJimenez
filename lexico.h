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
    bool esPunto(char c);
    bool esEspacio(char c);
    bool esSuma(char c);
    bool esMul(char c);
    bool esRelacion(char c);
    bool esIgual(char c);
    bool esOr(char c);
    bool esAnd(char c);
    bool esNot(char c);
    bool esParentesisI(char c);
    bool esParentesisD(char c);
    bool esLlaveI(char c);
    bool esLlaveD(char c);
    bool esPuntoyComa(char c);
    bool esComa(char c);
    bool esComillas(char c);
    bool esValido(char c);
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
    string getCadenaFromInd();
};

#endif
