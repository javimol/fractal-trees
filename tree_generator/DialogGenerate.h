/*******************************************************/
/* Fichero: DialogGenerate.h         Fecha: 06-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo de     */
/*              informacion de terminacion de la       */
/*              generacion del arbol.                  */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef DIALOGGENERATE_H
#define DIALOGGENERATE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class CDialogGenerate : public CDialog
{
public:
	// Constructor por defecto
	CDialogGenerate(CWnd* pParent = NULL);   // standard constructor

	// Datos del dialogo
	//{{AFX_DATA(CDialogGenerate)
	enum { IDD = IDD_GENERATE_DIALOG };
	//}}AFX_DATA

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CDialogGenerate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Funciones del mapeo de mensajes
	//{{AFX_MSG(CDialogGenerate)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif 
