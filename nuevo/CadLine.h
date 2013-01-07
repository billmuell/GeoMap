#pragma once

#include <fdo.h>

#include "CadEntity.h"

class CCadLine :
  public CCadEntity
{
public:
  CCadLine(FdoILineString * geom);
  CCadLine(FdoIMultiLineString * geom);
public:
  ~CCadLine(void);
public:
  FdoPtr<FdoIGeometry> ToGeometry();
protected:
  AcDbEntity * GetEntity(FdoPtr<FdoILineString> geom);
};
