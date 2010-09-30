#include "stdafx.h"
#include "FeatureClass.h"
#include "FeatureReaderFactory.h"

CFeatureClass::CFeatureClass(CConnection *connection, String &name, String &spatialColumn) 
  : _connection(connection), _name(name), _spatialColumn(spatialColumn)
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
		acutPrintf(e->GetExceptionMessage());
    if (e->GetCause()) acutPrintf(e->GetCause()->GetExceptionMessage());
    if (e->GetRootCause()) acutPrintf(e->GetRootCause()->GetExceptionMessage());
    return CFeatureReader(0, String(L""));
	}
}

FeatureClasses * CFeatureClass::GetFeatureClasses(CConnection * connection) 
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
        
        //String layerNameStr = schemaName + L"." + featureClassName;
        String layerNameStr = featureClassName;
        featureClasses->operator [](layerNameStr) = new CFeatureClass(connection, featureClassName, spatialColumn);
      }
    }
  }
  
  connection->Close();
  
  return featureClasses;
}