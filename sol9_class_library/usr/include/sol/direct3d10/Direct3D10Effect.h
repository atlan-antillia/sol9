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
 *  Direct3D10Effect.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10Resource.h>
#include <sol/direct3d10/Direct3D10Blob.h>

namespace SOL {

class Direct3D10Effect :public ComIUnknown {
protected:
  Direct3D10Effect()
  :ComIUnknown()
  {
  }
  
public:
  //Constructor based on D3DX10CreateEffectFromMemory.
  Direct3D10Effect(
      ID3D10Device*             pDevice,
      LPCVOID                   pData,
      SIZE_T                    dataLength,
      LPCSTR                    pSrcFileName,
      UINT                      hlslFlags)
  :ComIUnknown()
  {
    CONST D3D10_SHADER_MACRO* pDefines    = NULL;
    ID3D10Include*            pInclude    = NULL;

    LPCSTR                    pProfile    = "fx_4_0";   //
    UINT                      fxFlags     = 0;
    ID3D10EffectPool*         pEffectPool = NULL;
    ID3DX10ThreadPump*        pPump       = NULL;
    ID3D10Blob**              ppErrors    = NULL;
    HRESULT*                  pHResult    = NULL;

    ID3D10Effect *effect = NULL;

    HRESULT hr = D3DX10CreateEffectFromMemory(
            pData,
            dataLength,
            pSrcFileName,
            pDefines,
            pInclude,
            pProfile,
            hlslFlags,
            fxFlags,
            pDevice,
            pEffectPool,
            pPump,
            &effect,
            ppErrors,
            pHResult
          );
    if (SUCCEEDED(hr)) {
      set(effect);
    } else {
      throw IException("Failed to D3DX10CreateEffectFromMemory. HRESULT(0x%lx)", hr);
    }
  }

  //Constructor based on D3DX10CreateEffectFromMemory.
  Direct3D10Effect(
      ID3D10Device*             pDevice,
      LPCVOID                   pData,
      SIZE_T                    dataLength,
      LPCSTR                    pSrcFileName,
      CONST D3D10_SHADER_MACRO* pDefines,
      ID3D10Include*            pInclude,
      LPCSTR                    pProfile,
      UINT                      hlslFlags,
      UINT                      fxFlags,
      ID3D10EffectPool*         pEffectPool,
      ID3DX10ThreadPump*        pPump,
      ID3D10Blob**              ppErrors,
      HRESULT*                  pHResult)
  :ComIUnknown()
  {
    ID3D10Effect *effect = NULL;

    HRESULT hr = D3DX10CreateEffectFromMemory(
            pData,
            dataLength,
            pSrcFileName,
            pDefines,
            pInclude,
            pProfile,
            hlslFlags,
            fxFlags,
            pDevice,
            pEffectPool,
            pPump,
            &effect,
            ppErrors,
            pHResult
          );
    if (SUCCEEDED(hr)) {
      set(effect);
    } else {
      throw IException("Failed to D3DX10CreateEffectFromMemory. HRESULT(0x%lx)", hr);
    }
  }
  
  //Constructor based on D3D10CreateEffectFromMemory.
  Direct3D10Effect(
        ID3D10Device*     pDevice,
        void*             pData, 
        SIZE_T            dataLength, 
        UINT              fxFlags, 
        ID3D10EffectPool* pEffectPool)
  :ComIUnknown()
  {
    ID3D10Effect *effect = NULL;
    HRESULT hr = D3D10CreateEffectFromMemory(
        pData, 
        dataLength, fxFlags, 
        pDevice, 
        pEffectPool, 
        &effect);
    if (SUCCEEDED(hr)) {
      set(effect);
    } else {
      throw IException("Failed to D3D10CreateEffectFromMemory. HRESULT(0x%lx)", hr);
    }
  }

  //Constructor based on D3DX10CreateEffectFromFile.  
  Direct3D10Effect(
        ID3D10Device*             pDevice,
        LPCTSTR                   pFileName)
  :ComIUnknown()
  {
    LPCSTR                    pProfile    = "fx_4_0";
    CONST D3D10_SHADER_MACRO* pDefines    = NULL;
    ID3D10Include*            pInclude    = NULL;
    UINT                      hlslFlags   = D3D10_SHADER_ENABLE_STRICTNESS;
    UINT                      fxFlags     = 0;
    ID3D10EffectPool*         pEffectPool = NULL;
    ID3DX10ThreadPump*        pPump       = NULL;
    HRESULT*                  pHResult    = NULL;

    ID3D10Effect *effect = NULL;
    ID3D10Blob   *errors = NULL;
    HRESULT hr = D3DX10CreateEffectFromFile(
              pFileName,
              pDefines,
              pInclude,
              pProfile,
              hlslFlags,
              fxFlags,
              pDevice,
              pEffectPool,
              pPump,
              &effect,
              &errors,
              pHResult);
    
    
    if (SUCCEEDED(hr)) {
      set(effect); 
    } else {
      throw IException("Faile to D3DX10CreateEffectFromFile. HRESULT(0x%lx)", hr);
    }
  }
  
  //Constructor based on D3DX10CreateEffectFromFile.
  
  Direct3D10Effect(
        ID3D10Device*             pDevice,
        LPCTSTR                   pFileName,
        CONST D3D10_SHADER_MACRO* pDefines,
        ID3D10Include*            pInclude,
        UINT                      hlslFlags,
        UINT                      fxFlags,
        ID3D10EffectPool*         pEffectPool,
        ID3DX10ThreadPump*        pPump,
        HRESULT*                   pHResult
        )
  :ComIUnknown()
  {
    LPCSTR       pProfile= "fx_4_0";   
    ID3D10Effect *effect = NULL;
    ID3D10Blob   *errors = NULL;
    HRESULT hr = D3DX10CreateEffectFromFile(
              pFileName,
              pDefines,
              pInclude,
              pProfile,
              hlslFlags,
              fxFlags,
              pDevice,
              pEffectPool,
              pPump,
              &effect,
              &errors,
              pHResult);
    
    
    if (SUCCEEDED(hr)) {
      set(effect); 
    } else {
      Direct3D10Blob blob(errors);
      //blob.geBuffer();
      throw IException("Faile to D3DX10CreateEffectFromFile. HRESULT(0x%lx)", hr);
    }
  }
  
  operator  ID3D10Effect*()
  {
    return getEffect();
  }
  
  ID3D10Effect* getEffect()
  {
    ID3D10Effect* effect = (ID3D10Effect*)getIUnknown();
    if (effect) {
      return effect;
    } else {
      throw IException("ID3D10Effect is NULL.");
    }
  }
  
  BOOL isValid()
  {
    ID3D10Effect* effect = getEffect();
    return effect -> IsValid();
  }
  
  BOOL isPool()
  {
    ID3D10Effect* effect = getEffect();
    return effect -> IsPool();
  }

  void getDevice(ID3D10Device** ppDevice)
  {
    ID3D10Effect* effect = getEffect();
    HRESULT hr = effect -> GetDevice(ppDevice);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
    
  void getDesc(D3D10_EFFECT_DESC *pDesc)
  {
    ID3D10Effect* effect = getEffect();
    HRESULT hr = effect -> GetDesc(pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  void getDesc(D3D10_EFFECT_DESC& desc)
  {
    ID3D10Effect* effect = getEffect();
    HRESULT hr = effect -> GetDesc(&desc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
    
  ID3D10EffectConstantBuffer*  getConstantBufferByIndex(UINT index)
  {
    ID3D10Effect* effect = getEffect();
    return effect -> GetConstantBufferByIndex(index);
  }

  ID3D10EffectConstantBuffer*  getConstantBufferByName(LPCSTR name)
  {
    ID3D10Effect* effect = getEffect();
    return effect ->GetConstantBufferByName(name) ;
  }
    
  ID3D10EffectVariable*  getVariableByIndex(UINT index)
  {
    ID3D10Effect* effect = getEffect();
    return effect -> GetVariableByIndex(index);
  }

  ID3D10EffectVariable*  getVariableByName(LPCSTR name)
  {
    ID3D10Effect* effect = getEffect();
    return effect -> GetVariableByName(name);
  }

  ID3D10EffectVariable*  getVariableBySemantic(LPCSTR semantic)
  {
    ID3D10Effect* effect = getEffect();
    return effect -> GetVariableBySemantic(semantic);
  }
    
  ID3D10EffectTechnique*  getTechniqueByIndex(UINT index)
  {
    ID3D10Effect* effect = getEffect();
    return effect -> GetTechniqueByIndex(index);
  }

  ID3D10EffectTechnique*  getTechniqueByName(LPCSTR name)
  {
    ID3D10Effect* effect = getEffect();
    return effect -> GetTechniqueByName(name);
  }
  
  void optimize()
  {
    ID3D10Effect* effect = getEffect();
    HRESULT hr = effect -> Optimize();
    if (FAILED(hr)) {
      throw IException("Failed to Optimize. HRESULT(0x%lx)", hr);
    }
  }

  BOOL isOptimized()
  {
    ID3D10Effect* effect = getEffect();
    return effect -> IsOptimized();
  }
  
  void disassemble(BOOL enableColorCode, ID3D10Blob **ppDisassembly)
  {
    ID3D10Effect* effect = getEffect();
    HRESULT hr = D3D10DisassembleEffect(effect, enableColorCode, ppDisassembly);
    if (FAILED(hr)) {
      throw IException("Failed to D3D10DisassembleEffect. HRESULT(0x%lx)", hr);
    }
  }
};

}

