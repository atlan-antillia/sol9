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
 *  DirectXGISwapChain1.h
 *
 *****************************************************************************/
 
#pragma once

#include <dxgi1_3.h>

#include <sol/dxgi/DirectXGISwapChain.h>

namespace SOL {

class DirectXGISwapChain1 : public DirectXGISwapChain {
  
public:
  DirectXGISwapChain1()
  :DirectXGISwapChain()
  {
  }

  DirectXGISwapChain1(IDXGIFactory4* factory,
    __in  IUnknown *pDevice,
    __in  HWND hWnd,
    __in  DXGI_SWAP_CHAIN_DESC1 *pDesc,
    _In_opt_  const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc = nullptr,
    _In_opt_  IDXGIOutput *pRestrictToOutput = nullptr)
    :DirectXGISwapChain()
  {
    IDXGISwapChain1* swapChain1 = NULL;

    HRESULT hr = factory->CreateSwapChainForHwnd(
      pDevice,
      hWnd,
      pDesc,
      pFullscreenDesc,
      pRestrictToOutput,
      &swapChain1);

    if (SUCCEEDED(hr)) {
      set(swapChain1);
    }
    else {
      throw IException("Failed to IDXGIFactory4::CreateSwapChainForHwnd. HRESULT(0x%lx)", hr);
    }
  }

  DirectXGISwapChain1(IDXGISwapChain1* chain)
  :DirectXGISwapChain(chain)
  {
  }


  ~DirectXGISwapChain1()
  {
  }
  
  operator IDXGISwapChain1*()
  {
    return getSwapChain1();
  }

  IDXGISwapChain1* getSwapChain1()
  {
    IDXGISwapChain1* chain = (IDXGISwapChain1*)getIUnknown();
    if (chain) {
      return chain;
    } else {
      throw IException("IDXGISwapChain1 is NULL.")
    }
  }

  //
  void getDesc1( 
            _Out_  DXGI_SWAP_CHAIN_DESC1 *pDesc)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->GetDesc1( 
            pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc1. HRESULT(0x%lx)", hr);
    }
  }
          
  void getFullscreenDesc( 
            _Out_  DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->GetFullscreenDesc( 
            pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetFullscreenDesc. HRESULT(0x%lx)", hr);
    }
  }
        
  void getHwnd( 
            _Out_  HWND *pHwnd)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->GetHwnd( 
            pHwnd);
    if (FAILED(hr)) {
      throw IException("Failed to GetHwnd. HRESULT(0x%lx)", hr);
    }
  }
        
  void getCoreWindow( 
            _In_  REFIID refiid,
            _COM_Outptr_  void **ppUnk)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->GetCoreWindow( 
              refiid,
              ppUnk);
    if (FAILED(hr)) {
      throw IException("Failed to GetCoreWindow. HRESULT(0x%lx)", hr);
    }
  }
        
  void present1( 
            UINT syncInterval,
            UINT presentFlags, 
            _In_  const DXGI_PRESENT_PARAMETERS *pPresentParameters)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->Present1( 
              syncInterval,
              presentFlags, 
              pPresentParameters);
    if (FAILED(hr)) {
      throw IException("Failed to Present1. HRESULT(0x%lx)", hr);
    }
  }
        
  BOOL isTemporaryMonoSupported()
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    return chain1->IsTemporaryMonoSupported();
  }
        
  void getRestrictToOutput( 
            _Out_  IDXGIOutput **ppRestrictToOutput)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->GetRestrictToOutput( 
            ppRestrictToOutput);
    if (FAILED(hr)) {
      throw IException("Failed to GetRestrictToOutput. HRESULT(0x%lx)", hr);
    }
  }
        
  void setBackgroundColor( 
            _In_  const DXGI_RGBA *pColor)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->SetBackgroundColor( 
            pColor);
    if (FAILED(hr)) {
      throw IException("Failed to SetBackgroundColor. HRESULT(0x%lx)", hr);
    }
  }
        
  void getBackgroundColor( 
            _Out_  DXGI_RGBA *pColor)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->GetBackgroundColor( 
            pColor);
    if (FAILED(hr)) {
      throw IException("Failed to GetBackgroundColor. HRESULT(0x%lx)", hr);
    }
  }
        
  void setRotation( 
            _In_  DXGI_MODE_ROTATION rotation)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->SetRotation( 
              rotation);
    if (FAILED(hr)) {
      throw IException("Failed to SetRotation. HRESULT(0x%lx)", hr);
    }
  }
        
  void getRotation( 
            _Out_  DXGI_MODE_ROTATION *pRotation)
  {
    IDXGISwapChain1* chain1 = getSwapChain1();
    HRESULT hr = chain1->GetRotation( 
            pRotation);
    if (FAILED(hr)) {
      throw IException("Failed to GetRotation. HRESULT(0x%lx)", hr);
    }
  }


  //
  

};
}
