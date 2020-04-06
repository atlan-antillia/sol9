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
 *  Direct3D10Blob.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10Resource.h>

namespace SOL {

class Direct3D10Blob : public ComIUnknown {
public:
  Direct3D10Blob(ID3D10Blob* blob)
  :ComIUnknown()
  {
    if (blob) {
      set(blob);
    } else {
      throw IException("Invalid argument. ID3D10Blob is NULL.");
    }
  }

public:
  Direct3D10Blob(
        void *pData, 
        SIZE_T dataLength, 
        LPCSTR pSrcFileName, 
        CONST D3D10_SHADER_MACRO *pDefines, 
        ID3D10Include *pInclude, 
        UINT hlslFlags, 
        UINT fxFlags)
  :ComIUnknown()
  {
    ID3D10Blob *compiledEffect = NULL;
    ID3D10Blob *errors      = NULL;
    HRESULT hr = D3D10CompileEffectFromMemory(
        pData, 
        dataLength,
        pSrcFileName, 
        pDefines, 
        pInclude, 
        hlslFlags, 
        fxFlags, 
        &compiledEffect,
        &errors);
       
      errors->Release();

    if (SUCCEEDED(hr)) {
      set(compiledEffect);
    } else {
      throw IException("Failed to D3D10CompileEffectFromMemory. HRESULT(0x%lx)", hr);
    }
  }
  
public:
  Direct3D10Blob(
        ID3D10Effect *pEffect, 
        BOOL enableColorCode)
  :ComIUnknown()
  {
    ID3D10Blob *disassembly = NULL;
    HRESULT hr = D3D10DisassembleEffect(
          pEffect, 
          enableColorCode, 
          &disassembly);
    if (SUCCEEDED(hr)) {
      set(disassembly);
    } else {
      throw IException("Failed to D3D10DisassembleEffect. HRESULT(0x%lx)", hr);
    }
  }
  
  
  ~Direct3D10Blob()
  {
  }

  operator   ID3D10Blob*()
  {
    return getBlob();
  }

  ID3D10Blob* getBlob()
  {
    ID3D10Blob* blob = (ID3D10Blob*)getIUnknown();
    if (blob) {
        return blob;
    } else {
        throw IException("ID3D10Blob is NULL.")
    }
  }

  void*  getBufferPointer()
  {
    ID3D10Blob* blob = getBlob();
    return blob -> GetBufferPointer();
  }

  SIZE_T getBufferSize()
  {
    ID3D10Blob* blob = getBlob();
    return blob -> GetBufferSize();
  }

};

}
