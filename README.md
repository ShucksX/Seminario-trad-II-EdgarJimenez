# Seminario-trad-II-EdgarJimenez
Compilador estilo C con proposito de la materia de Seminario de Solucion de problemas de traductores de lenguajes II  
Edgar Jimenez Aceves  

Este proyecto se hizo mediante Visual Studio 2019 usando el paquete de C++
Consta de 3 analizadores (no todos terminados de momento), el analizador lexico, el analizado sintactico y el analizador semantico. Esto con el proposito de hacer un compilador estilo C

## Links ##
Mini analizador lexico: https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/tree/minilexico_JimenezAcevesEdgar  
Analizador lexico: https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/tree/analizadorLexico_JimenezAcevesEdgar  

## Analizador Lexico ## 

En el analizador lexico se analiza toda la cadena fuente o mas bien, el codigo fuente y se localizan varios diferentes tokens, como lo son identificadores, numeros enteros, numeros reales, operadores relacionales, operador and, operador or, igual, operadores de igualdad, negacion, puntos y comas, parentesis y llaves. Ademas de palabras reservadas como int, float, if, else, while.  
Aqui se presenta una captura de pantalla con el resultado:
## Demostracion ##
![AnalizadorLexico](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/a73fe174-f904-4d2a-abb9-9c361f305c01)

## Analizador sintactico ##

Este analizador utiliza reglas gramaticas con el objetivo de verificar que el orden de los tokens es apropiado  
El analizador lexico actualmente solo reconoce una suma de un identificador con otro, como lo puede ser a+b o azul+cafe, ademas imprime una tabla con el proceso que se hace para deducir si esto es correcto o no.

## Demostracion ##
![imagen](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/b8e3ef89-76e0-434a-907d-cb69776fea8b)  
Este es un ejemplo de un codigo sintacticamente correcto con las reglas actuales.  
  
![imagen](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/e7022f99-9861-4b07-ab3e-d40277aa51cf)  
Este es  un ejemplo de un codigo sintactimente incorrecto  
  
![imagen](https://github.com/ShucksX/Seminario-trad-II-EdgarJimenez/assets/55963528/3090daba-abb9-4467-bfbe-124f31662060)  
Finalmente, este es un ejemplo de tokens lexicamente correctos pero que no tomamos en cuenta todavia



