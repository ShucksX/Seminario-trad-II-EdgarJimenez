#include "genCodigo.h"

GenCodigo::GenCodigo() {

}

bool GenCodigo::crearASM(Sintactico sint, Semantico sem) {
	ofstream codigo("codigoASM.asm");
	codigo << "section .bss" << std::endl;
	for (int i = 0; i < sem.getVarCont(); i++) {
		if (sem.variables[i][2] == "#") {
			if(sem.variables[i][0] == "int")
				codigo << "\t" + sem.variables[i][1] + " RESB 1" << std::endl;
			else
				codigo << "\t" + sem.variables[i][1] + " RESD 1" << std::endl;
		}
	}
	codigo << "section .text" << std::endl;
	codigo << "global main" << std::endl << std::endl;
	for (int i = 0; i < sem.getFuncCont(); i++) {
		if (sem.funciones[i][1] != "main") {
			codigo << sem.funciones[i][1] + ": " << std::endl;
		}
	}
	codigo << "main:" << std::endl;
	return true;
}