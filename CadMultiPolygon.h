#pragma once

#include <fdo.h>

#include "CadPolygon.h"

class CCadMultiPolygon : public CCadPolygon
{
public:
  CCadMultiPolygon(FdoIMultiPolygon * geomPoly);
public:
  ~CCadMultiPolygon(void);
};
