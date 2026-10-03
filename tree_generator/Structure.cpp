/*******************************************************/
/* Fichero: Structure.cpp            Fecha: 02-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementacion de la clase  */
/*              structure.                             */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "Structure.h"

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
Structure::Structure() {
	setInitialPoint(NULL);
	setFinalPoint(NULL);
	setInitialDiameter(-1.0);
	setFinalDiameter(-1.0);
	setNumberBranch(-1);
	setBranches(NULL);
	setFather(NULL);
	setChildren(NULL);
	setAlfa(-1);
	setGamma(-1);
	setHigh(-1.0);
	setState(-1);
	setGeneration(-1);
	setOld(-1);
	setDeviousness(NULL);
	setCDeviousness(0);
}

/***************************************************************/
/* Funcion: Destructor                                         */
/*															   */
/* Descripcion: Función que eliminar los valores de la clase   */
/***************************************************************/
Structure::~Structure() {
	int i = 0;

	if (getInitialPoint() != NULL) {
		delete getInitialPoint();
		setInitialPoint(NULL);
	}
	if (getFinalPoint() != NULL) {
		delete getFinalPoint();
		setFinalPoint(NULL);
	}
	if (getDeviousness() != NULL) {
		delete getDeviousness();
		setDeviousness(NULL);
	}
	if (getBranches() != NULL) {
		for(i = 0; i < getNumberBranch(); i++) {
			if (getBranches()[i] != NULL) {
				delete getBranches()[i];
				getBranches()[i] = NULL;
			}
		}
		free(getBranches());
		setBranches(NULL);
	}
	if (getChildren() != NULL) {
		delete getChildren();
		setChildren(NULL);
	}
}

/***************************************************************/
/* Funcion: getInitialPoint                                    */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              initialPoint de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Point*: El punto inicial del tramo.     */ 
/***************************************************************/
Point* Structure::getInitialPoint() {
	return this->initialPoint;
}

/***************************************************************/
/* Funcion: getFinalPoint                                      */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              finalPoint de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Point*: El punto final del tramo.       */ 
/***************************************************************/
Point* Structure::getFinalPoint() {
	return this->finalPoint;
}

/***************************************************************/
/* Funcion: getInitialDiameter                                 */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              initialDiameter de la clase.                   */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El diametro inicial del tramo.   */ 
/***************************************************************/
float Structure::getInitialDiameter() {
	return this->initialDiameter;
}

/***************************************************************/
/* Funcion: getFinalDiameter                                   */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              finalDiameter de la clase.                     */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El diametro inicial del tramo.   */ 
/***************************************************************/
float Structure::getFinalDiameter() {
	return this->finalDiameter;
}

/***************************************************************/
/* Funcion: getNumberBranch                                    */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              numberBranch de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El numero de ramas del tramo.      */ 
/***************************************************************/
int Structure::getNumberBranch() {
	return this->numberBranch;
}

/***************************************************************/
/* Funcion: getBranches                                        */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              branches de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Structure**: Las ramas del tramo.       */
/***************************************************************/
Structure** Structure::getBranches() {
	return this->branches;
}

/***************************************************************/
/* Funcion: getFather                                          */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              father de la clase.                            */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Structure*: El tramo antecesor.         */
/***************************************************************/
Structure* Structure::getFather() {
	return this->father;
}

/***************************************************************/
/* Funcion: getChildren                                        */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              children de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Structure*: El tramo sucesor.           */
/***************************************************************/
Structure* Structure::getChildren() {
	return this->children;
}

/***************************************************************/
/* Funcion: getAlfa                                            */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              alfa de la clase.                              */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El angulo alfa que afecta al     */
/*                            tramo.                           */
/***************************************************************/
float Structure::getAlfa() {
	return this->alfa;
}

/***************************************************************/
/* Funcion: getGamma                                           */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              gamma de la clase.                             */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El angulo gamma que afecta al    */
/*                            tramo.                           */
/***************************************************************/
float Structure::getGamma() {
	return this->gamma;
}

/***************************************************************/
/* Funcion: getHigh                                            */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              high de la clase.                              */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La altura del tramo.             */
/***************************************************************/
float Structure::getHigh() {
	return this->high;
}

/***************************************************************/
/* Funcion: getState                                           */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              state de la clase.                             */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El estado del tramo.               */
/***************************************************************/
int Structure::getState() {
	return this->state;
}

/***************************************************************/
/* Funcion: getGeneration                                      */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              generation de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: La generacion del tramo.           */
/***************************************************************/
int Structure::getGeneration() {
	return this->generation;
}

/***************************************************************/
/* Funcion: getOld                                             */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              old de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El numero de padres del tramo.     */
/***************************************************************/
int Structure::getOld() {
	return this->old;
}

/***************************************************************/
/* Funcion: getCDeviousness                                    */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              cDeviousness de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El indicador de tortuosidad.       */
/***************************************************************/
int Structure::getCDeviousness() {
	return this->cDeviousness;
}

/***************************************************************/
/* Funcion: getDeviousness                                     */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              deviousness de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Structure*: El tramo disociado.         */
/***************************************************************/
Structure* Structure::getDeviousness() {
	return this->deviousness;
}

/***************************************************************/
/* Funcion: setInitialPoint                                    */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              initialPoint de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: Point* initialPoint: El punto inicial  */
/*                                           del tramo.        */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setInitialPoint(Point* initialPoint) {
	this->initialPoint = initialPoint;
}

/***************************************************************/
/* Funcion: setFinalPoint                                      */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              finalPoint de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: Point* finalPoint: El punto final del  */
/*                                         tramo.              */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setFinalPoint(Point* finalPoint) {
	this->finalPoint = finalPoint;
}

/***************************************************************/
/* Funcion: setInitialDiameter                                 */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              initialDiameter de la clase.                   */
/*                                                             */ 
/* Argumentos: Entrada: float intialDiameter: El diametro      */
/*                                            inicial del tramo*/ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setInitialDiameter(float initialDiameter) {
	this->initialDiameter = initialDiameter;
}

/***************************************************************/
/* Funcion: setFinalDiameter                                   */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              finalDiameter de la clase.                     */
/*                                                             */ 
/* Argumentos: Entrada: float finalDiameter: El diametro final */
/*                                           del tramo.        */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setFinalDiameter(float finalDiameter) {
	this->finalDiameter = finalDiameter;
}

/***************************************************************/
/* Funcion: setNumberBranch                                    */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              numberBranch de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: int numberBranch: El numero de ramas   */
/*                                        del tramo.           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setNumberBranch(int numberBranch) {
	this->numberBranch = numberBranch;
}

/***************************************************************/
/* Funcion: setBranches                                        */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              branches de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: Structure** branches: La estructura de */
/*                                            las ramas del    */ 
/*                                            tramo.           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setBranches(Structure** branches) {
	this->branches = branches;
}

/***************************************************************/
/* Funcion: setFather                                          */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              father de la clase.                            */
/*                                                             */ 
/* Argumentos: Entrada: Structure* father: La estructura del   */
/*                                         tramo antecesor del */ 
/*                                         tramo actual.       */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setFather(Structure* father) {
	this->father = father;
}

/***************************************************************/
/* Funcion: setChildren                                        */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              children de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: Structure* children: La estructura del */
/*                                           tramo sucesor del */ 
/*                                           tramo actual.     */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setChildren(Structure* children) {
	this->children = children;
}

/***************************************************************/
/* Funcion: setAlfa                                            */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              alfa de la clase.                              */
/*                                                             */ 
/* Argumentos: Entrada: float alfa: El angulo que afecta al    */
/*                                  tramo.                     */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setAlfa(float alfa) {
	this->alfa = alfa;
}

/***************************************************************/
/* Funcion: setGamma                                           */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              gamma de la clase.                             */
/*                                                             */ 
/* Argumentos: Entrada: float gamma: El angulo que afecta al   */
/*                                   tramo.                    */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setGamma(float gamma) {
	this->gamma = gamma;
}

/***************************************************************/
/* Funcion: setHigh                                            */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              high de la clase.                              */
/*                                                             */ 
/* Argumentos: Entrada: float high: La altura del tramo.       */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setHigh(float high) {
	this->high = high;
}

/***************************************************************/
/* Funcion: setState                                           */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              state de la clase.                             */
/*                                                             */ 
/* Argumentos: Entrada: int state: El estado del tramo.        */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setState(int state) {
	this->state = state;
}

/***************************************************************/
/* Funcion: setGeneration                                      */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              generation de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: int generation: La generacion del tramo*/
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setGeneration(int generation) {
	this->generation = generation;
}

/***************************************************************/
/* Funcion: setOld                                             */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              old de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: int old: El numero de padres del tramo.*/
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setOld(int old) {
	this->old = old;
}

/***************************************************************/
/* Funcion: setcDeviousness                                    */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              cDeviousness de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: int cDeviousness: El controlador de    */
/*                                        tortuosidad.         */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setCDeviousness(int cDeviousness) {
	this->cDeviousness = cDeviousness;
}

/***************************************************************/
/* Funcion: setdeviousness                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              deviousness de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: Structure* deviousness: El tramo a     */
/*                                              disociar.      */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::setDeviousness(Structure* deviousness) {
	this->deviousness = deviousness;
}

/***************************************************************/
/* Funcion: born                                               */
/*															   */
/* Descripcion: Función que indica el estado de nacimiento.    */
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::born() {
	state = 0;
}

/***************************************************************/
/* Funcion: life                                               */
/*															   */
/* Descripcion: Función que indica el estado de vida.          */
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::life() {
	state = 1;
}

/***************************************************************/
/* Funcion: dead                                               */
/*															   */
/* Descripcion: Función que indica el estado de muerte.        */
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Structure::dead() {
	state = 2;
}
