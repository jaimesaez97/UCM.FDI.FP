/*FUNDAMENTOS DE LA PROGRAMACI�N
Pr�ctica 1.

-GRUPO:
+L3-G02

-ALUMNOS:
+Jaime S�ez de Buruaga Brouns(GRUPO 1� C)
+ Fernando Dastis Soto(GRUPO 1� C)

-FLUJOS DE ENTRADA:
+fiestas: contiene la informaci�n de las fiestas
+fiestas2:contiene la informaci�n de las fiestas. se crean dos para que sea modificable con respecto a puentesMejorados

-FLUJOS DE SALIDA:
+puentes: contiene la informaci�n de los d�as de puente
+puentesmejora: contiene la informaci�n de los d�as de puente mejorados

-HECHO CON:
+Visual Studio Express 2013 para escritorio

*/
#include <locale>    /*Sirve para escribir caracteres en espa�ol*/
#include <iostream>
#include <fstream>
using namespace std;

const int anyoInicio = 1900;


/*DEFINICION DEL PROTOTIPO DE FUNCIONES*/
int menu();
int solicitaAnyo();										 /*Solicita, valida y devuelve un a�o introducido por el teclado. Debe ser 1900 o posterior*/
bool esBisiesto(int anyo);								 /*Devuelve un balor booleano que indica si el ANYO es bisiesto o no.*/
int solicitaMes();										 /*Solicita, valida y devuelve un mes introducido por el teclado. */
int diasMes(int mes, int anyo);							 /*Le entra por par�metro un mes de un a�o y devuelve el n�mero m�ximo de dias correspondiente a ese mes (30, 31, 28 o 29)*/
int solicitaDia(int mes, int anyo);						 /*Le entra por par�metro el mes y a�o escogidos y el n�mero de d�as m�ximo del mes, y solicita el d�a elegido al usuario */
int contarBisiestos(int anyoInicio, int anyoFinal);      /*Devuelve el n�mero de a�os bisiestos en el intervalo [anyoInicio=1900, anyoFinal=anyo]. */
long int diasTranscurridos(int dia, int mes, int anyo);  /*OPCION 1 DEL MEN�: Devuelve el n�mero de dias transcurridos desde el 1/enero/1900 hasta la fecha DIA/MES/ANYO. */
long int diasAnyosCompletos(int anyo);                   /*Devuelve el n�mero de d�as transcurridos desde el 1/enero/1900 hasta el 1/enero/ANYO. */
int diasEsteAnyo(int dia, int mes, int anyo);            /*Devuelve el n�mero de d�as transcurridos desde el 1/enero/anyo hasta el dia/mes/anyo. */
int diaSemana(long int diasTotales);                     /*Devuelve una representaci�n entera del d�a de la semana que es despues de haber transcurrido NUMDIAS desde el 1/enero/1900. */
string nombreDia(int representacionDia);                 /*Recibe un entero que representa un d�a de la semana (0 si es lunes, 1 si es martes...) y devuelve una cadena con el nombre del d�a. */
int diasQueFaltanDomingos(int representacionDia);		 /*Saca el n�mero de d�as a sumar para saber el primer domingo del a�o*/
string diaDeLaSemana(int dia, int mes, int anyo);		 /*OPCION 1 DEL MEN�: Devuelve una cadena con el nombre del d�a de la semana en que cae la fecha dia/mes/anyo.*/
int primerDomingoMes(int mes, int anyo);				 /*OPCI�N 2 DEL MEN�: solicita un mes de un a�o y devuelve el primer domingo*/
int domingosAnyo(int anyo);								 /*OPCI�N 3 DEL MEN�: solicita un a�o y saca por pantalla todos los domingos */
string nombreMes();
bool puentes();											 /*OPCI�N 4 DEL MEN�: Obtener los posibles puentes de un a�o*/
bool puentesmejora();									 /*OPCI�N 5 DEL MEN�: Obtener los puentes mejorados de un a�o*/
int fechaAnterior(int mes);								 /*Sirve para la opci�n 5 del men�: saca, seg�n los d�as transcurridos, la fecha anterior a la que se comprueba para ver si es fiesta*/

int main(){
	locale::global(locale("spanish"));    /*Sirve para usar caracteres espa�oles*/
	/*DECLARACI�N DE VARIABLES LOCALES*/

	int anyo, dia, mes;
	int anyoFinal = 0;
	string diaRepresentado;
	int opcion = 0;					 /*Opcion del men�*/
	int representacionDia;
	int diasTotales;
	int contador;							 /*Contador que corresponde al n�mero de domingos de un a�o (opci�n 3 del men�)*/
	int primerDia = 1;
	int primerMes = 1;
	int primerDomingo;						 /*Obtiene el primer domingo de un mes (opci�n 2 del men�)*/
	cout << "-------------------------------------------------------------------------------- " << endl;
	cout << "--//Dime qu� d�a de la semana fue, es o ser�  //--" << endl << endl;;

	while (opcion = !0){
		opcion = menu();
		switch (opcion){

		case 0:

			return 0;

		case 1:		/*Calcular el intervalo de d�as [01/enero/1900, dia/mes/anyo] y devolver el d�a de la semana*/
			cout << "-------------------------------------------------------------------------------- " << endl;
			cout << "Has escogido OPCION 1: Calcular el d�a de la semana para una fecha dada. " << endl << endl;
			anyo = solicitaAnyo();
			mes = solicitaMes();
			dia = solicitaDia(mes, anyo);
			diasTotales = diasTranscurridos(dia, mes, anyo);
			if (esBisiesto(anyo) == true){ diasTotales = diasTotales - 1; }
			representacionDia = diaSemana(diasTotales);

			diaRepresentado = nombreDia(representacionDia);


			cout << "El d�a que ha marcado es : " << diaRepresentado << endl << endl;
			cout << "-------------------------------------------------------------------------------- " << endl;
			break;

		case 2:		/*Averigua el primer domingo de mes/anyo*/
			cout << "-------------------------------------------------------------------------------- " << endl;
			cout << "Has escogido OPCION 2: Obtener la fecha correspondiente al primer domingo de un mes en un a�o dado. " << endl << endl;
			anyo = solicitaAnyo();
			mes = solicitaMes();
			primerDomingo = primerDomingoMes(mes, anyo);		/*Se invoca a la funcion primerDomingoMes y se guarda su valor en la variable primerDomingo, que se muestra por pantalla*/
			cout << " El primer domingo del a�o " << anyo << " y mes " << mes << " es el d�a ----------> " << primerDomingo << endl << endl;
			cout << "-------------------------------------------------------------------------------- " << endl;
			break;

		case 3:		/*Muestra por pantalla todos los domingos de un a�o solicitado y el n�mero*/
			cout << "-------------------------------------------------------------------------------- " << endl;
			cout << "Has escogido OPCION 3: Obtener los domingos de un a�o. " << endl << endl;
			anyo = solicitaAnyo();
			contador = domingosAnyo(anyo);		/*Se introduce en la variable contador el valor de la funcion domingosAnyo, que el par�metro que returnea es el n�mero de domingos y se muestra por pantalla*/
			cout << "El n�mero de domingos de " << anyo << " es :" << contador << " ." << endl << endl;
			cout << "-------------------------------------------------------------------------------- " << endl;
			break;

		case 4:		/*Obtener los posibles puentes de un a�o*/
			cout << "-------------------------------------------------------------------------------- " << endl;
			cout << "Has escogido OPCION 4: Obtener los posibles puentes de un a�o. " << endl << endl;
			puentes();
			if (puentes() == false){
				cout << "Ha habido un error al abrir el archivo. " << endl << endl;;
			}
			else{
				cout << "Se ha efectuado correctamente. " << endl << endl;
			}
			cout << "-------------------------------------------------------------------------------- " << endl;
			break;
		case 5:		/*Obtener los puentes mejorados de un a�o*/
			cout << "-------------------------------------------------------------------------------- " << endl;
			cout << "Has escogido OPCION 5: Obtener los puentes mejorados de un a�o. " << endl << endl;
			puentesmejora();
			if (puentesmejora() == false){
				cout << "Ha habido un error al abrir el archivo. " << endl << endl;;
			}
			else{
				cout << "Se ha efectuado correctamente. " << endl << endl;
			}
			cout << "-------------------------------------------------------------------------------- " << endl;
			break;
		}
		/*Hacemos el llamamiento a las FUNCIONES:*/

	}



	system("PAUSE");
	return 0;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
|																																										|
|																	IMPLEMENTACI�N DE FUNCIONES																			|																																				    |
|																																										|
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


int menu(){
	int opcion;

	cout << "1 � Calcular el d�a de la semana para una fecha dada " << endl;
	cout << "2 � Obtener la fecha correspondiente al primer domingo de un mes en un a�o dado" << endl;
	cout << "3 � Obtener los domingos de un a�o" << endl;
	cout << "4 � Obtener los posibles puentes de un a�o " << endl;
	cout << "5 - Obtener los puentes mejorados de un a�o " << endl;
	cout << "0 - Salir" << endl << endl;
	cout << "-------------------------------------------------------------------------------- " << endl;
	cout << "Elija la opci�n que desee realizar: " << endl << endl;
	cin >> opcion;

	while (opcion < 0 || opcion > 5){
		cout << "La opci�n no es correcta. Prueba otra vez: " << endl << endl;
		cin >> opcion;
		cout << endl;
	}
	return opcion;
}

int solicitaAnyo() { /*Solicita, valida y devuelve un a�o introducido por el teclado. Debe ser 1900 o posterior*/
	int anyo;

	cout << "Introduzca un a�o posterior a 1900: " << endl << endl;
	cin >> anyo;
	while (anyo < 1900){                                      /*Ponemos un WHILE para que el a�o no se ACEPTE hasta que no sea mayor o igual que 1900*/
		cout << "La fecha introducida no es correcta. Prueba otra vez: " << endl << endl;
		cin >> anyo;
	}
	/*AQU� DEBEREMOS LLAMAR A LA FUNCION ES BISIESTO PARA SABER SI EL A�O QUE HEMOS MARCADO ES BISIESTO O NO*/
	return anyo;
}

bool esBisiesto(int anyo){                       /*Devuelve un balor booleano que indica si el ANYO es bisiesto o no.*/


	/*Un a�o es bisiesto si: +Es m�ltiplo de 4 pero no de 100    +Es m�ltiplo de 400 */
	if ((anyo % 100 != 0 && anyo % 4 == 0) || anyo % 400 == 0){

		return true;
	}
	else{

		return false;
	}

}

int solicitaMes(){  /*Solicita, valida y devuelve un mes introducido por el teclado. */
	int mes;
	cout << "Introduzca un mes del a�o <del 1 al 12>" << endl << endl;
	cin >> mes;

	while (mes < 1 || mes>12){
		cout << "El mes introducido no es correcto. Prueba otra vez: " << endl << endl;
		cin >> mes;
	}
	return mes;
}

int diasMes(int mes, int anyo){
	int D;		/*La variable D guarda los d�as M�ximos correspondientes a mes/anyo, y se devuelve*/

	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
		D = 31;
	}
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
		D = 30;
	}
	if (mes == 2){
		if (esBisiesto(anyo) == true){
			D = 29;
		}
		else if (esBisiesto(anyo) == false){
			D = 28;
		}
	}

	return D;
}

int solicitaDia(int mes, int anyo){

	int dia;
	int D = diasMes(mes, anyo);		/*Se invoca a la funcion diasMes, que devuelve los d�as maximos de (mes, anyo) y se introduce su valor en la variable D*/

	cout << "Introduzca un d�a <del 1 al " << D << " >." << endl << endl;
	cin >> dia;
	while (dia < 1 || dia > D){
		cout << "D�a no v�lido. Introduzca un d�a <del 1 al " << D << " >." << endl << endl;
		cin >> dia;
	}

	return dia;			/*Se devuelve el d�a elegidos*/
}

int contarBisiestos(int anyoInicio, int anyoFinal){
	int anyosBisiestos;


	anyosBisiestos = (anyoFinal - anyoInicio) / 4;
	return anyosBisiestos;
}

int diasEsteAnyo(int dia, int mes, int anyo){
	int diasAnyoActual;		/*Corresponde a los d�as transcurridos en el intervalo [01/enero/anyo, dia/mes/anyo*/
	int dias = 0;			/*Se inicializa la variable d�as a 0, que es la que va a ejercer de contador*/
	int D;					/*Se llama al par�metro D que, al igual que en la funci�n diasMes, contendr� el valor m�ximo de d�as correspondientes a mes/anyo*/


	for (int i = 1; i <= mes; i++){					/*El procedimiento es hacer un bucle de recorrido que empieze en 1 y acabe en el mes escogido para recorrer los meses necesarios*/
		if (i == mes){
			dias = dias + dia;						/*Este if corresponde a que si el contador de meses ha llegado al mes escogido, se suman todos los d�as que se han
													recorrido desde enero hasta mes m�s el d�a escogido por el usuario, y sale fuera del for*/


		}
		else{

			if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
				D = 31;
			}
			if (i == 4 || i == 6 || i == 9 || i == 11){
				D = 30;
			}
			if (i == 2){
				if (esBisiesto(anyo) == true){
					D = 29;
				}
				if (esBisiesto(anyo) == false){
					D = 28;
				}

			}

			dias = dias + D;						/*Se iguala el valor anterior de d�as(0 en la primera vuelta) y se suma el valor m�ximo de d�as del mes (D), ya que si est� en el ELSE
													significa que no se est� en el mes escogido y, por lo tanto, se recorre entero*/

		}
	}

	diasAnyoActual = dias;							/*Se introduce el valor de dias en la variable diasAnyoActual, y se devuelve*/
	return diasAnyoActual;
}

long int diasAnyosCompletos(int anyo){
	int diasNormales;						/*Corresponden a los d�as transcurridos CORRESPONDIENTES A A�OS NO BISIESTOS en el intervalo [01/enero/1900, 01/enero/anyo]*/
	int diasBisiestos;						/*Corresponden a los d�as transcurridos DURANTE A�OS BISIESTOS en el intervalo [01/enero/1900, 01/enero/anyo]*/
	int diasCompletos;						/*Corresponden al valor de diasNormales + diasBisiestos, es decir, el valor de los d�as transcurridos en el intervalo [01/enero/1900, 01/enero/anyo]*/
	int anyosBisiestos;						/*Es el n�mero de a�os bisiestos en el intervalo [01/enero/1900, 01/enero/anyo]*/
	int anyoFinal = anyo;					/*Se inicializa anyoFinal y se introduce el valor del a�o escogido*/
	int anyosTransc = anyo - anyoInicio;	/*Corresponde al valor de los a�os transcurridos en el intervalo [1900, anyo]*/


	anyosBisiestos = contarBisiestos(anyoInicio, anyoFinal);
	diasNormales = ((anyo - anyoInicio) - anyosBisiestos) * 365;
	diasBisiestos = 366 * anyosBisiestos;
	diasCompletos = diasNormales + diasBisiestos;

	return diasCompletos;		/*Se devuelve el valor de los d�as transcurridos en el intervalo [01/enero/1900, 01/enero/anyo]*/
}

long int diasTranscurridos(int dia, int mes, int anyo){
	int diasTotales;					/*Corresponde al valor de los d�as transcurridos en el intervalo [1/enero/anyo, dia/mes/anyo]*/
	int diasAnyoActual;
	int diasCompletos;
	if (anyoInicio == anyo){			/*Este IF sirve para que si tu introduces el a�o 1900 se reste un d�a a los d�as transcurridos, ya que si no se cuenta dos veces el 1 de enero*/

		diasAnyoActual = diasEsteAnyo(dia, mes, anyo);		/*Se le introduce el valor de los d�as transcurridos en el intervalo [1/enero/anyo, dia/mes/anyo]*/
		diasTotales = diasAnyoActual - 1;

	}

	else {

		diasCompletos = diasAnyosCompletos(anyo);			/*Se le introduce el valor de los d�as transcurridos en el intervalo [01/enero/1900, 01/enero/anyo]*/
		diasAnyoActual = diasEsteAnyo(dia, mes, anyo);		/*Se le introduce el valor de los d�as transcurridos en el intervalo {01/enero/anyo,  dia/mes/anyo]*/
		diasTotales = diasAnyoActual + diasCompletos - 1;	/*Se resta 1 porque la fecha inicial es el UNO DE ENERO DE 1900 y se tiene en cuenta en la suma*/


	}


	return diasTotales;
}

int diaSemana(long int diasTotales){	/*Devuelve el d�a de la semana correspondiente a dia/mes/anyo*/
	/*Le entra por par�metro los d�as transcurridos en el intervalo [01/enero/1900, dia/mes/anyo]*/
	long int i = 1;						/*Se inicializa un LONG contador a 1*/
	int representacionDia = 0;			/*Se inicializa la representacion del d�a a 0 = lunes ya que el 1 de enero de 1900 fue lunes*/


	while (i <= diasTotales){			/*Mientras que el contador no haya llegado a dia/mes/anyo*/

		representacionDia = 0;			/*Se inicializa la prepresentacion del d�a a 0*/

		while (i <= diasTotales && representacionDia <= 6){	/*Mientras que el contador no haya llegado a dia/mes/anyo y la representacion del d�a sea menor o igual a 6*/
			/*Este bucle se traduce en: cada semana vuelve a ser igual a la anterior, as� que cada semana sumo el contador i y la representaci�n del d�a, que con
			el siguiente IF vuelve a ser 0, es decir, lunes*/

			i++;
			representacionDia++;

		}

		if (representacionDia == 7) { representacionDia = 0; }



	}

	return representacionDia;		/*Devuelvo el dia de la semana correspondiente a dia/mes/anyo*/
}

string nombreDia(int representacionDia){	/*Recibe un entero que representa un d�a de la semana (0 si es lunes, 1 si es martes...) y devuelve una cadena con el nombre del d�a. */

	string diaRepresentado;

	switch (representacionDia){

	case 0:
		diaRepresentado = "Lunes";
		break;
	case 1:
		diaRepresentado = "Martes";
		break;
	case 2:
		diaRepresentado = "Miercoles";
		break;
	case 3:
		diaRepresentado = "Jueves";
		break;
	case 4:
		diaRepresentado = "Viernes";
		break;
	case 5:
		diaRepresentado = "S�bado";
		break;
	case 6:
		diaRepresentado = "Domingo";
		break;


	}

	return diaRepresentado;
}

string nombreMes(int mes){		/*Le entra el n�mero del mes y devuelve una cadena con el nombre*/
	string mesRepresentado;

	switch (mes)
	{
	case 1:
		mesRepresentado = "Enero";
		break;
	case 2:
		mesRepresentado = "Febrero";
		break;
	case 3:
		mesRepresentado = "Marzo";
		break;
	case 4:
		mesRepresentado = "Abril";
		break;
	case 5:
		mesRepresentado = "Mayo";
		break;
	case 6:
		mesRepresentado = "Junio";
		break;
	case 7:
		mesRepresentado = "Julio";
		break;
	case 8:
		mesRepresentado = "Agosto";
		break;
	case 9:
		mesRepresentado = "Septiembre";
		break;
	case 10:
		mesRepresentado = "Octubre";
		break;
	case 11:
		mesRepresentado = "Noviembre";
		break;
	case 12:
		mesRepresentado = "Diciembre";
		break;

	default:
		break;
	}
	return mesRepresentado;
}

int diasqueFaltandomingo(int representacionDia){
	int diasAsumar = 6 - representacionDia;

	return diasAsumar;
}

int primerDomingoMes(int mes, int anyo){
	int dia;
	dia = 1;
	int anyosBisiestos;
	int diasTotales;
	int representacionDia;
	int diasAsumar;
	int anyoFinal = anyo;
	int primerDomingo;

	anyosBisiestos = contarBisiestos(anyoInicio, anyoFinal);
	diasTotales = diasTranscurridos(dia, mes, anyo);
	cout << "Los d�as transcurridos han sido :" << diasTotales << endl;
	representacionDia = diaSemana(diasTotales);
	if (esBisiesto(anyo) == true) { representacionDia = representacionDia - 1; }
	diasAsumar = diasqueFaltandomingo(representacionDia);
	primerDomingo = dia + diasAsumar;

	return primerDomingo;
}

int domingosAnyo(int anyo){

	int anyosBisiestos;
	int anyoFinal = anyo;
	int diasTotales;
	int contador = 0;

	anyosBisiestos = contarBisiestos(anyoInicio, anyoFinal);

	for (int j = 1; j <= 12; j++){

		int mes = j;
		int diasMax;
		diasMax = diasMes(mes, anyo);

		for (int x = 1; x <= diasMax; x++){

			int dia = x;
			int representacionDia;
			diasTotales = diasTranscurridos(dia, mes, anyo);
			if (esBisiesto(anyo) == true){ diasTotales = diasTotales - 1; }
			representacionDia = diaSemana(diasTotales);

			if (representacionDia == 6){

				cout << dia << " de " << nombreMes(mes) << "." << endl;
				contador = contador + 1;
			}

			if (representacionDia == 7){

				representacionDia = 0;
			}
		}
	}
	return contador;		/*Devuelve el n�mero de domingos del a�o elegido*/
}

string diaDeLaSemana(int dia, int mes, int anyo){
	string diaRepresentado;
	int anyosBisiestos;
	int anyoFinal = anyo;
	int diasTotales;
	int representacionDia;


	if (esBisiesto(anyo) == true){
		cout << " El a�o " << anyo << " es bisiesto" << endl << endl;
	}
	else {
		cout << " El a�o " << anyo << " NO es bisiesto " << endl << endl;
	}


	anyosBisiestos = contarBisiestos(anyoInicio, anyoFinal);				/*Contamos los a�os bisiestos*/

	diasTotales = diasTranscurridos(dia, mes, anyo);						/*Introducimos en diasTotales el valor de la funci�n diasTranscurridos*/
	cout << "Los d�as transcurridos han sido :" << diasTotales << endl << endl;

	representacionDia = diaSemana(diasTotales);								/*Introducimos en la variabloe representacionDia el valor de la funcion diaSemana con el nombre del d�a*/

	if (esBisiesto(anyo) == true) { representacionDia = representacionDia - 1; }
	diaRepresentado = nombreDia(representacionDia);							/*Introducimos en la variable diaRepresentado el nombre del d�a correspondiente a su representaci�n*/


	return diaRepresentado;
}

bool puentes(){

	int anyo, mes, dia;
	int diasTotales;
	int representacionDia;
	string diaRepresentado;
	ifstream fiestas;
	ofstream puentes;
	fiestas.open("fiestas.txt");

	if (!fiestas.is_open()){

		cout << "Se ha producido un error en la apertura del archivo fiestas.txt" << endl;
		return false;
	}
	puentes.open("puentes.txt");
	if (!puentes.is_open()){
		fiestas.close();
		cout << "Se ha producido un error en la apertura del archivo puentes.txt" << endl;
	}

	fiestas >> anyo;

	puentes << anyo << endl;
	fiestas >> dia >> mes;

	while (dia != 0 && mes != 0){
		diasTotales = diasTranscurridos(dia, mes, anyo);
		if (esBisiesto(anyo) == true){ diasTotales = diasTotales - 1; }
		representacionDia = diaSemana(diasTotales);
		diaRepresentado = nombreDia(representacionDia);

		if (diaRepresentado == "Martes" || diaRepresentado == "Jueves"){
			puentes << dia << " " << mes << " " << diaRepresentado << endl;
		}

		fiestas >> dia >> mes;
		if (dia == 0 && mes == 0){
			puentes << dia << " " << mes << " " << "XXX" << endl;
		}
	}
	puentes.close();
	fiestas.close();
	return true;
}

bool puentesmejora(){

	int anyo, mes, dia;
	int diaanterior;								/*Contiene la variable correspondiente al d�a anterior, para comprobar si es fiesta(viene dado por la funcion fechaAnterior(mes)]*/
	int diasTotales;
	int representacionDia;
	string diaRepresentado;
	ifstream fiestas2;
	ofstream puentesmejora;
	int fechanterior, diaposterior, mesposterior;	/*Contiene la fecha anterior, la fecha posterior y el mes porterior al d�a que es puente, para comprobar si es fiesta*/
	int fechaposterior;


	fiestas2.open("fiestas.txt");

	if (!fiestas2.is_open()){

		cout << "Se ha producido un error en la apertura del archivo fiestas.txt" << endl;
		return false;
	}
	puentesmejora.open("puentesm.txt");
	if (!puentesmejora.is_open()){
		fiestas2.close();
		cout << "Se ha producido un error en la apertura del archivo puentes.txt" << endl;
	}


	fiestas2 >> anyo;

	puentesmejora << anyo << endl;
	fiestas2 >> dia >> mes;									/*Lees el primer dia del archivo fiestas2*/

	diasTotales = diasTranscurridos(dia, mes, anyo);
	if (esBisiesto(anyo) == true){ diasTotales = diasTotales - 1; }
	representacionDia = diaSemana(diasTotales);
	diaRepresentado = nombreDia(representacionDia);
	if (diaRepresentado == "Martes"){						/*Si el primer dia es martes se escribe directamente porque el lunes no estar�a escrito*/
		puentesmejora << dia << " " << mes << " " << diaRepresentado << endl;
		fechanterior = dia;									/*Cada vez que se escribe un dia pasa ser fechaanterior*/
	}
	while (dia != 0 && mes != 0){



		if (diaRepresentado == "Martes"){
			if (dia == 1){									/*Si el dia es 1 no puedo hacer -1 para ver el lunes porque seria dia 0*/
				diaanterior = fechaAnterior(mes);			/*Funci�n que ve si el dia es 1 que dia tiene detras*/
				if (fechanterior != diaanterior){			/*Si no esta su anterior en la lista de fiestas se escribe*/
					puentesmejora << dia << " " << mes << " " << diaRepresentado << endl;
					fechanterior = dia;						/*Pasa a ser fechanterior*/
				}
			}
			else{
				if (fechanterior != dia - 1){				/*Si el dia no es 1 hace el mismo trabajo*/
					puentesmejora << dia << " " << mes << " " << diaRepresentado << endl;
					fechanterior = dia;
				}
			}
		}

		if (diaRepresentado == "Jueves"){

			fiestas2 >> diaposterior >> mesposterior;		/*Si es jueves leemos la siguiente linea para poder trabajar con ella (necesitamos el posterior)*/
			if (dia == 31 || dia == 30 || dia == 29 || dia == 28){/*Esto se necesita para regular el dia posterior, si es 31 que no sea 32, etc..*/
				if (esBisiesto(anyo) == true){
					if (dia == 31 || dia == 30 || dia == 29){ fechaposterior = 1; }/*Hacemos que el siguiente dia de estos dias extremos sea 1*/
					if (diaposterior != fechaposterior){
						puentesmejora << dia << " " << mes << " " << diaRepresentado << endl;
					}

				}
				else{
					if (dia == 31 || dia == 30 || dia == 28){ fechaposterior = 1; }
					if (diaposterior != fechaposterior){
						puentesmejora << dia << " " << mes << " " << diaRepresentado << endl;
					}
				}
			}
			else{
				if (diaposterior != dia + 1){
					puentesmejora << dia << " " << mes << " " << diaRepresentado << endl;
				}
			}
		}

		fechanterior = dia;									/*Guarda la fecha anterior en la variable dia, la cual coje su valor del OFSTREAM fiestas 2*/
		fiestas2 >> dia >> mes;
		diasTotales = diasTranscurridos(dia, mes, anyo);
		if (esBisiesto(anyo) == true){ diasTotales = diasTotales - 1; }
		representacionDia = diaSemana(diasTotales);
		diaRepresentado = nombreDia(representacionDia);
		if (dia == 0 && mes == 0){
			puentesmejora << dia << " " << mes << " " << "XXX" << endl;
		}
	}
	fiestas2.close();				/*Se cierran los flujos*/
	puentesmejora.close();
	return true;
}

int fechaAnterior(int mes){			/*Sirve para la opci�n 5 del men�: saca, seg�n los d�as transcurridos, la fecha anterior a la que se comprueba para ver si es fiesta*/
	int D;							/*Se introduce D, que guardar� los d�as que tiene un mes*/
	int diaanterior;
	mes = mes - 1;					/*Se le resta un mes porque tienes que mirar la fecha del mes anterior*/
	if (mes == 0){ mes = 12; }		/*Si el mes es enero, el anterior es diciembre*/

	D = diasMes(mes, 1900);			/*Mira el n�mero m�ximo de d�as que tiene ese mes en 1900*/

	diaanterior = D;

	return diaanterior;				/*Se devuelve el valor final de D, guardado en diaAnterior*/
}