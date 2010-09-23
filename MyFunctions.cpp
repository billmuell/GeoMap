/*
(arxload "C:\\Archivos de programa\\Bricsys\\Bricscad V9\\API\\brx\\GeoMap\\DebugBRX9\\GeoMap.brx")
DlgProviders
(arxunload "C:\\Archivos de programa\\Bricsys\\Bricscad V9\\API\\brx\\GeoMap\\DebugBRX9\\GeoMap.brx")

(arxload "C:\\Archivos de programa\\Bricsys\\Bricscad V9\\API\\brx\\GeoMap\\ReleaseBRX9\\GeoMap.brx")
DlgProviders
(arxunload "C:\\Archivos de programa\\Bricsys\\Bricscad V9\\API\\brx\\GeoMap\\ReleaseBRX9\\GeoMap.brx")
*/
// gisdesa@ser-linux:5433

#include "stdafx.h"
#include "MyDialog.h"

#include <sstream>
#include <iomanip>

#include "ProvidersCollection.h"
#include "DlgProviders.h"

#include "DlgProviderParam.h"
#include "DlgLayers.h"

#include "FeatureClass.h"
#include "FeatureReader.h"
#include "Connection.h"

#include "CadEntity.h"

#ifdef TEST
#include "TestProviderCollection.h"
#include "TestProvider.h"
#include "TestFunctions.h"
#endif

//*ads* *underscore sperator* *Lisp function Name*
// Sample command    *Group name*  *global name* *local name*
 
// *appname* _ *commandname*
  void GeoMap_MyCommand(void)
  {
  struct resbuf *prb= ads_getargs();

    ads_printf( _T( "\nHello From Brx arx command GeoMap_MyCommand\n"));
    ads_retint( 1);

  }
// ads_ *commandname*
  int ads_MyCommand(void)
  {
  struct resbuf *prb= ads_getargs();

    ads_printf( _T( "\nHello From Brx ads command ads_MyFunc\n"));
    ads_retint( 2);
    return( RSRSLT);

  }

// ads_ *functionname*
  int ads_MyFunc_(void)
  {
  struct resbuf *prb= ads_getargs();

    ads_printf( _T( "\nHello From Brx lisp function ads_MyFunc_\n"));
    ads_retint( 3);
    return( RSRSLT);

  }

// ads_ *functionname*
  int ads_MyFunc10(void)
  {
  struct resbuf *prb= ads_getargs();

    ads_printf( _T( "\nHello From Brx lisp function ads_MyFunc10\n"));
    ads_retint( 10);
    return( RSRSLT);

  }
// ads_ *commandname*
  int ads_MyCommand11(void)
  {
  struct resbuf *prb= ads_getargs();

    ads_printf( _T( "\nHello From Brx lisp command ads_MyCommand11\n"));
    ads_retint( 11);
    return( RSRSLT);

  }
// ads_ *commandname*
  int ads_MyCommand12(void)
  {
  struct resbuf *prb= ads_getargs();

    ads_printf( _T( "\nHello From Brx lisp function ads_MyCommand12\n"));
    ads_retint( 12);
    return( RSRSLT);

  }

  int ads_MyDialog()
  {
// sample from brxtemplate

//++-- See StdAfx for these types
  CStringPairs LayerList;

  AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    pDb->layerTableId();

  LayerTablePointer pLayerTable(pDb->layerTableId(),AcDb::kForRead);

    if(pLayerTable.openStatus() != eOk)
    {
      ads_retnil();
      return( RSRSLT);
    }

  AcDbLayerTableIterator *pLayerTableIterator;
    pLayerTable->newIterator(pLayerTableIterator);

    //++-- iterate though and get our stuff
    for (pLayerTableIterator->start(); 
        !pLayerTableIterator->done(); 
         pLayerTableIterator->step())
    {
    AcDbObjectId LayerId;
    TCHAR *LayerName;
    CString LayerColor;


      pLayerTableIterator->getRecordId(LayerId);
      LayerTableRecordPointer pLayerTableRecord(LayerId,AcDb::kForRead);
      pLayerTableRecord->getName(LayerName);
    AcCmColor clr = pLayerTableRecord->color();
      LayerColor = clr.bookName();

      LayerColor.Format(_T("Red = %03d   Green = %03d   Blue = %03d "), 
                           clr.red(),    clr.green() ,  clr.blue());

      LayerList.push_back(CStringPair(String(LayerName), String(LayerColor)));
    }

    delete pLayerTableIterator;
    {
    // you should always call this before your diaog;
    CAcModuleResourceOverride resOverride;

    //show our dialog
      MyDialog dlg(LayerList,CWnd::FromHandle(adsw_acadMainWnd()));
      dlg.DoModal();
    }
    ads_retnil();
    return( RSRSLT);

 }
void GeoMap_MyDialog2()
{
  ads_MyDialog();

}

String Round(double value, int numDecs)
{
  std::wostringstream rounder;
  rounder << std::fixed << std::setprecision(numDecs) << value;
  
  String valueStr = rounder.str();
  int pos = valueStr.find(L",");
  if (pos > 1) {
    valueStr = valueStr.substr(0, pos + numDecs);
  }
  
  return valueStr;
}

String GetSelectedExtent() {
  ads_name selection;
  int returnValue = acedSSGet(_T("I"), NULL, NULL, NULL, selection);
  if (returnValue == RTCAN) return 0;
  if (returnValue != RTNORM) {
    return L"";
  }

  if (acedSSSetFirst(selection, NULL) != RTNORM) {
    acedSSFree(selection);
    return L"";
  }
  ads_name element;
  acedSSName(selection, 0, element);
  acedSSFree(selection);
  
  AcDbObjectId idEntity;
  if (acdbGetObjectId(idEntity, element) != Acad::eOk) {
    acedSSFree(element);
    return L"";
  }
  
  AcDbEntity * entity;
  if ((acdbGetObjectId(idEntity, element) != Acad::eOk) || 
      (acdbOpenObject(entity, idEntity, AcDb::kForRead) != Acad::eOk)) {
    
    acedSSFree(element);
    return L"";
  }
  
  acedSSFree(element);
  
  if (!entity->isKindOf(AcDbPolyline::desc())) return L"";
  
  AcDbPolyline * poly = static_cast<AcDbPolyline*>(entity);
  if (!poly->isClosed()) return 0;
  
  String extent = L"POLYGON((";
  for (int i = 0; i < poly->numVerts(); i++) {
    AcGePoint2d point;
    poly->getPointAt(i, point);
    
    if (i > 0) extent += L", ";
    extent += Round(point.x, 0) + L" " + Round(point.y, 0);
  }
  extent += L"))";
  
  poly->close();
  
  return extent;
}

int ads_DlgProviders()
{
  CProvidersCollection pc;
  CStringPairs providersList = pc.ToStringPairs();
  
  DlgProviders dlg(providersList, CWnd::FromHandle(adsw_acadMainWnd()));
  dlg.DoModal();
  String providerName = dlg.GetProviderName();
  if (providerName.length() == 0) {
    ads_retnil();
    return( RSRSLT);
  }

  DlgProviderParam dlgProviders(pc.GetItem(providerName));
  dlgProviders.DoModal();
  
  CConnection * connection = dlgProviders.GetConnection();
  if (connection != NULL) {
    DlgLayers dlgLayers(connection);
    dlgLayers.DoModal();
    CFeatureClass * featureClass = dlgLayers.GetFeatureClass();
    if (featureClass == 0) {
      ads_retnil();
      return( RSRSLT);
    }
    
    String extent = GetSelectedExtent();

    connection->Open();
    CFeatureReader featureReader = featureClass->SelectByExtent(extent);
    featureReader.DrawAll();
    connection->Close();
    
    delete featureClass;
  }
  delete connection;

  ads_retnil();
  return( RSRSLT);
}

void GeoMap_DlgProviders()
{
  ads_DlgProviders();
}

#ifdef TEST
int ads_TestProviderCollection() { return CTestProviderCollection::TestAll(); }
void GeoMap_TestProviderCollection() { ads_TestProviderCollection(); }
int ads_TestProvider() { return CTestProvider::TestAll(); }
void GeoMap_TestProvider() { ads_TestProvider(); }
int ads_TestFunctions() { return CTestFunctions::TestAll(); }
void GeoMap_TestFunctions() { ads_TestFunctions(); }
int ads_TestArcSDE() { return CTestFunctions::TestArcSDE(); }
void GeoMap_TestArcSDE() { ads_TestArcSDE(); }

int ads_TestAll() 
{ 
  ads_TestProviderCollection();
  ads_TestProvider();
  ads_TestFunctions();
  
  return 1;
}
void GeoMap_TestAll() { ads_TestAll(); }

int ads_TestReadData() 
{
  acedSSSetFirst(NULL, NULL);
  
  ads_name selection;
  int returnValue = acedSSGet(L"_:S", NULL, NULL, NULL, selection);
  if (returnValue == RTCAN) return 0;
  if (returnValue != RTNORM) {
    return 0;
  }

  if (acedSSSetFirst(selection, NULL) != RTNORM) {
    acedSSFree(selection);
    return 0;
  }
  ads_name element;
  acedSSName(selection, 0, element);
  acedSSFree(selection);
  
  AcDbObjectId idEntity;
  if (acdbGetObjectId(idEntity, element) != Acad::eOk) {
    acedSSFree(element);
    return 0;
  }

  acedSSFree(element);
  
  CCadEntity cadEntity(idEntity);
  acutPrintf((L"\n" + cadEntity.GetData().ToFormattedString() + L"\n").c_str());
  
  return 1;
}
void GeoMap_TestReadData() { ads_TestReadData(); }
#endif


////////////////////////////////////////////////////
#ifndef BRX_APP
// workaround for Autocad only
#define ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) \
    __declspec(selectany) _ADSSYMBOL_ENTRY __AdsSymbolMap_##name = { _RXST("c:")_RXST( #name), classname::ads_ ##name, regFunc, -1 } ; \
    extern "C" __declspec(allocate("ADSSYMBOL$__m")) __declspec(selectany) _ADSSYMBOL_ENTRY* const __pAdsSymbolMap_##name = &__AdsSymbolMap_##name ; \
    ACED_ADSSYMBOL_ENTRY_PRAGMA(name)

#endif  // BRX_APP

// sample arx command
ACED_ARXCOMMAND_ENTRY_AUTO(, GeoMap, _MyCommand, MyCommand, ACRX_CMD_TRANSPARENT, NULL)

// sample Lisp function                    *func name*

ACED_ADSCOMMAND_ENTRY_AUTO(, MyCommand, false)

ACED_ADSSYMBOL_ENTRY_AUTO(, MyFunc_, false)
ACED_ADSSYMBOL_ENTRY_AUTO(, MyFunc10, false)

ACED_ADSCOMMAND_ENTRY_AUTO(, MyCommand11, false)
ACED_ADSCOMMAND_ENTRY_AUTO(, MyCommand12, false)

ACED_ADSCOMMAND_ENTRY_AUTO( , MyDialog, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _MyDialog2, MyDialog2, ACRX_CMD_TRANSPARENT, NULL)

ACED_ADSCOMMAND_ENTRY_AUTO( , DlgProviders, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _DlgProviders, DlgProviders, ACRX_CMD_TRANSPARENT, NULL)

#ifdef TEST
ACED_ADSCOMMAND_ENTRY_AUTO( , TestProviderCollection, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestProviderCollection, TestProviderCollection, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestProvider, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestProvider, TestProvider, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestFunctions, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestFunctions, TestFunctions, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestAll, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestAll, TestAll, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestArcSDE, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestArcSDE, TestArcSDE, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestReadData, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestReadData, TestReadData, ACRX_CMD_TRANSPARENT, NULL)
#endif