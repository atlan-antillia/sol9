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
 *  Direct3D10Buffer.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10Resource.h>

namespace SOL {

class Direct3D10Buffer : public Direct3D10Resource {
public:
  Direct3D10Buffer(
      __in  ID3D10Device* device,
      __in  const D3D10_BUFFER_DESC *pDesc,
      __in_opt  const D3D10_SUBRESOURCE_DATA *pInitialData
    )
  :Direct3D10Resource()
  {
    ID3D10Buffer* buffer = NULL;
    HRESULT hr = device -> CreateBuffer( 
        pDesc,
        pInitialData,
        &buffer);
    if (SUCCEEDED(hr)) {
      set(buffer);
    }
    if (FAILED(hr)) {
      throw IException("Failed to CreateBuffer. HRESULT(0x%lx)", hr)
    }
  }

  ~Direct3D10Buffer()
  {
  }

  operator ID3D10Buffer*()
  {
    return getBuffer();
  }

  ID3D10Buffer* getBuffer()
  {
    ID3D10Buffer* buffer = (ID3D10Buffer*)getIUnknown();
    if (buffer) {
      return buffer;
    } else {
      throw IException("ID3D10Buffer is NULL.");
    }
  }

  void map( 
            __in  D3D10_MAP mapType,
            __in  UINT mapFlags,
            __out  void **ppData)
  {
    ID3D10Buffer* buffer = getBuffer();
    HRESULT hr = buffer -> Map( 
            mapType,
            mapFlags,
           ppData);
    if (FAILED(hr)) {
      throw IException("Failed to Map. HRESULT(0x%lx)", hr)
    }
  }     

  void unmap()
  {
    ID3D10Buffer* buffer = getBuffer();
    buffer -> Unmap();
  }

  void  getDesc( 
            __out  D3D10_BUFFER_DESC *pDesc)
   {
     ID3D10Buffer* buffer = getBuffer();
     buffer -> GetDesc(pDesc); 
   }
  
  void  getDesc( 
            __out  D3D10_BUFFER_DESC& desc)
   {
     ID3D10Buffer* buffer = getBuffer();
     buffer -> GetDesc(&desc); 
   }     
};
}
