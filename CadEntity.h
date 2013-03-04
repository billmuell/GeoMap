#pragma once

#include <vector>
<<<<<<< HEAD
#include <fdo.h>
#include "AcDb/AcDbEntity.h"
=======
// #include "AcDb/AcDbEntity.h"
>>>>>>> origin/master
#include "FeatureData.h"

typedef std::pair<AcDbObjectId, AcDbEntity *> Entity;
typedef std::vector<Entity *> Entities;

class CCadEntity
{
protected:
  Entities _entities;
  CFeatureData _data;
  static const FdoPtr<FdoFgfGeometryFactory> geometryFactory;
protected:
  CCadEntity();
public:
  ~CCadEntity(void);
public:
public:
  void AddEntity(AcDbEntity * entity);
  void Draw();
  void SetData(CFeatureData data);
  CFeatureData GetData();
  bool IsNew(String & idKey);
  virtual FdoPtr<FdoIGeometry> ToGeometry() = 0;
};