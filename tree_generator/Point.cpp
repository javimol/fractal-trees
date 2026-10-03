/*******************************************************/
/* Fichero: Point.cpp                Fecha: 02-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementacion de la clase  */
/*              point.                                 */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "Point.h"

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
Point::Point() {
	setX(0.0);
	setY(0.0);
	setZ(0.0);
}

/***************************************************************/
/* Funcion: Destructor                                         */
/*															   */
/* Descripcion: Función que eliminar los valores de la clase   */
/***************************************************************/
Point::~Point() {
}

/***************************************************************/
/* Funcion: getX                                               */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              x de la clase.                                 */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La coordenada x del punto.       */ 
/***************************************************************/
float Point::getX() {
	return this->x;
}

/***************************************************************/
/* Funcion: getY                                               */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              y de la clase.                                 */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La coordenada y del punto.       */ 
/***************************************************************/
float Point::getY() {
	return this->y;
}

/***************************************************************/
/* Funcion: getZ                                               */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              z de la clase.                                 */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La coordenada z del punto.       */ 
/***************************************************************/
float Point::getZ() {
	return this->z;
}

/***************************************************************/
/* Funcion: setX                                               */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              x de la clase.                                 */
/*                                                             */ 
/* Argumentos: Entrada: float x: La coordenada x de la clase.  */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Point::setX(float x) {
	this->x = x;
}

/***************************************************************/
/* Funcion: setY                                               */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              y de la clase.                                 */
/*                                                             */ 
/* Argumentos: Entrada: float y: La coordenada y de la clase.  */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Point::setY(float y) {
	this->y = y;
}

/***************************************************************/
/* Funcion: setZ                                               */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              z de la clase.                                 */
/*                                                             */ 
/* Argumentos: Entrada: float z: La coordenada z de la clase.  */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Point::setZ(float z) {
	this->z = z;
}

