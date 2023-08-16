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
    char ch;
    int estado;

public:
    Lexico();
    void entrada(string cadena);
};

#endif
