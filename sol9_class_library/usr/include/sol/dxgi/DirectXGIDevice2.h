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
 *  DirectXGIDevice2.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIDevice1.h>
#include <dxgi1_2.h>

namespace SOL {

class DirectXGIDevice2 : public DirectXGIDevice1 {
public:
  DirectXGIDevice2()
  :DirectXGIDevice1()
  {
  }
  
  ~DirectXGIDevice2()
  {
  }
  
  operator IDXGIDevice2*()
  {
    return getDevice2();
  }

  IDXGIDevice2* getDevice2()
  {
    IDXGIDevice2* device2 = (IDXGIDevice2*)getIUnknown();
    if (device1) {
      return device2;
    } else {
      throw IException("IDXGIDevice2 is NULL.")
    }
  }  

  //
  void offerResources( 
            _In_  UINT numResources,
            _In_reads_(numResources)  IDXGIResource *const *ppResources,
            _In_  DXGI_OFFER_RESOURCE_PRIORITY priority)
  {
    IDXGIDevice2* device2 = getDevice2();
    HRESULT hr = device2 -> OfferResources( 
            numResources,
            ppResources,
            priority);
    if (FAILED(hr)) {
      throw IException("Failed to OfferResources. HRESULT(0x%lx)", hr);
    }
  }      
        
  void reclaimResources( 
            _In_  UINT numResources,
            _In_reads_(numResources)  IDXGIResource *const *ppResources,
            _Out_writes_all_opt_(NumResources)  BOOL *pDiscarded)
  {
    IDXGIDevice2* device2 = getDevice2();
    HRESULT hr = device2 -> ReclaimResources( 
              numResources,
              ppResources,
              pDiscarded);
    if (FAILED(hr)) {
      throw IException("Failed to ReclaimResources. HRESULT(0x%lx)", hr);
    }
  }      
        
  void enqueueSetEvent( 
            _In_  HANDLE hEvent)
  {
    IDXGIDevice2* device2 = getDevice2();
    HRESULT hr = device2 -> EnqueueSetEvent( 
            hEvent);
    if (FAILED(hr)) {
      throw IException("Failed to EnqueueSetEvent. HRESULT(0x%lx)", hr);
    }
  }      
  
  //
};

}
