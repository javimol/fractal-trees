/*******************************************************/
/* Fichero: Tree.cpp                 Fecha: 02-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementacion de la clase  */
/*              tree.                                  */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "Tree.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Utilizado para contar el numero de ramas generadas
int global = 0;
int tramo = 0;
long idum = (-1 * time(NULL));
FILE* fer = NULL;
int indice = 0;

/***************************************************************/
/* Funcion: Constructor por defecto                            */
/*															   */
/* Descripcion: Función que inicializa los valores de la clase */
/***************************************************************/
Tree::Tree() {
	float** matriz;
	int i = 0;

	setType(-1);
	setParameters(NULL);
	setStructure(NULL);
	matriz = (float**)malloc(4*sizeof(float*));
	for(i = 0; i < 4; i++)
		matriz[i] = (float*)malloc(4*sizeof(float));
	setMatriz(matriz);

}

/***************************************************************/
/* Funcion: Destructor                                         */
/*															   */
/* Descripcion: Función que eliminar los valores de la clase   */
/***************************************************************/
Tree::~Tree() {
	int i = 0;

	if (getParameters() != NULL) {
		delete getParameters();
		setParameters(NULL);
	}
	if (getStructure() != NULL) {
		delete getStructure();
		setStructure(NULL);
	}
	if (getMatriz() != NULL) {
		for(i = 0; i < 4; i++) {
			if (getMatriz()[i] != NULL) {
				free(getMatriz()[i]);
				getMatriz()[i] = NULL;
			}
		}
		free(getMatriz());
		setMatriz(NULL);
	}
}

/***************************************************************/
/* Funcion: getType                                            */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              type de la clase.                              */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: int: El tipo de arbol.                  */ 
/***************************************************************/
int Tree::getType() {
	return this->type;
}

/***************************************************************/
/* Funcion: getParameters                                      */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              parameters de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Parameters*: Los parametros del arbol.  */ 
/***************************************************************/
Parameters* Tree::getParameters() {
	return this->parameters;
}

/***************************************************************/
/* Funcion: getStructure                                       */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              structure de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: Structure*: La estructura del arbol.    */ 
/***************************************************************/
Structure* Tree::getStructure() {
	return this->structure;
}

/***************************************************************/
/* Funcion: getMatriz                                          */
/*															   */
/* Descripcion: Función que obtiene el valor del atributo      */
/*              matriz de la clase.                            */
/*                                                             */ 
/* Argumentos: Entrada: void.                                  */
/*                                                             */
/*             Salida: float**: La matriz del arbol.           */ 
/***************************************************************/
float** Tree::getMatriz() {
	return this->matriz;
}

/***************************************************************/
/* Funcion: setType                                            */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              type de la clase.                              */
/*                                                             */ 
/* Argumentos: Entrada: int type: El tipo del arbol.           */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::setType(int type) {
	this->type = type;
}

/***************************************************************/
/* Funcion: setParameters                                      */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              parameters de la clase.                        */
/*                                                             */ 
/* Argumentos: Entrada: Parameters* parameters: Los parametros */
/*                                              del arbol.     */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::setParameters(Parameters* parameters) {
	this->parameters = parameters;
}

/***************************************************************/
/* Funcion: setStructure                                       */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              structure de la clase.                         */
/*                                                             */ 
/* Argumentos: Entrada: Structure* structure: La estructura del*/
/*                                            arbol.           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::setStructure(Structure* structure) {
	this->structure = structure;
}

/***************************************************************/
/* Funcion: setMatriz                                          */
/*															   */
/* Descripcion: Función que establece el valor del atributo    */
/*              matriz de la clase.                            */
/*                                                             */ 
/* Argumentos: Entrada: float** matriz: La matriz del arbol.   */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::setMatriz(float** matriz) {
	this->matriz = matriz;
}

/***************************************************************/
/* Funcion: generate                                           */
/*															   */
/* Descripcion: Función que genera la estructura del arbol.    */
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::generate() {
	int flag = 0, cant = 0, aleat = 0;
	int i = 0, j  = 0;
	Structure** lives = NULL;
	Structure* initial = NULL;

	// Creamos el primer tronco
	this->initial();
	initial = this->getStructure();

	// Mientras queden vivos, o no llegen a todas las generacion
	while (flag == 0) {
		cant = 0;

		// Actualizamos los estados de las estructuras
		this->update(initial);
		
		// Elegimos todos los que pueden generar sucesores y/o ramas
		lives = this->searchLives(initial,lives,&cant);
		if (cant == 0) 
			flag = 1;

		// Los generamos
		this->exploit(lives,cant);

		// Eliminamos el array de vivos
		free(lives);
		lives = NULL;
	}

	// Eliminamos todas las partes sin padre y sin ramas
	clear(initial);
}

/***************************************************************/
/* Funcion: initial                                            */
/*															   */
/* Descripcion: Función que genera la estructura inicial del   */
/*              arbol.                                         */
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */ 
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::initial() {
	Structure* initial = NULL;
	Point* pInit = NULL, *pEnd = NULL;
	int aleat1 = 0, aleat2 = 0, aleat3 = 0;
	float aleatG = 0.0, alfa = 0.0, gamma = 0.0;
	float x = 0.0, y = 0.0, z = 0.0;
	int alfa2 = 0, gamma2 = 0;

	pInit = new Point();
	pEnd = new Point();

	initial = new Structure();
	// Punto inicial (0,0,0)
	pInit->setX(0);
	pInit->setY(0);
	pInit->setZ(0);
	initial->setInitialPoint(pInit);

	// Diametro inicial (diametro de la base)
	aleatG = this->randGauss(&idum);
	initial->setInitialDiameter((this->getParameters())->getDiameterBase());
	initial->setInitialDiameter(initial->getInitialDiameter() + (initial->getInitialDiameter() * aleatG));
	aleatG = this->randGauss(&idum);
	initial->setFinalDiameter((this->getParameters())->getDiameterBase() - ((this->getParameters())->getDiameterBase() * (this->getParameters())->getRatioDiameter2()));
	initial->setFinalDiameter(initial->getFinalDiameter() + (initial->getFinalDiameter() * aleatG));
		
	// Angulos alfa y gamma (pueden ser aleatorios)
	aleat1 = (this->getParameters())->getAleator()->alea();
	aleat2 = (this->getParameters())->getAleator()->alea();
	aleat3 = (this->getParameters())->getAleator()->alea();
	if (aleat1 <= ((this->getParameters())->getVariability() * 100.0)) {
		// obtenemos un aleatorio
		alfa = (float)(aleat2 * (aleat1 / 100.0));
		// pasamos de 0 a 100 <-> 0 a 360;
		alfa = (float)(alfa * 3.6);
		alfa2 = (int)alfa;
		// pasamos a radianes
		initial->setAlfa((this->getParameters())->radian(alfa2));
		// obtenemos un aleatorio
		gamma = (float)(aleat3 * (aleat1 / 100.0));
		// pasamos de 0 a 100 <-> 0 a 67.5;
		gamma = (float)(gamma * 0.675);
		gamma2 = (int)gamma;
		// pasamos a radianes
		initial->setAlfa((this->getParameters())->radian(alfa2));
		initial->setGamma((this->getParameters())->radian(gamma2));
	}
	else {
		initial->setAlfa(0);
		initial->setGamma(0);
	}
	aleatG = this->randGauss(&idum);
	initial->setAlfa(initial->getAlfa() + (initial->getAlfa() * aleatG));
	aleatG = this->randGauss(&idum);
	initial->setGamma(initial->getGamma() + (initial->getGamma() * aleatG));

	// longitud el tronco
	initial->setHigh((this->getParameters())->getHeightTrunk());
	aleatG = this->randGauss(&idum);
	initial->setHigh(initial->getHigh() + (initial->getHigh() * aleatG));

	// Calculamos el punto final
	x = (float)((initial->getHigh() * sin(initial->getGamma())) * (sin(initial->getAlfa())));
	y = (float)(initial->getHigh() * cos(initial->getGamma()));
	z = (float)((initial->getHigh() * sin(initial->getGamma())) * cos(initial->getAlfa()));
	pEnd->setX((initial->getInitialPoint())->getX() + x);
	pEnd->setY((initial->getInitialPoint())->getY() + y);
	pEnd->setZ((initial->getInitialPoint())->getZ() + z);
	initial->setFinalPoint(pEnd);

	// Indicamos que esta vivo
	initial->born();

	// Indicamos que es la primera generacion
	initial->setGeneration(0);
	initial->setOld(0);

	// Miramos si es tortuoso
	aleat1 = ((this->getParameters())->getAleator())->alea();
	if (aleat1 < ((this->getParameters())->getDeviousness()*100.0)) {
		initial->setDeviousness(this->initialDeviousness(initial));
		initial->setCDeviousness(1);
	}
	else
		global++;

	// Asignamos el segmento del arbol
	this->setStructure(initial);
}

/***************************************************************/
/* Funcion: initialdeviousness                                 */
/*															   */
/* Descripcion: Función que genera la estructura inicial del   */
/*              arbol con tortuosidad.                         */
/*                                                             */ 
/* Argumentos: Entrada: Structure* initiaL: El tramo implicado.*/ 
/*                                                             */
/*             Salida: Structure*: La descomposicion en pedazos*/ 
/***************************************************************/
Structure* Tree::initialDeviousness(Structure* initial) {
	Structure *result = NULL, *aux = NULL, *temp = NULL;
	Point* pInit = NULL, *pEnd = NULL;
	float diameterIni = 0.0, diameterEnd = 0.0, diameterIncr = 0.0;
	float alfa = 0.0, gamma = 0.0, aleatG = 0.0;
	float x = 0.0, y = 0.0, z = 0.0;
	float high = 0.0, subdivision = 0.0;
	int i = 0, j = 0, flag = 0, high2 = 0;
	int sub = 0, aleat1 = 0, aleat2 = 0, aux2 = 0;
	int* aleats = NULL;

	// Empezamos calculando los valores basicos
	pInit = new Point();
	pEnd = new Point();

	result = new Structure();
	// Punto inicial (0,0,0)
	pInit->setX((initial->getInitialPoint())->getX());
	pInit->setY((initial->getInitialPoint())->getY());
	pInit->setZ((initial->getInitialPoint())->getZ());

	// Diametro inicial (diametro de la base)
	diameterIni = initial->getInitialDiameter();
	diameterEnd = initial->getFinalDiameter();
		
	// Los angulos alfa y gamma
	alfa = initial->getAlfa();
	gamma = initial->getGamma();

	// longitud el tronco
	high = initial->getHigh();
	
	// Calculamos la variacion de diametro
	diameterIncr = (diameterEnd - diameterIni) / high;

	// Iniciamos el la subdivision en diferentes tramos
	// Calculamos el numero de subdivisiones
	subdivision = (float)1.0/(this->getParameters())->getInvDeviousness();
	if ((subdivision - (int)subdivision) < 0.5)
		sub = (int)subdivision;
	else
		sub = ((int)subdivision) + 1;

	aleats = (int*)malloc(sizeof(int)*(sub+1));
	for(i = 0; i < sub; i++) {
		aleats[i] = ((this->getParameters())->getAleator())->alea();
		if (aleats[i] == 100)
			aleats[i] = 99;
		if (aleats[i] == 0)
			aleats[i] = 1;
		for(j = 0; j > i; j++)
			if (aleats[j] == aleats[i]) {
				i--;
				break;
			}
	}
	aleats[sub] = 100;

	// Colocamos los aleatorios de menor a mayor
	i=sub+1;
	flag = 1;

	while ((flag==1) & (i>=1)){
		flag=0;
		for (j = 0; j < i-1; j++){
			if (aleats[j] > aleats[j+1]){
				aux2 = aleats[j];
				aleats[j] = aleats[j+1];
				aleats[j+1] = aux2;
				flag = 1;
			}
		}
		i--;
	}

	// Generamos el primer tramo y lo asignamos a las estructura
	result->setInitialPoint(pInit);
	result->setInitialDiameter(diameterIni);
	result->setAlfa(alfa);
	result->setGamma(gamma);
	result->setHigh(((float)(aleats[0]/100.0))*high);
	// Calculamos el punto final
	x = (float)((result->getHigh() * sin(result->getGamma())) * (sin(result->getAlfa())));
	y = (float)(result->getHigh() * cos(result->getGamma()));
	z = (float)((result->getHigh() * sin(result->getGamma())) * cos(result->getAlfa()));
	pEnd->setX((result->getInitialPoint())->getX() + x);
	pEnd->setY((result->getInitialPoint())->getY() + y);
	pEnd->setZ((result->getInitialPoint())->getZ() + z);
	result->setFinalPoint(pEnd);
	// Calculamos el diametro final
	diameterIni = diameterIni + (diameterIncr * result->getHigh());
	result->setFinalDiameter(diameterIni);
	// Indicamos que esta muerte
	result->dead();
	// Asi como su generacion y antiguedad
	result->setGeneration(0);
	result->setOld(0);
	result->setNumberBranch(0);

	// usamos un auxiliar
	aux = result;
	
	// Empezamos el calculo recursivo de los tramos
	for(i = 1; i < (sub+1); i++) {
		// Recalculamos lo necesario
		pInit = new Point();
		temp = new Structure();
		// Calculamos la longitud del nuevo tramo
		high = (((float)((aleats[i] - aleats[i-1])/100.0))*initial->getHigh());
		// Punto inicial del tramo es el punto final del anterior
		pInit->setX(pEnd->getX());
		pInit->setY(pEnd->getY());
		pInit->setZ(pEnd->getZ());

		// Obtenemos el nuevo alfa y gamma
		aleat1 = ((this->getParameters())->getAleator())->alea();
		aleat2 = ((this->getParameters())->getAleator())->alea();
		// Un gamma aleatorio (maximo el de tortuosidad indicado)
		gamma = (aleat1*((this->getParameters())->radian((this->getParameters())->getDeviousnessAngle())/((float)100.0)));
		// El alfa puede variar de -45 a 45 grados
		alfa = (float)((this->getParameters())->radian(this->getParameters()->getDeviousnessArch()) * (aleat2/100.0));
		alfa = (float)(alfa - ((this->getParameters())->radian(this->getParameters()->getDeviousnessArch()) / 2.0));
		alfa = (aux->getAlfa()) + alfa;
		// Calculamos el punto final
		x = (float)((high * sin(gamma)) * sin(alfa));
		y = (float)(high * cos(gamma));
		z = (float)((high * sin(gamma)) * cos(alfa));
		// El punto final
		pEnd = new Point();
		pEnd->setX(pInit->getX() + x);
		pEnd->setY(pInit->getY() + y);
		pEnd->setZ(pInit->getZ() + z);
		// Asignamos valores
		temp->setInitialPoint(pInit);
		temp->setFinalPoint(pEnd);
		temp->setInitialDiameter(diameterIni);
		temp->setHigh(high);
		temp->setAlfa(alfa);
		temp->setGamma(gamma);
		diameterIni = diameterIni + (diameterIncr * high);
		temp->setFinalDiameter(diameterIni);
		temp->dead();
		temp->setGeneration(0);
		temp->setOld(0);
		temp->setNumberBranch(0);
		// Indicamos la estructura del tramo
		aux->setChildren(temp);
		temp->setFather(aux);
		// Colocamos punteros de nuevo
		aux = aux->getChildren();
	}
	free(aleats);

	global += sub;

	return result;
}

/***************************************************************/
/* Funcion: update                                             */
/*															   */
/* Descripcion: Función que actualiza la estructura del arbol. */
/*                                                             */ 
/* Argumentos: Entrada: Structure* initial: El inicio del arbol*/
/*                                                             */
/*             Salida: int: Indica si se debe terminar de      */
/*                          generar el arbol.                  */ 
/***************************************************************/
int Tree::update(Structure* initial) {
	Structure* aux = NULL;
	int i = 0;

	if (initial->getChildren() != NULL) {
		aux = initial->getChildren();
		this->update(aux);
	}
	if (initial->getNumberBranch() != 0) {
		for (i = 0; i < initial->getNumberBranch(); i++) {
			aux = initial->getBranches()[i];
			this->update(aux);
		}
	}

	if (initial->getState() == 1) {
		initial->dead();
	}
	if (initial->getState() == 0) {
		initial->life();
	}

	return 0;
}

/***************************************************************/
/* Funcion: clear                                              */
/*															   */
/* Descripcion: Función que limpia el arbol.                   */
/*                                                             */ 
/* Argumentos: Entrada: Structure* initial: El inicio del arbol*/
/*                                                             */
/*             Salida: void.                                   */ 
/***************************************************************/
void Tree::clear(Structure* initial) {
	Structure* aux = NULL;
	int i = 0, flag = 0;
	float max = 0.0;
	
	if (initial->getChildren() != NULL) {
		aux = initial->getChildren();
		this->clear(aux);
	}
	if ((initial->getNumberBranch() != 0) & (initial->getNumberBranch() != -1)) {
		for (i = 0; i < initial->getNumberBranch(); i++) {
			aux = initial->getBranches()[i];
			this->clear(aux);
		}
	}

	// Si no tiene ramas y es de primera generacion
	if ((initial->getNumberBranch() == -1) &
		(initial->getGeneration() == 0)) {
		if (initial->getFather() != NULL) {
			if ((initial->getFather()->getNumberBranch() != -1) & (initial->getFather()->getNumberBranch() != 0))
				initial->getFather()->setFinalDiameter(initial->getFather()->getBranches()[0]->getInitialDiameter());
			initial->getFather()->setChildren(NULL);
			delete initial;
			initial = NULL;
			global--;
		}
	}

	// Si tenemos un tramo sin sucesor y con ramas, reducimos su diametro final al maximo del de sus hijos
	if ((initial->getChildren() == NULL) & (initial->getNumberBranch() > 0)) {
		if (initial->getCDeviousness() == 1) {
			aux = initial->getDeviousness();
			while(aux->getChildren() != NULL)
				aux = aux->getChildren();
			for(i = 0; i < initial->getNumberBranch(); i++) {
				flag = 0;
				if ((aux->getFinalPoint())->getX() != ((initial->getBranches())[i]->getInitialPoint())->getX())
					flag = 1;
				if ((aux->getFinalPoint())->getY() != ((initial->getBranches())[i]->getInitialPoint())->getY())
					flag = 1;
				if ((aux->getFinalPoint())->getZ() != ((initial->getBranches())[i]->getInitialPoint())->getZ())
					flag = 1;
				if (flag == 0) {
					if (max < (initial->getBranches())[i]->getInitialDiameter())
						max = (initial->getBranches())[i]->getInitialDiameter();
				}
			}
			initial->setFinalDiameter(max);
			aux->setFinalDiameter(max);
		}
		else {
			for(i = 0; i < initial->getNumberBranch(); i++) {
				flag = 0;
				if ((initial->getFinalPoint())->getX() != ((initial->getBranches())[i]->getInitialPoint())->getX())
					flag = 1;
				if ((initial->getFinalPoint())->getY() != ((initial->getBranches())[i]->getInitialPoint())->getY())
					flag = 1;
				if ((initial->getFinalPoint())->getZ() != ((initial->getBranches())[i]->getInitialPoint())->getZ())
					flag = 1;
				if (flag == 0) {
					if (max < (initial->getBranches())[i]->getInitialDiameter())
						max = (initial->getBranches())[i]->getInitialDiameter();
				}
			}
			initial->setFinalDiameter(max);
		}
	}

	return;
}

/***************************************************************/
/* Funcion: searchLives                                        */
/*															   */
/* Descripcion: Función que busca los nodos vivos en el arbol. */
/*                                                             */ 
/* Argumentos: Entrada: Structure* initial: El inicio del arbol*/ 
/*                      Structure** lives: La lista de vivos.  */
/*                      int* cant: El número de tramos vivos.  */
/*                                                             */
/*             Salida: Structure**: La lista de vivos.         */ 
/***************************************************************/
Structure** Tree::searchLives(Structure* initial, Structure** lives, int *cant) {
	Structure** aux = NULL;
	Structure* aux2 = NULL;
	int i = 0;
	
	if (initial->getChildren() != NULL) {
		aux2 = initial->getChildren();
		lives = this->searchLives(aux2, lives, cant);
	}
	if (initial->getNumberBranch() != -1) {
		for (i = 0; i < initial->getNumberBranch(); i++) {
			aux2 = initial->getBranches()[i];
			lives = this->searchLives(aux2,lives, cant);
		}
	}
	if (initial->getState() == 1) {
		// Creamos un puntero con una posicion adicional
		aux = (Structure**)malloc(((*cant)+1)*sizeof(Structure*));
		// Copiamos las direcciones anteriores
		for(i = 0; i < (*cant); i++) {
			aux[i] = lives[i];
		}
		free(lives);
		lives = NULL;
		// añades el nuevo vivo
		aux[(*cant)] = initial;
		// lo mantiene para la recursion
		lives = aux;
		*cant = *cant + 1;
		return lives;
	}
	return lives;
}

/***************************************************************/
/* Funcion: exploit                                            */
/*															   */
/* Descripcion: Función que produce el crecimiento del arbol.  */
/*                                                             */ 
/* Argumentos: Entrada: Structure** lives: Los tramos vivos.   */ 
/*                      int cant: El número de tramos vivos.   */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::exploit(Structure** lives, int cant) {
	Structure* current = NULL;
	int i = 0, j = 0;
	int aleat1 = 0, aleat2 = 0;

	// Recoremos cada uno de los tramos
	for(i = 0; i < cant; i++) {
		current = lives[i];

		// Generamos la continuacion
		this->generateChildren(current);

		// Generamos las ramas
		this->generateBranch(current);
	}
}

/***************************************************************/
/* Funcion: generateChildren                                   */
/*															   */
/* Descripcion: Función que genera el sucesor de un tramo del  */
/*              del arbol.                                     */  
/*                                                             */ 
/* Argumentos: Entrada: Structure* current: El tramo implicado */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::generateChildren(Structure* current) {
	Structure* initial = NULL, *children = NULL, *temp = NULL;
	Point* pIni = NULL, *pEnd = NULL;
	int aleat1 = -1, aleat2 = -1;
	float x = 0.0, y = 0.0, z = 0.0, modulo = 0.0;
	float aleatG = 0.0;
	int generation = 0;

	if (current->getOld() >= ((this->getParameters())->getGeneration()))
		return;

	// Si da el caso de no poder continuar el tronco
	aleat1 = ((this->getParameters())->getAleator())->alea();
	if (aleat1 < (this->getParameters())->getProbabilityTrunk() * 100) {
		// Retornamos sin generar sucesor
		return;
	}

	initial = current;
	// Si estaba dividido entramos cogemos dichos tramos como referente en
	// angulos, puntos iniciales, etc..
	if (current->getCDeviousness() == 1) {
		current = current->getDeviousness();
		while (current->getChildren() != NULL)
			current = current->getChildren();
	}

	children = new Structure();
	pIni = new Point();
	pEnd = new Point();

	// Indicamos el punto inicial
	pIni->setX(current->getFinalPoint()->getX());
	pIni->setY(current->getFinalPoint()->getY());
	pIni->setZ(current->getFinalPoint()->getZ());
	children->setInitialPoint(pIni);

	// Indicamos el diametro inicial
	children->setInitialDiameter(initial->getFinalDiameter());

	// Asignamos el alfa
	children->setAlfa(current->getAlfa());
	aleat1 = ((this->getParameters())->getAleator())->alea();
	aleat2 = ((this->getParameters())->getAleator())->alea();
	if (aleat1 < (this->getParameters())->getVariability() * 100) {
		if (aleat2 < 50) {
			children->setAlfa(children->getAlfa() - (children->getAlfa() * ((float)(aleat1/100.0))));
		}
		else {
			children->setAlfa(children->getAlfa() + (children->getAlfa() * ((float)(aleat1/100.0))));
		}
	}
	aleatG = this->randGauss(&idum);
	children->setAlfa(children->getAlfa() + (children->getAlfa() * aleatG));

	// Asignamos el gamma
	children->setGamma(current->getGamma());
	aleat1 = ((this->getParameters())->getAleator())->alea();
	aleat2 = ((this->getParameters())->getAleator())->alea();
	if (aleat1 < (this->getParameters())->getVariability() * 100) {
		if (aleat2 < 50) {
			children->setGamma(children->getGamma() - (children->getGamma() * ((float)(aleat1/100.0))));
		}
		else {
			children->setGamma(children->getGamma() + (children->getGamma() * ((float)(aleat1/100.0))));
		}
	}
	aleatG = this->randGauss(&idum);
	children->setGamma(children->getGamma() + (children->getGamma() * aleatG));

	// Indicamos su generacion
	children->setGeneration(initial->getGeneration());
	children->setOld(initial->getOld()+1);

	// La altura del nuevo tramo es igual al ratio entre niveles de ramajes
	children->setHigh(initial->getHigh() * (this->getParameters())->getRatioBranch());
	aleat1 = ((this->getParameters())->getAleator())->alea();
	aleat2 = ((this->getParameters())->getAleator())->alea();
	if (aleat1 < (this->getParameters())->getVariability() * 100) {
		if (aleat2 < 50) {
			children->setHigh(children->getHigh() - (children->getHigh() * (float)(aleat1/100.0)));
		}
		else {
			children->setHigh(children->getHigh() + (children->getHigh() * (float)(aleat1/100.0)));
		}
	}
	aleatG = this->randGauss(&idum);
	children->setHigh(children->getHigh() + (children->getHigh() * aleatG));

	// Calculamos el diametro final del tramo
	children->setFinalDiameter(children->getInitialDiameter() - (children->getInitialDiameter() * (this->getParameters())->getRatioDiameter2()));
	aleat1 = ((this->getParameters())->getAleator())->alea();
	if (aleat1 < ((this->getParameters())->getVariability() * 100)) {
		aleat2 = ((this->getParameters())->getAleator())->alea();
		if (aleat2 < 50) 
			children->setFinalDiameter(children->getFinalDiameter() - (children->getFinalDiameter() * ((float)(aleat1/100.0))));
		else
			children->setFinalDiameter(children->getFinalDiameter() + (children->getFinalDiameter() * ((float)(aleat1/100.0))));
	}
	aleatG = this->randGauss(&idum);
	children->setFinalDiameter(children->getFinalDiameter() + (children->getFinalDiameter() * aleatG));

	// Calculamos el punto final
	x = (float)((children->getHigh() * sin(children->getGamma())) * (sin(children->getAlfa())));
	y = (float)(children->getHigh() * cos(children->getGamma()));
	z = (float)((children->getHigh() * sin(children->getGamma())) * cos(children->getAlfa()));
	pEnd->setX((children->getInitialPoint())->getX() + x);
	pEnd->setY((children->getInitialPoint())->getY() + y);
	pEnd->setZ((children->getInitialPoint())->getZ() + z);
	children->setFinalPoint(pEnd);

	// Indicamos que tiene como padre a current
	children->setFather(initial);
	// Indicamos que ha nacido el tramo
	children->born();

	// Si es parte del tronco principal
	if (children->getGeneration() == 0) {
		// Si tiene un Z superior a la altura del arbol
		if ((children->getFinalPoint())->getY() > (this->getParameters())->getHeight()) {
			// Indicamos que muere
			children->dead();
		}
	}

	aleat1 = ((this->getParameters())->getAleator())->alea();
	if (aleat1 < ((this->getParameters())->getDeviousness() * 100.0)) {
		children->setDeviousness(this->generateDeviousness(children));
		children->setCDeviousness(1);
	}
	else {
		global++;
	}

	// Indicamos que lo creado es el hijo de current
	initial->setChildren(children);
}

/***************************************************************/
/* Funcion: generateDeviosness                                 */
/*															   */
/* Descripcion: Función que genera el sucesor de un tramo del  */
/*              del arbol con tortuosidad.                     */  
/*                                                             */ 
/* Argumentos: Entrada: Structure* current: El tramo implicado */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
Structure* Tree::generateDeviousness(Structure* current) {
	Structure* children = NULL, *aux = NULL, *temp = NULL;
	Point* pIni = NULL, *pEnd = NULL;
	int aleat1 = -1, aleat2 = -1;
	int generation = 0, sub = 0;
	int* aleats = NULL;
	int i = 0, j = 0, flag = 0, aux2 = 0;
	float x = 0.0, y = 0.0, z = 0.0, modulo = 0.0, highT = 0.0;
	float diameterIni = 0.0, diameterEnd = 0.0, diameterIncr = 0.0;
	float alfa = 0.0, gamma = 0.0, high = 0.0, subdivision = 0.0;
	float aleatG = 0.0;

	children = new Structure();
	pIni = new Point();
	pEnd = new Point();

	// Indicamos el punto inicial
	pIni->setX(current->getInitialPoint()->getX());
	pIni->setY(current->getInitialPoint()->getY());
	pIni->setZ(current->getInitialPoint()->getZ());

	// Indicamos el diametro inicial
	diameterIni = current->getInitialDiameter();
		
	// Asignamos el alfa
	alfa = current->getAlfa();
	aleatG = this->randGauss(&idum);
	alfa = alfa + (alfa * aleatG);
	
	// Asignamos el gamma
	gamma = current->getGamma();
	aleatG = this->randGauss(&idum);
	gamma = gamma + (gamma * aleatG);
	
	// La altura 
	highT = current->getHigh();

	// Calculamos el diametro final del tramo
	diameterEnd = current->getFinalDiameter();

	// Calculamos la variacion de diametro
	diameterIncr = (diameterEnd - diameterIni) / highT;

	// Iniciamos el la subdivision en diferentes tramos
	// Calculamos el numero de subdivisiones
	subdivision = (float)1.0/(this->getParameters())->getInvDeviousness();
	if ((subdivision - (int)subdivision) < 0.5)
		sub = (int)subdivision;
	else
		sub = ((int)subdivision) + 1;

	aleats = (int*)malloc(sizeof(int)*(sub+1));
	for(i = 0; i < sub; i++) {
		aleats[i] = ((this->getParameters())->getAleator())->alea();
		if (aleats[i] == 100)
			aleats[i] = 99;
		if (aleats[i] == 0)
			aleats[i] = 1;
		for(j = 0; j > i; j++)
			if (aleats[j] == aleats[i]) {
				i--;
				break;
			}
	}
	aleats[sub] = 100;

	// Colocamos los aleatorios de menor a mayor
	i=sub+1;
	flag = 1;

	while ((flag==1) & (i>=1)){
		flag=0;
		for (j = 0; j < i-1; j++){
			if (aleats[j] > aleats[j+1]){
				aux2 = aleats[j];
				aleats[j] = aleats[j+1];
				aleats[j+1] = aux2;
				flag = 1;
			}
		}
		i--;
	}

	// Generamos el primer tramo y lo asignamos a las estructura
	children->setInitialPoint(pIni);
	children->setInitialDiameter(diameterIni);
	children->setAlfa(alfa);
	children->setGamma(gamma);
	children->setHigh(((float)(aleats[0]/100.0))*highT);
	// Calculamos el punto final
	x = (float)((children->getHigh() * sin(children->getGamma())) * (sin(children->getAlfa())));
	y = (float)(children->getHigh() * cos(children->getGamma()));
	z = (float)((children->getHigh() * sin(children->getGamma())) * cos(children->getAlfa()));
	pEnd->setX((children->getInitialPoint())->getX() + x);
	pEnd->setY((children->getInitialPoint())->getY() + y);
	pEnd->setZ((children->getInitialPoint())->getZ() + z);
	children->setFinalPoint(pEnd);
	// Calculamos el diametro final
	diameterIni = diameterIni + (diameterIncr * children->getHigh());
	children->setFinalDiameter(diameterIni);
	// Indicamos que esta muerte
	children->dead();
	// Asi como su generacion y antiguedad
	children->setGeneration(current->getGeneration());
	children->setOld(current->getOld()+1);
	children->setNumberBranch(0);
	
	// Asignamos el segmento del arbol
	aux = children;

	// Empezamos el calculo recursivo de los tramos
	for(i = 1; i < (sub+1); i++) {
		// Recalculamos lo necesario
		pIni = new Point();
		temp = new Structure();
		// Calculamos la longitud del nuevo tramo
		high = (((float)((aleats[i] - aleats[i-1])/100.0))*highT);
		// Punto inicial del tramo es el punto final del anterior
		pIni->setX(pEnd->getX());
		pIni->setY(pEnd->getY());
		pIni->setZ(pEnd->getZ());

		// Obtenemos el nuevo alfa y gamma
		aleat1 = ((this->getParameters())->getAleator())->alea();
		aleat2 = ((this->getParameters())->getAleator())->alea();
		// Un gamma aleatorio (maximo el de tortuosidad indicado)
		gamma = (aleat1*(this->getParameters())->radian(this->getParameters()->getDeviousnessAngle()))/((float)100.0);
		// El alfa puede variar de -45 a 45 grados
		alfa = (float)((this->getParameters())->radian(this->getParameters()->getDeviousnessArch()) * (aleat2/100.0));
		alfa = (float)(alfa - ((this->getParameters())->radian(this->getParameters()->getDeviousnessArch()) / 2.0));
		alfa = (children->getAlfa()) + alfa;
		// Calculamos el punto final
		x = (float)((high * sin(gamma)) * sin(alfa));
		y = (float)(high * cos(gamma));
		z = (float)((high * sin(gamma)) * cos(alfa));
		// El punto final
		pEnd = new Point();
		pEnd->setX(pIni->getX() + x);
		pEnd->setY(pIni->getY() + y);
		pEnd->setZ(pIni->getZ() + z);
		// Asignamos valores
		temp->setInitialPoint(pIni);
		temp->setFinalPoint(pEnd);
		temp->setInitialDiameter(diameterIni);
		temp->setHigh(high);
		temp->setAlfa(alfa);
		temp->setGamma(gamma);
		diameterIni = diameterIni + (diameterIncr * high);
		temp->setFinalDiameter(diameterIni);
		temp->dead();
		temp->setGeneration(children->getGeneration());
		temp->setOld(children->getOld());
		temp->setNumberBranch(0);
		// Indicamos la estructura del tramo
		children->setChildren(temp);
		temp->setFather(children);
		// Colocamos punteros de nuevo
		children = children->getChildren();
	}
	free(aleats);

	global+=sub+1;

	return aux;
}

/***************************************************************/
/* Funcion: generateBranch                                     */
/*															   */
/* Descripcion: Función que genera las ramas del un tramo del  */
/*              del arbol.                                     */  
/*                                                             */ 
/* Argumentos: Entrada: Structure* current: El tramo implicado */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
void Tree::generateBranch(Structure* current) {
	Structure** branch = NULL, *initial = NULL, *temp = NULL, *trunk = NULL;
	Point* pIni = NULL, *pEnd = NULL, *temp2 = NULL;
	float subdivision = 0.0, incrementSubdivision = 0.0, aleatG = 0.0;
	float initialSubdivision = 0.0, finalSubdivision = 0.0;
	float alfa  = 0.0, gamma = 0.0, gamma2 = 0.0, high = 0.0, highT = 0.0;
	float x = 0.0, y = 0.0, z = 0.0, modulo = 0.0, rangle = 0.0;
	int i = 0, sub = 0, contador = 0, angle = 0;
	int aleat1 = 0, aleat2 = 0;
	int* branches = NULL;
	int generations = 0, numBranches = 0;

	// Calculamos la generacion de la rama
	temp = current;
	generations = temp->getGeneration();

	if (generations >= ((this->getParameters())->getGeneration())) 
		return;
	
	// Calculamos el gamma asociado
	gamma = (float)(this->getParameters())->getTreeCone();
	for(i = 0; i < generations; i++) {	
		gamma = gamma + (this->getParameters())->getVarTreeCone() / ((float)(i+2));
	}

	// Calculamos el numero de subdivisiones
	subdivision = (float)1.0/(this->getParameters())->getFrondage();
	if ((subdivision - (int)subdivision) < 0.5)
		sub = (int)subdivision;
	else
		sub = ((int)subdivision) + 1;

	// Miramos si tenemos ramas
	branches = (int*)malloc(sub*sizeof(int));
	for(i = 0; i < sub; i++) {
		aleat1 = ((this->getParameters())->getAleator())->alea();
		if (((float)(aleat1/100.0)) <= (this->getParameters())->getInvFrondage()) {
			// con 1 indicamos la presencia de rama
			branches[i] = 1;
			numBranches++;
			global++;
		}
		else 
			// con 0 indicamos la no-presencia de rama
			branches[i] = 0;
	}

	// Calculamos el inicio de las subdivisiones
	aleat1 = ((this->getParameters())->getAleator())->alea();
	// Calculamos el angulo permitido
	angle = ((this->getParameters())->getMaxAngle() - (this->getParameters())->getMinAngle());
	rangle = (this->getParameters())->radian(angle);
	initialSubdivision = ((float)((aleat1 * rangle) / 100.0)) + (this->getParameters())->radian((this->getParameters())->getMinAngle());
	incrementSubdivision = (float)(rangle / sub);

	// Generamos el array de ramas del tramo
	current->setBranches((Structure**)malloc(numBranches*sizeof(Structure*)));

	// Por cada rama a generar
	contador = 0;
	for(i = 0; i < sub; i++) {
		finalSubdivision = initialSubdivision + incrementSubdivision;

		// Si hay rama
		if (branches[i] == 1) {
			// Calculamos alfa
			aleat1 = ((this->getParameters())->getAleator())->alea();
			alfa = ((aleat1*incrementSubdivision)/((float)100.0)) + initialSubdivision;
			if (alfa >= (this->getParameters())->radian((this->getParameters())->getMaxAngle()))
				alfa = alfa - (this->getParameters())->radian((this->getParameters())->getMaxAngle());
			aleatG = this->randGauss(&idum);
			alfa = alfa + (alfa * aleatG);

			// Calculamos gamma
			aleat1 = ((this->getParameters())->getAleator())->alea();
			aleat2 = ((this->getParameters())->getAleator())->alea();
			if (aleat1 < ((this->getParameters())->getVariability() * 100.0)) {
				if (aleat2 < 50) 
					gamma = (float)(gamma - (gamma * (aleat2/100.0)));
				else
					gamma = (float)(gamma + (gamma * (aleat2/100.0)));
			}
			gamma2 = (aleat1*gamma)/((float)100.0);
			aleatG = this->randGauss(&idum);
			gamma2 = gamma2 + (gamma2 * aleatG);

			// Si tienes tortuosidad
			if (current->getCDeviousness() == 1) {
				initial = current->getDeviousness();
				while(initial->getChildren() != NULL)
					initial = initial->getChildren();
			}
			// Generamos la rama
			temp = new Structure();
			// Indicamos su padre
			temp->setFather(current);
			// Indicamos que esta nacida
			temp->born();
			// Indicamos cual es su alfa y gamma
			temp->setAlfa(alfa);
			temp->setGamma(gamma2);
			// Indicamos su diametro y punto inicial
			pIni = new Point();
			aleat1 = ((this->getParameters())->getAleator())->alea();
			// Comprobamos la tortuosidad
			if (current->getCDeviousness() == 1) {
				trunk = current->getDeviousness();
				if (aleat1 <= ((this->getParameters())->getVariability()*100)) {
					high = current->getHigh();
					high = high - (high * ((float)(aleat1/100.0)));
					// Calculamos el tramo y la altura sobre este
					highT = high;
					high = high - trunk->getHigh();
					while (high > 0) {
						highT = high;
						high = high - trunk->getHigh();
						if (high > 0)
							trunk = trunk->getChildren();
					}
					x = (float)(highT * (sin(trunk->getGamma())) * (sin(trunk->getAlfa())));
					y = (float)(highT * cos(trunk->getGamma()));
					z = (float)(highT * (sin(trunk->getGamma())) * cos(trunk->getAlfa()));
					pIni->setX((trunk->getInitialPoint())->getX() + x);
					pIni->setY((trunk->getInitialPoint())->getY() + y);
					pIni->setZ((trunk->getInitialPoint())->getZ() + z);
				}
				else {
					while(trunk->getChildren() != NULL)
						trunk = trunk->getChildren();

					pIni->setX((trunk->getFinalPoint())->getX());
					pIni->setY((trunk->getFinalPoint())->getY());
					pIni->setZ((trunk->getFinalPoint())->getZ());
				}
			}
			else {
				if (aleat1 <= ((this->getParameters())->getVariability()*100)) {
					high = current->getHigh();
					high = high - (high * ((float)(aleat1/100.0)));
					x = (float)(high * (sin(current->getGamma())) * (sin(current->getAlfa())));
					y = (float)(high * cos(current->getGamma()));
					z = (float)(high * (sin(current->getGamma())) * cos(current->getAlfa()));
					pIni->setX((current->getInitialPoint())->getX() + x);
					pIni->setY((current->getInitialPoint())->getY() + y);
					pIni->setZ((current->getInitialPoint())->getZ() + z);
				}
				else {
					pIni->setX((current->getFinalPoint())->getX());
					pIni->setY((current->getFinalPoint())->getY());
					pIni->setZ((current->getFinalPoint())->getZ());
				}
			}
			temp->setInitialPoint(pIni);

			// Indicamos su generacion
			temp->setGeneration(current->getGeneration()+1);
			temp->setOld(current->getOld()+1);

			// Indicamos su longitud
			temp->setHigh((current->getHigh() * (this->getParameters())->getRatioTrunk()) + (current->getFinalDiameter() / (float)2.0));
			aleat1 = ((this->getParameters())->getAleator())->alea();
			if (aleat1 < ((this->getParameters())->getVariability()*100)) {
				aleat2 = ((this->getParameters())->getAleator())->alea();
				if (aleat2 < 50)
					temp->setHigh(temp->getHigh() - (temp->getHigh() * ((float)(aleat1/100.0))));
				else
					temp->setHigh(temp->getHigh() + (temp->getHigh() * ((float)(aleat1/100.0))));
			}
			aleatG = this->randGauss(&idum);
			temp->setHigh(temp->getHigh() + (temp->getHigh() * aleatG));

			// Calculamos los diametros
			temp->setInitialDiameter(current->getFinalDiameter() * (this->getParameters())->getRatioDiameter());
			temp->setFinalDiameter(temp->getInitialDiameter() - (temp->getInitialDiameter() * (this->getParameters())->getRatioDiameter2()));
			aleat1 = ((this->getParameters())->getAleator())->alea();
			aleat2 = ((this->getParameters())->getAleator())->alea();
			if (aleat1 < ((this->getParameters())->getVariability() * 100.0)) {
				if (aleat2 < 50) 
					temp->setFinalDiameter(temp->getFinalDiameter() - (temp->getFinalDiameter() * ((float)(aleat1/100.0))));
				else
					temp->setFinalDiameter(temp->getFinalDiameter() + (temp->getFinalDiameter() * ((float)(aleat1/100.0))));
			}
			aleatG = this->randGauss(&idum);
			temp->setInitialDiameter(temp->getInitialDiameter() + (temp->getInitialDiameter() * aleatG));
			aleatG = this->randGauss(&idum);
			temp->setFinalDiameter(temp->getFinalDiameter() + (temp->getFinalDiameter() * aleatG));
			
			// Calculamos el punto final
			pEnd = new Point();
			x = (float)((temp->getHigh() * sin(temp->getGamma())) * (sin(temp->getAlfa())));
			y = (float)(temp->getHigh() * cos(temp->getGamma()));
			z = (float)((temp->getHigh() * sin(temp->getGamma())) * cos(temp->getAlfa()));
			pEnd->setX((temp->getInitialPoint())->getX() + x);
			pEnd->setY((temp->getInitialPoint())->getY() + y);
			pEnd->setZ((temp->getInitialPoint())->getZ() + z);
			temp->setFinalPoint(pEnd);

			aleat1 = ((this->getParameters())->getAleator())->alea();
			if (aleat1 < ((this->getParameters())->getDeviousness() * 100.0)) {
				temp->setDeviousness(this->generateDeviousness(temp));
				temp->setCDeviousness(1);
			}
			else {
				global++;
			}

			current->getBranches()[contador] = temp;

			// Colocamos valores para la proxima interaccion
			contador++;
			if (finalSubdivision >= (this->getParameters())->radian((this->getParameters())->getMaxAngle()))
				finalSubdivision = finalSubdivision - (this->getParameters())->radian((this->getParameters())->getMaxAngle());
		}
		// Si no hay rama
		else {
			if (finalSubdivision >= (this->getParameters())->radian((this->getParameters())->getMaxAngle()))
				finalSubdivision = finalSubdivision - (this->getParameters())->radian((this->getParameters())->getMaxAngle());
		}
		// Indicamos el inicio y final de la nueva seccion
		initialSubdivision = finalSubdivision;
		finalSubdivision = initialSubdivision + incrementSubdivision;
	}

	current->setNumberBranch(numBranches);
	free(branches);
}

/***************************************************************/
/* Funcion: print                                              */
/*															   */
/* Descripcion: Función que imprime a un fichero el contenido  */
/*              de los tramos.                                 */  
/*                                                             */ 
/* Argumentos: Entrada: Structure* initial: El tramo inicial.  */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
int Tree::print(FILE* fp, Structure* initial) {
	float alfa = 0.0, gamma = 0.0, diameter = 0.0;
	int i = 0;
	Structure* temp = NULL;

	if (initial == NULL)
		return -1;
	

	if (initial->getCDeviousness() == 1) {
		temp = initial->getDeviousness();
		while(temp != NULL) {
			// pasamos alfa y gamma a grados
			alfa = this->getParameters()->angle(temp->getAlfa());
			gamma = this->getParameters()->angle(temp->getGamma());
			if ((temp->getChildren() == NULL) & (temp->getNumberBranch() < 0))
				diameter = 0.0;
			else
				diameter = temp->getFinalDiameter();

			fprintf(fp,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",temp->getInitialDiameter(),diameter,temp->getHigh(),gamma,alfa
														 ,temp->getInitialPoint()->getX(),temp->getInitialPoint()->getY()
														 ,temp->getInitialPoint()->getZ());
			temp = temp->getChildren();
		}
	}
	else {
		// pasamos alfa y gamma a grados
		alfa = this->getParameters()->angle(initial->getAlfa());
		gamma = this->getParameters()->angle(initial->getGamma());
		if ((initial->getChildren() == NULL) & (initial->getNumberBranch() < 0))
			diameter = 0.0;
		else
			diameter = initial->getFinalDiameter();
		// Imprimmos la linea por nodo
		fprintf(fp,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",initial->getInitialDiameter(),diameter,initial->getHigh(),gamma,alfa
			                                         ,initial->getInitialPoint()->getX(),initial->getInitialPoint()->getY()
													 ,initial->getInitialPoint()->getZ());
	}

	if (initial->getChildren() != NULL) {
		this->print(fp,initial->getChildren());
	}
	if (initial->getBranches() != NULL) {
		for(i = 0; i < initial->getNumberBranch(); i++) {
			this->print(fp,initial->getBranches()[i]);
		}
	}

	return global;
}

/***************************************************************/
/* Funcion: printMPEG4                                         */
/*															   */
/* Descripcion: Función que imprime a un fichero el contenido  */
/*              de los tramos en formato MPEG-4.               */  
/*                                                             */ 
/* Argumentos: Entrada: Structure* initial: El tramo inicial.  */
/*                                                             */
/*             Salida: Void.                                   */ 
/***************************************************************/
int Tree::printMPEG4(FILE* fp, Structure* initial, char* texture) {
	int i = 0;
	Structure* temp = NULL;

	if (initial == NULL)
		return -1;

	if (initial->getCDeviousness() == 1) {
		temp = initial->getDeviousness();
		while(temp != NULL) {
			
			fprintf(fp,"      Transform { #Tramo %d\n",tramo);
			fprintf(fp,"        translation %f %f %f\n",(temp->getInitialPoint())->getX()
				                                       ,(temp->getInitialPoint())->getY()
													   ,(temp->getInitialPoint())->getZ());
			fprintf(fp,"        rotation 0.0 1.0 0.0 %f\n",temp->getAlfa());
			fprintf(fp,"        children [\n");
			fprintf(fp,"          Transform {\n");
			fprintf(fp,"            rotation 1.0 0.0 0.0 %f\n",temp->getGamma());
			fprintf(fp,"            children [\n");
			fprintf(fp,"              Transform {\n");
			fprintf(fp,"                translation 0.0 %f 0.0\n",((float)(temp->getHigh() / 2.0)));
			fprintf(fp,"                children [\n");
			fprintf(fp,"                  Shape {\n");
			fprintf(fp,"                    appearance Appearance {\n");
			fprintf(fp,"                      material Material {\n");
			fprintf(fp,"                        diffuseColor 0.5 0.5 0.5\n");
			fprintf(fp,"                        emissiveColor 0.5 0.5 0.5\n");
			fprintf(fp,"                      }\n");
			fprintf(fp,"                      texture ImageTexture {\n");
			fprintf(fp,"                        url \"%s\"\n",texture);
			fprintf(fp,"                      }\n");
			fprintf(fp,"                    }\n");
			fprintf(fp,"                    geometry Cylinder {\n");
			fprintf(fp,"                      height %f\n",temp->getHigh());
			fprintf(fp,"                      radius %f\n",((float)(temp->getInitialDiameter()/2.0)));
			fprintf(fp,"                    }\n");
			fprintf(fp,"                  }\n");
			fprintf(fp,"                 ]\n");
			fprintf(fp,"                }\n");
			if ((temp->getChildren() == NULL) & (initial->getNumberBranch() <= 0)) {
				fprintf(fp,"              Transform {\n");
				fprintf(fp,"                translation 0.0 %f 0.0\n",((float)((temp->getHigh() + (temp->getHigh()/2.0)*0.5))));
				fprintf(fp,"                children [\n");
				fprintf(fp,"                  Shape {\n");
				fprintf(fp,"                    appearance Appearance {\n");
				fprintf(fp,"                      material Material {\n");
				fprintf(fp,"                        diffuseColor 0.5 0.5 0.5\n");
				fprintf(fp,"                        emissiveColor 0.5 0.5 0.5\n");
				fprintf(fp,"                      }\n");
				fprintf(fp,"                      texture ImageTexture {\n");
				fprintf(fp,"                        url \"%s\"\n",texture);
				fprintf(fp,"                      }\n");
				fprintf(fp,"                    }\n");
				fprintf(fp,"                    geometry Cone {\n");
				fprintf(fp,"                      bottomRadius %f\n",((float)(temp->getInitialDiameter()/2.0)));
				fprintf(fp,"                      height %f\n",((float)(temp->getHigh()/2.0)));
				fprintf(fp,"                    }\n");
				fprintf(fp,"                  }\n");
				fprintf(fp,"                ]\n");
				fprintf(fp,"              }\n");
			}
			else {
				fprintf(fp,"              Transform {\n");
				fprintf(fp,"                translation 0.0 %f 0.0\n",temp->getHigh());
				fprintf(fp,"                children [\n");
				fprintf(fp,"                  Shape {\n");
				fprintf(fp,"                    appearance Appearance {\n");
				fprintf(fp,"                      material Material {\n");
				fprintf(fp,"                        diffuseColor 0.5 0.5 0.5\n");
				fprintf(fp,"                        emissiveColor 0.5 0.5 0.5\n");
				fprintf(fp,"                      }\n");
				fprintf(fp,"                      texture ImageTexture {\n");
				fprintf(fp,"                        url \"%s\"\n",texture);
				fprintf(fp,"                      }\n");
				fprintf(fp,"                    }\n");
				fprintf(fp,"                    geometry Sphere {\n");
				fprintf(fp,"                      radius %f\n",((float)(temp->getInitialDiameter()/2.0)));
				fprintf(fp,"                    }\n");
				fprintf(fp,"                  }\n");
				fprintf(fp,"                ]\n");
				fprintf(fp,"              }\n");
			}
			fprintf(fp,"            ]\n");
			fprintf(fp,"          }\n");
			fprintf(fp,"        ]\n");
			fprintf(fp,"      }\n");
			tramo++;

			temp = temp->getChildren();
		}
	}
	else {
		fprintf(fp,"      Transform { #Tramo %d\n",tramo);
		fprintf(fp,"        translation %f %f %f\n",(initial->getInitialPoint())->getX()
			                                       ,(initial->getInitialPoint())->getY()
												   ,(initial->getInitialPoint())->getZ());
		fprintf(fp,"        rotation 0.0 1.0 0.0 %f\n",initial->getAlfa());
		fprintf(fp,"        children [\n");
		fprintf(fp,"          Transform {\n");
		fprintf(fp,"            rotation 1.0 0.0 0.0 %f\n",initial->getGamma());
		fprintf(fp,"            children [\n");
		fprintf(fp,"              Transform {\n");
		fprintf(fp,"                translation 0.0 %f 0.0\n",((float)(initial->getHigh() / 2.0)));
		fprintf(fp,"                children [\n");
		fprintf(fp,"                  Shape {\n");
		fprintf(fp,"                    appearance Appearance {\n");
		fprintf(fp,"                      material Material {\n");
		fprintf(fp,"                        diffuseColor 0.5 0.5 0.5\n");
		fprintf(fp,"                        emissiveColor 0.5 0.5 0.5\n");
		fprintf(fp,"                      }\n");
		fprintf(fp,"                      texture ImageTexture {\n");
		fprintf(fp,"                        url \"%s\"\n",texture);
		fprintf(fp,"                      }\n");
		fprintf(fp,"                    }\n");
		fprintf(fp,"                    geometry Cylinder {\n");
		fprintf(fp,"                      height %f\n",initial->getHigh());
		fprintf(fp,"                      radius %f\n",((float)(initial->getInitialDiameter()/2.0)));
		fprintf(fp,"                    }\n");
		fprintf(fp,"                  }\n");
		fprintf(fp,"                 ]\n");
		fprintf(fp,"                }\n");
		if ((initial->getChildren() == NULL) & (initial->getNumberBranch() <= 0)) {
			fprintf(fp,"              Transform {\n");
			fprintf(fp,"                translation 0.0 %f 0.0\n",((float)((initial->getHigh() + (initial->getHigh()/2.0)*0.5))));
			fprintf(fp,"                children [\n");
			fprintf(fp,"                  Shape {\n");
			fprintf(fp,"                    appearance Appearance {\n");
			fprintf(fp,"                      material Material {\n");
			fprintf(fp,"                        diffuseColor 0.5 0.5 0.5\n");
			fprintf(fp,"                        emissiveColor 0.5 0.5 0.5\n");
			fprintf(fp,"                      }\n");
			fprintf(fp,"                      texture ImageTexture {\n");
			fprintf(fp,"                        url \"%s\"\n",texture);
			fprintf(fp,"                      }\n");
			fprintf(fp,"                    }\n");
			fprintf(fp,"                    geometry Cone {\n");
			fprintf(fp,"                      bottomRadius %f\n",((float)(initial->getInitialDiameter()/2.0)));
			fprintf(fp,"                      height %f\n",((float)(initial->getHigh()/2.0)));
			fprintf(fp,"                    }\n");
			fprintf(fp,"                  }\n");
			fprintf(fp,"                ]\n");
			fprintf(fp,"              }\n");
		}
		else {
			fprintf(fp,"              Transform {\n");
			fprintf(fp,"                translation 0.0 %f 0.0\n",initial->getHigh());
			fprintf(fp,"                children [\n");
			fprintf(fp,"                  Shape {\n");
			fprintf(fp,"                    appearance Appearance {\n");
			fprintf(fp,"                      material Material {\n");
			fprintf(fp,"                        diffuseColor 0.5 0.5 0.5\n");
			fprintf(fp,"                        emissiveColor 0.5 0.5 0.5\n");
			fprintf(fp,"                      }\n");
			fprintf(fp,"                      texture ImageTexture {\n");
			fprintf(fp,"                        url \"%s\"\n",texture);
			fprintf(fp,"                      }\n");
			fprintf(fp,"                    }\n");
			fprintf(fp,"                    geometry Sphere {\n");
			fprintf(fp,"                      radius %f\n",((float)(initial->getInitialDiameter()/2.0)));
			fprintf(fp,"                    }\n");
			fprintf(fp,"                  }\n");
			fprintf(fp,"                ]\n");
			fprintf(fp,"              }\n");
		}
		fprintf(fp,"            ]\n");
		fprintf(fp,"          }\n");
		fprintf(fp,"        ]\n");
		fprintf(fp,"      }\n");
		tramo++;
	}

	if (initial->getChildren() != NULL) {
		this->printMPEG4(fp,initial->getChildren(),texture);
	}
	if (initial->getBranches() != NULL) {
		for(i = 0; i < initial->getNumberBranch(); i++) {
			this->printMPEG4(fp,initial->getBranches()[i],texture);
		}
	}

	return global;
}

/***************************************************************/
/* Funcion: randGauss                                          */
/*															   */
/* Descripcion: Función que obtiene un numero entre -1 a 1 con */
/*              con una distribucion gaussiana.                */  
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: float: El valor aleatorio obtenido.     */ 
/***************************************************************/
float Tree::randGauss(long *idum) {
	float ret = 10.0;

/*	while ((ret > 1.0) | (ret < -1.0))
		ret = gauss(idum);*/
	ret = (float)(((this->getParameters())->getAleator())->alea() / 100.0);
	if (ret > 0.5)
		ret =  (float)-0.1;
	else
		ret = (float)0.1;

	return ret;
}

/***************************************************************/
/* Funcion: gauss                                              */
/*															   */
/* Descripcion: Función que obtiene un numero entre -infinigo a*/
/*              infinito con una distribucion gaussiana.       */  
/*                                                             */ 
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: float: El valor aleatorio obtenido.     */ 
/***************************************************************/
float Tree::gauss(long *idum) {
	static int iset = 0;
	static float gset = 0.0;
	float rsq = 0.0, v1 = 0.0, v2 = 0.0, fac = 0.0;

	if (*idum < 0) iset = 0;
	if (iset == 0) {
		do {
			v1 = (float)(2.0 * this->rand1(idum)-1.0);
			v2 = (float)(2.0 * this->rand1(idum)-1.0);
			rsq=(v1*v1)+(v2*v2);
		} while ((rsq >= 1.0) || (rsq == 0.0));
		fac = (float)(sqrt(-2.0*log(rsq)/rsq));
		gset=v1*fac;
		iset=1;
		return v2*fac;
	}
	else {
		iset = 0;
		return gset;
	}
}

/***************************************************************/
/* Funcion: rand1                                              */
/*															   */
/* Descripcion: Función que obtiene un numero entre 0 a 1 con  */
/*              una distribucion uniforme.                     */  
/*                                                             */ 
/* Argumentos: Entrada: long *idum: Numero negativo para       */
/*                                  inicializar.               */
/*                                                             */
/*             Salida: float: El valor aleatorio obteneido.    */ 
/***************************************************************/
float Tree::rand1(long *idum) {
	int j = 0;
	long k = 0;
	static long iy = 0;
	static long iv[32];
	float temp = 0.0;

	if((*idum <= 0) || (!iy)) {
		if (-(*idum) < 1) *idum = 1;
		else *idum = -(*idum);
		for (j = 39; j >= 0; j--) {
			k = *idum / 127773;
			*idum = 16807 * (*idum-k*127773) - 2836 * k;
			if (*idum < 0) *idum += 2147483647;
			if (j < 32) iv[j] = *idum;
		}
		iy = iv[0];
	}
	k = (*idum)/127773;
	*idum = 16807 * (*idum-k*127773) - 2836 * k;
	if (*idum < 0) *idum += 2147483647;
	j = iy/(1+(2147483647-1)/32);
	iy = iv[j];
	iv[j] = *idum;
	if ((temp=(float)(1.0/2147483647)*iy) > (1.0 - 1.2e-7)) return (float)(1.0 - 1.2e-7);
	else return temp;
}
