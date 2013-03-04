#include "stdafx.h"
#include "FeatureData.h"
#include "Utils.h"

#include <fdo.h>

CFeatureData::CFeatureData(void)
{
}

CFeatureData::CFeatureData(String data)
{
  Strings fields = CUtils::Split(data, FIELD_SEPARATOR);
  for (Strings::iterator it = fields.begin(); it != fields.end(); it++) {
    Strings fieldValue = CUtils::Split(*it, VALUE_SEPARATOR);
    // _data.push_back(StringPair(fieldValue[0], fieldValue.size() > 1 ? fieldValue[1] : L""));
    info data;
    data.key = fieldValue[0];
    data.value = fieldValue[1];
    data.type = fieldValue[2];
    _data.push_back(data);
  }
}

// CFeatureData::CFeatureData(StringPairs data)
CFeatureData::CFeatureData(INFO data)
  : _data(data)
{
}

CFeatureData::~CFeatureData(void)
{
}

void CFeatureData::Add(String key, String value, String type)
{ 
  // _data.push_back(StringPair(key, value));
  info data;
  data.key = key;
  data.value = value;
  data.type = type;
  _data.push_back(data);
}

void CFeatureData::Add(String key, String value, FdoDataType type)
{
  CFeatureData::Add(key, value, InfoTypeStrings[type]);
}

String CFeatureData::GetValue(String key) 
{ 
  // for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
  for (INFO::iterator it = _data.begin(); it != _data.end(); it++) {
    // if (it->first == key) return it->second;
    if (it->key == key) return it->value;
  }
  
  throw FdoException::Create((L"Value for key " + key + L" not found").c_str());
}

String CFeatureData::GetType(String key) {
  for (INFO::iterator it = _data.begin(); it != _data.end(); it++) {
    if (it->key == key) return it->type;
  }
  
  throw FdoException::Create((L"Type for key " + key + L" not found").c_str());
}

Strings * CFeatureData::GetKeys() 
{
  Strings * keys = new Strings();
  // for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
  for (INFO::iterator it = _data.begin(); it != _data.end(); it++) {
    // keys->push_back(it->first);
    keys->push_back(it->key);
  }
  return keys;
}

FdoPtr<FdoPropertyValue> CFeatureData::GetPropertyValue(String key)
{
    int num = sizeof(InfoTypeStrings) / sizeof(String);
    String type = GetType(key);
    FdoPtr<FdoDataValue> value;
    for (int i = 0; i < num; i++) {
      if (InfoTypeStrings[i] == type) {
        // FdoByteArray arr = FdoByteArray::Create( data.GetValue(key).c_str();
        value = FdoDataValue::Create(FdoDataType::FdoDataType_Boolean);
        break;
      }
    }
    
    return FdoPropertyValue::Create(key.c_str(), value);
}

String CFeatureData::ToString() 
{
  String toS = L"";
  // for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
  for (INFO::iterator it = _data.begin(); it != _data.end(); it++) {
    // toS += it->first + VALUE_SEPARATOR + it->second + FIELD_SEPARATOR;
    toS += it->key + VALUE_SEPARATOR + it->value + VALUE_SEPARATOR + it->type + FIELD_SEPARATOR;
  }
  return toS;
}

String CFeatureData::ToFormattedString() 
{
  String toS = L"";
  // for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
  for (INFO::iterator it = _data.begin(); it != _data.end(); it++) {
    // toS += it->first + L": " + it->second + L"\n";
    toS += it->key + L": " + it->value + L"(" + it->type + L")\n";
  }
  return toS;
}