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
 *  Direct3D10Effect.h
 *
 *****************************************************************************/

#pragma once


#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d3d10_1.h>

#include <d3dx10.h>

namespace SOL {

class Direct3D10EffectPool : public ComIUnknown {
public:
  
  Direct3D10EffectPool(
        ID3D10Device *pDevice,
        void *pData, 
        SIZE_T dataLength, 
        UINT fxFlags
        )
  :ComIUnknown()
  {
    ID3D10EffectPool *effectPool = NULL;
    HRESULT hr = D3D10CreateEffectPoolFromMemory(
          pData,  
          dataLength, 
          fxFlags, 
          pDevice,
        &effectPool);
     if (SUCCEEDED(hr)) {
      set(effectPool);
    } else {
      throw IException("Failed to D3D10CreateEffectPoolFromMemory. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct3D10EffectPool()
  {
  }
  
  
  operator ID3D10EffectPool*()
  {
    return getEffectPool();
  }
  
  ID3D10EffectPool* getEffectPool()
  {
    ID3D10EffectPool* pool = (ID3D10EffectPool*)getIUnknown();
    if (pool) {
      return pool;
    } else {
      throw IException("ID3D10EffectPool is NULL.");
    }
  }
  
  ID3D10Effect* asEffect()
  {
    ID3D10EffectPool* pool = getEffectPool();
    return pool -> AsEffect();
  }
    
};

}
