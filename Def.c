/***************************************************/
/* Fichero: Def.c               Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene las funciones */
/*              de impresion de toda estrutura de  */
/*              datos definida en def.h.           */
/*                                                 */
/* Dependencias: Def.h: Fichero con las definición */
/*                      de las estructuras de datos*/  
/***************************************************/
// Incluimos la librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include "Def.h"

/**********************************************/
/* Funcion: void imprimirPunto(pPoint punto); */
/*                                            */
/* Autor: Víctor Fernández-Carbajales Cañete  */
/*                                            */
/* Descripcion: Funcion que imprime los valo- */
/*              res de una estructura punto.  */
/*                                            */
/* Inputs: pPoint punto: El punto a imprimir. */ 
/*                                            */
/* Outputs: No tiene salilda.                 */
/**********************************************/
void imprimirPunto(pPoint punto) {

	// Imprimimos los valores de sus campos
	fprintf(stdout,"X: %f, Y: %f, Z:%f\n",punto->x, punto->y, punto->z);
}

// Funcion que imprime por pantalla el puntos de vista
/***************************************************/
/* Funcion: void imprimirPuntoVista(pPoint punto); */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Funcion que imprime los valores de */
/*              una estructura punto de vista.     */
/*                                                 */
/* Inputs: viewpoint puntoVista: El punto a impri- */
/*                               mir.              */ 
/*                                                 */
/* Outputs: No tiene salilda.                      */
/***************************************************/
void imprimirPuntoVista(viewpoint puntoVista) {

	// Imprimimos los valores de sus campos
	fprintf(stdout,"Orientacion: %f %f %f %f\n",puntoVista.orientacion.x
											   ,puntoVista.orientacion.y
											   ,puntoVista.orientacion.z
											   ,puntoVista.w);

	fprintf(stdout,"Posicion: %f %f %f\n",puntoVista.posicion.x
										 ,puntoVista.posicion.y
										 ,puntoVista.posicion.z);
}

/**********************************************/
/* Funcion: void imprimirHueso(pBone hueso);  */
/*                                            */
/* Autor: Víctor Fernández-Carbajales Cañete  */
/*                                            */
/* Descripcion: Funcion que imprime los valo- */
/*              res de una estructura hueso.  */
/*                                            */
/* Inputs: pBone hueso: El hueso a imprimir.  */ 
/*                                            */
/* Outputs: No tiene salilda.                 */
/**********************************************/
void imprimirHueso(pBone hueso) {
	int i = 0;

	// Imprimimos los valores del hueso
	fprintf(stdout,"El ID del hueso: %d\n",hueso->id_bone);
	// Imprimimos los indices de los puntos
	fprintf(stdout,"Los puntos que los forman son: ");
	for (i = 0; i < hueso->numPuntos; i++) {
		fprintf(stdout,"%d ",hueso->puntos[i]);
	}
	// Imprimimos los indices de los puntos de nube
	fprintf(stdout,"\nLos puntos que forman su nube son:");
	for (i = 0; i < hueso->numNube; i++) {
		fprintf(stdout,"%d ",hueso->nube[i]);
	}
	fprintf(stdout,"\n");
}

/********************************************************/
/* Funcion: void imprimirEsqueleto(pSkeleton esquleto); */
/*                                                      */
/* Autor: Víctor Fernández-Carbajales Cañete            */
/*                                                      */
/* Descripcion: Funcion que imprime los valores de una  */
/*              estructura de esqueleto.                */
/*                                                      */
/* Inputs: pSkeleton esqueleto: El esqueleto a imprimir.*/ 
/*                                                      */
/* Outputs: No tiene salilda.                           */
/********************************************************/
void imprimirEsqueleto(pSkeleton esqueleto) {
	int i = 0;

	// Imprimimos el punto de vista
	fprintf(stdout,"El punto de vista desde donde se visualiza el esqueleto es:\n");
	imprimirPuntoVista(esqueleto->puntoVista);
	fprintf(stdout,"\n");


	// Imprimos la cantidad de hueso
	fprintf(stdout,"\nEl esqueleto esta formado por %d hueso que son:\n",esqueleto->numBones);
	// Imprimimos el esqueleto
	for(i = 0; i < esqueleto->numBones; i++) {
		// Imprimimos los huesos
		imprimirHueso(esqueleto->Huesos[i]);
		fprintf(stdout,"\n");
	}

	// Imprimos la cantidad de puntos que forman los huesos
	fprintf(stdout,"\nEl esqueleto esta formado por %d puntos de hueso que son:\n",esqueleto->numPointBones);
	// Imprimimos los puntos de hueso
	for(i = 0; i < esqueleto->numPointBones; i++) {
		// Imprimimos los puntos de hueso
		fprintf(stdout,"El punto %d: ",i); 
		imprimirPunto(esqueleto->pointBones[i]);
		fprintf(stdout,"\n");
	}

	// Imprimos la cantidad de puntos que forman la nube
	fprintf(stdout,"\nEl esqueleto esta formado por %d puntos de nube que son:\n",esqueleto->numPointNube);
	// Imprimimos los puntos de la nube
	for(i = 0; i < esqueleto->numPointNube; i++) {
		// Imprimimos los puntos de la nube
		fprintf(stdout,"El punto %d: ",i); 
		imprimirPunto(esqueleto->pointNube[i]);
		fprintf(stdout,"\n");
	}

}