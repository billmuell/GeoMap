#pragma once

#include "CadEntity.h"

#include <fdo.h>

class CCadEntityFactory
{
private:
  CCadEntityFactory(void);
private:
  ~CCadEntityFactory(void);
public:
  static CCadEntity * GetCadEntity(FdoPtr<FdoIGeometry> geom);
};
