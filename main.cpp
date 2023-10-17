// Seminario-trad-II-EdgarJimenez.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include <string>
#include "lexico.h"
#include "sintactico.h"

using namespace std;

//Jimenez Aceves Edgar D02

int main() {
    Lexico lexico;
    Sintactico sintactico;

    char cadena[200];
    cout << "Compilador" << endl;
    string line;
    ifstream myfile("codigo.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            strcpy_s(cadena, line.c_str());
        }
        myfile.close();
    }

    else {
        cout << "Unable to open file";
        return 0;
    }


    lexico.entrada(cadena);
    sintactico.empezar();
    //sintactico.printLR();
    cout << "Estado en pila\t\tEntrada\t\tSalida" << endl;
    bool lexicoFlag = true;
    string entradaSint = lexico.getCadenaFromInd();
    string back = sintactico.pilaTop()->getToken();
    lexico.sigSimbolo();

    string salida = sintactico.salida(lexico.token, lexico.tipo);
    while (salida.compare("r0") != 0) {
        entradaSint = lexico.getCadenaFromInd();
        string pilaString = sintactico.pilaToString();
        if (lexico.tipo < 0) {
            lexicoFlag = false;
        }
        if (salida.empty()) {
            cout << pilaString << "\t\t\t" << entradaSint << "$\t\t" << "Error" << endl;

            cout << "Resultado del analisis sintactico: Error" << endl;
            break;
        }
        else {
            cout << pilaString << "\t\t\t"<< entradaSint  << "$\t\t" << salida << endl;
        }
        back = sintactico.pilaTop()->getToken();
        if (salida.find("-e") == string::npos)
            lexico.sigSimbolo();
        salida = sintactico.salida(lexico.token, lexico.tipo);
    }
    if (salida.compare("r0") == 0) {
        cout << sintactico.pilaToString() << "\t\t\t" << entradaSint << "$\t\t" << "r0 (acept)" << endl;
        cout << "Resultado del analisis sintactico: Correcto" << endl;
        
    }
    cout << "Arbol de la pila: " << endl;

    while (sintactico.getPilaSize() != 0) {
        sintactico.pilaTop()->printToken(0);
        sintactico.popPila();
    }

    //RESULTADO DE ANALISIS LEXICO
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
