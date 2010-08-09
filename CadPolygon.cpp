#include "stdafx.h"
#include "CadPolygon.h"

CCadPolygon::CCadPolygon()
{
}

CCadPolygon::CCadPolygon(FdoIPolygon * geomPoly)
{
  _entities.push_back(getEntity(geomPoly));
}

CCadPolygon::~CCadPolygon(void)
{
}

AcDbEntity * CCadPolygon::getEntity(FdoIPolygon * geomPoly)
{
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
  
  poly->close();
  return poly;
}