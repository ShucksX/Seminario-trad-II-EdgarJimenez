#include "sintactico.h"

Sintactico::Sintactico() {
	pila.push("$");
	pila.push("0");
}

void Sintactico::empezar() {
	pila.push("$");
	pila.push("0");
}

int Sintactico::getLRAt(int fila, int columna) {
	return LR[fila][columna];
}

void Sintactico::printLR() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			cout << getLRAt(i, j) << "\t";
		}
		cout << endl;
	}
}

void Sintactico::popPila() {
	pila.pop();
}

string Sintactico::pilaTop() {
	return pila.top();
}

int Sintactico::salida(string token, int tipo) { //Funcion principal
	if (tipo < 0 || tipo > 3) { //Error o fuera de rango
		return -200;
	}
	int fila = stoi(pilaTop());
	if (fila < 0 || fila > 4) { //Error o fuera de rango (no deberia ocurrir pero por si acaso
		return -200;
	}

	int estado = getLRAt(fila, tipo);

	if (estado == -199){ //Estado acept
		return estado;
	}
	else if (estado >= 0) { //Desplazamientos
		pila.push(token);
		pila.push(to_string(estado));
		return estado;
	}
	else if (estado == -1) {//Regla 1
		return regla1();
	}
	else if (estado == -2) {//Regla 2
		return regla2();
	}
	else {//Error
		return -200;
	}
}

int Sintactico::regla1() { // E -> id + E
	for (int i = 0; i < 6;i++) { //Haz pop al doble de tokens en la regla
		popPila();
	}
	int fila = stoi(pilaTop()); //Ultimo valor en pila
	int estado = getLRAt(fila, 3); //Obtener el valor para E
	if (estado < -199) {
		return -200; //Error 
	}
	else {
		pila.push("E");
		pila.push(to_string(estado));
		return -1;
	}

}
int Sintactico::regla2() { // E -> id
	for (int i = 0; i < 2; i++) { //Haz pop al doble de tokens en la regla
		popPila();
	}
	int fila = stoi(pilaTop()); //Ultimo valor en pila
	int estado = getLRAt(fila, 3); //Obtener el valor para E
	if (estado < -199) {
		return -200; //Error 
	}
	else {
		pila.push("E");
		pila.push(to_string(estado));
		return -2;
	}
}