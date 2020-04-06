/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SWbemLocator.h
 *
 *****************************************************************************/

// 2012/03/08 Updated.

#pragma once

#include <sol/wmi/SWbemBaseObject.h>
#include <sol/wmi/SWbemServices.h>

namespace SOL {

class SWbemLocator :public SWbemBaseObject {

public:
  SWbemLocator(bool instanceCreation=true)
  {
    if (instanceCreation) {
      createInstance();
    }
  }

public:
  HRESULT createInstance()
  {
    return ComObject::createInstance(CLSID_SWbemLocator, IID_ISWbemLocator, CLSCTX_INPROC_SERVER);
  }

public:
  ISWbemLocator* get()
  {
    return (ISWbemLocator*)getIDispatch();
  }


public:
  ISWbemServices* connectServer( 
           __in BSTR strServer,
           __in BSTR strNamespace,
           __in BSTR strUser=NULL,
           __in BSTR strPassword=NULL,
           __in BSTR strLocale=NULL,
           __in BSTR strAuthority=NULL,
           __in long iSecurityFlags=0,
           __in IDispatch *objWbemNamedValueSet=NULL)        
  {
    ISWbemLocator* locator = get();

    ISWbemServices* iservices = NULL;
  
    HRESULT hr = locator->ConnectServer(
      strServer,
      strNamespace,
      strUser,
      strPassword,
      strLocale,
      strAuthority,
      iSecurityFlags,
      objWbemNamedValueSet,
      &iservices);
    if (FAILED(hr)) {
      printf("Failed to connectServer: \"%S\"\n", strServer);
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
      
    return iservices;
  }


public:
  ISWbemSecurity* getSecurity()
  {
    ISWbemLocator* locator = get();
    ISWbemSecurity* security = NULL;

    HRESULT hr = locator->get_Security_(&security);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return security;
  }
};


}
