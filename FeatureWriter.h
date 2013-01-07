#pragma once

#include "CadEntity.h"
#include "CadEntities.h"
#include "FeatureClass.h"
#include "FeatureReader.h"

class CFeatureWriter
{
protected:
  CFeatureClass * _featureClass;
public:
  CFeatureWriter(CFeatureClass * _featureClass);
public:
  ~CFeatureWriter(void);

public:
  bool Write(CCadEntities * entities);
};
