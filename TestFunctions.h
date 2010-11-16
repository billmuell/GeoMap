#pragma once

class CTestFunctions 
{
protected:
  static int TestProvider(String &providerName, String &connectionString, String &featureClassName, String &spatialColumn, String &extent);

public:  
  static int TestShape();
  static int TestArcSDE();
  static int TestPostGIS();
  static int TestLocale();
  static int TestAll();
};
