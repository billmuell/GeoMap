#include "stdafx.h"
#include "FeatureData.h"

#include <fdo.h>

CFeatureData::CFeatureData(void)
{
}

CFeatureData::CFeatureData(CStringPairs data)
  : _data(data)
{
}

CFeatureData::~CFeatureData(void)
{
}

void CFeatureData::Add(String key, String value) { _data.push_back(CStringPair(key, value)); }
String CFeatureData::GetValue(String key) 
{ 
  for (CStringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
    if (it->first == key) return it->second;
  }
  
  throw FdoException::Create((L"Value for key " + key + L" not found").c_str());
}

String CFeatureData::ToString() 
{
  String toS = L"";
  for (CStringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
    toS += it->first + VALUE_SEPARATOR + it->second + FIELD_SEPARATOR;
  }
  return toS;
}

String CFeatureData::ToFormattedString() 
{
  String toS = L"";
  for (CStringPairs::iterator it = _data.begin(); it != _data.end(); it++) {
    toS += it->first + L": " + it->second + L"\n";
  }
  return toS;
}

void CFeatureData::FromString(String data) 
{
  Strings fields = split(data, FIELD_SEPARATOR);
  for (Strings::iterator it = fields.begin(); it != fields.end(); it++) {
    Strings fieldValue = split(*it, VALUE_SEPARATOR);
    _data.push_back(CStringPair(fieldValue[0], fieldValue.size() > 1 ? fieldValue[1] : L""));
  }
}

Strings CFeatureData::split(String data, const String & separator)
{
  Strings dataSplitted;
  
  int position(0);
  while ((position = data.find(separator)) != -1) {
    dataSplitted.push_back(data.substr(0, position));
    data = data.substr(position + separator.length());
  }
  if (data.length() > 0) dataSplitted.push_back(data);
  
  return dataSplitted;
}