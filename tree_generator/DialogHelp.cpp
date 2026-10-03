/*******************************************************/
/* Fichero: DialogHelp.cpp           Fecha: 06-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementación del dialogo  */
/*              de informacion de la aplicacion.       */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "DialogHelp.h"

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
CDialogHelp::CDialogHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogHelp::IDD, pParent) {
	//{{AFX_DATA_INIT(CDialogHelp)
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
void CDialogHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogHelp)
	//}}AFX_DATA_MAP
}

/**************************************************************/
/* Mapeo de Mensajes del Dialogo                              */
/**************************************************************/
BEGIN_MESSAGE_MAP(CDialogHelp, CDialog)
	//{{AFX_MSG_MAP(CDialogHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

