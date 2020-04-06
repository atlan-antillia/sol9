/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Direct3D11VertexShader.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11DeviceChild.h>
#include <sol/direct3d11/Direct3D11Blob.h>

namespace SOL {

class Direct3D11VertexShader : public Direct3D11DeviceChild {
public:
  //2016/02/20
  Direct3D11VertexShader(
        __in ID3D11Device* device,
        __in ID3DBlob*   blob,
        __in_opt  ID3D11ClassLinkage *pClassLinkage = NULL)
  {
    if (device && blob) {
      ID3D11VertexShader* vertexShader = NULL;
      HRESULT hr = device -> CreateVertexShader( 
              blob->GetBufferPointer(),
              blob->GetBufferSize(),
              pClassLinkage,
              &vertexShader);
      if (SUCCEEDED(hr)) {
        set(vertexShader);
      } else {
        throw IException("Failed to CreateVertexShader. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device or ID3D11Blob is NULL");
    }
  }
   
public:
  Direct3D11VertexShader(
        __in ID3D11Device* device,
        __in void*   pShaderBytecode,
        __in  SIZE_T bytecodeLength,
        __in_opt  ID3D11ClassLinkage *pClassLinkage = NULL)
  {
    if (device) {
      ID3D11VertexShader* vertexShader = NULL;
      HRESULT hr = device -> CreateVertexShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              &vertexShader);
      if (SUCCEEDED(hr)) {
        set(vertexShader);
      } else {
        throw IException("Failed to CreateVertexShader. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL");
    }
  }

public:
  Direct3D11VertexShader(
        __in ID3D11Device* device,
        __in const TCHAR* fullpath,     //shader file fullpath
        __in const char*  functionName, 
        __in const char*  profile,
        __in_opt  ID3D11ClassLinkage *pClassLinkage = NULL)
  {
    if (device) {
      Direct3D11Blob* vertexShaderBlob = new Direct3D11Blob(fullpath, functionName, profile);
      if (vertexShaderBlob) {
          
        ID3D11VertexShader* vertexShader = NULL;
        HRESULT hr = device -> CreateVertexShader( 
              vertexShaderBlob->getBufferPointer(),
              vertexShaderBlob->getBufferSize(),
              pClassLinkage,
              &vertexShader);
          
        delete vertexShaderBlob;
          
        if (SUCCEEDED(hr)) {
          set(vertexShader);
        } else {
          throw IException("Failed to CreateVertexShader. HRESULT(0x%lx)", hr); 
        }
      } else {
        throw IException("Direct3D11Blob is NULL."); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL");
    }
  }

  ~Direct3D11VertexShader()
  {
  }

  operator ID3D11VertexShader*()
  {
    return getVertexShader();
  }
  
  ID3D11VertexShader* getVertexShader()
  {
    ID3D11VertexShader* shader = (ID3D11VertexShader*)getIUnknown();
    if (shader) {
        return shader;
    } else {
      throw IException("ID3D11VertexShader is NULL.");
    }
  }
        
};


}

