#pragma once

#include <fdo.h>

class CConnectionParam
{
protected:
  String _name;
  FdoPtr<FdoIConnectionPropertyDictionary> _connDict;

public:
  CConnectionParam(FdoPtr<FdoIConnectionPropertyDictionary> connDict, String & name);
public:
  ~CConnectionParam(void);
public:
  String GetDisplayName() const;
  bool IsRequired() const;
  bool IsProtected() const;
  bool IsEnumerable() const;
  bool IsFilePath() const;
  bool IsFileName() const;
  Strings GetEnumValues() const;
};
