#include "stdafx.h"
#include "Connection.h"

CConnection::CConnection() : _connection(NULL)
{
}

CConnection::CConnection(String providerName)
{
  FdoPtr<FdoConnectionManager> connectMgr = (FdoConnectionManager *)FdoFeatureAccessManager::GetConnectionManager();
  _connection = connectMgr->CreateConnection(providerName.c_str());
}

CConnection::~CConnection(void)
{
}

void CConnection::SetConnectionString(String connString)
{
  _connection->SetConnectionString(connString.c_str());
}

FdoConnectionState CConnection::Open() {
  FdoConnectionState state;
  try {
	  state = _connection->Open();
	} catch (FdoConnectionException * ce) {
    state = FdoConnectionState_Closed;
	} catch (FdoException * e) {
    state = FdoConnectionState_Closed;
	}
  
  return state;
}

void CConnection::Close() { _connection->Close(); }

FdoPtr<FdoIConnectionInfo> CConnection::GetConnectionInfo() const { return _connection->GetConnectionInfo(); }

CConnectionParams CConnection::GetParams() const 
{ 
  CConnectionParams params;
  
  FdoPtr<FdoIConnectionInfo> info = _connection->GetConnectionInfo();
  FdoPtr<FdoIConnectionPropertyDictionary> connDict = info->GetConnectionProperties();
  
  FdoInt32 count = 0;
  FdoString ** names = connDict->GetPropertyNames(count);
  
  FdoStringP name;
  FdoStringP localname;
  
  for(int i = 0; i < count; i++) {
    name = names[i];
    params.push_back(CConnectionParam(connDict, String(name)));
  }
  
  return params;
}

CConnectionParam CConnection::GetParam(String id) const 
{ 
  FdoPtr<FdoIConnectionInfo> info = _connection->GetConnectionInfo();
  FdoPtr<FdoIConnectionPropertyDictionary> connDict = info->GetConnectionProperties();
  return CConnectionParam(connDict, id);
}

FdoICommand * CConnection::CreateCommand(FdoCommandType commandType) 
{
  return _connection->CreateCommand(commandType);
}