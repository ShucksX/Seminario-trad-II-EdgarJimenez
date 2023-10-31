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
		virtual stack<ElementoPila*> getNodo();
		virtual int getTipo();
};

class Terminal : public ElementoPila{
	private:
		int tipo;
	public:
		Terminal(string tokens);
		void setTipo(int tip);
		int getTipo() override;
};

class NoTerminal : public ElementoPila {
	private:
		stack<ElementoPila*> nodo;
	public:
		NoTerminal(string tokens);
		void  pushNodo(ElementoPila* elemento);
		stack<ElementoPila*> getNodo() override;
		void printToken(int nivel) override;
};

class Estado : public ElementoPila {
	public:
		Estado(string tokens);
};


#endif