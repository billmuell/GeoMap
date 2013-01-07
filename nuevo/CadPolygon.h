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
public:
  ~CCadPolygon(void);
public:
  FdoPtr<FdoIGeometry> ToGeometry();
protected:
  AcDbEntity * GetEntity(FdoPtr<FdoIPolygon> geom);
};
