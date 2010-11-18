#pragma once

#include "afxcmn.h"
#include "resource.h"

#include "Connection.h"
#include "Provider.h"
#include "afxwin.h"

// Cuadro de diálogo de DlgProviderParam

class DlgProviderParam : public CDialog
{
protected:
  CProvider _provider;
  CConnection * _connection;
  
  ListaControles* _etiquetas;
  ListaControles* _paramControls;
  
  CButton _cancelButton;
  CButton _connectButton;

  DECLARE_DYNAMIC(DlgProviderParam)

public:
	DlgProviderParam(CProvider provider, /* int ParentX, int ParentY, */ CWnd* pParent = NULL);   // Constructor estándar
	virtual ~DlgProviderParam();

public:
  CConnection * GetConnection() const;
  
protected:
  // Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PROVIDER_PARAMS };

	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
  virtual BOOL OnInitDialog();
  virtual void OnCancel();
  virtual void OnOK();
  virtual void hidePreviousCtrls();

public:
  virtual void showProviderParamsCtrls();
  virtual bool fillEnumerablePropertiesValues(CConnectionParam & param, CComboBox * enums);

	DECLARE_MESSAGE_MAP()
};
