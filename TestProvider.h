#pragma once

class CTestProvider
{
public:
  static int TestProvider(String & providerName);
  static int TestCreateConnection(String & providerName);
  static int TestAll();
};
