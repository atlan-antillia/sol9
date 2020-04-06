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
 *  Direct3DX11EffectTechnique.h
 *
 *****************************************************************************/

#pragma once


#include <sol/com/ComInterface.h>
#include <sol/Exception.h>

#include <sol/direct3d11/Direct3D11Resource.h>
#include <sol/direct3d11/Direct3D11Blob.h>
#include <d3dx11effect.h>

#pragma comment( lib, "Effects11.lib" )  
#pragma comment( lib, "d3dcompiler.lib" )


namespace SOL {

class Direct3DX11EffectTechnique : public ComInterface {

public:
  Direct3DX11EffectTechnique(ID3DX11EffectTechnique* technique)
  :ComInterface()
  {
    if (technique) {
      set(technique);
    } else {
      throw IException("Invalid argument. ID3DX11EffectTechnique is NULL.");
    }
  }
  
  ~Direct3DX11EffectTechnique()
  {
  }
  
  operator ID3DX11EffectTechnique*()
  {
    return getTechinique();
  }
  
  ID3DX11EffectTechnique* getTechinique()
  {
    ID3DX11EffectTechnique* technique = (ID3DX11EffectTechnique*)getInterface();
    if (technique) {
      return technique;
    } else {
      throw IException("ID3DX11EffectTechnique is NULL.");
    }
  }
  
  
  BOOL isValid()
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    return technique -> IsValid();
  }
  
  void getDesc(D3DX11_TECHNIQUE_DESC *pDesc)
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    HRESULT hr = technique -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  void getDesc(D3DX11_TECHNIQUE_DESC& desc)
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    HRESULT hr = technique -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  ID3DX11EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    return technique -> GetAnnotationByIndex(index);
  }
  
  ID3DX11EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    return technique -> GetAnnotationByName(name);
  }
  
  ID3DX11EffectPass* getPassByIndex(UINT index)
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    return technique -> GetPassByIndex(index);
  }
  
  ID3DX11EffectPass* getPassByName(LPCSTR name)
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    return technique -> GetPassByName(name);
  }
  
  void computeStateBlockMask(D3DX11_STATE_BLOCK_MASK *pStateBlockMask)
  {
    ID3DX11EffectTechnique* technique = getTechinique();
    HRESULT hr = technique -> ComputeStateBlockMask(pStateBlockMask);
    if (FAILED(hr)) {
      throw IException("Failed to ComputeStateBlockMask. HRESULT(0x%lx)", hr);
    }
  }
};

}
