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
 *  Direct3DX11EffectConstantBuffer.h
 *
 *****************************************************************************/

//2015/12/01

#pragma once

#include <sol/direct3d11/Direct3DX11EffectVariable.h>
;
namespace SOL {

class Direct3DX11EffectConstantBuffer: public Direct3DX11EffectVariable {
public:
  Direct3DX11EffectConstantBuffer(ID3DX11EffectConstantBuffer* variable)
  :Direct3DX11EffectVariable()
  {
    if (variable) {
      set(variable);
    } else {
      throw IException("Invalid argument. ID3DX11EffectConstantBuffer is NULL.");
    }
  }
  
  ~Direct3DX11EffectConstantBuffer()
  {
  }
    
  operator ID3DX11EffectConstantBuffer*()
  {
    return getConstantBuffer();  
  }
  
  ID3DX11EffectConstantBuffer* getConstantBuffer()
  {
    ID3DX11EffectConstantBuffer* variable = (ID3DX11EffectConstantBuffer*)getInterface();
    if (variable) {
      return variable;
    } else {
      throw IException("ID3DX11EffectConstantBuffer is NULL.");
    }
  }
  
    
  ID3DX11EffectType* getType()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetType();
  }
  
  void getDesc(D3DX11_EFFECT_VARIABLE_DESC *pDesc)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getDesc(D3DX11_EFFECT_VARIABLE_DESC& desc)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  ////////////////////////////////////////////////////////////////
  ID3DX11EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetAnnotationByIndex(index);
  }
  
  ID3DX11EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetAnnotationByName(name);
  }
    
  ID3DX11EffectVariable* getMemberByIndex(UINT index)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetMemberByIndex(index);
  }
  
  ID3DX11EffectVariable* getMemberByName(LPCSTR name)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetMemberByName(name);
  }
  
  ID3DX11EffectVariable* getMemberBySemantic(LPCSTR semantic)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetMemberBySemantic(semantic);
  }
    
  ID3DX11EffectVariable* getElement(UINT index)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable ->  GetElement(index);
  }
    
  ID3DX11EffectConstantBuffer* getParentConstantBuffer()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetParentConstantBuffer();
  }
    
  ID3DX11EffectScalarVariable* asScalar()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsScalar();
  }
  
  ID3DX11EffectVectorVariable* asVector()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsVector();
  }
  
  ID3DX11EffectMatrixVariable* asMatrix()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsMatrix();
  }
  
  ID3DX11EffectStringVariable* asString()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsString();
  }
  
  ID3DX11EffectShaderResourceVariable* asShaderResource()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsShaderResource();
  }
  
  ID3DX11EffectRenderTargetViewVariable* asRenderTargetView()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsRenderTargetView();
  }
  
  ID3DX11EffectDepthStencilViewVariable* asDepthStencilView()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsDepthStencilView();
  }
  
  ID3DX11EffectConstantBuffer* asConstantBuffer()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsConstantBuffer();
  }
  
  ID3DX11EffectShaderVariable* asShader()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsShader();
  }
  
  ID3DX11EffectBlendVariable* asBlend()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsBlend();
  }
  
  ID3DX11EffectDepthStencilVariable* asDepthStencil()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsDepthStencil();
  }
  
  ID3DX11EffectRasterizerVariable* asRasterizer()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsRasterizer();
  }
  
  ID3DX11EffectSamplerVariable* asSampler()
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsSampler();
  }
    
  void setRawValue(void *pData, UINT offset, UINT count)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> SetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  void getRawValue(void *pData, UINT offset, UINT count)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  void setConstantBuffer(ID3D11Buffer *pConstantBuffer)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> SetConstantBuffer(pConstantBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to SetConstantBuffer. HRESULT(0x%lx)", hr);
    }
  }
  
  void getConstantBuffer(ID3D11Buffer **ppConstantBuffer)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetConstantBuffer(ppConstantBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetConstantBuffer. HRESULT(0x%lx)", hr);
    }
  }
    
  void setTextureBuffer(ID3D11ShaderResourceView *pTextureBuffer)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> SetTextureBuffer(pTextureBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to SetTextureBuffer. HRESULT(0x%lx)", hr);
    }
  }
  
  void getTextureBuffer(ID3D11ShaderResourceView **ppTextureBuffer)
  {
    ID3DX11EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetTextureBuffer(ppTextureBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetTextureBuffer. HRESULT(0x%lx)", hr);
    }
  }
};

}
