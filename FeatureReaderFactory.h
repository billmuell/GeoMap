#pragma once

#include "FeatureReader.h"

class CFeatureReaderFactory
{
private:
  CFeatureReaderFactory(void);
private:
  ~CFeatureReaderFactory(void);
public:
  static CFeatureReader GetFeatureReader(FdoPtr<FdoIFeatureReader> reader, String &spatialColumn);
};
