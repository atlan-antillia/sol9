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
 *  Direct3D10Texture3D.h
 *
 *****************************************************************************/

#pragma once


#include <sol/direct3d10/Direct3D10Resource.h>

namespace SOL {
  
class Direct3D10Texture3D : public Direct3D10Resource {
public:
  Direct3D10Texture3D(
    ID3D10Device*           pDevice,
    LPCTSTR                 pSrcFile,
    D3DX10_IMAGE_LOAD_INFO* pLoadInfo,
    ID3DX10ThreadPump*      pPump,
    HRESULT*               pHResult)
  :Direct3D10Resource(
    pDevice,
    pSrcFile,
    pLoadInfo,
    pPump,
    pHResult)
  {
  }
  
public:
  Direct3D10Texture3D(ID3D10Device* device,
        __in  const D3D10_TEXTURE3D_DESC *desc,
        __in  const D3D10_SUBRESOURCE_DATA *initialData)
  :Direct3D10Resource()
  {
   ID3D10Texture3D* texture = NULL;
    HRESULT hr = device -> CreateTexture3D(desc, 
      initialData, &texture );
    if (SUCCEEDED(hr)) {
      set(texture);
    } else {
      throw IException("Failed to CreateTexture3D. HRESULT(0x%lx)", hr)
    }
  }
 
  ~Direct3D10Texture3D() 
  {
  }
  
  operator ID3D10Texture3D*()
  {
    return getTexture3D();
  }
  
  ID3D10Texture3D* getTexture3D()
  {
    ID3D10Texture3D* texture3D = (ID3D10Texture3D*) getIUnknown();
    if (texture3D) {
      return texture3D;
    } else {
      throw IException("ID3D10Texture3D is NULL.");
    }
  }
   

public:
  void map( 
            __in  UINT subresource,
            __in  D3D10_MAP mapType,
            __in  UINT mapFlags,
            __out  D3D10_MAPPED_TEXTURE3D *pMappedTex3D)
  {
    ID3D10Texture3D* texture3D = getTexture3D();
    HRESULT hr = texture3D -> Map( 
            subresource,
            mapType,
            mapFlags,
            pMappedTex3D);
    if (FAILED(hr)) {
      throw IException("Failed to Map, HRESULT(0x%lx)", hr);
    }
  }
  
  //void        
  void unmap( 
            __in  UINT subresource)
  {
    ID3D10Texture3D* texture3D = getTexture3D();
    texture3D -> Unmap( 
            subresource);
  }
  

  void  getDesc( 
            __out  D3D10_TEXTURE3D_DESC *pDesc)
  {
    ID3D10Texture3D* texture3D = getTexture3D();
    texture3D -> GetDesc( 
            pDesc);
  }

  void  getDesc( 
            __out  D3D10_TEXTURE3D_DESC& desc)
  {
    ID3D10Texture3D* texture3D = getTexture3D();
    texture3D -> GetDesc( 
            &desc);
  }
        
};
}

    