#pragma once

#include <fdo.h>

#include "CadEntity.h"

class CCadPoint :
  public CCadEntity
{
public:
  CCadPoint(FdoIPoint * geom);
  CCadPoint(FdoIMultiPoint * geom);
public:
  ~CCadPoint(void);
protected:
  AcDbEntity * GetEntity(FdoIPoint * geom);
};
