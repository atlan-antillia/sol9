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
 *  Direct3D10EffectVariable.h
 *
 *****************************************************************************/

#pragma once


#include <sol/com/ComInterface.h>
#include <sol/Exception.h>

#include <d3d10_1.h>
#include <d3dx10.h>

namespace SOL {

class Direct3D10EffectVariable : public ComInterface {

public:
  Direct3D10EffectVariable()
  :ComInterface()
  {
  }

  Direct3D10EffectVariable(ID3D10EffectVariable* variable)
  :ComInterface()
  {
    if (variable) {
      set(variable);
    } else {
      throw IException("Invalid argument. ID3D10EffectVariable is NULL.");
    }
  }
  
  ~Direct3D10EffectVariable()
  {
  }  

  operator ID3D10EffectVariable*()
  {
    return getVariable();
  }
 
  virtual ID3D10EffectVariable* getVariable()
  {
    ID3D10EffectVariable* variable = (ID3D10EffectVariable*)getInterface();
    if (variable) {
      return variable;
    } else {
      throw IException("ID3D10EffectVariable is NULL.");
    }
  }
  
  virtual BOOL IsValid()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> IsValid();
  }
  
  virtual ID3D10EffectType* getType()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetType();
  }
  
  virtual void getDesc(D3D10_EFFECT_VARIABLE_DESC *pDesc)
  {
    ID3D10EffectVariable* variable = getVariable();
    HRESULT hr = variable -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  virtual ID3D10EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetAnnotationByIndex(index);
  }
  
  virtual ID3D10EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetAnnotationByName(name);
  }
    
  virtual ID3D10EffectVariable* getMemberByIndex(UINT index)
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetMemberByIndex(index);
  }
  
  virtual ID3D10EffectVariable* getMemberByName(LPCSTR name)
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetMemberByName(name);
  }
  
  virtual ID3D10EffectVariable* getMemberBySemantic(LPCSTR semantic)
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetMemberBySemantic(semantic);
  }
    
  virtual ID3D10EffectVariable* getElement(UINT index)
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetElement(index);
  }

  virtual ID3D10EffectConstantBuffer* getParentConstantBuffer()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> GetParentConstantBuffer();
  }
    
  virtual ID3D10EffectScalarVariable* asScalar()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsScalar();
  }
  
  virtual ID3D10EffectVectorVariable* asVector()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsVector();
  }
  
  virtual ID3D10EffectMatrixVariable* asMatrix()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsMatrix();
  }
  
  virtual ID3D10EffectStringVariable* asString()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsString();
  }
  
  virtual ID3D10EffectShaderResourceVariable* asShaderResource()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsShaderResource();
  }
  
  virtual ID3D10EffectRenderTargetViewVariable* asRenderTargetView()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsRenderTargetView();
  }
  
  virtual ID3D10EffectDepthStencilViewVariable* asDepthStencilView()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsDepthStencilView();
  }
  
  virtual ID3D10EffectConstantBuffer* asConstantBuffer()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsConstantBuffer();
  }
  
  virtual ID3D10EffectShaderVariable* asShader()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsShader();
  }
  
  virtual ID3D10EffectBlendVariable* asBlend()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsBlend();
  }
  
  virtual ID3D10EffectDepthStencilVariable* asDepthStencil()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsDepthStencil();
  }
  
  virtual ID3D10EffectRasterizerVariable* asRasterizer()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsRasterizer();
  }
  
  virtual ID3D10EffectSamplerVariable* asSampler()
  {
    ID3D10EffectVariable* variable = getVariable();
    return variable -> AsSampler();
  }
    
  virtual void setRawValue(void *pData, UINT offset, UINT count)
  {
    ID3D10EffectVariable* variable = getVariable();
    HRESULT hr = variable -> SetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  virtual void getRawValue(void *pData, UINT offset, UINT count)
  {
    ID3D10EffectVariable* variable = getVariable();
    HRESULT hr = variable -> GetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetRawValue. HRESULT(0x%lx)", hr);
    }
  }
};

}
