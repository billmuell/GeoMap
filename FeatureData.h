#pragma once

#include <map>

#define VALUE_SEPARATOR L"###"
#define FIELD_SEPARATOR L"~~~"

class CFeatureData
{
protected:
  StringPairs _data;
public:
  CFeatureData();
  CFeatureData(StringPairs data);
public:
  ~CFeatureData(void);
public:
  void Add(String key, String value);
  String GetValue(String key);
  
  String ToString();
  String ToFormattedString();
  void FromString(String data);
};
