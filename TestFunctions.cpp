#include "stdafx.h"
#include "TestFunctions.h"

#include "Connection.h"
#include "FeatureClass.h"
#include "FeatureReader.h"
#include "Provider.h"
#include "ProvidersCollection.h"

int CTestFunctions::TestProvider(String &providerName, String &connectionString, 
        String &featureClassName, String &spatialColumn, 
        String &extent) 
{
  CProvidersCollection pc;
  CStringPairs providersList = pc.ToStringPairs();
  CProvider provider = pc.GetItem(providerName);
  
  CConnection connection;
  try {
    connection = provider.CreateConnection();
  } catch (FdoException * e) {
    acutPrintf(e->GetExceptionMessage());
    return(RSERR);
  }
  
  CConnectionParams params = connection.GetParams();
  
  connection.SetConnectionString(connectionString);
  if (connection.Open() != FdoConnectionState_Open) {
    return(RSERR);
  }
  
  CFeatureClass featureClass(&connection, featureClassName, spatialColumn);
  CFeatureReader featureReader = featureClass.SelectByExtent(extent);
  featureReader.DrawAll();
  
  return(RSRSLT);
}

int CTestFunctions::TestShape() 
{
  String providerName = L"OSGeo.SHP.3.4";
  String connectionString = L"DefaultFileLocation = C:\\temp\\Shapes\\";
  String featureClassName = L"pgou_ca";
  String spatialColumn = L"Geometry";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850))";
  return TestProvider(providerName, connectionString, featureClassName, spatialColumn, extent);
}

int CTestFunctions::TestArcSDE() 
{
  String providerName = L"OSGeo.ArcSDE.3.4";
  String connectionString = L"Server=sigsde2;Instance=esri_sde;Username=sde;Password=benaguacil;Datastore=esri_sde";
  String featureClassName = L"PGOU_CA";
  String spatialColumn = L"SHAPE";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850))";
  return TestProvider(providerName, connectionString, featureClassName, spatialColumn, extent);
}

int CTestFunctions::TestPostGIS() 
{
  //String providerName = L"OSGeo.PostgreSQL.3.4";
  //String connectionString = L"Service=sigweb2:5434;Username=gis;Password=gisd;DataStore=gispm";
  
  String providerName = L"OSGeo.PostGIS.3.4";
  String connectionString = L"Service=gispm@sigweb2:5434;Username=gis;Password=gisd;DataStore=gis";
  
  String featureClassName = L"pgou_ca";
  String spatialColumn = L"the_geom";
  String extent = L"POLYGON((726000 4372508, 726500 4372508, 726500 4372850, 726000 4372850))";
  return TestProvider(providerName, connectionString, featureClassName, spatialColumn, extent);
}

int CTestFunctions::TestAll() 
{
  CTestFunctions::TestShape();
  CTestFunctions::TestArcSDE();
  CTestFunctions::TestPostGIS();
  
  return (RSRSLT);
}