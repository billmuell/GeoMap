#pragma once

#include "CadEntity.h"
#include "AcDb/AcDbEntity.h"
#include <fdo.h>

class CCadEntityFactory
{
private:
  CCadEntityFactory(void);
private:
  ~CCadEntityFactory(void);
public:
  static CCadEntity * GetCadEntity(AcDbObjectId & idEntity);
  static CCadEntity * GetCadEntity(AcDbEntity * entity);
  static CCadEntity * GetCadEntity(FdoPtr<FdoIGeometry> geom);
};
