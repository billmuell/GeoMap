#include "stdafx.h"
#include "CadEntity.h"

CCadEntity::CCadEntity(AcDbEntity * entity) :
  _entity(entity)
{
}

CCadEntity::~CCadEntity(void)
{
  try {
    _entity->close();
  } catch (...)
  {}
}

CCadEntity::CCadEntity(const CCadEntity & entity)
{
  this->_entity = entity._entity;
}

void CCadEntity::Draw() {
	AcDbHostApplicationServices* pServices = acdbHostApplicationServices();
	AcDbDatabase* pDb = pServices->workingDatabase();

	AcDbBlockTable* pBlockTable = NULL;
	pDb->getSymbolTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord* pBlockTableRecord = NULL;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	pBlockTable->close();
	
	AcDbObjectId entityId;
	pBlockTableRecord->appendAcDbEntity(entityId, _entity);
	pBlockTableRecord->close();

  _entity->close();
}
