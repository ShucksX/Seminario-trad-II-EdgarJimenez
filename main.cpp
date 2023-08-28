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
    cout << "Por favor inserte su codigo aqui: " << endl;
    cin.getline(cadena,200);

    lexico.entrada(cadena);

    //cout << "Palabra\t\tSimbolo\t\tTipo" << endl;
    bool lexicoFlag = true;
    while (lexico.ch != '$') {
        lexico.sigSimbolo();
        if (lexico.tipo < 0) {
            lexicoFlag = false;
        }
        //cout << lexico.token << "\t\t" << lexico.simbolo << "\t\t" << lexico.tipo << endl;
    }
    cout << "Resultado del analisis lexico: ";
    if (lexicoFlag) {
        cout << "Correcto" << endl;
    }
    else {
        cout << "Error" << endl;
    }

    cout << "Programa terminado, presiona enter para terminar" << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();

    return 0;
}

