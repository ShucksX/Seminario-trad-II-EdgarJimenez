#pragma once

#ifndef _SINTACTICO
#define _SINTACTICO

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include "ElementoPila.h"

using namespace std;

class Sintactico{
	private:
		string LR[95][46];  //-199 es r0, para eliminar confusiones con posibles d0, y las r son numeros negativos.
		stack<ElementoPila*> pila;
		string regla(int elementos,int columna, string estad, string nomRegla);
	public:
		Sintactico();
		void empezar();
		string getLRAt(int fila, int columna);
		void printLR();
		bool llenarLR();
		void popPila();
		int getPilaSize();
		ElementoPila* pilaTop();
		string salida(string tokens, int tipo);
		string pilaToString();
};


#endif