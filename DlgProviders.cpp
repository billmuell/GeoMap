// DlgProviders.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgProviders.h"
#include "AppConf.h"
#include "Locale.h"


// Cuadro de diálogo de DlgProviders

IMPLEMENT_DYNAMIC(DlgProviders, CDialog)

BEGIN_MESSAGE_MAP(DlgProviders, CDialog)
  ON_NOTIFY(NM_CLICK, IDC_TREE1, &DlgProviders::OnNMClickTree1)
END_MESSAGE_MAP()

DlgProviders::DlgProviders(StringPairs providersList, CWnd* pParent /* = NULL */)
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
  DDX_Control(pDX, IDC_TREE1, _treeList);
  DDX_Control(pDX, IDCANCEL, _cancelButton);
}

BOOL DlgProviders::OnInitDialog() {
  CDialog::OnInitDialog();
  
  CLocale locale = CAppConf::GetLocale();
  SetWindowText(locale.GetTranslation(L"Select a provider").c_str());
  _cancelButton.SetWindowTextW(locale.GetTranslation(L"Cancel").c_str());

  fillProvidersList();
  
  return FALSE;
}

void DlgProviders::fillProvidersList() {
  CLocale locale = CAppConf::GetLocale();
  for (int i = 0 ; i < _providersList.size() ; i++) { 
    String itemStr = locale.GetTranslation(L"Add a new connection with ");
    itemStr.append(_providersList[i].first);
    HTREEITEM provider = _treeList.InsertItem(itemStr.c_str());
    if (i == 0) _treeList.SelectItem(provider);
    _treeList.SetItemData(provider, i);
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
  _treeList.ScreenToClient(&pt);
  UINT uFlags = 0;
  HTREEITEM hti = _treeList.HitTest(pt, &uFlags);
  
  *pResult = 0;

  int providerIndex = _treeList.GetItemData(hti); //_treeList.GetSelectedItem());
  _providerName = _providersList[providerIndex].second;
  
  /*DlgProviderParam dlgProviders(_providersList[providerIndex].second, this);
  dlgProviders.DoModal();
  
  FdoPtr<FdoIConnection> fdoConnection = dlgProviders.GetConnection();
  if (fdoConnection == NULL) return;
  
  DlgLayers dlgLayers(fdoConnection, this);
  dlgLayers.DoModal();*/

  EndDialog(NULL);
}
