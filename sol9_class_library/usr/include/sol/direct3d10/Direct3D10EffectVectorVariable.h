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
 *  Direct3D10EffectVectorVariable.h
 *
 *****************************************************************************/

#pragma once


#include <sol/direct3d10/Direct3D10EffectVariable.h>


namespace SOL {

class Direct3D10EffectVectorVariable : public Direct3D10EffectVariable {
public:
  Direct3D10EffectVectorVariable(ID3D10EffectVectorVariable* variable) 
  :Direct3D10EffectVariable(variable)
  {
  }
  
  ~Direct3D10EffectVectorVariable() 
  {
  }
    
  operator ID3D10EffectVectorVariable*()
  {
    return getVectorVariable();
  }
  
  ID3D10EffectVectorVariable* getVectorVariable()
  {
    ID3D10EffectVectorVariable* variable = (ID3D10EffectVectorVariable*)getInterface();
    if (variable) {
      return variable;
    } else {
      throw IException("ID3D10EffectVectorVariable is NULL.");
    }
  }
  
  BOOL isValid()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> IsValid();
  }
  
  ID3D10EffectType* getType()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetType();
  }
  
  void getDesc(D3D10_EFFECT_VARIABLE_DESC *pDesc)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  void getDesc(D3D10_EFFECT_VARIABLE_DESC& desc)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  ID3D10EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetAnnotationByIndex(index);
  }
  
  ID3D10EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetAnnotationByName(name);
  }
    
  ID3D10EffectVariable* getMemberByIndex(UINT index)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetMemberByIndex(index);
  }
  
  ID3D10EffectVariable* getMemberByName(LPCSTR name)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetMemberByName(name);
  }
  
  ID3D10EffectVariable* getMemberBySemantic(LPCSTR semantic)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetMemberBySemantic(semantic);
  }
    
  ID3D10EffectVariable* getElement(UINT index)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetElement(index);
  }
    
  ID3D10EffectConstantBuffer* getParentConstantBuffer()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> GetParentConstantBuffer();
  }
    
  ID3D10EffectScalarVariable* asScalar()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsScalar();
  }
  
  ID3D10EffectVectorVariable* asVector()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsVector();
  }
  
  ID3D10EffectMatrixVariable* asMatrix()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsMatrix();
  }
  
  ID3D10EffectStringVariable* asString() 
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsString();
  }
  
  ID3D10EffectShaderResourceVariable* asShaderResource()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsShaderResource();
  }
  
  ID3D10EffectRenderTargetViewVariable* asRenderTargetView()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsRenderTargetView();
  }
  
  ID3D10EffectDepthStencilViewVariable* asDepthStencilView()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsDepthStencilView();
  }
  
  ID3D10EffectConstantBuffer* asConstantBuffer()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsConstantBuffer();
  }
  
  ID3D10EffectShaderVariable* asShader()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsShader();
  }
  
  ID3D10EffectBlendVariable* asBlend()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsBlend();
  }
  
  ID3D10EffectDepthStencilVariable* asDepthStencil()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsDepthStencil();
  }
  
  ID3D10EffectRasterizerVariable* asRasterizer()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsRasterizer();
  }
  
  ID3D10EffectSamplerVariable* asSampler()
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    return variable -> AsSampler();
  }
    
  void setRawValue(void *pData, UINT byteOffset, UINT byteCount)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> SetRawValue(pData, byteOffset, byteCount);
    if (FAILED(hr)) {
      throw IException("Failed to SetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  void getRawValue(void *pData, UINT byteOffset, UINT byteCount)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetRawValue(pData, byteOffset, byteCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetRawValue. HRESULT(0x%lx)", hr);
    }
  }
    
  void setBoolVector(BOOL *pData)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> SetBoolVector(pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetBoolVector. HRESULT(0x%lx)", hr);
    }
  }
  
  void setIntVector(int *pData)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> SetIntVector(pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetIntVector. HRESULT(0x%lx)", hr);
    }
  }
  
  void setFloatVector(float *pData)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> SetFloatVector(pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetFloatVector. HRESULT(0x%lx)", hr);
    }
  }

  void getBoolVector(BOOL *pData)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetBoolVector(pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetBoolVector. HRESULT(0x%lx)", hr);
    }
  }
  
  void getIntVector(int *pData)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetIntVector(pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetIntVector. HRESULT(0x%lx)", hr);
    }
  }
  
  void getFloatVector(float *pData)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetFloatVector(pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetFloatVector. HRESULT(0x%lx)", hr);
    }
  }

  void setBoolVectorArray(BOOL *pData, UINT offset, UINT count)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> SetBoolVectorArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetBoolVectorArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void setIntVectorArray(int *pData, UINT offset, UINT count)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> SetIntVectorArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetIntVectorArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void setFloatVectorArray(float *pData, UINT offset, UINT count)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> SetFloatVectorArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetFloatVectorArray. HRESULT(0x%lx)", hr);
    }
  }

  void getBoolVectorArray(BOOL *pData, UINT offset, UINT count)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetBoolVectorArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetBoolVectorArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void getIntVectorArray(int *pData, UINT offset, UINT count)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetIntVectorArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetIntVectorArray. HRESULT(0x%lx)", hr);
    }
  }
  
  void getFloatVectorArray(float *pData, UINT offset, UINT count)
  {
    ID3D10EffectVectorVariable* variable = getVectorVariable();
    HRESULT hr = variable -> GetFloatVectorArray(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetFloatVectorArray. HRESULT(0x%lx)", hr);
    }
  }
};

}
