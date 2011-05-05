#pragma once

#include "Connection.h"
#include "FeatureReader.h"
#include <fdo.h>

class CFeatureClass;
typedef std::map<String, CFeatureClass*> FeatureClasses;

class CFeatureClass
{
protected: 
  CConnection *_connection;
  String _name;
  String _spatialColumn;
public:
  CFeatureClass(CConnection *connection, String &name, String &spatialColumn);
public:
  ~CFeatureClass(void);
public:
  CFeatureReader SelectByExtent(String &extent);
  CFeatureReader SelectByAttributes(String &query);
  static FeatureClasses *GetFeatureClasses(CConnection *connection);
};