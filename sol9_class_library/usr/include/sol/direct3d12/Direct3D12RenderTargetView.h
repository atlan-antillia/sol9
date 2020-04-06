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
 *  Direct3D12RenderTargetView.h
 *
 *****************************************************************************/

// 2016/10/01
// 2016/11/10 Updated.

#pragma once

#include <sol/direct3d12/Direct3D12View.h>

namespace SOL {


class Direct3D12RenderTargetView : public Direct3D12View {
private:
  static const D3D12_DESCRIPTOR_HEAP_TYPE heapType = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  
  //static const UINT             bufferCount = 2;
  UINT                          bufferCount;

  D3D12_CPU_DESCRIPTOR_HANDLE*  handle;
  
  ID3D12Resource**              resource;

  UINT                          descriptorIncrementSize;
  
public:
  Direct3D12RenderTargetView(
      __in ID3D12Device*   device,
      __in IDXGISwapChain* swapChain, 
      __in UINT            count = 2)
  :Direct3D12View(device, 
                  count,
                  heapType),
  bufferCount(count),
  descriptorIncrementSize(0),
  resource(NULL),
  handle(NULL)
  {
    if (device    == nullptr || 
        swapChain == nullptr ||
        bufferCount < 1) {
      throw IException("Invalid parameter."); 
    }

    handle = new D3D12_CPU_DESCRIPTOR_HANDLE[bufferCount];
    resource = new ID3D12Resource*[bufferCount];
    
    for(UINT i = 0; i<bufferCount; i++) {
      resource[i] = NULL;
      handle[i].ptr    = 0;
    }
    
 
    descriptorIncrementSize = device->GetDescriptorHandleIncrementSize(heapType);
                  
    D3D12_RENDER_TARGET_VIEW_DESC rtvDesc;
      memset(&rtvDesc,0, sizeof(rtvDesc));

      rtvDesc.Format               = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
      rtvDesc.ViewDimension        = D3D12_RTV_DIMENSION_TEXTURE2D;
      rtvDesc.Texture2D.MipSlice   = 0;
      rtvDesc.Texture2D.PlaneSlice = 0;
  
    for (UINT i = 0; i<bufferCount; i++) {
      //Get a resource for ecah buffer.
      HRESULT hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&resource[i]));
      if (FAILED(hr)) {
        throw IException("Failed to GetBuffer. HRESULT(0x%lx)", hr); 
      }
      handle[i] = getCPUDescriptorHandleForHeapStart();

      handle[i].ptr +=  (i * descriptorIncrementSize);
        
      device -> CreateRenderTargetView( 
            resource[i],
            //nullptr, //2016/11/05 
            &rtvDesc,
            handle[i]);
    }
  }

  Direct3D12RenderTargetView(
      __in ID3D12Device*                        device,
      __in IDXGISwapChain*                      swapChain,
      __in const D3D12_DESCRIPTOR_HEAP_DESC*    heapDesc,
      __in const D3D12_RENDER_TARGET_VIEW_DESC* rtvDesc,
      __in UINT                                 count=2)
  :Direct3D12View(device, 
                  heapDesc),
  bufferCount(count),
  descriptorIncrementSize(0),
  resource(NULL),
  handle(NULL)
  {    
    if (device    == nullptr || 
        swapChain == nullptr ||
        heapDesc  == nullptr || 
        rtvDesc   == nullptr ||
        bufferCount < 1) {
      throw IException("Invalid parameter.");
    }
    
    handle = new D3D12_CPU_DESCRIPTOR_HANDLE[bufferCount];
    resource = new ID3D12Resource*[bufferCount];
    
    for(UINT i = 0; i<bufferCount; i++) {
      resource[i] = NULL;
      handle[i].ptr    = 0;
    }
    
    descriptorIncrementSize = device->GetDescriptorHandleIncrementSize(heapType);
    
    for (UINT i = 0; i<bufferCount; i++) {
      HRESULT hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&resource[i]));
      if (FAILED(hr)) {
          throw IException("Failed to GetBuffer. HRESULT(0x%lx)", hr); 
      }
      handle[i] = getCPUDescriptorHandleForHeapStart();
      handle[i].ptr += (i * descriptorIncrementSize);       
      device -> CreateRenderTargetView( 
            resource[i],
            rtvDesc,
            handle[i]);
    }
  }

  ~Direct3D12RenderTargetView()
  {
    for(UINT i = 0; i<bufferCount; i++) {
      resource[i] ->Release();
    }
    delete [] resource;
    delete [] handle;
  }


  ID3D12Resource* getResource(UINT index)
  {
    if (index >= 0 && index< bufferCount) {
      return resource[index];
    } else {
      throw IException("Invalid index (%ld)", index);
    }
  }
    
  D3D12_CPU_DESCRIPTOR_HANDLE getHandle(UINT index)
  {
    if (index >= 0 && index< bufferCount) {
      return handle[index];
    } else {
      throw IException("Invalid index (%ld)", index);
    }
  }
  
  UINT getDescriptorIncrementSize()
  {
    return descriptorIncrementSize;
  }
};

}

