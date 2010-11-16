#include "stdafx.h"
#include "Utils.h"

#include <fstream>
#include <sstream>

CUtils::CUtils(void)
{
}

CUtils::~CUtils(void)
{
}

Strings CUtils::Split(String data, const String & separator)
{
  Strings dataSplitted;
  
  int position(0);
  while ((position = data.find(separator)) != -1) {
    dataSplitted.push_back(data.substr(0, position));
    data = data.substr(position + separator.length());
  }
  if (data.length() > 0) dataSplitted.push_back(data);
  
  return dataSplitted;
}

String CUtils::ReadFile(const String & filename)
{
  std::wfstream fs(filename.c_str(), std::ios_base::in);
  if (!fs) return L"";
  
  std::wostringstream ss;
  ss << fs.rdbuf();
  
  return ss.str();
}