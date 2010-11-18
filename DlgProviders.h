#pragma once

#include "afxcmn.h"
#include "resource.h"
#include "afxwin.h"

// Cuadro de di�logo de DlgProviders

class DlgProviders : public CDialog
{
public:
  StringPairs _providersList;
  String _providerName;

  CTreeCtrl _treeList;
  CButton _cancelButton;

  DECLARE_DYNAMIC(DlgProviders)

public:
	DlgProviders(StringPairs providersList, CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgProviders();
  virtual String GetProviderName() const;

// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_PROVIDERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
  virtual BOOL OnInitDialog();
  virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

protected:
  virtual void fillProvidersList();

protected:
  afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
