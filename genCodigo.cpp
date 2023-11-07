#include "genCodigo.h"

GenCodigo::GenCodigo() {

}

bool GenCodigo::crearASM(Sintactico sint, Semantico sem) {
	ofstream codigo("codigoASM.asm");
	codigo << "section .bss" << std::endl;
	for (int i = 0; i < sem.getVarCont(); i++) {
		if (sem.variables[i][2] == "#") {
			if(sem.variables[i][0] == "int")
				codigo << "\t" + sem.variables[i][1] + " RESB 1" << endl;
			else
				codigo << "\t" + sem.variables[i][1] + " RESD 1" << endl;
		}
	}
	codigo << endl <<"section .text" << endl << endl;
	codigo << "global main" <<endl << endl;
	for (int i = 0; i < sem.getFuncCont(); i++) {
		if (sem.funciones[i][1] != "main") {
			codigo << sem.funciones[i][1] + ": " << endl;
		}
	}
	codigo << "main:" << std::endl;
	return true;
}