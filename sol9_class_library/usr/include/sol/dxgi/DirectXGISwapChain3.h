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
 *  DirectXGISwapChain3.h
 *
 *****************************************************************************/
 
// 2016/11/10 Added new Direct3D12SwapChain3 constructors.
 
#pragma once

#include <d3d12.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>

#include <sol/dxgi/DirectXGISwapChain2.h>

namespace SOL {

class DirectXGISwapChain3 : public DirectXGISwapChain2 {

//2016/11/10
public:
  DirectXGISwapChain3(
          IDXGIFactory4*          factory, 
          ID3D12CommandQueue*     commandQueue,
          UINT                    frameCount,
          HWND                    hwnd,
          UINT                    width,
          UINT                    height,
          bool                    enableFullscreen= false)
  :DirectXGISwapChain2()
  {
    if (factory == nullptr || commandQueue == nullptr) {
      throw IException("Invalid parameter.");
    }
    
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = frameCount;
    swapChainDesc.Width       = width;
    swapChainDesc.Height      = height;
    swapChainDesc.Format      = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect  = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;
    
    IDXGISwapChain1* chain1 = NULL;
    HRESULT hr = factory->CreateSwapChainForHwnd(
      commandQueue,
      hwnd,
      &swapChainDesc,
      nullptr,
      nullptr,
      &chain1 );
    if (FAILED(hr)) {
      throw IException("Failed to CreateSwapChain");
    }

    IDXGISwapChain3* swapChain3= NULL;
    
    hr = chain1->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&swapChain3);
    chain1->Release();
    if (FAILED(hr)){
      throw IException("Failed to QueryInterface for IDXGISwapChain3. HRESULT(0x%lx)", hr);
    }    
    
    if (enableFullscreen) {
      set(swapChain3);
    } else {
	    hr = factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
      if (SUCCEEDED(hr)) {
        set(swapChain3);
      } else {
        throw IException("Failed to MakeWindowAssociation. HRESULT(0x%lx)", hr);
      }
    }    
  }
  
//2016/11/10
public:
  DirectXGISwapChain3(
          IDXGIFactory4*          factory, 
          ID3D12CommandQueue*     commandQueue,
          DXGI_SWAP_CHAIN_DESC1*  swapChainDesc,
          HWND                    hwnd,
          UINT                    width,
          UINT                    height,
          bool                    enableFullscreen= false)
  :DirectXGISwapChain2()
  {   
    if (factory == nullptr || commandQueue == nullptr ||
        swapChainDesc == nullptr) {
      throw IException("Invalid parameter.");
    }

    IDXGISwapChain1* chain1 = NULL;
    HRESULT hr = factory->CreateSwapChainForHwnd(
      commandQueue,
      hwnd,
      swapChainDesc, 
      nullptr,
      nullptr,
      &chain1 );
    if (FAILED(hr)) {
      throw IException("Failed to CreateSwapChain");
    }

    IDXGISwapChain3* swapChain3= NULL;
    
    hr = chain1->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&swapChain3);
    chain1->Release();
    if (FAILED(hr)){
      throw IException("Failed to QueryInterface for IDXGISwapChain3. HRESULT(0x%lx)", hr);
    }    
    
    if (enableFullscreen) {
      set(swapChain3);
    } else {
	    hr = factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
      if (SUCCEEDED(hr)) {
        set(swapChain3);
      } else {
        throw IException("Failed to MakeWindowAssociation. HRESULT(0x%lx)", hr);
      }
    }    
  }
  
public:
  DirectXGISwapChain3(
        IDXGIFactory4* dxgiFactory,
        ID3D12CommandQueue* commandQueue,
        DXGI_SWAP_CHAIN_DESC* desc)
  :DirectXGISwapChain2()
  {
    if (dxgiFactory == nullptr || commandQueue == nullptr || desc == nullptr) {
      throw IException("Invalid parameter.");
    }
    IDXGISwapChain3* swapChain3 = NULL;
    HRESULT hr = dxgiFactory->CreateSwapChain(commandQueue, desc, 
          (IDXGISwapChain**)&swapChain3);    
    if (SUCCEEDED(hr)){
      set(swapChain3); 
    } else {
      throw IException("Failed to CreateSwapChain");
    }
  }

public:
  
  DirectXGISwapChain3(IDXGISwapChain1* chain)
  :DirectXGISwapChain2()
  {
    if (chain) {
      IDXGISwapChain3* chain3 = NULL;
      HRESULT hr = chain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&chain3);
      if (SUCCEEDED(hr)){
        set(chain3); 
      } else {
        throw IException("Failed to QueryInterface for IDXGISwapChain3. HRESULT(0x%lx)", hr);
      }
    } else {
      throw IException("IDXGISwapChain is NULL");
    }
  }

  DirectXGISwapChain3(IDXGISwapChain3* chain)
  :DirectXGISwapChain2(chain)
  {
  }

  ~DirectXGISwapChain3()
  {
  }
  
  operator IDXGISwapChain3*()
  {
    return getSwapChain3();
  }

  IDXGISwapChain3* getSwapChain3()
  {
    IDXGISwapChain3* chain = (IDXGISwapChain3*)getIUnknown();
    if (chain) {
      return chain;
    } else {
      throw IException("IDXGISwapChain2 is NULL.")
    }
  }

  UINT getCurrentBackBufferIndex()
  {
    IDXGISwapChain3* chain3 = getSwapChain3();
    return chain3->GetCurrentBackBufferIndex();
  }
  
  void checkColorSpaceSupport( 
            _In_  DXGI_COLOR_SPACE_TYPE colorSpace,
            _Out_  UINT *pColorSpaceSupport)
  {
    IDXGISwapChain3* chain3 = getSwapChain3();
    HRESULT hr = chain3->CheckColorSpaceSupport( 
            colorSpace,
            pColorSpaceSupport);
    if (FAILED(hr)) {
      throw IException("Failed to CheckColorSpaceSupport. HRESULT(0x%lx)", hr);
    }
  }
        
  void setColorSpace1( 
            _In_  DXGI_COLOR_SPACE_TYPE colorSpace)
  {
    IDXGISwapChain3* chain3 = getSwapChain3();
    HRESULT hr = chain3->SetColorSpace1( 
              colorSpace);
    if (FAILED(hr)) {
      throw IException("Failed to SetColorSpace1. HRESULT(0x%lx)", hr);
    }
  }
        
  void resizeBuffers1( 
            _In_  UINT bufferCount,
            _In_  UINT width,
            _In_  UINT height,
            _In_  DXGI_FORMAT format,
            _In_  UINT swapChainFlags,
            _In_reads_(BufferCount)  const UINT *pCreationNodeMask,
            _In_reads_(BufferCount)  IUnknown *const *ppPresentQueue)
  {
    IDXGISwapChain3* chain3 = getSwapChain3();
    HRESULT hr = chain3->ResizeBuffers1( 
              bufferCount,
              width,
              height,
              format,
              swapChainFlags,
              pCreationNodeMask,
              ppPresentQueue);
    if (FAILED(hr)) {
      throw IException("Failed to ResizeBuffers1. HRESULT(0x%lx)", hr);
    }

  }

};
}
