/*******************************************************/
/* Fichero: ArbolesDlg.cpp           Fecha: 26-01-2006 */
/*                                                     */
/* Autor: Víctor Fernández-Carbajales Cañete           */
/*                                                     */
/* Descripción: Codigo para la pantalla principal.     */
/*******************************************************/

// Incluimos las librerias necesarias
#include "stdafx.h"
#include "Arboles.h"
#include "ArbolesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int arbol = 0;

/**************************************************************/
/* Funcion: Constructor del dialogo                           */
/*                                                            */
/* Descripcion: Funcion que crea el dialogo.                  */
/*                                                            */
/* Argumentos: Entrada: CWnd* pParent: La ventana padre del   */
/*                                     dialogo.               */
/**************************************************************/
CArbolesDlg::CArbolesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArbolesDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CArbolesDlg)
	m_Edit_Age = _T("");
	m_Edit_Max_Height = _T("");
	m_Edit_Pace = _T("");
	m_Edit_Deviousness = _T("");
	m_Edit_Frondage = _T("");
	m_Edit_Max_Angle = _T("");
	m_Edit_Min_Angle = _T("");
	m_Edit_Ratio_Base = _T("");
	m_Edit_Ratio_Branch = _T("");
	m_Edit_Ratio_Top = _T("");
	m_Edit_Ratio_Trunk = _T("");
	m_Edit_Ratio_Trunk2 = _T("");
	m_Edit_Variability = _T("");
	m_Edit_Deviousness_Angle = _T("");
	m_Edit_Tree_Cone = _T("");
	m_Edit_Var_Tree_Cone = _T("");
	m_Edit_Ratio_Diameter = _T("");
	m_Edit_Probability_Trunk = _T("");
	m_Edit_Generation = _T("");
	m_Edit_Deviousness_Arch = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
void CArbolesDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArbolesDlg)
	DDX_Control(pDX, IDC_EDIT_DEVIOUSNESS_ARCH, m_Edit_Deviousness_Arch_Control);
	DDX_Control(pDX, IDC_EDIT_GENERATION, m_Edit_Generation_Control);
	DDX_Control(pDX, IDC_DEVIOUSNESS_ARCH_STATIC, m_Static_Deviousness_Arch);
	DDX_Control(pDX, IDC_GENERATION_STATIC, m_Static_Generation);
	DDX_Control(pDX, IDC_PROBABILITY_TRUNK_STATIC, m_Static_Probability_Trunk);
	DDX_Control(pDX, IDC_EDIT_PROBABILITY_TRUNK, m_Edit_Probability_Trunk_Control);
	DDX_Control(pDX, IDC_RATIO_DIAMETER_STATIC, m_Static_Ratio_Diameter);
	DDX_Control(pDX, IDC_EDIT_RATIO_DIAMETER, m_Edit_Ratio_Diameter_Control);
	DDX_Control(pDX, IDC_EDIT_VAR_TREE_CONE, m_Edit_Var_Tree_Cone_Control);
	DDX_Control(pDX, IDC_EDIT_TREE_CONE, m_Edit_Tree_Cone_Control);
	DDX_Control(pDX, IDC_EDIT_DEVIOUSNESS_ANGLE, m_Edit_Deviousness_Angle_Control);
	DDX_Control(pDX, IDC_DEVIOUSNESS_ANGLE_STATIC, m_Static_Deviousness_Angle);
	DDX_Control(pDX, IDC_VAR_TREE_CONE_STATIC, m_Static_Var_Tree_Cone);
	DDX_Control(pDX, IDC_TREE_CONE_STATIC, m_Static_Tree_Cone);
	DDX_Control(pDX, IDC_EDIT_VARIABILITY, m_Edit_Variability_Control);
	DDX_Control(pDX, IDC_EDIT_RATIO_TRUNK2, m_Edit_Ratio_Trunk2_Control);
	DDX_Control(pDX, IDC_EDIT_RATIO_TRUNK, m_Edit_Ratio_Trunk_Control);
	DDX_Control(pDX, IDC_EDIT_RATIO_TOP, m_Edit_Ratio_Top_Control);
	DDX_Control(pDX, IDC_EDIT_RATIO_BRANCH, m_Edit_Ratio_Branch_Control);
	DDX_Control(pDX, IDC_EDIT_RATIO_BASE, m_Edit_Ratio_Base_Control);
	DDX_Control(pDX, IDC_EDIT_MIN_ANGLE, m_Edit_Min_Angle_Control);
	DDX_Control(pDX, IDC_EDIT_MAX_ANGLE, m_Edit_Max_Angle_Control);
	DDX_Control(pDX, IDC_EDIT_FRONDAGE, m_Edit_Frondage_Control);
	DDX_Control(pDX, IDC_EDIT_DEVIOUSNESS, m_Edit_Deviousness_Control);
	DDX_Control(pDX, IDC_RATIO_DIAMETER_TRUNK_STATIC, m_Static_Ratio_Trunk2);
	DDX_Control(pDX, IDC_EDIT_PACE, m_Edit_Pace_Control);
	DDX_Control(pDX, IDC_EDIT_MAX_HEIGHT, m_Edit_Max_Height_Control);
	DDX_Control(pDX, IDC_EDIT_AGE, m_Edit_Age_Control);
	DDX_Control(pDX, IDGENERATE, m_Boton_Generate);
	DDX_Control(pDX, IDC_VARIABILITY_STATIC, m_Static_Variability);
	DDX_Control(pDX, IDC_RATIO_TRUNK_STATIC, m_Static_Ratio_Trunk);
	DDX_Control(pDX, IDC_RATIO_TOP_STATIC, m_Static_Ratio_Top);
	DDX_Control(pDX, IDC_RATIO_BRANCH_STATIC, m_Static_Ratio_Branch);
	DDX_Control(pDX, IDC_RATIO_BASE_STATIC, m_Static_Ratio_Base);
	DDX_Control(pDX, IDC_PACE_STATIC, m_Static_Pace);
	DDX_Control(pDX, IDC_MAXI_STATIC, m_Static_Max);
	DDX_Control(pDX, IDC_MIN_ANGLE_STATIC, m_Static_Min_Angle);
	DDX_Control(pDX, IDC_MAX_ANGLE_STATIC, m_Static_Max_Angle);
	DDX_Control(pDX, IDC_FRONDAGE_STATIC, m_Static_Frondage);
	DDX_Control(pDX, IDC_DEVIOUSNESS_STATIC, m_Static_Deviousness);
	DDX_Control(pDX, IDRESET, m_Boton_Reset);
	DDX_Control(pDX, IDC_AGE_STATIC, m_Static_Age);
	DDX_Text(pDX, IDC_EDIT_AGE, m_Edit_Age);
	DDX_Text(pDX, IDC_EDIT_MAX_HEIGHT, m_Edit_Max_Height);
	DDX_Text(pDX, IDC_EDIT_PACE, m_Edit_Pace);
	DDX_Text(pDX, IDC_EDIT_DEVIOUSNESS, m_Edit_Deviousness);
	DDX_Text(pDX, IDC_EDIT_FRONDAGE, m_Edit_Frondage);
	DDX_Text(pDX, IDC_EDIT_MAX_ANGLE, m_Edit_Max_Angle);
	DDX_Text(pDX, IDC_EDIT_MIN_ANGLE, m_Edit_Min_Angle);
	DDX_Text(pDX, IDC_EDIT_RATIO_BASE, m_Edit_Ratio_Base);
	DDX_Text(pDX, IDC_EDIT_RATIO_BRANCH, m_Edit_Ratio_Branch);
	DDX_Text(pDX, IDC_EDIT_RATIO_TOP, m_Edit_Ratio_Top);
	DDX_Text(pDX, IDC_EDIT_RATIO_TRUNK, m_Edit_Ratio_Trunk);
	DDX_Text(pDX, IDC_EDIT_RATIO_TRUNK2, m_Edit_Ratio_Trunk2);
	DDX_Text(pDX, IDC_EDIT_VARIABILITY, m_Edit_Variability);
	DDX_Text(pDX, IDC_EDIT_DEVIOUSNESS_ANGLE, m_Edit_Deviousness_Angle);
	DDX_Text(pDX, IDC_EDIT_TREE_CONE, m_Edit_Tree_Cone);
	DDX_Text(pDX, IDC_EDIT_VAR_TREE_CONE, m_Edit_Var_Tree_Cone);
	DDX_Text(pDX, IDC_EDIT_RATIO_DIAMETER, m_Edit_Ratio_Diameter);
	DDX_Text(pDX, IDC_EDIT_PROBABILITY_TRUNK, m_Edit_Probability_Trunk);
	DDX_Text(pDX, IDC_EDIT_GENERATION, m_Edit_Generation);
	DDX_Text(pDX, IDC_EDIT_DEVIOUSNESS_ARCH, m_Edit_Deviousness_Arch);
	//}}AFX_DATA_MAP
}

/**************************************************************/
/* Mapeo de Mensajes del Dialogo                              */
/**************************************************************/
BEGIN_MESSAGE_MAP(CArbolesDlg, CDialog)
	//{{AFX_MSG_MAP(CArbolesDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ARCHIVEV_EXIT, OnArchivevExit)
	ON_COMMAND(ID_ARCHIVEV_SAVEFILE, OnArchivevSavefile)
	ON_COMMAND(ID_ARCHIVEV_SAVEFILE_MPEG4, OnArchivevSavefileMpeg4)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_BN_CLICKED(IDRESET, OnReset)
	ON_BN_CLICKED(IDGENERATE, OnGenerate)
	ON_EN_CHANGE(IDC_EDIT_MAX_HEIGHT, OnChangeEditMaxHeight)
	ON_EN_CHANGE(IDC_EDIT_AGE, OnChangeEditAge)
	ON_EN_CHANGE(IDC_EDIT_PACE, OnChangeEditPace)
	ON_EN_CHANGE(IDC_EDIT_DEVIOUSNESS, OnChangeEditDeviousness)
	ON_EN_CHANGE(IDC_EDIT_FRONDAGE, OnChangeEditFrondage)
	ON_EN_CHANGE(IDC_EDIT_MAX_ANGLE, OnChangeEditMaxAngle)
	ON_EN_CHANGE(IDC_EDIT_MIN_ANGLE, OnChangeEditMinAngle)
	ON_EN_CHANGE(IDC_EDIT_RATIO_BASE, OnChangeEditRatioBase)
	ON_EN_CHANGE(IDC_EDIT_RATIO_BRANCH, OnChangeEditRatioBranch)
	ON_EN_CHANGE(IDC_EDIT_RATIO_TOP, OnChangeEditRatioTop)
	ON_EN_CHANGE(IDC_EDIT_RATIO_TRUNK, OnChangeEditRatioTrunk)
	ON_EN_CHANGE(IDC_EDIT_RATIO_TRUNK2, OnChangeEditRatioTrunk2)
	ON_EN_CHANGE(IDC_EDIT_VARIABILITY, OnChangeEditVariability)
	ON_EN_CHANGE(IDC_EDIT_DEVIOUSNESS_ANGLE, OnChangeEditDeviousnessAngle)
	ON_EN_CHANGE(IDC_EDIT_TREE_CONE, OnChangeEditTreeCone)
	ON_EN_CHANGE(IDC_EDIT_VAR_TREE_CONE, OnChangeEditVarTreeCone)
	ON_EN_CHANGE(IDC_EDIT_RATIO_DIAMETER, OnChangeEditRatioDiameter)
	ON_EN_CHANGE(IDC_EDIT_PROBABILITY_TRUNK, OnChangeEditProbabilityTrunk)
	ON_EN_CHANGE(IDC_EDIT_GENERATION, OnChangeEditGeneration)
	ON_EN_CHANGE(IDC_EDIT_DEVIOUSNESS_ARCH, OnChangeEditDeviousnessArch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**************************************************************/
/* Funciones manejadoras de mensajes.                         */
/**************************************************************/

/***************************************************************/
/* Funcion: OnInitDailog                                       */
/*															   */
/* Descripcion: Función que inicializa el dialogo.             */
/*                                                             */
/* Argumentos: Entrada: Sin Entradas.                          */
/*                                                             */
/*             Salida: BOOL: Utilizado para el control de erro-*/
/*                           res.                              */
/***************************************************************/
BOOL CArbolesDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	int i = 0;
	double contador = 0.0;
	char *temporal = NULL;
	string tantoporciento;

	// Generamos el almacenador de parametros
	parameters = new Parameters();
	// Generamos un arbol
	tree = new Tree();
	tree->setParameters(parameters);
	parameters->setAleator(new Aleator);

	// Indicamos el icono
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	// Inicializamos la intefaz grafica
	// Indicamos que partes de la interfaz estaran disponibles
	// Primero los botones
	m_Boton_Generate.EnableWindow(false);
	m_Boton_Reset.EnableWindow(false);
	// Despues los edit box
	m_Edit_Age_Control.EnableWindow(true);
	m_Edit_Max_Height_Control.EnableWindow(true);
	m_Edit_Pace_Control.EnableWindow(true);
	m_Edit_Ratio_Top_Control.EnableWindow(true);
	m_Edit_Ratio_Branch_Control.EnableWindow(true);
	m_Edit_Frondage_Control.EnableWindow(true);
	m_Edit_Max_Angle_Control.EnableWindow(false);
	m_Edit_Min_Angle_Control.EnableWindow(true);
	m_Edit_Ratio_Trunk_Control.EnableWindow(true);
	m_Edit_Ratio_Base_Control.EnableWindow(true);
	m_Edit_Ratio_Diameter_Control.EnableWindow(true);
	m_Edit_Ratio_Trunk2_Control.EnableWindow(true);
	m_Edit_Deviousness_Control.EnableWindow(true);
	m_Edit_Variability_Control.EnableWindow(true);
	m_Edit_Tree_Cone_Control.EnableWindow(true);
	m_Edit_Var_Tree_Cone_Control.EnableWindow(true);
	m_Edit_Deviousness_Angle_Control.EnableWindow(true);
	m_Edit_Probability_Trunk_Control.EnableWindow(true);
	m_Edit_Deviousness_Arch_Control.EnableWindow(true);
	m_Edit_Generation_Control.EnableWindow(true);
	// Por ultimo los titulos de los combo o edit box
	m_Static_Deviousness.EnableWindow(true);
	m_Static_Frondage.EnableWindow(true);
	m_Static_Ratio_Base.EnableWindow(true);
	m_Static_Ratio_Branch.EnableWindow(true);
	m_Static_Ratio_Top.EnableWindow(true);
	m_Static_Ratio_Diameter.EnableWindow(true);
	m_Static_Ratio_Trunk.EnableWindow(true);
	m_Static_Ratio_Trunk2.EnableWindow(true);
	m_Static_Variability.EnableWindow(true);
	m_Static_Max_Angle.EnableWindow(false);
	m_Static_Min_Angle.EnableWindow(true);
	m_Static_Age.EnableWindow(true);
	m_Static_Max.EnableWindow(true);
	m_Static_Pace.EnableWindow(true);
	m_Static_Deviousness_Angle.EnableWindow(true);
	m_Static_Tree_Cone.EnableWindow(true);
	m_Static_Var_Tree_Cone.EnableWindow(true);
	m_Static_Probability_Trunk.EnableWindow(true);
	m_Static_Deviousness_Arch.EnableWindow(true);
	m_Static_Generation.EnableWindow(true);

	return TRUE;  
}

/***************************************************************/
/* Funcion: OnPaint                                            */
/*															   */
/* Descripcion: Función que controla el repintado del dialogo. */
/*                                                             */
/* Argumentos: Entrada: Sin Entradas.                          */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnPaint() {
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/***************************************************************/
/* Funcion: OnQueryDragIcon                                    */
/*															   */
/* Descripcion: Función que indica que cursor mostrar mientras */
/*              se minimiza.                                   */
/*                                                             */
/* Argumentos: Entrada: Sin Entradas.                          */
/*                                                             */
/*             Salida: HCURSOR: El cursor retornado.           */
/***************************************************************/
HCURSOR CArbolesDlg::OnQueryDragIcon() {
	return (HCURSOR) m_hIcon;
}

/***************************************************************/
/* Funciones Manejadores de Mensajes del Menu                  */
/***************************************************************/

/***************************************************************/
/* Funcion: OnArchiveExit                                      */
/*															   */
/* Descripcion: Función que se encarga de atender a la acción  */
/*              de seleccionar el menu archive->exit.          */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnArchivevExit() {
	// Creamos el dialogo
	CDialogClose dlgClose;

	// Eliminamos el almacen de parametros
	if (tree != NULL) {
		delete tree;
		tree = NULL;
	}

	// Presentamos el dialogo
	dlgClose.DoModal();

	// Cerramos y destruimos la ventana
	CArbolesDlg::DestroyWindow();
}

/***************************************************************/
/* Funcion: OnArchiveSavefile                                  */
/*															   */
/* Descripcion: Función que se encarga de atender a la acción  */
/*              de seleccionar el menu archive->save file.     */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnArchivevSavefile()  {
	Structure* initial = NULL;
	CString pathName;
	CString pathName2;
	char* nombre_defecto = "Arbol0.fra";
	char* extension_defecto = "Files Fractal Tree";
	char* extensiones = "Files Fractal Tree|*.fra|All files (*.*)|*.*|";
	char* fichero = NULL;
	char* fichero2 = NULL;
	int i = 0, transformacionesOriginales = 0;
	BOOL flag = true;
	FILE* fp = NULL;

	// Abrimos el seleccionador del nombre de guardado
	FileDlg dlgSave(FALSE, extension_defecto, nombre_defecto, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extensiones, NULL);

	if (dlgSave.DoModal() == IDOK) {
		// Obtenemos el nombre de guardado
		pathName = dlgSave.GetPathName();
		
		fichero = (char*)malloc(sizeof(char) * (pathName.GetLength() + 1));
		
		for(i = 0; i < pathName.GetLength(); i++)
			fichero[i] = pathName[i];

		fichero[pathName.GetLength()] = '\0';

		// Abrimos el fichero
		fp = fopen(fichero,"w");
		if (fp == NULL) {
			free(fichero);
			// Creamos el dialogo
			CDialogErrorFile dlgErrorFile;

			// Presentamos el dialogo
			dlgErrorFile.DoModal();
			return;
		}

		// Escribirmos el fichero
		fprintf(fp,"//d0\t\td1\t\th\t\tFi\t\talfa\t\tr0x\t\tr0y\t\tr0z\n");
		initial = this->tree->getStructure();
		this->tree->print(fp,initial);

		// Cerramos el fichero y lo liberarmos
		fclose(fp);
		fp = NULL;
		free(fichero);

		// Creamos el dialogo
		CDialogInformation dlgInformation;

		// Lo presentamos al usuaario
		dlgInformation.DoModal();
	}
	else {
		return;
	}
}

/***************************************************************/
/* Funcion: OnArchiveSavefileMPEG4                             */
/*															   */
/* Descripcion: Función que se encarga de atender a la acción  */
/*              de seleccionar el menu archive->save file MPEG4*/
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnArchivevSavefileMpeg4() {
	Structure* initial = NULL;
	CString pathName;
	CString pathName2;
	char* nombre_defecto = "Arbol0.wrl";
	char* extension_defecto = "Files MPEG4";
	char* extensiones = "Files MPEG4|*.wrl|All files (*.*)|*.*|";
	char* extension_defecto2 = "Files Texture";
	char* extensiones2 = "Files Texture|*.ttx|All files (*.*)|*.*|";
	char* fichero = NULL, *cadena = NULL, *texture = NULL;
	int i = 0, transformacionesOriginales = 0;
	BOOL flag = true;
	FILE* fp = NULL;
	

	arbol++;
	cadena = (char*)malloc(sizeof(char)*10);

	// Abrimos el seleccionador del nombre de guardado
	FileDlg dlgSave(FALSE, extension_defecto, nombre_defecto, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extensiones, NULL);

	if (dlgSave.DoModal() == IDOK) {
		// Obtenemos el nombre de guardado
		pathName = dlgSave.GetPathName();
		
		fichero = (char*)malloc(sizeof(char) * (pathName.GetLength() + 1));
		
		for(i = 0; i < pathName.GetLength(); i++)
			fichero[i] = pathName[i];

		fichero[pathName.GetLength()] = '\0';

		// Abrimos el fichero
		fp = fopen(fichero,"w");
		if (fp == NULL) {
			free(fichero);
			// Creamos el dialogo
			CDialogErrorFile dlgErrorFile;

			// Presentamos el dialogo
			dlgErrorFile.DoModal();
			return;
		}

		// Abrimos un dialogo de abrir fichero
		FileDlg dlgOpen(TRUE, extension_defecto2, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extensiones2, NULL);

		// Si se acepta el dialogo
		if (dlgOpen.DoModal() == IDOK) {
			// Consguimos el nombre del fichero (path completo)
			pathName2 = dlgOpen.GetPathName();
		
			// Creamos el nombre del fichero
			texture = (char*)malloc(sizeof(char) * (pathName2.GetLength() + 1));
		
			// Copiamos el path en este variable que contendra el fichero
			for(i = 0; i < pathName2.GetLength(); i++)
				texture[i] = pathName2[i];
			texture[pathName2.GetLength()] = '\0';
		}

		sprintf(cadena,"Arbol%d",arbol);
		// Llamamos a la funcion para escribir en el fichero
		fprintf(fp,"#VRML V2.0 utf8\n");
		fprintf(fp,"Group {\n");
		fprintf(fp,"  children [\n");
		fprintf(fp,"    DirectionalLight {\n");
		fprintf(fp,"      direction 0.8 0.6 0\n");
		fprintf(fp,"    }\n");
		fprintf(fp,"    Background {\n");
		fprintf(fp,"      skyColor 0.5 0.5 0.5\n");
		fprintf(fp,"    }\n");
		fprintf(fp,"    DEF Camera Viewpoint {\n");
		fprintf(fp,"      position 0.0 0.0 400.0\n");
		fprintf(fp,"      orientation 0.0 0.0 1.0 0.0\n");
		fprintf(fp,"      fieldOfView 0.6\n");
		fprintf(fp,"      description \"Camera\"\n");
		fprintf(fp,"    }\n");
		fprintf(fp,"    DEF %s Transform {\n",cadena);
		fprintf(fp,"      translation 0.0 0.0 0.0\n");
		fprintf(fp,"      scale 0.5 0.5 0.5\n");
		fprintf(fp,"      children [\n");
		fprintf(fp,"        Transform { #Azul = Z Axis\n");
		fprintf(fp,"          rotation 1.0 0.0 0.0 1.57\n");
		fprintf(fp,"          children [\n");
		fprintf(fp,"            Shape {\n");
		fprintf(fp,"              appearance Appearance {\n");
		fprintf(fp,"                material Material {\n");
		fprintf(fp,"                  diffuseColor 0.0 0.0 1.0\n");
		fprintf(fp,"                  emissiveColor 0.0 0.0 1.0\n");
		fprintf(fp,"                }\n");
		fprintf(fp,"              }\n");
		fprintf(fp,"              geometry Cylinder {\n");
		fprintf(fp,"                height 100.0\n");
		fprintf(fp,"                radius 1.0\n");
		fprintf(fp,"              }\n");
		fprintf(fp,"            }\n");
		fprintf(fp,"          ]\n");
		fprintf(fp,"        }\n");
		fprintf(fp,"        Transform { #Verde = Y Axis\n");
		fprintf(fp,"          rotation 0.0 1.0 0.0 1.57\n");
		fprintf(fp,"          children [\n");
		fprintf(fp,"            Shape {\n");
		fprintf(fp,"              appearance Appearance {\n");
		fprintf(fp,"                material Material {\n");
		fprintf(fp,"                  diffuseColor 0.0 1.0 0.0\n");
		fprintf(fp,"                  emissiveColor 0.0 1.0 0.0\n");
		fprintf(fp,"                }\n");
		fprintf(fp,"              }\n");
		fprintf(fp,"              geometry Cylinder {\n");
		fprintf(fp,"                height 100.0\n");
		fprintf(fp,"                radius 1.0\n");
		fprintf(fp,"              }\n");
		fprintf(fp,"            }\n");
		fprintf(fp,"          ]\n");
		fprintf(fp,"        }\n");
		fprintf(fp,"        Transform { #Rojo = X Axis\n");
		fprintf(fp,"          rotation 0.0 0.0 1.0 1.57\n");
		fprintf(fp,"          children [\n");
		fprintf(fp,"            Shape {\n");
		fprintf(fp,"              appearance Appearance {\n");
		fprintf(fp,"                material Material {\n");
		fprintf(fp,"                  diffuseColor 1.0 0.0 0.0\n");
		fprintf(fp,"                  emissiveColor 1.0 0.0 0.0\n");
		fprintf(fp,"                }\n");
		fprintf(fp,"              }\n");
		fprintf(fp,"              geometry Cylinder {\n");
		fprintf(fp,"                height 100.0\n");
		fprintf(fp,"                radius 1.0\n");
		fprintf(fp,"              }\n");
		fprintf(fp,"            }\n");
		fprintf(fp,"          ]\n");
		fprintf(fp,"        }\n");
		(this->tree)->printMPEG4(fp,(this->tree)->getStructure(),texture);
		fprintf(fp,"      ]\n");
		fprintf(fp,"    }\n");
		fprintf(fp,"  ]\n");
		fprintf(fp,"}\n");
		
		// Cerramos el fichero y lo liberarmos
		fclose(fp);
		fp = NULL;
		free(fichero);
		free(cadena);
		free(texture);

		// Creamos el dialogo
		CDialogInformation dlgInformation;

		// Lo presentamos al usuario
		dlgInformation.DoModal();
	}
	else {
		return;
	}
}

/***************************************************************/
/* Funcion: OnHelpAbout                                        */
/*															   */
/* Descripcion: Función que se encarga de atender a la acción  */
/*              de seleccionar el menu help->about... .        */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnHelpAbout() {
	// Creamos el dialogo
	CDialogAbout dlgAbout;

	// Presentamos el dialogo
	dlgAbout.DoModal();
	
}

/***************************************************************/
/* Funcion: OnHelpHelp                                         */
/*															   */
/* Descripcion: Función que se encarga de atender a la acción  */
/*              de seleccionar el menu help->help.             */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnHelpHelp() {
	// Creamos el dialogo
	CDialogHelp dlgHelp;

	// Presentamos el dialogo
	dlgHelp.DoModal();
}


/***************************************************************/
/* Funciones Manejadores de Botones del dialogo                */
/***************************************************************/

/***************************************************************/
/* Funcion: OnGenerate                                         */
/*															   */
/* Descripcion: Función que se encarga de generar un arbol     */
/*              mediante los parametros obtenidos.             */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnGenerate() {
	// Variamos los parametros calculados
	parameters->change();
	// Liberamos la estructura anterior
	delete tree->getStructure();
	// Generamos el arbol
	tree->generate();
	// Creamos el dialogo de informacion
	CDialogGenerate dlgGenerate;
	// Presentamos el dialog
	dlgGenerate.DoModal();
}

/***************************************************************/
/* Funcion: OnReset                                            */
/*															   */
/* Descripcion: Función que se encarga de resetear los valores */
/*              de la aplicacion.                              */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnReset() {
	// Limpiamos los Editbox
	m_Edit_Age = " ";
	m_Edit_Max_Height = " ";
	m_Edit_Pace = " ";
	m_Edit_Ratio_Top = " ";
	m_Edit_Ratio_Branch = " ";
	m_Edit_Frondage = " ";
	m_Edit_Tree_Cone = " ";
	m_Edit_Var_Tree_Cone = " ";
	m_Edit_Max_Angle = " ";
	m_Edit_Min_Angle = " ";
	m_Edit_Ratio_Trunk = " ";
	m_Edit_Ratio_Base = " ";
	m_Edit_Ratio_Diameter = " ";
	m_Edit_Probability_Trunk = " ";
	m_Edit_Ratio_Trunk2 = " ";
	m_Edit_Deviousness_Angle = " ";
	m_Edit_Deviousness = " ";
	m_Edit_Variability = " ";
	m_Edit_Deviousness_Arch = " ";
	m_Edit_Generation = " ";
	m_Edit_Age_Control.SetSel(0, -1);
	m_Edit_Age_Control.Clear();
	m_Edit_Max_Height_Control.SetSel(0, -1);
	m_Edit_Max_Height_Control.Clear();
	m_Edit_Pace_Control.SetSel(0, -1);
	m_Edit_Pace_Control.Clear();
	m_Edit_Ratio_Top_Control.SetSel(0, -1);
	m_Edit_Ratio_Top_Control.Clear();
	m_Edit_Ratio_Branch_Control.SetSel(0, -1);
	m_Edit_Ratio_Branch_Control.Clear();
	m_Edit_Frondage_Control.SetSel(0, -1);
	m_Edit_Frondage_Control.Clear();
	m_Edit_Max_Angle_Control.SetSel(0, -1);
	m_Edit_Max_Angle_Control.Clear();
	m_Edit_Min_Angle_Control.SetSel(0, -1);
	m_Edit_Min_Angle_Control.Clear();
	m_Edit_Ratio_Trunk_Control.SetSel(0, -1);
	m_Edit_Ratio_Trunk_Control.Clear();
	m_Edit_Ratio_Base_Control.SetSel(0, -1);
	m_Edit_Ratio_Base_Control.Clear();
	m_Edit_Ratio_Diameter_Control.SetSel(0, -1);
	m_Edit_Ratio_Diameter_Control.Clear();
	m_Edit_Ratio_Trunk2_Control.SetSel(0, -1);
	m_Edit_Ratio_Trunk2_Control.Clear();
	m_Edit_Probability_Trunk_Control.SetSel(0, -1);
	m_Edit_Probability_Trunk_Control.Clear();
	m_Edit_Deviousness_Control.SetSel(0, -1);
	m_Edit_Deviousness_Control.Clear();
	m_Edit_Variability_Control.SetSel(0, -1);
	m_Edit_Variability_Control.Clear();
	m_Edit_Tree_Cone_Control.SetSel(0, -1);
	m_Edit_Tree_Cone_Control.Clear();
	m_Edit_Var_Tree_Cone_Control.SetSel(0, -1);
	m_Edit_Var_Tree_Cone_Control.Clear();
	m_Edit_Deviousness_Angle_Control.SetSel(0, -1);
	m_Edit_Deviousness_Angle_Control.Clear();
	m_Edit_Deviousness_Arch_Control.SetSel(0, -1);
	m_Edit_Deviousness_Arch_Control.Clear();
	m_Edit_Generation_Control.SetSel(0, -1);
	m_Edit_Generation_Control.Clear();
	// Las cajas de texto inhabilitadas
	m_Edit_Max_Angle_Control.EnableWindow(false);
	// Los titulos del dialogo
	m_Static_Max_Angle.EnableWindow(false);
	// Colocamos a incativos los botones
	m_Boton_Reset.EnableWindow(false);
	m_Boton_Generate.EnableWindow(false);

	// Liberamos los parametros y generamos unos nuevos
	delete parameters;
	parameters = new Parameters();
	tree->setParameters(parameters);
	parameters->setAleator(new Aleator());
}

/***************************************************************/
/* Funciones Manejadores de Combo boxes del dialogo            */
/***************************************************************/

/***************************************************************/
/* Funcion: OnChangedEditMaxHeight                             */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Max Height.        */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditMaxHeight() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Max_Height_Control.GetWindowText(max);
	m_Edit_Max_Height = max;
	contador = m_Edit_Max_Height.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	m_Edit_Max_Height = salida;
	m_Edit_Max_Height_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Max_Height_Control.SetWindowText(salida);
	parameters->setMaxHeight(cantidad);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditAge                                   */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Age.               */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditAge() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Age_Control.GetWindowText(max);
	m_Edit_Age = max;
	contador = m_Edit_Age.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	m_Edit_Age = salida;
	m_Edit_Age_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Age_Control.SetWindowText(salida);
	parameters->setAge(cantidad);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditPace                                  */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Pace Growth        */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditPace() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Pace_Control.GetWindowText(max);
	m_Edit_Pace = max;
	contador = m_Edit_Pace.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	m_Edit_Pace = salida;
	m_Edit_Pace_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Pace_Control.SetWindowText(salida);
	parameters->setPaceGrowth(cantidad);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditRatioTop                              */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Ratio Top/Trunk.   */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditRatioTop() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Ratio_Top_Control.GetWindowText(max);
	m_Edit_Ratio_Top = max;
	contador = m_Edit_Ratio_Top.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 1) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Ratio_Top = salida;
	m_Edit_Ratio_Top_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Ratio_Top_Control.SetWindowText(salida);
	parameters->setRatioTop(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditRatioBranch                           */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Ratio Branch/Branch*/
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditRatioBranch() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Ratio_Branch_Control.GetWindowText(max);
	m_Edit_Ratio_Branch = max;
	contador = m_Edit_Ratio_Branch.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 1) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Ratio_Branch = salida;
	m_Edit_Ratio_Branch_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Ratio_Branch_Control.SetWindowText(salida);
	parameters->setRatioBranch(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditFrondage                              */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Frondage.          */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditFrondage() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Frondage_Control.GetWindowText(max);
	m_Edit_Frondage = max;
	contador = m_Edit_Frondage.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 1) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Frondage = salida;
	m_Edit_Frondage_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Frondage_Control.SetWindowText(salida);
	parameters->setFrondage(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditTreeCone                              */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Tree Cone.         */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditTreeCone() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Tree_Cone_Control.GetWindowText(max);
	m_Edit_Tree_Cone = max;
	contador = m_Edit_Tree_Cone.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 180) {
		cantidad = 180;
		salida = "180";
	}
	if (cantidad <= 0) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Tree_Cone = salida;
	m_Edit_Tree_Cone_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Tree_Cone_Control.SetWindowText(salida);
	parameters->setTreeCone(parameters->radian(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditVarTreeCone                           */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Var Tree Cone.     */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditVarTreeCone() {
	CString max,salida;
	char* valor = NULL;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Var_Tree_Cone_Control.GetWindowText(max);
	m_Edit_Var_Tree_Cone = max;
	contador = m_Edit_Var_Tree_Cone.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 180) {
		cantidad = 180;
		salida = "180";
	}
	if (cantidad < 0) {
		cantidad = 0;
		salida = "0";
	}
	m_Edit_Var_Tree_Cone = salida;
	m_Edit_Var_Tree_Cone_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Var_Tree_Cone_Control.SetWindowText(salida);
	parameters->setVarTreeCone(parameters->radian(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditMaxAngle                              */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Max. Angle.        */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditMaxAngle() {
	CString max,salida;
	char* valor = NULL, *cadena = NULL;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	int cantidad = 0, cantidad2 = 0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Max_Angle_Control.GetWindowText(max);
	m_Edit_Max_Angle = max;
	contador = m_Edit_Max_Angle.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 360) {
		cantidad = 360;
		salida = "360";
	}
	m_Edit_Max_Angle = salida;
	m_Edit_Max_Angle_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Max_Angle_Control.SetWindowText(salida);
	parameters->setMaxAngle(cantidad);
	free(cadena);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditMinAngle                              */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Min. Angle.        */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditMinAngle() {
	CString max,salida,salida2;
	char* valor = NULL, *cadena = NULL;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0, cantidad2 = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	// Activamos el edit box y el titulo del maximo
	m_Edit_Max_Angle_Control.EnableWindow(true);
	m_Static_Max_Angle.EnableWindow(true);

	m_Edit_Min_Angle_Control.GetWindowText(max);
	m_Edit_Min_Angle = max;
	contador = m_Edit_Min_Angle.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 360) {
		cantidad = 360;
		salida = "360";
	}
	if (cantidad < 0) {
		cantidad = 0;
		salida = "0";
	}
	cadena = (char*)malloc(sizeof(char)*5);
	cantidad2 = cantidad +1;
	sprintf(cadena,"%d",cantidad2);
	salida2 = cadena;

	m_Edit_Min_Angle = salida;
	m_Edit_Min_Angle_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Min_Angle_Control.SetWindowText(salida);
	m_Edit_Max_Angle_Control.SetWindowText(salida2);
	parameters->setMinAngle(cantidad);
	free(cadena);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditGeneration                            */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Generation.        */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditGeneration() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Generation_Control.GetWindowText(max);
	m_Edit_Generation = max;
	contador = m_Edit_Generation.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	m_Edit_Generation = salida;
	m_Edit_Generation_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Generation_Control.SetWindowText(salida);
	parameters->setGeneration(cantidad);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditRatioTrunk                            */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Ratio Trunk/Branch.*/
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditRatioTrunk() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Ratio_Trunk_Control.GetWindowText(max);
	m_Edit_Ratio_Trunk = max;
	contador = m_Edit_Ratio_Trunk.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 0) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Ratio_Trunk = salida;
	m_Edit_Ratio_Trunk_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Ratio_Trunk_Control.SetWindowText(salida);
	parameters->setRatioTrunk(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditRatioBase                             */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Ratio Base/Height. */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditRatioBase() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Ratio_Base_Control.GetWindowText(max);
	m_Edit_Ratio_Base = max;
	contador = m_Edit_Ratio_Base.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 0) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Ratio_Base = salida;
	m_Edit_Ratio_Base_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Ratio_Base_Control.SetWindowText(salida);
	parameters->setRatioBase(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditRatioDiameter                         */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Ratio Diameter.    */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditRatioDiameter() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Ratio_Diameter_Control.GetWindowText(max);
	m_Edit_Ratio_Diameter = max;
	contador = m_Edit_Ratio_Diameter.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 0) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Ratio_Diameter = salida;
	m_Edit_Ratio_Diameter_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Ratio_Diameter_Control.SetWindowText(salida);
	parameters->setRatioDiameter2(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditRatioTrunk2                           */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Ratio Diameter     */
/*              Trunk/Branch.                                  */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditRatioTrunk2() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Ratio_Trunk2_Control.GetWindowText(max);
	m_Edit_Ratio_Trunk2 = max;
	contador = m_Edit_Ratio_Trunk2.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 0) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Ratio_Trunk2 = salida;
	m_Edit_Ratio_Trunk2_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Ratio_Trunk2_Control.SetWindowText(salida);
	parameters->setRatioDiameter(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditProbabilityTrunk                      */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Probability Trunk  */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditProbabilityTrunk() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Probability_Trunk_Control.GetWindowText(max);
	m_Edit_Probability_Trunk = max;
	contador = m_Edit_Probability_Trunk.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 100) {
		cantidad = 100;
		salida = "100";
	}
	if (cantidad < 0) {
		cantidad = 0;
		salida = "0";
	}
	m_Edit_Probability_Trunk = salida;
	m_Edit_Probability_Trunk_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Probability_Trunk_Control.SetWindowText(salida);
	parameters->setProbabilityTrunk(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditDeviousnessAngle                      */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Deviousness Angle. */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditDeviousnessAngle() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Deviousness_Angle_Control.GetWindowText(max);
	m_Edit_Deviousness_Angle = max;
	contador = m_Edit_Deviousness_Angle.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 180) {
		cantidad = 180;
		salida = "180";
	}
	if (cantidad < 0) {
		cantidad = 0;
		salida = "0";
	}
	m_Edit_Deviousness_Angle = salida;
	m_Edit_Deviousness_Angle_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Deviousness_Angle_Control.SetWindowText(salida);
	parameters->setDeviousnessAngle(cantidad);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditDeviousnessArch                       */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Deviousness Arch.  */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditDeviousnessArch() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Deviousness_Arch_Control.GetWindowText(max);
	m_Edit_Deviousness_Arch = max;
	contador = m_Edit_Deviousness_Arch.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 180) {
		cantidad = 180;
		salida = "180";
	}
	if (cantidad < 0) {
		cantidad = 0;
		salida = "0";
	}
	m_Edit_Deviousness_Arch = salida;
	m_Edit_Deviousness_Arch_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Deviousness_Arch_Control.SetWindowText(salida);
	parameters->setDeviousnessArch(cantidad);

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditDeviousness                           */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Deviousness.       */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditDeviousness() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Deviousness_Control.GetWindowText(max);
	m_Edit_Deviousness = max;
	contador = m_Edit_Deviousness.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad >= 100) {
		cantidad = 99;
		salida = "99";
	}
	if (cantidad <= 0) {
		cantidad = 1;
		salida = "1";
	}
	m_Edit_Deviousness = salida;
	m_Edit_Deviousness_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Deviousness_Control.SetWindowText(salida);
	parameters->setDeviousness(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funcion: OnChangedEditVariability                           */
/*															   */
/* Descripcion: Función que se encarga de atender a la         */
/*              escritura en el edit box de Variability.       */
/*                                                             */
/* Argumentos: Entrada: Sin Entrada.                           */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
void CArbolesDlg::OnChangeEditVariability() {
	CString max,salida;
	char* valor;
	int contador = 0, i = 0, elegidos = 0, aux = 0, flag = 0;
	float cantidad = 0.0;

	// Indicamos la posibilidad de resetear el valor
	m_Boton_Reset.EnableWindow(true);

	m_Edit_Variability_Control.GetWindowText(max);
	m_Edit_Variability = max;
	contador = m_Edit_Variability.GetLength();

	// Eliminamos caracteres no numericas (excluyendo '.')
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) 
			elegidos++;
		else if  ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				elegidos++;
				flag = 1;
			}
		}
	}

	// Combertimos de cadena a valor numerico
	valor = (char*)malloc(sizeof(char)*(elegidos + 1));
	aux = 0;
	flag = 0;
	for(i = 0; i < contador; i++) {
		if ((max[i] == '0') | (max[i] == '1') | (max[i] == '2') |
			(max[i] == '3') | (max[i] == '4') | (max[i] == '5') |
			(max[i] == '6') | (max[i] == '7') | (max[i] == '8') |
			(max[i] == '9')) {
				valor[aux] = max[i];
				aux++;
		}
		else if ((max[i] == '.') | (max[i] == ',')) {
			if (flag == 0) {
				valor[aux] = '.';
				aux++;
				flag = 1;
			}
		}
	}
	valor[elegidos] = '\0';
	flag = 0;
	cantidad = atof(valor);
	aux = 0;
	for(i = 0; i < contador; i++) {
		if ((valor[i] == '0') | (valor[i] == '1') | (valor[i] == '2') |
			(valor[i] == '3') | (valor[i] == '4') | (valor[i] == '5') |
			(valor[i] == '6') | (valor[i] == '7') | (valor[i] == '8') |
			(valor[i] == '9') | (valor[i] == '.')) {
			if ((i == 0) && (contador >= 2) && (valor[i] == '0') && (valor[i+1] != '.'))
				flag = 1;
			if (flag == 0) {
				salida.Insert(aux,valor[i]);
				aux++;
			}
			else
				flag = 0;
		}
	}
	free(valor);
	if (cantidad > 100) {
		cantidad = 100;
		salida = "100";
	}
	if (cantidad < 0) {
		cantidad = 0;
		salida = "0";
	}
	m_Edit_Variability = salida;
	m_Edit_Variability_Control.SetSel(-1);
	if (max != salida)
		m_Edit_Variability_Control.SetWindowText(salida);
	parameters->setVariability(parameters->ratio1(cantidad));

	// Si todos los parametros tiene valor se activa generar
	if (parameters->complete() == 0)
		m_Boton_Generate.EnableWindow(true);
}

/***************************************************************/
/* Funciones Auxiliares o de Ayuda                             */
/***************************************************************/

/***************************************************************/
/* Funcion: crearDouble                                        */
/*															   */
/* Descripcion: Función que se encarga de crear una cadena de  */
/*              caracteres que representa un valor numerico    */
/*              decimal                                        */
/*                                                             */
/* Argumentos: Entrada: double valor: El valor decimal a utili-*/
/*                                    zar.                     */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
char* CArbolesDlg::crearDouble(double valor) {
	char numero[33];
	char *resultado = NULL, *resultado2 = NULL;
	int entera = 0, contador = 0, negativo = 0, slot = 0;
	double decimal = 0.0;
	int i = 0;
	bool flag = true;

	// Se divide al numero en su parte entera y en su parte decimal
	if (valor >= 0) {
		decimal = valor - floor(valor);
		entera = valor - decimal;
	}
	else {
		decimal = ceil(valor) - valor;
		entera = valor + decimal;
	}

	// Pasamos la parte entera
	itoa(entera,numero,10);

	if ((entera == 0) & (valor < 0)) {
		contador = 0;
		negativo = 1;
	}

	// Calculamos el numero de cifras 
	for(;flag;) {
		if (entera == 0) {
			flag = false;
			if ((contador == 0) && (valor >= 0))
				contador++;
		}
		else {
			contador++;
			entera = (int)floor((long double)entera/10);
		}
	}
	
	// Si es negativo imprimimos el signo -
	if (valor < 0) 
		contador++;
	
	//pasamos al resultado final la parte entera.
	resultado = (char*)malloc(sizeof(char*)*(contador + 8));
	if (negativo == 1) resultado[0] = '-';
	for(i = 0 + negativo; i < contador; i++)
		resultado[i] = numero[i];
	resultado[contador] = '.';
	flag = true;
	slot = contador;
	contador = 0;

	// Calculamos el numero de cifras 
	for(;flag & (contador != 6);) {
		if (decimal == 0.0) {
			if (contador == 0) {
				resultado[contador + slot + 1] = '0';
				resultado[contador + slot + 2] = '\0';
				return resultado;
			}
			flag = false;
		}
		else {
			contador++;
			entera = floor(decimal*10);

			decimal = (decimal * 10) - floor(decimal*10);		

			itoa(entera,numero,10);
			resultado[contador+slot] = numero[0];
		}
	}

	resultado[contador + slot + 1] = '\0';

	return resultado;
}

/***************************************************************/
/* Funcion: crearEntero                                        */
/*															   */
/* Descripcion: Función que se encarga de crear una cadena de  */
/*              caracteres que representa un valor numerico    */
/*              entero                                         */
/*                                                             */
/* Argumentos: Entrada: double valor: El valor entero a utili- */
/*                                    zar.                     */
/*                                                             */
/*             Salida: Sin Salida.                             */
/***************************************************************/
char* CArbolesDlg::crearEntero(double valor) {
	char numero[33], *resultado = NULL;
	int entera = 0, contador = 0;
	double decimal = 0.0;
	int i = 0;
	bool flag = true;

	// Se divide al numero en su parte entera y en su parte decimal
	decimal = valor - floor(valor);
	entera = valor - decimal;

	// Pasamos la parte entera
	itoa(entera,numero,10);

	if (entera == 0)
		contador = 1;

	// Calculamos el numero de cifras 
	for(;flag;) {
		if (entera == 0)
			flag = false;
		else {
			contador++;
			entera = (int)floor((long double)entera/10);
		}
	}
	
	// Si es negativo imprimimos el signo -
	if (valor < 0) 
		contador++;

	resultado = (char*)malloc(sizeof(char)*(contador+1));

	for(i = 0; i < contador; i++)
		resultado[i] = numero[i];
	resultado[contador] = '\0';

	return resultado;
}

