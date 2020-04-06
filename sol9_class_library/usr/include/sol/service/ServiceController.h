/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *  
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  ServiceController.h
 *
 *****************************************************************************/

// SOL9

#pragma once
// 2010/05/30

#include <sol/service/ServiceControl.h>

namespace SOL {

class ServiceController :public ServiceControl {

public:
  ServiceController(SC_HANDLE handle=NULL)
    :ServiceControl(handle)
  {
  }

public:
  ~ServiceController()
  {
  }

public:
  BOOL controlService(
    __in  DWORD             dwControl,
    __out LPSERVICE_STATUS  lpServiceStatus)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;

    if ((rc = ControlService(
      hService,
      dwControl,
      lpServiceStatus)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  BOOL
    startService(
      __in    DWORD   dwNumServiceArgs,
      __inout LPCTSTR *lpServiceArgVectors)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = StartService(
        hService,
        dwNumServiceArgs,
        lpServiceArgVectors)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  BOOL deleteService()
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = DeleteService(hService)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  /*
  dwServiceState takes one of the following values
  SERVICE_ACTIVE 
  SERVICE_INACTIVE
  SERVICE_STATE_ALL  
  */
  BOOL enumDependentServices(
    __in  DWORD                   dwServiceState,        
    __in  LPENUM_SERVICE_STATUS  lpServices,
    __in  DWORD                   cbBufSize,
    __out LPDWORD                 pcbBytesNeeded,
    __out LPDWORD                 lpServicesReturned)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = EnumDependentServices(
      hService,
      dwServiceState,
            lpServices,
      cbBufSize,
      pcbBytesNeeded,
      lpServicesReturned)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  SERVICE_STATUS queryStatus()
  {
    SERVICE_STATUS status;
    ZeroMemory(&status, sizeof(status));
    
    SC_HANDLE hService = getServiceControl();

    if (QueryServiceStatus(hService, &status) == FALSE) {
      throw E_FAIL;  
    }
    return status;
  }

public:
  BOOL queryServiceStatusEx(
      __in  SC_STATUS_TYPE infoLevel,
      __in  LPBYTE         lpBuffer,
      __in  DWORD          cbBufSize,
      __out LPDWORD        pcbBytesNeeded)
  {
    SC_HANDLE hService = getServiceControl();

    BOOL rc = FALSE;
    if ((rc = QueryServiceStatusEx(
        hService,
        infoLevel,
        lpBuffer,
        cbBufSize,
        pcbBytesNeeded)) == FALSE) {
      throw E_FAIL; 
    }
    return rc;
  }

public:

  BOOL isServiceRunning()
  {
    BOOL rc = FALSE;
    SERVICE_STATUS status;
    ZeroMemory(&status, sizeof(status));

    SC_HANDLE hService = getServiceControl();

    if (QueryServiceStatus(hService, &status) == FALSE) {
      throw E_FAIL;  
    }
    if (status.dwCurrentState == SERVICE_RUNNING) {
      rc = TRUE;
    }
    return rc;
  }

public:
  DWORD getCurentState()
  {
    SERVICE_STATUS status;
    ZeroMemory(&status,sizeof(status));
    SC_HANDLE hService = getServiceControl();

    if (QueryServiceStatus(hService, &status ) == FALSE) {
      throw E_FAIL;  
    }
    return status.dwCurrentState;
  }

public:
  BOOL setServiceObjectSecurity(
    __in  SECURITY_INFORMATION    dwSecurityInformation,
    __in  PSECURITY_DESCRIPTOR    lpSecurityDescriptor)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = SetServiceObjectSecurity(
        hService,
        dwSecurityInformation,
        lpSecurityDescriptor)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  BOOL changeServiceConfig(
    __in       DWORD    dwServiceType,
    __in       DWORD    dwStartType,
    __in       DWORD    dwErrorControl,
    __in_opt   LPCTSTR  lpBinaryPathName,
    __in_opt   LPCTSTR  lpLoadOrderGroup,
    __out_opt  LPDWORD  lpdwTagId,
    __in_opt   LPCTSTR  lpDependencies,
    __in_opt   LPCTSTR  lpServiceStartName,
    __in_opt   LPCTSTR  lpPassword,
    __in_opt   LPCTSTR  lpDisplayName)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = ChangeServiceConfig(
      hService,
      dwServiceType,
      dwStartType,
      dwErrorControl,
      lpBinaryPathName,
      lpLoadOrderGroup,
      lpdwTagId,
      lpDependencies,
      lpServiceStartName,
      lpPassword,
      lpDisplayName)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  BOOL queryServiceConfig(
      __in  LPQUERY_SERVICE_CONFIG lpServiceConfig,
      __in  DWORD   cbBufSize,
      __out LPDWORD pcbBytesNeeded)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = QueryServiceConfig(
        hService,
        lpServiceConfig,
        cbBufSize,
        pcbBytesNeeded)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }


public:
  BOOL queryServiceConfig2(
      __in   DWORD   dwInfoLevel,
      __in   LPBYTE  lpBuffer,
      __in   DWORD   cbBufSize,
      __out  LPDWORD pcbBytesNeeded)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = QueryServiceConfig2(
          hService,
          dwInfoLevel,
          lpBuffer,
          cbBufSize,
          pcbBytesNeeded)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }


public:
  BOOL queryServiceObjectSecurity(
      __in  SECURITY_INFORMATION    dwSecurityInformation,
            __in  PSECURITY_DESCRIPTOR    lpSecurityDescriptor,
      __in  DWORD                   cbBufSize,
      __out LPDWORD                 pcbBytesNeeded)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = QueryServiceObjectSecurity(
          hService,
          dwSecurityInformation,
          lpSecurityDescriptor,
          cbBufSize,
          pcbBytesNeeded)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }


#if (NTDDI_VERSION >= NTDDI_VISTA)

public:

  DWORD notifyServiceStatusChange (
    __in  DWORD            dwNotifyMask,
    __in  PSERVICE_NOTIFY  pNotifyBuffer)
  {
    SC_HANDLE hService = getServiceControl();
    return NotifyServiceStatusChange (
      hService,
      dwNotifyMask,
      pNotifyBuffer);
  }

public:
  BOOL controlServiceEx(
    __in    DWORD  dwControl,
    __in    DWORD  dwInfoLevel,
    __inout PVOID  pControlParams)
  {
    SC_HANDLE hService = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = ControlServiceEx(
      hService,
      dwControl,
      dwInfoLevel,
      pControlParams)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

#endif // NTDDI_VERSION >= NTDDI_VISTA
    

};


}
