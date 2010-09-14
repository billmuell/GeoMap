#include "stdafx.h"
#include "CadEntity.h"

CCadEntity::CCadEntity() 
{
}

CCadEntity::CCadEntity(AcDbObjectId & idEntity) 
{
  AcDbEntity * entity;
  if (acdbOpenObject(entity, idEntity, AcDb::kForRead) == Acad::eOk) {
    AcDbObjectId oid = entity->objectId();
    if (oid != NULL) {
      resbuf * data = entity->xData(APPNAME);
      if (data != NULL) {
        _data.FromString(data->rbnext->resval.rstring);
      }
      acutRelRb(data);
    }
  }
  entity->close();
  
  AddEntity(entity);
}

/*CCadEntity::CCadEntity(AcDbEntity * entity) 
{
  AddEntity(entity);
}

CCadEntity::CCadEntity(AcDbEntity * entity, CFeatureData data) : 
  _data(data) 
{
  AddEntity(entity);
}*/

 void CCadEntity::AddEntity(AcDbEntity * entity)
 { 
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
    
    resbuf * data = acutBuildList(AcDb::kDxfRegAppName, APPNAME,
        AcDb::kDxfXdAsciiString, const_cast<ACHAR*>(_data.ToString().c_str()),
        NULL);
    entity->setXData(data);
    acutRelRb(data);
    
    entity->close();
  }
}

void CCadEntity::SetData(CFeatureData data) { this->_data = data; }
CFeatureData CCadEntity::GetData() { return _data; }