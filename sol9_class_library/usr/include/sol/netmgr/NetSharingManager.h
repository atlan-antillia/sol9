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
 *  NetSharingManager.h
 *
 *****************************************************************************/

//2012/\08/29

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netcon.h>

namespace SOL {

class NetSharingManager : public ComIDispatch {
    
public:
  NetSharingManager()
  {
    createInstance(CLSID_NetSharingManager,
      IID_INetSharingManager, 
      CLSCTX_ALL);
  }

private:
  INetSharingManager* getManager()
  {
    return (INetSharingManager*)getIDispatch();
  }

public:
  operator INetSharingManager*() 
  {
    return (INetSharingManager*)getIDispatch();
  }

public:
  HRESULT getSharingInstalled( 
            /* [retval][out] */ VARIANT_BOOL *pbInstalled)
  {
    HRESULT hr = getManager() -> get_SharingInstalled( 
        pbInstalled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getSharingInstalled()
  {
    VARIANT_BOOL bInstalled = VARIANT_FALSE;
    HRESULT hr = getManager() -> get_SharingInstalled( 
        &bInstalled);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(bInstalled);
  }

public:
  HRESULT getEnumPublicConnections( 
            /* [in] */ SHARINGCONNECTION_ENUM_FLAGS Flags,
            /* [retval][out] */ INetSharingPublicConnectionCollection **ppColl)
  {
    HRESULT hr = getManager() -> get_EnumPublicConnections( 
          Flags,
          ppColl);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  INetSharingPublicConnectionCollection* getEnumPublicConnections( 
            /* [in] */ SHARINGCONNECTION_ENUM_FLAGS Flags=ICSSC_DEFAULT)
  {
    INetSharingPublicConnectionCollection* pColl= NULL;
    HRESULT hr = getManager() -> get_EnumPublicConnections( 
          Flags,
          &pColl);
    if (FAILED(hr)) {
      throw hr;
    }
    return pColl;
  }


public:  
  HRESULT getEnumPrivateConnections( 
    /* [in] */ SHARINGCONNECTION_ENUM_FLAGS Flags,
            /* [retval][out] */ INetSharingPrivateConnectionCollection **ppColl)
  {
    HRESULT hr = getManager() -> get_EnumPrivateConnections( 
        Flags,
        ppColl);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:  
  INetSharingPrivateConnectionCollection* getEnumPrivateConnections( 
    /* [in] */ SHARINGCONNECTION_ENUM_FLAGS Flags=ICSSC_DEFAULT)
  {
    INetSharingPrivateConnectionCollection* pColl = NULL;
    HRESULT hr = getManager() -> get_EnumPrivateConnections( 
        Flags,
        &pColl);

    if (FAILED(hr)) {
      throw hr;
    }
    return pColl;
  }

public:       
  HRESULT getINetSharingConfigurationForINetConnection( 
            /* [in] */ INetConnection *pNetConnection,
            /* [retval][out] */ INetSharingConfiguration **ppNetSharingConfiguration)
  {
    HRESULT hr = getManager() -> get_INetSharingConfigurationForINetConnection( 
          pNetConnection,
          ppNetSharingConfiguration);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:       
  INetSharingConfiguration* getINetSharingConfigurationForINetConnection( 
            /* [in] */ INetConnection *pNetConnection)
  {
    INetSharingConfiguration* pNetSharingConfiguration = NULL;
    HRESULT hr = getManager() -> get_INetSharingConfigurationForINetConnection( 
          pNetConnection,
          &pNetSharingConfiguration);
    if (FAILED(hr)) {
      throw hr;
    }
    return pNetSharingConfiguration;
  }

public:        
  HRESULT getEnumEveryConnection( 
            /* [retval][out] */ INetSharingEveryConnectionCollection **ppColl)
  {
    HRESULT hr = getManager() -> get_EnumEveryConnection( 
        ppColl);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  INetSharingEveryConnectionCollection* getEnumEveryConnection()
  {
    INetSharingEveryConnectionCollection* pColl = NULL;
    HRESULT hr = getManager() -> get_EnumEveryConnection( 
        &pColl);

    if (FAILED(hr)) {
      throw hr;
    }
    return pColl;
  }
  
public:
  HRESULT getNetConnectionProps( 
            /* [in] */ INetConnection *pNetConnection,
            /* [retval][out] */ INetConnectionProps **ppProps)
  {
    HRESULT hr = getManager() -> get_NetConnectionProps( 
          pNetConnection,
          ppProps);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  INetConnectionProps* getNetConnectionProps( 
            /* [in] */ INetConnection *pNetConnection)
   {
    INetConnectionProps *pProps = NULL;
    HRESULT hr = getManager() -> get_NetConnectionProps( 
          pNetConnection,
          &pProps);

    if (FAILED(hr)) {
      throw hr;
    }
    return pProps;
  }

};
    
}
