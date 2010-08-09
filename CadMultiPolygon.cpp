#include "CadMultiPolygon.h"

CCadMultiPolygon::CCadMultiPolygon(FdoIMultiPolygon * geomPoly)
{
  for (FdoInt32 i = 0; i < geomPoly->GetCount(); i++) {
    _entities.push_back(getEntity(geomPoly->GetItem(i)));
  }
}

CCadMultiPolygon::~CCadMultiPolygon(void)
{
}
