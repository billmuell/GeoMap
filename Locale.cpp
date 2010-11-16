#include "stdafx.h"
#include "Locale.h"
#include "Utils.h"

CLocale::CLocale()
{
  CLocale::CLocale(L"");
}

CLocale::CLocale(const String & lcl)
{
  String filename(L"locale/messages_");
  filename += lcl;
  filename += L".properties";
  
  String content = CUtils::ReadFile(filename);
  if (content.length() == 0) return;
  
  Strings lines = CUtils::Split(content, L"\n");
  for (Strings::iterator it = lines.begin(); it != lines.end(); it++) {
    Strings splitted = CUtils::Split(*it, L"=");
    _locale.push_back(StringPair(splitted[0], splitted[1]));
  }
}

CLocale::~CLocale(void)
{
}

String CLocale::GetTranslation(String key) 
{
  for (StringPairs::iterator it = _locale.begin(); it != _locale.end(); it++) {
    if (it->first.compare(key)) return it->second;
  }
  
  return key;
}