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

void DlgLayers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL DlgLayers::OnInitDialog() {
  CDialog::OnInitDialog();
  
  m_Connection->Open();
  
  /*FdoPtr<FdoIGetClassNames> cmdGCN = NULL;
  try {
    cmdGCN = (FdoIGetClassNames*)m_Connection->CreateCommand(FdoCommandType_GetClassNames); 
  } catch (FdoException * e) {
    //AfxMessageBox(e->GetExceptionMessage());
    //return FALSE;
  }

  if (cmdGCN != NULL) {
    FdoStringCollection* layers = cmdGCN->Execute();
    FdoInt32 num = layers->GetCount();
    for (int i=0; i<num; i++) { 
      AfxMessageBox(layers->GetString(i));
      break;
    }
  } else {
    FdoPtr<FdoIDescribeSchema> cmdDS = NULL;
    cmdDS = (FdoIDescribeSchema*)m_Connection->CreateCommand(FdoCommandType_DescribeSchema);
    //FdoCommandType_DescribeSchemaMapping

    cmdDS->SetSchemaName(L"SDE");
    try {
      cmdDS->Execute();
    } catch (FdoException * e) {
      AfxMessageBox(e->GetExceptionMessage());
      return FALSE;
    }
    
    FdoPtr<FdoStringCollection> names = cmdDS->GetClassNames();
    FdoInt32 num = names->GetCount();
    for (int i=0; i<num; i++) {
      AfxMessageBox(names->GetString(i));
      break;
    }
  }
  */

  /*describeSchemaCmd->SetSchemaName(L"gis");
  FdoPtr<FdoFeatureSchemaCollection> schemas = describeSchemaCmd->Execute(); 
  
  FdoInt32 numSchemas = schemas->GetCount(); 
  for (int i=0; i<numSchemas; i++) 
  { 
      FdoPtr<FdoFeatureSchema> schema = schemas->GetItem(i); 

      FdoString* schemaName = schema->GetName(); 
                  wprintf(L"Current schema '%ls'\n", schemaName); 
      FdoPtr<FdoClassCollection> classes = schema->GetClasses(); 

      FdoInt32 numClasses = classes->GetCount(); 
      for (int j=0; j<numClasses; j++) 
      {
        // Note the assumption here that it is a feature class (it is set up so 
        // in the test data). 
        FdoPtr<FdoClassDefinition> classDef = classes->GetItem(j); 
        
        // analyze the feature class
        FdoString* className = classDef->GetName();
        AfxMessageBox(className);
        break;
      }
  }*/
  m_Connection->Close();

  return TRUE;
}

void DlgLayers::OnCancel() {
  CDialog::OnCancel();
}

void DlgLayers::OnOK() {
  EndDialog(NULL);
}

BEGIN_MESSAGE_MAP(DlgLayers, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de DlgLayers
