#pragma once

#include <map>

class CFeatureData
{
protected:
  CStringPairs _data;
public:
  CFeatureData();
  CFeatureData(CStringPairs data);
public:
  ~CFeatureData(void);
public:
  void Add(String key, String value);
  String GetValue(String key);
  
  String ToString();
  void FromString(String data);
};
