#pragma once

#include <fdo.h>

class CFeatureReader
{
protected:
  FdoPtr<FdoIFeatureReader> _reader;
  String _spatialColumn;
public:
  CFeatureReader(FdoPtr<FdoIFeatureReader> reader, String &spatialColumn);
public:
  CFeatureReader(const CFeatureReader & featureReader);
public:
  ~CFeatureReader(void);
public:
  void Draw();
  void DrawAll();
};
