#include "sintactico.h"

Sintactico::Sintactico() {
	//pila.push(new Terminal("$"));
	//pila.push(new Estado("0"));
}

void Sintactico::empezar() {
	pila.push(new Terminal("$"));
	pila.push(new Estado("0"));
	llenarLR();
}

string Sintactico::getLRAt(int fila, int columna) {
	return LR[fila][columna];
}

bool Sintactico::llenarLR() {
	ifstream fin;
	bool entro = false;

	// Open an existing file
	fin.open("compilador.csv");
	if (fin.fail())
		return false;

	// Read the Data from the file
	// as String Vector
	string line, word, temp;
	bool firstline = true;
	bool firstword = true;
	int fila = 0;
	int columna = 0;
	while (getline(fin, line)) {
		if (firstline) {
			firstline = false;
		}
		else {
			entro = true;

			// used for breaking words
			stringstream s(line);

			// read every column data of a row and
			// store it in a string variable, 'word'
			while (getline(s, word, ',')) {
				if (firstword) {
					firstword = false;
				}
				else {
					// add all the column data
					// of a row to a vector
					LR[fila][columna] = word;
					columna++;
				}
			}
			firstword = true;
			columna = 0;
			fila++;
		}
	}
	return entro;
}

void Sintactico::printLR() {
	for (int i = 0; i < 95; i++) {
		for (int j = 0; j < 46; j++) {
			if (getLRAt(i, j).empty())
				cout << "v ";
			else
				cout << getLRAt(i, j) << " ";
		}
		cout << endl;
	}
}

void Sintactico::popPila() {
	pila.pop();
}

ElementoPila* Sintactico::pilaTop() {
	return pila.top();
}

string Sintactico::salida(string tokens, int tipo) { //Funcion principal
	if (tipo < 0 || tipo > 46) { //Error o fuera de rango
		return "";
	}
	int fila = stoi(pilaTop()->getToken());
	if (fila < 0 || fila > 94) { //Error o fuera de rango (no deberia ocurrir pero por si acaso
		return "";
	}

	string estado = getLRAt(fila, tipo);
	//cout << fila << " " << tipo << " " << estado << endl ;
	if (estado.compare("r0") == 0) { //Estado acept
		return estado;
	}
	else if (estado.substr(0,1).compare("d") == 0) { //Desplazamientos
		pila.push(new Terminal(tokens));
		pila.push(new Estado(estado.substr(1)));
		return estado;
	}
	else if (estado.substr(0,1).compare("r") == 0) {//Reglas
		int numregla = stoi(estado.substr(1));
		string retorno = "";
		switch (numregla) {
			case 1: // Programa -> Definiciones
				retorno= regla(1, 24, estado,"Programa");
				break;
			case 2: //<Definiciones> ::= \e 
				retorno= regla(0, 25, estado,"Definiciones");
				break;
			case 3://<Definiciones> ::= <Definicion> <Definiciones> 
				retorno= regla(2, 25, estado,"Definiciones");
				break;
			case 4: //<Definicion> ::= <DefVar> 
				retorno =regla(1, 26, estado,"Definicion");
				break;
			case 5: //<Definicion> ::= <DefFunc> 
				retorno = regla(1, 26, estado,"Definicion");
				break;
			case 6: //<DefVar> ::= tipo identificador <ListaVar> ;
				retorno = regla(4, 27, estado,"DefVar");
				break;
			case 7: //<ListaVar> ::= \e
				retorno = regla(0, 28, estado,"ListaVar");
				break;
			case 8: //<ListaVar> ::= , identificador <ListaVar> 
				retorno = regla(3, 28, estado,"ListaVar");
				break;
			case 9: //<DefFunc> :: = tipo identificador(<Parametros>) < BloqFunc >
				retorno = regla(6, 29, estado,"DefFunc");
				break;
			case 10: //<Parametros> ::= \e
				retorno = regla(0, 30, estado,"Parametros");
				break;
			case 11: // <Parametros> ::= tipo identificador <ListaParam>
				retorno = regla(3, 30, estado,"Parametros");
				break;
			case 12: //<ListaParam> ::= \e 
				retorno = regla(0, 31, estado,"ListaParam");
				break;
			case 13: //<ListaParam> ::= , tipo identificador <ListaParam>
				retorno = regla(4, 31, estado,"ListaParam");
				break;
			case 14: //<BloqFunc> ::= { <DefLocales> }
				retorno = regla(3, 32, estado,"BloqFunc");
				break;
			case 15: //<DefLocales> ::= \e 
				retorno = regla(0, 33, estado,"DefLocales");
				break;
			case 16: //<DefLocales> ::= <DefLocal> <DefLocales>
				retorno = regla(2, 33, estado,"DefLocales");
				break;
			case 17: //<DefLocal> ::= <DefVar> 
				retorno = regla(1, 34, estado,"DefLocal");
				break;
			case 18: //<DefLocal> ::= <Sentencia>
				retorno = regla(1, 34, estado,"DefLocal");
				break;
			case 19: //<Sentencias> ::= \e
				retorno = regla(0, 35, estado,"Sentencias");
				break;
			case 20: //<Sentencias> ::= <Sentencia> <Sentencias>
				retorno = regla(2, 35, estado,"Sentencias");
				break;
			case 21: //<Sentencia> ::= identificador = <Expresion> ;
				retorno = regla(4, 36, estado,"Sentencia");
				break;
			case 22: //<Sentencia> ::= if ( <Expresion> ) <SentenciaBloque> <Otro>
				retorno = regla(6, 36, estado, "Sentencia");
				break;
			case 23: //<Sentencia> ::= while ( <Expresion> ) <Bloque>
				retorno = regla(5, 36, estado,"Sentencia");
				break;
			case 24: //<Sentencia> ::= return <ValorRegresa> ;
				retorno = regla(3, 36, estado, "Sentencia");
				break;
			case 25: // <Sentencia> ::= <LlamadaFunc> ;
				retorno = regla(2, 36, estado, "Sentencia");
				break;
			case 26: // <Otro> ::= \e
				retorno = regla(0, 37, estado,"Otro");
				break;
			case 27: //<Otro> ::= else <SentenciaBloque>
				retorno = regla(2, 37, estado,"Otro");
				break;
			case 28: //<Bloque> ::= { <Sentencias> }
				retorno = regla(3, 38, estado,"Bloque");
				break;
			case 29: //<ValorRegresa> ::= \e
				retorno = regla(0, 39, estado,"ValorRegresa");
				break;
			case 30: //<ValorRegresa> ::= <Expresion>
				retorno = regla(1, 39, estado,"ValorRegresa");
				break;
			case 31: // <Argumentos> ::= \e
				retorno = regla(0, 40, estado,"Argumentos");
				break;
			case 32: //<Argumentos> ::= <Expresion> <ListaArgumentos>
				retorno = regla(2, 40, estado,"Argumentos");
				break;
			case 33: //<ListaArgumentos> ::= \e 
				retorno = regla(0, 41, estado,"ListaArgumentos");
				break;
			case 34: //<ListaArgumentos> ::= , <Expresion> <ListaArgumentos>
				retorno = regla(3, 41, estado,"ListaArgumentos");
				break;
			case 35: //<Termino> ::= <LlamadaFunc>
				retorno = regla(1, 42, estado,"Termino");
				break;
			case 36: //<Termino> ::= identificador
				retorno = regla(1, 42, estado, "Termino");
				break;
			case 37: //<Termino> ::= entero
				retorno = regla(1, 42, estado, "Termino");
				break;
			case 38: //<Termino> ::= real
				retorno = regla(1, 42, estado, "Termino");
				break;
			case 39: //<Termino> ::= cadena
				retorno = regla(1, 42, estado, "Termino");
				break;
			case 40: // <LlamadaFunc> ::= identificador ( <Argumentos> )
				retorno = regla(4, 43, estado, "LlamadaFunc");
				break;
			case 41: //<SentenciaBloque> ::= <Sentencia>
				retorno = regla(1, 44, estado,"SentenciaBloque");
				break;
			case 42: //<SentenciaBloque> ::= <Bloque>
				retorno = regla(1, 44, estado,"SentenciaBloque");
				break;
			case 43: //<Expresion> ::= ( <Expresion> )
				retorno = regla(3, 45, estado, "Expresion");
				break;
			case 44: //<Expresion> ::= opSuma <Expresion>
				retorno = regla(2, 45, estado, "Expresion");
				break;
			case 45: //<Expresion> ::= opNot <Expresion>
				retorno = regla(2, 45, estado, "Expresion");
				break;
			case 46: //<Expresion> ::= <Expresion> opMul <Expresion>
				retorno = regla(3, 45, estado, "Expresion");
				break;
			case 47: //<Expresion> ::= <Expresion> opSuma <Expresion>
				retorno = regla(3, 45, estado, "Expresion");
				break;
			case 48: //<Expresion> ::= <Expresion> opRelac <Expresion>
				retorno = regla(3, 45, estado, "Expresion");
				break;
			case 49: //<Expresion> ::= <Expresion> opIgualdad <Expresion>
				retorno = regla(3, 45, estado, "Expresion");
				break;
			case 50: //<Expresion> ::= <Expresion> opAnd <Expresion>
				retorno = regla(3, 45, estado, "Expresion");
				break;
			case 51: //<Expresion> ::= <Expresion> opOr <Expresion>
				retorno = regla(3, 45, estado, "Expresion");
				break;
			case 52: //<Expresion> ::= <Termino>
				retorno = regla(1, 45, estado, "Expresion");
				break;
		}
		return retorno;
	}
	else if (estado.empty()){//Error
		return "";
	}
	else {
		return estado;
	}
}

string Sintactico::regla(int elementos, int columna, string estad, string nomRegla) { 
	NoTerminal* nt = new NoTerminal(nomRegla);
	for (int i = 0; i < elementos*2;i++) { //Haz pop al doble de tokens en la regla
		if (div(i,2).rem == 1) //Para comodidad en semantico no se guardan los desplazamientos para el arbol
			nt->pushNodo(pilaTop());
		popPila();
	}
	int fila = stoi(pilaTop()->getToken()); //Ultimo valor en pila
	string estado = getLRAt(fila, columna); //Obtener el valor para E
	if (estado.empty()) {
		return ""; //Error 
	}
	else {
		pila.push(nt);
		pila.push(new Estado(estado));
		return estad.substr(1) + "-e";
	}

}

int Sintactico::getPilaSize() {
	return pila.size();
}

string Sintactico::pilaToString() {
	stack<ElementoPila*> pila2;
	pila2 = pila;
	string pilaEntera = "";
	while (!pila2.empty()) {
		pilaEntera = pilaEntera + pila2.top()->getToken();
		pila2.pop();
	}
	return pilaEntera;
}