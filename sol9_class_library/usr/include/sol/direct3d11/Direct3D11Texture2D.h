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
 *  Direct3D11Texture2D.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11Resource.h>

namespace SOL {

class Direct3D11Texture2D : public Direct3D11Resource {
    
public:
  Direct3D11Texture2D(IDXGISwapChain* chain)
    :Direct3D11Resource()
  {
    ID3D11Texture2D* texture = NULL;
    HRESULT hr = chain -> GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&texture);
    if (SUCCEEDED(hr)) {
      set(texture);
    } else {
      throw IException("Failed to GetBuffer. HRESULT(0x%lx)", hr);
    }
  }
  
public:
  Direct3D11Texture2D(
      __in  ID3D11Device* device,
      __in  const D3D11_TEXTURE2D_DESC *pDesc,
      __in  const D3D11_SUBRESOURCE_DATA *pInitialData = NULL)
    :Direct3D11Resource()
  {
    if (device) {
      ID3D11Texture2D* texture2D;
      HRESULT hr = device -> CreateTexture2D( 
              pDesc,
              pInitialData,
              &texture2D);
      if (SUCCEEDED(hr)) {
        set(texture2D); 
      } else {
        throw IException("Failed to CreateTexture2D. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL.");
    }
  }

  ~Direct3D11Texture2D()
  {
  }

  operator ID3D11Texture2D*()
  {
    return getTexture2D();
  }
  
  ID3D11Texture2D* getTexture2D()
  {
    ID3D11Texture2D* texture = (ID3D11Texture2D*)getIUnknown();
    if (texture) {
        return texture;
    } else {
      throw IException("ID3D11Texture2D is NULL.");
    }
  }
  
  void getDesc( 
            __out  D3D11_TEXTURE2D_DESC *pDesc)
  {
    ID3D11Texture2D* texture = getTexture2D();
    texture -> GetDesc(pDesc);
  }
        
};

}
