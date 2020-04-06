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
 *  DirectXGIResource.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIDeviceSubObject.h>

namespace SOL {

class DirectXGIResource : public DirectXGIDeviceSubObject {
    
public:
  DirectXGIResource()
  :DirectXGIDeviceSubObject()
  {
  }
  
  ~DirectXGIResource()
  {
  }
  operator IDXGIResource*()
  {
    return getResource();
  }
  
  IDXGIResource* getResource()
  {
    IDXGIResource* resource = (IDXGIResource*)getIUnknown();
    if (resource) {
      return resource;
    } else {
      throw IException("IDXGIResource is NULL");
    }
  }
  
  void getSharedHandle( 
            __out  HANDLE *pSharedHandle)
  {
    IDXGIResource* resource = getResource();
    HRESULT hr = resource -> GetSharedHandle( 
              pSharedHandle);
    if (FAILED(hr)) {
      throw IException("Failed to GetSharedHandle. HRESULT(0x%lx)", hr);
    }
  }
	
  void getUsage( 
            __out  DXGI_USAGE *pUsage)
  {
    IDXGIResource* resource = getResource();
    HRESULT hr = resource -> GetUsage( 
            pUsage);
    if (FAILED(hr)) {
      throw IException("Failed to GetUsage. HRESULT(0x%lx)", hr);
    }
  }
        
  void setEvictionPriority( 
           __in UINT evictionPriority)
  {
    IDXGIResource* resource = getResource();
    HRESULT hr = resource -> SetEvictionPriority( 
           evictionPriority);
    if (FAILED(hr)) {
      throw IException("Failed to SetEvictionPriority. HRESULT(0x%lx)", hr);
    }
  }
        
  void getEvictionPriority( 
            __out  UINT *pEvictionPriority)
  {
    IDXGIResource* resource = getResource();
    HRESULT hr = resource -> GetEvictionPriority( 
              pEvictionPriority);
    if (FAILED(hr)) {
      throw IException("Failed to GetEvictionPriority. HRESULT(0x%lx)", hr);
    }
  }
        
};

}

