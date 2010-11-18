// DlgLayers.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgLayers.h"
#include "Locale.h"
#include "AppConf.h"

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
  DDX_Control(pDX, IDC_LIST1, _layersList);
  DDX_Control(pDX, IDCANCEL, _cancelButton);
  DDX_Control(pDX, IDOK, _acceptButton);
}

BOOL DlgLayers::OnInitDialog() {
  CDialog::OnInitDialog();
  
  CLocale locale = CAppConf::GetLocale();
  
  SetWindowText(locale.GetTranslation(L"Select layer").c_str());
  _acceptButton.SetWindowTextW(locale.GetTranslation(L"Accept").c_str());
  _cancelButton.SetWindowTextW(locale.GetTranslation(L"Cancel").c_str());
  
  return FillLayersList();
}

BOOL DlgLayers::FillLayersList()
{ 
  for (FeatureClasses::iterator it = _featureClasses->begin(); it != _featureClasses->end(); it++) {
    _layersList.AddString(it->first.c_str());
  }
  
  return TRUE;
}

void DlgLayers::OnCancel() {
  _featureClassName = L"";

  CDialog::OnCancel();
}

void DlgLayers::OnOK() {
  CString layer;
  _layersList.GetText(_layersList.GetCurSel(), layer);
  _featureClassName = layer;
  
  EndDialog(NULL);
}

BEGIN_MESSAGE_MAP(DlgLayers, CDialog)
END_MESSAGE_MAP()

// Controladores de mensajes de DlgLayers
