/*******************************************************/
/* Fichero: Arboles.h                Fecha: 27-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera de la aplicación   */
/*              principal.                             */
/*******************************************************/

// Protegemos la definicion
#ifndef ARBOLES_H
#define ARBOLES_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

// Incluimos las librerias necesarias
#include "resource.h"		

// Definición de la clase
class CArbolesApp : public CWinApp
{
public:
	// Constructor estándar
	CArbolesApp();

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CArbolesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	// Funciones del mapeo de mensajes
	//{{AFX_MSG(CArbolesApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}


#endif 
