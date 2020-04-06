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

#include <sol/dxgi/DirectXGIAdapter1.h>
#include <dxgi1_2.h<

namespace SOL {
  
class DirectXGIAdapter : public DirectXGIAdapter1 {
   

public:
  //Enumerate an IDXGIAdapter throw IDXGIFactory interface.
  DirectXGIAdapter2(IDXGIFactory* factory, __in UINT adapterIndex)
  :DirectXGIAdapter1()
  {
    IDXGIAdapter* adapter = NULL;
    HRESULT hr = factory -> EnumAdapters( 
              adapterIndex,
              &adapter);
    if (SUCCEEDED(hr)) {
      set(adapter);
    } else {
      throw IException("Failed to EnumAdapters. HRESULT(0x%lx)", hr);
    }
  }

public:
  //Get an IDXGIAdapter from IDXGIDevice interface
  DirectXGIAdapter2(IDXGIDevice* device)
  :DirectXGIAdapter1()
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
  DirectXGIAdapter2(IDXGIFactory* factory, __in HMODULE module)
  :DirectXGIAdapter1()
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
    
  ~DirectXGIAdapter2()
  {
  }
  
  operator IDXGIAdapter2*()
  {
    return getAdapter2();
  }
  
  IDXGIAdapter2* getAdapter2()
  {
    IDXGIAdapter2* adapter2 = (IDXGIAdapter2*)getIUnknown();
    if (adapter2) {
      return adapter2;
    } else {
      throw IException("IDXGIAdapter2 is NULL.");
    }
  }
  
  //
  {
    IDXGIAdapter2* adapter2 = getAdapter2();
    HRESULT hr = adapter2 -> ;
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
    
  }
  
  //

};
  
}
