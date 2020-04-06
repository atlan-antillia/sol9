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
 *  EnumNetConnection.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>
#include <sol/Writer.h>

/*
NetFwMgr mgr;
NetFwPolicy  policy = mgr.getLocalPolicy();
NetFwProfile profile = policy.getCurrentProfile();
NetFwOpenPorts openPorts = profile.getGloballyOpenPorts();

NetFwOpenPort tcpOpenPort = openPorts.item(8080, NET_FW_IP_PROTOCOL_TCP);
NetFwOpenPort udpOpenPort = openPorts.item(6400, NET_FW_IP_PROTOCOL_UDP);

*/

namespace SOL {

class NetFwOpenPort: public ComIDispatch {
    
public:
  NetFwOpenPort(INetFwOpenPort* pPort=NULL)
    :ComIDispatch(pPort)
  {
    if (pPort == NULL) {
      createInstance();
    }
  }

public:
  HRESULT createInstance()
  {
    INetFwOpenPort* pPort = NULL;
    HRESULT hr = CoCreateInstance(   
        __uuidof(::NetFwOpenPort),   
        NULL,   
        CLSCTX_INPROC_SERVER,   
        __uuidof(INetFwOpenPort),   
        (void**)&pPort);   
    if (SUCCEEDED(hr)) {
      set(pPort);
    } else {
      throw hr;
    }
    return hr;
  }

private:
  INetFwOpenPort* getPortPtr()
  {
    return (INetFwOpenPort*) getIDispatch();
  }

public:
  operator INetFwOpenPort*()
  {
    return (INetFwOpenPort*) getIDispatch();
  }

public:
  HRESULT getName( 
            /* [retval][out] */ BSTR *name)
  {
    HRESULT hr = getPortPtr() -> get_Name( 
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
    HRESULT hr = getPortPtr() -> get_Name( 
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
    HRESULT hr = getPortPtr() -> put_Name( 
        name);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:       
  HRESULT getIpVersion( 
            /* [retval][out] */ NET_FW_IP_VERSION *ipVersion)
  {
    HRESULT hr = getPortPtr() -> get_IpVersion( 
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
    HRESULT hr = getPortPtr() -> get_IpVersion( 
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
    HRESULT hr = getPortPtr() -> put_IpVersion( 
        ipVersion);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getProtocol( 
            /* [retval][out] */ NET_FW_IP_PROTOCOL *ipProtocol)
  {
    HRESULT hr = getPortPtr() -> get_Protocol( 
        ipProtocol);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  NET_FW_IP_PROTOCOL getProtocol()
  {
    NET_FW_IP_PROTOCOL ipProtocol;
    HRESULT hr = getPortPtr() -> get_Protocol( 
        &ipProtocol);
    if (FAILED(hr)) {
      throw hr;
    }
    return ipProtocol;
  }


public:
  HRESULT putProtocol( 
            /* [in] */ NET_FW_IP_PROTOCOL ipProtocol)
  {
    HRESULT hr = getPortPtr() -> put_Protocol( 
        ipProtocol);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getPort( 
            /* [retval][out] */ LONG *portNumber)
  {
    HRESULT hr = getPortPtr() -> get_Port( 
          portNumber);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  LONG getPort()
  {
    LONG portNumber = 0;
    HRESULT hr = getPortPtr() -> get_Port( 
          &portNumber);
    if (FAILED(hr)) {
      throw hr;
    }
    return portNumber;
  }

public:        
  HRESULT putPort( 
            /* [in] */ LONG portNumber)
  {
    HRESULT hr = getPortPtr() -> put_Port( 
          portNumber);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getScope( 
            /* [retval][out] */ NET_FW_SCOPE *scope)
  {
    HRESULT hr = getPortPtr() -> get_Scope( 
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
    HRESULT hr = getPortPtr() -> get_Scope( 
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
    HRESULT hr = getPortPtr() -> put_Scope( 
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
    HRESULT hr = getPortPtr() -> get_RemoteAddresses( 
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
    HRESULT hr = getPortPtr() -> get_RemoteAddresses( 
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
    HRESULT hr = getPortPtr() -> put_RemoteAddresses( 
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
    HRESULT hr = getPortPtr() -> get_Enabled( 
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
    HRESULT hr = getPortPtr() -> get_Enabled( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }


public:        
  HRESULT getBuiltIn( 
            /* [retval][out] */ VARIANT_BOOL *builtIn)
  {
    HRESULT hr = getPortPtr() -> get_BuiltIn( 
        builtIn);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        
    
public:        
  bool getBuiltIn()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getPortPtr() -> get_BuiltIn( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }      

public:
  virtual void display(HWND hwnd=NULL)
  {
    NetFwName name;
    _tprintf(_T("<OpenPort>\n"));

    _tprintf(__T("<Name>%s</Name>\n"), (const TCHAR*)getName() );

    NET_FW_IP_VERSION version = getIpVersion();
    _tprintf(__T("<IPVersion>%s</IPVersion>\n"), name.toString(version) );
 
    NET_FW_IP_PROTOCOL protocol = getProtocol();
    _tprintf(__T("<Protocol>%s</Protocol>\n"), name.toString(protocol) );
  
    _tprintf(__T("<Port>%d</Port>\n"), getPort() );

    NET_FW_SCOPE scope = getScope();
    _tprintf(__T("<Scope>%s</Scope>\n"), name.toString(scope) );

    _tprintf(__T("<RemoteAddresses>%s</RemoteAddresses>\n"), (const TCHAR*)getRemoteAddresses() );

    _tprintf(__T("<Enabled>%s</Enabled>\n"), name.toString(getEnabled()) );
    _tprintf(__T("<BuiltIn>%s</BuiltIn>\n"), name.toString(getBuiltIn()) );

    _tprintf(_T("</OpenPort>\n"));
  }

public:
  virtual void write(Writer& writer)
  {
    NetFwName name;
    writer.write(L"<OpenPort>\n");

    writer.write(L"<Name>%s</Name>\n", 
      (const wchar_t*)_bstr_t(getName() ) );

    NET_FW_IP_VERSION version = getIpVersion();
    writer.write(L"<IPVersion>%s</IPVersion>\n", 
      (const wchar_t*)_bstr_t(name.toString(version) ) );
 
    NET_FW_IP_PROTOCOL protocol = getProtocol();
    writer.write(L"<Protocol>%s</Protocol>\n", 
      (const wchar_t*)_bstr_t(name.toString(protocol) ) );
  
    writer.write(L"<Port>%d</Port>\n", getPort() );

    NET_FW_SCOPE scope = getScope();
    writer.write(L"<Scope>%s</Scope>\n", 
      (const wchar_t*)_bstr_t(name.toString(scope) ) );

    writer.write(L"<RemoteAddresses>%s</RemoteAddresses>\n", 
      (const wchar_t*)_bstr_t(getRemoteAddresses() ) );

    writer.write(L"<Enabled>%s</Enabled>\n", 
      (const wchar_t*)_bstr_t(name.toString(getEnabled()) ) );
    writer.write(L"<BuiltIn>%s</BuiltIn>\n", 
      (const wchar_t*)_bstr_t(name.toString(getBuiltIn()) ) );

    writer.write(L"</OpenPort>\n");
  }

};

}
