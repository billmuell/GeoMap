#include "stdafx.h"
#include "FeatureReader.h"
#include "CadEntityFactory.h"
#include "CadEntity.h"

CFeatureReader::CFeatureReader(FdoPtr<FdoIFeatureReader> reader, String &spatialColumn) :
  _reader(reader), _spatialColumn(spatialColumn)
{
}

CFeatureReader::~CFeatureReader(void)
{
}

CFeatureReader::CFeatureReader(const CFeatureReader & featureReader) 
{
  this->_reader = featureReader._reader;
  this->_spatialColumn = featureReader._spatialColumn;
}

void CFeatureReader::Draw() 
{
  FdoPtr<FdoFgfGeometryFactory> gf = FdoFgfGeometryFactory::GetInstance();
  
  if (!_reader->IsNull(_spatialColumn.c_str())) {
		FdoPtr<FdoByteArray> geometry = _reader->GetGeometry (_spatialColumn.c_str());
		FdoPtr<FdoIGeometry> geom = gf->CreateGeometryFromFgf(geometry);
      
    CCadEntity * entity = CCadEntityFactory::GetCadEntity(geom);
    entity->Draw();
    delete entity;
	}
}

void CFeatureReader::DrawAll() 
{
  try {
    while (_reader->ReadNext ())
	  {
  		this->Draw();
    }
  } catch (FdoException * e) {
		acutPrintf(e->GetExceptionMessage());
    return;
	}
}