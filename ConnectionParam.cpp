#include "stdafx.h"
#include "ConnectionParam.h"

CConnectionParam::CConnectionParam(FdoPtr<FdoIConnectionPropertyDictionary> connDict, String & name) 
  : _connDict(connDict), _name(name)
{
}

CConnectionParam::~CConnectionParam(void)
{
}

String CConnectionParam::GetDisplayName() const
{
  return _connDict->GetLocalizedName(_name.c_str());
}

bool CConnectionParam::IsRequired() const
{
  return _connDict->IsPropertyRequired(_name.c_str());
}

bool CConnectionParam::IsProtected() const
{
  return _connDict->IsPropertyProtected(_name.c_str());
}

bool CConnectionParam::IsEnumerable() const
{
  return _connDict->IsPropertyEnumerable(_name.c_str());
}

bool CConnectionParam::IsFilePath() const
{
  return _connDict->IsPropertyFilePath(_name.c_str());
}

bool CConnectionParam::IsFileName() const
{
  return _connDict->IsPropertyFileName(_name.c_str());
}

Strings CConnectionParam::GetEnumValues() const
{
  Strings evs;
  FdoInt32 enumCount = 0;
  FdoString ** enumNames = _connDict->EnumeratePropertyValues(_name.c_str(), enumCount);
  if (enumCount == 0) {
    String def(_connDict->GetPropertyDefault(_name.c_str()));
    if (def.length() != 0) evs.push_back(def);
  } else {
    for(int j = 0; j < enumCount; j++) {
      evs.push_back(enumNames[j]);
    }
  }
  return evs;
}
