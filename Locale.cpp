#include "stdafx.h"
#include "Locale.h"
#include "Utils.h"

CLocale::CLocale()
{
  CLocale::CLocale(L"");
}

CLocale::CLocale(const String & lcl)
{
  String filename(L"locale/messages");
  if (lcl.length() > 0) {
    filename += L"_";
    filename += lcl;
  }
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

String CLocale::GetOriginal(String translation)
{
  bool appendSpace = false;
  if (translation.substr(translation.length() - 1, 1).compare(L" ") == 0) {
    translation = translation.substr(0, translation.length() - 1);
    appendSpace = true;
  }
  
  for (StringPairs::iterator it = _locale.begin(); it != _locale.end(); it++) {
    if (it->second.compare(translation) == 0) {
      String original = it->first;
      if (appendSpace) original += L" ";
      return original;
    }
  }

  return (appendSpace ? translation.append(L" ") : translation);
}

String CLocale::GetTranslation(String original) 
{
  bool appendSpace = false;
  if (original.substr(original.length() - 1, 1).compare(L" ") == 0) {
    original = original.substr(0, original.length() - 1);
    appendSpace = true;
  }

  for (StringPairs::iterator it = _locale.begin(); it != _locale.end(); it++) {
    if (it->first.compare(original) == 0) {
      String translation = it->second;
      if (appendSpace) translation += L" ";
      return translation;
#ifdef TEST    
    /*} else {
      acutPrintf(L"\noriginal:");
      acutPrintf(original.c_str());
      acutPrintf(L"\nCompare:");
      acutPrintf(it->first.c_str());*/
#endif
    }
  }
  
  return (appendSpace ? original.append(L" ") : original);
}