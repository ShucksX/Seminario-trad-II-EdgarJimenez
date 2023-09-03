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
		virtual void printToken(int nivel);
};

class Terminal : public ElementoPila{
	public:
		Terminal(string tokens);
};

class NoTerminal : public ElementoPila {
	private:
		stack<ElementoPila*> nodo;
	public:
		NoTerminal(string tokens);
		void  pushNodo(ElementoPila* elemento);
		void printToken(int nivel) override;
};

class Estado : public ElementoPila {
	public:
		Estado(string tokens);
};


#endif