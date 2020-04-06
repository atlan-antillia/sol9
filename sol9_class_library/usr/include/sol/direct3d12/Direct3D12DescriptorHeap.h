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
 *  Direct3D12DescriptorHeap.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Pageable.h>

namespace SOL {

class Direct3D12DescriptorHeap : public Direct3D12Pageable {
    
public:
  Direct3D12DescriptorHeap()
    :Direct3D12Pageable()
  {
  }

  Direct3D12DescriptorHeap(
          __in ID3D12Device*              device,
          __in UINT                       bufferCount,
          __in D3D12_DESCRIPTOR_HEAP_TYPE type,
          __in D3D12_DESCRIPTOR_HEAP_FLAGS flag=D3D12_DESCRIPTOR_HEAP_FLAG_NONE)
  {
    if (device == nullptr) {
      throw IException("Invalid parameter. iD3D12Device is NULL.");
    }
    //1 Define a descriptorHeap description
    D3D12_DESCRIPTOR_HEAP_DESC desc;
      memset(&desc, 0, sizeof(desc));
      desc.NumDescriptors = bufferCount;
      desc.Type           = type;
      desc.Flags          = flag;
      desc.NodeMask       = 0;
  
    createDescriptorHeap(device, &desc);
  }
  
  
  Direct3D12DescriptorHeap(
    __in ID3D12Device*                     device, 
    __in const D3D12_DESCRIPTOR_HEAP_DESC* desc)
  :Direct3D12Pageable()
  {
    if (device == nullptr || desc == nullptr) {
      throw IException("Invalid parameter.");
    }

    createDescriptorHeap(device, desc);
  }
  
  void createDescriptorHeap(
    __in ID3D12Device*                     device, 
    __in const D3D12_DESCRIPTOR_HEAP_DESC* desc)
  {
    ID3D12DescriptorHeap* descriptorHeap = NULL;

    if (device && desc) {
      HRESULT hr = device -> CreateDescriptorHeap( 
            desc,
            IID_PPV_ARGS(&descriptorHeap));
      if (SUCCEEDED(hr)) {
        set(descriptorHeap);
      } else {
        throw IException("Failed to CreateDescriptorHeap. HRESULT(0x%lx)", hr);
      }
    } else {
      throw IException("Invalid parameter.");
    }
  }
  
  Direct3D12DescriptorHeap(
    __in ID3D12DescriptorHeap* descriptorHeap)
  :Direct3D12Pageable(descriptorHeap)
  {
  }
  
  ~Direct3D12DescriptorHeap()
  { 
  }

   
  operator ID3D12DescriptorHeap*()
  {
    return getDescriptorHeap();
  }

  ID3D12DescriptorHeap* getDescriptorHeap()
  {
    ID3D12DescriptorHeap* descriptorHeap = (ID3D12DescriptorHeap*)getIUnknown();
    if (descriptorHeap) {
        return descriptorHeap;
    } else {
      throw IException("ID3D12DescriptorHeap is NULL.");
    }
  }

  D3D12_DESCRIPTOR_HEAP_DESC getDesc()
  {
    ID3D12DescriptorHeap* descriptorHeap = getDescriptorHeap();
    return descriptorHeap->GetDesc();
  }

  D3D12_CPU_DESCRIPTOR_HANDLE getCPUDescriptorHandleForHeapStart()
  {
    ID3D12DescriptorHeap* descriptorHeap = getDescriptorHeap();
    return descriptorHeap->GetCPUDescriptorHandleForHeapStart();
  }

  D3D12_GPU_DESCRIPTOR_HANDLE getGPUDescriptorHandleForHeapStart()
  {
    ID3D12DescriptorHeap* descriptorHeap = getDescriptorHeap();
    return descriptorHeap->GetGPUDescriptorHandleForHeapStart();
  }

  operator D3D12_CPU_DESCRIPTOR_HANDLE()
  {
    return getCPUDescriptorHandleForHeapStart();    
  }

  operator D3D12_GPU_DESCRIPTOR_HANDLE()
  {
    return getGPUDescriptorHandleForHeapStart();
  }
};

}
    
