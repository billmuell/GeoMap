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

String CUtils::ReadFile(const String & filename)
{
  std::wfstream fs(filename.c_str(), std::ios_base::in);
  if (!fs) return L"";
  
  std::wostringstream ss;
  ss << fs.rdbuf();
  
  return ss.str();
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

String CUtils::Trim(const String & data)
{
  String aux(data);
  
  if (aux.length() == 0) return aux;
  
  aux = LTrim(aux);
  aux = RTrim(aux);
  
  return aux;
}

String CUtils::LTrim(const String &data)
{
  String aux(data);
  for (int i = 0; (aux.length() > 0) && !iswgraph(aux.substr(i, 1).operator [](0)); ) 
    aux.erase(i, 1);
  
  return aux;
}

String CUtils::RTrim(const String& data)
{
  String  aux(data);
  for (int i = aux.length() - 1; (aux.length() > 0) && !iswgraph(aux.substr(i, 1).operator [](0)); i--)
    aux.erase(i, 1);
  
  return aux;
}