#pragma once

#include "resource.h"

#include "Connection.h"
#include "afxwin.h"
#include "FeatureClass.h"

// Cuadro de di�logo de DlgLayers

class DlgLayers : public CDialog
{
protected:
  CConnection * _connection;
  CFeatureClass * _featureClass;

public:
  void SetConnection(CConnection * connection);
  CFeatureClass * GetFeatureClass();

  DECLARE_DYNAMIC(DlgLayers)

public:
	DlgLayers(CConnection * connection, CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~DlgLayers();

// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_LAYERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
  virtual BOOL OnInitDialog();
  virtual void OnCancel();
  virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
  CListBox lstLayers;
};
