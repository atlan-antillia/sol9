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
 *  DirectXGISurface1.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGISurface.h>

namespace SOL {

class DirectXGISurface1 : public DirectXGISurface {
public:
  
  DirectXGISurface1(IDXGIDevice* device, 
            __in  const DXGI_SURFACE_DESC *pDesc,
            __in UINT numSurfaces,
            __in DXGI_USAGE usage,
            __in_opt  const DXGI_SHARED_RESOURCE *pSharedResource)
  :DirectXGISurface()
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
  
  DirectXGISurface1(IDXGISwapChain* chain, __in UINT buffer = 0)
  :DirectXGISurface()
  {
    IDXGISurface* surface = NULL;
    HRESULT hr = chain -> GetBuffer(buffer, IID_IDXGISurface, (void**)&surface) ;
    if (SUCCEEDED(hr)) {
      set(surface);
    } else {
      throw IException("Failed to GetBuffer. HRESULT(0x%lx)", hr)
    }
  }
  
  ~DirectXGISurface1()
  {
  }
  
  operator IDXGISurface1*()
  {
    return getSurface1();
  }
  
  IDXGISurface1* getSurface1()
  {
    IDXGISurface1* surface = (IDXGISurface1*)getIUnknown();
    if (surface) {
      return surface;
    } else {
      throw IException("IDXGISurface1 is NULL.");
    }
  }
  //
  void getDC( 
            BOOL discard,
            _Out_  HDC *phdc)
  {
    IDXGISurface1* surface1 = getSurface1();
    HRESULT hr = surface1 -> GetDC( 
              discard,
              phdc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDC. HRESULT(0x%lx)", hr);
    }
  }

  void releaseDC( 
            _In_opt_  RECT *pDirtyRect)
  {
    IDXGISurface1* surface1 = getSurface1();
    HRESULT hr = surface1 -> ReleaseDC( 
            _pDirtyRect);
    if (FAILED(hr)) {
      throw IException("Failed to ReleaseDC. HRESULT(0x%lx)", hr);
    }
  }
        
};

}
