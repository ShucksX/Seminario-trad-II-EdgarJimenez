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
		//0: TIPO 1: NOMBRE 2:FUNCION A LA QUE CORRESPONDE (o ambito) 3: PARAMETRO O NO
		string variables[100][4];
		int variablesCont;
		//0: TIPO 1: NOMBRE 2:PARAMETROS 
		string funciones[100][3];
		int funcionesCont;
		string funcionActual;
		string tipoActual;
		string error;
		bool variableGlobal(stack<ElementoPila*> nodo);
		bool ListaVar(stack<ElementoPila*> nodo, string tipo, string ambito);
		void addVariable(string tipo, string variable, string ambito, string parametro);
	public:
		Semantico();
		bool start(Sintactico sintat);
		bool analizarNodo(ElementoPila* elemento);
		bool encontrarFuncion(string nombre);
		bool encontrarVariable(string nombre, string ambito);
		string getError();
		void printFunciones();
		void printVariables();

};


#endif
