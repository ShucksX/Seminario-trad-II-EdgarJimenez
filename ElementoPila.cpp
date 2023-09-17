#include "ElementoPila.h"

string ElementoPila::getToken() {
	return token;
}

void ElementoPila::setToken(string tokens) {
	this->token = tokens;
}

void ElementoPila::printToken(int nivel) {
	for (int i = 0; i < nivel; i++) {
		cout << "\t";
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
		cout << "\t";
	}
	cout << "E -" << endl;
	while (nodo.size() != 0) {
		nodo.top()->printToken(nivel+1);
		nodo.pop();
	}
}

Estado::Estado(string tokens) {
	setToken(tokens);
}