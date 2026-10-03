/***************************************************/
/* Fichero: Mem.h               Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene lo necesario  */
/*              para la definición de las funciones*/
/*              de manejo de memoria.              */
/*                                                 */
/* Dependencias: Def.h : Fichero con las defini-   */
/*                       ciones basicas.           */
/***************************************************/

#ifndef Mem
#define Mem
// Librerias incluidas
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Def.h"

/* Indicamos las cabeceras de funciones */

// Funcion encapsulante de la funcion malloc
void* memMalloc(int capacidad);

// Funcion encapsulante de la funcion calloc
void* memCalloc(int cantidad, int espacioUnidad);

// Funcion encapsulante de la funcion realloc
void* memRealloc(void* puntero, int nuevaCapacidad);

// Funcion encapsulante de la funcion free
int memFree(void* puntero);
#endif