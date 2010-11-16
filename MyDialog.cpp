// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MyDialog.h"

// MyDialog dialog
IMPLEMENT_DYNAMIC(MyDialog, CAcUiDialog)

MyDialog::MyDialog(const StringPairs &LayerList, CWnd* pParent /*=NULL*/)
	: CAcUiDialog(MyDialog::IDD, pParent) , _layerList(LayerList) { }

MyDialog::~MyDialog() { }

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
  CAcUiDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST1, m_CListCtrl);
}

BOOL MyDialog::OnInitDialog()
{
  CAcUiDialog::OnInitDialog();
  initListCtrl();
  DisplayListCtrl();
  return TRUE;
}

void MyDialog::OnOK()
{
  CAcUiDialog::OnOK();
}

void MyDialog::initListCtrl()
{
  // calculate the size of our columns
  RECT listRect;
  m_CListCtrl.GetClientRect(&listRect);
  int nListWidth = (listRect.right - listRect.left);
  int nVScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL); 
  int nCol0w = int(nListWidth * 0.65);
  int nCol1w = nListWidth - nCol0w - nVScrollBarWidth;

  // add two columns
  LV_COLUMN Column;
  Column.mask	    = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
  Column.cx	      = nCol1w ;
  Column.pszText  = _T("Layer Name");
  Column.cchTextMax = 64;
  Column.iSubItem = 1;
  m_CListCtrl.InsertColumn (0, &Column);

  Column.mask	    = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
  Column.cx	      = nCol0w - 6;
  Column.pszText  = _T("Layer Color");
  Column.cchTextMax = 64;
  Column.iSubItem = 0;
  m_CListCtrl.InsertColumn (1, &Column);

  long Style = LVS_SHOWSELALWAYS;
  long ExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
  m_CListCtrl.ModifyStyle(NULL,Style,0);
  m_CListCtrl.SetExtendedStyle (ExStyle);
}


BOOL MyDialog::addListCtrlField( int iItem, CString FieldName, CString FieldValue )
{
  FieldName.TrimRight();
  FieldName.TrimLeft();
  FieldValue.TrimRight();
  FieldValue.TrimLeft();

  LV_ITEM FieldData;

  FieldData.iItem = iItem;
  FieldData.mask  = LVIF_TEXT;
  FieldData.iSubItem = 0;
  FieldData.pszText = (TCHAR*)(LPCTSTR)FieldValue;
  FieldData.cchTextMax = FieldValue.GetLength ();
  if (m_CListCtrl.InsertItem (&FieldData) != iItem)
    return FALSE;

  FieldData.iItem = iItem;
  FieldData.mask  = LVIF_TEXT;
  FieldData.iSubItem = 1;
  FieldData.pszText = (TCHAR*)(LPCTSTR)FieldName;
  FieldData.cchTextMax = FieldName.GetLength () + 1;
  if (m_CListCtrl.SetItem (&FieldData) == FALSE)
    return FALSE;

  return TRUE;
} 

void MyDialog::DisplayListCtrl()
{
  for (int i = 0 ; i < _layerList.size() ; i++)
  { 
    addListCtrlField(i ,  _layerList[i].second.c_str() , _layerList[i].first.c_str());
  }
  m_CListCtrl.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
  m_CListCtrl.EnsureVisible(0, FALSE);
}

BEGIN_MESSAGE_MAP(MyDialog, CAcUiDialog)
END_MESSAGE_MAP()
