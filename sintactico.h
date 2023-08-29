#pragma once

#ifndef _SINTACTICO
#define _SINTACTICO

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Sintactico{
	private:
		int LR[5][4] = { {2,-200,-200, 1}, {-200,-200,-199,-200},{-201,3,-2,-200},{2,-200,-200,4},{-200,-200,-1,-200}};  //-199 es r0, para eliminar confusiones con posibles d0, y las r son numeros negativos.
		stack<string> pila;
		int regla1();
		int regla2();
	public:
		Sintactico();
		void empezar();
		int getLRAt(int fila, int columna);
		void printLR();
		void popPila();
		string pilaTop();
		int salida(string token, int tipo);
};


#endif