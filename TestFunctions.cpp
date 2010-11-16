#ifdef TEST

#include "stdafx.h"
#include "TestFunctions.h"

#include "Connection.h"
#include "FeatureClass.h"
#include "FeatureReader.h"
#include "Provider.h"
#include "ProvidersCollection.h"

#include "Locale.h"

int CTestFunctions::TestProvider(String &providerName, String &connectionString, 
        String &featureClassName, String &spatialColumn, 
        String &extent) 
{
  CProvidersCollection pc;
  CProvider provider = pc.GetItem(providerName);
  
  CConnection connection;
  try {
    connection = provider.CreateConnection();
  } catch (FdoException * e) {
    acutPrintf(e->GetExceptionMessage());
    return(RSERR);
  }
  
  //CConnectionParams params = connection.GetParams();
  
  connection.SetConnectionString(connectionString);
  if (connection.Open() != FdoConnectionState_Open) {
    return(RSERR);
  }
  
  CFeatureClass featureClass(&connection, featureClassName, spatialColumn);
  CFeatureReader featureReader = featureClass.SelectByExtent(extent);
  featureReader.DrawAll();
  
  return 1;
}

int CTestFunctions::TestPostGIS() 
{
  String providerName = L"OSGeo.PostgreSQL.3.5";
  String connectionString = L"Service=sigweb2:5434;Username=gis;Password=gisd;DataStore=gispm";
  
  //String providerName = L"OSGeo.PostGIS.3.5";
  //String connectionString = L"service=gispm@sigweb2:5434;username=gis;password=gisd;datastore=gis";
  
  //String featureClassName = L"barrios";
  String featureClassName = L"pgou_ca";
  String spatialColumn = L"the_geom";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850, 726000 4372508))";
  return TestProvider(providerName, connectionString, featureClassName, spatialColumn, extent);
}

int CTestFunctions::TestShape() 
{
  String providerName = L"OSGeo.SHP.3.5";
  String connectionString = L"DefaultFileLocation = C:\\temp\\Shapes\\";
  String featureClassName = L"barrios";
  String spatialColumn = L"Geometry";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850, 726000 4372508))";
  return TestProvider(providerName, connectionString, featureClassName, spatialColumn, extent);
}

int CTestFunctions::TestArcSDE() 
{
  String providerName = L"OSGeo.ArcSDE.3.5";
  String connectionString = L"Server=sigsde2;Instance=esri_sde;Username=sde;Password=benaguacil;Datastore=esri_sde";
  //String featureClassName = L"BARRIOS";
  String featureClassName = L"CALLEJERO_PNT";
  String spatialColumn = L"SHAPE";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850, 726000 4372508))";
  return TestProvider(providerName, connectionString, featureClassName, spatialColumn, extent);
}

int CTestFunctions::TestLocale()
{
  CLocale locale(L"es");
  if (locale.GetTranslation(L"User") != L"Usuario") {
    acutPrintf(L"TestLocale Error: No se ha encontrado la traducción\n");
    return(RSERR);
  }
  
  return 1;
}

int CTestFunctions::TestAll() 
{
  CTestFunctions::TestShape();
  CTestFunctions::TestArcSDE();
  CTestFunctions::TestPostGIS();
  
  return 1;
}

#endif