#include "stdafx.h"
#include "FeatureData.h"
#include "Utils.h"

#include <fdo.h>

CFeatureData::CFeatureData()
{
}

CFeatureData::CFeatureData(String data)
{
  FromString(data);
}

CFeatureData::CFeatureData(StringPairs data)
  : _data(data)
{
}

CFeatureData::~CFeatureData(void)
{
}

void CFeatureData::Add(String key, String value) { _data.push_back(StringPair(key, value)); }
String CFeatureData::GetValue(String key) 
{ 
  for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
    if (it->first == key) return it->second;
  }
  
  throw FdoException::Create((L"Value for key " + key + L" not found").c_str());
}

Strings * CFeatureData::GetKeys() 
{
  Strings * keys = new std::vector<String>();
  for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
    keys->push_back(it->first);
  }
  return keys;
}


String CFeatureData::ToString() 
{
  String toS = L"";
  for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
    toS += it->first + VALUE_SEPARATOR + it->second + FIELD_SEPARATOR;
  }
  return toS;
}

String CFeatureData::ToFormattedString() 
{
  String toS = L"";
  for (StringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
    toS += it->first + L": " + it->second + L"\n";
  }
  return toS;
}

void CFeatureData::FromString(String data) 
{
  Strings fields = CUtils::Split(data, FIELD_SEPARATOR);
  for (Strings::iterator it = fields.begin(); it != fields.end(); it++) {
    Strings fieldValue = CUtils::Split(*it, VALUE_SEPARATOR);
    _data.push_back(StringPair(fieldValue[0], fieldValue.size() > 1 ? fieldValue[1] : L""));
  }
}