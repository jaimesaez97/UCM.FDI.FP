#ifndef indices_h
#define indices_h
#include "claveValor.h"
#include "matrices.h"
//main ---- > indices.h ----> clavevalor.h -----> listaCadenas.h
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>	//Funcion MYSTRING.TRANSFORM
#include <cctype>		//Funcion TOLOWER
#include <locale>
using namespace std;

void crearTabla(tIndicePalabras & tabla, const string & archivoInicial, tListaCadenas & totales, tMatriz & L);		//A partir de archivoInicial, rellena la tabl, tras haberla inicializado (a vacía)
void procesarTabla(tIndicePalabras & tabla, tListaCadenas & visitados, tListaCadenas & noVisitados, tListaCadenas & totales, tMatriz & L, int pos, int j);			//Le llega la siguiente palabra a analizar
string cargaPalabra(const string & archivoCompleto, int pos);
string cargaEnlace(const string & archivoCompleto, int pos);
void ordenarVectores(tVector & normalizado, tListaCadenas & totales);

#endif