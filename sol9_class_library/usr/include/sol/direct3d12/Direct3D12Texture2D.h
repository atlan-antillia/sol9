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
 *  Direct3D12Texture2D.h
 *
 *****************************************************************************/

// 2016/10/01

#pragma once

#include <sol/direct3d12/Direct3D12Resource.h>

namespace SOL {
  
class Direct3D12Texture2D : public Direct3D12Resource {

public:
  Direct3D12Texture2D(
    __in  ID3D12Device* device,
    __in  UINT          width,
    __in  UINT          height,
    __in  DXGI_FORMAT  format = DXGI_FORMAT_R8G8B8A8_UNORM) 
    :Direct3D12Resource()
  {
    if (device == nullptr) {
      throw IException("Invalid parameter.");
    }


    D3D12_HEAP_PROPERTIES heapProp;
    memset(&heapProp, 0, sizeof(heapProp));
    heapProp.Type                 = D3D12_HEAP_TYPE_DEFAULT;
    heapProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProp.CreationNodeMask     = 1; //11/03
    heapProp.VisibleNodeMask      = 1;

    D3D12_RESOURCE_DESC resDesc;
    memset(&resDesc, 0, sizeof(resDesc));

    resDesc.Dimension         = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resDesc.Width             = width;
    resDesc.Height            = height;
    resDesc.DepthOrArraySize  = 1;
    resDesc.MipLevels         = 1;
    resDesc.Format            = format; //DXGI_FORMAT_R8G8B8A8_UNORM;
    resDesc.Flags             = D3D12_RESOURCE_FLAG_NONE; //2016/11/02

    resDesc.Layout            = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resDesc.SampleDesc.Count  = 1;
    resDesc.SampleDesc.Quality = 0;

    createCommittedResource(device,
      &heapProp,
      D3D12_HEAP_FLAG_NONE,
      &resDesc,
      D3D12_RESOURCE_STATE_GENERIC_READ, 
      
      //D3D12_RESOURCE_STATE_COPY_DEST,
      nullptr);
  }


  ~Direct3D12Texture2D()
  {
  }

};

}
