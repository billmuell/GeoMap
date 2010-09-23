#pragma once
#include "afxwin.h"

class CButtonFile :
  public CButton
{
public:
  CButtonFile(void);
public:
  ~CButtonFile(void);
public:
  void SetTextBoxFile(CEdit * textBox);

protected:
  //DECLARE_DYNAMIC(CButtonFile)
  DECLARE_MESSAGE_MAP()
  //{{AFX_MSG(CButtonFile)
    afx_msg void OnBnClickedButton();
  //}}AFX_MSG

protected:
  CEdit * _textBox;
};