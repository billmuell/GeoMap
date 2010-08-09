#include "stdafx.h"
#include "CadEntityFactory.h"

#include "CadEntity.h"
#include "CadLine.h"
#include "CadPoint.h"
#include "CadPolygon.h"

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
    case FdoGeometryType_Point:
      acutPrintf(L"FdoGeometryType_Point\n");
      return (CCadEntity *)new CCadPoint(static_cast<FdoIPoint*>(geom.p));
      //return 0;

    case FdoGeometryType_MultiPoint:
      acutPrintf(L"FdoGeometryType_MultiPoint\n");
      return (CCadEntity *)new CCadPoint(static_cast<FdoIMultiPoint*>(geom.p));
      //return 0;

    case FdoGeometryType_LineString:
      acutPrintf(L"FdoGeometryType_LineString\n");
      return (CCadEntity *)new CCadLine(static_cast<FdoILineString*>(geom.p));
      
    case FdoGeometryType_MultiLineString:
			acutPrintf(L"FdoGeometryType_MultiLineString\n");
      return (CCadEntity *)new CCadLine(static_cast<FdoIMultiLineString*>(geom.p));
      
    case FdoGeometryType_Polygon:
			acutPrintf(L"FdoGeometryType_Polygon\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));

    case FdoGeometryType_MultiPolygon:
			acutPrintf(L"FdoGeometryType_MultiPolygon\n");
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIMultiPolygon*>(geom.p));

    case FdoGeometryType_CurveString:
			acutPrintf(L"FdoGeometryType_CurveString\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;

    case FdoGeometryType_CurvePolygon:
			acutPrintf(L"FdoGeometryType_CurvePolygon\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;

    case FdoGeometryType_MultiCurveString:
			acutPrintf(L"FdoGeometryType_MultiCurveString\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;

    case FdoGeometryType_MultiCurvePolygon:
			acutPrintf(L"FdoGeometryType_MultiCurvePolygon\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;
      
    case FdoGeometryType_MultiGeometry:
			acutPrintf(L"FdoGeometryType_MultiGeometry\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;
      
    case FdoGeometryType_None:
      acutPrintf(L"FdoGeometryType_None\n");
      return 0;

    default:
			acutPrintf(L"FdoGeometryType_Unexpected\n");
      return 0;
	}
}