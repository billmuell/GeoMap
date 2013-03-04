#pragma once

#include <fdo.h>

#define VALUE_SEPARATOR L"###"
#define FIELD_SEPARATOR L"~~~"

struct info {
  String key;
  String value;
  String type;
};
typedef std::vector<info> INFO;

static const String InfoTypeStrings[] = { 
  L"FdoDataType_Boolean", L"FdoDataType_Byte", L"FdoDataType_DateTime", L"FdoDataType_Decimal", 
  L"FdoDataType_Double", L"FdoDataType_Int16", L"FdoDataType_Int32", L"FdoDataType_Int64", 
  L"FdoDataType_Single", L"FdoDataType_String", L"FdoDataType_BLOB", L"FdoDataType_CLOB" };

class CFeatureData
{
protected:
  // StringPairs _data;
   INFO _data;
public:
  CFeatureData();
  CFeatureData(String data);
  CFeatureData(INFO data);
public:
  ~CFeatureData(void);
public:
  void Add(String key, String value, String type);
  void Add(String key, String value, FdoDataType type);

  String GetValue(String key);
  String GetType(String key);
  Strings * CFeatureData::GetKeys();
  FdoPtr<FdoPropertyValue> GetPropertyValue(String key);
  
  String ToString();
  String ToFormattedString();
};
