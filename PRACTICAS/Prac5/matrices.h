#ifndef matrices_h
#define matrices_h
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;


const int M_MAX = 5;
const double c = 0.85;



typedef struct{
	double datos[M_MAX];
	int tam;
}tVector;

typedef struct{
	double datos[M_MAX][M_MAX];
	int filas, columnas;
}tMatriz;



/*---------------------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------------------*/

tMatriz matrizConstante(double x, int n);	//Crea una matriz de n*n, en la que todos los valores iniciales son x
tVector operator*(const tMatriz & m, const tVector & v);	//Multiplica una matriz por un vector
tMatriz operator*(double x, const tMatriz & m);		//Multiplica cada elemento de la matriz por x
tMatriz operator+(const tMatriz & m1, const tMatriz & m2);	//Sumador de matrices
tMatriz desdeEnlacesAMatriz(const tMatriz & m); //Devuelve una matriz M obtenida de L (SECCION 4)
tVector normaliza(const tVector & v1);	//Devuelve un vector proporcional a V con la primera componente = 1.0
tVector vectorPropio(const tMatriz & m, double epsilon);	//M es una matriz tal que todas sus columnas suman uno.
//Devuelve un vector v con la primera comp igual a 1 tal que M * v =aprox v
int numEnlaces(const tMatriz & m, int columna);
bool proximo(const tVector & v1, const tVector & v2, double epsilon);
double sumaVec(const tVector &v);

#endif

