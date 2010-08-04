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
  //try {
		FdoPtr<FdoISelect> select = (FdoISelect*)_connection->CreateCommand(FdoCommandType_Select);
    select->SetFeatureClassName(_name.c_str());

		FdoPtr<FdoFgfGeometryFactory> gf = FdoFgfGeometryFactory::GetInstance();
    FdoPtr<FdoIGeometry> filterGeom = gf->CreateGeometry(extent.c_str());
		FdoPtr<FdoByteArray> polyfgf = gf->GetFgf(filterGeom);
		FdoPtr<FdoGeometryValue> gv = FdoGeometryValue::Create(polyfgf);
		FdoPtr<FdoSpatialCondition> filter = FdoSpatialCondition::Create(_spatialColumn.c_str(), FdoSpatialOperations::FdoSpatialOperations_Intersects, gv);
		select->SetFilter(filter);
		
		FdoPtr<FdoIFeatureReader> reader = select->Execute();
    
    return CFeatureReaderFactory::GetFeatureReader(reader, _spatialColumn);
    
  /*} catch (FdoException * e) {
		acutPrintf(e->GetExceptionMessage());
    return 0;
	}*/
}
