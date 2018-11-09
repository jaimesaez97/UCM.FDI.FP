#include "listacadenas.h"


tListaCadenas nuevaListaCadenas(){
	tListaCadenas l;
	l.cap = capIni_STRINGS;
	l.tam = 0;
	l.datos = new string[l.cap];
	return l;
}

int getSize(const tListaCadenas & l) {
	return l.tam;
};

string getCadena(const tListaCadenas & l, int pos){		// Devuelve una cadena en la posicion POS
	return l.datos[pos];
}

void insertar(tListaCadenas & l, const string & s){		// Inserta un elemento en la última posicion
	if (l.cap == l.tam)
		amplia(l);
	if (buscar(l, s) == false){
		l.datos[l.tam] = s;								// Metemos en la posicion l.tam; ya que será la última
		l.tam++;
	}
}

bool buscar(const tListaCadenas & l, const string & s){		// Devuelve true si la cadena está en la lista, y false si no
	bool encontrado = false;
	int cont = 0;
	while (cont < l.tam && !encontrado){
		if (l.datos[cont] == s){
			encontrado = true;
		}
		cont++;
	}
	return encontrado;
}

void eliminar(tListaCadenas & l, int pos){		//Elimina el elemento en la posicion pos
	for (int i = pos; i < l.tam - 1; i++){
		l.datos[i] = l.datos[i + 1];	
	}
	if (pos == l.tam){
		l.datos[pos] = "";
	}
	l.tam--;
}

void imprimir(const tListaCadenas & l){		// Imprime los elementos de la tabla
	for (int i = 0; i < l.tam; i++){
		cout << i << ".- " << l.datos[i] << endl;
	}
}

int getPos(const tListaCadenas & l, const string & s){
	int pos = 0;
	bool encontrado = false;
	while (pos < l.tam && !encontrado){
		if (l.datos[pos] == s){
			encontrado = true;
		}
		pos++;
	}
	if (pos == 0){
		pos = 1;
	}
	return pos - 1;
}

void liberar(tListaCadenas & l){
	delete[] l.datos;
	l.datos = NULL;
	l.cap = 0;
	l.tam = 0;
}

void amplia(tListaCadenas & l){
	l.cap = (l.cap * 3) / 2 + 1;
	tListaCadenas aux;
	aux.cap = l.cap;
	aux.tam = l.tam;
	aux.datos = new string[aux.cap];	
	for (int x = 0; x < l.tam; x++){
		aux.datos[x] = l.datos[x];
	}
	liberar(l);
	l.cap = aux.cap;
	l.tam = aux.tam;
	l.datos = aux.datos;
}
