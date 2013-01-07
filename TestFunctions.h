#pragma once

#include "Connection.h"
#include "CadEntities.h"

class CTestFunctions 
{
protected:
  static CConnection TestProvider(String &providerName, String &connectionString);
  static CCadEntities * TestSelectByAttributes(CConnection & connection, 
    String & featureClassName, String & spatialColumn, String & idColumn,
    String & query);
  static CCadEntities * TestSelectByExtent(CConnection & connection, 
    String & featureClassName, String & spatialColumn, String & idColumn,
    String & extent);

public:  
  static int TestShape();
  static int TestArcSDE();
  static int TestPostGIS();
  static int TestLocale();
  static int TestWrite();
  static int TestAll();
};
