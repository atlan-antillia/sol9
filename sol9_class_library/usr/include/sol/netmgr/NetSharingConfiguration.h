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
 *  NetSharingConfiguration.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netcon.h>

namespace SOL {

class NetSharingConfiguration : public ComIDispatch {

public:
  NetSharingConfiguration(INetSharingConfiguration* pConfig=NULL)
    :ComIDispatch(pConfig)
  {
  }

private:
  INetSharingConfiguration* getConfig()
  {
    return (INetSharingConfiguration*) getIDispatch();  
  }
  `

public:
  HRESUL getSharingEnabled( 
            /* [retval][out] */ VARIANT_BOOL *pbEnabled)
  {
    HRESULT hr = getConfig() -> get_SharingEnabledpbEnabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  
public:
  bool getSharingEnabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getConfig() -> get_SharingEnabled(&vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }


  HRESULT getSharingConnectionType( 
            /* [retval][out] */ SHARINGCONNECTIONTYPE *pType)
  {
    HRESULT hr = getConfig() -> get_SharingConnectionType(pType)
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

  SHARINGCONNECTIONTYPE getSharingConnectionType()
  {
    SHARINGCONNECTIONTYPE type;
    HRESULT hr = getConfig() -> get_SharingConnectionType(&type)
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

  HRESULT disableSharing()
  {
    HRESULT hr = getConfig() -> DisableSharing();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT enableSharing( 
            /* [in] */ SHARINGCONNECTIONTYPE Type)
  {
    HRESULT hr = getConfig() -> EnableSharing(Type);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT getInternetFirewallEnabled( 
            /* [retval][out] */ VARIANT_BOOL *pbEnabled)
  {
    HRESULT hr = getConfig() -> get_InternetFirewallEnabled(pbEnabled)
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  bool getInternetFirewallEnabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getConfig() -> get_InternetFirewallEnabled(&vbool)
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }
        
  HRESULT disableInternetFirewall()
  {
    HRESULT hr = getConfig() -> DisableInternetFirewall();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT enableInternetFirewall()
  {
    HRESULT hr = getConfig() ->  EnableInternetFirewall();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

  HRESULT getEnumPortMappings( 
            /* [in] */ SHARINGCONNECTION_ENUM_FLAGS Flags,
            /* [retval][out] */ INetSharingPortMappingCollection **ppColl)
  {
    HRESULT hr = getConfig() -> get_EnumPortMappings( 
            Flags,
            ppColl);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  INetSharingPortMappingCollection* getEnumPortMappings( 
            /* [in] */ SHARINGCONNECTION_ENUM_FLAGS Flags)
  {
    INetSharingPortMappingCollection* pColl = NULL;
    HRESULT hr = getConfig() -> get_EnumPortMappings( 
            Flags,
            &pColl);
    if (FAILED(hr)) {
      throw hr;
    }
    return pColl;
  }
        
  HRESULT addPortMapping( 
            /* [in] */ bstrName,
            /* [in] */ ucIPProtocol,
            /* [in] */ usExternalPort,
            /* [in] */ usInternalPort,
            /* [in] */ dwOptions,
            /* [in] */ bstrTargetNameOrIPAddress,
            /* [in] */ eTargetType,
            /* [retval][out] */ INetSharingPortMapping **ppMapping)
  {
    HRESULT hr = getConfig() -> AddPortMapping( 
            bstrName,
            ucIPProtocol,
            usExternalPort,
            usInternalPort,
            dwOptions,
            bstrTargetNameOrIPAddress,
            eTargetType,
            ppMapping);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
  INetSharingPortMapping* addPortMapping( 
            /* [in] */ bstrName,
            /* [in] */ ucIPProtocol,
            /* [in] */ usExternalPort,
            /* [in] */ usInternalPort,
            /* [in] */ dwOptions,
            /* [in] */ bstrTargetNameOrIPAddress,
            /* [in] */ eTargetType)
  {
    INetSharingPortMapping* pMapping = NULL;
    HRESULT hr = getConfig() -> AddPortMapping( 
            bstrName,
            ucIPProtocol,
            usExternalPort,
            usInternalPort,
            dwOptions,
            bstrTargetNameOrIPAddress,
            eTargetType,
            &pMapping);
    if (FAILED(hr)) {
      throw hr;
    }
    return pMapping;
  }

  HRESULT removePortMapping( 
            /* [in] */ INetSharingPortMapping *pMapping)        
  {
    HRESULT hr = getConfig() -> RemovePortMapping(pMapping);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
    
};

}
