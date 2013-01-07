#include "stdafx.h"
#include "FeatureClass.h"
#include "FeatureReaderFactory.h"
#include "AppConf.h"
#include "Utils.h"

CFeatureClass::CFeatureClass(CConnection *connection, String &name, String &spatialColumn, String & idColumn) 
  : _connection(connection), _name(name), _spatialColumn(spatialColumn), _idColumn(idColumn), editing(false)
{
}

CFeatureClass::~CFeatureClass(void)
{
}

CFeatureReader CFeatureClass::SelectByExtent(String &extent) 
{
  try {
		FdoPtr<FdoISelect> select = (FdoISelect*)_connection->CreateCommand(FdoCommandType_Select);
    select->SetFeatureClassName(_name.c_str());
    
    if (extent.length() > 0) {
      FdoPtr<FdoFgfGeometryFactory> gf = FdoFgfGeometryFactory::GetInstance();
      FdoPtr<FdoIGeometry> filterGeom = gf->CreateGeometry(extent.c_str());
		  FdoPtr<FdoByteArray> polyfgf = gf->GetFgf(filterGeom);
		  FdoPtr<FdoGeometryValue> gv = FdoGeometryValue::Create(polyfgf);
		  FdoPtr<FdoSpatialCondition> filter = FdoSpatialCondition::Create(_spatialColumn.c_str(), FdoSpatialOperations_Intersects, gv);
		  select->SetFilter(filter);
    }
		
		FdoPtr<FdoIFeatureReader> reader = select->Execute();
    
    return CFeatureReaderFactory::GetFeatureReader(reader, _spatialColumn);
    
  } catch (FdoException * e) {
#ifdef TEST
    acutPrintf(e->GetExceptionMessage());
    if (e->GetCause()) acutPrintf(e->GetCause()->GetExceptionMessage());
    if (e->GetRootCause()) acutPrintf(e->GetRootCause()->GetExceptionMessage());
#endif
    acutPrintf(CAppConf::GetLocale().GetTranslation(L"Unexpected error. Please, contact with the publisher").c_str());
    return CFeatureReader(0, String(L""));
	}
}

CFeatureReader CFeatureClass::SelectByAttributes(String &query) 
{
  try {
		FdoPtr<FdoISelect> select = (FdoISelect*)_connection->CreateCommand(FdoCommandType_Select);
    select->SetFeatureClassName(_name.c_str());
    
    if (query.length() > 0) {
      Strings querySplit = CUtils::Split(query, L"=");
      String field = querySplit[0];
      String value = querySplit[1];
      
      FdoPtr<FdoIdentifier> fdoField = FdoIdentifier::Create(CUtils::Trim(field).c_str());
      if (value != L"NULL") {
        FdoPtr<FdoDataValue> fdoValue = FdoDataValue::Create(CUtils::Trim(value).c_str());
        FdoPtr<FdoComparisonCondition> filter = FdoComparisonCondition::Create(fdoField, FdoComparisonOperations_EqualTo, fdoValue);
		    select->SetFilter(filter);
      } else {
        FdoPtr<FdoNullCondition> filterNull = FdoNullCondition::Create(fdoField);
        select->SetFilter(filterNull);
      }
    }
    
		FdoPtr<FdoIFeatureReader> reader = select->Execute();
    
    return CFeatureReaderFactory::GetFeatureReader(reader, _spatialColumn);
    
  } catch (FdoException * e) {
#ifdef TEST
    acutPrintf(e->GetExceptionMessage());
    if (e->GetCause()) acutPrintf(e->GetCause()->GetExceptionMessage());
    if (e->GetRootCause()) acutPrintf(e->GetRootCause()->GetExceptionMessage());
#endif
    acutPrintf(CAppConf::GetLocale().GetTranslation(L"Unexpected error. Please, contact with the publisher").c_str());
    return CFeatureReader(0, String(L""));
	}
}

FeatureClasses *CFeatureClass::GetFeatureClasses(CConnection *connection) 
{
  connection->Open();
  
  FdoPtr<FdoIDescribeSchema> cmdGDS = NULL;
  try {
    cmdGDS = (FdoIDescribeSchema*)connection->CreateCommand(FdoCommandType_DescribeSchema); 
  } catch (FdoException * e) {
    AfxMessageBox(e->GetExceptionMessage());
    connection->Close();
    return 0;
  }
  
  /*** TODO ***/
  /* Debería obtenerse del proveedor... */
  String idColumn = L"OBJECTID";
  /*** TODO ***/

  FeatureClasses * featureClasses = new FeatureClasses();
  
  FdoPtr<FdoFeatureSchemaCollection> schemas = cmdGDS->Execute();
  for (FdoInt32 i = 0; i < schemas->GetCount(); i++) { 
    FdoPtr<FdoFeatureSchema> schema = schemas->GetItem(0);
    String schemaName = schema->GetName();
    
    FdoClassCollection * layers = schema->GetClasses();
    for (FdoInt32 j = 0; j < layers->GetCount(); j++) { 
      FdoClassDefinition * layer = layers->GetItem(j);
      FdoPtr<FdoPropertyDefinitionCollection> properties = layer->GetProperties();
      for (FdoInt32 i = 0; i < properties->GetCount(); i++) {
        FdoPropertyDefinition * prop = properties->GetItem(i);
        if (prop->GetPropertyType() != FdoPropertyType_GeometricProperty) continue;
        
        String featureClassName = layer->GetName();
        String spatialColumn = prop->GetName();
        
        // String layerNameStr = schemaName + L"." + featureClassName;
        String layerNameStr = featureClassName;
        featureClasses->operator [](layerNameStr) = new CFeatureClass(connection, featureClassName, spatialColumn, idColumn);
      }
    }
  }
  
  connection->Close();
  
  return featureClasses;
}

String CFeatureClass::GetIdColumn() { return _idColumn; }

void CFeatureClass::StartInsertOrUpdate()
{
  if (editing) return;
  _connection->Open();
  editing = true;
}

void CFeatureClass::StopInsertOrUpdate(bool saveEdits)
{
  if (!editing) return;
  _connection->Close();
  editing = false;
}

bool CFeatureClass::Insert(FdoPtr<FdoIGeometry> geom, Strings & keys, CFeatureData & data)
{
  if (!editing) return false;
  
  return true;
}

bool CFeatureClass::Update(FdoPtr<FdoIGeometry> geom, Strings & keys, CFeatureData & data)
{
  if (!editing) return false;
  
  return true;
}