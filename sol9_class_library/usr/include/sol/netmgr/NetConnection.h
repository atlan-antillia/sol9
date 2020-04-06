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
 *  NetConnection.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIUnknown.h>
#include <netcon.h>
#include <sol/netmgr/NetConnectionProperties.h>

namespace SOL {

class NetConnection : public ComIUnknown
{

public:
  NetConnection(INetConnection* pCon=NULL)
  :ComIUnknown(pCon)
  {

  }
  
private:
  INetConnection* getConnection()
  {
    return (INetConnection*) getIUnknown();
  }


public:
  operator INetConnection*() 
  {
    return (INetConnection*) getIUnknown();
  }

public:
  HRESULT connect()
  {
    HRESULT hr = getConnection() -> Connect();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  HRESULT disconnect()
  {
    HRESULT hr = getConnection() -> Disconnect();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  HRESULT remove()
  {
    HRESULT hr = getConnection() -> Delete();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  HRESULT duplicate( 
            /* [string][in] */ LPCWSTR pszwDuplicateName,
            /* [out] */ INetConnection **ppCon)
  {
    HRESULT hr = getConnection() -> Duplicate( 
      pszwDuplicateName,
      ppCon);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  HRESULT getProperties( 
            /* [out] */ NETCON_PROPERTIES **ppProps)
  {
    HRESULT hr = getConnection() -> GetProperties( 
      ppProps);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
  NETCON_PROPERTIES* getProperties() 
   {
    NETCON_PROPERTIES *pProps = NULL;
    HRESULT hr = getConnection() -> GetProperties( 
      &pProps);
    if (FAILED(hr)) {
      throw hr;
    }
    return pProps;
  }

  HRESULT getUiObjectClassId( 
            /* [ref][out] */ CLSID *pclsid)
  {
    HRESULT hr = getConnection() -> GetUiObjectClassId( 
      pclsid);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  CLSID getUiObjectClassId()
  {
    CLSID clsid;
    HRESULT hr = getConnection() -> GetUiObjectClassId( 
      &clsid);
    if (FAILED(hr)) {
      throw hr;
    }
    return clsid;
  }

  HRESULT rename( 
            /* [string][in] */ LPCWSTR pszwNewName)
  {
    HRESULT hr = getConnection() -> Rename( 
      pszwNewName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  virtual void display(HWND hwnd = NULL)
  {  
    NetConnectionProperties properties = getProperties();
    properties.display();
  }
         
};
    
}

