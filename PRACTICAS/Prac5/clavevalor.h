#ifndef claveValor_h
#define claveValor_h

#include <string>
using namespace std;
#include "listaCadenas.h"
//main ---- > indices.h ----> clavevalor.h -----> listaCadenas.h

const int capIni_PARES = 4;

typedef struct {
	string clave;
	tListaCadenas valor;
} tRegistroIndicePalabras;

typedef tRegistroIndicePalabras * tArrayPares;

typedef struct {
	int tam;
	tArrayPares pares;
	int cap;
} tIndicePalabras;


int getTamanno(const tIndicePalabras & l);		//Devuelve el tamaño de la tabla

int buscarPosicion(const tIndicePalabras & idx, const string & s);

tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos);		//Devuelve el registro en la posicion pos

bool buscar(const tIndicePalabras & l, const string & s, int & pos);

bool buscar(const tIndicePalabras & l, const string & s, int ini, int fin, int & pos); // búsqueda binaria :: deuvelve true si la palabra es una clave en la tabla

int getPosicion(const tIndicePalabras & l, const string & s);		//Devuelve la posicion del registro cuya clave es S y -1 si no hay

void insertar(tIndicePalabras & idx, const string & palabra, const  string & nombreArchivo);		//Si la palabra ya es una clave, añade nombreArchivo a la lista de archivos corresonmdiente. Si no, crea un registro con la nueva INFO

void imprimir(const tIndicePalabras & idx);		//Imprime la tabla

bool operator<(tRegistroIndicePalabras opDech, tRegistroIndicePalabras opIzq);


tIndicePalabras nuevoIndice();

void liberar(tIndicePalabras & idx);

void amplia(tIndicePalabras & idx);


#endif