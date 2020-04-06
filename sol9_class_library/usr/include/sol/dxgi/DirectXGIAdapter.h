/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DirectXGIAdapter.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIObject.h>


namespace SOL {
  
class DirectXGIAdapter : public DirectXGIObject {
   

public:
  DirectXGIAdapter(IDXGIFactory* factory, __in UINT adapterIndex)
  :DirectXGIObject()
  {
    if (factory) {
      IDXGIAdapter* adapter = NULL;
      HRESULT hr = factory -> EnumAdapters( 
              adapterIndex,
              &adapter);
      if (SUCCEEDED(hr)) {
        set(adapter);
      } else {
        throw IException("Failed to EnumAdapters. HRESULT(0x%lx)", hr);
      }
    } else {
      throw IException("IDXGIFactory is NULL.");
    }
  }
#ifdef WIN10  
public:
  DirectXGIAdapter(IDXGIFactory3* factory3)
  :DirectXGIObject()
  {
    if (factory3) {
      IDXGIAdapter* adapter = NULL;
      
      HRESULT hr = factory3->EnumAdapters(0, &adapter);
      if (SUCCEEDED(hr)) {
        set(adapter);
      } else {
        throw IException("Failed to EnumAdapters. HRESULT(0x%lx)", hr);
      }
    } else {
      throw IException("IDXGIFactory4 is NULL.");
    }
  }
#endif
public:
  //Get an IDXGIAdapter from IDXGIDevice interface
  DirectXGIAdapter(IDXGIDevice* device)
  :DirectXGIObject()
  {
    IDXGIAdapter* adapter = NULL;
    HRESULT hr = device -> GetAdapter( 
              &adapter);
    if (SUCCEEDED(hr)) {
      set(adapter);
    } else {
      throw IException("Failed to GetAdapter. HRESULT(0x%lx)", hr);
    }
  }
  //Create a software IDXGIAdapter from IDXGIFactory interface. 
  DirectXGIAdapter(IDXGIFactory* factory, __in HMODULE module)
  :DirectXGIObject()
  {
    IDXGIAdapter* adapter = NULL;
    HRESULT hr = factory -> CreateSoftwareAdapter( 
              module,
              &adapter);
    if (SUCCEEDED(hr)) {
      set(adapter);
    } else {
      throw IException("Failed to CreateSoftwareAdapter. HRESULT(0x%lx)", hr);
    }
  }
    
  ~DirectXGIAdapter()
  {
  }
  
  operator IDXGIAdapter*()
  {
    return getAdapter();
  }
  
  IDXGIAdapter* getAdapter()
  {
    IDXGIAdapter* adapter = (IDXGIAdapter*)getIUnknown();
    if (adapter) {
      return adapter;
    } else {
      throw IException("IDXGIAdapter is NULL.");
    }
  }
  
  
  void enumOutputs( 
            __in UINT output,
            __out  IDXGIOutput **ppOutput)
  {
    IDXGIAdapter* adapter = getAdapter();
    HRESULT hr = adapter -> EnumOutputs( 
              output,
              ppOutput);
    if (FAILED(hr)) {
      throw IException("Failed to EnumOutputs. HRESULT(0x%lx)", hr);
    }
  }
  
  void getDesc( 
            __out  DXGI_ADAPTER_DESC *pDesc)
  {
    IDXGIAdapter* adapter = getAdapter();
    HRESULT hr = adapter -> GetDesc( 
            pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
        
  void checkInterfaceSupport( 
            __in  REFGUID interfaceName,
            __out  LARGE_INTEGER *pUMDVersion)
  {
    IDXGIAdapter* adapter = getAdapter();
    HRESULT hr = adapter -> CheckInterfaceSupport( 
              interfaceName,
              pUMDVersion);
    if (FAILED(hr)) {
      throw IException("Failed to CheckInterfaceSupport. HRESULT(0x%lx)", hr);
    }
  }
};
  
}
