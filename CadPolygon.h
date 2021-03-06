#pragma once

#include <fdo.h>

#include "CadEntity.h"

class CCadPolygon : public CCadEntity
{
protected:
  CCadPolygon();
public:
  CCadPolygon(FdoIPolygon * geom);
  CCadPolygon(FdoIMultiPolygon * geom);
  CCadPolygon(AcDbEntity * entity);
public:
  ~CCadPolygon(void);
public:
  virtual FdoPtr<FdoIGeometry> ToGeometry();
protected:
  AcDbEntity * GetEntity(FdoIPolygon * geom);
};
