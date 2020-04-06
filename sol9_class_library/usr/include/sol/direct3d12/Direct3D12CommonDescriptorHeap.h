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
 *  Direct3D12CommonDescriptorHeap.h
 *
 *****************************************************************************/

// 2016/09/25
// This will create a common descriptor heap for 
//ConstantBufferView, ShaderResourceView, and UnorderedAccessView, 
//specifying D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV to type field of D3D12_DESCRIPTOR_HEAP_DESC.

#pragma once

#include <sol/direct3d12/Direct3D12Pageable.h>

namespace SOL {

typedef enum {
  CBV_HANDLE = 0,
  SRV_HANDLE = 1,
  UOV_HANDLE = 2,
} DESCRIPTOR_HEAP_INDEX; //DescriptorHeapIndex;
  
class Direct3D12CommonDescriptorHeap : public Direct3D12DescriptorHeap {
private:
  
  static const D3D12_DESCRIPTOR_HEAP_TYPE type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

  UINT                          bufferCount;

  D3D12_CPU_DESCRIPTOR_HANDLE    cpuStart;

  D3D12_GPU_DESCRIPTOR_HANDLE    gpuStart;
  
  D3D12_CPU_DESCRIPTOR_HANDLE*  cpuHandles;
  D3D12_GPU_DESCRIPTOR_HANDLE*  gpuHandles;
  UINT                          incrementSize;


public:
  Direct3D12CommonDescriptorHeap()
    :Direct3D12DescriptorHeap(),
  cpuHandles(NULL),
  gpuHandles(NULL)
  {
  }

  Direct3D12CommonDescriptorHeap(
          __in ID3D12Device* device,
          __in UINT count = 2)   //1: CBV, 2 :CBV and SRV, 3: CBV, SRV, and UAV
  :Direct3D12DescriptorHeap(),

  bufferCount(count),
  cpuHandles(NULL)
  {
    if (device == nullptr) {
      throw IException("Invalid parameter. ID3D12Device is NULL.");
    }
    if (bufferCount < 1) {
      throw IException("Invalid bufferCount.");
    }
    cpuHandles = new D3D12_CPU_DESCRIPTOR_HANDLE[bufferCount];
    gpuHandles = new D3D12_GPU_DESCRIPTOR_HANDLE[bufferCount];
    
    //1 Define a descriptorHeap description
    D3D12_DESCRIPTOR_HEAP_DESC desc;
      memset(&desc, 0, sizeof(desc));
      desc.NumDescriptors = bufferCount;
      desc.Type           = type;  //D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
      desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
      desc.NodeMask       = 0;
  
    ID3D12DescriptorHeap* descriptorHeap = NULL;

    HRESULT hr = device -> CreateDescriptorHeap( 
            &desc,
            IID_PPV_ARGS(&descriptorHeap));
    if (SUCCEEDED(hr)) {
      set(descriptorHeap);
    } else {
      throw IException("Failed to CreateDescriptorHeap. HRESULT(0x%lx)", hr);
    }
    
    D3D12_CPU_DESCRIPTOR_HANDLE cheapStart = getCPUDescriptorHandleForHeapStart();
    D3D12_GPU_DESCRIPTOR_HANDLE gheapStart = getGPUDescriptorHandleForHeapStart();

    cpuStart = getCPUDescriptorHandleForHeapStart();
    gpuStart = getGPUDescriptorHandleForHeapStart();
    
    
    //UINT 
    incrementSize = device->GetDescriptorHandleIncrementSize(type);
    for (UINT i = 0; i<bufferCount; i++) {
      cpuHandles[i]     = cheapStart;
      cpuHandles[i].ptr +=  (incrementSize * i);
      gpuHandles[i]     = gheapStart;
      gpuHandles[i].ptr += (incrementSize * i);
    }
  }
    
  ~Direct3D12CommonDescriptorHeap()
  {
    delete [] cpuHandles;
    delete [] gpuHandles;
    cpuHandles = NULL;
    gpuHandles = NULL;
  }

  
  //206/11/12
  D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandle(DESCRIPTOR_HEAP_INDEX index)
  {
    return getCPUHandle((UINT)index);
  }
  
  D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandle(UINT index)
  {
    if (index >=0 && index< bufferCount) {
      return cpuHandles[index];
    } else {
      throw IException("Invalid parameter. index(%d)", index);
    }
  }
  
  //2016/11/12
  D3D12_GPU_DESCRIPTOR_HANDLE getGPUHandle(DESCRIPTOR_HEAP_INDEX index)
  {
    return getGPUHandle((UINT)index);
  }
  
  D3D12_GPU_DESCRIPTOR_HANDLE getGPUHandle(UINT index)
  {
    if (index >=0 && index< bufferCount) {
      return gpuHandles[index];
    } else {
      throw IException("Invalid parameter. index(%d)", index);
    }
  }
  
  UINT getIncrementSize()
  {
    return incrementSize;
  }
};

}
    
