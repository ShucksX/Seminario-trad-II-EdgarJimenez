#include "semantico.h"

Semantico::Semantico() {
    variablesCont = 0;
    funcionesCont = 0;
    funcionActual = "#";
}

bool Semantico::start(Sintactico sintactico) {
    sint = sintactico;
    variablesCont = 0;
    funcionesCont = 0;
    funcionActual = "#";    
    while (sint.getPilaSize() != 0) {
        if (!analizarNodo(sint.pilaTop())) {
            return false;
        }
        sint.popPila();
    }
    return true;
}

string Semantico::getError() {
    return error;
}

//BIG WIP Empieza a manejar el arbol para la creacion y verificacion de las tablas semanticas.
bool Semantico::analizarNodo(ElementoPila* elemento) {
    stack<ElementoPila*> nodo = elemento->getNodo();
    while (nodo.size() != 0) {
        if (!(nodo.top()->getToken().find("DefFunc") == string::npos)) {
            //Accede a funciones
            cout << "Funcion:" << endl;
            nodo.top()->printToken(0);
        }
        else if (!(nodo.top()->getToken().find("DefVar") == string::npos)) {
            //Obtiene vartiables globales
            if (!variableGlobal(nodo.top()->getNodo())) {
                return false;
            }
        }
        else {
            if (!analizarNodo(nodo.top()))
                return false;
        }
        nodo.pop();

    }
    return true;
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
            if (variables[i][1] == nombre) {
                if (variables[i][2] == ambito || variables[i][2] == "#") {
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

bool Semantico::variableGlobal(stack<ElementoPila*> nodo) {
    string tipo = nodo.top()->getToken();
    nodo.pop();
    string variable = nodo.top()->getToken();
    nodo.pop();
    if (encontrarVariable(variable, "#")) {
        error = "La variable " + variable + " ya existe en el ambito actual o global.";
        return false;
    }
    addVariable(tipo, variable, "#", "np");
    bool correcto = ListaVar(nodo.top()->getNodo(),tipo,"#");
    nodo.pop();
    return correcto;
}

bool Semantico::ListaVar(stack<ElementoPila*> nodo, string tipo, string ambito) {
    if (!nodo.empty()) {
        //Empieza con pop por la coma;
        nodo.pop();
        string variable = nodo.top()->getToken();
        nodo.pop();
        if (encontrarVariable(variable, ambito)) {
            error = "La variable " + variable + " ya existe en el ambito actual o global.";
            return false;
        }
        addVariable(tipo, variable, ambito, "np");
        bool correcto = ListaVar(nodo.top()->getNodo(), tipo, ambito);
        nodo.pop();
        return correcto;
    }
    return true;
}

void Semantico::addVariable(string tipo, string variable, string ambito, string parametro) {
    if (variablesCont < 100) {
        variables[variablesCont][0] = tipo;
        variables[variablesCont][1] = variable;
        variables[variablesCont][2] = ambito;
        variables[variablesCont][3] = parametro;
        variablesCont++;
    }
}
