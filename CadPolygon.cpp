#include "stdafx.h"
#include "CadPolygon.h"

CCadPolygon::CCadPolygon()
{
}

CCadPolygon::CCadPolygon(FdoIPolygon * geom)
{
  AddEntity(GetEntity(geom));
}

CCadPolygon::CCadPolygon(FdoIMultiPolygon * geom)
{
  for (FdoInt32 i = 0; i < geom->GetCount(); i++) {
    AddEntity(GetEntity(geom->GetItem(i)));
  }
}

CCadPolygon::CCadPolygon(AcDbEntity * entity)
{
  AddEntity(entity);
}

CCadPolygon::~CCadPolygon(void)
{
}

FdoPtr<FdoIGeometry> CCadPolygon::ToGeometry()
{
  return 0;
}

AcDbEntity * CCadPolygon::GetEntity(FdoIPolygon * geom)
{
  FdoPtr<FdoILinearRing> exteriorRing = geom->GetExteriorRing();
	
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
  
  poly->close();
  return poly;
}