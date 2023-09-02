#include "ElementoPila.h"

string ElementoPila::getToken() {
	return token;
}

void ElementoPila::setToken(string tokens) {
	this->token = tokens;
}

Terminal::Terminal(string tokens) {
	setToken(tokens);
}

NoTerminal::NoTerminal(string tokens) {
	setToken(tokens);
}

Estado::Estado(string tokens) {
	setToken(tokens);
}