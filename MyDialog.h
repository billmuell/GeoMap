#pragma once
#include "afxcmn.h"
#include "resource.h"


// MyDialog dialog

class MyDialog : public CAcUiDialog
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(const CStringPairs &LayerList, CWnd* pParent = NULL);   // standard constructor
	virtual ~MyDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 BOOL	addListCtrlField (int iItem, CString FieldName, CString FieldValue);
 void initListCtrl();
 void DisplayListCtrl();
 virtual BOOL OnInitDialog();
 virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
  CListCtrl m_CListCtrl;
  const CStringPairs &m_LayerList;
};
