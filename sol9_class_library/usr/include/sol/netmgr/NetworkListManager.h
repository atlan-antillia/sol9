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
 *  NetworkListManager.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol\com\ComIDispatch.h>
#include <netlistmgr.h>

namespace SOL {

class NetworkListManager: public ComIDispatch {

public:
  NetworkListManager()
  :ComIDispatch()
  {
    createInstance();
  }
    

public:
  HRESULT createInstance()
  {
    INetworkListManager* pManager;
    
    HRESULT hr = CoCreateInstance(CLSID_NetworkListManager, NULL, 
              CLSCTX_ALL, __uuidof(INetworkListManager), 
        (LPVOID*)&pManager);
    if (SUCCEEDED(hr)) {
      set(pManager);
    } else {
      throw hr;
    }
    return hr;
  }

private:
  INetworkListManager* getManager()
  {
    return (INetworkListManager*) getIDispatch(); 
  }

public:
/*
LM_ENUM_NETWORK can take the following value:
 NLM_ENUM_NETWORK_CONNECTED
 NLM_ENUM_NETWORK_DISCONNECTED
 NLM_ENUM_NETWORK_ALL
*/
  HRESULT getNetworks( 
            /* [in] */ NLM_ENUM_NETWORK flags,
            /* [retval][out] */ IEnumNetworks **ppEnumNetwork)
  {
    HRESULT hr = getManager() -> GetNetworks( 
        flags,
        ppEnumNetwork);

    if (FAILED(hr)) {
      throw hr;  
    }
    return hr;
  }
        

  IEnumNetworks* getNetworks( 
            /* [in] */ NLM_ENUM_NETWORK flags=NLM_ENUM_NETWORK_ALL)

  {
    IEnumNetworks *pEnumNetwork = NULL;
  
    HRESULT hr = getManager() -> GetNetworks( 
        flags,
        &pEnumNetwork);

    if (FAILED(hr)) {
      throw hr;  
    }
    return pEnumNetwork;
  }
        
  HRESULT getNetwork( 
            /* [in] */ GUID gdNetworkId,
            /* [retval][out] */ INetwork **ppNetwork)
  {
    HRESULT hr = getManager() -> GetNetwork( 
      gdNetworkId,
      ppNetwork);

    if (FAILED(hr)) {
      throw hr;  
    }
    return hr;
  }
        
  INetwork* getNetwork( 
            /* [in] */ GUID gdNetworkId)
  {
    INetwork* pNetwork = NULL;
 
    HRESULT hr = getManager() -> GetNetwork( 
      gdNetworkId,
      &pNetwork);

    if (FAILED(hr)) {
      throw hr;  
    }
    return pNetwork;
  }

  HRESULT getNetworkConnections( 
            /* [retval][out] */ IEnumNetworkConnections **ppEnum)
  {
    HRESULT hr = getManager() -> GetNetworkConnections( 
      ppEnum);

    if (FAILED(hr)) {
      throw hr;  
    }
    return hr;
  }
        
  IEnumNetworkConnections* getNetworkConnections()
  {
    IEnumNetworkConnections *pEnum = NULL;
    HRESULT hr = getManager() -> GetNetworkConnections( 
        &pEnum);

    if (FAILED(hr)) {
      throw hr;  
    }
    return pEnum;
  }

  HRESULT getNetworkConnection( 
            /* [in] */ GUID gdNetworkConnectionId,
            /* [retval][out] */ INetworkConnection **ppNetworkConnection)
  {
    HRESULT hr = getManager() -> GetNetworkConnection( 
        gdNetworkConnectionId,
        ppNetworkConnection);

    if (FAILED(hr)) {
      throw hr;  
    }
    return hr;
  }

  INetworkConnection* getNetworkConnection( 
            /* [in] */ GUID gdNetworkConnectionId)
  {
    INetworkConnection *pNetworkConnection = NULL;

    HRESULT hr = getManager() -> GetNetworkConnection( 
      gdNetworkConnectionId,
      &pNetworkConnection);

    if (FAILED(hr)) {
      throw hr;  
    }
    return pNetworkConnection;
  }
        

  HRESULT getIsConnectedToInternet( 
            /* [retval][out] */ VARIANT_BOOL *pbIsConnected)
  {
    HRESULT hr = getManager() -> get_IsConnectedToInternet( 
      pbIsConnected);

    if (FAILED(hr)) {
      throw hr;  
    }
    return hr;
  }
        
  bool getIsConnectedToInternet()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getManager() -> get_IsConnectedToInternet(&vbool);
    if (FAILED(hr)) {
      throw hr;  
    }
    return toBool(vbool);
  }

  HRESULT getIsConnected( 
            /* [retval][out] */ VARIANT_BOOL *pbIsConnected)
  {
    HRESULT hr = getManager() -> get_IsConnected( 
      pbIsConnected);

    if (FAILED(hr)) {
      throw hr;  
    }
    return hr;
  }
        
  bool getIsConnected()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getManager() -> get_IsConnected(&vbool);
    if (FAILED(hr)) {
      throw hr;  
    }
    return toBool(vbool);
  }
        

  HRESULT getConnectivity( 
            /* [retval][out] */ NLM_CONNECTIVITY *pConnectivity)
  {
    HRESULT hr = getManager() -> GetConnectivity( 
      pConnectivity);

    if (FAILED(hr)) {
      throw hr;  
    }
    return hr;
  }
        
  NLM_CONNECTIVITY getConnectivity()
  {
    NLM_CONNECTIVITY connectivity;

    HRESULT hr = getManager() -> GetConnectivity(&connectivity);
    if (FAILED(hr)) {
      throw hr;  
    }
    return connectivity;
  }
    

};

}

