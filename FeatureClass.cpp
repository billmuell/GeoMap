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

CFeatureReader CFeatureClass::SelectByExtent(String &extent) {
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
