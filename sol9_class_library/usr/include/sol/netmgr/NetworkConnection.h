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
 *  NetworkConnection.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol\com\ComIDispatch.h>
#include <netlistmgr.h>

namespace SOL {


class NetworkConnection: public ComIDispatch {
    
public:
  NetworkConnection(INetworkConnection* pConnection=NULL)
    :ComIDispatch(pConnection)
  {
  }

private:
  INetworkConnection* getConnection()
  {
    return (INetworkConnection*) getIDispatch();
  }

public:
  HRESULT getNetwork( 
            /* [retval][out] */ INetwork **ppNetwork)
  {
    HRESULT hr = getConnection() -> GetNetwork( 
        ppNetwork);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  INetwork* getNetwork()
  {
    INetwork* pNetwork = NULL;
    HRESULT hr = getConnection() -> GetNetwork( 
        &pNetwork);
    if (FAILED(hr)) {
      throw hr;
    }
    return pNetwork;
  }


  HRESULT getIsConnectedToInternet( 
            /* [retval][out] */ VARIANT_BOOL *pbIsConnected)
  {
    HRESULT hr = getConnection() -> get_IsConnectedToInternet( 
        pbIsConnected);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  bool getIsConnectedToInternet()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getConnection() -> get_IsConnectedToInternet( 
        &vbool);

    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

  HRESULT getIsConnected( 
            /* [retval][out] */ VARIANT_BOOL *pbIsConnected)
  {
    HRESULT hr = getConnection() -> get_IsConnected( 
        pbIsConnected);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  bool getIsConnected()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getConnection() -> get_IsConnected( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

  HRESULT getConnectivity( 
            /* [retval][out] */ NLM_CONNECTIVITY *pConnectivity)
  {
    HRESULT hr = getConnection() -> GetConnectivity( 
        pConnectivity);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  NLM_CONNECTIVITY getConnectivity()
  {
    NLM_CONNECTIVITY connectivity;
    HRESULT hr = getConnection() -> GetConnectivity( 
        &connectivity);
    if (FAILED(hr)) {
      throw hr;
    }
    return connectivity;
  }

  HRESULT getConnectionId( 
            /* [retval][out] */ GUID *pgdConnectionId)
  {
    HRESULT hr = getConnection() -> GetConnectionId( 
        pgdConnectionId);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  GUID getConnectionId()
  {
    GUID id;
    HRESULT hr = getConnection() -> GetConnectionId( 
        &id);
    if (FAILED(hr)) {
      throw hr;
    }
    return id;
  }

  HRESULT getAdapterId( 
            /* [retval][out] */ GUID *pgdAdapterId)
  {
    HRESULT hr = getConnection() -> GetAdapterId( 
        pgdAdapterId);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  GUID getAdapterId()
  {
    GUID id;
    HRESULT hr = getConnection() -> GetAdapterId( 
        &id);
    if (FAILED(hr)) {
      throw hr;
    }
    return id;
  }

  HRESULT getDomainType( 
            /* [retval][out] */ NLM_DOMAIN_TYPE *pDomainType)
  {
    HRESULT hr = getConnection() -> GetDomainType( 
        pDomainType);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  NLM_DOMAIN_TYPE getDomainType()
  {
    NLM_DOMAIN_TYPE type;
    HRESULT hr = getConnection() -> GetDomainType( 
        &type);

    if (FAILED(hr)) {
      throw hr;
    }
    return type;
  }
    
};
    
}
