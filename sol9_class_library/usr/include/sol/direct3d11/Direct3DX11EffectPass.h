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
 *  Direct3DX11EffectPass.h
 *
 *****************************************************************************/

#pragma once

#include <sol/com/ComInterface.h>

namespace SOL {

class Direct3DX11EffectPass :public ComInterface {
public:
  Direct3DX11EffectPass(ID3DX11EffectPass* pass)
  :ComInterface()
  {
    if(pass) {
      set(pass);
    } else {
      throw IException("Invalid argument. ID3DX11EffectPass is NULL");
    }
  }
  
  ~Direct3DX11EffectPass()
  {
  }
  
  operator ID3DX11EffectPass*()
  {
    return getPass();
  }
  
  ID3DX11EffectPass* getPass()
  {
    ID3DX11EffectPass* pass = (ID3DX11EffectPass*)getInterface();
    if (pass) {
      return pass;
    } else {
      throw IException("ID3DX11EffectPass is NULL.");
    }
  }
  
  BOOL isValid()
  {
    ID3DX11EffectPass* pass = getPass();
    return pass -> IsValid();
  }
  
  void getDesc(D3DX11_PASS_DESC *pDesc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
   
  void getDesc(D3DX11_PASS_DESC& desc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  void getVertexShaderDesc(D3DX11_PASS_SHADER_DESC *pDesc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetVertexShaderDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetVertexShaderDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getVertexShaderDesc(D3DX11_PASS_SHADER_DESC& desc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetVertexShaderDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetVertexShaderDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getGeometryShaderDesc(D3DX11_PASS_SHADER_DESC *pDesc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetGeometryShaderDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetGeometryShaderDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  void getGeometryShaderDesc(D3DX11_PASS_SHADER_DESC& desc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetGeometryShaderDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetGeometryShaderDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  void getPixelShaderDesc(D3DX11_PASS_SHADER_DESC *pDesc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetPixelShaderDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetPixelShaderDesc. HRESULT(0x%lx)", hr);
    }
  }
   
  void getPixelShaderDesc(D3DX11_PASS_SHADER_DESC& desc)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> GetPixelShaderDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetPixelShaderDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  ID3DX11EffectVariable*  getAnnotationByIndex(UINT index)
  {
    ID3DX11EffectPass* pass = getPass();
    return pass -> GetAnnotationByIndex(index);
  }
  
  ID3DX11EffectVariable*  getAnnotationByName(LPCSTR name)
  {
    ID3DX11EffectPass* pass = getPass();
    return pass -> GetAnnotationByName(name);
  }
    
  void apply(UINT flags, ID3D11DeviceContext* deviceContext)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass->Apply(flags, deviceContext);
    //HRESULT hr = pass -> Apply(flags);

    if (FAILED(hr)) {
      throw IException("Failed to Apply. HRESULT(0x%lx)", hr);
    }
  }
    
  void computeStateBlockMask(D3DX11_STATE_BLOCK_MASK *pStateBlockMask)
  {
    ID3DX11EffectPass* pass = getPass();
    HRESULT hr = pass -> ComputeStateBlockMask(pStateBlockMask);
    if (FAILED(hr)) {
      throw IException("Failed to ComputeStateBlockMask. HRESULT(0x%lx)", hr);
    }
  }

};

}

