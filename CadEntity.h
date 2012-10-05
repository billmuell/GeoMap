#pragma once

#include <vector>
// #include "AcDb/AcDbEntity.h"
#include "FeatureData.h"

typedef std::vector<AcDbEntity*> Entities;

class CCadEntity
{
protected:
  Entities _entities;
  CFeatureData _data;
protected:
  CCadEntity();
public:
  CCadEntity(AcDbObjectId & idEntity);
  //CCadEntity(AcDbEntity * entity);
  //CCadEntity(AcDbEntity * entity, CFeatureData data);
  //CCadEntity(Entities entities);
public:
  ~CCadEntity(void);
public:
  //CCadEntity(const CCadEntity & entity);
public:
  void AddEntity(AcDbEntity * entity);
  void Draw();
  void SetData(CFeatureData data);
  CFeatureData GetData();
};
