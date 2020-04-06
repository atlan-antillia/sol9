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
 *  Direct3D12Buffer.h
 *
 *****************************************************************************/

// 2016/10/10

#pragma once

#include <sol/direct3d12/Direct3D12Resource.h>

namespace SOL {

class Direct3D12Buffer : public Direct3D12Resource {
private:
  UINT bufferSize;
  
public:
  Direct3D12Buffer(
           __in ID3D12Device*    device,
           __in const void*      data,
               UINT              sizeInBytes, 
               D3D12_HEAP_TYPE   type = D3D12_HEAP_TYPE_UPLOAD,
               DXGI_FORMAT       format=DXGI_FORMAT_UNKNOWN)
  :Direct3D12Resource(),
  bufferSize(sizeInBytes)
  {
    if (device == nullptr || data == nullptr || sizeInBytes <1 ) {
      throw IException("Invalid parameters.");
    }
 
    D3D12_HEAP_PROPERTIES heapProp;
      memset(&heapProp, 0, sizeof(heapProp));
      heapProp.Type                 = type; //D3D12_HEAP_TYPE_UPLOAD; //UPLOAD
      heapProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
      heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
      heapProp.CreationNodeMask     = 1;
      heapProp.VisibleNodeMask      = 1;
    
    D3D12_RESOURCE_DESC resDesc;
      memset(&resDesc, 0, sizeof(resDesc));
      resDesc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
      resDesc.Alignment          = 0;
      resDesc.Width              = 256; //2016/11/14 sizeInBytes;
      resDesc.Height             = 1;
      resDesc.DepthOrArraySize   = 1;
      resDesc.MipLevels          = 1;
      resDesc.Format             = format; //DXGI_FORMAT_UNKNOWN; //
      resDesc.SampleDesc.Count   = 1;
      resDesc.SampleDesc.Quality = 0;
      resDesc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
      resDesc.Flags              = D3D12_RESOURCE_FLAG_NONE;

    createCommittedResource(device, 
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr);
    
    // Map resource to the desitination.
    unsigned char* destination = NULL;
    map(0, nullptr, (void**)&destination);
  
    // Do copy the data to the destination
    memcpy(destination, data, sizeInBytes);
    // Unmap
    unmap(0, nullptr);  
  }

public:
  Direct3D12Buffer(
           __in ID3D12Device*          device,
           __in D3D12_HEAP_PROPERTIES* heapProp,
           __in D3D12_RESOURCE_DESC*   resDesc,
           __in const void*            data,
               UINT                    sizeInBytes, 
               D3D12_HEAP_TYPE   type = D3D12_HEAP_TYPE_UPLOAD,
               DXGI_FORMAT       format=DXGI_FORMAT_UNKNOWN)
  :Direct3D12Resource(),
  bufferSize(sizeInBytes)
  {
    if (device == nullptr || heapProp == nullptr || resDesc == nullptr || 
        data == nullptr || sizeInBytes <1 ) {
      throw IException("Invalid parameters.");
    }
 
    createCommittedResource(device, 
        heapProp,
        D3D12_HEAP_FLAG_NONE,
        resDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr);
    
    // Map resource to the desitination.
    unsigned char* destination = NULL;
    map(0, nullptr, (void**)&destination);
  
    // Do copy the data to the destination
    memcpy(destination, data, sizeInBytes);
    // Unmap
    unmap(0, nullptr);  
  }

  ~Direct3D12Buffer()
  {
  }
 
  virtual UINT getBufferSize()
  {
    return bufferSize;
  }
};

}

