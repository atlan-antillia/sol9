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
 *  Direct3D10ShaderReflection.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Exception.h>

#include <sol/com/ComIUnknown.h>
#include <d3d10_1.h>
#include <d3dx10.h>
\
namespace SOL {

class Direct3D10ShaderReflection : public ComIUnknown {
public:
  Direct3D10ShaderReflection(CONST void *pShaderBytecode, SIZE_T bytecodeLength)
  :ComIUnknown()
  {
    ID3D10ShaderReflection* reflection = NULL;
    HRESULT hr = D3D10ReflectShader(pShaderBytecode, bytecodeLength, &reflection);
    if (SUCCEEDED(hr)) {
      set(reflection);
    } else {
      throw IException("Failed to D3D10ReflectShader. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct3D10ShaderReflection()
  {
  }
  
  operator ID3D10ShaderReflection*()
  {
    return getReflection();
  }
  
  ID3D10ShaderReflection* getReflection()
  {
    ID3D10ShaderReflection* reflection = (ID3D10ShaderReflection*)getIUnknown();
    if (reflection) {
      reflection;
    } else {
      throw IException("ID3D10ShaderReflection is NULL.");
    }
  }
  
  void getDesc(D3D10_SHADER_DESC *pDesc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getDesc(D3D10_SHADER_DESC& desc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  ID3D10ShaderReflectionConstantBuffer*  getConstantBufferByIndex(UINT index)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    return reflection -> GetConstantBufferByIndex(index);
  }
  
  ID3D10ShaderReflectionConstantBuffer*  getConstantBufferByName(LPCSTR name)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    return reflection -> GetConstantBufferByName(name);
  }
    
  void getResourceBindingDesc(UINT resourceIndex, D3D10_SHADER_INPUT_BIND_DESC *pDesc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetResourceBindingDesc(resourceIndex, pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetResourceBindingDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  void getResourceBindingDesc(UINT resourceIndex, D3D10_SHADER_INPUT_BIND_DESC& desc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetResourceBindingDesc(resourceIndex, &desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetResourceBindingDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  void getInputParameterDesc(UINT parameterIndex, D3D10_SIGNATURE_PARAMETER_DESC *pDesc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetInputParameterDesc(parameterIndex, pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetInputParameterDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getInputParameterDesc(UINT parameterIndex, D3D10_SIGNATURE_PARAMETER_DESC& desc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetInputParameterDesc(parameterIndex, &desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetInputParameterDesc. HRESULT(0x%lx)", hr);
    }
  }

  void getOutputParameterDesc(UINT parameterIndex, D3D10_SIGNATURE_PARAMETER_DESC *pDesc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetOutputParameterDesc(parameterIndex, pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetOutputParameterDesc. HRESULT(0x%lx)", hr);
    }
  }
   
  void getOutputParameterDesc(UINT parameterIndex, D3D10_SIGNATURE_PARAMETER_DESC& desc)
  {
    ID3D10ShaderReflection* reflection = getReflection();
    HRESULT hr = reflection -> GetOutputParameterDesc(parameterIndex, &desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetOutputParameterDesc. HRESULT(0x%lx)", hr);
    }
  }
};

}

