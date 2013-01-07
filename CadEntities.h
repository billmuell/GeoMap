#pragma once

#include "CadEntity.h"

class CCadEntities : public std::vector<CCadEntity*>
{
public:
  CCadEntities(void);
  ~CCadEntities(void);
};
