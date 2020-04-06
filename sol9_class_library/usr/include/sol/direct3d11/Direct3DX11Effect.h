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
 *  Direct3DX11Effect.h
 *
 *****************************************************************************/

#pragma once

#include <DXGItype.h>

#include <sol/direct3d11/Direct3D11Resource.h>
#include <sol/direct3d11/Direct3D11Blob.h>
#include <d3dx11effect.h>
#include <sol/direct3d11/Direct3DX11ShaderCompiler.h>
#pragma comment(lib, "legacy_stdio_definitions.lib")

#pragma comment( lib, "Effects11.lib" )  
#pragma comment( lib, "d3dcompiler.lib" )


namespace SOL {

class Direct3DX11Effect :public ComIUnknown {
protected:
  Direct3DX11Effect()
  :ComIUnknown()
  {
  }
  
public:
  //Constructor based on Direct3DX11ShaderCompiler and D3DX11CreateEffectFromFile.  
  Direct3DX11Effect(
        __in ID3D11Device* device,
        __in const TCHAR* filepath,
        __in UINT          fxFlags = 0)
  :ComIUnknown()
  {
    //1 Compiler a shadefile.
    Direct3DX11ShaderCompiler compiler(filepath);
    
    void* data    = compiler.getBufferPointer();
    size_t length = compiler.getBufferSize();
    
    ID3DX11Effect *effect = NULL;
    //2 Create ID3DXEffect interface from the compiled shader.
    HRESULT hr = D3DX11CreateEffectFromMemory(
        data, 
        length, 
        fxFlags,
        device, 
        &effect);
      
    if (SUCCEEDED(hr)) {
      set(effect); 
    } else {
      throw IException("Faile to D3DX11CreateEffectFromFile. HRESULT(0x%lx)", hr);
    }
  }

public:
  //Constructor based on D3DX11CreateEffectFromMemory.
  Direct3DX11Effect(
        ID3D11Device*     pDevice,
        void*             pData, 
        SIZE_T            dataLength, 
        UINT              fxFlags)
  :ComIUnknown()
  {
    ID3DX11Effect *effect = NULL;
    HRESULT hr = D3DX11CreateEffectFromMemory(
        pData, 
        dataLength, 
        fxFlags, 
        pDevice, 
        &effect);
    if (SUCCEEDED(hr)) {
      set(effect);
    } else {
      throw IException("Failed to D3DX11CreateEffectFromMemory. HRESULT(0x%lx)", hr);
    }
  }

  operator  ID3DX11Effect*()
  {
    return getEffect();
  }
  
  ID3DX11Effect* getEffect()
  {
    ID3DX11Effect* effect = (ID3DX11Effect*)getIUnknown();
    if (effect) {
      return effect;
    } else {
      throw IException("ID3DX11Effect is NULL.");
    }
  }
  
  BOOL isValid()
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> IsValid();
  }
  /*
  BOOL isPool()
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> IsPool();
  }
  */

  void getDevice(ID3D11Device** ppDevice)
  {
    ID3DX11Effect* effect = getEffect();
    HRESULT hr = effect -> GetDevice(ppDevice);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
    
  void getDesc(D3DX11_EFFECT_DESC *pDesc)
  {
    ID3DX11Effect* effect = getEffect();
    HRESULT hr = effect -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  void getDesc(D3DX11_EFFECT_DESC& desc)
  {
    ID3DX11Effect* effect = getEffect();
    HRESULT hr = effect -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  ID3DX11EffectConstantBuffer*  getConstantBufferByIndex(UINT index)
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> GetConstantBufferByIndex(index);
  }

  ID3DX11EffectConstantBuffer*  getConstantBufferByName(LPCSTR name)
  {
    ID3DX11Effect* effect = getEffect();
    return effect ->GetConstantBufferByName(name) ;
  }
    
  ID3DX11EffectVariable*  getVariableByIndex(UINT index)
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> GetVariableByIndex(index);
  }

  ID3DX11EffectVariable*  getVariableByName(LPCSTR name)
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> GetVariableByName(name);
  }

  ID3DX11EffectVariable*  getVariableBySemantic(LPCSTR semantic)
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> GetVariableBySemantic(semantic);
  }
    
  ID3DX11EffectTechnique*  getTechniqueByIndex(UINT index)
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> GetTechniqueByIndex(index);
  }

  ID3DX11EffectTechnique*  getTechniqueByName(LPCSTR name)
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> GetTechniqueByName(name);
  }
  
  void optimize()
  {
    ID3DX11Effect* effect = getEffect();
    HRESULT hr = effect -> Optimize();
    if (FAILED(hr)) {
      throw IException("Failed to Optimize. HRESULT(0x%lx)", hr);
    }
  }

  BOOL isOptimized()
  {
    ID3DX11Effect* effect = getEffect();
    return effect -> IsOptimized();
  }
/*  
  void disassemble(BOOL enableColorCode, ID3DX11Blob **ppDisassembly)
  {
    ID3DX11Effect* effect = getEffect();
    HRESULT hr = D3DX11DisassembleEffect(effect, enableColorCode, ppDisassembly);
    if (FAILED(hr)) {
      throw IException("Failed to D3DX11DisassembleEffect. HRESULT(0x%lx)", hr);
    }
  }
 */
};

}

