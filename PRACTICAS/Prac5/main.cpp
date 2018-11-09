/*			DATOS:			
ALUMNOS:
	+FERNANDO DASTIS SOTO
	+JAIME SÁEZ DE BURUAGA
COMPILAR CON:
	+VISUAL STUDIO
GRUPO:
	+L05-G02
*/		


#include "indices.h"
#include "checkML.h"



int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	tListaCadenas totales;
	totales = nuevaListaCadenas();
	tIndicePalabras idx;
	idx = nuevoIndice();
	/*----------------------------------------------------------------------*/
	string aInicio;
	string palabra;
	tMatriz L;
	L = {};
	bool fuera = false;
	tMatriz M = {};
	double epsilon = 0.000001;
	int contot = 0;
	

	cout << "Introduzca el nombre del archivo raiz: " << endl;
	cin >> aInicio;


	cout << "~~~~~~~~~> VISUALIZACION DE CALCULOS <~~~~~~~~~" << endl;

	cout << "///////////////////////////////////////" << endl;
	cout << "        MATRIZ  L (Por pasos):         " << endl;
	crearTabla(idx, aInicio, totales, L);
	cout << "///////////////////////////////////////" << endl;
	cout << "        TABLA:         " << endl;
	imprimir(idx);
	system("PAUSE");
	M = desdeEnlacesAMatriz(L);

	cout << endl;
	cout << "///////////////////////////////////////" << endl;
	cout << "        MATRIZ  M:         " << endl;

	for (int fil = 0; fil < M.filas; fil++){
		for (int col = 0; col < M.columnas; col++){
			cout << setw(10) << M.datos[fil][col];

		}
		cout << endl;
	}

	tVector nonormali = {};
	nonormali = vectorPropio(M, epsilon);
	system("PAUSE");

	tVector normalizado = {};
	normalizado = normaliza(nonormali);
	cout << "///////////////////////////////////////" << endl;
	cout << "        VECTOR DEL PAGERANK NORMALIZADO:         " << endl;
	for (int i = 0; i < M.filas; i++){
		cout << setw(10) << normalizado.datos[i];

	}
	cout << endl << endl;
	cout << "~~~~~~~~~> BUSQUEDA DE PALABRAS <~~~~~~~~~" << endl;
	cout << "//////////////////////////////////////////" << endl;
	cout << "La informacion ha sido cargada. Puede empezar a hacer busquedas" << endl;

	do{
		int pos = 0;
		cout << "--Introduzca la palabra a buscar('fin') para acabar: " << endl;
		cin.clear();
		cin.sync();
		cin >> palabra;
		fuera = palabra == "fin";
		if (!buscar(idx, palabra, pos)){
			if (!fuera){
				cout << "No se ha encontrado en ningun archivo." << endl;
			}
		}
		else{
			ordenarVectores(normalizado, totales);
			contot = 0;
			
			for (int x = 0; x < totales.tam; x++){
				for (int i = 0; i < getRegistro(idx, pos).valor.tam; i++){
					if (getRegistro(idx, pos).valor.datos[i] == totales.datos[x]){
						cout << " ~>> Encontrada en : [" << totales.datos[x] << "] (Relevancia : " << normalizado.datos[x] << ")." << endl;
					}
				}	
			}
		}
	} while (fuera != true);
	
	/*----------------------------------------------------------------------
						LIBERAR MEMORIA:
	-----------------------------------------------------------------------*/
	// Hay que cerrar antes listaCadenas que indicePalabras
	liberar(totales);
	for (int x = 0; x < idx.tam; x++){
		liberar(idx.pares[x].valor);
	}
	liberar(idx);
	system("PAUSE");
	return 0;
}
