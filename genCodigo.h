#pragma once

#ifndef _GENCODIGO
#define _GENCODIGO

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <fstream>
#include "sintactico.h"
#include "semantico.h"

using namespace std;

class GenCodigo {
private:
    

public:
    GenCodigo();
    bool crearASM(Sintactico sint, Semantico sem);

};

#endif
