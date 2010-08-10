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

CFeatureData CFeatureReader::GetData()
{
  //FdoPtr<FdoSchemaAttributeDictionary> dict = def->GetAttributes();
  //FdoInt32 length = 0;
  //FdoString ** names = dict->GetAttributeNames(length);
  //FdoString * name = names[i];
  //FdoString * value = dict->GetAttributeValue(name);
  
  FdoPtr<FdoClassDefinition> def = _reader->GetClassDefinition();
  FdoPtr<FdoPropertyDefinitionCollection> prop = def->GetProperties();
  
  CFeatureData featureData;
  for (FdoInt32 i = 0; i < prop->GetCount(); i++) {
    FdoPropertyDefinition * p = prop->GetItem(i);
    
    FdoString * name = p->GetName();
    
    FdoPropertyType type = p->GetPropertyType();
    
    //pd = 0;
    switch (type) {
      case FdoPropertyType_DataProperty:
        FdoDataPropertyDefinition * pd = (FdoDataPropertyDefinition*)p;
        FdoDataType dataType = pd->GetDataType();
        acutPrintf(L"\n");
        break;
/*      default:
        break;*/
    }
    
    FdoString * value = L"";
    featureData.Add(name, value);
  }
  
  return featureData;
}

void CFeatureReader::Draw() 
{
  FdoPtr<FdoFgfGeometryFactory> gf = FdoFgfGeometryFactory::GetInstance();
  
  if (!_reader->IsNull(_spatialColumn.c_str())) {
		FdoPtr<FdoByteArray> geometry = _reader->GetGeometry (_spatialColumn.c_str());
    FdoPtr<FdoIGeometry> geom = gf->CreateGeometryFromFgf(geometry);
    
    CCadEntity * entity = CCadEntityFactory::GetCadEntity(geom);
    if (entity != 0) {
      entity->SetData(this->GetData());
      entity->Draw();
      delete entity;
    }
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