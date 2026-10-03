/*******************************************************/
/* Fichero: DialogAbout.h            Fecha: 27-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo de des-*/
/*              pedida de la aplicación.               */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class CDialogAbout : public CDialog
{
public:
	// Constructor por defecto
	CDialogAbout(CWnd* pParent = NULL);   

	// Datos del dialogo
	//{{AFX_DATA(CDialogAbout)
	enum { IDD = IDD_ABOUT_DIALOG };
	//}}AFX_DATA

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CDialogAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


protected:
	// Funciones del mapeo de mensajes
	//{{AFX_MSG(CDialogAbout)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif 
