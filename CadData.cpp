#include "stdafx.h"
#include "CadData.h"

CCadData::CCadData(void)
{
}

CCadData::~CCadData(void)
{
}

/*AcDbObject * CCadData::selectObject(AcDbObjectId eId, AcDb::OpenMode openMode)
{
    // Allow user to either pick an entity, or type in the object handle.
    ads_name en;
    
    ACHAR * handleStr = args->resval.rstring;
    if (acdbHandEnt(handleStr, en) != RTNORM) {
      return 0;
    }
    acdbHandEnt(handleStr, en);
    
    // Now, exchange the old-fangled ads_name for the new-fangled
    // object id...
    Acad::ErrorStatus retStat = acdbGetObjectId(eId, en);
    if (retStat != Acad::eOk) {
        return NULL;
    }

    AcDbObject *pObj;
    if ((retStat = acdbOpenObject(pObj, eId, openMode)) != Acad::eOk) {
        return NULL;
    }
    return pObj;
}*/

void CCadData::commonOpen(AcDbObjectId pObjId,
    AcDb::OpenMode mode,
    AcDbObject*& pObj,
    AcDbDictionary*& pXDict,
    AsdkInventoryData*& pIObj)
{
    // Get the main object.
    pObj = NULL;
    
    if (acdbOpenObject(pObj, pObjId, mode) != Acad::eOk) return;
    
    // Get extension dictionary object Id
    pXDict = NULL;
    AcDbObjectId xDictId = pObj->extensionDictionary();

    // If there is no dictionary to be opened,
    // then there are no relevant contents.
    if (xDictId == AcDbObjectId::kNull) {
      if (mode != AcDb::kForWrite) return;
      
      // This next step should never fail.
    	if (pObj->createExtensionDictionary() != Acad::eOk) return;

      // This next step should also never fail.
      if ((xDictId = pObj->extensionDictionary()) == AcDbObjectId::kNull) return;
    }

    // Open the dictionary, if we can.
    if (acdbOpenObject(pXDict, xDictId, mode) != Acad::eOk)
        return;

    // Now, get and open the inventory object, if it is there.
    // If we can't open it, that's OK for now.
    pIObj = NULL;
    pXDict->getAt(ED_INVENTORY_SERVICE, ((AcDbObject*&) pIObj), mode);
}

/*int CCadData::Read()
{
    AcDbObjectId pObjId;
    AcDbObject* pObj;
    AcDbDictionary* xDict;
    AsdkInventoryData* iObj;
    
    struct resbuf * args = acedGetArgs();
    if (args == 0 || args->restype != RTSTR) return 0;
    commonOpen(pObjId, AcDb::kForRead, pObj, xDict, iObj, args);
    
    // No Object or no extension dictionary means
    // there is nothing to do.
    //
    if (pObj == NULL) {
      return 0;
    }
    if (xDict == NULL) {
      pObj->close();
      return 0;
    }
    ACHAR *idStr = NULL;
    if (iObj != NULL) {
      try {
        //AsdkInventoryData a = *iObj;
        idStr = iObj->inventoryId();
      } catch (...) {
        // De momento, nada
      }
      if (idStr != NULL) {
        acedRetStr(idStr);
        free(idStr);
      }
    }
    
    if (iObj != NULL)
        iObj->close();
    if (xDict != NULL)
        xDict->close();
    if (pObj != NULL)
        pObj->close();

  return 0;
}*/

void CCadData::Write(AcDbObjectId pObjId, String data)
{
    AcDbObject* pObj;
    AcDbDictionary* pXDict;
    AsdkInventoryData* pIObj;
    
// TODO
    // ¡¡¡Necesitamos el Id del elemento!!!
    commonOpen(pObjId, AcDb::kForWrite, pObj, pXDict, pIObj);
    
    // No Object or no extension dictionary means
    // there is nothing to do.
    if (pObj == NULL) return;

    if (pXDict == NULL) {
        pObj->close();
        return;
    }
    
    // No inventory object id in the extension dictionary means
    // it is time to create one.
    //
    if (pIObj == NULL) {
        AcDbObjectId iObjId;
        pIObj = new AsdkInventoryData();
        if (pXDict->setAt(ED_INVENTORY_SERVICE, pIObj, iObjId) != Acad::eOk) {
	        delete pIObj;
            pXDict->close();
            pObj->close();
            return;
        }
    }
    pIObj->setInventoryId(data.c_str());
    
    pIObj->close();
    pXDict->close();
    pObj->close();
    
    ads_name ads;
    acdbGetAdsName(ads, pObjId);
    
    resbuf * rb = acdbEntGet(ads);
    acdbEntMod(rb);
    acutRelRb(rb);
    acdbEntUpd(ads);
    
    return;
}