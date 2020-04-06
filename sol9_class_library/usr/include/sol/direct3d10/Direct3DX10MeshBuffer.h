/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Direct3DX10MeshBuffer.h
 *
 *****************************************************************************/

#pragma once


#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>
#include <d3d10_1.h>

#include <d3dx10.h>

namespace SOL {

class Direct3DX10MeshBuffer : public ComIUnknown {
public:
  Direct3DX10MeshBuffer(ID3DX10MeshBuffer* buffer)
  :ComIUnknown()
  {
  }
  
  ~Direct3DX10MeshBuffer()
  {
  }
  
  operator   ID3DX10MeshBuffer*()
  {
    return getBuffer();
  }
  
  ID3DX10MeshBuffer* getBuffer()
  {
    ID3DX10MeshBuffer* buffer = (ID3DX10MeshBuffer*)getIUnknown();
    if (buffer) {
      return buffer;
    } else {
      throw IException("ID3DX10MeshBuffer is NULL.");
    }
  }
  
  void map(void **ppData, SIZE_T *pSize)
  {
    ID3DX10MeshBuffer* buffer = getBuffer();
    HRESULT hr = buffer -> Map(ppData, pSize);
    if (FAILED(hr)) {
      throw IException("Failed to Map. HRESULT(0x%lx)", hr);
    }
  }
  
  void unmap()
  {
    ID3DX10MeshBuffer* buffer = getBuffer();
    HRESULT hr = buffer -> Unmap();
    if (FAILED(hr)) {
      throw IException("Failed to Unmap. HRESULT(0x%lx)", hr);
    }
  }

  SIZE_T getSize()
  {
    ID3DX10MeshBuffer* buffer = getBuffer();
    return buffer -> GetSize();
  }
  
};

}
