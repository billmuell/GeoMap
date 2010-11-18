#pragma once

class CLocale
{
protected:
  StringPairs _locale;
public:
  CLocale();
  CLocale(const String & locale);
public:
  ~CLocale(void);
protected:
  String ReadFile(const String & filename);
public:
  String GetOriginal(String translation);
  String GetTranslation(String key);
};
