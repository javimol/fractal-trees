/*******************************************************/
/* Fichero: Point.h                  Fecha: 02-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera de la clase para   */
/*              almacenar un punto tridimensional.     */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef POINT_H
#define POINT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class Point  
{
// Indicamos los atributos privados de la clase
private:
	// Indicamos la coordenada x
	float x;
	// Indicamos la coordenada y
	float y;
	// Indicamos la coordenada z
	float z;

// Indicamos los metodos publicos
public:
	// Constructor por defecto
	Point();

	// Destructor de la clase
	virtual ~Point();

	/****************************************************************************************/
	/* Indicamos los metodos para obtener los valores de los atributos privados de la clase */   
	/****************************************************************************************/
	float getX();
	float getY();
	float getZ();

	/*******************************************************************************************/
	/* Indicamos los metodos para establecer los valores de los atributos privados de la clase */
	/*******************************************************************************************/
	void setX(float x);
	void setY(float y);
	void setZ(float z);

};

#endif 