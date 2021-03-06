#pragma once

#include <fdo.h>

#include "CadEntity.h"

class CCadPoint :
  public CCadEntity
{
public:
  CCadPoint(FdoIPoint * geom);
  CCadPoint(FdoIMultiPoint * geom);
  CCadPoint(AcDbEntity * entity);
public:
  ~CCadPoint(void);
public:
  virtual FdoPtr<FdoIGeometry> ToGeometry();
protected:
  //FdoIPoint * GetPoint(AcDbPoint * point);
  FdoIPoint * GetPoint(Entity * entity);
  AcDbEntity * GetEntity(FdoIPoint * geom);
};
