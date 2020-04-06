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
 *  Direct3DX11EffectScalarVariable.h
 *
 *****************************************************************************/

#pragma once


#include <sol/direct3d11/Direct3DX11EffectVariable.h>

namespace SOL {

class Direct3DX11EffectScalarVariable : public Direct3DX11EffectVariable {
public:
  Direct3DX11EffectScalarVariable(ID3DX11EffectScalarVariable* variable) 
  :Direct3DX11EffectVariable(variable)
  {
  }
  
  ~Direct3DX11EffectScalarVariable()
  {
  }
  
  operator ID3DX11EffectScalarVariable*()
  {
    return getScalarVariable();
  }
  
  ID3DX11EffectScalarVariable* getScalarVariable()
  {
    ID3DX11EffectScalarVariable* variable = (ID3DX11EffectScalarVariable*)getInterface();
    if (variable) {
      return variable;
    } else {
      throw IException("ID3DX11EffectScalarVariable is NULL."); 
    }
  }
  
  BOOL isValid()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> IsValid();
  }
  
  ID3DX11EffectType* getType()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetType();
  }
  
  void getDesc(D3DX11_EFFECT_VARIABLE_DESC *pDesc)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  void getDesc(D3DX11_EFFECT_VARIABLE_DESC& desc)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  ID3DX11EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetAnnotationByIndex(index);
  }
  
  ID3DX11EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetAnnotationByName(name);
  }
    
  ID3DX11EffectVariable* getMemberByIndex(UINT index)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetMemberByIndex(index);
  }
  
  ID3DX11EffectVariable* getMemberByName(LPCSTR name)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetMemberByName(name);
  }
  
  ID3DX11EffectVariable* getMemberBySemantic(LPCSTR semantic)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetMemberBySemantic(semantic);
  }
    
  ID3DX11EffectVariable* getElement(UINT index)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetElement(index);
  }
    
  ID3DX11EffectConstantBuffer* getParentConstantBuffer()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> GetParentConstantBuffer();
  }
    
  ID3DX11EffectScalarVariable* asScalar()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsScalar();
  }
  
  ID3DX11EffectVectorVariable* asVector()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsVector();
  }
  
  ID3DX11EffectMatrixVariable* asMatrix()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsMatrix();
  }
  
  ID3DX11EffectStringVariable* asString()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsString();
  }
  
  ID3DX11EffectShaderResourceVariable* asShaderResource()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsShaderResource();
  }
  
  ID3DX11EffectRenderTargetViewVariable* asRenderTargetView()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsRenderTargetView();
  }
  
  ID3DX11EffectDepthStencilViewVariable* asDepthStencilView()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsDepthStencilView();
  }
  
  ID3DX11EffectConstantBuffer* asConstantBuffer()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsConstantBuffer();
  }
  
  ID3DX11EffectShaderVariable* asShader()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsShader();
  }
  
  ID3DX11EffectBlendVariable* asBlend()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsBlend();
  }
  
  ID3DX11EffectDepthStencilVariable* asDepthStencil()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsDepthStencil();
  }
  
  ID3DX11EffectRasterizerVariable* asRasterizer()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsRasterizer();
  }
  
  ID3DX11EffectSamplerVariable* asSampler()
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    return variable -> AsSampler();
  }
    
  void setRawValue(void *pData, UINT byteOffset, UINT byteCount)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> SetRawValue(pData, byteOffset, byteCount);
    if (FAILED(hr)) {
      throw IException("Failed to SetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  void getRawValue(void *pData, UINT byteOffset, UINT byteCount)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetRawValue(pData, byteOffset, byteCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetRawValue. HRESULT(0x%lx)", hr);
    }
  }
    
  void setFloat(float value)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> SetFloat(value);
    if (FAILED(hr)) {
      throw IException("Failed to SetFloat. HRESULT(0x%lx)", hr);
    }
  }
  
  void getFloat(float *pValue)    
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetFloat(pValue);
    if (FAILED(hr)) {
      throw IException("Failed to GetFloat. HRESULT(0x%lx)", hr);
    }
  }
    
  void setFloatArray(float *pData, UINT offset, UINT count)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> SetFloatArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetFloatArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void getFloatArray(float *pData, UINT offset, UINT count)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetFloatArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetFloatArray. HRESULT(0x%lx)", hr);
    }
  }
    
  void setInt(int value)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> SetInt(value);
    if (FAILED(hr)) {
      throw IException("Failed to SetInt. HRESULT(0x%lx)", hr);
    }
  }
  
  void getInt(int *pValue)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetInt(pValue);
    if (FAILED(hr)) {
      throw IException("Failed to GetInt. HRESULT(0x%lx)", hr);
    }
  }
    
  void setIntArray(int *pData, UINT offset, UINT count)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> SetIntArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetIntArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void getIntArray(int *pData, UINT offset, UINT count)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetIntArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetIntArray. HRESULT(0x%lx)", hr);
    }
  }
    
  void setBool(BOOL value)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> SetBool(value);
    if (FAILED(hr)) {
      throw IException("Failed to SetBool. HRESULT(0x%lx)", hr);
    }
  }
  
  void getBool(BOOL *pValue)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetBool(pValue);
    if (FAILED(hr)) {
      throw IException("Failed to GetBool. HRESULT(0x%lx)", hr);
    }
  }
    
  void setBoolArray(BOOL *pData, UINT offset, UINT count)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> SetBoolArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetBoolArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void getBoolArray(BOOL *pData, UINT offset, UINT count)
  {
    ID3DX11EffectScalarVariable* variable = getScalarVariable();
    HRESULT hr = variable -> GetBoolArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetBoolArray. HRESULT(0x%lx)", hr);
    }
  }
};

}
