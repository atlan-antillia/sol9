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
 *  DirectXGIFactory.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIObject.h>

namespace SOL {

class DirectXGIFactory : public DirectXGIObject {
public:
  DirectXGIFactory()
  :DirectXGIObject()
  {
    IDXGIFactory* factory = NULL;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    if (SUCCEEDED(hr)) {
      set(factory);
    } else {
      throw IException("Failed to CreateDXGIFactory. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectXGIFactory()
  {
  }
  
  operator   IDXGIFactory*()
  {
    return getFactory();
  }
  
  IDXGIFactory* getFactory()
  {
    IDXGIFactory* factory = (IDXGIFactory*)getIUnknown();
    if (factory) {
      return factory;
    } else {
      throw IException("IDXGIFactory is NULL.");
    }
  }
  void enumAdapters( 
            __in UINT adapter,
            __out  IDXGIAdapter **ppAdapter)
  {
    IDXGIFactory* factory = getFactory();
    HRESULT hr = factory -> EnumAdapters( 
              adapter,
              ppAdapter);
    if (FAILED(hr)) {
      throw IException("Failed to EnumAdapters. HRESULT(0x%lx)", hr);
    }
  }
  
  void makeWindowAssociation( 
            HWND windowHandle,
            UINT flags)
  {
    IDXGIFactory* factory = getFactory();
    HRESULT hr = factory -> MakeWindowAssociation( 
            windowHandle,
            flags);
    if (FAILED(hr)) {
      throw IException("Failed to MakeWindowAssociation. HRESULT(0x%lx)", hr);
    }
  }
        
  void getWindowAssociation( 
            __out  HWND *pWindowHandle)
  {
    IDXGIFactory* factory = getFactory();
    HRESULT hr = factory -> GetWindowAssociation( 
              pWindowHandle);
    if (FAILED(hr)) {
      throw IException("Failed to GetWindowAssociation. HRESULT(0x%lx)", hr);
    }
  }
        
  void createSwapChain( 
            __in  IUnknown *pDevice,
            __in  DXGI_SWAP_CHAIN_DESC *pDesc,
            __out  IDXGISwapChain **ppSwapChain)
  {
    IDXGIFactory* factory = getFactory();
    HRESULT hr = factory -> CreateSwapChain( 
              pDevice,
              pDesc,
              ppSwapChain);
    if (FAILED(hr)) {
      throw IException("Failed to CreateSwapChain. HRESULT(0x%lx)", hr);
    }
  }
        
  void createSoftwareAdapter( 
            __in HMODULE module,
            __out  IDXGIAdapter **ppAdapter)
  {
    IDXGIFactory* factory = getFactory();
    HRESULT hr = factory -> CreateSoftwareAdapter( 
              module,
              ppAdapter);
    if (FAILED(hr)) {
      throw IException("Failed to CreateSoftwareAdapter. HRESULT(0x%lx)", hr);
    }
  }
        
};
}

