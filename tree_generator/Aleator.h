/*******************************************************/
/* Fichero: Aleator.h                Fecha: 03-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera de la clase para   */
/*              generar numeros aleatorios.            */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef ALEATOR_H
#define ALEATOR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class Aleator  
{
// Indicamos los atributos privados de la clase
private:
	// Indicamos el valor maximo
	int max;
	// Indicamos el valor minimo
	int min;
	// Indicamos la semilla inicializadora
	int randomize;
	
// Indicamos los metodos publicos de la clase.
public:
	// Constructor por defecto
	Aleator();

	// Desctructor de la clase
	virtual ~Aleator();

	/****************************************************************************************/
	/* Indicamos los metodos para obtener los valores de los atributos privados de la clase */   
	/****************************************************************************************/
	int getMax();
	int getMin();
	int getRandomize();

	/*******************************************************************************************/
	/* Indicamos los metodos para establecer los valores de los atributos privados de la clase */
	/*******************************************************************************************/
	void setMax(int max);
	void setMin(int min);
	void setRandomize(int randomize);
	
	/*******************************************************************************************/
	/* Indicamos los metodos para la generación del arbol                                      */
	/*******************************************************************************************/
	int alea();


};

#endif
