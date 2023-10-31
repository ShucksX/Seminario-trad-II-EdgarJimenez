#include "semantico.h"

Semantico::Semantico() {
    variablesCont = 0;
    funcionesCont = 0;
    indArg = 0;
    indF = -1;
    indV = -1;
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
     if (!(nodo.top()->getToken().find("LlamadaFunc") == string::npos)) {
         //Obtiene llamadas a funcion
         if (!llamadaFunc(nodo.top()->getNodo(), ambito)) {
                    return false;
         }
     }
     else if (nodo.top()->getTipo() == 0) {
         //Obtiene uso de variables en sentencia
        indV = -1;
        if (!usoVar(nodo, ambito)) {
            return false;
        }
     }
     else {
         while (nodo.top()->getNodo().empty()) {
             nodo.pop();
         }
         if (!buscarExpresion(nodo.top()->getNodo(), ambito)) {
             return false;
         }
     }
     nodo.pop();
     return true;
}

bool Semantico::llamadaFunc(stack<ElementoPila*> nodo, string ambito) {
    indF = existenciaFuncion(nodo.top()->getToken());
    if (indF != -1) {
        indArg = 0;
        //Pop a nombre de funcion
        nodo.pop();
        //Pop a parentesis
        nodo.pop();
        if (!argumentos(nodo.top()->getNodo(),ambito)){
            return false;
        }
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
        //Nodo de expresion
        stack<ElementoPila*> termino = nodo.top()->getNodo();
        //Nodo de termino
        termino = termino.top()->getNodo();
        //Verificar que el argumento existe y concuerda con la funcion
        if (!verificarArgumento(termino.top(), ambito)) {
            return false;
        }
        nodo.pop();
        if (!listaArgumentos(nodo.top()->getNodo(), ambito)) {
            return false;
        }
        return true;
    }
    if (funciones[indF][2].size() == 0) {
        return true;
    }
    else {
        error = "Se estan enviando menos argumentos de los que la funcion " + funciones[indF][1] + " requiere";
        return false;
    }
}

bool Semantico::listaArgumentos(stack<ElementoPila*> nodo, string ambito) {
    while (nodo.size() != 0) {
        //Pop por la coma
        nodo.pop();
        //Nodo de expresion
        stack<ElementoPila*> termino = nodo.top()->getNodo();
        //Nodo de termino
        if(termino.top()->getToken() == "Termino")
            termino = termino.top()->getNodo();
        //Verificar que el argumento existe y concuerda con la funcion
        if (!verificarArgumento(termino.top(), ambito)) {
            return false;
        }
        nodo.pop();
        if (!listaArgumentos(nodo.top()->getNodo(), ambito)) {
            return false;
        }
        return true;
    }
    if (indArg == funciones[indF][2].size()) {
        return true;
    }
    else {
        error = "Se estan enviando menos argumentos de los que la funcion " + funciones[indF][1] + " requiere";
        return false;
    }
}

bool Semantico::verificarArgumento(ElementoPila* argumento, string ambito) {
    //Primero checa si es numero real o entero
    if (argumento->getTipo() == 1) {
        if (indArg >= funciones[indF][2].size()) {
            error = "La funcion " + funciones[indF][1] + " solo acepta " + to_string(funciones[indF][2].size()) + " argumentos.";
            return false;
        }
        if (funciones[indF][2].substr(indArg, 1) == "i") {
            indArg++;
            return true;
        }
        error = "El tipo del argumento " + argumento->getToken() + " no concuerda con la definicion de " + funciones[indF][1];
        return false;
    }
    else if (argumento->getTipo() == 2) {
        if (indArg >= funciones[indF][2].size()) {
            error = "La funcion " + funciones[indF][1] + " solo acepta " + to_string(funciones[indF][2].size()) + " argumentos.";
            return false;
        }
        if (funciones[indF][2].substr(indArg, 1) == "f") {
            indArg++;
            return true;
        }
        error = "El tipo del argumento " + argumento->getToken() + " no concuerda con la definicion de " + funciones[indF][1];
        return false;
    }
    int indA = existenciaVariable(argumento->getToken(), ambito);
    //Primero busca el argumento si esta definido
    if (indA != -1) {
        //Revisar que no sean demasiados argumentos
        if (indArg >= funciones[indF][2].size()) {
            error = "La funcion " + funciones[indF][1] + " solo acepta " + to_string(funciones[indF][2].size()) + " argumentos.";
            return false;
        }
        //Revisar si el tipo de variable concuerda con el parametro de la funcion
        if (variables[indA][0] == "int") {
            if (funciones[indF][2].substr(indArg, 1) == "i") {
                indArg++;
                return true;
            }
        }
        else {
            if (funciones[indF][2].substr(indArg, 1) == "f") {
                indArg++;
                return true;
            }
        }
        error = "El tipo del argumento " + argumento->getToken() + " no concuerda con la definicion de " + funciones[indF][1];
        return false;
    }
    else {
        error = "La variable " + argumento->getToken() + " no esta definida en el ambito " + ambito + " o global";
        return false;
    }
}

bool Semantico::usoVar(stack<ElementoPila*> nodo, string ambito) {
    indV = existenciaVariable(nodo.top()->getToken(), ambito);
    if (indV != -1) {
        //Pop a la variable inicial
        nodo.pop();
        //pop a igual
        nodo.pop();
        //Expresion
        if (!asignacion(nodo.top()->getNodo(), ambito)) {
            return false;
        }
        return true;
    }
    else {
        error = "La variable " + nodo.top()->getToken() + " no esta definida en el ambito " + ambito + " o global";
        return false;
    }
}

bool Semantico::asignacion(stack<ElementoPila*> nodo, string ambito) {
    if (!nodo.empty()) {
        //Expresion
        stack<ElementoPila*> termino = nodo.top()->getNodo();
        //Llega a termino
        if (termino.top()->getToken() == "Termino")
            termino = termino.top()->getNodo();
        if (termino.top()->getToken() == "LlamadaFunc") {
            if (!llamadaFunc(termino.top()->getNodo(), ambito)) {
                return false;
            }
            if (variables[indV][0] != funciones[indF][0]) {
                error = "La funcion " + funciones[indF][1] + " no puede ser asignada a " + variables[indV][1] + " porque los tipos no concuerdan";
                return false;
            }
        }
        else {
            if (!verificarVariable(termino.top(), ambito)) {
                return false;
            }
        }
        nodo.pop();
        //Otro pop por suma o punto y coma o similares
        if(!nodo.empty())
            nodo.pop();
        if (!asignacion(nodo, ambito)) {
            return false;
        }
    }
    return true;
}

bool Semantico::buscarExpresion(stack<ElementoPila*> nodo, string ambito) {
    while (nodo.size() != 0) {
        if (!(nodo.top()->getToken().find("Sentencia") == string::npos)) {
            //Obtiene sentencias
            if (!sentencia(nodo.top()->getNodo(), ambito)) {
                return false;
            }

        }
        /*else if (!(nodo.top()->getToken().find("Expresion") == string::npos)) {
            indV = -1;
            stack<ElementoPila*> termino = nodo.top()->getNodo();
            //Llega a termino
            if (termino.top()->getToken() == "Termino")
                termino = termino.top()->getNodo();
            else {
                return true;
            }
            indV = existenciaVariable(termino.top()->getToken(), ambito);
            if (indV == -1) {
                error = "La variable " + termino.top()->getToken() + " no esta definida en el ambito " + ambito + " o global";
                return false;
            }
            else {
                nodo.pop();
                if(nodo.top()->getNodo().empty())
                    nodo.pop();
                if (!manejarExpresion(nodo.top()->getNodo(), ambito)) {
                    return false;
                }
            }
        }*/
        else {
            if (!buscarExpresion(nodo.top()->getNodo(), ambito))
                return false;
        }
        nodo.pop();

    }
    return true;
}

bool Semantico::manejarExpresion(stack<ElementoPila*> nodo, string ambito) {
    if (!nodo.empty()) {
        //Expresion
        stack<ElementoPila*> termino = nodo.top()->getNodo();
        //Llega a termino
        if (termino.top()->getToken() == "Termino")
            termino = termino.top()->getNodo();
        if (termino.top()->getToken() == "LlamadaFunc") {
            if (!llamadaFunc(termino.top()->getNodo(), ambito)) {
                return false;
            }
            if (variables[indV][0] != funciones[indF][0]) {
                error = "La funcion " + funciones[indF][1] + " no puede ser asignada a " + variables[indV][1] + " porque los tipos no concuerdan";
                return false;
            }
        }
        else {
            if (!verificarVariable(termino.top(), ambito)) {
                return false;
            }
        }
        nodo.pop();
        //Otro pop por suma o punto y coma o similares
        if (!nodo.empty() && nodo.top()->getNodo().empty())
            nodo.pop();
        if (!manejarExpresion(nodo, ambito)) {
            return false;
        }
    }
    return true;
}

bool Semantico::verificarVariable(ElementoPila* variable, string ambito) {
    //Primero checa si es numero real o entero
    if (variable->getTipo() == 1) {
        if (variables[indV][0] == "int") {
            return true;
        }
        error = "El tipo del dato " + variable->getToken() + " no concuerda con el tipo de la variable " + variables[indV][1];
        return false;
    }
    else if (variable->getTipo() == 2) {
        if (variables[indV][0] == "float") {
            return true;
        }
        error = "El tipo del dato " + variable->getToken() + " no concuerda con el tipo de la variable " + variables[indV][1];
        return false;
    }
    int indA = existenciaVariable(variable->getToken(), ambito);
    //Primero busca el argumento si esta definido
    if (indA != -1) {
        //Revisar si el tipo de variable concuerda con el parametro de la funcion
        if (variables[indA][0] == variables[indV][0]) {
            return true;
        }
        error = "El tipo de la variable " + variable->getToken() + " no concuerda con el tipo de la variable " + variables[indV][1];
        return false;
    }
    else {
        error = "La variable " + variable->getToken() + " no esta definida en el ambito " + ambito + " o global";
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
