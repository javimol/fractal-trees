/*******************************************************/
/* Fichero: Parameters.h             Fecha: 27-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera de la clase para   */
/*              almacenar los parametros del arbol.    */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef PARAMETERS_H
#define PARAMETERS_H

// Incluimos las librerias necesaria
#include "Aleator.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos el numero pi
#define PI 3.141592 

// Definimos la clase
class Parameters  
{
// Indicamos los atributos privados de la clase
private:
	// Indicamos la altura maxima
	float maxHeight;
	// Indicamos el indice de crecimiento
	float paceGrowth;
	// Indicamos la edad (meses)
	int age;
	// Indicamos la altura del arbol
	float height;
	// Indicamos el ratio entre copa y tronco
	float ratioTop;
	// Indicamos la altura del tronco
	float heightTrunk;
	// Indicamos la altura de la copa
	float heightTop;
	// Indicamos el ratio entre niveles de ramaje
	float ratioBranch;
	// Indicamos la frondosidad
	float frondage;
	// Indicamos el valor inverso de la frondosidad
	float invFrondage;
	// Indicamos el maximo giro en la direccion del crecimiento
	float treeCone;
	// Indicamos el minimo giro en la direccion del crecimiento
	float varTreeCone;
	// Indicamos el maximo giro en la perpendicular de la direccion de crecimiento
	int maxAngle;
	// Indicamos el minimo giro en la perpendicular de la direccion de crecimiento
	int minAngle;
	// Indicamos el ratio entre tronco y ramas
	float ratioTrunk;
	// Indicamos el ratio entre el radio de la base con respecto a la altura
	float ratioBase;
	// Indicamos el diametro de la base
	float diameterBase;
	// Indicamos el ratio entre el radio de la parte superior del tronco con respecto a la altura
	float ratioDiameter2;
	// Indicamos el ratio entre el diametro del tronco y las ramas
	float ratioDiameter;
	// Indicamos la tortuosidad
	float deviousness;
	// Indicamos el inverso de la tortuosidad
	float invDeviousness;
	// Indicamos el maximo giro en la direccion del crecimiento para la tortuosidad
	int deviousnessAngle;
	// Indicamos el maximo giro en la direccion perpendicular del crecimiento para la tortuosidad
	int deviousnessArch;
	// Indicamos la variabilidad del arbol
	float variability;
	// Generador de numeros aleatorios
	Aleator* aleator;
	// Probabilidad de continuacion de un tronco
	float probabilityTrunk;
	// El numero de generaciones
	int generation;
	
// Indicamos los metodos publicos
public:
	// Constructor por defecto
	Parameters();

	// Destructor de la clase
	virtual ~Parameters();

	/****************************************************************************************/
	/* Indicamos los metodos para obtener los valores de los atributos privados de la clase */   
	/****************************************************************************************/
	float getMaxHeight();
	float getPaceGrowth();
	int getAge();
	float getHeight();
	float getRatioTop();
	float getHeightTrunk();
	float getHeightTop();
	float getRatioBranch();
	float getFrondage();
	float getInvFrondage();
	float getTreeCone();
	float getVarTreeCone();
	int getMaxAngle();
	int getMinAngle();
	float getRatioTrunk();
	float getRatioBase();
	float getDiameterBase();
	float getRatioDiameter2();
	float getRatioDiameter();
	float getDeviousness();
	float getInvDeviousness();
	int getDeviousnessAngle();
	int getDeviousnessArch();
	float getVariability();
	float getProbabilityTrunk();
	Aleator* getAleator();
	int getGeneration();

	/*******************************************************************************************/
	/* Indicamos los metodos para establecer los valores de los atributos privados de la clase */
	/*******************************************************************************************/
	void setMaxHeight(float maxHeight);
	void setPaceGrowth(float paceGrowth);
	void setAge(int age);
	void setHeight(float height);
	void setRatioTop(float ratioTop);
	void setHeightTrunk(float heightTrunk);
	void setHeightTop(float heightTop);
	void setRatioBranch(float ratioBranch);
	void setFrondage(float frondage);
	void setInvFrondage(float invFrondage);
	void setTreeCone(float treeCone);
	void setVarTreeCone(float varTreeCone);
	void setMaxAngle(int maxAngle);
	void setMinAngle(int minAngle);
	void setRatioTrunk(float ratioTrunk);
	void setRatioBase(float ratioBase);
	void setDiameterBase(float diameterBase);
	void setRatioDiameter2(float ratioDiameter2);
	void setRatioDiameter(float ratioDiameter);
	void setDeviousness(float deviousness);
	void setInvDeviousness(float invDeviousness);
	void setDeviousnessAngle(int deviousnessAngle);
	void setDeviousnessArch(int deviousnessArch);
	void setVariability(float variability);
	void setProbabilityTrunk(float probabilityTrunk);
	void setAleator(Aleator* aleator);
	void setGeneration(int generation);

	/*******************************************/
	/* Metodos de transformacion de parametros */
	/*******************************************/	
	// Funcion que pasa un valor en centimetros a metros
	float meters(float centimeters);
	// Funcion que pasa un valor en metros a centimetros
	float centimeters(float meters);

	// Funcion que pasa de radianes a angulo
	float angle(float radian);
	// Funcion que pasa de angulos a radianes
	float radian(int angle);
	
	// Funcion que pasa de meses a años
	float years(int months);
	// Funcion que pasa de años a meses
	int months(float years);

	// Funcion que pasa un ratio de (0 a 1) a de (0 a 100)
	float ratio100(float ratio1);
	// Funcion que pasa un ratio de (0 a 100) a de (0 a 1)
	float ratio1(float ratio100);
	// Funcion que invierte un ratio (entre 0 a 1)
	float inverse(float ratio);

	/************************************/
	/* Metodos con otra funcionalidades */
	/************************************/
	// Funcion que calcular la altura del arbol
	float calculateHeight();
	// Funcion que calcular la altura del tronco
	float calculateHeightTrunk();
	// Funcion que calcular la altura de la copa
	float calculateHeightTop();
	// Funcion que calcula el diametro de la base
	float calculateDiameterBase();
	// Funcion que calcular una dimension al que se aplica un ratio de 0 a 1
	float applyRatio(float value, float ratio);
	float applyRatio(int value, float ratio);
	// Funcion que da el numero de partes/subdivison/etc a partir de un ratio de 0 a 100
	int subdivide(float ratio);
	// Funcion que indica si todos los parametros tiene valores
	int complete();
	// Funcion para variar los parametros calculados
	void change();

	

};

#endif 
