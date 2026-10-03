/*******************************************************/
/* Fichero: Structure.h              Fecha: 02-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera de la clase para   */
/*              almacenar la estructura del arbol.     */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef STRUCTURE_H
#define STRUCTURE_H

// Incluimos las librerias necesarias
#include "Point.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la estructura para poder referenciarse
class Structure;

// Definimos la clase
class Structure  
{
// Indicamos los atributos privados de la clase
private:
	// Indicamos el punto inicial del tramo
	Point* initialPoint;
	// Indicamos el punto final del tramo
	Point* finalPoint;
	// Indicamos el diametro inicial del tramo
	float initialDiameter;
	// Indicamos el diametro final del tramo
	float finalDiameter;
	// Indicamos el angulo alfa que se giro
	float alfa;
	// Indicamos el angulo gamma que se giro
	float gamma;
	// Indicamos la altura del tramo
	float high;
	// Indicamos el numero de ramas
	int numberBranch;
	// Indicamos las ramas que nacen
	Structure** branches;
	// Indicamos el antecesor de dicho tramo
	Structure* father;
	// Indicamos el sucesor de dicho tramo
	Structure* children;
	// Indica el estado de crecimiento
	int state; // 0 = Born, 1 = Life, 2 = Dead
	// Indicamos la generacion del tramo
	int generation ;
	// Indica la cantidad de padres que tiene
	int old;
	// Indica si presenta tortuosidad
	int cDeviousness;
	// Estructura de la tortuosidad
	Structure* deviousness;

// Indicamos los metodos publicos
public:
	// Constructor por defecto
	Structure();

	// Destructor de la clase
	virtual ~Structure();

	/****************************************************************************************/
	/* Indicamos los metodos para obtener los valores de los atributos privados de la clase */   
	/****************************************************************************************/
	Point* getInitialPoint();
	Point* getFinalPoint();
	float getInitialDiameter();
	float getFinalDiameter();
	float getAlfa();
	float getGamma();
	float getHigh();
	int getNumberBranch();
	Structure** getBranches();
	Structure* getFather();
	Structure* getChildren();
	int getState();
	int getGeneration();
	int getOld();
	int getCDeviousness();
	Structure* getDeviousness();

	/*******************************************************************************************/
	/* Indicamos los metodos para establecer los valores de los atributos privados de la clase */
	/*******************************************************************************************/
	void setInitialPoint(Point* initialPoint);
	void setFinalPoint(Point* finalPoint);
	void setInitialDiameter(float initialDiameter);
	void setFinalDiameter(float finalDiameter);
	void setAlfa(float alfa);
	void setGamma(float gamma);
	void setHigh(float high);
	void setNumberBranch(int numberBranch);
	void setBranches(Structure** branches);
	void setFather(Structure* father);
	void setChildren(Structure* children);
	void setState(int state);
	void setGeneration(int generation);
	void setOld(int old);
	void setCDeviousness(int cDeviousness);
	void setDeviousness(Structure* deviousness);

	/*******************************************************************************************/
	/* Indicamos los metodos de utilidades varias                                              */
	/*******************************************************************************************/
	void born();
	void life();
	void dead();


};	

#endif 
