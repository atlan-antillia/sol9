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
 *  Direct3DX10Sprite.h
 *
 *****************************************************************************/

#pragma once

#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d3d10_1.h>
#include <d3dx10.h>


namespace SOL {

class Direct3DX10Sprite : public ComIUnknown {

public:
  Direct3DX10Sprite(
      ID3D10Device* pDevice, 
      UINT         cDeviceBufferSize)
  :ComIUnknown()
  {
    ID3DX10Sprite* sprite = NULL;
    HRESULT hr = D3DX10CreateSprite( 
        pDevice, 
        cDeviceBufferSize,
        &sprite);
    if (SUCCEEDED(hr)) {
      set(sprite);
    } else {
      throw IException("Failed to D3DX10CreateSprite. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct3DX10Sprite()
  {
  }
  
  operator  ID3DX10Sprite*()
  {
    return getSprite();
  }
  
  ID3DX10Sprite* getSprite()
  {
    ID3DX10Sprite* sprite = (ID3DX10Sprite*)getIUnknown();
    if (sprite) {
      return sprite;
    } else {
      throw IException("ID3DX10Sprite is NULL.");
    }
  }
    
 
  void begin(UINT flags)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> Begin(flags);
    if (FAILED(hr)) {
      throw IException("Failed to Begin. HRESULT(0x%lx)", hr);
    }
  }
  
/*
typedef struct _D3DX10_SPRITE
{
    D3DXMATRIX  matWorld;

    D3DXVECTOR2 TexCoord;
    D3DXVECTOR2 TexSize;

    D3DXCOLOR   ColorModulate;

    ID3D10ShaderResourceView *pTexture;
    UINT        TextureIndex;
} D3DX10_SPRITE;
  */
  void drawSpritesBuffered(D3DX10_SPRITE *pSprites, UINT cSprites)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> DrawSpritesBuffered(pSprites, cSprites);
    if (FAILED(hr)) {
      throw IException("Failed to DrawSpritesBuffered. HRESULT(0x%lx)", hr);
    }
  }

  void flush()
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> Flush();
    if (FAILED(hr)) {
      throw IException("Failed to Flush. HRESULT(0x%lx)", hr);
    }
  }
  

  void drawSpritesImmediate(D3DX10_SPRITE *pSprites, UINT cSprites, UINT cbSprite, UINT flags)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> DrawSpritesImmediate(pSprites, cSprites, cbSprite, flags);
    if (FAILED(hr)) {
      throw IException("Failed to DrawSpritesImmediate. HRESULT(0x%lx)", hr);
    }
  }

  void end()
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> End();
    if (FAILED(hr)) {
      throw IException("Failed to End. HRESULT(0x%lx)", hr);
    }
  }

  void getViewTransform(D3DXMATRIX *pViewTransform)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> GetViewTransform(pViewTransform);
    if (FAILED(hr)) {
      throw IException("Failed to GetViewTransform. HRESULT(0x%lx)", hr);
    }
  }

  void setViewTransform(D3DXMATRIX *pViewTransform)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> SetViewTransform(pViewTransform);
    if (FAILED(hr)) {
      throw IException("Failed to SetViewTransform. HRESULT(0x%lx)", hr);
    }
  }

  void getProjectionTransform(D3DXMATRIX *pProjectionTransform)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> GetProjectionTransform(pProjectionTransform);
    if (FAILED(hr)) {
      throw IException("Failed to GetProjectionTransform. HRESULT(0x%lx)", hr);
    }
  }

  void setProjectionTransform(D3DXMATRIX *pProjectionTransform)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> SetProjectionTransform(pProjectionTransform);
    if (FAILED(hr)) {
      throw IException("Failed to SetProjectionTransform. HRESULT(0x%lx)", hr);
    }
  }

  void getDevice(ID3D10Device** ppDevice)
  {
    ID3DX10Sprite* sprite = getSprite();
    HRESULT hr = sprite -> GetDevice(ppDevice);
    if (FAILED(hr)) {
      throw IException("Failed to GetDevice. HRESULT(0x%lx)", hr);
    }
  }

};


}

