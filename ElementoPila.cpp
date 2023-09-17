#include "ElementoPila.h"

string ElementoPila::getToken() {
	return token;
}

void ElementoPila::setToken(string tokens) {
	this->token = tokens;
}

void ElementoPila::printToken(int nivel) {
	for (int i = 0; i < nivel; i++) {
		cout << " ";
	}
	cout << token << endl;
}

Terminal::Terminal(string tokens) {
	setToken(tokens);
}

NoTerminal::NoTerminal(string tokens) {
	setToken(tokens);
}

void NoTerminal::pushNodo(ElementoPila* elemento) {
	nodo.push(elemento);
}

void NoTerminal::printToken(int nivel){
	for (int i = 0; i < nivel; i++) {
		cout << " ";
	}
	cout << this->getToken() <<" -" << endl;
	stack<ElementoPila*> aux;
	while (nodo.size() != 0) {
		aux.push(nodo.top());
		nodo.pop();
	}
	while (aux.size() != 0) {
		aux.top()->printToken(nivel+1);
		aux.pop();
	}
}

Estado::Estado(string tokens) {
	setToken(tokens);
}