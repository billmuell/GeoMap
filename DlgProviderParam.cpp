// DlgProviderParam.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgProviderParam.h"
#include "ButtonFile.h"
#include "AppConf.h"

// Cuadro de diálogo de DlgProviderParam

IMPLEMENT_DYNAMIC(DlgProviderParam, CDialog)
BEGIN_MESSAGE_MAP(DlgProviderParam, CDialog)
END_MESSAGE_MAP()

DlgProviderParam::DlgProviderParam(CProvider provider, /* int ParentX, int ParentY, */ CWnd* pParent /*=NULL*/)
: CDialog(DlgProviderParam::IDD, pParent), _provider(provider), 
  _paramControls(NULL), _etiquetas(NULL),
  _connection(NULL)
{

}

DlgProviderParam::~DlgProviderParam()
{
  hidePreviousCtrls();
}

void DlgProviderParam::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDCANCEL, _cancelButton);
  DDX_Control(pDX, IDOK, _connectButton);
}

BOOL DlgProviderParam::OnInitDialog() {
  CDialog::OnInitDialog();
  
  CLocale locale = CAppConf::GetLocale();
  
  SetWindowText((locale.GetTranslation(L"Connection parameters for ") + locale.GetTranslation(_provider.GetName())).c_str());
  _connectButton.SetWindowTextW(locale.GetTranslation(L"Connect").c_str());
  _cancelButton.SetWindowTextW(locale.GetTranslation(L"Cancel").c_str());

  showProviderParamsCtrls();
  
  return FALSE;
}

void DlgProviderParam::hidePreviousCtrls() {
  CWnd* control = NULL;
  ListaControles::iterator iteratorControles;
  if (_paramControls) {
    if (!_paramControls->empty()) {
      for (iteratorControles = _paramControls->begin(); iteratorControles != _paramControls->end(); iteratorControles++) ::DestroyWindow(::GetDlgItem(m_hWnd, *iteratorControles));
      _paramControls->clear();
      delete _paramControls;
    }
    _paramControls = NULL;
  }
  if (_etiquetas) {
    if (!_etiquetas->empty()) {
      for (iteratorControles = _etiquetas->begin(); iteratorControles != _etiquetas->end(); iteratorControles++) ::DestroyWindow(::GetDlgItem(m_hWnd, *iteratorControles));
      _etiquetas->clear();
      delete _etiquetas;
    }
    _etiquetas = NULL;
  }
}

void DlgProviderParam::showProviderParamsCtrls() {
  hidePreviousCtrls();
  
  CConnection conn;
  try {
    conn = _provider.CreateConnection();
  } catch(...) {
    EndDialog(NULL);
    return;
  }
  
  CConnectionParams params = conn.GetParams();
  
  _paramControls = new ListaControles();
  _etiquetas = new ListaControles();
  
  int numControl = 1;
  CRect rect(10, 0, 300, 0);
  
  CLocale locale = CAppConf::GetLocale();
  for (CConnectionParams::iterator param = params.begin(); param != params.end(); param++) {
    rect.top = rect.bottom + 10;
    rect.bottom = rect.top + 15;
    rect.right = 300;
    
    CStatic * label = new CStatic();
    label->Create((locale.GetTranslation(param->GetDisplayName()) + (param->IsRequired() ? L"*" : L"")).c_str(), WS_VISIBLE | SS_LEFT | SS_NOPREFIX | SS_SIMPLE | WS_CHILD, rect, this, IDC_CONTROLES + numControl);
    label->SetFont(GetFont());
    
    _etiquetas->push_back(IDC_CONTROLES + numControl);
    numControl++;
    
    rect.top = rect.bottom;
    rect.bottom = rect.top + 20;
    
    if (param->IsEnumerable()) {
      CComboBox * enums = new CComboBox();
      enums->Create(CBS_DROPDOWNLIST | WS_BORDER | WS_VSCROLL | WS_TABSTOP | WS_VISIBLE, 
        rect, this, IDC_CONTROLES + numControl);
      enums->SetFont(GetFont());

      _paramControls->push_back(IDC_CONTROLES + numControl);
      numControl++;
      
      if (!fillEnumerablePropertiesValues(*param, enums)) {
        // TODO: Tenemos que volver a intentar llenarlo cuando se complete con éxito la conexión
        ;
      }
    
    } else {
      CEdit * value = new CEdit();
      
      if (param->IsFilePath() || param->IsFileName()) {
        rect.left = rect.right - 30;
        rect.right = rect.left + 30;
        
        CButtonFile * file = new CButtonFile();
        file->Create(L"...", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 
          rect, this, IDC_CONTROLES + numControl);
        file->SetFont(GetFont());
        file->SetTextBoxFile(value);
        
        numControl++;
        
        rect.right = rect.left - 10;
        rect.left = 10;
      }
      
      value->CreateEx(WS_EX_CLIENTEDGE, L"EDIT", L"", 
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_LEFT | ES_AUTOHSCROLL, 
        rect, this, IDC_CONTROLES + numControl);
      value->SetFont(GetFont());
      if (param->IsProtected()) value->SetPasswordChar('*');
      
      _paramControls->push_back(IDC_CONTROLES + numControl);
      numControl++;
    }
  }
}

bool DlgProviderParam::fillEnumerablePropertiesValues(CConnectionParam & param, CComboBox * enums) {
  Strings enumValues = param.GetEnumValues();
  for (Strings::iterator it = enumValues.begin(); it != enumValues.end(); it++) {
    enums->AddString(it->c_str());
  }
  if (enums->GetCount() != 0) enums->SetCurSel(0);
  
  return true;
}

// Controladores de mensajes de DlgProviderParam
void DlgProviderParam::OnCancel()
{
  if (_connection != NULL) {
    try {
      _connection->Close();
    } catch (...) {
    }  
    _connection = NULL;
  }

  CDialog::OnCancel();
}

void DlgProviderParam::OnOK()
{
  String connString = L"";
  CString label = L"";
  CString value = L"";
  
  CLocale locale = CAppConf::GetLocale();

  ListaControles::iterator itParam;
  ListaControles::iterator itValues;
  for (itParam = _etiquetas->begin(), itValues = _paramControls->begin(); itParam != _etiquetas->end() && itValues != _paramControls->end(); itParam++, itValues++) {
    GetDlgItemText(*itParam, label);
    GetDlgItemText(*itValues, value);
    if (label.Right(1) == "*") label = label.Left(label.GetLength() - 1);
    connString += locale.GetOriginal(String(label));
    connString += L"= " + value + L";";
  }
  if (_connection == NULL) _connection = new CConnection(_provider.GetName());
  _connection->SetConnectionString(connString);

  try {
		FdoConnectionState state = _connection->Open();
    if (state != FdoConnectionState_Open) {
      if (state == FdoConnectionState_Pending) {
        for (itParam = _etiquetas->begin(), itValues = _paramControls->begin(); itParam != _etiquetas->end() && itValues != _paramControls->end(); itParam++, itValues++) {
          GetDlgItemText(*itParam, label);
          if (label.Right(1) == "*") label = label.Left(label.GetLength() - 1);
          
          CConnectionParam param = _connection->GetParam(locale.GetOriginal(String(label)));
          if (param.IsEnumerable()) {
            CComboBox * cbo = (CComboBox*)GetDlgItem(*itValues);
            if (cbo != NULL &&
                cbo->GetCount() == 0) {
              fillEnumerablePropertiesValues(param, cbo);
              if (cbo->GetCount() == 1) {
                cbo->SetCurSel(0);
                DlgProviderParam::OnOK();
              } else {
                AfxMessageBox((locale.GetTranslation(L"You have to provide ") + locale.GetTranslation(param.GetDisplayName())).c_str());
              }
            } else if (cbo->GetCurSel() < 0) {
              AfxMessageBox((locale.GetTranslation(L"You have to provide ") + locale.GetTranslation(param.GetDisplayName())).c_str());
            }
          }
        }
      }
      
      return;
    }
  } catch (FdoConnectionException * ce) {
    AfxMessageBox(ce->GetExceptionMessage());
    _connection->Close();
    _connection = NULL;
    return;
	} catch (FdoException * e) {
    AfxMessageBox(e->GetExceptionMessage());
    _connection->Close();
    _connection = NULL;
    return;
	}
  
  _connection->Close();
  
  EndDialog(NULL);
}

CConnection * DlgProviderParam::GetConnection() const { return _connection; }