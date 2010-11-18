#pragma once

#include "resource.h"
#include "afxwin.h"
#include "FeatureClass.h"

// Cuadro de di�logo de DlgLayers
class DlgLayers : public CDialog
{
protected:
  String _featureClassName;
  FeatureClasses * _featureClasses;

  CListBox _layersList;
  CButton _cancelButton;
  CButton _acceptButton;

public:
  String GetFeatureClassName();
  
  DECLARE_DYNAMIC(DlgLayers)

public:
	DlgLayers(FeatureClasses * featureClasses, CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~DlgLayers();

// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_LAYERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
  virtual BOOL OnInitDialog();
  virtual void OnCancel();
  virtual void OnOK();
  
  virtual BOOL FillLayersList();

	DECLARE_MESSAGE_MAP()
};
