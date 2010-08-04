#include "stdafx.h"
#include "CadEntityFactory.h"
#include "CadEntity.h"

CCadEntityFactory::CCadEntityFactory(void)
{
}

CCadEntityFactory::~CCadEntityFactory(void)
{
}

CCadEntity CCadEntityFactory::GetCadEntity(FdoPtr<FdoIGeometry> geom) 
{
  FdoGeometryType type = geom->GetDerivedType();
	switch (type) {
		case FdoGeometryType_Polygon:
			acutPrintf(L"FdoGeometryType_Polygon\n");
			break;
		case FdoGeometryType_MultiPolygon:
			acutPrintf(L"FdoGeometryType_MultiPolygon\n");
			break;
		case FdoGeometryType_MultiGeometry:
			acutPrintf(L"FdoGeometryType_MultiGeometry\n");
			break;
		case FdoGeometryType_CurveString:
			acutPrintf(L"FdoGeometryType_CurveString\n");
			break;
		case FdoGeometryType_CurvePolygon:
			acutPrintf(L"FdoGeometryType_CurvePolygon\n");
			break;
		case FdoGeometryType_MultiCurveString:
			acutPrintf(L"FdoGeometryType_MultiCurveString\n");
			break;
		case FdoGeometryType_MultiCurvePolygon:
			acutPrintf(L"FdoGeometryType_MultiCurvePolygon\n");
			break;
		default:
			acutPrintf(L"Otro\n");
	}
	
	FdoIPolygon * geomPoly = static_cast<FdoIPolygon*>(geom.p);
	
	FdoPtr<FdoILinearRing> exteriorRing = geomPoly->GetExteriorRing();
	
	AcDb2dPolyline * poly = new AcDb2dPolyline();
	poly->makeClosed();
	
	AcGePoint3d p(0,0,0);
	for (int i = 0; i < exteriorRing->GetCount(); i++) {
		FdoPtr<FdoIDirectPosition> pos = exteriorRing->GetItem(i);
		p.x = pos->GetX();
		p.y = pos->GetY();
		
		AcDb2dVertex * v = new AcDb2dVertex();
		v->setPosition(p);
		poly->appendVertex(v);
		delete v;
	}
  
  return CCadEntity(poly);
}