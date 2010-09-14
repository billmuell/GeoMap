// DlgLayers.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgLayers.h"


// Cuadro de diálogo de DlgLayers

IMPLEMENT_DYNAMIC(DlgLayers, CDialog)

DlgLayers::DlgLayers(CConnection * connection, CWnd* pParent /*=NULL*/)
	: CDialog(DlgLayers::IDD, pParent), m_Connection(connection)
{
}

DlgLayers::~DlgLayers()
{
}

void DlgLayers::SetConnection(CConnection * connection) {
  m_Connection = connection;
}

const String DlgLayers::GetLayer() { return m_layer; }

void DlgLayers::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST1, lstLayers);
}

BOOL DlgLayers::OnInitDialog() {
  CDialog::OnInitDialog();
  
  m_Connection->Open();
  
  FdoPtr<FdoIDescribeSchema> cmdGDS = NULL;
  try {
    cmdGDS = (FdoIDescribeSchema*)m_Connection->CreateCommand(FdoCommandType_DescribeSchema); 
  } catch (FdoException * e) {
    AfxMessageBox(e->GetExceptionMessage());
    return FALSE;
  }
  
  cmdGDS->SetSchemaName(L"SDE");
  FdoPtr<FdoFeatureSchemaCollection> schemas = cmdGDS->Execute();
  for (FdoInt32 i = 0; i < schemas->GetCount(); i++) { 
    FdoPtr<FdoFeatureSchema> schema = schemas->GetItem(0);
    FdoClassCollection * layers = schema->GetClasses();
    for (FdoInt32 j = 0; j < layers->GetCount(); j++) { 
      FdoClassDefinition * layer = layers->GetItem(j);
      lstLayers.AddString(layer->GetName());
    }
  }
  
  m_Connection->Close();

  return TRUE;
}

void DlgLayers::OnCancel() {
  CDialog::OnCancel();
}

void DlgLayers::OnOK() {
  CString layer;
  lstLayers.GetText(lstLayers.GetCurSel(), layer);
  m_layer = layer;
  
  EndDialog(NULL);
}

BEGIN_MESSAGE_MAP(DlgLayers, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de DlgLayers
