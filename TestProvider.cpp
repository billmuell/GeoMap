#include "stdafx.h"
#include "TestProvider.h"

#include "ProvidersCollection.h"

int CTestProvider::TestProvider(String & providerName)
{
  CProvidersCollection pc;
  
  try {
    CProvider provider = pc.GetItem(providerName);
  } catch (...) {
    acutPrintf((L"Error 'CTestProvider::TestProvider': Unexpected error when accessing provider " + providerName + L"\n").c_str());
    return 0;
  }
  
  return TestCreateConnection(providerName);
}

int CTestProvider::TestCreateConnection(String & providerName) 
{
  CProvidersCollection pc;

  try {
    CProvider provider = pc.GetItem(providerName);
    provider.CreateConnection();
  } catch (...) {
    acutPrintf((L"Error 'CTestProvider::TestCreateConnection': Unexpected error when creating connection with " + providerName + L"\n").c_str());
    return 0;
  }

  return 1;
}

int CTestProvider::TestAll()
{
  String providerName = L"OSGeo.ArcSDE.3.4";
  TestProvider(providerName);
  providerName = L"OSGeo.PostGIS.3.4";
  TestProvider(providerName);
  
  providerName = L"OSGeo.Shape.3.4";
  acutPrintf(L"This must fail *****\n\t");
  if (TestProvider(providerName) == 1) {
    acutPrintf(L"***** Error 'CTestProvider::TestAll': Check test");
  }
  
  providerName = L"OSGeo.SHP.3.4";
  TestProvider(providerName);

  return 1;
}