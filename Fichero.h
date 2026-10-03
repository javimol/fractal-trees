/***************************************************/
/* Fichero: Fichero.h           Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene las cabeceras */
/*              de funciones de manejo de ficheros.*/
/*                                                 */
/* Dependencias: Def.h: Fichero con las definicio- */
/*                      nes globales necesarias    */
/*               Mem.h: Fichero que contiene las   */
/*                      cabeceras de las funciones */
/*                      de manejo de memoria.      */
/***************************************************/

#ifndef Fichero
#define Fichero
// Incluimos las librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include "Def.h"
#include "Mem.h"

/* Indicamos las cabeceras de funciones */

// Funcion que se encarga de abrir un fichero
FILE* abrirFichero(char* nombreFichero, int tipoApertura);

// Funcion que se encarga de cerrar un fichero
int cerrarFichero(FILE* fichero);

// Funcion principal de lectura de ficheros de esqueleto
pSkeleton leerEsqueleto(FILE* fichero, int tipoLectura);

//Funcion de lectura de un fichero de arbol. Devuelve el número de ramas
int leerArbol(FILE* fichero, FILE* fichero_textura,Arbol* parbol);	


// Funcion para la lectura de un hueso
int leerHueso(FILE* fichero, pSkeleton esqueleto, int tipoLectura, int indice);

// Funcion para la lectura de puntos
int leerPunto(FILE* fichero, pSkeleton esqueleto, int tipoLectura, int indice, int tipo);

// Funcion para la lectura del punto de vista
int leerPuntoVista(FILE* fichero, pSkeleton esqueleto);

#endif

