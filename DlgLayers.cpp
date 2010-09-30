// DlgLayers.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgLayers.h"

// Cuadro de diálogo de DlgLayers

IMPLEMENT_DYNAMIC(DlgLayers, CDialog)

DlgLayers::DlgLayers(FeatureClasses * featureClasses, CWnd* pParent /*=NULL*/)
	: CDialog(DlgLayers::IDD, pParent), _featureClasses(featureClasses)
{
}

DlgLayers::~DlgLayers()
{
}

String DlgLayers::GetFeatureClassName() { return _featureClassName; }

void DlgLayers::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST1, lstLayers);
}

BOOL DlgLayers::OnInitDialog() {
  CDialog::OnInitDialog();
  
  return FillLayersList();
}

BOOL DlgLayers::FillLayersList()
{ 
  for (FeatureClasses::iterator it = _featureClasses->begin(); it != _featureClasses->end(); it++) {
    lstLayers.AddString(it->first.c_str());
  }
  
  return TRUE;
}

void DlgLayers::OnCancel() {
  _featureClassName = L"";

  CDialog::OnCancel();
}

void DlgLayers::OnOK() {
  CString layer;
  lstLayers.GetText(lstLayers.GetCurSel(), layer);
  _featureClassName = layer;
  
  EndDialog(NULL);
}

BEGIN_MESSAGE_MAP(DlgLayers, CDialog)
END_MESSAGE_MAP()

// Controladores de mensajes de DlgLayers
