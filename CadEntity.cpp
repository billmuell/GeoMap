#include "stdafx.h"
#include "CadEntity.h"

CCadEntity::CCadEntity() 
{
}

CCadEntity::CCadEntity(AcDbEntity * entity) 
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

    entity->close();
  }
}
