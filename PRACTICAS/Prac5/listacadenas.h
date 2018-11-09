
#ifndef listaCadenas_h
#define listaCadenas_h
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DECLARACIÓN DE TIPOS Y CONSTANTES:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


const int capIni_STRINGS = 1;

typedef string* tArrayStrings;

typedef struct {
	tArrayStrings datos;
	int tam;
	int cap;
} tListaCadenas;


tListaCadenas nuevaListaCadenas();

int getTamanno(const tListaCadenas & l);		//Devuelve el tamaño de la lista

string getCadena(const tListaCadenas & l, int pos);	//Devuelve una cadena en la posicion pos

void insertar(tListaCadenas & l, const string & s);	//Inserta un elemento al final de la lista

bool buscar(const tListaCadenas & l, const string & s);	//Devuelve true si la cadena está lista

void eliminar(tListaCadenas & l, int pos);	//Elimina el elemento de la posicion pos

void imprimir(const tListaCadenas & l);	//Imprime los elementos de la lista.

int getPos(const tListaCadenas & l, const string & s); // Devuelve la posición de la cadena s
/*------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/

void amplia(tListaCadenas & l);

void liberar(tListaCadenas & l);


#endif

