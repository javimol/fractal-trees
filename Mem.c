/***************************************************/
/* Fichero: Mem.c               Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene las funciones */
/*              de manejo de memoria.              */
/*                                                 */
/* Dependencias: Mem.h : Fichero con las cabeceras */
/*                       de las funciones de mane- */
/*                       jo de memoria..           */
/***************************************************/

// Librerias incluidas
#include "Mem.h"
/***************************************************/
/* Funcion: void* memMalloc(int capacidad);        */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Función encapsulante de malloc.    */
/*                                                 */
/* Inputs: int capacidad: Entero que indica la     */
/*                   cantidad de memoria a reser-  */
/*                   var.                          */
/*                                                 */
/* Outputs: void*: Puntero a la zona de memoria    */
/*                 obtenida, Null en caso de error.*/
/***************************************************/
void* memMalloc(int capacidad) {
	void *puntero = NULL;

	// Generamos la memoria indicada
	puntero = malloc(capacidad);
	// Comprobamos que se reservo correctamente, en otro caso indicamos error
	if(puntero == NULL) {
		fprintf(stderr,"Error en la obtención de memoria en la funcion memMalloc\n");
		return puntero;
	}
	return puntero;
}

/**************************************************************/
/* Funcion: void* memCalloc(int cantidad, int espacioUnidad); */
/*                                                            */
/* Autor: Víctor Fernández-Carbajales Cañete                  */
/*                                                            */
/* Descripcion: Función encapsulante de la funcion calloc.    */
/*                                                            */
/* Inputs: int cantidad: Entero que indica el número de uni-  */
/*                       dades de memoria a reservar.         */
/*         int espacionUnidad: Entero que indica el espacio   */
/*                       de memoria que ocupa cada unidad.    */
/*                                                            */
/* Outputs: void*: Puntero a la zona de memoria obtenida.     */
/*                 Null en caso de error.                     */
/**************************************************************/
void* memCalloc(int cantidad, int espacioUnidad) {
	void *puntero = NULL;

	// Generamos la memoria indicada
	puntero = calloc(cantidad, espacioUnidad);
	// Comprobamos que se reservo correctamente, en otro caso indicamos error
	if(puntero == NULL) {
		fprintf(stderr,"Error en la obtención de memoria en la funcion memCalloc\n");
		return puntero;
	}
	return puntero;
}

/****************************************************************/
/* Funcion: void* memRealloc(void* puntero, int nuevaCapacidad);*/
/*                                                              */
/* Autor: Víctor Fernández-Carbajales Cañete                    */
/*                                                              */
/* Descripcion: Función encapsulante de la funcion realloc.     */
/*                                                              */
/* Inputs: void* puntero: Puntero a la zona de memoria a redi-  */
/*                        mensionar.                            */
/*         int nuevaCapacidad: entero que indica la nueva capa- */
/*                        cidad del puntero.                    */
/*                                                              */
/* Outputs: void*: Puntero a la zona de memoria obtenida. Null  */
/*                 en caso de error.                            */
/****************************************************************/
void* memRealloc(void* puntero, int nuevaCapacidad) {
	void *punteroNuevo = NULL;

	// Recolocamos la memoria necesaria
	punteroNuevo = realloc(puntero,nuevaCapacidad);
    // Comprobamos la reserva de dicha memoria
	if(punteroNuevo == NULL) {
		fprintf(stderr,"Error en la obtención de memoria en la funcion memRealloc\n");
		return punteroNuevo;
	}
	return punteroNuevo;
}

/***************************************************/
/* Funcion: int memFree(void* puntero);            */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Función encapsulante de free       */
/*                                                 */
/* Inputs: void* puntero: Puntero de memoria a li- */
/*                        berar.                   */
/*                                                 */
/* Outputs: int: Entero utilizado para el control  */
/*               de errores. ERR en caso de error  */
/*               OK en otro caso.                  */
/***************************************************/
int memFree(void* puntero) {
	int resultado = OK;

	// Liberamos la memoria apuntada por el puntero
	free(puntero);
	puntero = NULL;
	// Controlamos los posibles errores
	if (resultado == -1) {
		fprintf(stderr,"Error en la liberación de memoria en la funcion memFree\n");
		return resultado;
	}
	return resultado;
}

