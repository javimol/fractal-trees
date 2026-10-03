/*******************************************************/
/* Fichero: FileDlg.h                Fecha: 13-04-2005 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo para   */
/*              guardar o cargar ficheros.             */
/*******************************************************/

// Protegemos la definición de la clase
#if !defined FILEDLG_H
#define FILEDLG_H

#if _MSC_VER > 1000
#pragma once
#endif 

// Definimos la clase
class FileDlg : public CFileDialog
{
	// Indicamos la declaración dinamica
	DECLARE_DYNAMIC(FileDlg)

public:
	// Constructor estándar de la clase
	FileDlg(BOOL bOpenFileDialog,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(FileDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
