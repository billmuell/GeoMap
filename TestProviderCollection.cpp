#ifdef TEST

#include "stdafx.h"
#include "TestProviderCollection.h"

#include "ProvidersCollection.h"

int CTestProviderCollection::TestAll()
{
  CProvidersCollection pc;
  if (pc.GetCount() <= 0) {
    acutPrintf(L"Error 'CTestProviderCollection::TestAll': No providers found\n");
    return 0;
  }
  
  try {
    StringPairs providersList = pc.ToStringPairs();
  } catch (...) {
    acutPrintf(L"Error 'CTestProviderCollection::TestAll': Unexpected error when exporting to StringPairs\n");
    return 0;
  }
  
  try {
    CProvider provider = pc.GetItem(0);
  } catch (...) {
    acutPrintf(L"Error 'CTestProviderCollection::TestAll': Unexpected error when accessing to first provider\n");
    return 0;
  }

  return 1;
}

#endif