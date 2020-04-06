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
 *  ServiceControlManager.h
 *
 *****************************************************************************/

// SOL9
// 2011/09/06 Updated createService method.
#pragma once
// 2010/05/30

#include <sol/service/ServiceControl.h>
#include <sol/service/ServiceController.h>

namespace SOL {

class ServiceControlManager :public ServiceControl {
  
public:
  /*
  desiredAccess may take one or some combination of the following values:
  SC_MANAGER_CONNECT             
  SC_MANAGER_CREATE_SERVICE      
  SC_MANAGER_ENUMERATE_SERVICE   
  SC_MANAGER_LOCK                
  SC_MANAGER_QUERY_LOCK_STATUS   
  SC_MANAGER_MODIFY_BOOT_CONFIG  
  SC_MANAGER_ALL_ACCESS
  */

  ServiceControlManager(__in LPCTSTR machineName=NULL, 
      __in LPCTSTR databaseName=NULL,
      __in DWORD desiredAccess=SC_MANAGER_ALL_ACCESS)
    :ServiceControl(NULL)
  {
    SC_HANDLE hServiceControl = OpenSCManager(
        machineName,
      databaseName,
       desiredAccess);
    if (hServiceControl == NULL) {
      throw E_FAIL;
    } else {
      setServiceControl(hServiceControl);
    }
  }
  
/*
The desiredAccess parameter takes one or combinations of the following values
  SERVICE_ALL_ACCESS
  SERVICE_CHANGE_CONFIG
   SERVICE_ENUMERATE_DEPENDENTS
  SERVICE_INTERROGATE
  SERVICE_PAUSE_CONTINUE
  SERVICE_QUERY_CONFIG
  SERVICE_QUERY_STATUS
  SERVICE_START
  SERVICE_STOP
  SERVICE_USER_DEFINED_CONTROL
*/
public:
  BOOL openService(
      __in LPCTSTR serviceName,
      __in DWORD desiredAccess,
      __out ServiceController& service)
  {
    BOOL rc = FALSE;
    SC_HANDLE hServiceControl = getServiceControl();

    SC_HANDLE hService = OpenService(
          hServiceControl,
        serviceName,
        desiredAccess);
    if (hService == NULL) {
      throw E_FAIL;
    } else {
      service.setServiceControl(hService);
      rc = TRUE;
    }
    return rc;
  }

public:
  SC_HANDLE openService(
      __in LPCTSTR serviceName,
      __in DWORD desiredAccess)
  {
    SC_HANDLE hServiceControl = getServiceControl();

    SC_HANDLE hService = OpenService(
          hServiceControl,
        serviceName,
        desiredAccess);
    if (hService == NULL) {
      throw E_FAIL;
    }
    return hService;
  }

public:
  SC_HANDLE createService(
        __in        LPCTSTR  lpServiceName,  //2011/09/06 Changed to LPCSTR
        __in_opt    LPCTSTR  lpDisplayName,  //2011/09/06 Changed to LPCTSTR
        __in        DWORD    dwDesiredAccess,
        __in        DWORD    dwServiceType,
        __in        DWORD    dwStartType,
        __in        DWORD    dwErrorControl,
        __in_opt    LPCTSTR  lpBinaryPathName,
        __in_opt    LPCTSTR  lpLoadOrderGroup,
        __out_opt   LPDWORD  lpdwTagId,
        __in_opt    LPCTSTR  lpDependencies,
        __in_opt    LPCTSTR  lpServiceStartName,
        __in_opt    LPCTSTR  lpPassword)
  {

    SC_HANDLE hServiceControl = getServiceControl();
    SC_HANDLE hService =  CreateService(
          hServiceControl,
        lpServiceName,
        lpDisplayName,
        dwDesiredAccess,
        dwServiceType,
        dwStartType,
        dwErrorControl,
        lpBinaryPathName,
        lpLoadOrderGroup,
        lpdwTagId,
        lpDependencies,
        lpServiceStartName,
        lpPassword);
    if (hService == NULL) {
      throw E_FAIL;
    }
    return hService;
  }

public:
  BOOL queryServiceLockStatus(
      __in  LPQUERY_SERVICE_LOCK_STATUS  lpLockStatus,
      __in  DWORD                        cbBufSize,
      __out LPDWORD                      pcbBytesNeeded)
  {
    SC_HANDLE hSCManager = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = QueryServiceLockStatus(
          hSCManager,
          lpLockStatus,
          cbBufSize,
          pcbBytesNeeded)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }


public:
  BOOL enumServicesStatus(
      __in  DWORD                   dwServiceType,
      __in  DWORD                   dwServiceState,
      __in  LPENUM_SERVICE_STATUS   lpServices,
      __in  DWORD                   cbBufSize,
      __out LPDWORD                 pcbBytesNeeded,
      __out LPDWORD                 lpServicesReturned,
      __inout_opt LPDWORD           lpResumeHandle)
  {
    SC_HANDLE hSCManager = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = EnumServicesStatus(
          hSCManager,
          dwServiceType,
          dwServiceState,
          lpServices,
          cbBufSize,
          pcbBytesNeeded,
          lpServicesReturned,
          lpResumeHandle)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  BOOL enumServicesStatusEx(
      __in   SC_ENUM_TYPE    InfoLevel,
      __in   DWORD           dwServiceType,
      __in   DWORD           dwServiceState,
      __in   LPBYTE          lpServices,
      __in   DWORD           cbBufSize,
      __out  LPDWORD         pcbBytesNeeded,
      __out  LPDWORD         lpServicesReturned,
      __inout_opt  LPDWORD   lpResumeHandle,
      __in_opt LPCTSTR       pszGroupName)
  {
    SC_HANDLE hSCManager = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = EnumServicesStatusEx(
          hSCManager,
          InfoLevel,
          dwServiceType,
          dwServiceState,
          lpServices,
          cbBufSize,
          pcbBytesNeeded,
          lpServicesReturned,
          lpResumeHandle,
          pszGroupName)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  BOOL getServiceKeyName(
        __in    LPCTSTR  lpDisplayName,
                __in    LPTSTR   lpServiceName,
        __inout LPDWORD  lpcchBuffer)
  {
    SC_HANDLE hSCManager = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = GetServiceKeyName(
          hSCManager,
          lpDisplayName,
          lpServiceName,
          lpcchBuffer)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  BOOL getServiceDisplayName(
      __in    LPCTSTR lpServiceName,
      __in    LPTSTR  lpDisplayName,
      __inout LPDWORD lpcchBuffer)
  {
    SC_HANDLE hSCManager = getServiceControl();
    BOOL rc = FALSE;
    if ((rc = GetServiceDisplayName(
        hSCManager,
        lpServiceName,
                lpDisplayName,
        lpcchBuffer)) == FALSE) {
      throw E_FAIL;
    }
    return rc;
  }

public:
  SC_LOCK lockServiceDatabase()
  {
    SC_HANDLE hSCManager = getServiceControl();
    SC_LOCK hLock = NULL;

    if ((hLock = LockServiceDatabase(
      hSCManager)) == NULL) {
      throw E_FAIL;
    }
    return hLock;
  }
};


}
