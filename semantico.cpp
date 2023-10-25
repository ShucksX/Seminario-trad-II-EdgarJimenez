#include "semantico.h"

Semantico::Semantico() {
    variablesCont = 0;
    funcionesCont = 0;
    funcionActual = "#";
}

void Semantico::start(Sintactico sintactico) {
    sint = sintactico;
    variablesCont = 0;
    funcionesCont = 0;
    funcionActual = "#";
    cout << "Semantico: " << endl;

    while (sint.getPilaSize() != 0) {
        analizarNodo(sint.pilaTop());
        sint.popPila();
    }
}

//BIG WIP Empieza a manejar el arbol para la creacion y verificacion de las tablas semanticas.
void Semantico::analizarNodo(ElementoPila* elemento) {
    stack<ElementoPila*> nodo = elemento->getNodo();
    while (nodo.size() != 0) {
        if (!(nodo.top()->getToken().find("DefFunc") == string::npos)) {
            cout << "Funcion:" << endl;
            nodo.top()->printToken(0);
        }
        else {
            analizarNodo(nodo.top());
        }
        nodo.pop();
    }
}

bool Semantico::encontrarFuncion(string nombre) {
    if (funcionesCont > 0) {
        for (int i = 0; i < funcionesCont; i++) {
            if (funciones[i][1].compare(nombre) == 0) {
                return true;
            }
        }
        return false;
    }
    else {
        return false;
    }
}

bool Semantico::encontrarVariable(string nombre, string ambito) {
    if (variablesCont > 0) {
        for (int i = 0; i < variablesCont; i++) {
            if (funciones[i][1].compare(nombre) == 0) {
                if (funciones[i][2].compare(ambito) == 0) {
                    return true;
                }
            }
        }
        return false;
    }
    else {
        return false;
    }
}

void Semantico::printFunciones() {
    cout << "Funciones:" << endl;
    cout << "Tipo\t\tNombre\t\tParametros" << endl;
    if (funcionesCont > 0) {
        for (int i = 0; i < funcionesCont; i++) {
            cout << funciones[i][0] << "\t\t" << funciones[i][1] << "\t\t" << funciones[i][2] <<  endl;
        }
    }
    else {
        cout << "La tabla esta vacia" << endl;
    }
}

void Semantico::printVariables() {
    cout << "Variables:" << endl;
    cout << "Tipo\t\tNombre\t\tAmbito\t\tParametro" << endl;
    if (variablesCont > 0) {
        for (int i = 0; i < variablesCont; i++) {
            cout << variables[i][0] << "\t\t" << variables[i][1] << "\t\t" << variables[i][2] << "\t\t" << variables[i][3] << endl;
        }
    }
    else {
        cout << "La tabla esta vacia" << endl;
    }
}
