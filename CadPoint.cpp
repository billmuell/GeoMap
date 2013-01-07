#include "stdafx.h"
#include "CadPoint.h"

CCadPoint::CCadPoint(FdoIPoint * geom)
{
  AddEntity(GetEntity(geom));
}

CCadPoint::CCadPoint(FdoIMultiPoint * geom)
{
  for (FdoInt32 i = 0; i < geom->GetCount(); i++) {
    AddEntity(GetEntity(geom->GetItem(i)));
  }
}

CCadPoint::CCadPoint(AcDbEntity * entity)
{
  AddEntity(entity);
}

CCadPoint::~CCadPoint(void)
{
}

FdoPtr<FdoIGeometry> CCadPoint::ToGeometry()
{
  if (_entities.size() == 0) return 0;
  
  if (_entities.size() == 1) return GetPoint(static_cast<Entity *>(_entities.at(0)));
  
  FdoPointCollection * points = new FdoPointCollection();
  for (int i = 0; i < _entities.size(); i++) {
    FdoIPoint * point = GetPoint(static_cast<Entity *>(_entities.at(i)));
    if (point == 0) {
      points->Clear();
      delete points;
      return 0;
    }
  }
  return geometryFactory->CreateMultiPoint(points);
}

FdoIPoint * CCadPoint::GetPoint(Entity * entity)
{
  AcDbEntity * acadEntity = entity->second;
  if (!acadEntity->isKindOf(AcDbPoint::desc())) return 0;
  
  AcDbPoint * point;
  if (acdbOpenObject(point, entity->first, AcDb::kForRead) != Acad::eOk) return 0;
  
  double coordinates[2];
  coordinates[0] = point->position().x;
  coordinates[1] = point->position().y;
  
  point->close();
  
  return geometryFactory->CreatePoint(geometryFactory->CreatePosition(2, coordinates));
}

AcDbEntity * CCadPoint::GetEntity(FdoIPoint * geom)
{
  AcGePoint3d p3d(geom->GetOrdinates()[0], geom->GetOrdinates()[1], geom->GetOrdinates()[2]);
  
  AcDbPoint * point = new AcDbPoint(p3d);
  point->close();
  
  return point;
}