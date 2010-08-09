#include "stdafx.h"
#include "CadEntityFactory.h"

#include "CadEntity.h"
#include "CadPolygon.h"
#include "CadMultiPolygon.h"

CCadEntityFactory::CCadEntityFactory(void)
{
}

CCadEntityFactory::~CCadEntityFactory(void)
{
}

CCadEntity * CCadEntityFactory::GetCadEntity(FdoPtr<FdoIGeometry> geom) 
{
  FdoGeometryType type = geom->GetDerivedType();
	
  switch (type) {
		case FdoGeometryType_Polygon:
			acutPrintf(L"FdoGeometryType_Polygon\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
			break;
		case FdoGeometryType_MultiPolygon:
			acutPrintf(L"FdoGeometryType_MultiPolygon\n");
      return (CCadEntity *)new CCadMultiPolygon(static_cast<FdoIMultiPolygon*>(geom.p));
      break;
		case FdoGeometryType_MultiGeometry:
			acutPrintf(L"FdoGeometryType_MultiGeometry\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
			break;
		case FdoGeometryType_CurveString:
			acutPrintf(L"FdoGeometryType_CurveString\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
			break;
		case FdoGeometryType_CurvePolygon:
			acutPrintf(L"FdoGeometryType_CurvePolygon\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
			break;
		case FdoGeometryType_MultiCurveString:
			acutPrintf(L"FdoGeometryType_MultiCurveString\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
			break;
		case FdoGeometryType_MultiCurvePolygon:
			acutPrintf(L"FdoGeometryType_MultiCurvePolygon\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
			break;
		default:
			acutPrintf(L"FdoGeometryType_Unexpected\n");
      return 0;
	}
}