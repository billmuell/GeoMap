#include "stdafx.h"

class CTheArxApp: public AcRxArxApp
{
public:
  CTheArxApp(): AcRxArxApp() {}

  virtual void RegisterServerComponents() {}

  virtual AcRx::AppRetCode On_kInitAppMsg(void* pAppData)
  {
    AcRx::AppRetCode result = AcRxArxApp::On_kInitAppMsg(pAppData);

    //Place your init code here

    return result;
  }
};

IMPLEMENT_ARX_ENTRYPOINT(CTheArxApp)

/////////////////////////////////////////////////////////////
#include <afxdllx.h>

AC_IMPLEMENT_EXTENSION_MODULE( TheArxAppDLL)

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
  UNREFERENCED_PARAMETER(lpReserved);

  if (DLL_PROCESS_ATTACH == dwReason)
  {
    _hdllInstance = hInstance;
    TheArxAppDLL.AttachInstance(hInstance);
    InitAcUiDLL();
    acdbRegApp(APPNAME);
  }
  else 
  if (DLL_PROCESS_DETACH == dwReason)
  {
    TheArxAppDLL.DetachInstance();
  }
  return TRUE;

} // extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)


