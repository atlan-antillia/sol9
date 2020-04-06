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
 *  DirectXGISwapChain.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIDeviceSubObject.h>

namespace SOL {

class DirectXGISwapChain : public DirectXGIDeviceSubObject {

public:
  DirectXGISwapChain()
    :DirectXGIDeviceSubObject()
  {
  }

  DirectXGISwapChain(IDXGISwapChain* chain)
  :DirectXGIDeviceSubObject()
  {
  	set(chain);
  }

  DirectXGISwapChain(IDXGIFactory* factory,
            __in  IUnknown *pDevice,
            __in  DXGI_SWAP_CHAIN_DESC *pDesc)
   :DirectXGIDeviceSubObject()
  {
    IDXGISwapChain* swapChain = NULL;
    HRESULT hr = factory -> CreateSwapChain( 
              pDevice,
              pDesc,
              &swapChain);
    if (SUCCEEDED(hr)) {
      set(swapChain);
    } else {
      throw IException("Failed to CreateSwapChain. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectXGISwapChain()
  {
  }
  
  operator IDXGISwapChain*()
  {
    return getSwapChain();
  }

  IDXGISwapChain* getSwapChain()
  {
    IDXGISwapChain* chain = (IDXGISwapChain*)getIUnknown();
    if (chain) {
      return chain;
    } else {
      throw IException("IDXGISwapChain is NULL.")
    }
  }

  void  present( 
            __in UINT syncInterval = 0,
            __in UINT flags        = 0)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> Present( 
              syncInterval,
              flags);
    if (FAILED(hr)) {
      throw IException("Failed to Present. HRESULT(0x%lx)", hr)
    }
  }      

  void  getBuffer( 
            __in UINT buffer,
            __in  REFIID riid,
            __out  void **ppSurface)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> GetBuffer( 
              buffer,
              riid,
              ppSurface);
    if (FAILED(hr)) {
      throw IException("Failed to GetBuffer. HRESULT(0x%lx)", hr)
    }
  }      
        
  void  setFullscreenState( 
            __in BOOL fullscreen,
            __in  IDXGIOutput *pTarget)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> SetFullscreenState( 
              fullscreen,
              pTarget);
    if (FAILED(hr)) {
      throw IException("Failed to SetFullscreenState. HRESULT(0x%lx)", hr)
    }
  }      
        
  void  getFullscreenState( 
            __out  BOOL *pFullscreen,
            __out  IDXGIOutput **ppTarget)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> GetFullscreenState( 
              pFullscreen,
              ppTarget);
    if (FAILED(hr)) {
      throw IException("Failed to GetFullscreenState. HRESULT(0x%lx)", hr)
    }
  }      
        
  void  getDesc( 
            __out  DXGI_SWAP_CHAIN_DESC *pDesc)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> GetDesc( 
            pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr)
    }
  }      
        
  void  resizeBuffers( 
            __in UINT bufferCount,
            __in UINT width,
            __in UINT height,
            __in DXGI_FORMAT newFormat,
            __in UINT swapChainFlags)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> ResizeBuffers( 
              bufferCount,
              width,
              height,
              newFormat,
            swapChainFlags);
    if (FAILED(hr)) {
      throw IException("Failed to ResizeBuffers. HRESULT(0x%lx)", hr)
    }
  }  
  
  //
  void resizeBuffers(
          __in UINT width,
          __in UINT height)
  {  
    try {

	   IDXGISwapChain* chain = getSwapChain();
	   if (chain) {
		  DXGI_SWAP_CHAIN_DESC desc;
		  chain->GetDesc(&desc);
		  chain->ResizeBuffers(desc.BufferCount, width, height, desc.BufferDesc.Format, desc.Flags);
	  }
    } catch (...) {
    }
  }
    
  void  resizeTarget( 
            __in  const DXGI_MODE_DESC *pNewTargetParameters)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> ResizeTarget( 
            pNewTargetParameters);
    if (FAILED(hr)) {
      throw IException("Failed to ResizeTarget. HRESULT(0x%lx)", hr)
    }
  }      
        
  void  getContainingOutput( 
            __out  IDXGIOutput **ppOutput)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> GetContainingOutput( 
              ppOutput);
    if (FAILED(hr)) {
      throw IException("Failed to GetContainingOutput. HRESULT(0x%lx)", hr)
    }
  }      
        
  void  getFrameStatistics( 
            __out  DXGI_FRAME_STATISTICS *pStats)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> GetFrameStatistics( 
            pStats);
    if (FAILED(hr)) {
      throw IException("Failed to GetFrameStatistics. HRESULT(0x%lx)", hr)
    }
  }      
        
  void  getLastPresentCount( 
            __out  UINT *pLastPresentCount)
  {
    IDXGISwapChain* chain = getSwapChain();
    HRESULT hr = chain -> GetLastPresentCount( 
            pLastPresentCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetLastPresentCount. HRESULT(0x%lx)", hr)
    }
  }      

};
}
