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

protected:
  AcDbEntity * getEntity(FdoIPolygon * geom);
};
