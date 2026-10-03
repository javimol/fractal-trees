/***************************************************/
/* Fichero: Def.h               Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene las macros,   */
/*              tipos y estructuras de datos nece- */
/*              sarios.                            */
/*                                                 */
/* Dependencias: No tiene dependencias externas    */  
/***************************************************/

#ifndef Def
#define Def

// Definimos el valor de error para los controles de
// errores
#define ERR -1;
// Definimos el valor de exito para los controles de
// errores
#define OK 0;

// Definimos Tipos de Lectura
#define Recta 0
#define Prisma 1
#define Nube 2
#define Puntos 3

// Definimos Tipos Apertura
#define Escritura 0
#define Lectura 1
#define Reescritura 2
#define PI 3.14159
// Definimos la estructura de datos que almacena un 
// puntos (en el espacion 3D).
typedef struct Points {
	float x; // Coordenada x
	float y; // Coordenada y
	float z; // Coordenada z
} point, *pPoint;

// Definimos la estructura de datos que almacena un hueso
typedef struct Bones {
	int id_bone;   // Identificador del hueso
	int numPuntos; // Entero con el numero de puntos que 
	               // forma el hueso
	int numNube;   // Entero con el numero de puntos que 
	               // forma la nube del hueso
	int *puntos;   // Array con los indices de los puntos 
	               // del hueso
	int *nube;     // Array con los indices de los puntos 
	               // de la piel que recubre al hueso
} bone, *pBone;

// Definimos la estructura de datos para el punto de vista
typedef struct Viewpoint {
	point posicion;    // Indica la posición del punto de 
	                   // vista
	point orientacion; // La orientación del punto de vista
	float w;           // Indica si el punto de vista esta o
	                   // no en el infinito
} viewpoint, *pViewpoint;

// Definimos la estructura de datos que almacena el
// esqueleto
typedef struct Skeleton {
	int tipo;              // Indica el tipo de esqueleto (0) Rectas,
	                       // (1) Prisma y (2) con nube
	int numBones;          // Indica el número de huesos
	int numPointBones;     // Indica el número de puntos 
	                       // de los huesos
	int numPointNube;      // Indica el número de puntos de
	                       // la piel que recubre el esque-
					       // leto
	int numLight;          // Indica el número de luces que
	                       // iluminan el esqueleto
	pBone* Huesos;         // Array con los huesos del es-
	                       // queleto
	pPoint* pointBones;    // Array de puntos de los huesos
	pPoint* pointNube;     // Array de puntos de la piel
	viewpoint puntoVista;  // Puntos de vista para ver el
	                       // esqueleto.  
} skeleton, *pSkeleton;

typedef struct
{
	int   indice_rama;	//Si es igual a -1, es la última rama
	float D1;			//Diametro base
	float D2;			//Diametro tapa
	float h;			//Longitud de la rama
	float Fi;			//Ángulo con respecto  a la vertical (coordenadas esféricas)
	float alfa;		//Ángulo con respecto al eje x	    (coordenadas esféricas o cilindricas)
	float r0x;		//Coordenadas del pto central de la base de la rama.
	float r0y;
	float r0z;		
} Coordenadas_Rama;

typedef struct
{
	void* 				textura;
	long					tamanio_textura;
	Coordenadas_Rama*	ramas;
	float 				traslacion_horizontal_x;
	float 				traslacion_horizontal_z;
} Arbol;

/* Indicamos los prototipos de las funciones */

// Funcion que imprime por pantalla el puntos de vista
void imprimirPuntoVista(viewpoint puntoVista);

// Funcion que imprime por pantalla un punto
void imprimirPunto(pPoint punto);

// Funcion que imprime por pantalla un hueso
void imprimirHueso(pBone hueso);

// Funcion que imprime por pantalla un esquleto
void imprimirEsqueleto(pSkeleton esqueleto);

#endif