#pragma once

#include "afxcmn.h"
#include "resource.h"

// Cuadro de diálogo de DlgProviders

class DlgProviders : public CDialog
{
public:
  StringPairs _providersList;
  String _providerName;

  CTreeCtrl m_TreeList;
  
	DECLARE_DYNAMIC(DlgProviders)

public:
	DlgProviders(StringPairs providersList, CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgProviders();
  virtual String GetProviderName() const;

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PROVIDERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
  virtual BOOL OnInitDialog();
  virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

protected:
  virtual void fillProvidersList();

public:
  afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
