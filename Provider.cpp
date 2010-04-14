#include "stdafx.h"
#include "Provider.h"

CProvider::CProvider(FdoPtr<FdoProvider> provider)
  : _provider(provider)
{
}

CProvider::~CProvider(void)
{
}

CConnection CProvider::CreateConnection() const 
{ 
  return CConnection(this->GetName());
}
String CProvider::GetDisplayName() const { return _provider->GetDisplayName(); }
String CProvider::GetName() const { return _provider->GetName(); }
