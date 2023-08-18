// Seminario-trad-II-EdgarJimenez.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "lexico.h"

using namespace std;

//Jimenez Aceves Edgar D02

int main() {
    Lexico lexico;

    char cadena [200];
    cout << "Por favor inserte su codigo aqui:";
    cin.getline(cadena,200);

    lexico.entrada(cadena);

    cout << "Resultado del analisis lexico:" << endl;
    cout << "Palabra\t\tSimbolo\t\tTipo" << endl;

    while (lexico.ch != '$') {
        lexico.sigSimbolo();
        cout << lexico.token << "\t\t" << lexico.simbolo << "\t\t" << lexico.tipo << endl;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Programa terminado, presiona enter para terminar" << endl;
    cin.get();

    return 0;
}

