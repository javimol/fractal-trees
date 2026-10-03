/*******************************************************/
/* Fichero: DialogGenerate.cpp       Fecha: 06-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de implementación del dialogo  */
/*              de información de la generación del    */
/*              arból.                                 */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "DialogGenerate.h"

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
CDialogGenerate::CDialogGenerate(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogGenerate::IDD, pParent) {
	//{{AFX_DATA_INIT(CDialogGenerate)
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
void CDialogGenerate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogGenerate)
	//}}AFX_DATA_MAP
}

/**************************************************************/
/* Mapeo de Mensajes del Dialogo                              */
/**************************************************************/
BEGIN_MESSAGE_MAP(CDialogGenerate, CDialog)
	//{{AFX_MSG_MAP(CDialogGenerate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

