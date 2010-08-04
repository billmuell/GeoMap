#pragma once

#include "Connection.h"
#include "FeatureReader.h"

#include <fdo.h>

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
};
