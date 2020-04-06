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
 *  Direct3D10Texture1D.h
 *
 *****************************************************************************/

#pragma once


#include <sol/direct3d10/Direct3D10Resource.h>

namespace SOL {
  
class Direct3D10Texture1D : public Direct3D10Resource {
public:
  Direct3D10Texture1D(ID3D10Device* device,
        __in  const D3D10_TEXTURE1D_DESC *desc,
        __in  const D3D10_SUBRESOURCE_DATA *initialData)
  :Direct3D10Resource()
  {
   ID3D10Texture1D* texture = NULL;
    HRESULT hr = device -> CreateTexture1D(desc, 
      initialData, &texture );
    if (SUCCEEDED(hr)) {
      set(texture);
    } else {
      throw IException("Failed to CreateTexture1D. HRESULT(0x%lx)", hr)
    }
  }
 
  ~Direct3D10Texture1D() 
  {
  }
  
  operator ID3D10Texture1D*()
  {
    return getTexture1D();
  }
  
  ID3D10Texture1D* getTexture1D()
  {
    ID3D10Texture1D* texture1D = (ID3D10Texture1D*) getIUnknown();
    if (texture1D) {
      return texture1D;
    } else {
      throw IException("ID3D10Texture1D is NULL.");
    }
  }
  
  void map( 
            __in  UINT subresource,
            __in  D3D10_MAP mapType,
            __in  UINT mapFlags,
            __out  void **ppData)
  {
    ID3D10Texture1D* texture1D = getTexture1D();
    HRESULT hr = texture1D -> Map( 
              subresource,
              mapType,
              mapFlags,
              ppData);
    if (FAILED(hr)) {
      throw IException("Failed to MAP. HRESULT(0x%lx)", hr); 
    }
  }
  
  void unmap( 
            __in  UINT subresource)
  {
    ID3D10Texture1D* texture1D = getTexture1D();
    texture1D -> Unmap( 
              subresource);
  }
        
  void getDesc( 
            __out  D3D10_TEXTURE1D_DESC *pDesc)
  {
    ID3D10Texture1D* texture1D = getTexture1D();
    texture1D -> GetDesc( 
              pDesc);
  }
  
  void getDesc( 
            __out  D3D10_TEXTURE1D_DESC& desc)
  {
    ID3D10Texture1D* texture1D = getTexture1D();
    texture1D -> GetDesc( 
              &desc);
  }
        
};
}
    