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
 *  NetFwAuthorizedApplication.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>


namespace SOL {

class NetFwAuthorizedApplication: public ComIDispatch {

public:
  NetFwAuthorizedApplication(INetFwAuthorizedApplication* pApp=NULL)
    :ComIDispatch(pApp)
  {
    if (pApp == NULL) {
      createInstance();
    }
  }

public:
  HRESULT createInstance()
  {
    INetFwAuthorizedApplication* pApp = NULL;

    HRESULT hr = CoCreateInstance(__uuidof(::NetFwAuthorizedApplication), 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        __uuidof(INetFwAuthorizedApplication), 
        (void**)&pApp);
    if (SUCCEEDED(hr)) {
      set(pApp);
    } else {
      throw hr;
    }
    return hr;
  }

private:
  INetFwAuthorizedApplication* getApplication()
  {
    return (INetFwAuthorizedApplication*) getIDispatch();
  }

    
public:
  //2012/09/21
  operator INetFwAuthorizedApplication*()
  {
    return (INetFwAuthorizedApplication*) getIDispatch();
  }

public:
  HRESULT getName( 
            /* [retval][out] */ BSTR *name)
  {
    HRESULT hr = getApplication() -> get_Name( 
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
    HRESULT hr = getApplication() -> get_Name( 
          &name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }

public:
  HRESULT putName( 
            /* [in] */ BSTR name)
  {
    HRESULT hr = getApplication() -> put_Name( 
          name);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getProcessImageFileName( 
            /* [retval][out] */ BSTR *imageFileName)
  {
    HRESULT hr = getApplication() -> get_ProcessImageFileName( 
          imageFileName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  _bstr_t getProcessImageFileName( 
            /* [retval][out] */ )
  {
    BSTR imageFileName = NULL;
    HRESULT hr = getApplication() -> get_ProcessImageFileName( 
          &imageFileName);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(imageFileName, false);
  }

public:
  HRESULT putProcessImageFileName( 
            /* [in] */ BSTR imageFileName)
  {
    HRESULT hr = getApplication() -> put_ProcessImageFileName( 
          imageFileName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getIpVersion( 
            /* [retval][out] */ NET_FW_IP_VERSION *ipVersion)
  {
    HRESULT hr = getApplication() -> get_IpVersion( 
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
    HRESULT hr = getApplication() -> get_IpVersion( 
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
    HRESULT hr = getApplication() -> put_IpVersion( 
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
    HRESULT hr = getApplication() -> get_Scope( 
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
    HRESULT hr = getApplication() -> get_Scope( 
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
    HRESULT hr = getApplication() -> put_Scope( 
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
    HRESULT hr = getApplication() -> get_RemoteAddresses( 
          remoteAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  _bstr_t getRemoteAddresses( 
            /* [retval][out] */ )
  {
    BSTR remoteAddrs = NULL;
    HRESULT hr = getApplication() -> get_RemoteAddresses( 
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
    HRESULT hr = getApplication() -> put_RemoteAddresses( 
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
    HRESULT hr = getApplication() -> get_Enabled( 
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
    HRESULT hr = getApplication() -> get_Enabled( 
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
    HRESULT hr = getApplication() -> put_Enabled( 
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
    HRESULT hr = getApplication() -> put_Enabled( 
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
    _tprintf(_T("<AuthorizedApplication>\n"));
    _tprintf(_T("<Name>%s</Name>\n"), (const TCHAR*)getName() );
 
    _tprintf(_T("<ProcessImageFileName>%s</ProcessImageFileName>\n"), (const TCHAR*)getProcessImageFileName() );
        
    NET_FW_IP_VERSION v = getIpVersion();
   
    _tprintf(_T("<IpVersion>%s</IpVersion>\n"), (const TCHAR*) name.toString(v) );
   
    NET_FW_SCOPE scope = getScope();
    _tprintf(_T("<Scope>%s</Scope>\n"), (const TCHAR*) name.toString(scope) );        

    _tprintf(_T("<RemoteAddresses>%s</RemoteAddresses>\n"), (const TCHAR*)getRemoteAddresses() );
 
    _tprintf(_T("<Enabled>%s</Enabled>\n"), (const TCHAR*)name.toString(getEnabled()) );
 
    _tprintf(_T("</AuthorizedApplication>\n"));
  }

public:
  virtual void write(Writer& writer)
  {
    NetFwName name;
    writer.write(L"<AuthorizedApplication>\n");
    writer.write(L"<Name>%s</Name>\n", 
      (const wchar_t*)_bstr_t(getName()) );
 
    writer.write(L"<ProcessImageFileName>%s</ProcessImageFileName>\n", 
      (const wchar_t*)_bstr_t(getProcessImageFileName()) );
        
    NET_FW_IP_VERSION v = getIpVersion();
    writer.write(L"<IpVersion>%s</IpVersion>\n", 
      (const wchar_t*)_bstr_t(name.toString(v)) );
   
    NET_FW_SCOPE scope = getScope();
    writer.write(L"<Scope>%s</Scope>\n", 
      (const wchar_t*)_bstr_t(name.toString(scope)) );        

    writer.write(L"<RemoteAddresses>%s</RemoteAddresses>\n", 
      (const wchar_t*)_bstr_t(getRemoteAddresses()) );
 
    writer.write(L"<Enabled>%s</Enabled>\n", 
      (const wchar_t*)_bstr_t(name.toString(getEnabled()) ) );
 
    writer.write(L"</AuthorizedApplication>\n");
  }
};
    
}
