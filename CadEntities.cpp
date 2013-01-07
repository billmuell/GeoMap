#include "stdafx.h"
#include "CadEntities.h"

CCadEntities::CCadEntities(void)
{
}

CCadEntities::~CCadEntities(void)
{
  for (long i = 0; i < size(); i++) {
    delete at(i);
  }
  clear();
}
