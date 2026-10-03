/***************************************************/
/* Fichero: Main.c              Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que se encarga de cargar   */
/*              un fichero en memoria y mantener   */
/*              el control del bucle de control    */
/*              del visualizador                   */
/*                                                 */
/* Dependencias: Fichero.c : Fichero con las fun-  */
/*                   ciones para el control del    */
/*                   fichero que contiene el es-   */
/*                   queleto.                      */
/*               Fichero.h : Fichero que contiene  */
/*                   las cabeceras para el manejo  */
/*                   de fichero.                   */
/*               Mem.c : Fichero que contiene las  */
/*                   funciones de manejo de memo-  */
/*                   ria.                          */
/*               Mem.h : Fichero con las cabeceras */
/*                   de funciones de manejo de me- */
/*                   moria.                        */
/*               Visualizador.c : Fichero con las  */
/*                   funciones necesarias para la  */
/*                   visualización de un esqueleto */
/*               Visualizador.h : Fichero que con- */
/*                   tiene las cabeceras de las    */
/*                   funciones de visualizacion de */
/*                   un esqueleto.                 */
/*               Def.h : Fichero con definiciones  */
/*                   de macros y tipos y estructu- */
/*                   ras de datos necesarios para  */
/*                   definir valores de retorno,   */
/*                   esqueletos, huesos y puntos.  */
/***************************************************/
// Incluimos las librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include "Def.h"
#include "Mem.h"
#include "Visualizador.h"
#include "Fichero.h"

/***************************************************/
/* Funcion: int main(int argc, char* argv[]);      */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Función principal del visualizador.*/
/*                                                 */
/* Inputs: int argc: Entero que indica el número   */
/*                   argumentos de entrada.        */
/*         char* argv[]: Array que contiene los    */
/*                   parametros de entrada.        */
/*                                                 */
/* Outputs: int: Entero utilizado para el control  */
/*               de errores.                       */
/***************************************************/


int main(int argc, char* argv[]) {
	char  nombre_fichero[256];
	char  nombre_fichero_textura[256];
	int i = 0;
	FILE*	fichero = NULL;
	FILE*	fichero_textura = NULL;
	FILE**				array_ficheros[50];
	Arbol* parbol=NULL;
	Arbol 	array_arboles[50];
	FILE *directory = NULL;
	pSkeleton esqueleto = NULL;	
	
	int no_ramas = 0;
	int tipoLectura = 0;
	int flag = 0;
	
	for (i= 0; i<50; i++)
	{
		array_ficheros[i] = NULL;
		array_arboles[i].textura = NULL;
		array_arboles[i].ramas = NULL;
	}

	// Mensaje de bienvenida
	fprintf(stdout,"*************************************************************************\n");
	fprintf(stdout,"*Programa de Visualizacion de				 Arboles Fractales              			*\n");
	fprintf(stdout,"*Diseñado y Programado por: Victor Fernandez-Carbjales Cañete y Javier Molina Vela  *\n");
	fprintf(stdout,"***************************************************************\n\n\n\n");
	// Comprobamos que el número de parametros es correcto, sino indicamos un
	// error
	if (argc < 2) {
		fprintf(stderr,"Error en la llamada al programa, la forma correcta es:\n");
		fprintf(stderr,"[nombre_ejecutable] [fichero] [tipoLectura]\n");
		fprintf(stderr,"[fichero] es un fichero de txt con el formato adecuado\n");
		fprintf(stderr,"[tipoLectura] indica el tipo de fichero de entrada: 0 - Huesos\n");
		fprintf(stderr,"como rectas, 1- Huesos como prismas, 2- Nube de puntos\n");
		fprintf(stderr,"Fin del Progama producido por un ERROR\n");
		return ERR;
	}
i = 0;	
sprintf(nombre_fichero, 			"%s/Arbol%d.fra",argv[1], i);
sprintf(nombre_fichero_textura, 	"%s/Arbol%d.bmp",argv[1], i);

fichero 			= abrirFichero(nombre_fichero,Lectura);
fichero_textura 	= abrirFichero(nombre_fichero_textura,Lectura);
	
while (fichero)
{
	
 	no_ramas =  leerArbol(fichero,fichero_textura,&array_arboles[i]);
	fichero = NULL;
	fichero_textura = NULL;
	i++;
	sprintf(nombre_fichero, "%s/Arbol%d.fra",argv[1], i);
	sprintf(nombre_fichero_textura, 	"%s/Arbol%d.bmp",argv[1], i);
	fichero 			= abrirFichero(nombre_fichero,Lectura);
	fichero_textura 	= abrirFichero(nombre_fichero_textura,Lectura);
}


	glutInit(&argc, argv);
	// Mostramos la ventana inicial del OpenGL
	inicializarVentanaOpenGL(argv[1],esqueleto,&array_arboles);
	// Inicializamos con la visualización
	glutMainLoop();
	
	/*
		Liberamos la memoria de la estructura que corresponda
		Esqueleto o Arbol
	*/
	if (1)
	{
		i = 0;
		while(array_arboles[i].ramas!=NULL)
		{
			if (array_arboles[i].textura)
                memFree(array_arboles[i].textura);
			memFree(array_arboles[i].ramas);
			i++;
		}
		
	}
	else
	{
		// Liberamos la memoria del esqueleto
		// Liberamos los huesos
		for (i = 0; i < esqueleto->numBones; i++) {
			if( esqueleto->Huesos[i]->puntos != NULL) memFree(esqueleto->Huesos[i]->puntos);
			if( esqueleto->Huesos[i]->nube != NULL) memFree(esqueleto->Huesos[i]->nube);
			if( esqueleto->Huesos[i] != NULL) memFree(esqueleto->Huesos[i]);
		}
		if( esqueleto->Huesos != NULL) memFree(esqueleto->Huesos);

		// Liberamos los puntos de los huesos
		for (i = 0; i < esqueleto->numPointBones; i++) {
			if( esqueleto->pointBones[i] != NULL) memFree(esqueleto->pointBones[i]);
		}
		if( esqueleto->pointBones != NULL) memFree(esqueleto->pointBones);

		// Liberamos los puntos de la nube
		for (i = 0; i < esqueleto->numPointNube; i++) {
			if( esqueleto->pointNube[i] != NULL) memFree(esqueleto->pointNube[i]);
		}
		if( esqueleto->pointNube != NULL) memFree(esqueleto->pointNube);

		// Liberamos el propio esqueleto
		if( esqueleto != NULL) memFree(esqueleto);
	}
	// Cerramos el fichero
	cerrarFichero(fichero);

	return OK;
}


