#pragma once

#include "resource.h"

#include "Connection.h"
#include "afxwin.h"
#include "FeatureClass.h"

typedef std::map<String, CFeatureClass*> FeatureClasses;

// Cuadro de diálogo de DlgLayers
class DlgLayers : public CDialog
{
protected:
  CConnection * _connection;
  CFeatureClass * _featureClass;
  FeatureClasses features;

public:
  void SetConnection(CConnection * connection);
  CFeatureClass * GetFeatureClass();

  DECLARE_DYNAMIC(DlgLayers)

public:
	DlgLayers(CConnection * connection, CWnd* pParent = NULL);   // Constructor estándar
	virtual ~DlgLayers();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_LAYERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
  virtual BOOL OnInitDialog();
  virtual void OnCancel();
  virtual void OnOK();
  
  virtual BOOL FillLayersList(const String & schemaName);

	DECLARE_MESSAGE_MAP()
public:
  CListBox lstLayers;
};
