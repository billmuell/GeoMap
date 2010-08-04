#include "stdafx.h"
#include "FeatureReaderFactory.h"

CFeatureReaderFactory::CFeatureReaderFactory(void)
{
}

CFeatureReaderFactory::~CFeatureReaderFactory(void)
{
}

CFeatureReader CFeatureReaderFactory::GetFeatureReader(FdoPtr<FdoIFeatureReader> reader, String &spatialColumn)
{
  return CFeatureReader(reader, spatialColumn);
}
