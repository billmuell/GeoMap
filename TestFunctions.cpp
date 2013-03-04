#ifdef TEST

#include "stdafx.h"
#include "TestFunctions.h"

#include "CadEntity.h"
#include "CadEntityFactory.h"
#include "Connection.h"
#include "FeatureClass.h"
#include "FeatureReader.h"
#include "FeatureWriter.h"
#include "Provider.h"
#include "ProvidersCollection.h"

#include "Locale.h"

CCadEntities * CTestFunctions::TestSelectByAttributes(CConnection & connection, 
  String & featureClassName, String & spatialColumn, String & idColumn,
  String & query)
{
  CFeatureClass featureClass(&connection, featureClassName, spatialColumn, idColumn);
  CFeatureReader featureReader = featureClass.SelectByAttributes(query);
  return featureReader.DrawAll();
}

CCadEntities * CTestFunctions::TestSelectByExtent(CConnection & connection, 
  String & featureClassName, String & spatialColumn, String & idColumn,
  String & extent) 
{
  CFeatureClass featureClass(&connection, featureClassName, spatialColumn, idColumn);
  CFeatureReader featureReader = featureClass.SelectByExtent(extent);
  return featureReader.DrawAll();
}  

CConnection CTestFunctions::TestProvider(String &providerName, String &connectionString) 
{
  CProvidersCollection pc;
  CProvider provider = pc.GetItem(providerName);
  
  CConnection connection;
  try {
    connection = provider.CreateConnection();
  } catch (FdoException * e) {
    acutPrintf(e->GetExceptionMessage());
    return 0;
  }
  
  connection.SetConnectionString(connectionString);
  if (connection.Open() != FdoConnectionState_Open) {
    return 0;
  }
  
  return connection;
}

int CTestFunctions::TestPostGIS() 
{
  String providerName = L"OSGeo.PostgreSQL.3.5";
  String connectionString = L"Service=sigweb2:5434;Username=gis;Password=gisd;DataStore=gispm";
  
  //String providerName = L"OSGeo.PostGIS.3.5";
  //String connectionString = L"service=gispm@sigweb2:5434;username=gis;password=gisd;datastore=gis";
  
  /*CConnection connection = TestProvider(providerName, connectionString, featureClassName, spatialColumn, extent);
  if (connection.Open() != FdoConnectionState_Open) {
    return (RSERR);
  }*/
  // Por alguna extraña razón, la llamada anterior no funciona bien cuando conectamos con PostgreSQL
  // y la conexión se pierde, así que toca hacerlo aquí "a pelo"
  CProvidersCollection pc;
  CProvider provider = pc.GetItem(providerName);
  
  CConnection connection;
  try {
    connection = provider.CreateConnection();
  } catch (FdoException * e) {
    acutPrintf(e->GetExceptionMessage());
    return (RSERR);
  }
  
  connection.SetConnectionString(connectionString);
  if (connection.Open() != FdoConnectionState_Open) {
    return (RSERR);
  }
  
  String featureClassName = L"pgou_ca";
  String spatialColumn = L"the_geom";
  String idColumn = L"gid";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850, 726000 4372508))";
  CCadEntities * entities = TestSelectByExtent(connection, featureClassName, spatialColumn, idColumn, extent);
  if (entities == 0) return(RSERR);
  delete entities;
  
  // No hace falta poner comillas
  String query = L"clase = SUNP";
  entities = TestSelectByAttributes(connection, featureClassName, spatialColumn, idColumn, query);
  
  int result = (entities != 0 ? 1 : 0);
  delete entities;
  return result;
}

int CTestFunctions::TestShape() 
{
  String providerName = L"OSGeo.SHP.3.5";
  String connectionString = L"DefaultFileLocation = C:\\temp\\Shapes\\";
  CConnection connection = TestProvider(providerName, connectionString);
  if (connection.Open() != FdoConnectionState_Open) {
    return (RSERR);
  }
  
  String featureClassName = L"barrios";
  String spatialColumn = L"Geometry";
  String idColumn = L"NOMBRE";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850, 726000 4372508))";
  CCadEntities * entities = TestSelectByExtent(connection, featureClassName, spatialColumn, idColumn, extent);
  if (entities == 0) return(RSERR);
  delete entities;
  
  // El campo debe estar en mayúsculas...
  String query = L"CODDISTRIT = 1";
  //String query = L"coddistrit = 1";
  entities = TestSelectByAttributes(connection, featureClassName, spatialColumn, idColumn, query);
  
  int result = (entities != 0 ? 1 : 0);
  delete entities;
  return result;
}

int CTestFunctions::TestArcSDE() 
{
  String providerName = L"OSGeo.ArcSDE.3.5";
  String connectionString = L"Server=dsigsde2;Instance=esri_sde;Username=sde;Password=benaguacil;Datastore=esri_sde";
  CConnection connection = TestProvider(providerName, connectionString);
  if (connection.Open() != FdoConnectionState_Open) {
    return (RSERR);
  }
  
  String featureClassName = L"CALLEJERO_PNT";
  String spatialColumn = L"SHAPE";
  String idColumn = L"OBJECTID";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850, 726000 4372508))";
  CCadEntities * entities = TestSelectByExtent(connection, featureClassName, spatialColumn, idColumn, extent);
  if (entities == 0) return(RSERR);
  delete entities;

  String query = L"codvia = 10";
  entities = TestSelectByAttributes(connection, featureClassName, spatialColumn, idColumn, query);

  int result = (entities != 0 ? 1 : 0);
  delete entities;
  return result;
}

int CTestFunctions::TestLocale()
{
  CLocale locale(L"es");
  if (locale.GetTranslation(L"User") != L"Usuario") {
    acutPrintf(L"Error 'CTestFunctions::TestLocale':  Error: Translation not found\n");
    return(RSERR);
  }
  
  return 1;
}

int CTestFunctions::TestWrite()
{
  String providerName = L"OSGeo.ArcSDE.3.5";
  String connectionString = L"Server=dsigsde2;Instance=esri_sde;Username=sde;Password=benaguacil;Datastore=esri_sde";
  CConnection connection = TestProvider(providerName, connectionString);
  if (connection.Open() != FdoConnectionState_Open) {
    return (RSERR);
  }
  
  String featureClassName = L"CALLEJERO_PNT";
  String spatialColumn = L"SHAPE";
  String idColumn = L"OBJECTID";
  String query = L"codvia = 10";
  CCadEntities * entities = TestSelectByAttributes(connection, featureClassName, spatialColumn, idColumn, query);
  
  CFeatureClass featureClass(&connection, featureClassName, spatialColumn, idColumn);
  CFeatureWriter writer(&featureClass);
  writer.Write(entities);
  delete entities;
  
  return 1;
}

int CTestFunctions::TestAll() 
{
  CTestFunctions::TestShape();
  CTestFunctions::TestArcSDE();
  CTestFunctions::TestPostGIS();
  
  return 1;
}

int CTestFunctions::TestSaveEntityInMemory()
{
  ads_name seleccion;
  int returnValue = acedSSGet(_T("_I"), NULL, NULL, NULL, seleccion);
  if (returnValue != RTNORM) {
    acutPrintf(_T("\nSe produjo un error al seleccionar entidades. Asegúrese de tener al menos un elemento seleccionado\n"));
    return 0;
  }
  
  long tamanyoSel = 0;
  if (acedSSLength(seleccion, &tamanyoSel) != RTNORM) {
    acedSSFree(seleccion);
    acutPrintf(_T("\nSe produjo un error al comprobar el número de entidades seleccionadas\n"));
    return 0;
  }
  if (tamanyoSel == 0) {
    acedSSFree(seleccion);
    acutPrintf(_T("\nNo se ha podido seleccionar ninguna entidad\n"));
    return 0;
  }
  
  AcDbDatabase * db = acdbHostApplicationServices()->workingDatabase();

  bool error = false;
  AcDbEntity * entidad;
  ads_name nombreElemento;
  for (long i = 0; i < tamanyoSel; i++) {
    acedSSName(seleccion, i, nombreElemento);
    
    AcDbObjectId objectIdElemento;
    if (acdbGetObjectId(objectIdElemento, nombreElemento) != Acad::eOk) {
      error = true;
    } else if (acdbOpenObject(entidad, objectIdElemento, AcDb::kForRead) != Acad::eOk) {
      error = true;
    }
       
    if (error) {
      acedSSFree(nombreElemento);
      acutPrintf(_T("\nSe produjo un error al consultar alguna entidad\n"));
      return false;
    }
    acedSSFree(nombreElemento);
    
    entidad->close();
    
    AcDbIdMapping idMapping;
    //AcDbObject * nuevaEntidad;
    //pBlockTableRecord->deepClone(entidad, nuevaEntidad, idMapping, false);
    AcDbObjectIdArray oidArray;
    oidArray.append(objectIdElemento);
    
    AcDbObjectId modelId = acdbSymUtil()->blockModelSpaceId(db);
    
    Acad::ErrorStatus status = db->deepCloneObjects(oidArray, modelId, idMapping, false);
    acutPrintf(_T("ErrorStatus: %d\n"), status);
    
  }
  
  return 1;
}

#endif