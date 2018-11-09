/*
PRÁCTICA 2 - 2017
FUNDAMENTOS DE LA PROGRAMACIÓN
GRUPO:
	+L03-G02
COMPILAR CON:
	+VISUAL STUDIO VS
ALUMNOS:
	+FERNANDO DASTIS SOTO
	+JAIME SÁEZ DE BURUAGA

*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>   
#include <locale>
#include <string.h>
using namespace std;

const int MAX_PROD = 25;
const int PROD_NULO = 0;
const int CENTINELA = -1;

typedef int tArray[MAX_PROD];


/*-----------------------------------------------------------------------------------------------------------------------*/
/*												PROTOTIPOS SUBPROGRAMAS V1																 */

// FILA

/**
Muestra la fila en pantalla

@param fila Array donde estan guardados los elementos.
@param tam Variable contadora que indica el n?mero de posiciones del array que componen la fila.
*/
void mostrarFila(const tArray fila, int tam);

/**
Devuelve si la posici?n es v?lida

@param tam Variable contadora que indica el n?mero de posiciones del array que componen la fila.
@param pos Posici?n a validar.
@return true si la posici?n es v?lida; false c.c.
*/
bool esPosValida(int tam, int pos);

/**
Indica si la posici?n est? vac?a

@param fila Array donde estan guardados los elementos.
@param pos Posici?n de la fila (v?lida)
@return true si en la posici?n hay hueco; false c.c.
*/
bool estaVacia(const tArray fila, int pos);

// FICHEROS
void leerFilaFichero(ifstream &fich, tArray fila, int &tam);
void escribirFilaFichero(ofstream &fich, const tArray fila, int tam);

// GRUA
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar);
bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar);

// EXCAVADORA
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);

// MENU
int menu();
void ejecutarLeerFichero(tArray fila, int &tam);
void ejecutarGuardarFichero(const tArray fila, int tam);
void ejecutarExcavadora(tArray fila, int tam);
void ejecutarGrua(tArray fila, int tam);
void ejecutarOpc(int opc, tArray fila, int &tam);
/*-----------------------------------------------------------------------------------------------------------------------*/


/*															MAIN															 */

int main() {


	locale::global(locale("spanish"));

	tArray fila;
	int tam = 0;
	int opc = 0;

	opc = menu();

	ejecutarOpc(opc, fila, tam);




	system("PAUSE");
	return 0;
}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*												IMPLEMENTACIÓN SUBPROGRAMAS V1																 */

/*-----------------------------------------------------------------------------------------------------------------------*/
/*															FILA																 */
void mostrarFila(const tArray fila, int tam){

	cout << endl;			
	for (int i = 0; i < tam; i++){

		if (fila[i] == 0){				/*Si el dato del material es un 0, por pantalla no aparece nada*/
			cout << " |  ";				
		}
		else{
			cout << " | " << fila[i];	/*Si no es un cero, aparece el dato*/
		}

	}
	cout << "| " << endl;
	cout << "-";
	for (int x = 0; x < tam; x++){
		cout << "----";
	}
	cout << endl;
	for (int j = 0; j < tam; j++){
		if (j <10){
			cout << " | " << j;
		}
		else{
			cout << " |" << j;

		}
	}
	cout << "| " << endl << endl;
}

bool esPosValida(int tam, int pos){

	if (pos > tam || pos < 0){
		return false;			/*Devuelve false si la posición marcada NO es válida*/
	}

	return true;
}

bool estaVacia(const tArray fila, int pos){

	if (fila[pos] == 0){		/*Devuelve TRUE si la posición marcada está vacía*/
		return true;
	}

	return false;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*														FICHEROS																	 */
void leerFilaFichero(ifstream &fich, tArray fila, int &tam){

	int i = 0;
	int dato = 0;

	fich >> fila[i];	


	while (fila[i] != CENTINELA){		/*Mientras que no se encuentre el centinela, introducir los datos de los materiales del fichero en la fila*/

		tam++;
		i++;
		fich >> fila[i];

	}
}

void escribirFilaFichero(ofstream &fich, const tArray fila, int tam){

	int i = 0;
	int dato = 0;


	fich << fila[i] << " ";

	while (fila[i] != CENTINELA){		/*Mientras que no se encuentre el centinela, escribir los datos de la fila en el fichero.*/
		tam++;
		i++;
		fich << fila[i] << " ";
	}
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*														GRÚA															     */
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar){

	if (esPosValida(tam, posSoltar) == false || esPosValida(tam, posIni) == false || estaVacia(fila, posSoltar) == false){
		cout << "No es posible ejecutar el movimiento." << endl;			/*Solo no es posible si la posicion a soltar no es válida o está vacía o si la posición inicial no es válida. En alguno de estos casos, devuelve FALSE*/
		return false;
	}
	return true;
}

bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar){

	if (esPosibleGrua1Entre(fila, tam, posIni, posSoltar) == true){		/*Devuelve true cuando es posible la grua: si se ha realizado el movimiento*/
		fila[posSoltar] = fila[posIni];
		fila[posIni] = 0;
		return true;
	}
	else { return false; }

}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*													EXCAVADORA:																	 */
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion){
	int i = posIni;								/*I las posiciones desde la que marca el usuario hasta el hueco libre*/
	if (direccion == 1){						/*1 == DERECHA*/
		while (i < tam && estaVacia(fila, i) == false){

			i++;
		}
	}
	else{										/*-1 == IZQUIERDA*/
		while (i > 0 && estaVacia(fila, i) == false){
			i--;
		}
	}
	return i;
}

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion){
	//contador son las casillas ocupadas 
	int i = 0;
	i = posHuecoLibreDir(fila, tam, posIni, direccion);	/*I es la posición en la que esta el hueco*/
	int datoAmover = 0;
	if (direccion == 1){
		if (i == tam){
			cout << "No se pueden aplastar materiales contra el muro. " << endl;
			return false;
		}


		for (int x = i; x > posIni; x--){	/*En este bucle i i=posIni no entra*/
			datoAmover = fila[x - 1];		/*Muevo el dato y actualizo a 0*/
			fila[x] = datoAmover;
			fila[x - 1] = 0;
		}
	}
	else{
		if (i == 0){
			cout << "No se pueden aplastar materiales contra el muro. " << endl;
			return false;
		}

		for (int x = i; x < posIni; x++){
			datoAmover = fila[x + 1];
			fila[x] = datoAmover;
			fila[x + 1] = 0;
		}
	}
	return true;
}

/* -------------------------------------------------------------------------------------------------------------------*/
/*												MENÚ Y SUS 5 SUBFUNCIONES																	  */
int menu(){
	//Interfaz del menú:


	int opcion;

	cout << "-------------------------------------------------------------" << endl;
	cout << "Bienvenido al menú de 'Al ladrillo con excavadora y grúa'. " << endl << endl;
	cout << "OPCIÓN 1: Cargar fila de fichero" << endl;
	cout << "OPCIÓN 2: Guardar fila en fichero" << endl;
	cout << "OPCIÓN 3: Usar grúa (1 elemento)" << endl;
	cout << "OPCIÓN 4: Usar excavadora (1 posición derecha)" << endl << endl;
	cout << "OPCIÓN 0: Salir" << endl;
	cout << "-------------------------------------------------------------" << endl << endl;;

	cout << "Por favor, introduzca una opción: " << endl;
	cin >> opcion;

	while (opcion < 0 || opcion > 4){
		cout << "Opción incorrecta. Prueba otra vez: " << endl;
		cin >> opcion;
	}
	return opcion;
}

void ejecutarLeerFichero(tArray fila, int &tam){


	ifstream archivoCarga;
	char nombre[50];		/*Nombre de archivo que introduce el usuario*/


	cout << "Has escogido OPCIÓN 1: Cargar fila de fichero" << endl;


	cout << "Introduzca el nombre del fichero en el que quiera cargar su fila. " << endl;
	cin >> nombre;

	strcat_s(nombre, ".txt");

	archivoCarga.open(nombre);
	if (!archivoCarga.is_open()){
		for (int i = 0; i < MAX_PROD; i++){		/*Si no se crea fila: cuál es el tamaño por definición?*/
			fila[i] = 0;
		}
		cout << "El archivo de carga no se ha encontrado. " << endl;
		cout << "Se va a proceder a inicializar la cadena a 0. " << endl;
		mostrarFila(fila, MAX_PROD);
	}
	else{
		leerFilaFichero(archivoCarga, fila, tam);
		mostrarFila(fila, tam);
	}
	archivoCarga.close();
}

void ejecutarGuardarFichero(const tArray fila, int tam){

	char nombre[50];
	ofstream archivoGuarda;

	cout << "Has escogido OPCIÓN 2: Guardar fila en fichero" << endl;


	cout << "Introduzca el nombre del fichero en el que quiere guardar su fila. " << endl;
	cin >> nombre;

	strcat_s(nombre, ".txt");				/*Se le añade la extension .txt al nombre*/

	archivoGuarda.open(nombre);
	escribirFilaFichero(archivoGuarda, fila, tam);
	mostrarFila(fila, tam);

	archivoGuarda.close();

}

void ejecutarExcavadora(tArray fila, int tam){
	int posIni = 0;
	int direccion = 0;

	cout << "Has escogido OPCIÓN 4: Usar excavadora (1 posición derecha)" << endl << endl;

	cout << "Introduzca la dirección hacia la que quieres mover: DERECHA(1) o IZQUIERDA(-1)" << endl;
	cin >> direccion;

	while (direccion != 1 && direccion != -1){
		cout << "Direccion incorrecta. Introduzca la direccion otra vez: " << endl;
		cin >> direccion;
	}

	cout << "Indica la posición en la que quieres empezar: " << endl;
	cin >> posIni;

	while (posIni < 0 || posIni > tam){
		cout << "Posición incorrecta. Introduzca otra: " << endl;
		cin >> posIni;
	}
	excavadora1Dir(fila, tam, posIni, direccion);
	mostrarFila(fila, tam);
}

void ejecutarGrua(tArray fila, int tam){
	int posIni = 0;
	int posAsoltar = 0;
	cout << "Has escogido OPCIÓN 3: Usar grúa (1 elemento)" << endl << endl;
	cout << "Indica la posición que quieres levantar: " << endl;
	cin >> posIni;
	while (posIni < 0 || posIni > tam){
		cout << "Posicion no válida. Introduce otra: " << endl;
		cin >> posIni;
	}
	cout << "Indica la posición a la que quieres mover: " << endl;
	cin >> posAsoltar;
	while (posAsoltar < 0 || posAsoltar > tam){
		cout << "Posición no válida. Introduce otra: " << endl;
		cin >> posAsoltar;
	}
	grua1Elemento(fila, tam, posIni, posAsoltar);
	mostrarFila(fila, tam);
}

void ejecutarOpc(int opc, tArray fila, int &tam){

	while (opc != 0){

		switch (opc){
		case 1:
			ejecutarLeerFichero(fila, tam);

			break;

		case 2:
			ejecutarGuardarFichero(fila, tam);

			break;

		case 3:
			ejecutarGrua(fila, tam);

			break;
		case 4:
			ejecutarExcavadora(fila, tam);

			break;
		case 0:
			cout << "Has escogido OPCIÓN 5: Salir" << endl;

			break;
		}
		opc = menu();
	}
}

/*------------------------------------------------------------------------------------------------------------------------*/