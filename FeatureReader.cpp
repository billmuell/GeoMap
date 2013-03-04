#include "stdafx.h"
#include "FeatureReader.h"
#include "CadEntityFactory.h"
#include "CadEntity.h"
#include <boost/lexical_cast.hpp>

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
  FdoPtr<FdoClassDefinition> def = _reader->GetClassDefinition();
  FdoPtr<FdoPropertyDefinitionCollection> properties = def->GetProperties();
  
  CFeatureData featureData;
  for (FdoInt32 i = 0; i < properties->GetCount(); i++) {
    FdoPropertyDefinition * prop = properties->GetItem(i);
    if (prop->GetPropertyType() != FdoPropertyType_DataProperty) continue;

    FdoString * name = prop->GetName();
    String value = L"";
    
    FdoDataPropertyDefinition * propDef = (FdoDataPropertyDefinition*)prop;
    if (_reader->IsNull(name)){
      value = L"__NULL__";
    } else {
      value = this->GetDataValue(name, propDef->GetDataType());
    }
    featureData.Add(name, value, propDef->GetDataType());
  }
  
  return featureData;
}

String CFeatureReader::GetDataValue(FdoString * name, FdoDataType dataType)
{
    switch (dataType) {
      case FdoDataType_String:
        return _reader->GetString(name);
      case FdoDataType_Single:
        return boost::lexical_cast<String>(_reader->GetSingle(name));
      case FdoDataType_Decimal:
        return boost::lexical_cast<String>(_reader->GetDouble(name));
      case FdoDataType_Double:
        return boost::lexical_cast<String>(_reader->GetDouble(name));
      case FdoDataType_Int16:
        return boost::lexical_cast<String>(_reader->GetInt16(name));
      case FdoDataType_Int32:
        return boost::lexical_cast<String>(_reader->GetInt32(name));
      case FdoDataType_Int64:
        return boost::lexical_cast<String>(_reader->GetInt64(name));
      case FdoDataType_Boolean:
        return boost::lexical_cast<String>(_reader->GetBoolean(name));
      case FdoDataType_Byte:
        return boost::lexical_cast<String>(_reader->GetByte(name));
      case FdoDataType_DateTime:
        {
          FdoDateTime date = _reader->GetDateTime(name);
          
          return boost::lexical_cast<String>(date.year) + L"/" +
              boost::lexical_cast<String>(date.month) + L"/" +
              boost::lexical_cast<String>(date.day);
        }
      default:
        return L"";
    }
}

CCadEntity * CFeatureReader::Draw() 
{
  FdoPtr<FdoFgfGeometryFactory> gf = FdoFgfGeometryFactory::GetInstance();
  
  if (_reader->IsNull(_spatialColumn.c_str())) return 0;
  
	FdoPtr<FdoByteArray> geometry = _reader->GetGeometry (_spatialColumn.c_str());
  FdoPtr<FdoIGeometry> geom = gf->CreateGeometryFromFgf(geometry);
  
  CCadEntity * entity = CCadEntityFactory::GetCadEntity(geom);
  if (entity == 0) return 0;
  
  entity->SetData(this->GetData());
  entity->Draw();
  
  return entity;
}

CCadEntities * CFeatureReader::DrawAll() 
{
  CCadEntities * entities = new CCadEntities();
  try {
    while (_reader->ReadNext ())
	  {
  		CCadEntity * cadEntity = this->Draw();
      if (cadEntity == 0) {
        delete entities;
        return 0;
      }
      entities->push_back(cadEntity);
    }
    return entities;
  
  } catch (FdoException * e) {
		acutPrintf(e->GetExceptionMessage());
    delete entities;
    return 0;
	}
}