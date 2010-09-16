// DlgProviders.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgProviders.h"
//#include "DlgProviderParam.h"
//#include "DlgLayers.h"


// Cuadro de diálogo de DlgProviders

IMPLEMENT_DYNAMIC(DlgProviders, CDialog)

BEGIN_MESSAGE_MAP(DlgProviders, CDialog)
  ON_NOTIFY(NM_CLICK, IDC_TREE1, &DlgProviders::OnNMClickTree1)
END_MESSAGE_MAP()

DlgProviders::DlgProviders(CStringPairs providersList, CWnd* pParent /* = NULL */)
	: CDialog(DlgProviders::IDD, pParent), _providersList(providersList), _providerName(L"")
{

}

DlgProviders::~DlgProviders()
{
}

String DlgProviders::GetProviderName() const { return _providerName; }

void DlgProviders::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TREE1, m_TreeList);
}

BOOL DlgProviders::OnInitDialog() {
  CDialog::OnInitDialog();
  
  fillProvidersList();
  
  return FALSE;
}

void DlgProviders::fillProvidersList() {
  for (int i = 0 ; i < _providersList.size() ; i++) { 
    String itemStr = L"Add a new connection with ";
    itemStr.append(_providersList[i].first);
    HTREEITEM provider = m_TreeList.InsertItem(itemStr.c_str());
    if (i == 0) m_TreeList.SelectItem(provider);
    m_TreeList.SetItemData(provider, i);
  }
}

// Controladores de mensajes de DlgProviders

void DlgProviders::OnCancel()
{
  CDialog::OnCancel();
}

void DlgProviders::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
  DWORD dw = GetMessagePos(); // See where cursor is on tree control
  CPoint pt(GET_X_LPARAM(dw), GET_Y_LPARAM(dw));
  m_TreeList.ScreenToClient(&pt);
  UINT uFlags = 0;
  HTREEITEM hti = m_TreeList.HitTest(pt, &uFlags);
  
  *pResult = 0;

  int providerIndex = m_TreeList.GetItemData(hti); //m_TreeList.GetSelectedItem());
  _providerName = _providersList[providerIndex].second;
  
  /*DlgProviderParam dlgProviders(_providersList[providerIndex].second, this);
  dlgProviders.DoModal();
  
  FdoPtr<FdoIConnection> fdoConnection = dlgProviders.GetConnection();
  if (fdoConnection == NULL) return;
  
  DlgLayers dlgLayers(fdoConnection, this);
  dlgLayers.DoModal();*/

  EndDialog(NULL);
}
