#pragma once

#include "Provider.h"

class CProvidersCollection
{
protected:
  std::vector<CProvider> _providers;

public:
  CProvidersCollection(bool onlySupported = false);
public:
  ~CProvidersCollection(void);
public:
  int GetCount() const;
  CProvider GetItem(int num) const;
  CProvider GetItem(String id) const;
  StringPairs ToStringPairs();

protected:
  bool IsSupported(FdoPtr<FdoProvider> provider);
};
