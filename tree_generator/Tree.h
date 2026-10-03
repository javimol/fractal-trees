/*******************************************************/
/* Fichero: Tree.h                   Fecha: 02-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera de la clase para   */
/*              almacenar un arbol.                    */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef TREE_H
#define TREE_H

// Incluimos las librerias necesarias
#include "Parameters.h"
#include "Structure.h"
#include <cmath>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class Tree  
{
// Indicamos los atributos privados de la clase
private:
	// Indicamos el tipo de arbol (0: Alambre; 1: Volumétrico; 2: Completo; 3:Con Hojas)
	int type;
	// Indicamos los parametros de generación
	Parameters* parameters;
	// Indicamos la estructura del arbol
	Structure* structure;
	// Matriz para rotaciones o translaciones
	float** matriz;

// Indicamos los metodos publicos
public:
	// Constructor por defecto
	Tree();

	// Destructor de la clase
	virtual ~Tree();

	/****************************************************************************************/
	/* Indicamos los metodos para obtener los valores de los atributos privados de la clase */   
	/****************************************************************************************/
	int getType();
	Parameters* getParameters();
	Structure* getStructure();
	float** getMatriz();
	
	/*******************************************************************************************/
	/* Indicamos los metodos para establecer los valores de los atributos privados de la clase */
	/*******************************************************************************************/
	void setType(int type);
	void setParameters(Parameters* parameters);
	void setStructure(Structure* structure);
	void setMatriz(float** matriz);

	/*******************************************************************************************/
	/* Indicamos los metodos para la generación del arbol                                      */
	/*******************************************************************************************/
	// Funciones para la generación del arbol
	void generate();

	void initial();
	Structure* initialDeviousness(Structure* initial);

	int update(Structure* initial); 
	void clear(Structure* initial);
	void exploit(Structure** lives, int cant);
	Structure** searchLives(Structure* initial, Structure** lives, int* cant);

	void generateChildren(Structure* current);
	Structure* generateDeviousness(Structure* current);
	void generateBranch(Structure* current);
	int print(FILE* fp, Structure* initial);
	int printMPEG4(FILE* fp, Structure* initial, char* texture);

	float randGauss(long *idum);
	float gauss(long *idum);
	float rand1(long *idum);
};

#endif
