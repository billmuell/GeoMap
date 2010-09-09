#pragma once

#include "AsdkInventoryData.h"

class CCadData
{
public:
  CCadData(void);
public:
  ~CCadData(void);
public:
  static void Write(AcDbObjectId pObjId, String data);
protected:
  static void commonOpen(AcDbObjectId pObjId,
           AcDb::OpenMode mode,
           AcDbObject*& pObj,
           AcDbDictionary*& pXDict,
           AsdkInventoryData*& pIObj);
};
