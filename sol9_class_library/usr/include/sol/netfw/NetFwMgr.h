/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  NetFwMgr.h
 *
 *****************************************************************************/

//2012/09/14

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>

/** 
//Usage:
  ApartmentThreadedModel model;
  NetFwMgr mgr;
*/

namespace SOL {

class NetFwMgr: public ComIDispatch {
    
public:
  NetFwMgr()
    :ComIDispatch()
  {
    createInstance();
  }

public:
  HRESULT createInstance()
  {
    INetFwMgr* pMgr = NULL;

    HRESULT hr = CoCreateInstance(__uuidof(::NetFwMgr), NULL, 
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwMgr), 
        (void**)&pMgr );
    if (SUCCEEDED(hr)) {
      set(pMgr);
    } else {
      throw hr;
    }
    return hr;
  }

private:
  INetFwMgr* getManager()
  {
    return (INetFwMgr*) getIDispatch();
  }

public:
  
  HRESULT getLocalPolicy( 
            /* [retval][out] */ INetFwPolicy **localPolicy)
  {
    HRESULT hr = getManager() -> get_LocalPolicy( 
        localPolicy);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  INetFwPolicy* getLocalPolicy()
  {
    INetFwPolicy* pLocalPolicy = NULL;
    HRESULT hr = getManager() -> get_LocalPolicy( 
        &pLocalPolicy);
    if (FAILED(hr)) {
      throw hr;
    }
    return pLocalPolicy;
  }

public:
  HRESULT getCurrentProfileType( 
            /* [retval][out] */ NET_FW_PROFILE_TYPE *profileType)
  {
    HRESULT hr = getManager() -> get_CurrentProfileType( 
          profileType);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  NET_FW_PROFILE_TYPE getCurrentProfileType()
  {
    NET_FW_PROFILE_TYPE profileType;
    HRESULT hr = getManager() -> get_CurrentProfileType( 
          &profileType);

    if (FAILED(hr)) {
      throw hr;
    }
    return profileType;
  }

public:
  HRESULT restoreDefaults()
  {
    HRESULT hr = getManager() -> RestoreDefaults();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT isPortAllowed( 
            /* [in] */ BSTR imageFileName,
            /* [in] */ NET_FW_IP_VERSION ipVersion,
            /* [in] */ LONG portNumber,
            /* [in] */ BSTR localAddress,
            /* [in] */ NET_FW_IP_PROTOCOL ipProtocol,
            /* [out] */ VARIANT *allowed,
            /* [out] */ VARIANT *restricted)
  {
    HRESULT hr = getManager() -> IsPortAllowed( 
        imageFileName,
        ipVersion,
        portNumber,
        localAddress,
        ipProtocol,
        allowed,
        restricted);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT isPortAllowed( 
            /* [in] */ BSTR imageFileName,
            /* [in] */ NET_FW_IP_VERSION ipVersion,
            /* [in] */ LONG portNumber,
            /* [in] */ BSTR localAddress,
            /* [in] */ NET_FW_IP_PROTOCOL ipProtocol,
            /* [out] */ bool& allowed,
      /* [out] */ bool& restricted)
  {
    _variant_t vAllowed;
    _variant_t vRestricted;
    HRESULT hr = getManager() -> IsPortAllowed( 
        imageFileName,
        ipVersion,
        portNumber,
        localAddress,
        ipProtocol,
        &vAllowed,
        &vRestricted);
    if (FAILED(hr)) {
      throw hr;
    }

    if (vAllowed.vt == VT_BOOL) {
      allowed = toBool(vAllowed.boolVal);
    }    
    if (vRestricted.vt == VT_BOOL) {
      restricted = toBool(vRestricted.boolVal);
    }
    return hr;
  }

public:
  HRESULT isIcmpTypeAllowed( 
            /* [in] */ NET_FW_IP_VERSION ipVersion,
            /* [in] */ BSTR localAddress,
            /* [in] */ BYTE type,
            /* [out] */ VARIANT *allowed,
            /* [out] */ VARIANT *restricted)
  {
    HRESULT hr = getManager() ->  IsIcmpTypeAllowed( 
        ipVersion,
        localAddress,
        type,
        allowed,
        restricted);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  HRESULT isIcmpTypeAllowed( 
            /* [in] */ NET_FW_IP_VERSION ipVersion,
            /* [in] */ BSTR localAddress,
            /* [in] */ BYTE type,
            /* [out] */ bool& allowed,
            /* [out] */ bool& restricted)
  {
    _variant_t vAllowed;
    _variant_t vRestricted;

    HRESULT hr = getManager() ->  IsIcmpTypeAllowed( 
        ipVersion,
        localAddress,
        type,
        &vAllowed,
        &vRestricted);
    if (FAILED(hr)) {
      throw hr;
    }

    if (vAllowed.vt == VT_BOOL) {
      allowed = toBool(vAllowed.boolVal);
    }    
    if (vRestricted.vt == VT_BOOL) {
      restricted = toBool(vRestricted.boolVal);
    }

    return hr;
  }
public:
  virtual void displayIsPortAllowed( 
            /* [in] */ _bstr_t imageFileName,
            /* [in] */ NET_FW_IP_VERSION ipVersion,
            /* [in] */ LONG portNumber,
            /* [in] */ _bstr_t localAddress,
            /* [in] */ NET_FW_IP_PROTOCOL ipProtocol,
            /* [out] */ bool& allowed,
      /* [out] */ bool& restricted)
  {
    HRESULT hr = isPortAllowed( 
          (BSTR)imageFileName,
          ipVersion,
          portNumber,
          (BSTR)localAddress,
          ipProtocol,
          allowed,
          restricted);
    if (FAILED(hr)) {
      _tprintf(_T("Failed to displayIsPortAllowed: %x\n"), hr);
      //throw hr;
    } else {

      NetFwName name;
      _tprintf(_T("<IsPortAllowed>\n"));
      _tprintf(_T("<In>\n"));
      _tprintf(_T("<ImageFileName>%s</ImageFileName>\n"), (const TCHAR*)imageFileName);
      _tprintf(_T("<IPVersion>%s</IPVersion>\n"), (const TCHAR*)name.toString(ipVersion));
      _tprintf(_T("<LocalPort>%d</LocalPort>\n"), portNumber);
      
      _tprintf(_T("<LocalAddress>%s</LocalAddress>\n"), (const TCHAR*)localAddress);
      _tprintf(_T("<Protocol>%s</Protocol>\n"), (const TCHAR*)name.toString(ipProtocol));
      _tprintf(_T("</In>\n"));

      _tprintf(_T("<Out>\n"));
      _tprintf(_T("<Allowed>%s</Allowed>\n"), name.toString(allowed) );
      _tprintf(_T("<Restricted>%s</Restricted>\n"), name.toString(restricted) );
      _tprintf(_T("</Out>\n"));

      _tprintf(_T("</IsPortAllowed>\n"));
    }
  }

};

}
