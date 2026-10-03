/***************************************************/
/* Fichero: Visualizador.c      Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene las funciones */
/*              necesarias para el control del     */
/*              OpenGL y la visualización del es-  */
/*              queleto.                           */ 
/*                                                 */
/* Dependencias: Visualizador.h: Fichero con las   */
/*                      cabeceras de las funciones */
/*                      necesarias.                */
/***************************************************/
//Incluimos la librerias necesarias
#include <math.h>
#include "Visualizador.h"

// Definimos variables globales
int modo_visualizacion 		= MODO_RECTAS;
int calidad_visualizacion		= 0;				//Del 0 al 10 


// Posiciones iniciales
int x0 = 0, y00 = 0;
// Angulos de Rotación
float alpha = 0.0, beta = 0.0;
// Desplazamientos de zoom
float unidadesZoom = 1.0;
// Despalazamientos
float newX = 0.0, newY = 0.0, newZ = 0.0;
// Bandera de acción para el control el raton
// (0) sin accion, (1) rotación, (2) escalado(zoom)
int flag = 0;
// Posicion de la camara en la escena
float posicionCamara[] = {0.0,0.0,0.0,0.0};
float orientacionCamara[] = {0.0,0.0,0.0};
// Almacenamos el esqueleto
pSkeleton esqueletoGL = NULL;

Arbol* pbosqueGL = NULL;

/*****************************************************************/
/* Funcion: void inicializarVentanaOpenGL (char* tituloVentana); */
/*                                                               */
/* Autor: Víctor Fernández-Carbajales Cañete                     */
/*                                                               */
/* Descripcion: Función encargada de inicializar la ventana de   */
/*              OpenGL, como tamaño 250x250, fondo negro, un     */
/*              solo buffer unico y colores RGB.                 */
/*                                                               */
/* Inputs: char* tituloVentana: El nombre del fichero a visuali- */
/*                              zar.                             */
/*         pSkeleton esqueleto: El esqueleto que hay que visuali-*/
/*                              zar.                             */
/*                                                               */ 
/* Outputs: No tiene salida.                                     */
/*****************************************************************/
void inicializarVentanaOpenGL (char* tituloVentana, pSkeleton esqueleto,Arbol* pbosque ) {
	int retvalue = 0;
	GLfloat light_amb[] = { 1.0, 1.0, 1.0, 1.0 };
	posicionCamara[0] = 0;
	posicionCamara[1] = 100;
	posicionCamara[2] = 310;
	posicionCamara[3] = 0;
	orientacionCamara[0] = 0;
	orientacionCamara[1] = 0;
	orientacionCamara[2] = 1;
	esqueletoGL = esqueleto;
	pbosqueGL = pbosque;

	// Inicializamos el modo de visualización, con doble buffer, 
	// con colores RGB y algoritmo de profundidad
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// Inicializamos el tamaño de la ventana
	glutInitWindowSize(LADO_HORIZONTAL,LADO_VERTICAL);
	// Indicamos la posición inicial de la ventana
	glutInitWindowPosition(100,100);
	// Indicamos el titulo de la ventana con el nombre del fichero y
	// creamos la ventana
	glutCreateWindow(tituloVentana);
	// Indicamos la función de visualización
	glutDisplayFunc(visualizar);
	// Función que controla el cambio de tamaño ventana
	glutReshapeFunc(cambioTamagno);
	// Indicamos la función que controla el ratón
	glutMouseFunc(interaccionRaton);
	glutMotionFunc(movimientoRaton);
	// Indicamos la función que controla el teclado
	glutSpecialFunc(controlTecladoEspecial);
	glutKeyboardFunc(controlTeclado);
	
	glEnable(GL_DEPTH_TEST);
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );
	glLightfv( GL_LIGHT0, GL_AMBIENT, light_amb );
	
	glLightf( GL_LIGHT1, GL_SPOT_EXPONENT, 0 );
	//glEnable( GL_COLOR_MATERIAL ); 


	
	
	
}

/*****************************************************************/
/* Funcion: void visualizar(void);                               */
/*                                                               */
/* Autor: Víctor Fernández-Carbajales Cañete                     */
/*                                                               */
/* Descripcion: Función que se llama para crear la visualización.*/
/*                                                               */
/* Inputs: No tiene argumentos de entrada.                       */
/*                                                               */ 
/* Outputs: No tiene salida.                                     */
/*****************************************************************/
void visualizar (void) {
	// Limpiamos el buffer antes de visuaizar
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Cargamos la matriz de projección
	glMatrixMode(GL_PROJECTION);
	// La inicializamos
	glLoadIdentity();
	// Indicamos la matriz de perspectiva
	gluPerspective(-100.0f,1.0f,1.0f,-500.f);
	// Pasamos a la matriz de modelo
	glMatrixMode(GL_MODELVIEW);
	// La inicializamos
	glLoadIdentity();
	// Indicamos el punto de vista
#if 0
	posicionCamara[0] = posicionCamara[0]+newX;
	posicionCamara[1] = posicionCamara[1]+newY;
	posicionCamara[2] = 	posicionCamara[2]+newZ;
	newX = 0;
	newY = 0;
	newZ = 0;
	#endif
	
	gluLookAt(posicionCamara[0]+newX,posicionCamara[1]+newY,posicionCamara[2]+newZ,
		      0.0f,0.0f,0.0f,
			  orientacionCamara[0],orientacionCamara[1],orientacionCamara[2]);
	// Colocamos la escena según lo indicado por el usuario
	// Respecto al angulo de rotación
	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
	// Respecto al zoom elegido
	if (unidadesZoom >= 0.1) {
		glScalef(unidadesZoom, unidadesZoom, unidadesZoom);
	}
	else {
		glScalef(0.1, 0.1, 0.1);
		unidadesZoom = 0.1;
	}
	// Pintamos los ejes de coordenadas
	glLineWidth (2);
	glBegin (GL_LINES);
	// Rojo el de las x's
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1000.0f,0.0f,0.0f);
	// Verde el de las y's
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,1000.0f,0.0f);
	// Azul el de las z's
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,1000.0f);
	glEnd ();
	// Indicamos el color gris de nuevo
	glColor3f(0.5f,0.5f,0.5f);
	glLineWidth (1);
	if (pbosqueGL)
	{
        visualizaBosque(pbosqueGL);
	}
	else
	{
		// Visualizamos el esqueleto
		if (esqueletoGL->tipo == Recta) {
			visualizarTipo0(esqueletoGL);
		}
		else if (esqueletoGL->tipo == Prisma) {
			visualizarTipo1(esqueletoGL);
		}
		else if (esqueletoGL->tipo == Nube) {
			visualizarTipo2(esqueletoGL);
		}
		else if (esqueletoGL->tipo == Puntos) {
			visualizarTipo3(esqueletoGL);
		}
	}
	// Forzamos la visualización
	glFlush();
	// Cambiamos el buffer.
	glutSwapBuffers();
	
}

/*****************************************************************/
/* Funcion: void cambioTamagno(GLsizei w, GLsizei h);            */
/*                                                               */
/* Autor: Víctor Fernández-Carbajales Cañete                     */
/*                                                               */ 
/* Descripcion: Función que se llama para reajustar la ventana   */
/*              cuando se incrementa/decrementa la ventana de    */
/*              visualización.                                   */
/*                                                               */
/* Inputs: GLsizei w: El ancho de la ventana.                    */
/*         GLsizei h: El alto de la ventana.                     */
/*                                                               */ 
/* Outputs: No tiene salida.                                     */
/*****************************************************************/
void cambioTamagno(GLsizei w, GLsizei h) {

	// Prevenimos una division por cero cuando la ventana es muy pequeña
	if (h == 0) {
		h = 1;
	}

	// Ajustamos la vista al ancho completo de la ventana y
	// centramos el viewport
	glViewport(0,0,w,h);

	// Reinicia el sistema de coordenadas antes de modificarlo
	glLoadIdentity();

	// Definimos el espacio de trabajo
	gluPerspective(20.0f,(float)w/(float)h,1.0f,10.f);
}


/***********************************************************************/
/* Funcion: void interaccionRaton(int boton, int estado, int x, int y);*/
/*                                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete                           */
/*                                                                     */
/* Descripcion: Función que se llama cuando utilizamos alguno de los   */
/*              botones del raton.                                     */
/*                                                                     */
/* Inputs: int boton:  Indica el boton del raton que interacciona.     */
/*         int estado: Indica si el boton es pulsado o levantado.      */
/*         int x:      Indica la posición del puntero del raton en la  */
/*                     interacción.                                    */
/*         int y:      Indica la posición del puntero del raton en la  */
/*                     interacción.                                    */      
/*                                                                     */ 
/* Outputs: No tiene salida.                                           */
/***********************************************************************/
void interaccionRaton(int boton, int estado, int x, int y) {
	// Si utilizamos el botón derecho y esta pulsado
	if (( boton == GLUT_LEFT_BUTTON) & (estado == GLUT_DOWN)) {
		// Actualizamos los valores iniciales
		x0 = x;
		y00 = y;
		flag = 1;
	}
	else if ((boton == GLUT_RIGHT_BUTTON) & (estado == GLUT_DOWN)) {
		x0 = x;
		y00 = y;
		flag = 2;
	}
}

/********************************************************************/
/* Funcion: void movimientoRaton(int x, int y);                     */
/*                                                                  */
/* Autor: Víctor Fernández-Carbajales Cañete                        */
/*                                                                  */
/* Descripcion: Función que se llama cuando movemos el ratón dentro */
/*              de la ventana.                                      */
/*                                                                  */
/* Inputs: int x: Indica la posición del puntero del raton en la    */
/*                interacción.                                      */
/*         int y: Indica la posición del puntero del raton en la    */
/*                interacción.                                      */
/*                                                                  */
/* Outputs: No tiene salida.                                        */
/********************************************************************/
void movimientoRaton(int x, int y){
	// Calculamos los angulos de rotación según el desplazamiento del
	// raton
	if (flag == 1) {
		alpha = (alpha + ( y - y00));
		beta = (beta + (x - x0));
	}
	// Realizamos el zoom
	else if (flag == 2) {
		unidadesZoom = unidadesZoom + (((float)y - (float)y00)/100);
	}
	// Colocamos de nuevo los puntos iniciales
	x0 = x;
	y00 = y;
	// Llamamos a visualizar
	glutPostRedisplay();
}

/********************************************************************/
/* Funcion: void controlTecladoEspecial(int tecla, int x, int y);   */
/*                                                                  */
/* Autor: Víctor Fernández-Carbajales Cañete                        */
/*                                                                  */
/* Descripcion: Función que se llama cuando pulsamos una tecla      */
/*              especial en el teclado.                             */
/*                                                                  */
/* Inputs: int tecla: Indica la tecla especial pulsada.             */
/*         int x:     Indica la posición del puntero del raton en   */
/*                    la interacción.                               */
/*         int y:     Indica la posición del puntero del raton en   */
/*                    la interacción.                               */
/*                                                                  */
/* Outputs: No tiene salida.                                        */
/********************************************************************/
void controlTecladoEspecial(int tecla, int x, int y) {
	switch (tecla) {
		// Si quiere un desplazamiento a la izquierda
		// reducimos en 1 las unidades en el eje de las exis
	case GLUT_KEY_LEFT:
			newX = newX - 0.1;
			break;
		// Si quiere un desplazamiento a la derecha
		// aumentamos en 1 las unidades en el eje de las exis
	case GLUT_KEY_RIGHT:
			newX = newX + 0.1;
			break;
		// Si quiere un desplazamiento hacia arriba
		// aumentamos en 1 las unidades en el eje de las ys
	case GLUT_KEY_UP:
			newY = newY + 0.1;
			break;
		// Si quiere un desplazamiento hacia arriba
		// reducimos en 1 las unidades en el eje de las ys
	case GLUT_KEY_DOWN:
			newY = newY - 0.1;
			break;
		default:
			return;
	}

	// Llamamos a visualizar
	glutPostRedisplay();
}

/********************************************************************/
/* Funcion: void controlTeclado(unsigned char tecla, int x, int y); */
/*                                                                  */
/* Autor: Víctor Fernández-Carbajales Cañete                        */
/*                                                                  */
/* Descripcion: Función que se llama cuando pulsamos una tecla      */
/*              en el teclado.                                      */
/*                                                                  */
/* Inputs: unsigned char tecla: Indica la tecla especial pulsada.   */
/*         int x:     Indica la posición del puntero del raton en   */
/*                    la interacción.                               */
/*         int y:     Indica la posición del puntero del raton en   */
/*                    la interacción.                               */
/*                                                                  */
/* Outputs: No tiene salida.                                        */
/********************************************************************/
void controlTeclado(unsigned char tecla, int x, int y){
	switch (tecla) {
		// Si quiere un desplazamiento hacia delante
		// reducimos en 1 las unidades en el eje de las zetas
	case'0':	//Con rectas
		modo_visualizacion = MODO_RECTAS;
		calidad_visualizacion = 0;
		glDisable(GL_TEXTURE_2D);
		break;
	case '1':	//Con secciones cónicas
		modo_visualizacion = MODO_CILINDROS;
		calidad_visualizacion = 1;
		glDisable(GL_TEXTURE_2D);
		break;
	case '2':	//Con secciones cónicas y esferas
		modo_visualizacion = MODO_CILINDROS_ESFERAS;
		calidad_visualizacion = 1;
		glDisable(GL_TEXTURE_2D);
		break;
	case '3':
		modo_visualizacion = MODO_TEXTURA;
		calidad_visualizacion = 1;
		 glEnable(GL_TEXTURE_2D);
	  	break;
	case '4':
	  break;
	case '+':	//Mas cualidad
		if (modo_visualizacion != MODO_RECTAS)
        {
			calidad_visualizacion = calidad_visualizacion +1;
		}
		else 
		{
			modo_visualizacion = MODO_CILINDROS;
			calidad_visualizacion = 1;
		}
	  break;
	case '-':	//Menos calidad
		if (modo_visualizacion != MODO_RECTAS)
        {
			calidad_visualizacion = calidad_visualizacion -1;
		}
		if (calidad_visualizacion == 0)
		{
			modo_visualizacion = MODO_RECTAS;
		}
	  break;
	default:
		return;
	}
#if 0
	case '+':
			newZ = newZ - 0.1;
			break;
		// Si quiere un desplazamiento hacia atras
		// aumentamos en 1 las unidades en el eje de las zetas
	case '-':
			newZ = newZ + 0.1;
			break;
		default:
			return;
	}
#endif
	// Llamamos a visualizar
	glutPostRedisplay();
}

/*******************************************************/
/* Funcion: void visualizarTipo0(pSkeleton esqueleto); */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripcion: Función que visualiza el esqueleto con */
/*              huesos como rectas.                    */
/*                                                     */
/* Inputs: pSkeleton esqueleto: El esqueleto a visua-  */
/*                              lizar.                 */
/*                                                     */
/* Outputs: No tiene salida.                           */
/*******************************************************/
void visualizarTipo0(pSkeleton esqueleto) {
	int i = 0;
	int inicio = -1, fin = -1;

	// Indicamos el color verde
	glColor3f(0.2f,1.0f,0.2f);
	// Indicamos que vamos a dibujar lineas
	glLineWidth (1);
	glBegin (GL_LINES);
	// Por cada hueso
	for(i = 0; i < esqueleto->numBones; i++) {
		if (esqueleto->Huesos[i]->numPuntos > 0) {
			inicio = esqueleto->Huesos[i]->puntos[0];
			fin  = esqueleto->Huesos[i]->puntos[1];
			glVertex3f(esqueleto->pointBones[inicio]->x
				      ,esqueleto->pointBones[inicio]->y
					  ,esqueleto->pointBones[inicio]->z);
			glVertex3f(esqueleto->pointBones[fin]->x
				      ,esqueleto->pointBones[fin]->y
					  ,esqueleto->pointBones[fin]->z);
		}
	}
	// Fin
	glEnd ();
}

/*******************************************************/
/* Funcion: void visualizarTipo1(pSkeleton esqueleto); */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripcion: Función que visualiza el esqueleto con */
/*              huesos como prismas.                   */
/*                                                     */
/* Inputs: pSkeleton esqueleto: El esqueleto a visua-  */
/*                              lizar.                 */
/*                                                     */
/* Outputs: No tiene salida.                           */
/*******************************************************/
void visualizarTipo1(pSkeleton esqueleto) {
	int i = 0, j = 0;
	int inicio = -1, fin= -1;

	// Indicamos el color verde
	glColor3f(0.2f,1.0f,0.2f);
	// Indicamos que vamos a dibujar lineas
	glLineWidth (1);
	glBegin (GL_LINES);
	// Por cada hueso
	for(i = 0; i < esqueleto->numBones; i++) {
		if (esqueleto->Huesos[i]->numPuntos > 0) {
			// Dibujamos la primera tapa del prisma
			for ( j = 0; j < 3; j++) {
				inicio = esqueleto->Huesos[i]->puntos[j];
				fin = esqueleto->Huesos[i]->puntos[j+1];
				glVertex3f(esqueleto->pointBones[inicio]->x
					      ,esqueleto->pointBones[inicio]->y
						  ,esqueleto->pointBones[inicio]->z);
				glVertex3f(esqueleto->pointBones[fin]->x
					      ,esqueleto->pointBones[fin]->y
						  ,esqueleto->pointBones[fin]->z);
			}
			inicio = esqueleto->Huesos[i]->puntos[0];
			fin = esqueleto->Huesos[i]->puntos[3];
			glVertex3f(esqueleto->pointBones[inicio]->x
				      ,esqueleto->pointBones[inicio]->y
					  ,esqueleto->pointBones[inicio]->z);
			glVertex3f(esqueleto->pointBones[fin]->x
				      ,esqueleto->pointBones[fin]->y
					  ,esqueleto->pointBones[fin]->z);
			// Dibujamos la segunda tapa del primas
			for ( j = 0; j < 3; j++) {
				inicio = esqueleto->Huesos[i]->puntos[j+4];
				fin = esqueleto->Huesos[i]->puntos[j+5];
				glVertex3f(esqueleto->pointBones[inicio]->x
					      ,esqueleto->pointBones[inicio]->y
						  ,esqueleto->pointBones[inicio]->z);
				glVertex3f(esqueleto->pointBones[fin]->x
					      ,esqueleto->pointBones[fin]->y
						  ,esqueleto->pointBones[fin]->z);
			}
			inicio = esqueleto->Huesos[i]->puntos[4];
			fin	= esqueleto->Huesos[i]->puntos[7];
			glVertex3f(esqueleto->pointBones[inicio]->x
				      ,esqueleto->pointBones[inicio]->y
					  ,esqueleto->pointBones[inicio]->z);
			glVertex3f(esqueleto->pointBones[fin]->x
				      ,esqueleto->pointBones[fin]->y
					  ,esqueleto->pointBones[fin]->z);
			// Unimos las tapas
			for ( j = 0; j < 4; j++) {
				inicio = esqueleto->Huesos[i]->puntos[j];
				fin = esqueleto->Huesos[i]->puntos[j+4];
				glVertex3f(esqueleto->pointBones[inicio]->x
					      ,esqueleto->pointBones[inicio]->y
						  ,esqueleto->pointBones[inicio]->z);
				glVertex3f(esqueleto->pointBones[fin]->x
					      ,esqueleto->pointBones[fin]->y
						  ,esqueleto->pointBones[fin]->z);
			}
		}
	}
	// Fin
	glEnd ();
}

/*******************************************************/
/* Funcion: void visualizarTipo2(pSkeleton esqueleto); */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripcion: Función que visualiza el esqueleto con */
/*              huesos como prismas con nube.          */
/*                                                     */
/* Inputs: pSkeleton esqueleto: El esqueleto a visua-  */
/*                              lizar.                 */
/*                                                     */
/* Outputs: No tiene salida.                           */
/*******************************************************/
void visualizarTipo2(pSkeleton esqueleto) {
	int i = 0;
	// Visualizamos los huesos como prismas
	visualizarTipo1(esqueleto);
	// Indicamos el color rojo
	glColor3f(1.0f,0.0f,0.0f);
	// Indicamos que vamos a dibujar lineas
	glBegin (GL_POINTS);
	// Por cada punto de nube
	for(i = 0; i < esqueleto->numPointNube; i++) {
		glVertex3f(esqueleto->pointNube[i]->x
			      ,esqueleto->pointNube[i]->y
				  ,esqueleto->pointNube[i]->z);
	}
	// Fin
	glEnd ();
}

/*******************************************************/
/* Funcion: void visualizarTipo3(pSkeleton esqueleto); */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripcion: Función que visualiza el esqueleto con */
/*              huesos como prismas con nube.          */
/*                                                     */
/* Inputs: pSkeleton esqueleto: El esqueleto a visua-  */
/*                              lizar.                 */
/*                                                     */
/* Outputs: No tiene salida.                           */
/*******************************************************/
void visualizarTipo3(pSkeleton esqueleto) {
	int i = 0;
	// Indicamos el color rojo
	glColor3f(1.0f,0.0f,0.0f);
	// Indicamos que vamos a dibujar lineas
	glBegin (GL_POINTS);
	// Por cada punto de nube
	for(i = 0; i < esqueleto->numPointNube; i++) {
		glVertex3f(esqueleto->pointNube[i]->x
			      ,esqueleto->pointNube[i]->y
				  ,esqueleto->pointNube[i]->z);
	}
	// Fin
	glEnd ();
}

void  visualizaArbol(Arbol *parbolito)
{
	int i= 0;
	void* textura = NULL;
	GLuint texture = 0;
	long  tamanio_textura = 0;
	float h = 0;
	float Fi = 0;
	float alfa = 0;
	float x	= 0;
	float y	= 0;
	float z	= 0;

   	if (!parbolito)
		return;

	x = parbolito->traslacion_horizontal_x;
	z = parbolito->traslacion_horizontal_z;
	
	if ((parbolito->textura != NULL)&& (modo_visualizacion == MODO_TEXTURA))
	{
		textura			= parbolito->textura;
		tamanio_textura	= parbolito->tamanio_textura;		
		//glClearColor(0,0,0,0);
		// allocate a texture name
		glGenTextures( 1, &texture );

		// select our current texture
		glBindTexture( GL_TEXTURE_2D, texture );

		// select modulate to mix texture with color for shading
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                 GL_LINEAR_MIPMAP_NEAREST );
		// when texture area is large, bilinear filter the original
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// the texture wraps over at the edges (repeat)
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		// build our texture mipmaps
				
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, ANCHO_TEXTURA_ARBOL, ALTO_TEXTURA_ARBOL,
               GL_RGB, GL_UNSIGNED_BYTE, textura );

		
	}
	
	
	glTranslatef(x, y,z);		//Traslado el arbol horizontalmente
	
	while(parbolito->ramas[i].indice_rama != -1)
		{
			i++;
		}
		
	while (1)
	{		
		h = parbolito->ramas[i].h;
		Fi = parbolito->ramas[i].Fi;
		alfa = parbolito->ramas[i].alfa;
		if (modo_visualizacion == MODO_RECTAS)
			//if (TRUE)
		{
			PintarRecta(
				parbolito->ramas[i].r0x,
				parbolito->ramas[i].r0y,
				parbolito->ramas[i].r0z,
				parbolito->ramas[i].r0x + h*sin(Fi*PI/180)*sin(alfa*PI/180),
				parbolito->ramas[i].r0y + h*cos(Fi*PI/180),
				parbolito->ramas[i].r0z + h*sin(Fi*PI/180)*cos(alfa*PI/180)			
				);
		}

		else if (modo_visualizacion != MODO_RECTAS)
		{			
			PintarCilindro(
				parbolito->ramas[i].D1/2,
				parbolito->ramas[i].D2/2,
				parbolito->ramas[i].h,
				parbolito->ramas[i].r0x,
				parbolito->ramas[i].r0y,
				parbolito->ramas[i].r0z,
				parbolito->ramas[i].Fi,
				parbolito->ramas[i].alfa,
				calidad_visualizacion
				);
		}		
		
		//if (parbolito->ramas[i].indice_rama == -1)
		if (i==0)
			break;
		//i++;
		i--;
	}

	glTranslatef(-x, -y,-z); //Recoloco los ejes, con un desplazamiento horizontal
	if ((parbolito->textura != NULL)&& (modo_visualizacion == MODO_TEXTURA))
	{
		glDeleteTextures(1,&texture);
	}
	return;
}

void  visualizaBosque(Arbol* pbosque)
{
	int i = 0;
	float x = 0;
	float y = 0;
	float z = 0;
	float r = 0;
	int distancia_camara = 0;
	int distancia_arbol  = 0;
	int alfa  = 0;	//En grados

	
	distancia_camara  = sqrt(pow(posicionCamara[0],2) + pow(posicionCamara[1],2) + pow(posicionCamara[2],2));
	
	while (pbosque[i].ramas != NULL)
	{
		if ((pbosque[i].traslacion_horizontal_x	== 0) && (pbosque[i].traslacion_horizontal_z == 0))
		{
			distancia_camara = sqrt(pow(posicionCamara[0],2) + pow(posicionCamara[2],2));
			r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
			distancia_arbol = r*distancia_camara/2;
			alfa =  rand();
			alfa = alfa % 360;
			pbosque[i].traslacion_horizontal_x	= distancia_arbol*sin(alfa*PI/180);
			pbosque[i].traslacion_horizontal_z	= distancia_arbol*cos(alfa*PI/180);			
		}
		visualizaArbol(&pbosque[i]);
		i++;
	}
}
void PintarRecta(float r0x,float r0y,float r0z,float r1x,float r1y,float r1z)
{
	glLineWidth (2);
	glBegin (GL_LINES);

	glVertex3f(r0x,r0y,r0z);			
	glVertex3f(r1x,r1y,r1z);
	
	glEnd ();
	return;
}
void PintarCilindro(float radio0,float radio1,float h,float r0x,float r0y,float r0z,float Fi,float alfa, int calidad)
{
	GLUquadric* quad = NULL;
	GLUquadric* quad2 = NULL;
	GLint slices 	= 0;
	GLint stacks 	= 0;
	GLint stacks_esfera 	= 0;
	
	
	//calidad va a valer entre 1 y 10, si fuera cero habríamos pasado a MODO_RECTAS
	
		slices = 3 + (calidad-1)*2;
		stacks_esfera = 3+ (calidad-1)*3;
		stacks = 1;

	
	glPushMatrix();			//Almaceno la matriz original


	glTranslatef(r0x, r0y,r0z);
	glRotatef (alfa -90, 0, 1, 0);
		
	glRotatef (Fi , 0, 0, -1);	
	
	glRotatef (90 , -1, 0, 0);

	quad = gluNewQuadric();
       gluQuadricTexture(quad,GL_TRUE);
	
    // gluQuadricOrientation(quad, GLU_INSIDE);
      if (modo_visualizacion==MODO_TEXTURA)
	{	
	 glEnable(GL_TEXTURE_2D);
	}

     gluCylinder (quad , radio0 , radio1 , h,  slices , stacks);
	


	
	
	if ((modo_visualizacion != MODO_CILINDROS)&&(radio1 > 0))
	{
		glTranslatef(0, 0,h);
		quad2 = gluNewQuadric();
		gluQuadricTexture(quad2,GL_TRUE);
    		gluSphere   (quad2, radio1, slices, stacks_esfera);
	}
     

#if 0

If texturing is turned on (with gluQuadricTexture): texture coordinates are generated so that t ranges linearly
from 0.0 at z = 0 to 1.0 at z = height; and s ranges from 0.0 at the positive y-axis, to 0.25 at the positive x-axis,
to 0.5 at the negative y-axis, to 0.75 at the positive x-axis, and back to 1.0 at the positive y-axis.
	void gluQuadricTexture(
  	GLUquadricObj *quadObject,
  	GLboolean textureCoords
	);

void gluQuadricNormals(
  GLUquadricObj *qobj,
  GLenum normals
);


The glDrawPixels function writes a block of pixels to the framebuffer.

void glDrawPixels(
  GLsizei width,
  GLsizei height,
  GLenum format,
  GLenum type,
  const GLvoid *pixels
);


The glCopyTexImage2D function copies pixels from the framebuffer into a two-dimensional texture image.

void glCopyTexImage2D(
  GLenum target,
  GLint level,
  GLenum internalFormat,
  GLint x,
  GLint y,
  GLsizei width,
  GLsizei height,
  GLint border
);


The glGetTexImage function returns a texture image.

void glGetTexImage(
  GLenum target,
  GLint level,
  GLenum format,
  GLenum type,
  GLvoid *pixels
);
#endif

	glPopMatrix();	//Recupero la matriz original
	

	return;
}
