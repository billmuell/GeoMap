#pragma once

#include "Connection.h"
#include "FeatureData.h"
#include "FeatureReader.h"
#include <fdo.h>

class CFeatureClass;
typedef std::map<String, CFeatureClass*> FeatureClasses;

class CFeatureClass
{
protected: 
  CConnection * _connection;
  String _name;
  String _spatialColumn;
  String _idColumn;
  bool editing;
public:
  CFeatureClass(CConnection * connection, String & name, String & spatialColumn, String & idColumn);
public:
  ~CFeatureClass(void);
public:
  CFeatureReader SelectByExtent(String &extent);
  CFeatureReader SelectByAttributes(String &query);
  static FeatureClasses *GetFeatureClasses(CConnection *connection);
  
  String GetIdColumn();
  void StartInsertOrUpdate();
  void StopInsertOrUpdate(bool saveEdits);
  bool Insert(FdoPtr<FdoIGeometry> geom, Strings & keys, CFeatureData & data);
  bool Update(FdoPtr<FdoIGeometry> geom, Strings & keys, CFeatureData & data);
};