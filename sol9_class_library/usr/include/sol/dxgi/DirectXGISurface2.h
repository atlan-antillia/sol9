/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DirectXGISurface2.h
 *
 *****************************************************************************/
 
#pragma once

#include <dxgi1_2.h>

#include <sol/dxgi/DirectXGISurface1.h>

namespace SOL {

class DirectXGISurface2 : public DirectXGISurface1 {
public:
  
  DirectXGISurface2(IDXGIDevice* device, 
            __in  const DXGI_SURFACE_DESC *pDesc,
            __in UINT numSurfaces,
            __in DXGI_USAGE usage,
            __in_opt  const DXGI_SHARED_RESOURCE *pSharedResource)
  :DirectXGISurface1()
  {
    IDXGISurface* surface = NULL;
    HRESULT hr = device -> CreateSurface( 
              pDesc,
              numSurfaces,
              usage,
            pSharedResource,
            &surface) ;
    if (SUCCEEDED(hr)) {
      set(surface);
    } else {
      throw IException("Failed to CreateSurface. HRESULT(0x%lx)", hr)
    }

  }
  
  DirectXGISurface2(IDXGISwapChain* chain, __in UINT buffer = 0)
  :DirectXGISurface1()
  {
    IDXGISurface* surface = NULL;
    HRESULT hr = chain -> GetBuffer(buffer, IID_IDXGISurface, (void**)&surface) ;
    if (SUCCEEDED(hr)) {
      set(surface);
    } else {
      throw IException("Failed to GetBuffer. HRESULT(0x%lx)", hr)
    }
  }
  
  ~DirectXGISurface2()
  {
  }
  
  operator IDXGISurface2*()
  {
    return getSurface2();
  }
  
  IDXGISurface2* getSurface2()
  {
    IDXGISurface2* surface = (IDXGISurface2*)getIUnknown();
    if (surface) {
      return surface;
    } else {
      throw IException("IDXGISurface2 is NULL.");
    }
  }
  //
  void getResource( 
            _In_  REFIID riid,
            _COM_Outptr_  void **ppParentResource,
            _Out_  UINT *pSubresourceIndex)
  {
    IDXGISurface2* surface2 = getSurface2();
    HRESULT hr = surface1 -> GetResource( 
            riid,
            ppParentResource,
            pSubresourceIndex);
    if (FAILED(hr)) {
      throw IException("Failed to GetResource. HRESULT(0x%lx)", hr);
    }
    
  }        
};

}
