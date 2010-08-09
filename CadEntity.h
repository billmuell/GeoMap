#pragma once

#include <vector>
#include "AcDb/AcDbEntity.h"

typedef std::vector<AcDbEntity*> Entities;

class CCadEntity
{
protected:
  Entities _entities;
protected:
  CCadEntity();
public:
  CCadEntity(AcDbEntity * entity);
  //CCadEntity(Entities entities);
public:
  ~CCadEntity(void);
public:
  //CCadEntity(const CCadEntity & entity);
public:
  void Draw();
};
