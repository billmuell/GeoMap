#pragma once

#include "Connection.h"

#include <fdo.h>

class CFeatureClass
{
protected: 
  CConnection *_connection;
  String _name;
public:
  CFeatureClass(CConnection *connection, String name);
public:
  ~CFeatureClass(void);
public:
  void SelectByExtent(String wkt);
};
