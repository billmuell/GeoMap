#pragma once

#include "Connection.h"

class CTestFunctions 
{
protected:
  static CConnection TestProvider(String &providerName, String &connectionString);
  static int TestSelectByAttributes(CConnection &connection, 
    String &featureClassName, String &spatialColumn,
    String &query);
  static int TestSelectByExtent(CConnection &connection, 
    String &featureClassName, String &spatialColumn,
    String &extent);

public:  
  static int TestShape();
  static int TestArcSDE();
  static int TestPostGIS();
  static int TestLocale();
  static int TestAll();
};
