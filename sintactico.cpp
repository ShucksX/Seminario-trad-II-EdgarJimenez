#include "sintactico.h"

Sintactico::Sintactico() {
	pila.push(new Terminal("$"));
	pila.push(new Estado("0"));
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
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 47; j++) {
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
	if (tipo < 0 || tipo > 3) { //Error o fuera de rango
		return "";
	}
	int fila = stoi(pilaTop()->getToken());
	if (fila < 0 || fila > 4) { //Error o fuera de rango (no deberia ocurrir pero por si acaso
		return "";
	}

	string estado = getLRAt(fila, tipo);

	if (estado.compare("r0") == 0) { //Estado acept
		return estado;
	}
	else if (estado.substr(0,1).compare("d") == 0) { //Desplazamientos
		pila.push(new Terminal(tokens));
		pila.push(new Estado(estado.substr(1)));
		return estado;
	}
	else if (estado.substr(0,1).compare("r") == 0) {//Regla 1
		return regla1();
	}
	else {//Error
		return "";
	}
}

string Sintactico::regla1() { // E -> id + E
	NoTerminal* nt = new NoTerminal("E");
	for (int i = 0; i < 6;i++) { //Haz pop al doble de tokens en la regla
		nt->pushNodo(pilaTop());
		popPila();
	}
	int fila = stoi(pilaTop()->getToken()); //Ultimo valor en pila
	string estado = getLRAt(fila, 3); //Obtener el valor para E
	if (estado.compare("")== 0) {
		return ""; //Error 
	}
	else {
		pila.push(nt);
		pila.push(new Estado(estado));
		return "r1";
	}

}

int Sintactico::getPilaSize() {
	return pila.size();
}