/*******************************************************/
/* Fichero: Parameters.cpp           Fecha: 27-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementacion de la clase  */
/*              parameters.                            */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "Parameters.h"

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
Parameters::Parameters() {
	setMaxHeight(-1.0);
	setPaceGrowth(-1.0);
	setAge(-1);
	setHeight(-1.0);
	setRatioTop(-1.0);
	setHeightTrunk(-1.0);
	setHeightTop(-1.0);
	setRatioBranch(-1.0);
	setFrondage(-1.0);
	setInvFrondage(-1.0);
	setTreeCone(-1);
	setVarTreeCone(-1);
	setMaxAngle(-1);
	setMinAngle(-1);
	setRatioTrunk(-1.0);
	setRatioBase(-1.0);
	setDiameterBase(-1.0);
	setRatioDiameter2(-1.0);
	setRatioDiameter(-1.0);
	setDeviousness(-1.0);
	setInvDeviousness(-1.0);
	setDeviousnessAngle(-1);
	setDeviousnessArch(-1);
	setVariability(-1.0);
	setProbabilityTrunk(-1.0);
	setAleator(NULL);
	setGeneration(-1);
}

/***************************************************************/
/* Funcion: Destructor                                         */
/*															   */
/* Descripcion: Función que eliminar los valores de la clase   */
/***************************************************************/
Parameters::~Parameters() {
	if (getAleator() != NULL) {
		delete getAleator();
		setAleator(NULL);
	}
}

/***************************************************************/
/* Funcion: getMaxHeight                                       */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              maxHeight de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La maxima altura del arbol.      */ 
/***************************************************************/
float Parameters::getMaxHeight() {
	return this->maxHeight;
}

/***************************************************************/
/* Funcion: getPaceGrowth                                      */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              paceGrowth de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El ritmo de crecimiento del arbol*/
/***************************************************************/
float Parameters::getPaceGrowth() {
	return this->paceGrowth;
}

/***************************************************************/
/* Funcion: getAge                                             */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              age de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: La edad del arbol (en meses).      */
/***************************************************************/
int Parameters::getAge() {
	return this->age;
}

/***************************************************************/
/* Funcion: getHeigth                                          */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              height de la clase.                            */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La altura del arbol.             */
/***************************************************************/
float Parameters::getHeight() {
	return this->height;
}

/***************************************************************/
/* Funcion: getRatioTop                                        */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              ratioTop de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La relacion entre la copa y el   */
/*                            tronco.                          */
/***************************************************************/
float Parameters::getRatioTop() {
	return this->ratioTop;
}

/***************************************************************/
/* Funcion: getHeightTrunk                                     */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              heightTrunk de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La altura del tronco.            */
/***************************************************************/
float Parameters::getHeightTrunk() {
	return this->heightTrunk;
}

/***************************************************************/
/* Funcion: getHeightTop                                       */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              heightTop de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La altura de la copa.            */
/***************************************************************/
float Parameters::getHeightTop() {
	return this->heightTop;
}

/***************************************************************/
/* Funcion: getRatioBranch                                     */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              ratioBranch de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La relacion entre niveles de     */
/*                            ramas.                           */
/***************************************************************/
float Parameters::getRatioBranch() {
	return this->ratioBranch;
}

/***************************************************************/
/* Funcion: getFrondage                                        */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              frondage de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La frondosidad del arbol.        */
/***************************************************************/
float Parameters::getFrondage() {
	return this->frondage;
}

/***************************************************************/
/* Funcion: getInvFrondage                                     */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              invFrondage de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La frondosidad del arbol.        */
/***************************************************************/
float Parameters::getInvFrondage() {
	return this->invFrondage;
}

/***************************************************************/
/* Funcion: getTreeCone                                        */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              treeCone de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El cone de crecimiento del arbol.  */
/***************************************************************/
float Parameters::getTreeCone() {
	return this->treeCone;
}

/***************************************************************/
/* Funcion: getVarTreeCone                                     */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              varTreeCone de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: La variacion del cono.             */
/***************************************************************/
float Parameters::getVarTreeCone() {
	return this->varTreeCone;
}

/***************************************************************/
/* Funcion: getMaxAngle                                        */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              maxAngle de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: el angulo maximo de giro.          */
/***************************************************************/
int Parameters::getMaxAngle() {
	return this->maxAngle;
}

/***************************************************************/
/* Funcion: getMinAngle                                        */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              minAngle de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: el angulo minimo de giro.          */
/***************************************************************/
int Parameters::getMinAngle() {
	return this->minAngle;
}

/***************************************************************/
/* Funcion: getRatioTrunk                                      */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              ratioTrunk de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La relacion entre longitud del   */
/*                            tronco y la longitud de la rama. */
/***************************************************************/
float Parameters::getRatioTrunk() {
	return this->ratioTrunk;
}

/***************************************************************/
/* Funcion: getRatioBase                                       */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              ratioBase de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La relacion entre el diametro de */
/*                            la base y la altura del arbo.    */
/***************************************************************/
float Parameters::getRatioBase() {
	return this->ratioBase;
}

/***************************************************************/
/* Funcion: getDiameterBase                                    */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              diameterBase de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El diametro de la base del arbol.*/
/***************************************************************/
float Parameters::getDiameterBase() {
	return this->diameterBase;
}

/***************************************************************/
/* Funcion: getRatioDiameter2                                  */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              ratioDiameter2 de la clase.                    */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La relacion entre el diametro de */
/*                            la parte superior del arbol y    */
/*                            su parte inferior.               */
/***************************************************************/
float Parameters::getRatioDiameter2() {
		return this->ratioDiameter2;
}

/***************************************************************/
/* Funcion: getRatioDiameter                                   */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              ratioDiameter de la clase.                     */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La relacion entre el diametero   */
/*                            del tronco con el diametro de la */
/*                            rama.                            */
/***************************************************************/
float Parameters::getRatioDiameter() {
	return this->ratioDiameter;
}

/***************************************************************/
/* Funcion: getDeviousness                                     */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              deviousness de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El grado de tortuosidad del arbol*/
/***************************************************************/
float Parameters::getDeviousness() {
	return this->deviousness;
}

/***************************************************************/
/* Funcion: getInvDeviousness                                  */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              invDeviousness de la clase.                    */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: El inverso del deviousness.      */
/***************************************************************/
float Parameters::getInvDeviousness() {
	return this->invDeviousness;
}

/***************************************************************/
/* Funcion: getDeviousnessAngle                                */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              deviousnessAngle de la clase.                  */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El angulo de giro para los giros   */
/*                          del arbol.     .                   */
/***************************************************************/
int Parameters::getDeviousnessAngle() {
	return this->deviousnessAngle;
}

/***************************************************************/
/* Funcion: getDeviousnessArch                                 */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              deviousnessArch de la clase.                   */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El angulo de giro para los giros   */
/*                          del arbol.     .                   */
/***************************************************************/
int Parameters::getDeviousnessArch() {
	return this->deviousnessArch;
}

/***************************************************************/
/* Funcion: getVariability                                     */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              variability de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: Indica la variabilidad de la     */
/*                            especie de arboles.              */
/***************************************************************/
float Parameters::getVariability() {
	return this->variability;
}

/***************************************************************/
/* Funcion: getAleator                                         */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              aleator de la clase.                           */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Aleator*: Un puntero al generador de    */
/*                               numeros aleatorios.           */
/***************************************************************/
Aleator* Parameters::getAleator() {
	return this->aleator;
}

/***************************************************************/
/* Funcion: getProbabilityTrunk                                */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              probabilityTrunk de la clase.                  */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float: La probabilidad de continuidad   */
/*                            del tronco.                      */
/***************************************************************/
float Parameters::getProbabilityTrunk() {
	return this->probabilityTrunk;
}

/***************************************************************/
/* Funcion: getGeneration                                      */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              generation de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El numero de generaciones del arbol*/
/***************************************************************/
int Parameters::getGeneration() {
	return this->generation;
}

/***************************************************************/
/* Funcion: setMaxHeight                                       */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              maxHeight de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: float maxHeight: La altura maxima del  */
/*                                       arbol.                */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setMaxHeight(float maxHeight) {
	this->maxHeight = maxHeight;
	setHeight(calculateHeight());
}

/***************************************************************/
/* Funcion: setPaceGrowth                                      */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              paceGrowth de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: float paceGrowth: El ritmo de creci-   */
/*                                        miento del arbol.    */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setPaceGrowth(float paceGrowth) {
	this->paceGrowth = paceGrowth;
	setHeight(calculateHeight());
}

/***************************************************************/
/* Funcion: setAge                                             */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              age de la clase.                               */
/*                                                             */ 
/* Argumentos: Entrada: int age: La edad (en meses) del arbol. */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setAge(int age) {
	this->age = age;
	setHeight(calculateHeight());
}

/***************************************************************/
/* Funcion: setHeight                                          */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              height de la clase.                            */
/*                                                             */ 
/* Argumentos: Entrada: float height: La altura del arbol.     */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setHeight(float height) {
	this->height = height;
	setHeightTrunk(calculateHeightTrunk());
	setHeightTop(calculateHeightTop());
	setDiameterBase(calculateDiameterBase());
}

/***************************************************************/
/* Funcion: setRatioTop                                        */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              ratioTop de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: float ratioTop: El ratio entre copa y  */
/*                                      tronco.                */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setRatioTop(float ratioTop) {
	this->ratioTop = ratioTop;
	setHeightTrunk(calculateHeightTrunk());
	setHeightTop(calculateHeightTop());
}

/***************************************************************/
/* Funcion: setHeightTrunk                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              heightTrunk de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: float heightTrunk: La altura del tronco*/
/*                                         del arbol.          */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setHeightTrunk(float heightTrunk) {
	this->heightTrunk = heightTrunk;
}

/***************************************************************/
/* Funcion: setHeightTop                                       */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              heightTop de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: float heightTop: La altura de la copa  */
/*                                       del arbol.            */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setHeightTop(float heightTop) {
	this->heightTop = heightTop;
}

/***************************************************************/
/* Funcion: setRatioBranch                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              ratioBranch de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: float ratioBranch: El ratio de entre   */
/*                                         niveles de ramajes. */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setRatioBranch(float ratioBranch) {
	this->ratioBranch = ratioBranch;
}

/***************************************************************/
/* Funcion: setFrondage                                        */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              frondage de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: float frondage: El indicador de        */
/*                                      frondosidad del arbol. */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setFrondage(float frondage) {
	this->frondage = frondage;
	setInvFrondage(inverse(frondage));
}

/***************************************************************/
/* Funcion: setInvFrondage                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              invFrondage de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: float invFrondage: El inverso de la    */
/*                                         frondosidad.        */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setInvFrondage(float invFrondage) {
	this->invFrondage = invFrondage;
}

/***************************************************************/
/* Funcion: setTreeCone                                        */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              treeCone de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: float treeCone: El cono de crecimiento */
/*                                      del arbol.             */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setTreeCone(float treeCone) {
	this->treeCone = treeCone;
}

/***************************************************************/
/* Funcion: setVarTreeCone                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              varTreeCone de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: float varTreeCone: La variacion del    */
/*                                         cono de crecimiento.*/
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setVarTreeCone(float varTreeCone) {
	this->varTreeCone = varTreeCone;
}

/***************************************************************/
/* Funcion: setMaxAngle                                        */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              maxAngle de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: int maxAngle: El giro maximo en la     */
/*                                    dirección perpendicular a*/
/*                                    la del crecimiento.      */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setMaxAngle(int maxAngle) {
	this->maxAngle = maxAngle;
}

/***************************************************************/
/* Funcion: setMinAngle                                        */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              minAngle de la clase.                          */
/*                                                             */ 
/* Argumentos: Entrada: int minAngle: El giro minimo en la     */
/*                                    dirección perpendicular a*/
/*                                    la del crecimiento.      */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setMinAngle(int minAngle) {
	this->minAngle = minAngle;
}

/***************************************************************/
/* Funcion: setRatioBranch                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              ratioBranch de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: float ratioBranch: El ratio de entre   */
/*                                         niveles de ramajes. */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setRatioTrunk(float ratioTrunk) {
	this->ratioTrunk = ratioTrunk;
}

/***************************************************************/
/* Funcion: setRatioBranch                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              ratioBranch de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: float ratioBranch: El ratio de entre   */
/*                                         niveles de ramajes. */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setRatioBase(float ratioBase) {
	this->ratioBase = ratioBase;
	setDiameterBase(calculateDiameterBase());
}

/***************************************************************/
/* Funcion: setDiameterBase                                    */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              diameterBase de la clase.                      */
/*                                                             */ 
/* Argumentos: Entrada: float diameterBase: El diametro de la  */
/*                                          base del arbol.    */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setDiameterBase(float diameterBase) {
	this->diameterBase = diameterBase;
}

/***************************************************************/
/* Funcion: setRatioDiameter2                                  */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              ratioDiameter2 de la clase.                    */
/*                                                             */ 
/* Argumentos: Entrada: float ratioDiameter2: El ratio entre   */
/*                                            diametros entre  */ 
/*                                            niveles de ramaje*/
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setRatioDiameter2(float ratioDiameter2) {
	this->ratioDiameter2 = ratioDiameter2;
}

/***************************************************************/
/* Funcion: setRatioDiameter                                   */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              ratioDiameter de la clase.                     */
/*                                                             */ 
/* Argumentos: Entrada: float ratioDiameter: El ratio entre    */
/*                                           el diametro de    */
/*                                           un tronco y el    */
/*                                           diametro de una   */ 
/*                                           rama del mismo.   */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setRatioDiameter(float ratioDiameter) {
	this->ratioDiameter = ratioDiameter;
}

/***************************************************************/
/* Funcion: setDeviousness                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              deviousness de la clase.                       */
/*                                                             */ 
/* Argumentos: Entrada: float deviousness: Indica lo retorcido */
/*                                         de la apariencia del*/
/*                                         arbol.              */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setDeviousness(float deviousness) {
	this->deviousness = deviousness;
	setInvDeviousness(inverse(deviousness));
}

/***************************************************************/
/* Funcion: setInvDeviousness                                  */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              invDeviousness de la clase.                    */
/*                                                             */ 
/* Argumentos: Entrada: float invDeviousness: Indica el inverso*/
/*                                            del valor de     */
/*                                            tortosidad.      */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setInvDeviousness(float invDeviousness) {
	this->invDeviousness = invDeviousness;
}

/***************************************************************/
/* Funcion: setDeviousnessAngle                                */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              deviousnessAngle de la clase.                  */
/*                                                             */ 
/* Argumentos: Entrada: int deviousnessAngle: El giro que puede*/
/*                                            sufrir el arbol. */  
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setDeviousnessAngle(int deviousnessAngle) {
	this->deviousnessAngle = deviousnessAngle;
}

/***************************************************************/
/* Funcion: setDeviousnessArch                                 */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              deviousnessArch de la clase.                   */
/*                                                             */ 
/* Argumentos: Entrada: int deviousnessArch: El giro que puede */
/*                                           sufrir el arbol.  */  
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setDeviousnessArch(int deviousnessArch) {
	this->deviousnessArch = deviousnessArch;
}

/***************************************************************/
/* Funcion: setVariability                                     */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              varibility de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: float variability: Indica un rasgo de  */
/*                                         variabilidad de la  */
/*                                         especie del arbol.  */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setVariability(float variability) {
	this->variability = variability;
}

/***************************************************************/
/* Funcion: setAleator                                         */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              aleator de la clase.                           */
/*                                                             */ 
/* Argumentos: Entrada: Aleator* aleator: El generador de      */
/*                                        numeros aleatorios.  */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setAleator(Aleator* aleator) {
	this->aleator = aleator;
}

/***************************************************************/
/* Funcion: setProbabilityTrunk                                */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              probabilityTrunk de la clase.                  */
/*                                                             */ 
/* Argumentos: Entrada: float probabilityTrunk: La probabilidad*/
/*                                              de continuidad */ 
/*                                              del tronco.    */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setProbabilityTrunk(float probabilityTrunk) {
	this->probabilityTrunk = probabilityTrunk;
}

/***************************************************************/
/* Funcion: setGeneration                                      */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              generation de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: int generation: Las generaciones del   */
/*                                      arbol.                 */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::setGeneration(int generation) {
	this->generation = generation;
}

/***************************************************************/
/* Funcion: meters                                             */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en centimetros a metros.              */
/*                                                             */ 
/* Argumentos: Entrada: float centimeters: Indica el valor en  */
/*                                         centimetros.        */ 
/*                                                             */
/*             Salida: float: El valor de entrada en metros.   */ 
/***************************************************************/
float Parameters::meters(float centimeters) {
	if (centimeters != 0.0) 
		return (float)(centimeters/100.0);
	else
		return (float)0.0;
}

/***************************************************************/
/* Funcion: centimeters                                        */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en metros a centimetros.              */
/*                                                             */ 
/* Argumentos: Entrada: float meters: Indica el valor en metros*/
/*                                                             */
/*             Salida: float: El valor de entrada en           */
/*                            centimetros.                     */ 
/***************************************************************/
float Parameters::centimeters(float meters) {
	return (float)(meters*100.0);
}

/***************************************************************/
/* Funcion: angle                                              */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en radianes a grados.                 */
/*                                                             */ 
/* Argumentos: Entrada: float radian: Indica el valor en       */
/*                                    radianes.                */ 
/*                                                             */
/*             Salida: float: El valor en grados.              */ 
/***************************************************************/
float Parameters::angle(float radian) {
	return (float)((radian*360)/(2*PI));
}

/***************************************************************/
/* Funcion: radian                                             */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en grados a radianes.                 */
/*                                                             */ 
/* Argumentos: Entrada: int angle: Indica el valor en grados.  */
/*                                    radianes.                */ 
/*                                                             */
/*             Salida: float: El valor en radianes.            */ 
/***************************************************************/
float Parameters::radian(int angle) {
	return (float)((angle*2*PI)/360.0);
}

/***************************************************************/
/* Funcion: years                                              */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en meses a años.                      */
/*                                                             */ 
/* Argumentos: Entrada: int months: Indica el valor en meses.  */ 
/*                                                             */
/*             Salida: float: El valor de entrada en años.     */ 
/***************************************************************/
float Parameters::years(int months) {
	if (months != 0)
		return (float)((float)months/12.0);
	else
		return 0;
}

/***************************************************************/
/* Funcion: months                                             */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en años a meses.                      */
/*                                                             */ 
/* Argumentos: Entrada: float years: Indica el valor en años.  */
/*                                                             */
/*             Salida: int: El valor de entrada en meses.      */ 
/***************************************************************/
int Parameters::months(float years) {
	return (int)(years*12);
}

/***************************************************************/
/* Funcion: ratio100                                           */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en el intevalo (0-1) al intervalo     */
/*              (0-100).                                       */ 
/*                                                             */ 
/* Argumentos: Entrada: float ratio1: Indica el valor en el    */
/*                                    intervalo (0-1).         */   
/*                                                             */
/*             Salida: float: El valor de entrada en el        */ 
/*                            intervalo (0-100).               */ 
/***************************************************************/
float Parameters::ratio100(float ratio1) {
	return (float)(ratio1*100.0);
}

/***************************************************************/
/* Funcion: ratio1                                             */
/*															   */
/* Descripcion: Función que se encarga de convertir un valor   */
/*              numerico en el intevalo (0-100) al intervalo   */
/*              (0-1).                                         */ 
/*                                                             */ 
/* Argumentos: Entrada: float ratio100: Indica el valor en el  */
/*                                      intervalo (0-100).     */   
/*                                                             */
/*             Salida: float: El valor de entrada en el        */ 
/*                            intervalo (0-1).                 */ 
/***************************************************************/
float Parameters::ratio1(float ratio100) {
	if (ratio100 != 0.0)
		return (float)(ratio100/100.0);
	else
		return (float)0.0;
}

/***************************************************************/
/* Funcion: inverse                                            */
/*															   */
/* Descripcion: Función que se encarga de invertir un ratio.   */ 
/*                                                             */ 
/* Argumentos: Entrada: float ratio: Indica el valor a invertir*/
/*                                                             */
/*             Salida: float: El valor de entrada invertido.   */ 
/***************************************************************/
float Parameters::inverse(float ratio) {
	return (float)(1.0 - ratio);
}

/***************************************************************/
/* Funcion: calculeHeight                                      */
/*															   */
/* Descripcion: Función que se encarga de calcular la altura   */ 
/*              del arbol.                                     */  
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: float: La altura del arbol (-1.0 si no  */
/*                            puede calcularse).               */ 
/***************************************************************/
float Parameters::calculateHeight() {
	float height;

	if ((getPaceGrowth() == -1.0) | (getMaxHeight() == -1.0) | (getAge() == -1))
		return (float)(-1.0);
	else {
		height = this->years(getAge()) * getPaceGrowth();
		if (height > getMaxHeight())
			return getMaxHeight();
		else
			return height;
	}

	return -1.0;
}

/***************************************************************/
/* Funcion: calculeHeightTrunk                                 */
/*															   */
/* Descripcion: Función que se encarga de calcular la altura   */ 
/*              del tronco del arbol.                          */  
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: float: La altura del tronco (-1.0 si no */
/*                            puede calcularse).               */ 
/***************************************************************/
float Parameters::calculateHeightTrunk() {
	float heightTrunk;

	if ((getHeight() == -1.0) | (getRatioTop() == -1.0))
		return (float)(-1.0);
	else {
		heightTrunk = applyRatio(getHeight(),getRatioTop());
		return heightTrunk;
	}

	return -1.0;
}

/***************************************************************/
/* Funcion: calculeHeightTop                                   */
/*															   */
/* Descripcion: Función que se encarga de calcular la altura   */ 
/*              de la copa del arbol.                          */  
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: float: La altura de la copa (-1.0 si no */
/*                            puede calcularse).               */ 
/***************************************************************/
float Parameters::calculateHeightTop() {
	float heightTop;

	if ((getHeight() == -1.0) | (getRatioTop() == -1.0))
		return (float)(-1.0);
	else {
		heightTop = applyRatio(getHeight(),inverse(getRatioTop()));
		return heightTop;
	}

	return -1.0;
}

/***************************************************************/
/* Funcion: calculeDiameterBase                                */
/*															   */
/* Descripcion: Función que se encarga de calcular el diametro */ 
/*              de la base del arbol.                          */  
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: float: El diametro de la base (-1.0 si  */
/*                            no puede calcularse).            */ 
/***************************************************************/
float Parameters::calculateDiameterBase() {
	float diameterBase;

	if ((getHeight() == -1.0) | (getRatioBase() == -1.0))
		return (float)(-1.0);
	else {
		diameterBase = applyRatio(getHeight(),getRatioBase());
		return diameterBase;
	}

	return -1.0;
}

/***************************************************************/
/* Funcion: applyRatio                                         */
/*															   */
/* Descripcion: Función que se encarga de aplicar un ratio a   */ 
/*              un valor.                                      */  
/*                                                             */ 
/* Argumentos: Entrada: float value: El valor donde se aplica  */
/*                                   el ratio.                 */
/*                      float ratio: El ratio a aplicar, en el */
/*                                   intervalo (0-1).          */    
/*                                                             */
/*             Salida: float: El valor calculado.              */ 
/***************************************************************/
float Parameters::applyRatio(float value, float ratio) {
	return value*ratio;
}

/***************************************************************/
/* Funcion: applyRatio                                         */
/*															   */
/* Descripcion: Función sobrecargada para aceptar enteros.     */  
/*                                                             */ 
/* Argumentos: Entrada: int value: El valor donde se aplica el */
/*                                 ratio.                      */
/*                      float ratio: El ratio a aplicar, en el */
/*                                   intervalo (0-1).          */    
/*                                                             */
/*             Salida: float: El valor calculado.              */ 
/***************************************************************/
float Parameters::applyRatio(int value, float ratio) {
	return value*ratio;
}

/***************************************************************/
/* Funcion: subdivide                                          */
/*															   */
/* Descripcion: Función que calcula la cantidad de partes      */  
/*              obtenidas mediante un ratio.                   */ 
/*                                                             */ 
/* Argumentos: Entrada: float ratio: El ratio a aplicar, en el */
/*                                   intervalo (0-100).        */    
/*                                                             */
/*             Salida: float: El valor calculado.              */ 
/***************************************************************/
int Parameters::subdivide(float ratio) {
	float result = -1.0;
	float difference = -1.0;

	result = (float)(ratio/100.0);
	difference = result - (int)(result);
	if (difference > 0.5) 
		return (int)(result + 1);
	else
		return (int)result;
}

/***************************************************************/
/* Funcion: complete                                           */
/*															   */
/* Descripcion: Función que indica si la clase tiene todos lo  */
/*              parametros necesarios.                         */ 
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada                            */
/*                                                             */
/*             Salida: int: 0 si esta completo y 1 si no.      */ 
/***************************************************************/
int Parameters::complete() {
	if (getMaxHeight() == -1.0) {
		return 1;
	}
	else if (getMaxHeight() == -1.0) {
		return 1;
	}
	else if (getPaceGrowth() == -1.0) {
		return 1;
	}
	else if (getAge() == -1.0) {
		return 1;
	}
	else if (getDeviousness() == -1.0) {
		return 1;
	}
	else if (getFrondage() == -1.0) {
		return 1;
	}
	else if (getMaxAngle() == -1) {
		return 1;
	}
	else if (getDeviousnessAngle() == -1) {
		return 1;
	}
	else if (getTreeCone() == -1) {
		return 1;
	}
	else if (getVarTreeCone() == -1) {
		return 1;
	}
	else if (getMinAngle() == -1) {
		return 1;
	}
	else if (getRatioBase() == -1.0) {
		return 1;
	}
	else if (getRatioBranch() == -1.0) {
		return 1;
	}
	else if (getRatioTop() == -1.0) {
		return 1;
	}
	else if (getRatioDiameter2() == -1.0) {
		return 1;
	}
	else if (getRatioTrunk() == -1.0) {
		return 1;
	}
	else if (getVariability() == -1.0) {
		return 1;
	}
	else if (getProbabilityTrunk() == -1.0) {
		return 1;
	}
	else if (getGeneration() == -1.0) {
		return 1;
	}
	
	return 0;
}

/***************************************************************/
/* Funcion: change                                             */
/*															   */
/* Descripcion: Función que varia los parametros calculados del*/
/*              arbol si es necesario.                         */ 
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada                            */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Parameters::change() {
	Aleator* alea = NULL;
	float vari = 0.0;
	int aleat1 = 0, aleat2 = 0;

	// Aplicamos la variabilidad a los parametros calculados
	alea = getAleator();

	vari = getVariability()*100;
	alea->setMin(0);
	alea->setMax(100);
	alea->setRandomize(0);

	// Puede modificarse la altura
	aleat1 = alea->alea();
	if (aleat1 <= vari) {
		aleat2 = alea->alea();
		// Incremento positivo
		if (aleat2 <= 50) {
			setHeight(getHeight() + (float)(getHeight() * (aleat1/100.0)));
		}
		// Incremento negativo
		else {
			setHeight(getHeight() - (float)(getHeight() * (aleat1/100.0)));
		}
	}

	// Puede modificarse la altura del tronco
	aleat1 = alea->alea();
	if (aleat1 <= vari) {
		aleat2 = alea->alea();
		// Incremento positivo
		if (aleat2 <= 50) {
			setHeightTrunk(getHeightTrunk() + (float)(getHeightTrunk() * (aleat1/100.0)));
			setHeightTop(getHeight() - getHeightTrunk());
		}
		// Incremento negativo
		else {
			setHeightTrunk(getHeightTrunk() - (float)(getHeightTrunk() * (aleat1/100.0)));
			setHeightTop(getHeight() - getHeightTrunk());
		}
	}
	
	// Puede modificarse la altura de la copa
	aleat1 = alea->alea();
	if (aleat1 <= vari) {
		aleat2 = alea->alea();
		// Incremento positivo
		if (aleat2 <= 50) {
			setHeightTop(getHeightTop() + (float)(getHeightTop() * (aleat1/100.0)));
			setHeightTrunk(getHeight() - getHeightTop());
		}
		// Incremento negativo
		else {
			setHeightTop(getHeightTop() - (float)(getHeightTop() * (aleat1/100.0)));
			setHeightTrunk(getHeight() - getHeightTop());
		}
	}

	// Puede modificarse el diametro de la base
	aleat1 = alea->alea();
	if (aleat1 <= vari) {
		aleat2 = alea->alea();
		// Incremento positivo
		if (aleat2 <= 50) {
			setDiameterBase(getDiameterBase() + (float)(getDiameterBase() * (aleat1/100.0)));
		}
		// Incremento negativo
		else {
			setDiameterBase(getDiameterBase() - (float)(getDiameterBase() * (aleat1/100.0)));
		}
	}
}