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
 *  DirectXGIDevice2.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIDevice.h>


namespace SOL {

class DirectXGIDevice1 : public DirectXGIDevice {

  
public:
  DirectXGIDevice1(ID3D11On12Device* d3d12Device)
//2016/11/25  DirectXGIDevice1(ID3D12Device* d3d12Device)

  :DirectXGIDevice()
  {
	  IDXGIDevice1* device1 = NULL;
	  HRESULT hr = d3d12Device->QueryInterface(__uuidof(IDXGIDevice1),
		  (void **)&device1);
	  if (SUCCEEDED(hr)) {
		  set(device1);
	  }
	  else {
		  throw IException("Failed to QueryInterface. HRESULT(0x%lx)", hr);
	  }
  }
  
  ~DirectXGIDevice1()
  {
  }
  
  operator IDXGIDevice1*()
  {
    return getDevice1();
  }

  IDXGIDevice1* getDevice1()
  {
    IDXGIDevice1* device1 = (IDXGIDevice1*)getIUnknown();
    if (device1) {
      return device1;
    } else {
      throw IException("IDXGIDevice1 is NULL.")
    }
  }  

  void setMaximumFrameLatency( 
            __in UINT maxLatency)
  {
    IDXGIDevice1* device1 = getDevice1();
    HRESULT hr = device1 -> SetMaximumFrameLatency( 
            maxLatency);
    if (FAILED(hr)) {
      throw IException("Failed to SetMaximumFrameLatency. HRESULT(0x%lx)", hr);
    }
  }      

  void getMaximumFrameLatency( 
            __out  UINT *pMaxLatency)
  {
    IDXGIDevice1* device1 = getDevice1();
    HRESULT hr = device1 -> GetMaximumFrameLatency( 
            pMaxLatency);
    if (FAILED(hr)) {
      throw IException("Failed to GetMaximumFrameLatency. HRESULT(0x%lx)", hr);
    }
  }      
        
};

}
