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
    toS += it->first + L"###" + it->second;
  }
  return toS;
}

void CFeatureData::FromString(String data) 
{
  _data.push_back(CStringPair(data, data));
}