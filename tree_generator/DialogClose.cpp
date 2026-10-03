/*******************************************************/
/* Fichero: DialogClose.cpp          Fecha: 26-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementación del dialogo  */
/*              de despedida de la aplicación.         */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "DialogClose.h"

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
CDialogClose::CDialogClose(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogClose::IDD, pParent) {
	//{{AFX_DATA_INIT(CDialogClose)
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
void CDialogClose::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogClose)
	//}}AFX_DATA_MAP
}

/**************************************************************/
/* Mapeo de Mensajes del Dialogo                              */
/**************************************************************/
BEGIN_MESSAGE_MAP(CDialogClose, CDialog)
	//{{AFX_MSG_MAP(CDialogClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

