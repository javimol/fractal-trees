/*******************************************************/
/* Fichero: DialogAbout.cpp          Fecha: 26-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementación del dialogo  */
/*              de informacion sobre la aplicación.    */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "DialogAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************************************/
/* Funcion: Constructor del dialogo                           */
/*                                                            */
/* Descripcion: Funcion que crea el dialogo.                  */
/*                                                            */
/* Argumentos: Entrada: CWnd* pParent: La ventana padre del   */
/*                                     dialogo.               */
/**************************************************************/
CDialogAbout::CDialogAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAbout::IDD, pParent) {
	//{{AFX_DATA_INIT(CDialogAbout)
	//}}AFX_DATA_INIT
}

/**************************************************************/
/* Funcion: DoDataExchange                                    */
/*                                                            */
/* Descripcion: Funcion para el control de datos en la ventana*/
/*                                                            */
/* Argumentos: Entrada: CDataExchange* pDX: Los datos cambia- */
/*                                          dos.              */
/*                                                            */
/*             Salida: Sin Salida.                            */
/**************************************************************/
void CDialogAbout::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAbout)
	//}}AFX_DATA_MAP
}

/**************************************************************/
/* Mapeo de Mensajes del Dialogo                              */
/**************************************************************/
BEGIN_MESSAGE_MAP(CDialogAbout, CDialog)
	//{{AFX_MSG_MAP(CDialogAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

