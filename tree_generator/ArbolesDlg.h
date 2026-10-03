/*******************************************************/
/* Fichero: ArbolesDlg.h             Fecha: 27-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Fichero de cabecera del dialogo prin-  */
/*              cipal de la aplicación.                */
/*******************************************************/

// Protegemos la definición 
#ifndef ARBOLESDLG_H
#define ARBOLESDLG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Incluimos las librerias necesarias
#include "DialogAbout.h"
#include "DialogHelp.h"
#include "DialogClose.h"
#include "DialogErrorFile.h"
#include "DialogGenerate.h"
#include "DialogInformation.h"
#include "FileDlg.h"
#include "Tree.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

// Definimos la clase
class CArbolesDlg : public CDialog
{
public:
	// Los parametros del arbol
	Parameters *parameters;
	// El arbol generado
	Tree* tree;

	// Constructor estándar
	CArbolesDlg(CWnd* pParent = NULL);

	// Funcion que crea una cadena con un numero decimal de un valor double
	char* crearDouble(double valor);
	// Funcion que crea una cadena con un numero entero de un valor double
	char* crearEntero(double valor);

	// Datos del dialogo
	//{{AFX_DATA(CArbolesDlg)
	enum { IDD = IDD_ARBOLES_DIALOG };
	CEdit	m_Edit_Deviousness_Arch_Control;
	CEdit	m_Edit_Generation_Control;
	CStatic	m_Static_Deviousness_Arch;
	CStatic	m_Static_Generation;
	CStatic	m_Static_Probability_Trunk;
	CEdit	m_Edit_Probability_Trunk_Control;
	CStatic	m_Static_Ratio_Diameter;
	CEdit	m_Edit_Ratio_Diameter_Control;
	CEdit	m_Edit_Var_Tree_Cone_Control;
	CEdit	m_Edit_Tree_Cone_Control;
	CEdit	m_Edit_Deviousness_Angle_Control;
	CStatic	m_Static_Deviousness_Angle;
	CStatic	m_Static_Var_Tree_Cone;
	CStatic	m_Static_Tree_Cone;
	CEdit	m_Edit_Variability_Control;
	CEdit	m_Edit_Ratio_Trunk2_Control;
	CEdit	m_Edit_Ratio_Trunk_Control;
	CEdit	m_Edit_Ratio_Top_Control;
	CEdit	m_Edit_Ratio_Branch_Control;
	CEdit	m_Edit_Ratio_Base_Control;
	CEdit	m_Edit_Min_Angle_Control;
	CEdit	m_Edit_Max_Angle_Control;
	CEdit	m_Edit_Frondage_Control;
	CEdit	m_Edit_Deviousness_Control;
	CStatic	m_Static_Ratio_Trunk2;
	CEdit	m_Edit_Pace_Control;
	CEdit	m_Edit_Max_Height_Control;
	CEdit	m_Edit_Age_Control;
	CButton	m_Boton_Generate;
	CStatic	m_Static_Variability;
	CStatic	m_Static_Ratio_Trunk;
	CStatic	m_Static_Ratio_Top2;
	CStatic	m_Static_Ratio_Top;
	CStatic	m_Static_Ratio_Branch;
	CStatic	m_Static_Ratio_Base;
	CStatic	m_Static_Pace;
	CStatic	m_Static_Max;
	CStatic	m_Static_Min_Angle;
	CStatic	m_Static_Max_Angle;
	CStatic	m_Static_Frondage;
	CStatic	m_Static_Deviousness;
	CButton	m_Boton_Reset;
	CStatic	m_Static_Age;
	CString	m_Edit_Age;
	CString	m_Edit_Max_Height;
	CString	m_Edit_Pace;
	CString	m_Edit_Deviousness;
	CString	m_Edit_Frondage;
	CString	m_Edit_Max_Angle;
	CString	m_Edit_Min_Angle;
	CString	m_Edit_Ratio_Base;
	CString	m_Edit_Ratio_Branch;
	CString	m_Edit_Ratio_Top;
	CString	m_Edit_Ratio_Trunk;
	CString	m_Edit_Ratio_Trunk2;
	CString	m_Edit_Variability;
	CString	m_Edit_Deviousness_Angle;
	CString	m_Edit_Tree_Cone;
	CString	m_Edit_Var_Tree_Cone;
	CString	m_Edit_Ratio_Diameter;
	CString	m_Edit_Probability_Trunk;
	CString	m_Edit_Generation;
	CString	m_Edit_Deviousness_Arch;
	//}}AFX_DATA

	// Funciones sobrecargadas
	//{{AFX_VIRTUAL(CArbolesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Funciones de mapeo de mensajes
	//{{AFX_MSG(CArbolesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnArchivevExit();
	afx_msg void OnArchivevSavefile();
	afx_msg void OnHelpAbout();
	afx_msg void OnHelpHelp();
	afx_msg void Onstore();
	afx_msg void OnReset();
	afx_msg void OnGenerate();
	afx_msg void OnChangeEditMaxHeight();
	afx_msg void OnChangeEditAge();
	afx_msg void OnChangeEditPace();
	afx_msg void OnChangeEditDeviousness();
	afx_msg void OnChangeEditFrondage();
	afx_msg void OnChangeEditMaxAngle();
	afx_msg void OnChangeEditMinAngle();
	afx_msg void OnChangeEditRatioBase();
	afx_msg void OnChangeEditRatioBranch();
	afx_msg void OnChangeEditRatioTop();
	afx_msg void OnChangeEditRatioTrunk();
	afx_msg void OnChangeEditRatioTrunk2();
	afx_msg void OnChangeEditVariability();
	afx_msg void OnChangeEditDeviousnessAngle();
	afx_msg void OnChangeEditTreeCone();
	afx_msg void OnChangeEditVarTreeCone();
	afx_msg void OnChangeEditRatioDiameter();
	afx_msg void OnChangeEditProbabilityTrunk();
	afx_msg void OnChangeEditGeneration();
	afx_msg void OnChangeEditDeviousnessArch();
	afx_msg void OnSavefileMpeg4();
	afx_msg void OnArchivevSavefileMpeg4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif 
