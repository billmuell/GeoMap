#include "FeatureClass.h"

CFeatureClass::CFeatureClass(CConnection *connection, String name) 
  : _connection(connection), _name(name)
{  
}

CFeatureClass::~CFeatureClass(void)
{
}

CFeatureReader CFeatureClass::SelectByExtent(String extent) {
  try {
		FdoPtr<FdoISelect> select = (FdoISelect*)_connection->CreateCommand(FdoCommandType_Select);
    select->SetFeatureClassName(_name.c_str());

		FdoPtr<FdoFgfGeometryFactory> gf = FdoFgfGeometryFactory::GetInstance();
    FdoPtr<FdoIGeometry> filterGeom = gf->CreateGeometry(extent.c_str());
		FdoPtr<FdoByteArray> polyfgf = gf->GetFgf(filterGeom);
		FdoPtr<FdoGeometryValue> gv = FdoGeometryValue::Create(polyfgf);
		FdoPtr<FdoSpatialCondition> filter = FdoSpatialCondition::Create(L"Geometry", FdoSpatialOperations::FdoSpatialOperations_Intersects, gv);
		select->SetFilter(filter);
		
		FdoPtr<FdoIFeatureReader> reader = select->Execute();
        
    return CFeatureReaderFactory.GetFeatureReader(reader);
    
  } catch (FdoException * e) {
		//acutPrintf(e->GetExceptionMessage());
    return 0;
	}
}
