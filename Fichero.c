/***************************************************/
/* Fichero: Fichero.c           Fecha: 29-12-2004  */
/*                                                 */
/* Autor: Víctor Fernández-Carbajales Cañete       */
/*                                                 */
/* Descripcion: Fichero que contiene las funciones */
/*              de manejo de fichero de esquele-   */
/*              to.                                */ 
/*                                                 */
/* Dependencias: Fichero.h : Fichero con las cabe- */
/*                       ceras de las funciones de */
/*                       manejo de fichero.        */
/***************************************************/
// Librerias incluidas
#include "Fichero.h"

/***********************************************************************/
/* Funcion: FILE* abrirFichero(char* nombreFichero, int tipoApertura); */
/*                                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete                           */
/*                                                                     */
/* Descripcion: Función encargada de abrir un fichero de esqueleto.    */
/*                                                                     */
/* Inputs: char* nombreFichero: El nombre del fichero a abrir.         */
/*         int tipoApertura:    La manera para abrir el fichero. 0     */
/*                              escritura, 1 para lectura, 2 para      */
/*                              añadir.                                */
/*                                                                     */ 
/* Outputs: FILE*: Puntero al manejador de fichero abierto. Null en    */
/*                 caso de error.                                      */
/***********************************************************************/
FILE* abrirFichero(char* nombreFichero, int tipoApertura) {
	FILE* fichero = NULL;

	// Abrimos el fichero según el tipo de apertura
	if (tipoApertura == Escritura) {
		fichero = fopen(nombreFichero,"w");
	}
	else if (tipoApertura == Lectura) {
		fichero = fopen(nombreFichero,"r");
	}
	else if (tipoApertura == Reescritura) {
		fichero = fopen(nombreFichero,"w+");
	}
	// Si no sabemos el tipo de apertura indicamos el error y salimos
	else {
		fprintf(stderr,"Tipo de Apertura inadecuado en la funcion abrirFichero\n");
		return NULL;
	}
	// Comprobamos que el fichero se ha abierto, sino indicamos el error
	if (fichero == NULL) {
		fprintf(stderr,"El fichero no pudo abrirse en la funcion abrirFichero\n");
		return NULL;
	}

	return fichero;
}


/***********************************************************************/
/* Funcion: FILE* cerrarFichero(FILE* fichero);                        */
/*                                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete                           */
/*                                                                     */
/* Descripcion: Función encargada de cerrar un fichero de esqueleto.   */
/*                                                                     */
/* Inputs: char* nombreFichero: El nombre del fichero a cerrar.        */
/*                                                                     */
/* Outputs: int: Entero utilizado en el control de error. ERR en caso  */
/*               de error y OK en otro supuesto.                       */
/***********************************************************************/
int cerrarFichero(FILE* fichero) {
	int resultado = ERR;

	//Cerramos el fichero
	resultado = fclose(fichero);
	// Comprobamos el cierre, si no lo cerro indicamos el error
	if (resultado == -1) {
		fprintf(stderr,"Error en el cierre del fichero en la funcion cerrarFichero\n");
		return resultado;
	}
	return resultado;
}

/***********************************************************************/
/* Funcion: pSkeleton leerEsqueleto(FILE* fichero, int tipoLectura);   */
/*                                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete                           */
/*                                                                     */
/* Descripcion: Función principal que dirigue la lectura del fichero   */
/*              de esqueleto y vuelca su contenido a estructuras de    */
/*              datos.                                                 */
/*                                                                     */
/* Inputs: FILE* fichero:   El fichero a procesar.                     */
/*         int tipoLectura: Indica si se leera como un fichero donde   */
/*                          los huesos son rectas (0) o prismas (1)    */
/*                          y se aparecera nube de puntos (2).         */  
/*                                                                     */
/* Outputs: pSkeleton: Estructura de datos que contiene el esqueleto   */
/*                     obtenido del fichero. Null en caso de error.    */
/***********************************************************************/
pSkeleton leerEsqueleto(FILE* fichero, int tipoLectura) {
	pSkeleton esqueleto = NULL;
    int i = 0, j = 0, resultado = OK;

	// Comprobamos que el tipo de lectura es correcta
	if ((tipoLectura != Recta) && (tipoLectura != Prisma) && (tipoLectura != Nube) && (tipoLectura != Puntos)) {
		fprintf(stderr,"Error en el tipo de lectura seleccionado en la funcion leerEsqueleto\n");
		return NULL;
	}

	// Obtenemos la memoria para la estructura del esqueleto
	esqueleto = (pSkeleton) memMalloc(sizeof(skeleton) * 1);
	if (esqueleto == NULL) {
		fprintf(stderr,"Error al generar el esqueleto en la funcion leerEsqueleto\n");
		return NULL;
	}

	// Indicamos el tipo de esqueleto
	esqueleto->tipo = tipoLectura;
	// Leemos el punto de vista del fichero
	resultado = leerPuntoVista(fichero,esqueleto);
	if (resultado == -1) {
		fprintf(stderr,"Error en la lectura del punto de vista en la función leerFcihero\n");
		//liberamos la memoria del esqueleto
		if(esqueleto != NULL) memFree(esqueleto);
		return NULL;
	}

	// Obtenemos la tercera linea del fichero
	if ((tipoLectura == Recta) || (tipoLectura == Prisma)) {
		fscanf(fichero,"%d %d\n", &(esqueleto->numBones), &(esqueleto->numPointBones));
		esqueleto->numPointNube = 0;
	}
	else {
		fscanf(fichero,"%d %d %d\n", &(esqueleto->numBones), &(esqueleto->numPointBones),&(esqueleto->numPointNube));
	}

	// Comprobamos que los valores obtenidos pueden ser posibles
	if ((esqueleto->numBones <= 0) || (esqueleto->numPointBones <= 0) ||
		(esqueleto->numPointNube < 0)) {
		fprintf(stderr,"Los datos leidos, en leerFichero, del fichero no son correctos\n");
		//liberamos la memoria del esqueleto
		if(esqueleto != NULL) memFree(esqueleto);
		return NULL;
	}

	//Generamos la memoria necesaria para los huesos y puntos que contiene el fichero
	// Para los huesos
	esqueleto->Huesos = (pBone*)memMalloc(sizeof(pBone) * esqueleto->numBones);
	if (esqueleto->Huesos == NULL) {
		fprintf(stderr,"Error en generar la memoria para almacenar los huesos en leerFichero\n");
		// liberamos la estrutura del esqueleto
		if(esqueleto != NULL) memFree(esqueleto);
		return NULL;
	}

	// Para los puntos de los huesos
	esqueleto->pointBones = (pPoint*)memMalloc(sizeof(pPoint) * esqueleto->numPointBones);
	if (esqueleto->pointBones == NULL) {
		fprintf(stderr,"Error en generar la memoria para almacenar los puntos de los huesos en leerFichero\n");
		// liberamos la estrutura del esqueleto
		if(esqueleto->Huesos != NULL) memFree(esqueleto->Huesos);
		if(esqueleto != NULL) memFree(esqueleto);
		return NULL;
	}

	// Para los puntos de la nube
	if ((tipoLectura == Nube) || (tipoLectura == Puntos)) {
		esqueleto->pointNube = (pPoint*)memMalloc(sizeof(pPoint) * esqueleto->numPointNube);
		if (esqueleto->pointNube == NULL) {
			fprintf(stderr,"Error en generar la memoria para almacenar los puntos de la nube en leerFichero\n");
			// liberamos la estrutura del esqueleto
			if(esqueleto->pointBones != NULL) memFree(esqueleto->pointBones);
			if(esqueleto->Huesos != NULL) memFree(esqueleto->Huesos);
			if(esqueleto != NULL) memFree(esqueleto);
			return NULL;
		}
	}

	// Empezamos la captura de los huesos
	for(i = 0; i < esqueleto->numBones; i++) {
		resultado = OK;
		// Leemos un hueso
		resultado = leerHueso(fichero, esqueleto, tipoLectura, i);
		// Comprobamos que no se produjesen errores, pero si los hay lo indicamos y 
		// liberamos la memoria
		if (resultado == -1) {
			fprintf(stderr,"Error en la obtención de un hueso en leerFichero\n");
			// liberamos la estrutura del esqueleto
			for(j = 0; j < i; j++) {
				if(esqueleto->Huesos[j]->puntos != NULL) memFree(esqueleto->Huesos[j]->puntos);
				if(esqueleto->Huesos[j]->nube != NULL) memFree(esqueleto->Huesos[j]->nube);
				if(esqueleto->Huesos[j] != NULL) memFree(esqueleto->Huesos[j]);
			}
			if(esqueleto->pointNube != NULL) memFree(esqueleto->pointNube);
			if(esqueleto->pointBones != NULL) memFree(esqueleto->pointBones);
			if(esqueleto->Huesos != NULL) memFree(esqueleto->Huesos);
			if(esqueleto != NULL) memFree(esqueleto);
			return NULL;
		}
	}

	// Empezamos la captura de los puntos de los huesos
	for(i = 0; i < esqueleto->numPointBones; i++) {
		resultado = OK;
		// Leemos un punto de hueso
		resultado = leerPunto(fichero,esqueleto, tipoLectura, i, Recta);
		// Eliminamos el espacio separador o el salto de linea
		if(i == esqueleto->numPointNube - 1) {
			fscanf(fichero,"\n");
		}
		else {
			fscanf(fichero," ");
		}
		// Comprobamos que no se produjesen errores, pero si los hay lo indicamos y 
		// liberamos la memoria
		if (resultado == -1) {
			fprintf(stderr,"Error en la obtención de un punto de hueso en leerFichero\n");
			// liberamos la estrutura del esqueleto
			for(j = 0; j < i; j++) {
				if(esqueleto->pointBones[j] != NULL) memFree(esqueleto->pointBones[j]);
			}
			for(j = 0; j < esqueleto->numBones; j++) { 
				if(esqueleto->Huesos[j]->puntos != NULL) memFree(esqueleto->Huesos[j]->puntos);
				if(esqueleto->Huesos[j]->nube != NULL) memFree(esqueleto->Huesos[j]->nube);
				if(esqueleto->Huesos[j] != NULL) memFree(esqueleto->Huesos[j]);
			}
			if(esqueleto->pointNube != NULL) memFree(esqueleto->pointNube);
			if(esqueleto->pointBones != NULL) memFree(esqueleto->pointBones);
			if(esqueleto->Huesos != NULL) memFree(esqueleto->Huesos);
			if(esqueleto != NULL) memFree(esqueleto);
			return NULL;
		}
	}

	// Si tenemos que leer la nube de puntos
	if ((tipoLectura == Nube) || (tipoLectura == Puntos)) {
		// Empezamos la captura de los puntos de la nube
		for(i = 0; i < esqueleto->numPointNube; i++) {
			resultado = OK;
			// Leemos un punto de la nube
			resultado = leerPunto(fichero,esqueleto, tipoLectura, i, Nube);
			// Eliminamos el espacio separador o el salto de linea
			if(i == esqueleto->numPointNube - 1) {
				fscanf(fichero,"\n");
			}
			else {
				fscanf(fichero," ");
			}
			// Comprobamos que no se produjesen errores, pero si los hay lo indicamos y 
			// liberamos la memoria
			if (resultado == -1) {
				fprintf(stderr,"Error en la obtención de un punto de hueso en leerFichero\n");
				// liberamos la estrutura del esqueleto
				for(j = 0; j < i; j++) {
					if(esqueleto->pointNube[j] != NULL) memFree(esqueleto->pointNube[j]);
				}
				for(j = 0; j < esqueleto->numPointBones; j++) { 
					if(esqueleto->pointBones[j] != NULL) memFree(esqueleto->pointBones[j]);
				}
				for(j = 0; j < esqueleto->numBones; j++) { 
					if(esqueleto->Huesos[j]->puntos != NULL) memFree(esqueleto->Huesos[j]->puntos);
					if(esqueleto->Huesos[j]->nube != NULL) memFree(esqueleto->Huesos[j]->nube);
					if(esqueleto->Huesos[j] != NULL) memFree(esqueleto->Huesos[j]);
				}
				if(esqueleto->pointNube != NULL) memFree(esqueleto->pointNube);
				if(esqueleto->pointBones != NULL) memFree(esqueleto->pointBones);
				if(esqueleto->Huesos != NULL) memFree(esqueleto->Huesos);
				if(esqueleto != NULL) memFree(esqueleto);
				return NULL;
			}
		}
	}

	return esqueleto;
}

/**********************************************************************************************/
/* Funcion: int leerHueso(FILE* fichero, pSkeleton esqueleto, int tipoLectura, int indice);   */
/*                                                                                            */
/* Autor: Víctor Fernández-Carbajales Cañete                                                  */
/*                                                                                            */
/* Descripcion: Función que se encarga de leer un hueso del fichero de esqueleto.             */
/*                                                                                            */
/* Inputs: FILE* fichero:      El fichero del esqueleto.                                      */
/*         pSkeleto esqueleto: La estructura de datos del esqueleto definido en el fichero.   */
/*         int tipoLectura:    Indica si se leera como un fichero donde los huesos son rectas */
/*                             (0) o prismas (1) y se aparecera nube de puntos (2).           */  
/*         int indice:         Entero que indica el identificador del hueso dentro del esque- */
/*                             leto.                                                          */
/*                                                                                            */
/* Outputs: int: Entero utilizado en el control de error. ERR en caso de error y OK en otro   */
/*               caso.                                                                        */  
/**********************************************************************************************/
int leerHueso(FILE* fichero, pSkeleton esqueleto, int tipoLectura, int indice) {
	int i = 0, cantidad = 0;

	// obtenemos el número de puntos que conforman el hueso
	fscanf(fichero,"%d ",&cantidad);
	// comprobamos que el numero sea verosimil
	if(cantidad < 0) {
		fprintf(stderr,"Error en los valores leido, en la funcion leerHueso, en el fichero\n");
		return ERR;
	}

	// Generamos memoria para el hueso
	esqueleto->Huesos[indice] = (pBone)memMalloc(sizeof(bone) * 1);
	// Comprobamos que se genero la memoria, sino en ese caso indicamos el error
	if (esqueleto->Huesos[indice] == NULL) {
		fprintf(stderr,"Error en generar la memoria para el hueso en la funcion leerHueso\n");
		return ERR;
	}

	// Indicamos el identificador del hueso
	esqueleto->Huesos[indice]->id_bone = indice;
	// Indicamos la cantidad de puntos de hueso
	esqueleto->Huesos[indice]->numPuntos = cantidad;
	// Generamos memoria para el array de puntos
	esqueleto->Huesos[indice]->puntos = (int*)memMalloc(sizeof(int) * cantidad);
	// Comprobamos que se genero la memoria, sino indicaremos un error
	if (esqueleto->Huesos[indice]->puntos == NULL) {
		fprintf(stderr,"Error en generar la memoria para los puntos del hueso en la funcion leerHueso\n");
		//Liberamos la estructura del hueso
		if(esqueleto->Huesos[indice] != NULL) memFree(esqueleto->Huesos[indice]);
	}

	// Leemos los indices de los puntos del hueso
	for(i = 0; i < cantidad; i++) {
		fscanf(fichero,"%d ",&(esqueleto->Huesos[indice]->puntos[i]));
	}

	// Si el tipo de lectura es con nube 
	if (tipoLectura == Nube) {
		// obtenemos el número de puntos que conforman la nube
		fscanf(fichero,"%d ",&cantidad);
		// comprobamos que el numero sea verosimil
		if(cantidad < 0) {
			fprintf(stderr,"Error en los valores leido, en la funcion leerHueso, en el fichero\n");
			// Liberamo al memoria del hueso
			if(esqueleto->Huesos[indice]->puntos != NULL) memFree(esqueleto->Huesos[indice]->puntos);
			if(esqueleto->Huesos[indice] != NULL) memFree(esqueleto->Huesos[indice]);
			return ERR;
		}
		// Indicamos la cantidad de puntos de la nube
		esqueleto->Huesos[indice]->numNube = cantidad;

		// Generamos memoria para el array de nube
		esqueleto->Huesos[indice]->nube = (int*)memMalloc(sizeof(int) * cantidad);
		// Comprobamos que se genero la memoria, sino indicaremos un error
		if (esqueleto->Huesos[indice]->nube == NULL) {
			fprintf(stderr,"Error en generar la memoria para los puntos del hueso en la funcion leerHueso\n");
			//Liberamos la estructura del hueso
			if(esqueleto->Huesos[indice]->puntos != NULL) memFree(esqueleto->Huesos[indice]->puntos);
			if(esqueleto->Huesos[indice] != NULL) memFree(esqueleto->Huesos[indice]);
		}

		// Leemos los indices de los puntos del hueso
		for(i = 0; i < cantidad; i++) {
			fscanf(fichero,"%d ",&(esqueleto->Huesos[indice]->nube[i]));
		}
	}
	else {
		// Indicamos la cantidad de puntos de la nube
		esqueleto->Huesos[indice]->numNube = 0;
	}


	// Leemos el final de la linea
	fscanf(fichero,"\n");

	return OK;
}

/******************************************************************************************************/
/* Funcion: int leerHueso(FILE* fichero, pSkeleton esqueleto, int tipoLectura, int indice, int tipo); */
/*                                                                                                    */
/* Autor: Víctor Fernández-Carbajales Cañete                                                          */
/*                                                                                                    */
/* Descripcion: Función que se encarga de leer un punto del fichero de esqueleto.                     */
/*                                                                                                    */
/* Inputs: FILE* fichero:      El fichero del esqueleto.                                              */
/*         pSkeleto esqueleto: La estructura de datos del esqueleto definido en el fichero.           */
/*         int tipoLectura:    Indica si se leera como un fichero donde los huesos son rectas         */
/*                             (0) o prismas (1) y se aparecera nube de puntos (2).                   */  
/*         int indice:         Entero que indica el identificador del hueso dentro del esque-         */
/*                             leto.                                                                  */
/*         int tipo:           Entero que indica si el punto es de hueso (0 o 1) o de nube (2).       */  
/*                                                                                                    */
/* Outputs: int: Entero utilizado en el control de error. ERR en caso de error y OK en otro caso.     */ 
/******************************************************************************************************/
int leerPunto(FILE* fichero, pSkeleton esqueleto, int tipoLectura, int indice, int tipo) {
	int i = 0;

	// Generamos la memoria par el punto, y leemos el punto del fichero y lo almacenamos en el lugar
	// indicado según el tipo
	if ((tipo == Recta) || (tipo == Prisma)) {
		// Generamos la memoria
		esqueleto->pointBones[indice] = (pPoint)memMalloc(sizeof(point) * 1);
		// Comprobamos que se reserve la memoria, sino indicamos el menaje de error
		if (esqueleto->pointBones[indice] == NULL) {
			fprintf(stderr,"Error en obtener memoria para un punto de hueso en la funcion leerPuntos\n");
			return ERR;
		}
		// Leemos el punto
		fscanf(fichero,"%f %f %f",&(esqueleto->pointBones[indice]->x),&(esqueleto->pointBones[indice]->y),
								  &(esqueleto->pointBones[indice]->z));
	}
	else if (tipo == Nube) {
		// Generamos la memoria
		esqueleto->pointNube[indice] = (pPoint)memMalloc(sizeof(point) * 1);
		// Comprobamos que se reserve la memoria, sino indicamos el menaje de error
		if (esqueleto->pointNube[indice] == NULL) {
			fprintf(stderr,"Error en obtener memoria para un punto de la nube en la funcion leerPuntos\n");
			return ERR;
		}
		// Leemos el punto
		fscanf(fichero,"%f %f %f",&(esqueleto->pointNube[indice]->x),&(esqueleto->pointNube[indice]->y),
								  &(esqueleto->pointNube[indice]->z));
	}
	else {
		fprintf(stderr,"Error en el tipo de lectura de los puntos en la funcion leerPunto\n");
		return ERR;
	}

	return OK;
}

/********************************************************************/
/* Funcion: int leerPuntoVista(FILE* fichero, pSkeleton esqueleto); */
/*                                                                  */
/* Autor: Víctor Fernández-Carbajales Cañete                        */
/*                                                                  */
/* Descripcion: Función que se encarga de leer un punto de vista del*/
/*              fichero el esqueleto.                               */   
/*                                                                  */
/* Inputs: FILE* fichero:      El fichero del esqueleto.            */
/*         pSkeleto esqueleto: La estructura de datos del esqueleto */
/*                             definido en el fichero.              */
/*                                                                  */
/* Outputs: int: Entero utilizado en el control de error. ERR en    */
/*               caso de error y OK en otro caso.                   */ 
/********************************************************************/
int leerPuntoVista(FILE* fichero, pSkeleton esqueleto) {
	// Leemos el punto de vista del fichero en dos pasos
	// Primero la orientacion y el infinito
	fscanf(fichero,"%f %f %f %f ",&(esqueleto->puntoVista.orientacion.x)
		                         ,&(esqueleto->puntoVista.orientacion.y)
								 ,&(esqueleto->puntoVista.orientacion.z)
								 ,&(esqueleto->puntoVista.w));

	// Después la posicion
	fscanf(fichero,"%f %f %f\n",&(esqueleto->puntoVista.posicion.x)
		                       ,&(esqueleto->puntoVista.posicion.y)
							   ,&(esqueleto->puntoVista.posicion.z));

	return OK;
}

int leerArbol(FILE* fichero, FILE* fichero_textura,Arbol* parbol)//Coordenadas_Rama** pparbol)	
{
	//int tamanio = sizeof(fichero);
	int tamanio = 1000;
	long tamanio_textura = 0;
	int i = 0;
	float aux1 = 0;
	float aux2 = 0;
	float aux3 = 0;
	float aux4 = 0;
	float aux5 = 0;
	float aux6 = 0;
	float aux7 = 0;
	float aux8 = 0;
	char caracter;
	
	//while(!feof(fichero_textura)) {
	//	printf("\n%d %d %d", (unsigned char) fgetc(fichero_textura),(unsigned char) fgetc(fichero_textura),(unsigned char) fgetc(fichero_textura));
	//}




	if (fichero_textura)
	{
		fseek(fichero_textura,0,SEEK_END);
		tamanio_textura = ftell( fichero_textura);
		fseek(fichero_textura,0,SEEK_SET);
		parbol->tamanio_textura = tamanio_textura;
		parbol->textura = memMalloc (tamanio_textura);

		 fread( parbol->textura, 1, tamanio_textura,fichero_textura);
		/*
		i=0;
		for(i = 0; i<tamanio_textura/3; i++)
		{
			((unsigned char*)(parbol->textura))[3*i] = i%255;
			((unsigned char*)(parbol->textura))[3*i+1] = 255;
			((unsigned char*)(parbol->textura))[3*i+2] = 0;
		}

		while(!feof(fichero_textura)) {
			((unsigned char* ) (parbol->textura))[i++] = (unsigned char) fgetc(fichero_textura);			
		}
		printf("\n%d, %d", i, tamanio_textura);
	 

		 for(i =0; i<tamanio_textura/3;i++) {
			printf("*%d %d %d", (unsigned char)((unsigned char* ) (parbol->textura))[3*i], ((unsigned char* ) (parbol->textura))[3*i+1], ((unsigned char* ) (parbol->textura))[3*i+2]);
		 }
		 */
		
	}

	i=0;
	
	parbol->ramas 		= (	Coordenadas_Rama*)memMalloc((int) tamanio*sizeof(Coordenadas_Rama));
	caracter = getc(fichero);
	while ((caracter!='\n')&&(caracter!='\r'))
	{
		caracter = getc(fichero);
	}
	
	while ((fscanf(fichero,"%f	%f	%f	%f	%f	%f	%f	%f\n",&aux1,&aux2,&aux3, &aux4,&aux5,&aux6,&aux7,&aux8)!=EOF)&&(i<tamanio))
	{
		parbol->ramas[i].D1	= aux1;
		parbol->ramas[i].D2	= aux2;	
		parbol->ramas[i].h	= aux3;
		parbol->ramas[i].Fi	= aux4;
		parbol->ramas[i].alfa	= aux5;
		parbol->ramas[i].r0x	= aux6;
		parbol->ramas[i].r0y	= aux7;
		parbol->ramas[i].r0z	= aux8;
		parbol->ramas[i].indice_rama = i;
		i++;
	}
	parbol->traslacion_horizontal_x	= 0;
	parbol->traslacion_horizontal_z	= 0;
	if (i>0)
		parbol->ramas[i-1].indice_rama = -1;
	return i;
}


