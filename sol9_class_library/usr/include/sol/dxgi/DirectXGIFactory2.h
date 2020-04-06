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
 *  DirectXGIFactory2.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIFactory1.h>

#ifdef WIN10
#include <dxgi1_2.h>  //C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\shared
#endif

namespace SOL {

class DirectXGIFactory2 : public DirectXGIFactory1 {

public:
  DirectXGIFactory2()
  :DirectXGIFactory1()
  {
    IDXGIFactory2* factory2 = NULL;
	  HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory2), (void**)&factory2);
    if (SUCCEEDED(hr)) {
      set(factory2);
    } else {
		  throw IException("Failed to Get IDXGIFactory2. HRESULT(0x%lx)", hr);
    }
  }
  
  
  operator IDXGIFactory2*()
  {
    return getFactory2();
  }
  
  IDXGIFactory2* getFactory2()
  {
    IDXGIFactory2* factory2 = (IDXGIFactory2*)getIUnknown();
    if (factory2) {
      return factory2;
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
    
  BOOL isWindowedStereoEnabled()
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      return factory2 -> IsWindowedStereoEnabled();
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
  
  void createSwapChainForHwnd( 
            _In_  IUnknown *pDevice,
            _In_  HWND hWnd,
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            _In_opt_  const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> CreateSwapChainForHwnd( 
            pDevice,
            hWnd,
            pDesc,
            pFullscreenDesc,
            pRestrictToOutput,
            ppSwapChain);
      if (FAILED(hr)) {
        throw IException("Failed to CreateSwapChainForHwnd. HESULT(%ld)", hr);
      }
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void createSwapChainForCoreWindow( 
            _In_  IUnknown *pDevice,
            _In_  IUnknown *pWindow,
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> CreateSwapChainForCoreWindow( 
            pDevice,
            pWindow,
            pDesc,
            pRestrictToOutput,
            ppSwapChain);
      if (FAILED(hr)) {
        throw IException("Failed to CreateSwapChainForCoreWindow. HRESULT(%ld)", hr);
      }
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void getSharedResourceAdapterLuid( 
            _In_  HANDLE hResource,
            _Out_  LUID *pLuid)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> GetSharedResourceAdapterLuid( 
            hResource,
            pLuid);
      if (FAILED(hr)) {
        throw IException("Failed to GetSharedResourceAdapterLuid. HRESULT(%ld)", hr);
      }
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void registerStereoStatusWindow( 
            _In_  HWND windowHandle,
            _In_  UINT wMsg,
            _Out_  DWORD *pdwCookie)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> RegisterStereoStatusWindow( 
            windowHandle,
            wMsg,
            pdwCookie);
      if (FAILED(hr)) {
        throw IException("Failed to RegisterStereoStatusWindow. HRESULT(%ld)", hr);
      }      
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void registerStereoStatusEvent( 
            _In_  HANDLE hEvent,
            _Out_  DWORD *pdwCookie)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> RegisterStereoStatusEvent( 
            hEvent,
            pdwCookie);
      if (FAILED(hr)) {
        throw IException("Failed to RegisterStereoStatusEvent. HRESULT(%ld)", hr);
      }      
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void unregisterStereoStatus( 
            _In_  DWORD dwCookie)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      factory2 -> UnregisterStereoStatus( 
            dwCookie);
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void registerOcclusionStatusWindow( 
            _In_  HWND windowHandle,
            _In_  UINT wMsg,
            _Out_  DWORD *pdwCookie)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> RegisterOcclusionStatusWindow( 
            windowHandle,
            wMsg,
            pdwCookie);
      if (FAILED(hr)) {
        throw IException("Failed to RegisterOcclusionStatusWindow. HRESULT(%ld)", hr);
      }
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void registerOcclusionStatusEvent( 
            _In_  HANDLE hEvent,
            _Out_  DWORD *pdwCookie)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> RegisterOcclusionStatusEvent( 
            hEvent,
            pdwCookie);
      if (FAILED(hr)) {
        throw IException("Failed to RegisterOcclusionStatusEvent. HRESULT(%ld)", hr);
      }
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void unregisterOcclusionStatus( 
            _In_  DWORD dwCookie)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      factory2 -> UnregisterOcclusionStatus( 
            dwCookie);
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
        
  void createSwapChainForComposition( 
            _In_  IUnknown *pDevice,
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain)
  {
    IDXGIFactory2* factory2 = getFactory2();
    if (factory2) {
      HRESULT hr = factory2 -> CreateSwapChainForComposition( 
            pDevice,
            pDesc,
            pRestrictToOutput,
            ppSwapChain);
      if (FAILED(hr)) {
        throw IException("Failed to CreateSwapChainForComposition. HRESULT(%ld)", hr);
      }
    } else {
      throw IException("IDXGIFactory2 is NULL.");
    }
  }
};

}
            