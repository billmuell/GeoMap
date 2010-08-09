#include "stdafx.h"
#include "CadPoint.h"

CCadPoint::CCadPoint(FdoIPoint * geom)
{
  _entities.push_back(getEntity(geom));
}

CCadPoint::CCadPoint(FdoIMultiPoint * geom)
{
  for (FdoInt32 i = 0; i < geom->GetCount(); i++) {
    _entities.push_back(getEntity(geom->GetItem(i)));
  }
}

CCadPoint::~CCadPoint(void)
{
}

AcDbEntity * CCadPoint::getEntity(FdoIPoint * geom)
{
  AcGePoint3d p3d(geom->GetOrdinates()[0], geom->GetOrdinates()[1], geom->GetOrdinates()[2]);
  
  AcDbPoint * point = new AcDbPoint(p3d);
  point->close();
  
  return point;
}