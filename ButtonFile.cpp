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
  /*// TODO: Add your control notification handler code here
  CFile flEmployees;
  char strFilter[] = { "Employees Records (*.mpl)|*.mpl|Palace Ice Cream Files (*.pis)|*.pis|All Files (*.*)|*.*||" };

  CFileDialog FileDlg(TRUE, ".mpl", NULL, 0, strFilter);

  if( FileDlg.DoModal() != IDOK ) return;

  if( flEmployees.Open(FileDlg.GetFileName(), CFile::modeRead) == FALSE ) return;
  CArchive ar(&flEmployees, CArchive::load);
  
  ar >> m_FirstName >> m_LastName >> m_Address >> m_City >> m_State >> m_ZIPCode >> m_HourlySalary >> m_EmploymentStatus;
  ar.Close();
  
  flEmployees.Close();

  UpdateData(FALSE);*/
}