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
 *  Direct3D12DepthStencilView.h
 *
 *****************************************************************************/

// 2016/10/01

#pragma once

#include <sol/direct3d12/Direct3D12View.h>

namespace SOL {

class Direct3D12DepthStencilView : public Direct3D12View {
private:
  static const D3D12_DESCRIPTOR_HEAP_TYPE heapType = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
  
  ID3D12Resource*               depthStencil;
  
  D3D12_CPU_DESCRIPTOR_HANDLE   handle;
  
  UINT                          descriptorIncrementSize;
  

public:
  Direct3D12DepthStencilView(
      __in ID3D12Device* device,
      __in UINT          width,
      __in UINT          height)
  :Direct3D12View(device, 
                  1,  //bufferCount,
                  heapType), 
  depthStencil(NULL)
  {
    if (device == nullptr) {
      throw IException("Invalid parameter.");
    }
    if (width == 0 && height == 0) {
      throw IException("Invalid width(%d) and height(%d)", width, height); 
    }

    handle.ptr = 0;
    
    descriptorIncrementSize = device->GetDescriptorHandleIncrementSize(heapType);
      
    //1 Define a heapProperites
    D3D12_HEAP_PROPERTIES heapProp;
      memset(&heapProp, 0, sizeof(heapProp));
      heapProp.Type                 = D3D12_HEAP_TYPE_DEFAULT;
      heapProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
      heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
      heapProp.CreationNodeMask     = 1;
      heapProp.VisibleNodeMask      = 1;

    //2 Define a resourceDesc.
    D3D12_RESOURCE_DESC resDesc;
      memset(&resDesc, 0, sizeof(resDesc));
      resDesc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
      resDesc.Alignment          = 0;
      resDesc.Width              = width;
      resDesc.Height             = height;
      resDesc.DepthOrArraySize   = 1;
      resDesc.MipLevels          = 0;
      resDesc.Format             = DXGI_FORMAT_D32_FLOAT; //
      resDesc.SampleDesc.Count   = 1;
      resDesc.SampleDesc.Quality = 0;
      resDesc.Flags              = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
      resDesc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;

    //3 Define a clearValue
    D3D12_CLEAR_VALUE clearValue;
      memset(&clearValue, 0, sizeof(clearValue));
      clearValue.Format               = DXGI_FORMAT_D32_FLOAT;
      clearValue.DepthStencil.Depth   = 1.0f;
      clearValue.DepthStencil.Stencil = 0;
    
    //4 Create a depthStencil resource.
    HRESULT hr = device->CreateCommittedResource( 
              &heapProp,
              D3D12_HEAP_FLAG_NONE,
              (const D3D12_RESOURCE_DESC*)&resDesc,
              D3D12_RESOURCE_STATE_DEPTH_WRITE,
              &clearValue,
              IID_PPV_ARGS(&depthStencil));
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12Device::CreateCommittedResource. HRESULT(0x%lx)", hr );
    }
    
    //5 Define a depthStencailViewDesc
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
      memset(&dsvDesc, 0, sizeof(dsvDesc));
      dsvDesc.Format        = DXGI_FORMAT_D32_FLOAT;
      dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
      dsvDesc.Flags         = D3D12_DSV_FLAG_NONE;
        
    handle = getCPUDescriptorHandleForHeapStart();
    
    //6 Create a depthStencilView from resource depthStencil, depthStencilViewDesc dsvDes,
    // and cpuDescriptorHandle handle. 
    device->CreateDepthStencilView(
              depthStencil,
              &dsvDesc,
              handle);
  }

public:
  Direct3D12DepthStencilView(
        __in ID3D12Device*                     device,
        __in const D3D12_DESCRIPTOR_HEAP_DESC* heapDesc,
        __in D3D12_HEAP_PROPERTIES*            heapProp,
        __in D3D12_RESOURCE_DESC*              resourceDesc,
        __in D3D12_CLEAR_VALUE*                clearValue,
        __in D3D12_DEPTH_STENCIL_VIEW_DESC*    dsvDesc)
  :Direct3D12View(device, heapDesc),
  depthStencil(NULL)
  {
    if (device       == nullptr || 
        heapDesc     == nullptr || 
        heapProp     == nullptr ||
        resourceDesc == nullptr || 
        clearValue   == nullptr || 
        dsvDesc      == nullptr) {
        throw IException("Invalid parameters.");
    }
    
    descriptorIncrementSize = device->GetDescriptorHandleIncrementSize(heapType); //D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
      
    handle = getCPUDescriptorHandleForHeapStart();

    //1 Create a depthStencil resource.
    HRESULT hr = device->CreateCommittedResource(
          heapProp,
          D3D12_HEAP_FLAG_NONE,
          (const D3D12_RESOURCE_DESC*)&heapDesc,
          D3D12_RESOURCE_STATE_DEPTH_WRITE,
          clearValue,
          IID_PPV_ARGS(&depthStencil));
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12Device::CreateCommittedResource. HRESULT(0x%lx)", hr);
    }

    //2 Create a depthStencilView from the depthStencil resource and dsvDesc depthStencilDesc. 
    device->CreateDepthStencilView(
          depthStencil,
          dsvDesc,
          handle);
  }

  ~Direct3D12DepthStencilView()
  {
    if (depthStencil) {
      depthStencil->Release();
      depthStencil = NULL;
    }
  }
  
  operator ID3D12Resource*()
  {
    return depthStencil;
  }
  
  ID3D12Resource* getResource()
  {
    return depthStencil;
  }
  
  D3D12_CPU_DESCRIPTOR_HANDLE getHandle()
  {
    return handle;
  }
  
  UINT getDescriptorIncrementSize()
  {
    return descriptorIncrementSize;
  }
};

}

