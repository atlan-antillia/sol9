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
 *  Network.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol\com\ComIDispatch.h>
#include <netlistmgr.h>
#include <sol\FileTime.h>
#include <sol\ArgT.h>
#include <sol\ArgListT.h>
#include <sol\StringBufferT.h>


namespace SOL {

class Network: public ComIDispatch {
public:
  Network(INetwork* pNetwork=NULL)
    :ComIDispatch(pNetwork)
  {
  }

private:
  INetwork* getNetwork()
  {
    return (INetwork*) getIDispatch();
  }

public:
  HRESULT getName( 
            /* [retval][string][out] */ BSTR *pszNetworkName)
  {
    HRESULT hr = getNetwork() -> GetName( 
        pszNetworkName);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  _bstr_t getName()
  {
    BSTR name = NULL;
    HRESULT hr = getNetwork() -> GetName( 
        &name);

    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }

  HRESULT setName( 
            /* [string][in] */ BSTR szNetworkNewName)
  {
    HRESULT hr = getNetwork() -> SetName( 
        szNetworkNewName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  HRESULT getDescription( 
            /* [retval][string][out] */ BSTR *pszDescription)
  {
    HRESULT hr = getNetwork() -> GetDescription( 
        pszDescription);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  _bstr_t getDescription()
  {
    BSTR description = NULL;
    HRESULT hr = getNetwork() -> GetDescription( 
        &description);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(description, false);
  }

  HRESULT setDescription( 
            /* [string][in] */ BSTR szDescription)
  {
    HRESULT hr = getNetwork() -> SetDescription( 
        szDescription);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT getNetworkId( 
            /* [retval][out] */ GUID *pgdGuidNetworkId)
  {
    HRESULT hr = getNetwork() -> GetNetworkId( 
      pgdGuidNetworkId);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  GUID getNetworkId()
  {
    GUID id;
    HRESULT hr = getNetwork() -> GetNetworkId( 
      &id);
    if (FAILED(hr)) {
      throw hr;
    }
    return id;
  }

  HRESULT getDomainType( 
            /* [retval][out] */ NLM_DOMAIN_TYPE *pNetworkType)
  {
    HRESULT hr = getNetwork() -> GetDomainType( 
        pNetworkType);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  NLM_DOMAIN_TYPE getDomainType()
  {
    NLM_DOMAIN_TYPE type;
    HRESULT hr = getNetwork() -> GetDomainType( 
        &type);

    if (FAILED(hr)) {
      throw hr;
    }
    return type;
  }

  HRESULT getNetworkConnections( 
            /* [retval][out] */ IEnumNetworkConnections **ppEnumNetworkConnection)
  {
    HRESULT hr = getNetwork() -> GetNetworkConnections( 
        ppEnumNetworkConnection);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  IEnumNetworkConnections* getNetworkConnections()
  {
    IEnumNetworkConnections* pConnections = NULL;
    HRESULT hr = getNetwork() -> GetNetworkConnections( 
        &pConnections);

    if (FAILED(hr)) {
      throw hr;
    }
    return pConnections;
  }

  HRESULT getTimeCreatedAndConnected( 
            /* [out] */ DWORD *pdwLowDateTimeCreated,
            /* [out] */ DWORD *pdwHighDateTimeCreated,
            /* [out] */ DWORD *pdwLowDateTimeConnected,
            /* [out] */ DWORD *pdwHighDateTimeConnected)
  {
    HRESULT hr = getNetwork() -> GetTimeCreatedAndConnected( 
        pdwLowDateTimeCreated,
        pdwHighDateTimeCreated,
        pdwLowDateTimeConnected,
        pdwHighDateTimeConnected);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  FILETIME getCreatedTime()
  {
    FILETIME time;
    DWORD dwLowDateTimeCreated = 0;
    DWORD dwHighDateTimeCreated = 0;
    DWORD dwLowDateTimeConnected = 0;
    DWORD dwHighDateTimeConnected = 0;

    HRESULT hr = getNetwork() -> GetTimeCreatedAndConnected( 
        &dwLowDateTimeCreated,
        &dwHighDateTimeCreated,
        &dwLowDateTimeConnected,
        &dwHighDateTimeConnected);

    if (FAILED(hr)) {
      throw hr;
    }

    time.dwLowDateTime = dwLowDateTimeCreated;    
    time.dwHighDateTime = dwHighDateTimeCreated;
    return time;
  }

  FILETIME getConnectedTime()
  {
    FILETIME time;
    DWORD dwLowDateTimeCreated = 0;
    DWORD dwHighDateTimeCreated = 0;
    DWORD dwLowDateTimeConnected = 0;
    DWORD dwHighDateTimeConnected = 0;

    HRESULT hr = getNetwork() -> GetTimeCreatedAndConnected( 
        &dwLowDateTimeCreated,
        &dwHighDateTimeCreated,
        &dwLowDateTimeConnected,
        &dwHighDateTimeConnected);

    if (FAILED(hr)) {
      throw hr;
    }
    time.dwLowDateTime = dwLowDateTimeConnected;    
    time.dwHighDateTime = dwHighDateTimeConnected;
    return time;
  }

  HRESULT getIsConnectedToInternet( 
            /* [retval][out] */ VARIANT_BOOL *pbIsConnected)
  {
    HRESULT hr = getNetwork() -> get_IsConnectedToInternet( 
        pbIsConnected);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  bool getIsConnectedToInternet()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getNetwork() -> get_IsConnectedToInternet( 
        &vbool);

    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

  HRESULT getIsConnected( 
            /* [retval][out] */ VARIANT_BOOL *pbIsConnected)
  {
    HRESULT hr = getNetwork() -> get_IsConnected( 
        pbIsConnected);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  bool getIsConnected()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getNetwork() -> get_IsConnected( 
        &vbool);

    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

  HRESULT getConnectivity( 
            /* [retval][out] */ NLM_CONNECTIVITY *pConnectivity)
  {
    HRESULT hr = getNetwork() -> GetConnectivity( 
        pConnectivity);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  NLM_CONNECTIVITY getConnectivity()
  {
    NLM_CONNECTIVITY connectivity;
    HRESULT hr = getNetwork() -> GetConnectivity( 
        &connectivity);
    if (FAILED(hr)) {
      throw hr;
    }
    return connectivity;
  }

  HRESULT getCategory( 
            /* [retval][out] */ NLM_NETWORK_CATEGORY *pCategory)
  {
    HRESULT hr = getNetwork() -> GetCategory( 
        pCategory);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  NLM_NETWORK_CATEGORY getCategory()
  {
    NLM_NETWORK_CATEGORY category;
    HRESULT hr = getNetwork() -> GetCategory( 
        &category);

    if (FAILED(hr)) {
      throw hr;
    }
    return category;
  }

  HRESULT setCategory( 
            /* [in] */ NLM_NETWORK_CATEGORY newCategory)
  {
    HRESULT hr = getNetwork() -> SetCategory( 
        newCategory);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  static const TCHAR* toString(NLM_DOMAIN_TYPE type)
  {
    ArgT<TCHAR> names[] = {
      {_T("NON_DOMAIN_NETWORK"), NLM_DOMAIN_TYPE_NON_DOMAIN_NETWORK},
      {_T("DOMAIN_NETWORK"), NLM_DOMAIN_TYPE_DOMAIN_NETWORK},
      {_T("DOMAIN_AUTHENTICATED"), NLM_DOMAIN_TYPE_DOMAIN_AUTHENTICATED}
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(type);
  }

public:
  static const TCHAR* toString(NLM_NETWORK_CATEGORY cat)
  {
    ArgT<TCHAR> names[] = {
      {_T("PUBLIC"), NLM_NETWORK_CATEGORY_PUBLIC},
      {_T("PRIVATE"), NLM_NETWORK_CATEGORY_PRIVATE},
      {_T("DOMAIN_AUTHENTICATED"), NLM_NETWORK_CATEGORY_DOMAIN_AUTHENTICATED} 
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(cat);
  }

public:
  static _bstr_t toString(NLM_CONNECTIVITY value)
  {
    ArgT<TCHAR> names[] = {
    {_T("DISCONNECTED"), NLM_CONNECTIVITY_DISCONNECTED},
    {_T("IPV4_NOTRAFFIC"), NLM_CONNECTIVITY_IPV4_NOTRAFFIC},
    {_T("IPV6_NOTRAFFIC"), NLM_CONNECTIVITY_IPV6_NOTRAFFIC},
    {_T("IPV4_SUBNET"), NLM_CONNECTIVITY_IPV4_SUBNET},
    {_T("IPV4_LOCALNETWORK"), NLM_CONNECTIVITY_IPV4_LOCALNETWORK},
    {_T("IPV4_INTERNET"), NLM_CONNECTIVITY_IPV4_INTERNET},
    {_T("IPV6_SUBNET"), NLM_CONNECTIVITY_IPV6_SUBNET},
    {_T("IPV6_LOCALNETWORK"), NLM_CONNECTIVITY_IPV6_LOCALNETWORK},
    {_T("IPV6_INTERNET"), NLM_CONNECTIVITY_IPV6_INTERNET},
    };

    StringBufferT<TCHAR> buffer;
    int n = 0;
    for (int i = 0; i<CountOf(names); i++) {
      if (value & names[i].value) {
        if (n > 0) {
          buffer.append(_T("|"));
        }
        buffer.append(names[i].name);
        n++;
      }
    }
    return _bstr_t((const TCHAR*)buffer);
  }


public:
    virtual void display(HWND hwnd=NULL)
  {
    _tprintf(_T("Name = %s\n"), (const TCHAR*)getName());
    _tprintf(_T("Description = %s\n"), (const TCHAR*)getDescription());
    _tprintf(_T("IsConnectedToInternet = %d\n"), getIsConnectedToInternet());
    _tprintf(_T("IsConnected = %d\n"), getIsConnected());
    
    FileTime createdTime(getCreatedTime(), FileTime::GMT);
    FileTime connectedTime(getConnectedTime(), FileTime::GMT);
    _tprintf(_T("CreatedTime = %s\n"), (const TCHAR*)createdTime.toString());
    _tprintf(_T("ConnectedTime = %s\n"), (const TCHAR*)connectedTime.toString());

    NLM_DOMAIN_TYPE type = getDomainType();
    _tprintf(_T("DomainType = %s\n"), (const TCHAR*)toString(type) );

    NLM_NETWORK_CATEGORY category = getCategory();
    _tprintf(_T("Category = %s\n"), (const TCHAR*)toString(category) );
    NLM_CONNECTIVITY connectivity = getConnectivity();
    _tprintf(_T("Connectivity = %s\n"), (const TCHAR*)toString(connectivity) );

    _tprintf(_T("\n"));

  }
};
    
}
