/*******************************************************/
/* Fichero: DialogHelp.h             Fecha: 01-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo del    */
/*              dialogo de ayuda de la aplicacion.     */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef DIALOGHELP_H
#define DIALOGHELP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class CDialogHelp : public CDialog
{
public:
	// Constructor por defecto
	CDialogHelp(CWnd* pParent = NULL);   // standard constructor

	// Datos del dialogo
	//{{AFX_DATA(CDialogHelp)
	enum { IDD = IDD_HELP_DIALOG };
	//}}AFX_DATA

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CDialogHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Funciones del mapeo de mensajes
	//{{AFX_MSG(CDialogHelp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
