#pragma once

#ifndef _ELEMENTOPILA
#define _ELEMENTOPILA

#include <iostream>
#include <string>
#include <stack>
using namespace std;


class ElementoPila {
	private:
		string token;
	public:
		string getToken();
		void setToken(string tokens);
};

class Terminal : public ElementoPila{
	public:
		Terminal(string tokens);
};

class NoTerminal : public ElementoPila {
	public:
		NoTerminal(string tokens);
		stack<ElementoPila*> nodo;
};

class Estado : public ElementoPila {
	public:
		Estado(string tokens);
};


#endif