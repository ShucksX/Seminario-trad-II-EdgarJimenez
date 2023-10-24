#include "semantico.h"

Semantico::Semantico() {

}

void Semantico::start(Sintactico sintactico) {
    sint = sintactico;
    cout << "Semantico: " << endl;

    while (sint.getPilaSize() != 0) {
        analizarNodo(sint.pilaTop());
        sint.popPila();
    }
}

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
