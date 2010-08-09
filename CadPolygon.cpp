#include "stdafx.h"
#include "CadPolygon.h"

CCadPolygon::CCadPolygon()
{
}

CCadPolygon::CCadPolygon(FdoIPolygon * geom)
{
  _entities.push_back(getEntity(geom));
}

CCadPolygon::CCadPolygon(FdoIMultiPolygon * geom)
{
  for (FdoInt32 i = 0; i < geom->GetCount(); i++) {
    _entities.push_back(getEntity(geom->GetItem(i)));
  }
}

CCadPolygon::~CCadPolygon(void)
{
}

AcDbEntity * CCadPolygon::getEntity(FdoIPolygon * geom)
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