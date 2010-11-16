#include "stdafx.h"
#include "ProvidersCollection.h"

#include <fdo.h>

CProvidersCollection::CProvidersCollection(bool onlySupported)
{
  FdoPtr<IProviderRegistry> pRegistry = FdoFeatureAccessManager::GetProviderRegistry();
  const FdoProviderCollection * providers = pRegistry->GetProviders();
  for (int i = 0; i < providers->GetCount(); i++ ) {
    FdoPtr<FdoProvider> provider = providers->GetItem(i);
    if (onlySupported) {
      if (IsSupported(provider)) {
        _providers.push_back(CProvider(provider));
      }
    } else {
      _providers.push_back(CProvider(provider));
    }
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
  
  throw FdoException::Create((L"Provider " + id + L" not found").c_str());
}

StringPairs CProvidersCollection::ToStringPairs() {
  StringPairs providersList;
  for (int i = 0; i < this->GetCount(); i++ ) {
    CProvider provider = this->GetItem(i);
    providersList.push_back(StringPair(provider.GetDisplayName(), provider.GetName()));
  }
  return providersList;
}

bool CProvidersCollection::IsSupported(FdoPtr<FdoProvider> provider) {
  String name = provider->GetDisplayName();
  return name.find(L"SHP") != -1 || name.find(L"PostGIS") != -1 || name.find(L"ArcSDE") != -1;
}