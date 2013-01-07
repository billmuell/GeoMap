#include "stdafx.h"
#include "CadEntity.h"

const FdoPtr<FdoFgfGeometryFactory> CCadEntity::geometryFactory = FdoFgfGeometryFactory::GetInstance();

CCadEntity::CCadEntity() 
{
}

 void CCadEntity::AddEntity(AcDbEntity * entity)
 { 
   _entities.push_back(new Entity(entity->objectId(), entity));
 }

CCadEntity::~CCadEntity(void)
{
}

void CCadEntity::Draw() {
  AcDbHostApplicationServices* pServices = acdbHostApplicationServices();
  AcDbDatabase* pDb = pServices->workingDatabase();
  
  AcDbBlockTable* pBlockTable = NULL;
  pDb->getSymbolTable(pBlockTable, AcDb::kForRead);
  AcDbBlockTableRecord* pBlockTableRecord = NULL;
  pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
  pBlockTable->close();

  for (Entities::iterator it = _entities.begin(); it != _entities.end(); it++) {
    Entity * entity = (*it);
    // Si tiene informado el objectId, no lo volvemos a pintar
    if (entity->first != 0) continue;
    
    AcDbEntity * acadEntity = entity->second;
    
    AcDbObjectId idEntity;
    pBlockTableRecord->appendAcDbEntity(idEntity, acadEntity);
    entity->first = idEntity;
    
    resbuf * data = acutBuildList(AcDb::kDxfRegAppName, APPNAME,
        AcDb::kDxfXdAsciiString, const_cast<ACHAR*>(_data.ToString().c_str()),
        NULL);
    acadEntity->setXData(data);
    acutRelRb(data);
    
    acadEntity->close();
  }

  pBlockTableRecord->close();
}

void CCadEntity::SetData(CFeatureData data) { this->_data = data; }
CFeatureData CCadEntity::GetData() { return _data; }
bool CCadEntity::IsNew(String & idKey) { return _data.GetValue(idKey).compare(L"") == 0; }