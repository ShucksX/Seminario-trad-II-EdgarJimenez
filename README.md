# Seminario-trad-II-EdgarJimenez
Compilador estilo C con proposito de la materia de Seminario de Solucion de problemas de traductores de lenguajes II  
Edgar Jimenez Aceves  

Este proyecto se hizo mediante Visual Studio 2019 usando el paquete de C++
Consta de 3 analizadores (no todos terminados de momento), el analizador lexico, el analizado sintactico y el analizador semantico. Esto con el proposito de hacer un compilador estilo C

## Links ##
Mini analizador lexico: https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/tree/minilexico_JimenezAcevesEdgar  
Analizador lexico: https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/tree/analizadorLexico_JimenezAcevesEdgar  
Sintactico Ejercicio 1: https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/tree/sintactico1_JimenezAcevesEdgar  
Sintactico Ejercicio 2: https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/tree/sintactico2_JimenezAcevesEdgar  

## Analizador Lexico ## 

En el analizador lexico se analiza toda la cadena fuente o mas bien, el codigo fuente y se localizan varios diferentes tokens, como lo son identificadores, numeros enteros, numeros reales, operadores relacionales, operador and, operador or, igual, operadores de igualdad, negacion, puntos y comas, parentesis y llaves. Ademas de palabras reservadas como int, float, if, else, while.  
Aqui se presenta una captura de pantalla con el resultado:
## Demostracion ##
![AnalizadorLexico](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/a73fe174-f904-4d2a-abb9-9c361f305c01)

## Analizador sintactico ##

Este analizador utiliza reglas gramaticas con el objetivo de verificar que el orden de los tokens es apropiado  
El analizador lexico actualmente solo reconoce una suma recurrente de un identificador con otro, como lo puede ser a+b+c+d+e o azul+cafe+verde, ademas imprime una tabla con el proceso que se hace para deducir si esto es correcto o no.

## Demostracion ##
![imagen](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/90f454e1-8e95-4734-8efc-ef10b472c16a)  
Este es un ejemplo de un codigo sintacticamente correcto con las reglas actuales.  
  
![imagen](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/81613f13-85ad-40f8-bc8d-6abfe690360e)
Este es  un ejemplo de un codigo sintactimente incorrecto (hay dos signos de suma entre un operador y otro)  
  
![imagen](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/a7dc0de9-12b8-4dc1-b714-43dca9103677)  
Finalmente, este es un ejemplo de tokens lexicamente correctos pero que no forman parte de nuestras reglas todavia.

## Arbol de la pila (Implementacion con objetos) ##
Se implementa una pila que acepte objetos de tipo ElementoPila, el cual hereda a otras clases llamadas Terminal, NoTerminal y Estado, gracias a esto ahora se puede mostrar un arbol de la pila para el analizador sintactico.  
Se imprime los mismos resultados en la verificacion de la regla, pero si la entrada es aceptada por el analizador sintactico, imprime el arbol de la pila de la manera siguiente:  
![imagen](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/ffd1b2e6-43a3-48c3-ab0d-dc2feb91a1b2)



