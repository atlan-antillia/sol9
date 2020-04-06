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
 *  DirectXGIResource1.h
 *
 *****************************************************************************/
 
#pragma once

#include <dxgi1_2.h>
#include <sol/dxgi/DirectXGIResource.h>

namespace SOL {

class DirectXGIResource1 : public DirectXGIResource {
    
public:
  DirectXGIResource1()
  :DirectXGIResource()
  {
  }
  
  ~DirectXGIResource1()
  {
  }
  operator IDXGIResource1*()
  {
    return getResource1();
  }
  
  IDXGIResource1* getResource1()
  {
    IDXGIResource1* resource = (IDXGIResource1*)getIUnknown();
    if (resource) {
      return resource;
    } else {
      throw IException("IDXGIResource1 is NULL");
    }
  }
  
  //
  void createSubresourceSurface( 
            UINT index,
            _COM_Outptr_  IDXGISurface2 **ppSurface)
  {
    IDXGIResource1* resource1 = getResource1();
    HRESULT hr = resource1 -> CreateSubresourceSurface( 
            index,
            ppSurface);
    if (FAILED(hr)) {
      throw IException("Failed to CreateSubresourceSurface. HRESULT(0x%lx)", hr);
    } 
  }
        
  void createSharedHandle( 
            _In_opt_  const SECURITY_ATTRIBUTES *pAttributes,
            _In_  DWORD dwAccess,
            _In_opt_  LPCWSTR lpName,
            _Out_  HANDLE *pHandle)
  {
    IDXGIResource1* resource1 = getResource1();
    HRESULT hr = resource1 -> CreateSharedHandle( 
            pAttributes,
            dwAccess,
            lpName,
            pHandle);
    if (FAILED(hr)) {
      throw IException("Failed to CreateSharedHandle. HRESULT(0x%lx)", hr);
    }
 
  }
  
  //
        
};

}

