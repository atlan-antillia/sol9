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
 *  Direct3D10EffectConstantBuffer.h
 *
 *****************************************************************************/

//2015/12/01

#pragma once

#include <sol/direct3d10/Direct3D10EffectVariable.h>
;
namespace SOL {

class Direct3D10EffectConstantBuffer: public Direct3D10EffectVariable {
public:
  Direct3D10EffectConstantBuffer(ID3D10EffectConstantBuffer* variable)
  :Direct3D10EffectVariable()
  {
    if (variable) {
      set(variable);
    } else {
      throw IException("Invalid argument. ID3D10EffectConstantBuffer is NULL.");
    }
  }
  
  ~Direct3D10EffectConstantBuffer()
  {
  }
    
  operator ID3D10EffectConstantBuffer*()
  {
    return getConstantBuffer();  
  }
  
  ID3D10EffectConstantBuffer* getConstantBuffer()
  {
    ID3D10EffectConstantBuffer* variable = (ID3D10EffectConstantBuffer*)getInterface();
    if (variable) {
      return variable;
    } else {
      throw IException("ID3D10EffectConstantBuffer is NULL.");
    }
  }
  
    
  ID3D10EffectType* getType()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetType();
  }
  
  void getDesc(D3D10_EFFECT_VARIABLE_DESC *pDesc)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getDesc(D3D10_EFFECT_VARIABLE_DESC& desc)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  ////////////////////////////////////////////////////////////////
  ID3D10EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetAnnotationByIndex(index);
  }
  
  ID3D10EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetAnnotationByName(name);
  }
    
  ID3D10EffectVariable* getMemberByIndex(UINT index)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetMemberByIndex(index);
  }
  
  ID3D10EffectVariable* getMemberByName(LPCSTR name)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetMemberByName(name);
  }
  
  ID3D10EffectVariable* getMemberBySemantic(LPCSTR semantic)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetMemberBySemantic(semantic);
  }
    
  ID3D10EffectVariable* getElement(UINT index)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable ->  GetElement(index);
  }
    
  ID3D10EffectConstantBuffer* getParentConstantBuffer()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> GetParentConstantBuffer();
  }
    
  ID3D10EffectScalarVariable* asScalar()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsScalar();
  }
  
  ID3D10EffectVectorVariable* asVector()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsVector();
  }
  
  ID3D10EffectMatrixVariable* asMatrix()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsMatrix();
  }
  
  ID3D10EffectStringVariable* asString()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsString();
  }
  
  ID3D10EffectShaderResourceVariable* asShaderResource()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsShaderResource();
  }
  
  ID3D10EffectRenderTargetViewVariable* asRenderTargetView()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsRenderTargetView();
  }
  
  ID3D10EffectDepthStencilViewVariable* asDepthStencilView()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsDepthStencilView();
  }
  
  ID3D10EffectConstantBuffer* asConstantBuffer()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsConstantBuffer();
  }
  
  ID3D10EffectShaderVariable* asShader()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsShader();
  }
  
  ID3D10EffectBlendVariable* asBlend()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsBlend();
  }
  
  ID3D10EffectDepthStencilVariable* asDepthStencil()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsDepthStencil();
  }
  
  ID3D10EffectRasterizerVariable* asRasterizer()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsRasterizer();
  }
  
  ID3D10EffectSamplerVariable* asSampler()
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    return variable -> AsSampler();
  }
    
  void setRawValue(void *pData, UINT offset, UINT count)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> SetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  void getRawValue(void *pData, UINT offset, UINT count)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  void setConstantBuffer(ID3D10Buffer *pConstantBuffer)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> SetConstantBuffer(pConstantBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to SetConstantBuffer. HRESULT(0x%lx)", hr);
    }
  }
  
  void getConstantBuffer(ID3D10Buffer **ppConstantBuffer)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetConstantBuffer(ppConstantBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetConstantBuffer. HRESULT(0x%lx)", hr);
    }
  }
    
  void setTextureBuffer(ID3D10ShaderResourceView *pTextureBuffer)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> SetTextureBuffer(pTextureBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to SetTextureBuffer. HRESULT(0x%lx)", hr);
    }
  }
  
  void getTextureBuffer(ID3D10ShaderResourceView **ppTextureBuffer)
  {
    ID3D10EffectConstantBuffer* variable = getConstantBuffer();
    HRESULT hr = variable -> GetTextureBuffer(ppTextureBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to GetTextureBuffer. HRESULT(0x%lx)", hr);
    }
  }
};

}
