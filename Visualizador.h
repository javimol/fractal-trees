/***************************************************/
/* Fichero: Visualizador.h      Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene las cabeceras */
/*              de las funciones para el control   */
/*              del visualizador de OpenGL.        */
/*                                                 */
/* Dependencias: Def.h: Fichero con las definición */
/*                      de las estructuras de datos*/
/***************************************************/

#ifndef Visualizador
#define Visualizador
//Incluimos la librerias necesarias
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <GL\glaux.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include "Def.h"

// Definimos la longitud y ancho de la ventana
#define LADO_HORIZONTAL 800
#define LADO_VERTICAL 800

#define MODO_RECTAS 				0
#define MODO_CILINDROS 				1
#define MODO_CILINDROS_ESFERAS 	2
#define MODO_TEXTURA				3


#define ANCHO_TEXTURA_ARBOL		128
#define ALTO_TEXTURA_ARBOL		128
/* Indicamos los prototipos de las funciones */

// Función que inicializa la ventana principal de OpenGL
void inicializarVentanaOpenGL (char* tituloVentana,pSkeleton esqueleto,Arbol* parbol );

// Función que inicializa la visualización del esqueleto
void visualizar (void);

// Función para el cambio de tamaño de la ventana
void cambioTamagno(GLsizei w, GLsizei h);

// Función que contrala interacción con el ratón
void interaccionRaton(int boton, int estado, int x, int y);

// Función que controla el movimiento del ratón
void movimientoRaton(int x, int y);

// Función que controla las teclas del teclado especiales
void controlTecladoEspecial(int tecla, int x, int y);

// Función que controla las teclas del teclado
void controlTeclado(unsigned char tecla, int x, int y);

// Función que visualiza los huesos como rectas
void visualizarTipo0(pSkeleton esqueleto);

// Función que visualiza los huesos como prismas
void visualizarTipo1(pSkeleton esqueleto);

// Función que visualiza los huesos como prismas y su
// nube de puntos
void visualizarTipo2(pSkeleton esqueleto);

// Función que visualiza su nube de puntos
void visualizarTipo3(pSkeleton esqueleto);

void  visualizaArbol(Arbol* parbolito);
void  visualizaBosque(Arbol* pbosque);
void PintarRecta(float r0x,float r0y,float r0z,float r1x,float r1y,float r1z);
void PintarCilindro(float radio0,float radio1,float h,float r0x,float r0y,float r0z,float Fi,float alfa, int calidad);
#endif
