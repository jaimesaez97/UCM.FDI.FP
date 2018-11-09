#include "indices.h"


void crearTabla(tIndicePalabras & tabla, const string & archivoInicial, tListaCadenas & totales, tMatriz & L) {


	int j = 0;
	bool encontrado = false;
	//Hay que inicializar visitados, no-visitados y totales (son listas de array) a listas vacías

	tListaCadenas visitados;
	visitados = nuevaListaCadenas();
	tListaCadenas noVisitados;	
	noVisitados = nuevaListaCadenas();
	//– Meter el nombre del archivo inicial en no visitados

	int i = 0;
	insertar(noVisitados, archivoInicial);
	insertar(totales, archivoInicial);
	L.filas = 1;
	L.columnas = 1;
	L.datos[0][0] = 0;

	while (noVisitados.tam > 0){	//– Mientras haya algún archivo en no - visitados
		//Sacar el archivo y meterlo en no visitados:
		insertar(visitados, noVisitados.datos[i]);	 //DESPUES DE INSERTAR EL ARCHIVO EN VISITADOS SACO LA POS EN LA QUE ENTRA Y LO GUARDO EN J
		j = getPos(visitados, noVisitados.datos[i]); // Guardo la posición que tiene el elemento de noVisitados.datos[i] --> j
		eliminar(noVisitados, i);	//Eliminamos el archivo

		//Leemos todos los archivos de visitados desde aquí:
		int x = j;		//Contador del array visitados
		while (x < visitados.tam){

			procesarTabla(tabla, visitados, noVisitados, totales, L, x, j);		//Leemos el último archivo de visitados (que estaba en no-visitados y lo acabamos de insertar aquí, borrandolo de no-v)
			cout << endl;
			for (int i = 0; i < L.filas; i++){
				for (int m = 0; m < L.columnas; m++){ // Visualizacion por pasos
					cout << setw(10) << L.datos[i][m];
				}
				cout << endl;
			}
			cout << "[ ";
			for (int contotales = 0; contotales < totales.tam; contotales++){
				cout << totales.datos[contotales] << " ";
			}
			cout << "]" << endl;

			system("PAUSE");
			x++;
		}

	}
	liberar(visitados);
	liberar(noVisitados);
}

void procesarTabla(tIndicePalabras & tabla, tListaCadenas & visitados, tListaCadenas & noVisitados, tListaCadenas & totales, tMatriz & L, int pos, int j){
	bool cargaArchivo = true;
	ifstream archivo;
	string linea;
	string archivoCompleto;	//Metemos todo el archivo en un string (caben 2^16 caracteres)
	char c;
	int z;

	//En el array noVisitados vienen los archivos como strings con el .txt
	archivo.open(visitados.datos[pos]);
	if (!archivo.is_open()){
		cout << "No se ha encontrado el índice " << noVisitados.datos[pos] << "." << endl;
		cargaArchivo = false;
	}
	else{
		//Sacamos caracter a caracter toda la tabla

		while (!archivo.eof()){	//Mientras que no se acabe el archivo
			getline(archivo, linea);
			archivoCompleto = archivoCompleto + " " + linea;	//Concatenamos las líneas
		}
		//Cuando sale del while tiene en archivoCompleto un string con el archivo completo
		int i = 0;
		while (i < archivoCompleto.size()){
			c = archivoCompleto[i];
			linea = "";

			if (c == '<'){

				linea = cargaEnlace(archivoCompleto, i);

				if (buscar(totales, linea)){ // Si esta en totales en la posición z  L[z][j]=1

					z = getPos(totales, linea) - 1;
					if (z == -1){
						z = 0;
					}

					L.datos[z][j] = 1;
				}

				else{//Si no está en totales lo meto en totales y no visitados
					insertar(noVisitados, linea);
					insertar(totales, linea);
					L.filas++;
					L.columnas++;

					for (int borcol = 0; borcol < L.filas; borcol++){//Pongo las nuevas componentes de la matriz a 0
						//Cada vez que pongo nuevas componentes se echa todo una columna mas alla
						L.datos[borcol][L.columnas - 1] = 0;
						L.datos[L.filas - 1][borcol] = 0;
					}


					L.datos[L.filas - 1][j] = 1;// En t - 1 siendo t nuestra nueva dimensión si le añadimos en 1 la dimensión las nuevas componentes son - 1 y t - 1 = fila - 2

				}

				i++;

			}
			else if (!ispunct(c) && !isspace(c)){
				//Llamamos a procesarPalabra
				linea = cargaPalabra(archivoCompleto, i);
				insertar(tabla, linea, visitados.datos[pos]);
			}
			if (linea.size() == 0){
				i++;
			}
			i = i + linea.size();	//Para que lea la posición siguiente al final de la palabra leida
		}
	}
}

string cargaPalabra(const string & archivoCompleto, int pos){
	//Comienza a cargar desde pos hasta que se acaba la palabra
	int i = pos;
	string palabraCargada = "";
	while (!ispunct(archivoCompleto[i]) && !isspace(archivoCompleto[i])){
		palabraCargada += archivoCompleto[i];
		i++;
	}
	transform(palabraCargada.begin(), palabraCargada.end(), palabraCargada.begin(), tolower);
	return palabraCargada;
}

string cargaEnlace(const string & archivoCompleto, int pos){
	int i = pos + 1;	//Para que no coja <
	string enlaceCargado = "";
	while (archivoCompleto[i] != '>'){	//No coje < tampoco
		enlaceCargado += archivoCompleto[i];
		i++;
	}
	transform(enlaceCargado.begin(), enlaceCargado.end(), enlaceCargado.begin(), tolower);
	return enlaceCargado;		//Returnea el enlace sin <>
}

void ordenarVectores(tVector & normalizado, tListaCadenas & totales){
	
	double tmp = 0.00;
	string s = "";
	int pos = 0;
	for (int i = 1; i < normalizado.tam; i++){
		pos = i;
		while ((pos > 0) && (normalizado.datos[pos - 1] < normalizado.datos[pos])){
			// Cambios en normalizado:
			tmp = normalizado.datos[pos];
			normalizado.datos[pos] = normalizado.datos[pos - 1];
			normalizado.datos[pos - 1] = tmp;
			// Cambios en listaCadenas:
			s = totales.datos[pos];
			totales.datos[pos] = totales.datos[pos - 1];
			totales.datos[pos - 1] = s;
			pos--;
		}
	}
}

