#pragma once

#include <fdo.h>

#include "CadEntity.h"

class CCadPolygon : public CCadEntity
{
protected:
  CCadPolygon();
public:
  CCadPolygon(FdoIPolygon * geomPoly);
public:
  ~CCadPolygon(void);

protected:
  AcDbEntity * getEntity(FdoIPolygon * geomPoly);
};
