#pragma once

#include <fdo.h>

#include "FeatureData.h"

class CFeatureReader
{
protected:
  FdoPtr<FdoIFeatureReader> _reader;
  String _spatialColumn;
public:
  CFeatureReader(FdoPtr<FdoIFeatureReader> reader, String & spatialColumn);
public:
  CFeatureReader(const CFeatureReader & featureReader);
public:
  ~CFeatureReader(void);
protected:
  CFeatureData GetData();
  String GetDataValue(FdoString * name, FdoDataType dataType);
public:
  void Draw();
  void DrawAll();
};
