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
		int indArg;
		int indF;
		int indV;
		//0: TIPO 1: NOMBRE 2:PARAMETROS 
		string funciones[100][3];
		int funcionesCont;
		string error;
		bool variableGlobal(stack<ElementoPila*> nodo);
		bool ListaVar(stack<ElementoPila*> nodo, string tipo, string ambito);
		bool funcion(stack<ElementoPila*> nodo);
		string parametros(stack<ElementoPila*> nodo, string ambito);
		string listaParametros(stack<ElementoPila*> nodo, string ambito);
		bool bloqFunc(stack<ElementoPila*> nodo, string ambito);
		bool sentencia(stack<ElementoPila*> nodo, string ambito);
		bool llamadaFunc(stack<ElementoPila*> nodo, string ambito);
		bool argumentos(stack<ElementoPila*> nodo, string ambito);
		bool listaArgumentos(stack<ElementoPila*> nodo, string ambito);
		bool verificarArgumento(ElementoPila* argumento, string ambito);
		bool usoVar(stack<ElementoPila*> nodo, string ambito);
		bool asignacion(stack<ElementoPila*> nodo, string ambito);
		bool buscarExpresion(stack<ElementoPila*> nodo, string ambito);
		bool manejarExpresion(stack<ElementoPila*> nodo, string ambito);
		bool verificarVariable(ElementoPila* variable, string ambito);
		bool variableLocal(stack<ElementoPila*> nodo, string ambito);
		void addVariable(string tipo, string variable, string ambito, string parametro);
		void addFuncion(string tipo, string funcion, string parametros);
	public:
		Semantico();
		bool start(Sintactico sintat);
		bool analizarNodo(ElementoPila* elemento);
		bool encontrarFuncion(string nombre);
		bool encontrarVariable(string nombre, string ambito);
		int existenciaFuncion(string funcion);
		int existenciaVariable(string variable, string ambito);
		string getError();
		void printFunciones();
		void printVariables();

};


#endif
