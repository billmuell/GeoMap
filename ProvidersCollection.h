#pragma once

#include "Provider.h"

class CProvidersCollection
{
protected:
  //FdoProviderCollection * _providers;
  std::vector<CProvider> _providers;

public:
  CProvidersCollection(void);
public:
  ~CProvidersCollection(void);
public:
  int GetCount() const;
  CProvider GetItem(int num) const;
  CProvider GetItem(String id) const;
  CStringPairs ToStringPairs();
};
