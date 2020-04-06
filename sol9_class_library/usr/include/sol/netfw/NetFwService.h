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
 *  NetFwService.h
 *
 *****************************************************************************/

//2012/09/14
//2017/01/29 Updated write method to use a try-catch block.

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>
#include <sol/Writer.h>

/*
NetFwMgr mgr;
NetFwPolicy  policy = mgr.getLocalPolicy();
NetFwProfile profile = policy.getCurrentProfile();
NetFwServices services = profile.getServices();

NetFwService service = services.item(NET_FW_SERVICE_FILE_AND_PRINT);
*/

namespace SOL {

class NetFwService: public ComIDispatch {

public:
  NetFwService(INetFwService* pService)
    :ComIDispatch(pService)
  {
  }

private:
  INetFwService* getService()
  {
    return (INetFwService*) getIDispatch();
  }

public:
  HRESULT getName( 
            /* [retval][out] */ BSTR *name)
  {
    HRESULT hr = getService() -> get_Name( 
        name);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getName()
  {
    BSTR name = NULL;
    HRESULT hr = getService() -> get_Name( 
        &name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }

public:
  HRESULT getType( 
            /* [retval][out] */ NET_FW_SERVICE_TYPE *type)
  {
    HRESULT hr = getService() -> get_Type( 
        type);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  NET_FW_SERVICE_TYPE getType()
  {
    NET_FW_SERVICE_TYPE type;
    HRESULT hr = getService() -> get_Type( 
        &type);
    if (FAILED(hr)) {
      throw hr;
    }
    return type;
  }

public:
  HRESULT getCustomized( 
            /* [retval][out] */ VARIANT_BOOL *customized)
  {
    HRESULT hr = getService() -> get_Customized( 
        customized);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  bool getCustomized()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getService() -> get_Customized( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT getIpVersion( 
            /* [retval][out] */ NET_FW_IP_VERSION *ipVersion)
  {
    HRESULT hr = getService() -> get_IpVersion( 
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
    HRESULT hr = getService() -> get_IpVersion( 
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
    HRESULT hr = getService() -> put_IpVersion( 
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
    HRESULT hr = getService() -> get_Scope( 
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
    HRESULT hr = getService() -> get_Scope( 
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
    HRESULT hr = getService() -> put_Scope( 
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
    HRESULT hr = getService() -> get_RemoteAddresses( 
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
    HRESULT hr = getService() -> get_RemoteAddresses( 
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
    HRESULT hr = getService() -> put_RemoteAddresses( 
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
    HRESULT hr = getService() -> get_Enabled( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  bool getEnabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getService() -> get_Enabled( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putEnabled( 
            /* [in] */ VARIANT_BOOL enabled)
  {
    HRESULT hr = getService() -> put_Enabled( 
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
    HRESULT hr = getService() -> put_Enabled( 
        toVariantBool(enabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getGloballyOpenPorts( 
            /* [retval][out] */ INetFwOpenPorts **openPorts)
  {
    HRESULT hr = getService() -> get_GloballyOpenPorts( 
        openPorts);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwOpenPorts* getGloballyOpenPorts()
  {
    INetFwOpenPorts* openPorts = NULL;
    HRESULT hr = getService() -> get_GloballyOpenPorts( 
        &openPorts);
    if (FAILED(hr)) {
      throw hr;
    }
    return openPorts;
  }

public:
  virtual void display(HWND hwnd=NULL)
  {
    NetFwName name;
    _tprintf(_T("<Service>\n"));

    _tprintf(_T("<Name>%s</Name>\n"), (const TCHAR*) getName() );

    NET_FW_SERVICE_TYPE type = getType();
    _tprintf(_T("<Type>%s</Type>\n"), (const TCHAR*) name.toString(type) );

    _tprintf(_T("<Customized>%s</Customized>\n"), name.toString(getCustomized()) );

    NET_FW_IP_VERSION version = getIpVersion();
    _tprintf(_T("<IPVersion>%s</IPVersion>\n"), (const TCHAR*) name.toString(version) );

    NET_FW_SCOPE scope = getScope();
    _tprintf(_T("<Scope>%s</Scope>\n"), (const TCHAR*) name.toString(scope) );

    _tprintf(_T("<RemoteAddresses>%s</RemoteAddresses>\n"), (const TCHAR*) getRemoteAddresses() );

    _tprintf(_T("<Enabled>%s</Enabled>\n"), name.toString(getEnabled()) );

    NetFwOpenPorts openPorts = getGloballyOpenPorts();
    openPorts.display(hwnd);

    _tprintf(_T("</Service>\n"));

  }

public:
  virtual void write(Writer& writer)
  {
    NetFwName name;
    writer.write(L"<Service>\n");
    //2017/01/29 Added try catch block
    try {
      writer.write(L"<Name>%s</Name>\n", 
      (const wchar_t*)_bstr_t(getName() ) );

      NET_FW_SERVICE_TYPE type = getType();
      writer.write(L"<Type>%s</Type>\n", 
      (const wchar_t*)_bstr_t(name.toString(type) ) );

      writer.write(L"<Customized>%s</Customized>\n", 
      (const wchar_t*)_bstr_t(name.toString(getCustomized()) ) );

      NET_FW_IP_VERSION version = getIpVersion();
      writer.write(L"<IPVersion>%s</IPVersion>\n", 
      (const wchar_t*)_bstr_t(name.toString(version) ) );

      NET_FW_SCOPE scope = getScope();
      writer.write(L"<Scope>%s</Scope>\n", 
      (const wchar_t*)_bstr_t(name.toString(scope) ) );

      writer.write(L"<RemoteAddresses>%s</RemoteAddresses>\n", 
      (const wchar_t*)_bstr_t(getRemoteAddresses() ) );

      writer.write(L"<Enabled>%s</Enabled>\n", 
      (const wchar_t*)_bstr_t(name.toString(getEnabled()) ) );

      NetFwOpenPorts openPorts = getGloballyOpenPorts();
      openPorts.write(writer);
    } catch (...) {
      
    }
    writer.write(L"</Service>\n");
  }

};
    
}
