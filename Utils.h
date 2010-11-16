#pragma once

class CUtils
{
protected:
  CUtils(void);
public:
  ~CUtils(void);
public:
  static Strings Split(String data, const String & separator);
  static String ReadFile(const String & filename);
};
