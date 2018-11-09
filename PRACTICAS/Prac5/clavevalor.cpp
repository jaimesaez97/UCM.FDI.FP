#include "clavevalor.h"

int getTamanno(const tIndicePalabras & l){  //Devuelve el tamaño de la tabla
	return l.tam;
}

int buscarPosicion(const tIndicePalabras & idx, const string & s){
	int cont = 0;
	int posicionPalabra = 0;
	bool posEncontrada = false;
	while (cont < idx.tam && !posEncontrada){
		if (getRegistro(idx, cont).clave > s){ //Si la clave de idx[cont] es > s <---- la posicion es esa porque esta ordenada de menor a mayor (Si getRegistro(idx, cont).clave > s es porque nos hemos pasado)
			posEncontrada = true;
			posicionPalabra = cont;
		}
		else{
			cont++;
		}
	}
	if (cont == idx.tam){   
		posicionPalabra = idx.tam;
	}
	return posicionPalabra;
}

tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos){  
	return l.pares[pos];
}

bool buscar(const tIndicePalabras & l, const string & s, int &pos){
	return buscar(l, s, 0, l.tam - 1, pos);
}

bool buscar(const tIndicePalabras & l, const string & s, int ini, int fin, int &pos){

	int mitad = 0;
	bool encontrado = false;
	pos = -1;

	if (ini <= fin){
		mitad = (ini + fin) / 2;
		if (s == l.pares[mitad].clave){
			encontrado = true;
			pos = mitad;
		}
		else if (s < l.pares[mitad].clave){
			encontrado = buscar(l, s, ini, mitad - 1, pos);
		}
		else{
			encontrado = buscar(l, s, mitad + 1, fin, pos);
		}
	}
	return encontrado;
}

int getPosicion(const tIndicePalabras & l, const string & s){
	int i = 0;
	bool encontrado = false;

	while (i < l.tam && !encontrado){
		if (l.pares[i].clave == s){
			encontrado = true;
		}
		i++;
	}
	//Devuelvo i-1 porque cuando en la lista hay 0 elementos no entra en getPosicion, sino que va al ELSE del insertar y ahí se usa buscarPosicion para que entre ordenado
	if (i == 0){
		i = 1;
	}
	return i - 1; 
}

void insertar(tIndicePalabras & idx, const string & palabra, const  string & nombreArchivo){
	int posicion = 0;
	

	if (idx.cap == idx.tam)
		amplia(idx);

	if (buscar(idx, palabra, posicion)){
		int x = 0;
		bool yaMetida = false;
		while (x < idx.pares[posicion].valor.tam && !yaMetida){
			if (idx.pares[posicion].valor.datos[x] == nombreArchivo){ //Si corresponde el nombreArchivo es que está la clave y el valor ya metida <- NO se mete
				yaMetida = true;
			}
			x++;
		}
		if (!yaMetida){  //Para que no escriba en la tabla dos palabras iguales dentro de un mismo archivo <-- No funciona
			insertar(idx.pares[posicion].valor, nombreArchivo);
		}
	}
	else{
		if (posicion == -1)	
			posicion = buscarPosicion(idx, palabra);

		if (posicion == idx.tam){
			idx.pares[posicion].clave = palabra;
			idx.pares[posicion].valor.tam = 0;	//Como insertamos una palabra que no está, no tiene valores
			if (idx.pares[posicion].valor.tam == 0){
				idx.pares[posicion].valor = nuevaListaCadenas();
			}
			insertar(idx.pares[posicion].valor, nombreArchivo);
			idx.tam++;
		}
		else{ //Solo hay que mover una casilla desde buscarPosicion(idx, palabra) hasta idx.tam - 1
			tRegistroIndicePalabras aux;
			int x = posicion;

			for (int i = idx.tam; i > x; i--){
				idx.pares[i] = {};
				idx.pares[i].valor.tam = 0;
				idx.pares[i] = idx.pares[i - 1];
			}
			idx.pares[x] = {};
			idx.pares[x].clave = palabra;

			insertar(idx.pares[x].valor, nombreArchivo);

			idx.tam++;
		}
	}
}

void imprimir(const tIndicePalabras & idx){
	for (int i = 0; i < idx.tam; i++){
		cout << endl;
		cout << idx.pares[i].clave << "                  ";
		for (int x = 0; x < idx.pares[i].valor.tam; x++){
			cout << idx.pares[i].valor.datos[x] << "." << endl;
			cout << "                         ";
		}
	}
	cout << endl;
	cout << endl;
}

bool operator<(tRegistroIndicePalabras opDech, tRegistroIndicePalabras opIzq){
	return(opDech.clave < opIzq.clave);
}

tIndicePalabras nuevoIndice(){
	tIndicePalabras idx;
	idx.cap = capIni_PARES;
	idx.tam = 0;
	idx.pares = new tRegistroIndicePalabras[idx.cap];

	return idx;
}

void liberar(tIndicePalabras & idx){

	delete[] idx.pares;
	idx.pares = NULL;
	idx.tam = 0;

	idx.cap = 0;
}

void amplia(tIndicePalabras &idx){
	idx.cap = (idx.cap * 3) / 2 + 1;
	tIndicePalabras aux;
	aux.cap = idx.cap;
	aux.tam = idx.tam;
	aux.pares = new tRegistroIndicePalabras[aux.cap];
	for (int x = 0; x < idx.tam; x++){
		aux.pares[x] = idx.pares[x];
	}
	liberar(idx);
	idx.cap = aux.cap;
	idx.tam = aux.tam;
	idx.pares = aux.pares; //Ahora idx.pares es un puntero que apunta a aux.pares
}