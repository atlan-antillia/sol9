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
 *  NetFwRemoteAdminSettings.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>
#include <sol/Writer.h>


namespace SOL {

class NetFwRemoteAdminSettings: public ComIDispatch {

public:
  NetFwRemoteAdminSettings(INetFwRemoteAdminSettings* pSettings)
    :ComIDispatch(pSettings)
  {
  }

private:
  INetFwRemoteAdminSettings* getSettings()
  {
    return (INetFwRemoteAdminSettings*) getIDispatch();
  }

public:
  HRESULT getIpVersion( 
            /* [retval][out] */ NET_FW_IP_VERSION *ipVersion)
  {
    HRESULT hr = getSettings() -> get_IpVersion( 
        ipVersion);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  NET_FW_IP_VERSION getIpVersion()
  {
    NET_FW_IP_VERSION ipVersion;
    HRESULT hr = getSettings() -> get_IpVersion( 
        &ipVersion);
    if (FAILED(hr)) {
      throw hr;
    }
    return ipVersion;
  }

public:
  HRESULT putIpVersion( 
            /* [in] */ NET_FW_IP_VERSION ipVersion)
  {
    HRESULT hr = getSettings() -> put_IpVersion( 
          ipVersion);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getScope( 
            /* [retval][out] */ NET_FW_SCOPE *scope)
  {
    HRESULT hr = getSettings() -> get_Scope( 
          scope);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  NET_FW_SCOPE getScope()
  {
    NET_FW_SCOPE scope;
    HRESULT hr = getSettings() -> get_Scope( 
          &scope);
    if (FAILED(hr)) {
      throw hr;
    }
    return scope;
  }


public:
  HRESULT putScope( 
            /* [in] */ NET_FW_SCOPE scope)
  {
    HRESULT hr = getSettings() -> put_Scope( 
        scope);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  HRESULT getRemoteAddresses( 
            /* [retval][out] */ BSTR *remoteAddrs)
  {
    HRESULT hr = getSettings() -> get_RemoteAddresses( 
          remoteAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  _bstr_t getRemoteAddresses()
  {
    BSTR remoteAddrs = NULL;
    HRESULT hr = getSettings() -> get_RemoteAddresses( 
          &remoteAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(remoteAddrs, false);
  }

public:
  HRESULT putRemoteAddresses( 
            /* [in] */ BSTR remoteAddrs)
        
  {
    HRESULT hr = getSettings() -> put_RemoteAddresses( 
          remoteAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getEnabled( 
            /* [retval][out] */ VARIANT_BOOL *enabled)
  {
    HRESULT hr = getSettings() -> get_Enabled( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getEnabled()
  {
    VARIANT_BOOL enabled;
    HRESULT hr = getSettings() -> get_Enabled( 
        &enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(enabled);
  }

public:
  HRESULT putEnabled( 
            /* [in] */ VARIANT_BOOL enabled)
        
  {
    HRESULT hr = getSettings() -> put_Enabled( 
          enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putEnabled( 
            /* [in] */ bool enabled)
        
  {
    HRESULT hr = getSettings() -> put_Enabled( 
          toVariantBool(enabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  virtual void display(HWND hwnd=NULL)
  {
    NetFwName name;
    _tprintf(_T("<NetFwRemoteAdminSettings>\n"));

    NET_FW_IP_VERSION v= getIpVersion();
     _tprintf(_T("<IPVersion>%s</IPVersion>\n"), name.toString(v));
    NET_FW_SCOPE scope = getScope();
     _tprintf(_T("<Scope>%s</Scope>\n"), name.toString(scope));
    _tprintf(_T("<RemoteAddresses>%s</RemoteAddresses>\n"), (const TCHAR*)getRemoteAddresses());
    _tprintf(_T("<Enabled>%s</Enabled>\n"), name.toString(getEnabled()) );

    _tprintf(_T("</NetFwRemoteAdminSettings>\n"));
  }

public:
  virtual void write(Writer& writer)
  {
    NetFwName name;
    writer.write(L"<NetFwRemoteAdminSettings>\n");

    NET_FW_IP_VERSION v= getIpVersion();
     writer.write(L"<IPVersion>%s</IPVersion>\n", 
      (const wchar_t*)_bstr_t(name.toString(v)) );
    NET_FW_SCOPE scope = getScope();
     writer.write(L"<Scope>%s</Scope>\n", 
      (const wchar_t*)_bstr_t(name.toString(scope)) );
    writer.write(L"<RemoteAddresses>%s</RemoteAddresses>\n", 
      (const wchar_t*)_bstr_t(getRemoteAddresses()) );
    writer.write(L"<Enabled>%s</Enabled>\n", 
      (const wchar_t*)_bstr_t(name.toString(getEnabled()) ) );

    writer.write(L"</NetFwRemoteAdminSettings>\n");
  }
};

}
