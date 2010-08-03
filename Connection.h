#pragma once

#include "stdafx.h"

#include "ConnectionParam.h"

#include <fdo.h>

typedef std::vector<CConnectionParam> CConnectionParams;

class CConnection
{
protected:
  FdoPtr<FdoIConnection> _connection;
public:
  CConnection();
  CConnection(String providerName);
public:
  ~CConnection(void);

public:
  void SetConnectionString(String connString);
  FdoConnectionState Open();
  void Close();
  FdoPtr<FdoIConnectionInfo> GetConnectionInfo() const;
  CConnectionParams GetParams() const;
  CConnectionParam GetParam(String id) const;
  FdoICommand * CreateCommand(FdoCommandType commandType);

protected:
};
