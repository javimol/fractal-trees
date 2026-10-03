/*******************************************************/
/* Fichero: DialogErrorFile.h        Fecha: 06-02-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo de     */
/*              informacion de error en la apertura de */
/*              fichero por parte de la aplicacion.    */
/*******************************************************/

// Protegemos la definición de la clase
#ifndef DIALOGERRORFILE_H
#define DIALOGERRORFILE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definimos la clase
class CDialogErrorFile : public CDialog
{
public:
	// Constructor por defecto
	CDialogErrorFile(CWnd* pParent = NULL);   // standard constructor

	// Datos del dialogo
	//{{AFX_DATA(CDialogErrorFile)
	enum { IDD = IDD_ERR_FILE_DIALOG };
	//}}AFX_DATA

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CDialogErrorFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Funciones del mapeo de mensajes
	//{{AFX_MSG(CDialogErrorFile)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif 
