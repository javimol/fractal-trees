/*******************************************************/
/* Fichero: DialogAbout.h            Fecha: 27-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo de des-*/
/*              pedida de la aplicación.               */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef DIALOGCLOSE_H
#define DIALOGCLOSE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class CDialogClose : public CDialog
{
public:
	// Constructor por defecto
	CDialogClose(CWnd* pParent = NULL);

	// Datos del dialogo
	//{{AFX_DATA(CDialogClose)
	enum { IDD = IDD_CLOSE_DIALOG };
	//}}AFX_DATA

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CDialogClose)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Funciones del mapeo de mensajes
	//{{AFX_MSG(CDialogClose)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif 
