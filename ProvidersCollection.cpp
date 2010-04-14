#include "stdafx.h"
#include "ProvidersCollection.h"

#include <fdo.h>

CProvidersCollection::CProvidersCollection(void)
{
  FdoPtr<IProviderRegistry> pRegistry = FdoFeatureAccessManager::GetProviderRegistry();
  const FdoProviderCollection * providers = pRegistry->GetProviders();
  for (int i = 0; i < providers->GetCount(); i++ ) {
    FdoPtr<FdoProvider> provider = providers->GetItem(i);
    _providers.push_back(CProvider(provider));
  }
}

CProvidersCollection::~CProvidersCollection(void)
{
}

int CProvidersCollection::GetCount() const { return _providers.size(); }
CProvider CProvidersCollection::GetItem(int num) const 
{ 
  return _providers[num];
}
CProvider CProvidersCollection::GetItem(String id) const
{ 
  for (int i = 0; i < this->GetCount(); i++ ) {
    CProvider provider = this->GetItem(i);
    if (provider.GetName() == id) return provider;
  }

  return NULL;
}

CStringPairs CProvidersCollection::ToStringPairs() {
  CStringPairs providersList;
  for (int i = 0; i < this->GetCount(); i++ ) {
    CProvider provider = this->GetItem(i);
    providersList.push_back(CStringPair(provider.GetDisplayName(), provider.GetName()));
  }
  return providersList;
}