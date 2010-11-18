#include "stdafx.h"
#include "AppConf.h"

CLocale * CAppConf::_locale = new CLocale(); 

CAppConf::CAppConf(void)
{
}

CAppConf::~CAppConf(void)
{
}

void CAppConf::SetLocale(String locale) {
  _locale = new CLocale(locale);
}

CLocale & CAppConf::GetLocale() {
  if (_locale == 0) {
    _locale = new CLocale();
  }
  return *(_locale);
}