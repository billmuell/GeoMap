#include "stdafx.h"
#include "CadPoint.h"

CCadPoint::CCadPoint(FdoIPoint * geom)
{
  _entities.push_back(GetEntity(geom));
}

CCadPoint::CCadPoint(FdoIMultiPoint * geom)
{
  for (FdoInt32 i = 0; i < geom->GetCount(); i++) {
    _entities.push_back(GetEntity(geom->GetItem(i)));
  }
}

CCadPoint::~CCadPoint(void)
{
}

FdoPtr<FdoIGeometry> CCadPoint::ToGeometry(void)
{
  FdoPtr<FdoIGeometry> geom = 0;
  
  if (_entities.size() == 0) return 0;
  if (_entities.size() == 1) {
    
  } else {
    
  }
  
  return geom;
}

FdoPtr<FdoIPoint> CCadPoint::ToGeometry(AcGePoint3d & point)
{
  FdoPtr<FdoIPoint> geom = 0; //new FdoIPoint();
  
  /*AcGePoint3d p3d(geom->GetOrdinates()[0], geom->GetOrdinates()[1], geom->GetOrdinates()[2]);
  
  AcDbPoint * point = new AcDbPoint(p3d);
  point->close();*/
  
  return geom;
}

AcDbEntity * CCadPoint::GetEntity(FdoPtr<FdoIPoint> geom)
{
  AcGePoint3d p3d(geom->GetOrdinates()[0], geom->GetOrdinates()[1], geom->GetOrdinates()[2]);
  
  AcDbPoint * point = new AcDbPoint(p3d);
  point->close();
  
  return point;
}