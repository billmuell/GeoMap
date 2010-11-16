#pragma once

#include "Locale.h"

class CAppConf
{
protected:
  static CLocale * _locale;
protected:
  CAppConf(void);
protected:
  ~CAppConf(void);
public:
  static void SetLocale(String locale);
  static CLocale & GetLocale();
};
