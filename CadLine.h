#pragma once

#include <fdo.h>

#include "CadEntity.h"

class CCadLine :
  public CCadEntity
{
public:
  CCadLine(FdoILineString * geom);
  CCadLine(FdoIMultiLineString * geom);
  CCadLine(AcDbEntity * entity);
public:
  ~CCadLine(void);
public:
  virtual FdoPtr<FdoIGeometry> ToGeometry();
protected:
  AcDbEntity * GetEntity(FdoILineString * geom);
};
