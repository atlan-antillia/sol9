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
 *  Direct3DX11EffectVariable.h
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

class Direct3DX11EffectVariable : public ComInterface {

public:
  Direct3DX11EffectVariable()
  :ComInterface()
  {
  }

  Direct3DX11EffectVariable(ID3DX11EffectVariable* variable)
  :ComInterface()
  {
    if (variable) {
      set(variable);
    } else {
      throw IException("Invalid argument. ID3DX11EffectVariable is NULL.");
    }
  }
  
  ~Direct3DX11EffectVariable()
  {
  }  

  operator ID3DX11EffectVariable*()
  {
    return getVariable();
  }
 
  virtual ID3DX11EffectVariable* getVariable()
  {
    ID3DX11EffectVariable* variable = (ID3DX11EffectVariable*)getInterface();
    if (variable) {
      return variable;
    } else {
      throw IException("ID3DX11EffectVariable is NULL.");
    }
  }
  
  virtual BOOL IsValid()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> IsValid();
  }
  
  virtual ID3DX11EffectType* getType()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetType();
  }
  
  virtual void getDesc(D3DX11_EFFECT_VARIABLE_DESC *pDesc)
  {
    ID3DX11EffectVariable* variable = getVariable();
    HRESULT hr = variable -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  virtual ID3DX11EffectVariable* getAnnotationByIndex(UINT index)
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetAnnotationByIndex(index);
  }
  
  virtual ID3DX11EffectVariable* getAnnotationByName(LPCSTR name)
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetAnnotationByName(name);
  }
    
  virtual ID3DX11EffectVariable* getMemberByIndex(UINT index)
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetMemberByIndex(index);
  }
  
  virtual ID3DX11EffectVariable* getMemberByName(LPCSTR name)
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetMemberByName(name);
  }
  
  virtual ID3DX11EffectVariable* getMemberBySemantic(LPCSTR semantic)
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetMemberBySemantic(semantic);
  }
    
  virtual ID3DX11EffectVariable* getElement(UINT index)
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetElement(index);
  }

  virtual ID3DX11EffectConstantBuffer* getParentConstantBuffer()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> GetParentConstantBuffer();
  }
    
  virtual ID3DX11EffectScalarVariable* asScalar()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsScalar();
  }
  
  virtual ID3DX11EffectVectorVariable* asVector()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsVector();
  }
  
  virtual ID3DX11EffectMatrixVariable* asMatrix()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsMatrix();
  }
  
  virtual ID3DX11EffectStringVariable* asString()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsString();
  }
  
  virtual ID3DX11EffectShaderResourceVariable* asShaderResource()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsShaderResource();
  }
  
  virtual ID3DX11EffectRenderTargetViewVariable* asRenderTargetView()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsRenderTargetView();
  }
  
  virtual ID3DX11EffectDepthStencilViewVariable* asDepthStencilView()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsDepthStencilView();
  }
  
  virtual ID3DX11EffectConstantBuffer* asConstantBuffer()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsConstantBuffer();
  }
  
  virtual ID3DX11EffectShaderVariable* asShader()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsShader();
  }
  
  virtual ID3DX11EffectBlendVariable* asBlend()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsBlend();
  }
  
  virtual ID3DX11EffectDepthStencilVariable* asDepthStencil()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsDepthStencil();
  }
  
  virtual ID3DX11EffectRasterizerVariable* asRasterizer()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsRasterizer();
  }
  
  virtual ID3DX11EffectSamplerVariable* asSampler()
  {
    ID3DX11EffectVariable* variable = getVariable();
    return variable -> AsSampler();
  }
    
  virtual void setRawValue(void *pData, UINT offset, UINT count)
  {
    ID3DX11EffectVariable* variable = getVariable();
    HRESULT hr = variable -> SetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to SetRawValue. HRESULT(0x%lx)", hr);
    }
  }
  
  virtual void getRawValue(void *pData, UINT offset, UINT count)
  {
    ID3DX11EffectVariable* variable = getVariable();
    HRESULT hr = variable -> GetRawValue(pData, offset, count);
    if (FAILED(hr)) {
      throw IException("Failed to GetRawValue. HRESULT(0x%lx)", hr);
    }
  }
};

}
