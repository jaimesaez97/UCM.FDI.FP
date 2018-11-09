#include "matrices.h"

tMatriz matrizConstante(double x, int n){
	tMatriz matrizConstante = {};
	matrizConstante.filas = n;
	matrizConstante.columnas = n;
	for (int i = 0; i < matrizConstante.filas; i++){
		for (int j = 0; j < matrizConstante.columnas; j++){
			matrizConstante.datos[i][j] = x;
		}
	}
	return matrizConstante;
}

tVector operator*(const tMatriz & m, const tVector & v){
	tVector vecRes = {};
	vecRes.tam = m.filas;
	for (int i = 0; i < m.filas; i++){
		for (int x = 0; x < m.filas; x++){
			vecRes.datos[i] = vecRes.datos[i] + m.datos[i][x] * v.datos[x];


		}
	}

	return vecRes;
}

tMatriz operator*(double x, const tMatriz & m){
	tMatriz matriz = {};
	matriz.columnas = m.columnas;
	matriz.filas = m.filas;

	for (int i = 0; i < m.filas; i++){
		for (int j = 0; j < m.columnas; j++){
			matriz.datos[i][j] = m.datos[i][j] * x;
		}
	}
	return matriz;
}

tMatriz operator+(const tMatriz & m1, const tMatriz & m2){
	tMatriz M = {};
	M.filas = m1.filas;
	M.columnas = m1.columnas;

	for (int f = 0; f < m1.filas; f++){
		for (int c = 0; c < m1.columnas; c++){

			M.datos[f][c] = m1.datos[f][c] + m2.datos[f][c];
		}

	}
	return M;
}

tMatriz desdeEnlacesAMatriz(const tMatriz & m){ //Devuelve la matriz m obtenida de L (SECCION 4)
	//Cálculo de la matriz Cn:
	tMatriz Cn = {};

	double k = double(1) / double(m.filas);
	Cn = matrizConstante(k, m.filas);
	cout << "/////////////////////////////////" << endl;
	cout << " MATRIZ CN : " << endl;

	for (int i = 0; i < Cn.filas; i++){
		for (int j = 0; j < Cn.columnas; j++){
			cout << setw(10) << Cn.datos[i][j];
		}
		cout << endl;
	}
	//Calculo de la matriz M:
	tMatriz Mprima = {};
	Mprima = m;
	int col = 0;
	int enlcs;


	while (col < m.columnas){ // RECURSION POR LAS COLUMNAS, TENGO QUE VER CUANTOS ENLACES HAY EN CADA UNA PARA MULTIPLICAR LA COLUMNA POR UN NUM
		double k = double(1) / double(m.filas);  // CTE 1/N
		int fil = 1;
		enlcs = numEnlaces(m, col);


		if (enlcs > 1){//SI LA COLUMNA TIENE 1 ENLACE SE QUEDA COMO ESTA, SI TIENE MAS DE 1 SUS COMPONENTES PASAN A SER 1/Nj DONDE Nj ES EL NUM DE ENLACES
			double Nj = double(1) / double(enlcs);

			for (int fila = 0; fila < Mprima.filas; fila++){
				Mprima.datos[fila][col] = Mprima.datos[fila][col] * Nj;
			}
		}
		if (enlcs == 0){//SII NO TIENE ENLACES TODAS SUS COMPONENTES PASAN A SER 1/N 
			for (int fila = 0; fila < Mprima.filas; fila++){
				Mprima.datos[fila][col] = k;
			}
		}


		col++;
	}

	cout << endl;
	cout << "/////////////////////////////////" << endl;
	cout << "Matriz MPRIMA:" << endl;

	for (int fil = 0; fil < Mprima.filas; fil++){
		for (int col = 0; col < Mprima.columnas; col++){
			cout << setw(10) << Mprima.datos[fil][col];

		}
		cout << endl;
	}


	double cte = double(1) - double(c);
	tMatriz newCn = Cn; // newCn es la Matriz (1-c)Cn
	newCn.columnas = Cn.columnas;
	newCn.filas = Cn.filas;


	newCn = cte * Cn;
	cout << "/////////////////////////////////" << endl;
	cout << " NUEVA CN ( (1-c)Cn ):" << endl;

	for (int i = 0; i < Cn.filas; i++){
		for (int j = 0; j < Cn.columnas; j++){
			cout << setw(10) << newCn.datos[i][j];
		}
		cout << endl;
	}

	tMatriz MprimaC = Mprima;//Nueva matriz Mprima * c
	MprimaC.columnas = Mprima.columnas;
	MprimaC.filas = Mprima.filas;


	MprimaC = c * Mprima;
	cout << "/////////////////////////////////" << endl;
	cout << " MPRIMA POR C:" << endl;

	for (int i = 0; i < Mprima.filas; i++){
		for (int j = 0; j < Mprima.columnas; j++){
			cout << setw(10) << MprimaC.datos[i][j];
		}
		cout << endl;
	}

	tMatriz M;

	M = newCn + MprimaC; // M es la suma de las dos matrices anteriores


	return M;
}

int numEnlaces(const tMatriz & m, int columna){
	int numEnlaces = 0;
	for (int fil = 0; fil < m.filas; fil++){
		if (m.datos[fil][columna] == 1){
			numEnlaces++;
		}
	}
	return numEnlaces;
}

tVector vectorPropio(const tMatriz & m, double epsilon){

	tVector PR = {};
	PR.tam = m.filas;

	for (int i = 0; i < PR.tam; i++){ // EMPEZAMOS CON EL VECTOR DEL MISMO TAMAÑO QUE m.filas RELLENO A 1
		PR.datos[i] = 1;
	}

	tVector vecRes = {};

	vecRes = m * PR; // ESTO YA MULTIPLICA SOLO LA MATRIZ Y TRAE EL VECTOR RESULTADO

	while (!proximo(vecRes, PR, epsilon)){ // MIENTRAS QUE NO SEAN PROXIMOS SIGO RECURRIENDO

		PR = vecRes;
		vecRes = m * PR;

	}
	cout << "////////////////////////////////////////////////" << endl;
	cout << "        VECTOR DEL PAGERANK SIN NORMALIZAR     " << endl;
	for (int x = 0; x < vecRes.tam; x++){
		cout << setw(10) << vecRes.datos[x];
	}
	cout << endl;
	return vecRes;
}

bool proximo(const tVector & v1, const tVector & v2, double epsilon){

	bool diferencia = true; // HACEMOS EL COCIENTE ENTRE LAS COMPONENTES DE LOS VECTORES Y ESO CON LA DIFERENCIA ENTRE 1.0 TIENE QUE SER MENOR A 10^-6 (EPSILON)
	int x = 0;


	while (diferencia && x < v1.tam){// En la primera vuelta de este proximo v2 --> PR v1 -- > vecRes

		double cociente = v1.datos[x] / v2.datos[x];
		double resta = 1 - cociente;

		resta = abs(resta);



		if (resta < epsilon){
			diferencia = true;//SI ES MENOR A EPSILON SIGO, TODAS LAS COMPONENTES TIENEN QUE ESTAR PROXIMAS
		}
		else{
			diferencia = false;
		}

		x++;

	}

	return diferencia;

}

tVector normaliza(const tVector& v1){
	tVector normalizado = v1;
	int x = 0;
	for (int i = 0; i < v1.tam; i++){
		normalizado.datos[i] = normalizado.datos[i] / v1.datos[x];
	}
	return normalizado;
}

