#include "stdafx.h"
#include "FeatureWriter.h"
#include "CadEntityFactory.h"

CFeatureWriter::CFeatureWriter(CFeatureClass * featureClass)
{
  _featureClass = featureClass;
}

CFeatureWriter::~CFeatureWriter(void)
{
}

bool CFeatureWriter::Write(CadEntities entities)
{
  Strings * keys = 0;
  
  _featureClass->StartInsertOrUpdate();
  
  for (CadEntities::iterator itEntity = entities.begin(); itEntity != entities.end(); itEntity++) {
    CCadEntity * entity = *itEntity;
    
    FdoPtr<FdoIGeometry> geom = entity->ToGeometry();
    if (geom == 0) {
      _featureClass->StopInsertOrUpdate(false);
      return false;
    }
    
    CFeatureData data = entity->GetData();
    if (keys == 0) keys = data.GetKeys();
    
    for (Strings::iterator itKeys = keys->begin(); itKeys != keys->end(); itKeys++) {
      if (entity->IsNew(_featureClass->GetIdColumn())) {
        if (!_featureClass->Insert(geom, *keys, data)) {
          _featureClass->StopInsertOrUpdate(false);
          delete keys;
          return false;
        }
      } else if (!_featureClass->Update(geom, *keys, data)) {
        _featureClass->StopInsertOrUpdate(false);
        delete keys;
        return false;
      }
    }
  }
  
  _featureClass->StopInsertOrUpdate(true);
  
  if (keys != 0) delete keys;
  
  return true;
}
