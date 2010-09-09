#include "stdafx.h"
#include "CadEntity.h"
#include "CadData.h"

CCadEntity::CCadEntity() 
{
}

CCadEntity::CCadEntity(AcDbEntity * entity) 
{
  AddEntity(entity);
}

CCadEntity::CCadEntity(AcDbEntity * entity, CFeatureData data) : 
  _data(data) 
{
  AddEntity(entity);
}

 void CCadEntity::AddEntity(AcDbEntity * entity)
 { 
  if (!entity->isReadEnabled()) {
    acutPrintf(L"Cerrado");
  }
  
  if (entity->isReadEnabled()) {
    AcDbObjectId oid = entity->objectId();
    if (oid != NULL) {
      resbuf * data = entity->xData(L"GEOMAP_DICT_ID");
      if (data != NULL) {
        _data.FromString(data->rbnext->resval.rstring);
      }
      acutRelRb(data);
    }
  }
  
  _entities.push_back(entity);
 }

CCadEntity::~CCadEntity(void)
{
  try {
    for (Entities::iterator it = _entities.begin(); it != _entities.end(); it++) {
      (*it)->close();
    }
  } catch (...)
  {}
}

/*CCadEntity::CCadEntity(const CCadEntity & entity)
{
  this->_entity = entity._entity;
}*/

void CCadEntity::Draw() {
  for (Entities::iterator it = _entities.begin(); it != _entities.end(); it++) {
	  AcDbEntity * entity = *it;

    AcDbHostApplicationServices* pServices = acdbHostApplicationServices();
	  AcDbDatabase* pDb = pServices->workingDatabase();

	  AcDbBlockTable* pBlockTable = NULL;
	  pDb->getSymbolTable(pBlockTable, AcDb::kForRead);
	  AcDbBlockTableRecord* pBlockTableRecord = NULL;
	  pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	  pBlockTable->close();
  	
	  AcDbObjectId entityId;
	  pBlockTableRecord->appendAcDbEntity(entityId, entity);
	  pBlockTableRecord->close();
    
    AcDbObjectId oid = entity->objectId();
    
    //acdbRegApp(L"GEOMAP_DICT_ID");
    resbuf * data = acutBuildList(AcDb::kDxfRegAppName, L"GEOMAP_DICT_ID",
        AcDb::kDxfXdAsciiString, const_cast<ACHAR*>(_data.ToString().c_str()),
        NULL);
    entity->setXData(data);
    acutRelRb(data);
    
    entity->close();
    
    //CCadData::Write(oid, _data.ToString());
  }
}

void CCadEntity::SetData(CFeatureData data) { this->_data = data; }
CFeatureData CCadEntity::GetData() { return _data; }