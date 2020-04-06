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
 *  Direct3D12ConstantBufferView.h
 *
 *****************************************************************************/

// 2016/10/15
// Simple constBufferView for D3D12ConstantBuffer (worldViewProject)
//
// 2016/11/24  Added the following constructor
//  Direct3D12ConstantBufferView(
//      __in ID3D12Device* device,
//      __in Direct3D12CommonDescriptorHeap*   commonDescriptorHeap, 
//      __in UINT          constantBufferSize= ConstantBufferSize )

#pragma once

#include <sol/direct3d12/Direct3D12View.h>
#include <sol/direct3d12/Direct3D12CommonDescriptorHeap.h>


namespace SOL {

class Direct3D12ConstantBufferView : public Direct3D12View {
private:
  static const int                HandleIndex = CBV_HANDLE; //
  
  static const int                ConstantBufferSize=256;
    
  D3D12_CPU_DESCRIPTOR_HANDLE     handle;
  
  ID3D12Resource*                 resource;
    
  D3D12_CONSTANT_BUFFER_VIEW_DESC resourceView;
  
/*
typedef struct D3D12_CONSTANT_BUFFER_VIEW_DESC {
  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation;
  UINT                      SizeInBytes;
} D3D12_CONSTANT_BUFFER_VIEW_DESC;
*/
  
protected:
  //Define your own getHeapProperites method in your subclass derived from this class.
  virtual D3D12_HEAP_PROPERTIES getHeapProperties()
  {
    D3D12_HEAP_PROPERTIES prop;
    memset(&prop, 0, sizeof(prop));
    prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    prop.CreationNodeMask     = 1;
    prop.VisibleNodeMask      = 1;
    return prop;
  }
  
  
  //Define your own getResourceDesc method in your subclass derived from this class.
  virtual D3D12_RESOURCE_DESC getResourceDesc(UINT width)
  {
      D3D12_RESOURCE_DESC resDesc;
      memset(&resDesc, 0, sizeof(resDesc));
      resDesc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
      resDesc.Alignment          = 0;
      resDesc.Width              = width;
      resDesc.Height             = 1;
      resDesc.DepthOrArraySize   = 1;
      resDesc.MipLevels          = 1;
      resDesc.Format             = DXGI_FORMAT_UNKNOWN;
      resDesc.SampleDesc.Count   = 1;
      resDesc.SampleDesc.Quality = 0;
      resDesc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
      resDesc.Flags              = D3D12_RESOURCE_FLAG_NONE;
    return resDesc;
  }

public:
  //2016/11/24 Added the following constructor.
  Direct3D12ConstantBufferView(
      __in ID3D12Device* device,
      __in Direct3D12CommonDescriptorHeap*   commonDescriptorHeap, 
      __in UINT          constantBufferSize= ConstantBufferSize )
  
  :Direct3D12View(),
  //handle(cbvHandle),
  resource(NULL)
  {
    if (device == nullptr || commonDescriptorHeap == nullptr || constantBufferSize<1) {
      throw IException("Invalid parameter.");
    }
    
    handle = commonDescriptorHeap->getCPUHandle(HandleIndex);
    
    //1 Get a heapProperties.
    D3D12_HEAP_PROPERTIES heapProp = getHeapProperties();
        
    //2 Get a resourceDesc.
    D3D12_RESOURCE_DESC resDesc = getResourceDesc( constantBufferSize );
 
    //3 Create a resource resource frpm the heapProp, resDesc.
    HRESULT  hr = device->CreateCommittedResource(
            &heapProp,
            D3D12_HEAP_FLAG_NONE,
            &resDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,  //const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            IID_PPV_ARGS(&resource) );
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12Device::CreateCommittedResource. HRESULT(0x%lx)", hr);
    }
    
    memset(&resourceView,  0, sizeof(resourceView));

    resourceView.BufferLocation = resource->GetGPUVirtualAddress();
   
    resourceView.SizeInBytes    = ConstantBufferSize;// (constantBufferSize + 255) & ~255; // CB size is required to be 256-byte aligned.

    device->CreateConstantBufferView(&resourceView, handle);
  }

public:
  Direct3D12ConstantBufferView(
      __in ID3D12Device* device,
      __in D3D12_CPU_DESCRIPTOR_HANDLE cbvHandle,  //CPU Handle gotten from Direct3D12CommonDescriptorHeap
      __in UINT          constantBufferSize= ConstantBufferSize )
  
  :Direct3D12View(),
  handle(cbvHandle),
  resource(NULL)
  {
    if (device == nullptr || constantBufferSize<1) {
      throw IException("Invalid parameter.");
    }
              
    //1 Get a heapProperties.
    D3D12_HEAP_PROPERTIES heapProp = getHeapProperties();
        
    //2 Get a resourceDesc.
    D3D12_RESOURCE_DESC resDesc = getResourceDesc( constantBufferSize );
 
    //3 Create a resource resource frpm the heapProp, resDesc.
    HRESULT  hr = device->CreateCommittedResource(
            &heapProp,
            D3D12_HEAP_FLAG_NONE,
            &resDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,  //const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            IID_PPV_ARGS(&resource) );
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12Device::CreateCommittedResource. HRESULT(0x%lx)", hr);
    }
    
    memset(&resourceView,  0, sizeof(resourceView));

    resourceView.BufferLocation = resource->GetGPUVirtualAddress();
   
    resourceView.SizeInBytes    = ConstantBufferSize;// (constantBufferSize + 255) & ~255; // CB size is required to be 256-byte aligned.

    device->CreateConstantBufferView(&resourceView, handle);
  }

  ~Direct3D12ConstantBufferView()
  {
    if (resource) {
      resource->Release();
      resource = NULL;
    }
  }
  
  
  
  ID3D12Resource* getConstantBuffer()
  {
    return resource;
  }

  operator D3D12_CPU_DESCRIPTOR_HANDLE()
  {
    return handle;
  }
  
  operator D3D12_CONSTANT_BUFFER_VIEW_DESC*()
  {
    return &resourceView;
  }
 

  void update(void* constantBuffer, UINT constantBufferSize)
  {
    if (constantBuffer != nullptr && constantBufferSize > 0) {
      void* mapped = NULL;

      resource->Map( 0, nullptr, (void**)&mapped);

      memcpy(mapped, (void*)constantBuffer, constantBufferSize );
      resource->Unmap(0, nullptr);
    } else {
      throw IException("Invalid parameters.");
    }
  }
  
  int getHandleIndex()
  {
    return HandleIndex;
  }
};

}

