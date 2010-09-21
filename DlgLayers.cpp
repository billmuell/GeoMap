// DlgLayers.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgLayers.h"

// Cuadro de diálogo de DlgLayers

IMPLEMENT_DYNAMIC(DlgLayers, CDialog)

DlgLayers::DlgLayers(CConnection * connection, CWnd* pParent /*=NULL*/)
	: CDialog(DlgLayers::IDD, pParent), _connection(connection)
{
}

DlgLayers::~DlgLayers()
{
}

void DlgLayers::SetConnection(CConnection * connection) {
  _connection = connection;
}

CFeatureClass * DlgLayers::GetFeatureClass() { return _featureClass; }

void DlgLayers::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST1, lstLayers);
}

BOOL DlgLayers::OnInitDialog() {
  CDialog::OnInitDialog();
  
  return FillLayersList(L"SDE");
}

BOOL DlgLayers::FillLayersList(const String & schemaName) 
{
  _connection->Open();
  
  FdoPtr<FdoIDescribeSchema> cmdGDS = NULL;
  try {
    cmdGDS = (FdoIDescribeSchema*)_connection->CreateCommand(FdoCommandType_DescribeSchema); 
  } catch (FdoException * e) {
    AfxMessageBox(e->GetExceptionMessage());
    return FALSE;
  }
  
  cmdGDS->SetSchemaName(schemaName.c_str());
  FdoPtr<FdoFeatureSchemaCollection> schemas = cmdGDS->Execute();
  for (FdoInt32 i = 0; i < schemas->GetCount(); i++) { 
    FdoPtr<FdoFeatureSchema> schema = schemas->GetItem(0);
    FdoClassCollection * layers = schema->GetClasses();
    for (FdoInt32 j = 0; j < layers->GetCount(); j++) { 
      FdoClassDefinition * layer = layers->GetItem(j);
      FdoPtr<FdoPropertyDefinitionCollection> properties = layer->GetProperties();
      for (FdoInt32 i = 0; i < properties->GetCount(); i++) {
        FdoPropertyDefinition * prop = properties->GetItem(i);
        if (prop->GetPropertyType() != FdoPropertyType_GeometricProperty) continue;
        
        String featureClassName = layer->GetName();
        String spatialColumn = prop->GetName();
        
        //features.push_back(featureClassName, CFeatureClass(_connection, featureClassName, spatialColumn));
        features[featureClassName] = new CFeatureClass(_connection, featureClassName, spatialColumn);
        
        lstLayers.AddString(layer->GetName());
      }
    }
  }
  
  _connection->Close();
  
  return TRUE;
}

void DlgLayers::OnCancel() {
  CDialog::OnCancel();
}

void DlgLayers::OnOK() {
  CString layer;
  lstLayers.GetText(lstLayers.GetCurSel(), layer);
  String featureClassName = layer;
  //_featureClass = features.at(lstLayers.GetCurSel());
  //_featureClass = new CFeatureClass(_connection, featureClassName, spatialColumn)
  _featureClass = features[featureClassName];
  
  EndDialog(NULL);
}

BEGIN_MESSAGE_MAP(DlgLayers, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de DlgLayers
