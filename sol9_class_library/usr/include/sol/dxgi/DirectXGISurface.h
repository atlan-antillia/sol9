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
 *  DirectXGISurface.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIDeviceSubObject.h>

namespace SOL {

class DirectXGISurface : public DirectXGIDeviceSubObject {
public:
  
  DirectXGISurface(IDXGIDevice* device, 
            __in  const DXGI_SURFACE_DESC *pDesc,
            __in UINT numSurfaces,
            __in DXGI_USAGE usage,
            __in_opt  const DXGI_SHARED_RESOURCE *pSharedResource)
  :DirectXGIDeviceSubObject()
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
  
  DirectXGISurface(IDXGISwapChain* chain, __in UINT buffer = 0)
  :DirectXGIDeviceSubObject()
  {
    IDXGISurface* surface = NULL;
    HRESULT hr = chain -> GetBuffer(buffer, IID_IDXGISurface, (void**)&surface) ;
    if (SUCCEEDED(hr)) {
      set(surface);
    } else {
      throw IException("Failed to GetBuffer. HRESULT(0x%lx)", hr)
    }
  }
  
  ~DirectXGISurface()
  {
  }
  
  operator IDXGISurface*()
  {
    return getSurface();
  }
  
  IDXGISurface* getSurface()
  {
    IDXGISurface* surface = (IDXGISurface*)getIUnknown();
    if (surface) {
      return surface;
    } else {
      throw IException("IDXGISurface is NULL.");
    }
  }
  
  void getDesc( 
            __out  DXGI_SURFACE_DESC *pDesc)
  {
    IDXGISurface* surface = getSurface();
    HRESULT hr = surface -> GetDesc( 
            pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  void map( 
            __out  DXGI_MAPPED_RECT *pLockedRect,
            __in UINT mapFlags)
  {
    IDXGISurface* surface = getSurface();
    HRESULT hr = surface -> Map( 
            pLockedRect,
            mapFlags);
    if (FAILED(hr)) {
      throw IException("Failed to Map. HRESULT(0x%lx)", hr);
    }
  }
        
  void unmap()
  {
    IDXGISurface* surface = getSurface();
    HRESULT hr = surface -> Unmap();
    if (FAILED(hr)) {
      throw IException("Failed to Unmap. HRESULT(0x%lx)", hr);
    }
  }
        
};

}
