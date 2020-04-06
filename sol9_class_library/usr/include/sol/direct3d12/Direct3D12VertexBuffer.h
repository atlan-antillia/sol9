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
 *  Direct3D12VertexBuffer.h
 *
 *****************************************************************************/

// 2016/10/01

#pragma once

#include <sol/direct3d12/Direct3D12Buffer.h>

namespace SOL {

class Direct3D12VertexBuffer : public Direct3D12Buffer {
private:
  
  D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
  
public:
  Direct3D12VertexBuffer(
          __in ID3D12Device*   device,
          __in const void*     vertices,
          __in UINT            strideInBytes,
          __in UINT            sizeInBytes,
          __in D3D12_HEAP_TYPE type = D3D12_HEAP_TYPE_UPLOAD,
          __in DXGI_FORMAT     format=DXGI_FORMAT_UNKNOWN)
  :Direct3D12Buffer(device, vertices, sizeInBytes, type, format)
  {
    memset(&vertexBufferView, 0, sizeof(vertexBufferView));
    
    if (device == nullptr || vertices == nullptr || 
        strideInBytes <1 || sizeInBytes <1 ) {
      throw IException("Invalid parameters.");
    }
    vertexBufferView.BufferLocation = getGPUVirtualAddress();
    vertexBufferView.StrideInBytes  = strideInBytes;
    vertexBufferView.SizeInBytes    = sizeInBytes;    
  }

  ~Direct3D12VertexBuffer()
  {
  }


  operator D3D12_VERTEX_BUFFER_VIEW*()
  {
    return &vertexBufferView;
  }
  
};

}

