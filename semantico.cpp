#include "semantico.h"

Semantico::Semantico() {
    variablesCont = 0;
    funcionesCont = 0;
    indArg = 0;
}

bool Semantico::start(Sintactico sintactico) {
    sint = sintactico;
    variablesCont = 0;
    funcionesCont = 0;  
    indArg = 0;
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

//BIG WIP Empieza a manejar el arbol para la creacion y verificacion de las tablas semanticas. AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAS
bool Semantico::analizarNodo(ElementoPila* elemento) {
    stack<ElementoPila*> nodo = elemento->getNodo();
    while (nodo.size() != 0) {
        if (!(nodo.top()->getToken().find("DefFunc") == string::npos)) {
            //Accede a funciones
            if (!funcion(nodo.top()->getNodo())) {
                return false;
            }
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

bool Semantico::funcion(stack<ElementoPila*> nodo){
    string tipo = nodo.top()->getToken();
    nodo.pop();
    string funcion = nodo.top()->getToken();
    nodo.pop();
    //Un pop mas por el parentesis
    nodo.pop();
    string param = parametros(nodo.top()->getNodo(), funcion);
    nodo.pop();
    if (param.find("e") == string::npos) {
        addFuncion(tipo, funcion, param);
        //un pop mas por el otro parentesis
        nodo.pop();
        if (!bloqFunc(nodo.top()->getNodo(), funcion)) {
            return false;
        }
        nodo.pop();
        return true;
    }
    else {
        return false;
    }
}

string Semantico::parametros(stack<ElementoPila*> nodo, string ambito) {
    if (nodo.empty()) {
        return "sp";
    }
    else {
        string tipo = nodo.top()->getToken();
        nodo.pop();
        string variable = nodo.top()->getToken();
        nodo.pop();
        if (encontrarVariable(variable, ambito)) {
            error = "El parametro \"" + variable + "\" ya fue definida globalmente o en el ambito " + ambito + ".";
            return "e";
        }
        addVariable(tipo, variable, ambito, "p");
        string params;
        if (tipo == "int") {
            params = "i";
        }
        else {
            params = "f";
        }
        params += listaParametros(nodo.top()->getNodo(), ambito);
        nodo.pop();
        return params;
    }
}

string Semantico::listaParametros(stack<ElementoPila*> nodo, string ambito) {
    if (nodo.empty()) {
        return "";
    }
    else {
        //Se hace un pop primero debido a la coma
        nodo.pop();
        string tipo = nodo.top()->getToken();
        nodo.pop();
        string variable = nodo.top()->getToken();
        nodo.pop();
        if (encontrarVariable(variable, ambito)) {
            error = "El parametro \"" + variable + "\" ya fue definida globalmente o en el ambito " + ambito + ".";
            return "e";
        }
        addVariable(tipo, variable, ambito, "p");
        string params;
        if (tipo == "int") {
            params = "i";
        }
        else {
            params = "f";
        }
        params += listaParametros(nodo.top()->getNodo(), ambito);
        nodo.pop();
        return params;
    }
}

bool Semantico::bloqFunc(stack<ElementoPila*> nodo, string ambito) {
    while (nodo.size() != 0) {
        if (!(nodo.top()->getToken().find("DefVar") == string::npos)) {
            //Obtiene vartiables locales
            if (!variableLocal(nodo.top()->getNodo(),ambito)) {
                return false;
            }
        }
        else if (!(nodo.top()->getToken().find("Sentencia") == string::npos)) {
            //Obtiene sentencias
            if(!sentencia(nodo.top()->getNodo(),ambito)){
                return false;
            }

        }
        else {
            if (!bloqFunc(nodo.top()->getNodo(),ambito))
                return false;
        }
        nodo.pop();

    }
    return true;
}

bool Semantico::sentencia(stack<ElementoPila*> nodo, string ambito) {
    while (nodo.size() != 0) {
        if (!(nodo.top()->getToken().find("LlamadaFunc") == string::npos)) {
            //Obtiene llamadas a funcion
            if (!llamadaFunc(nodo.top()->getNodo(), ambito)) {
                return false;
            }
        }
        else if (nodo.top()->getTipo() == 0) {
            //Obtiene uso de variables en sentencia
            if (!usoVar(nodo, ambito)) {
                return false;
            }
        }
        else {
            if (!sentencia(nodo.top()->getNodo(), ambito))
                return false;
        }
        nodo.pop();

    }
    return true;
}

bool Semantico::llamadaFunc(stack<ElementoPila*> nodo, string ambito) {
    int indF = existenciaFuncion(nodo.top()->getToken());
    if (indF != -1) {
        indArg = 0;
        cout << "Llamada a la funcion " + nodo.top()->getToken() + ", esta es de tipo " + funciones[indF][0] << endl;
        return true;
    }
    else {
        error = "La funcion " + nodo.top()->getToken() +" no esta definida.";
        return false;
    }
}
//WIP
bool Semantico::argumentos(stack<ElementoPila*> nodo, string ambito) {
    while (nodo.size() != 0) {
        if (!(nodo.top()->getToken().find("LlamadaFunc") == string::npos)) {
            //Obtiene llamadas a funcion
            if (!llamadaFunc(nodo.top()->getNodo(), ambito)) {
                return false;
            }
        }
        else if (nodo.top()->getTipo() == 0) {
            //Obtiene uso de variables en sentencia
            if (!usoVar(nodo, ambito)) {
                return false;
            }
        }
        else {
            if (!sentencia(nodo.top()->getNodo(), ambito))
                return false;
        }
        nodo.pop();

    }
    return true;
}

bool Semantico::usoVar(stack<ElementoPila*> nodo, string ambito) {
    int indV = existenciaVariable(nodo.top()->getToken(), ambito);
    if (indV != -1) {
        cout << "Uso de variable " + nodo.top()->getToken() + ", esta es de tipo " + variables[indV][0] + " y esta en el ambito " + ambito << endl;
        return true;
    }
    else {
        error = "La variable " + nodo.top()->getToken() + " no esta definida en el ambito " + ambito + " o global";
        return false;
    }
}

int Semantico::existenciaFuncion(string funcion) {
    if (funcionesCont > 0) {
        for (int i = 0; i < funcionesCont; i++) {
            if (funciones[i][1] == funcion) {
                return i;
            }
        }
        return -1;
    }
    else {
        return -1;
    }
}

int Semantico::existenciaVariable(string variable, string ambito) {
    if (variablesCont > 0) {
        for (int i = 0; i < variablesCont; i++) {
            if (variables[i][1] == variable) {
                if (variables[i][2] == ambito || variables[i][2] == "#") {
                    return i;
                }
            }
        }
        return -1;
    }
    else {
        return -1;
    }
}

bool Semantico::variableLocal(stack<ElementoPila*> nodo, string ambito) {
    string tipo = nodo.top()->getToken();
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
                if (variables[i][2] == ambito || variables[i][2] == "#" || ambito == "#") {
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

void Semantico::addFuncion(string tipo, string funcion, string parametros) {
    if (funcionesCont < 100) {
        funciones[funcionesCont][0] = tipo;
        funciones[funcionesCont][1] = funcion;
        funciones[funcionesCont][2] = parametros;
        funcionesCont++;
    }
}
