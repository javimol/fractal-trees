/*******************************************************/
/* Fichero: Aleator.cpp              Fecha: 03-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementacion de la clase  */
/*              aleator.                               */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "Aleator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/***************************************************************/
/* Funcion: Constructor por defecto                            */
/*															   */
/* Descripcion: Función que inicializa los valores de la clase */
/***************************************************************/
Aleator::Aleator() {
	setMax(0);
	setMin(0);
	setRandomize(0);
}

/***************************************************************/
/* Funcion: Destructor                                         */
/*															   */
/* Descripcion: Función que eliminar los valores de la clase   */
/***************************************************************/
Aleator::~Aleator() {
}

/***************************************************************/
/* Funcion: getMax                                             */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              max de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El maximo valor obtenible.         */ 
/***************************************************************/
int Aleator::getMax() {
	return this->max;
}

/***************************************************************/
/* Funcion: getMin                                             */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              min de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El minimo valor obtenible.         */ 
/***************************************************************/
int Aleator::getMin() {
	return this->min;
}

/***************************************************************/
/* Funcion: getRandomize                                       */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              randomize de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El flag de inicializacion.         */ 
/***************************************************************/
int Aleator::getRandomize() {
	return this->randomize;
}

/***************************************************************/
/* Funcion: setMax                                             */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              max de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: int max: El maximo valor obtenible.    */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Aleator::setMax(int max) {
	this->max = max;
}

/***************************************************************/
/* Funcion: setMin                                             */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              min de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: int min: El minimo valor obtenible.    */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Aleator::setMin(int min) {
	this->min = min;
}

/***************************************************************/
/* Funcion: setRandomize                                       */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              randomize de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: int randomize: El flag para indicar la */
/*                                     inicializacion.         */  
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Aleator::setRandomize(int randomize) {
	this->randomize = randomize;
}

/***************************************************************/
/* Funcion: alea                                               */
/*															   */
/* Descripcion: Función que obtiene un valor aleatorio.        */
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: int: El valor entero aleatorio obtenido.*/ 
/***************************************************************/
int Aleator::alea() {
	int iP, iU;

	iP = getMin();
	iU = getMax();

	// Si no se inicializo la semilla
	if (getRandomize() == 0)  {
		srand(time(NULL));
		setRandomize(1);
	}

    return iP+(int)((double)(iU-iP+1)*(double)rand()/(double)(RAND_MAX+1.0));
   
}