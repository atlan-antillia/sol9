/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  UPnPDeviceFinder.h
 *
 *****************************************************************************/

// SOL9
// 2009/12/02

#pragma once

#include <sol/upnp/UPnPObject.h>
#include <sol/upnp/UPnPDevices.h>

namespace SOL {

class UPnPDeviceFinder :public UPnPObject {


public:
  /**
   * Constructor
   */
  UPnPDeviceFinder()
  :UPnPObject(NULL) 
  {
    IUPnPDeviceFinder *pDeviceFinder = NULL;

    HRESULT  hr = CoCreateInstance(CLSID_UPnPDeviceFinder, 
                      NULL,
                      CLSCTX_INPROC_SERVER,
                      IID_IUPnPDeviceFinder,
                      (void **) &pDeviceFinder);
  
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    } else {
      set(pDeviceFinder);
    }
  }

public:
  /**
   * Destructor
   */
  ~UPnPDeviceFinder()
  {
  }

public:
  IUPnPDeviceFinder* getFinder()
  {
    return (IUPnPDeviceFinder*)getIDispatch();
  }
  
public:
  /**
   * Find a set of devices specified by typeURI, and return it to foundDevices.
   */
  IUPnPDevices* find(__in const wchar_t* typeURI) 
  {
    IUPnPDevices* pFoundDevices = NULL;
    HRESULT hr = E_FAIL;
    if (FAILED(hr = find(typeURI, &pFoundDevices))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pFoundDevices;
   }

public:
  /**
   * Find a set of devices specified by typeURI, and return it to foundDevices.
   */
  HRESULT find(__in const wchar_t* typeURI, __out UPnPDevices& foundDevices) 
  {
    IUPnPDevices* pFoundDevices = NULL;
    HRESULT hr = find(typeURI, &pFoundDevices);
    if (SUCCEEDED(hr)) {
      foundDevices.set(pFoundDevices);
    }
    return hr;
   }


public:
  /**
   * Call IUPnPDeviceFinder::FindByType
   */
  HRESULT find(__in const wchar_t* typeURI, __out IUPnPDevices** ppFoundDevices) 
  {
    HRESULT hr = E_FAIL;
    
    if (typeURI && ppFoundDevices) {  
      BSTR uri = SysAllocString(typeURI);
      *ppFoundDevices = NULL;
      if (uri) {
        IUPnPDeviceFinder *pDeviceFinder = getFinder();
        hr = pDeviceFinder->FindByType(uri, 0, ppFoundDevices);
        SysFreeString(uri);
      }
    }
    return hr;
   }
};

}
