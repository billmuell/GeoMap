// DlgProviderParam.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgProviderParam.h"

// Cuadro de diálogo de DlgProviderParam

IMPLEMENT_DYNAMIC(DlgProviderParam, CDialog)
BEGIN_MESSAGE_MAP(DlgProviderParam, CDialog)
END_MESSAGE_MAP()

DlgProviderParam::DlgProviderParam(CProvider provider, /* int ParentX, int ParentY, */ CWnd* pParent /*=NULL*/)
: CDialog(DlgProviderParam::IDD, pParent), _provider(provider), 
  m_ParamCtrls(NULL), m_Etiquetas(NULL),
  m_Connection(NULL)
{

}

DlgProviderParam::~DlgProviderParam()
{
  hidePreviousCtrls();
}

void DlgProviderParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL DlgProviderParam::OnInitDialog() {
  CDialog::OnInitDialog();
  
  SetWindowText((_T("Connection parameters for ") + _provider.GetName()).c_str());
  showProviderParamsCtrls();
  
  return FALSE;
}

void DlgProviderParam::hidePreviousCtrls() {
  CWnd* control = NULL;
  ListaControles::iterator iteratorControles;
  if (m_ParamCtrls) {
    if (!m_ParamCtrls->empty()) {
      for (iteratorControles = m_ParamCtrls->begin(); iteratorControles != m_ParamCtrls->end(); iteratorControles++) ::DestroyWindow(::GetDlgItem(m_hWnd, *iteratorControles));
      m_ParamCtrls->clear();
      delete m_ParamCtrls;
    }
    m_ParamCtrls = NULL;
  }
  if (m_Etiquetas) {
    if (!m_Etiquetas->empty()) {
      for (iteratorControles = m_Etiquetas->begin(); iteratorControles != m_Etiquetas->end(); iteratorControles++) ::DestroyWindow(::GetDlgItem(m_hWnd, *iteratorControles));
      m_Etiquetas->clear();
      delete m_Etiquetas;
    }
    m_Etiquetas = NULL;
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
  
  m_ParamCtrls = new ListaControles();
  m_Etiquetas = new ListaControles();
  
  int numControl = 1;
  CRect rect(10, 0, 300, 0);

  for (CConnectionParams::iterator param = params.begin(); param != params.end(); param++) {
    rect.top = rect.bottom + 10;
    rect.bottom = rect.top + 15;
    rect.right = 300;
    
    CStatic * label = new CStatic();
    label->Create((param->GetDisplayName() + (param->IsRequired() ? L"*" : L"")).c_str(), WS_VISIBLE | SS_LEFT | SS_NOPREFIX | SS_SIMPLE | WS_CHILD, rect, this, IDC_CONTROLES + numControl);
    label->SetFont(GetFont());
    
    m_Etiquetas->push_back(IDC_CONTROLES + numControl);
    numControl++;
    
    rect.top = rect.bottom;
    rect.bottom = rect.top + 20;
    
    if (param->IsEnumerable()) {
      CComboBox * enums = new CComboBox();
      enums->Create(CBS_DROPDOWNLIST | WS_BORDER | WS_VSCROLL | WS_TABSTOP | WS_VISIBLE, 
        rect, this, IDC_CONTROLES + numControl);
      enums->SetFont(GetFont());

      m_ParamCtrls->push_back(IDC_CONTROLES + numControl);
      numControl++;
      
      if (!fillEnumerablePropertiesValues(*param, enums)) {
        // TODO: Tenemos que volver a intentar llenarlo cuando se complete con éxito la conexión
        ;
      }
    
    } else {
      if (param->IsFilePath() || param->IsFileName()) {
        rect.left = rect.right - 30;
        rect.right = rect.left + 30;
        
        CButton * file = new CButton();
        file->Create(L"...", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 
          rect, this, IDC_CONTROLES + numControl);
        file->SetFont(GetFont());
        numControl++;
        
        rect.right = rect.left - 10;
        rect.left = 10;
      } 
      
      CEdit * value = new CEdit();
      value->CreateEx(WS_EX_CLIENTEDGE, L"EDIT", L"", 
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_LEFT | ES_AUTOHSCROLL, 
        rect, this, IDC_CONTROLES + numControl);
      value->SetFont(GetFont());
      if (param->IsProtected()) value->SetPasswordChar('*');
      
      m_ParamCtrls->push_back(IDC_CONTROLES + numControl);
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
  if (m_Connection != NULL) {
    try {
      m_Connection->Close();
    } catch (...) {
    }  
    m_Connection = NULL;
  }

  CDialog::OnCancel();
}

void DlgProviderParam::OnOK()
{
  String connString = L"";
  CString label = L"";
  CString value = L"";

  ListaControles::iterator itParam;
  ListaControles::iterator itValues;
  for (itParam = m_Etiquetas->begin(), itValues = m_ParamCtrls->begin(); itParam != m_Etiquetas->end() && itValues != m_ParamCtrls->end(); itParam++, itValues++) {
    GetDlgItemText(*itParam, label);
    GetDlgItemText(*itValues, value);
    if (label.Right(1) == "*") label = label.Left(label.GetLength() - 1);
    connString += label + L"= " + value + L";";
  }
  if (m_Connection == NULL) m_Connection = new CConnection(_provider.GetName());
  m_Connection->SetConnectionString(connString);

  try {
		FdoConnectionState state = m_Connection->Open();
    if (state != FdoConnectionState_Open) {
      if (state == FdoConnectionState_Pending) {
        for (itParam = m_Etiquetas->begin(), itValues = m_ParamCtrls->begin(); itParam != m_Etiquetas->end() && itValues != m_ParamCtrls->end(); itParam++, itValues++) {
          GetDlgItemText(*itParam, label);
          if (label.Right(1) == "*") label = label.Left(label.GetLength() - 1);
          
          CConnectionParam param = m_Connection->GetParam(String(label));
          if (param.IsEnumerable()) {
            CComboBox * cbo = (CComboBox*)GetDlgItem(*itValues);
            if (cbo != NULL &&
                cbo->GetCount() == 0) {
              fillEnumerablePropertiesValues(param, cbo);
              if (cbo->GetCount() == 1) {
                cbo->SetCurSel(0);
                DlgProviderParam::OnOK();
              } else {
                AfxMessageBox((L"You have to provide " + param.GetDisplayName()).c_str());
              }
            } else if (cbo->GetCurSel() < 0) {
              AfxMessageBox((L"You have to provide " + param.GetDisplayName()).c_str());
            }
          }
        }
      }
      
      return;
    }
  } catch (FdoConnectionException * ce) {
    AfxMessageBox(ce->GetExceptionMessage());
    m_Connection->Close();
    m_Connection = NULL;
    return;
	} catch (FdoException * e) {
    AfxMessageBox(e->GetExceptionMessage());
    m_Connection->Close();
    m_Connection = NULL;
    return;
	}
  
  m_Connection->Close();
  
  EndDialog(NULL);
}

CConnection * DlgProviderParam::GetConnection() const { return m_Connection; }