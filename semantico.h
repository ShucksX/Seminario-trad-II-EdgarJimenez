#pragma once

#pragma once

#ifndef _SEMANTICO
#define _SEMANTICO

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include "sintactico.h"

using namespace std;

class Semantico {
	private:
		Sintactico sint;
		//0: TIPO 1: NOMBRE 2:FUNCION A LA QUE CORRESPONDE 3: PARAMETRO O NO
		string variables[100][4];
		//0: TIPO 1: NOMBRE 2:PARAMETROS 3: NO LO SE (WIP)
		string funciones[100][4];
		string funcionActual;
		string tipoActual;
		string error;
	public:
		Semantico();
		void start(Sintactico sintat);
		void analizarNodo(ElementoPila* elemento);

};


#endif
