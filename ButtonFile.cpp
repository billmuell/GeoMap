#include "stdafx.h"
#include "ButtonFile.h"

BEGIN_MESSAGE_MAP(CButtonFile, CButton)
  //{{AFX_MSG_MAP(CButtonFile)
  ON_CONTROL_REFLECT(BN_CLICKED, OnBnClickedButton)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CButtonFile::CButtonFile(void) : _textBox(NULL)
{
}

CButtonFile::~CButtonFile(void)
{
}

void CButtonFile::SetTextBoxFile(CEdit * textBox) { _textBox = textBox; }

void CButtonFile::OnBnClickedButton()
{
  CFileDialog fileDlg(TRUE, _defaultExt.c_str(), NULL, OFN_HIDEREADONLY, _filterStr.c_str());
  if(fileDlg.DoModal() != IDOK ) return;
  
  _textBox->SetWindowTextW(fileDlg.GetFileName());
}