/*****************************************************************/
/* Fichero: Arboles.cpp                      Fecha: 26-01-2006   */
/*                                                               */
/* Autor: Víctor Fernández-Carbajales Cañete                     */
/*                                                               */
/* Descripcion: Fichero que controla la aplicación.              */
/*****************************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "ArbolesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************************************/
/* Mapeo de Mensajes del Dialogo                              */
/**************************************************************/
BEGIN_MESSAGE_MAP(CArbolesApp, CWinApp)
	//{{AFX_MSG_MAP(CArbolesApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/**************************************************************/
/* Constructor por defecto de la clase                        */
/**************************************************************/
CArbolesApp::CArbolesApp()
{
}

// Creación de la aplicación
CArbolesApp theApp;

/**************************************************************/
/* Funcion: InitInstance                                      */
/*                                                            */
/* Descripción: Función que se encarga de inicializar la apli-*/ 
/*              cación.                                       */
/*                                                            */
/* Parametros: Entrada: Sin Entradas.                         */
/*                                                            */
/*             Salida: BOOL: Usado en el control de errores.  */
/**************************************************************/
BOOL CArbolesApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	// LLamada utilizada si se usan MFC en DLL
	Enable3dControls();	
#else
	// LLamada utilizada para linkar MFC estaticas
	Enable3dControlsStatic();
#endif

	// Creamos el dialogo principal
	CArbolesDlg dlg;
	// Indicamos que es la principal
	m_pMainWnd = &dlg;
	// Mostramos el dialogo
	int nResponse = dlg.DoModal();
	// Si se salido dando a OK
	if (nResponse == IDOK) {
	}
	// Si se salido dando a Cancel
	else if (nResponse == IDCANCEL) {
	}

	return FALSE;
}
