// Seminario-trad-II-EdgarJimenez.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "lexico.h"

using namespace std;

int main() {
    Lexico lexico;

    string cadena;
    cout << "Por favor inserte su codigo aqui:";
    cin >> cadena;

    lexico.entrada(cadena);

    cout << "Resultado del analisis lexico:" << endl;
    cout << "Palabra\t\tTipo";

    return 0;
}

