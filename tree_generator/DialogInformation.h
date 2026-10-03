/*******************************************************/
/* Fichero: DialogInformation.h      Fecha: 06-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo del    */
/*              de informacion.                        */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef DIALOGINFORMATION_H
#define DIALOGINFORMATION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class CDialogInformation : public CDialog
{
public:
	// Constructor por defecto
	CDialogInformation(CWnd* pParent = NULL);   // standard constructor

	// Datos del dialogo
	//{{AFX_DATA(CDialogInformation)
	enum { IDD = IDD_INFORAMTION_DIALOG };
	//}}AFX_DATA

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CDialogInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


protected:
	// Funciones del mapeo de mensajes
	//{{AFX_MSG(CDialogInformation)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
