#pragma once

#include "Connection.h"

#include <fdo.h>

class CProvider
{
protected:
  FdoPtr<FdoProvider> _provider;
public:
  CProvider(FdoPtr<FdoProvider> provider);
public:
  ~CProvider(void);
public:
  CConnection CreateConnection() const;
  String GetDisplayName() const;
  String GetName() const;
};
