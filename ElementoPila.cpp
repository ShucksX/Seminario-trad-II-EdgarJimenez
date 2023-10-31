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

stack<ElementoPila*> ElementoPila::getNodo() {
	stack<ElementoPila*> nodoFalso;
	return nodoFalso;
}

int ElementoPila::getTipo() {
	return -1;
}

Terminal::Terminal(string tokens) {
	setToken(tokens);
	tipo = -1;
}

void Terminal::setTipo(int tip) {
	tipo = tip;
}

int Terminal::getTipo() {
	return tipo;
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
	while (nodo.size() != 0) {
		nodo.top()->printToken(nivel + 1);
		nodo.pop();
	}
}

stack<ElementoPila*> NoTerminal::getNodo() {
	return nodo;
}



Estado::Estado(string tokens) {
	setToken(tokens);
}