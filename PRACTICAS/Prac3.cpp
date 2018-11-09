#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <string.h>
#include <Windows.h>	// SetConsoleTextAttribute y otros
#include <conio.h>		// _getch()
using namespace std;

const int MAX = 50;

typedef enum tCasilla{ Libre, Muro, DestinoL, DestinoC, DestinoJ, Jugador, Caja };

typedef tCasilla tTablero[MAX][MAX];

typedef struct{
	tTablero tablero;
	int nfilas; // n� filas (reales) del tablero
	int ncolumnas; // n� columnas (reales) del tablero
	int fila; // del jugador
	int columna; // del jugador
	int cajas; // n� de cajas
	int colocadas; // n� de cajas colocadas en destino

} tSokoban;

typedef struct {
	tSokoban sokoban;
	int numMovimientos;
	string nFichero;
	int nivel;
}tJuego;

typedef enum tTecla{ Arriba, Abajo, Izquierda, Derecha, Salir, Nada };


// ************
// PROTOTIPOS
// ************

// para visualizaci�n del tablero
void colorFondo(int color);
void dibujaCasilla(tCasilla casilla);
void dibujar(const tJuego &juego);
void rellenarStruct(tSokoban sokoban);
// para carga de un nivel de juego
void inicializa(tJuego &juego);
bool cargarJuego(tJuego &juego);
bool cargarNivel(ifstream & fichero, tSokoban &sokoban, int nivel);
tCasilla charToCasilla(char caracter);
// para lectura de teclas especiales
tTecla leerTecla();

// para realizar el movimiento indicado en tecla
void hacerMovimiento(tJuego &juego, tTecla tecla);


//
// auxiliares (no pedidos expresamente)
//

// para E/S con usuarios
void mostrarMenu();
int leerOpcion();

// otros...


// ************
// MAIN
// ************

int main() {

	int opc;
	tJuego juego;
	tSokoban sokoban;
	do{
		// solicitar opci�n
		mostrarMenu();
		opc = leerOpcion();
		// resto del main...
		if (cargarJuego(juego) == true){
			rellenarStruct(sokoban);
			dibujar(juego);
		}

	} while (opc != 0);

	system("pause");
	return 0;
}



// ************
// IMPLEMENTACI�N SUBPROGRAMAS
// ************


void colorFondo(int color){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void dibujaCasilla(tCasilla casilla) {
	int color;
	string texto;
	switch (casilla) {
	case Libre:
		color = 1; // azul
		texto = "  ";
		break;
	case Muro:
		color = 2; // verde
		texto = "  ";
		break;
	case DestinoL:
		color = 12; // magenta
		texto = "..";
		break;
	case DestinoC:
		color = 4; // rojo
		texto = "[]";
		break;
	case DestinoJ:
		color = 4; // rojo
		texto = "00";
		break;
	case Jugador:
		color = 6; // amarillo
		texto = "00";
		break;
	case Caja:
		color = 7; // gris
		texto = "()";
		break;
	}
	colorFondo(color);
	cout << texto;
	colorFondo(0);
}

void dibujar(const tJuego &juego){

	cout << " Fichero : " << juego.nFichero << "  Level : " << juego.nivel << endl;

	for (int i = 0; i < juego.sokoban.nfilas; i++){

		for (int j = 0; j < juego.sokoban.ncolumnas; j++){

			cout << juego.sokoban.tablero[i][j];

		}

		cout << endl;

	}

	cout << " Numero de movimientos : " << juego.numMovimientos << endl;

}



void inicializa(tJuego &juego){

	for (int i = 0; i < MAX; i++){

		for (int j = 0; j < MAX; j++){

			juego.sokoban.tablero[i][j] = Libre;


		}
	}

}



bool cargarJuego(tJuego &juego){

	bool cargaOK;
	int nivel;

	cout << "Introduzca el nombre del archivo del que desea cargar el juego : " << endl;
	cin >> juego.nFichero;
	while (cin.fail()){
		cin.sync();
		cin.clear();
		cin >> juego.nFichero;
	}

	cout << "Introduzca el nivel que desea jugar : " << endl;
	cin >> nivel;
	while (nivel < -1 || cin.fail()){
		cin.sync();
		cin.clear();
		cin >> nivel;

	}

	tSokoban sokoban;

	ifstream ficheroCarga;

	ficheroCarga.open(juego.nFichero.c_str());

	if (ficheroCarga.is_open()){

		cargaOK = cargarNivel(ficheroCarga, sokoban, nivel); /*QUEDA CONTROLAR EL CARGA OK PARA QUE SI NO SE ENCUENTRA EL ARCHIVO PIDA OTRO NOMBRE, WHILE!!*/
		if (cargaOK == false){

			cout << "No se ha podido encontrar el nivel indicado. " << endl;
			/*¿Qué hago? ¿Vuelvo a pedir el nivel?*/
		}
		else{
			juego.nivel = nivel;
		}
		ficheroCarga.close();
	}
	else {
		cout << "No se ha encontrado el fichero que ha indicado" << endl;
		cargaOK = false;
	}
	return cargaOK;
}


void rellenarStruct(tSokoban sokoban){

	for (int i = 0; i < sokoban.nfilas; i++){
		for (int j = 0; j < sokoban.ncolumnas; j++){
			if (sokoban.tablero[i][j] == Caja){
				sokoban.cajas++;
			}
			if (sokoban.tablero[i][j] == Jugador){
				sokoban.fila = i;
				sokoban.columna = j;
			}
			if (sokoban.tablero[i][j] == DestinoC){		/*¿Esto puede ser posible*/
				sokoban.colocadas++;
			}
		}

	}

}


bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int nivel) {

	string fila;
	bool encontrado = false;
	int numCajas = 0;


	while (encontrado == false){

		getline(fichero, fila);									/*Cogemos la primera línea : Level 0*/
		if (fila[7] == nivel && fila[0] == 'L'){				/*Si el primer caracter es L y elcaracter nº7 (número) corresponde con el elegido, carga*/
			int numFilas = 0;
			int numColumnas;
			getline(fichero, fila);								/*Inicializamos las filas y columnas a 0*/
			while (fila[0] != 'L'){
				/*Mientras que NO encuentre la siguiente fila de LEVEL */
				/*Cojo la primera línea*/
				numColumnas = 0;								/*Inicializo las columnas a 0*/
				while (fila[numColumnas] != '/n'){				/*Mientras que no haya SALTO DE LÍNEA*/
					sokoban.tablero[numFilas][numColumnas] = charToCasilla(fila[numColumnas]);		/*Introduzco el char de fila(numColumnas) en la casilla correspondiente del tablero*/

					numColumnas++;								/*Columnas++ para recorrer la fila entera*/
				}
				numFilas++;
				getline(fichero, fila);							/*Filas++ para recorrer todo el tablero*/
			}
			sokoban.ncolumnas = numColumnas - 1;					/*Introduzco el numero de columnas en el sokoban*/
			sokoban.nfilas = numFilas;							/*Introduzco el numerode filas en el sokoban*/
			//Terminar de rellenar el array
			encontrado = true;
		}
		else{
			/*¿Qué pasa cuando no hay nivel cargado?*/
			encontrado = false;
		}
	}
	return encontrado;
}

tCasilla charToCasilla(char caracter){
	tCasilla casilla;

	if (caracter == '#'){
		casilla = Muro;
	}

	if (caracter == ' '){
		casilla = Libre;
	}

	if (caracter == '.'){
		casilla = DestinoL;
	}

	if (caracter == '*'){
		casilla = DestinoC;
	}

	if (caracter == '+'){
		casilla = DestinoJ;
	}

	if (caracter == '@'){
		casilla = Jugador;
	}

	if (caracter == '$'){
		casilla = Caja;
	}

	return casilla;
}

tTecla leerTecla(){
	tTecla t;
	int dir;

	cin.sync();
	dir = _getch();
	if (dir == 0xe0){
		dir = _getch();
		switch (dir) {
		case 72:
			t = Arriba;
			break;
		case 80:
			t = Abajo;
			break;
		case 77:
			t = Derecha;
			break;
		case 75:
			t = Izquierda;
			break;
		}
	}
	else
		if (dir == 27)
			t = Salir;
		else
			t = Nada;
	return t;
}

void hacerMovimiento(tJuego &juego, tTecla tecla){
	int direccion = 0;
	string dir;

	switch (tecla){
	case Arriba:
		direccion = -1;
		dir = "Columna";
		break;
	case Abajo:
		direccion = +1;
		dir = "Columna";
		break;
	case Izquierda:
		direccion = -1;
		dir = "Fila";
		break;
	case Derecha:
		direccion = +1;
		dir = "Fila";
		break;
	case Salir:

		break;
	case Nada:

		break;
	}

	if (dir == "Columna"){
		if (juego.sokoban.fila + direccion == Libre){

			juego.sokoban.tablero[juego.sokoban.fila + direccion][juego.sokoban.columna] = Jugador;	/*Actualizo la casilla de jugador*/
			juego.sokoban.fila = juego.sokoban.fila + direccion;
			juego.numMovimientos++;
		}
		if (juego.sokoban.fila + direccion == Caja){
			if (juego.sokoban.fila + direccion * 2 == Libre){
				/*Disminuyo en 1 las filas del jugador porque subo arriba*/
				juego.sokoban.tablero[juego.sokoban.fila + direccion][juego.sokoban.columna] = Jugador;		/*Actualizo la casilla del jugador*/
				juego.sokoban.tablero[juego.sokoban.fila][juego.sokoban.columna] = Libre;
				juego.sokoban.tablero[juego.sokoban.fila + direccion * 2][juego.sokoban.columna] = Caja;	/*Subo la caja 1 hacia arriba*/
				juego.sokoban.fila = juego.sokoban.fila + direccion;

				juego.numMovimientos++;
			}
			if (juego.sokoban.fila + direccion * 2 == DestinoL){
				juego.sokoban.tablero[juego.sokoban.fila + direccion * 2][juego.sokoban.columna] = DestinoC;
				juego.sokoban.colocadas++;
				juego.sokoban.cajas--;

				juego.numMovimientos++;
			}
			/*También puede ser un muro, pero no se pone y no cuenta el movimiento*/
		}
	}

	if (dir == "Fila"){
		if (juego.sokoban.columna + direccion == Libre){

			juego.sokoban.tablero[juego.sokoban.fila][juego.sokoban.columna + direccion] = Jugador;	/*Actualizo la casilla de jugador*/
			juego.sokoban.columna = juego.sokoban.columna + direccion;
			juego.numMovimientos++;
		}
		if (juego.sokoban.columna + direccion == Caja){
			if (juego.sokoban.columna + direccion * 2 == Libre){
				/*Disminuyo en 1 las filas del jugador porque subo arriba*/
				juego.sokoban.tablero[juego.sokoban.fila][juego.sokoban.columna + direccion] = Jugador;		/*Actualizo la casilla del jugador*/
				juego.sokoban.tablero[juego.sokoban.fila][juego.sokoban.columna] = Libre;
				juego.sokoban.tablero[juego.sokoban.fila][juego.sokoban.columna + direccion * 2] = Caja;	/*Subo la caja 1 hacia arriba*/
				juego.sokoban.columna = juego.sokoban.columna + direccion;

				juego.numMovimientos++;
			}
			if (juego.sokoban.columna + direccion * 2 == DestinoL){
				juego.sokoban.tablero[juego.sokoban.fila][juego.sokoban.columna + direccion * 2] = DestinoC;
				juego.sokoban.colocadas++;
				juego.sokoban.cajas--;

				juego.numMovimientos++;
			}
			/*También puede ser un muro, pero no se pone y no cuenta el movimiento*/

		}
	}

}

void mostrarMenu() {

	cout << "1. Jugar partida." << endl;
	cout << "0. Salir del programa." << endl;
	cout << "Introduce una opcion: ";
}

int leerOpcion(){
	int i;

	cin >> i;
	while (cin.fail() || i<0 || i>1) {
		cin.clear();
		cin.sync();
		cout << "Opcion incorrecta. Introduce una opcion: ";
		cin >> i;
	}
	cin.sync();
	return i;
}


