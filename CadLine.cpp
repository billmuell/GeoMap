#include "stdafx.h"
#include "CadLine.h"

CCadLine::CCadLine(FdoILineString * geom)
{
  _entities.push_back(getEntity(geom));
}

CCadLine::CCadLine(FdoIMultiLineString * geom)
{
  for (FdoInt32 i = 0; i < geom->GetCount(); i++) {
    _entities.push_back(getEntity(geom->GetItem(i)));
  }
}

CCadLine::~CCadLine(void)
{
}

AcDbEntity * CCadLine::getEntity(FdoILineString * geom)
{
  AcDb2dPolyline * line = new AcDb2dPolyline();
  
  FdoPtr<FdoDirectPositionCollection> positions = geom->GetPositions();
  AcGePoint3d point(0, 0, 0);
  for (FdoInt32 i = 0; i < positions->GetCount(); i++) {
    FdoPtr<FdoIDirectPosition> position = positions->GetItem(i);
    
    point.x = position->GetX();
    point.y = position->GetY();
    point.z = position->GetZ();
    
    AcDb2dVertex * vertex = new AcDb2dVertex();
    vertex->setPosition(point);
    line->appendVertex(vertex);
    delete vertex;
  }

  line->close();
  
  return line;
}