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
 *  Direct3DX11EffectMatrixVariable.h
 *
 *****************************************************************************/

#pragma once


#include <sol/direct3d11/Direct3DX11EffectVariable.h>

namespace SOL {

class Direct3DX11EffectMatrixVariable : public Direct3DX11EffectVariable {
public:
  Direct3DX11EffectMatrixVariable(ID3DX11EffectMatrixVariable* variable) 
  :Direct3DX11EffectVariable(variable)
  {
  }
  
  ~Direct3DX11EffectMatrixVariable() 
  {
  }
  
  operator ID3DX11EffectMatrixVariable*()
  {
    return getMatrixVariable();
  }
  
  ID3DX11EffectMatrixVariable* getMatrixVariable()
  {
    ID3DX11EffectMatrixVariable* variable = (ID3DX11EffectMatrixVariable*)getInterface();
    if (variable) {
      return variable;
    } else {
      throw IException("ID3DX11EffectMatrixVariable is NULL.");
    }
  }
  
  BOOL isValid()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> IsValid();
  }
  
  ID3DX11EffectType* getType()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetType();
  }
  
  void getDesc(D3DX11_EFFECT_VARIABLE_DESC *pDesc)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getDesc(D3DX11_EFFECT_VARIABLE_DESC& desc)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  ID3DX11EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetAnnotationByIndex(index);
  }
  
  ID3DX11EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetAnnotationByName(name);
  }
    
  ID3DX11EffectVariable* getMemberByIndex(UINT index)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetMemberByIndex(index);
  }
  
  ID3DX11EffectVariable* getMemberByName(LPCSTR name)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetMemberByName(name);
  }
  
  ID3DX11EffectVariable* getMemberBySemantic(LPCSTR semantic)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetMemberBySemantic(semantic);
  }
    
  ID3DX11EffectVariable* getElement(UINT index)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetElement(index);
  }
    
  ID3DX11EffectConstantBuffer* getParentConstantBuffer()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> GetParentConstantBuffer();
  }
    
  ID3DX11EffectScalarVariable* asScalar()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsScalar();
  }
  
  ID3DX11EffectVectorVariable* asVector()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsVector();
  }
  
  ID3DX11EffectMatrixVariable* asMatrix()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsMatrix();
  }
  
  ID3DX11EffectStringVariable* asString()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsString();
  }
  
  ID3DX11EffectShaderResourceVariable* asShaderResource()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsShaderResource();
  }
  
  ID3DX11EffectRenderTargetViewVariable* asRenderTargetView()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsRenderTargetView();
  }
  
  ID3DX11EffectDepthStencilViewVariable* asDepthStencilView()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsDepthStencilView();
  }
  
  ID3DX11EffectConstantBuffer* asConstantBuffer()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsConstantBuffer();
  }
  
  ID3DX11EffectShaderVariable* asShader()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsShader();
  }
  
  ID3DX11EffectBlendVariable* asBlend()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsBlend();
  }
  
  ID3DX11EffectDepthStencilVariable* asDepthStencil()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsDepthStencil();
  }
  
  ID3DX11EffectRasterizerVariable* asRasterizer()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsRasterizer();
  }
  
  ID3DX11EffectSamplerVariable* asSampler()
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    return variable -> AsSampler();
  }
    
  void setRawValue(void *pData, UINT byteOffset, UINT byteCount)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> SetRawValue(pData, byteOffset, byteCount);
    if (FAILED(hr)) {
      throw IException("Failed to SetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  void getRawValue(void *pData, UINT byteOffset, UINT byteCount)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> GetRawValue(pData, byteOffset, byteCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetRawValue. HRESULT(0x%lx)", hr);
    }
  }
    
  void setMatrix(float *pData)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> SetMatrix(pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetMatrix. HRESULT(0x%lx)", hr);
    }
  }
  
  void getMatrix(float *pData)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> GetMatrix(pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetMatrix. HRESULT(0x%lx)", hr);
    }
  }
    
  void setMatrixArray(float *pData, UINT offset, UINT count)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> SetMatrixArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetMatrixArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void getMatrixArray(float *pData, UINT offset, UINT count)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> GetMatrixArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetMatrixArray. HRESULT(0x%lx)", hr);
    }
  }
    
  void setMatrixTranspose(float *pData)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> SetMatrixTranspose(pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetMatrixTranspose. HRESULT(0x%lx)", hr);
    }
  }
  
  void getMatrixTranspose(float *pData)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> GetMatrixTranspose(pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetMatrixTranspose. HRESULT(0x%lx)", hr);
    }
  }
    
  void setMatrixTransposeArray(float *pData, UINT offset, UINT count)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> SetMatrixTransposeArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetMatrixTransposeArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void getMatrixTransposeArray(float *pData, UINT offset, UINT count)
  {
    ID3DX11EffectMatrixVariable* variable = getMatrixVariable();
    HRESULT hr = variable -> GetMatrixTransposeArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetMatrixTransposeArray. HRESULT(0x%lx)", hr);
    }
  }
};

}

