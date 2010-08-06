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

#include "ProvidersCollection.h"
#include "DlgProviders.h"

#include "DlgProviderParam.h"
#include "DlgLayers.h"

#include "Connection.h"

#include "TestFunctions.h"


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
  }

  ads_retnil();
  return( RSRSLT);
}

void GeoMap_DlgProviders()
{
  ads_DlgProviders();
}

int ads_TestShape() { return CTestFunctions::TestShape(); }
void GeoMap_TestShape() { ads_TestShape(); }
int ads_TestArcSDE() { return CTestFunctions::TestArcSDE(); }
void GeoMap_TestArcSDE() { ads_TestArcSDE(); }
int ads_TestPostGIS() { return CTestFunctions::TestPostGIS(); }
void GeoMap_TestPostGIS() { ads_TestPostGIS(); }
int ads_TestAll() { return CTestFunctions::TestAll(); }
void GeoMap_TestAll() { ads_TestAll(); }


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

ACED_ADSCOMMAND_ENTRY_AUTO( , TestShape, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestShape, TestShape, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestArcSDE, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestArcSDE, TestArcSDE, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestPostGIS, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestPostGIS, TestPostGIS, ACRX_CMD_TRANSPARENT, NULL)
ACED_ADSCOMMAND_ENTRY_AUTO( , TestAll, false)
ACED_ARXCOMMAND_ENTRY_AUTO( , GeoMap, _TestAll, TestAll, ACRX_CMD_TRANSPARENT, NULL)