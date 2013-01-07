#pragma once

#include <vector>
#include "AcDb/AcDbEntity.h"
#include <fdo.h>
#include "FeatureData.h"

/*enum CadEntityType
{
  CadEntityType_Point = 0,
  CadEntityType_Line = 1,
  CadEntityType_Polygon = 2
};*/

typedef std::vector<AcDbEntity*> Entities;

class CCadEntity
{
protected:
  Entities _entities;
  CFeatureData _data;
protected:
  CCadEntity();
public:
  ~CCadEntity(void);
public:
  void AddEntity(AcDbEntity * entity);
  void Draw();
  void SetData(CFeatureData & data);
  CFeatureData & GetData();
  bool IsNew(String & idKey);
  FdoPtr<FdoIGeometry> ToGeometry(void);
};

typedef std::vector<CCadEntity*> CadEntities;