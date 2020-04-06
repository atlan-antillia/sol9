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
 *  Direct3D11DomainShader.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11DeviceChild.h>

namespace SOL {

class Direct3D11DomainShader : public Direct3D11DeviceChild {
   
public:
  Direct3D11DomainShader(
        __in ID3D11Device* device,
        __in  const void *pShaderBytecode,
        __in  SIZE_T bytecodeLength,
        __in_opt  ID3D11ClassLinkage *pClassLinkage)
  {
    if (device) {
      ID3D11DomainShader* domainShader = NULL;
      HRESULT hr = device -> CreateDomainShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              &domainShader);
      if (SUCCEEDED(hr)) {
        set(domainShader);
      } else {
        throw IException("Failed to CreateDomainShader. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL."); 
    }
  }

  ~Direct3D11DomainShader()
  {
  }

  operator ID3D11DomainShader*()
  {
    return getDomainShader();
  }
  
  ID3D11DomainShader* getDomainShader()
  {
    ID3D11DomainShader* shader = (ID3D11DomainShader*)getIUnknown();
    if (shader) {
        return shader;
    } else {
      throw IException("ID3D11DomainShader is NULL.");
    }
  }
        
};


}

