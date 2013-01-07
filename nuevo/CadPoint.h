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
public:
  FdoPtr<FdoIGeometry> ToGeometry();
protected:
  FdoPtr<FdoIPoint> ToGeometry(AcGePoint3d & point);
  AcDbEntity * GetEntity(FdoPtr<FdoIPoint> geom);
};
