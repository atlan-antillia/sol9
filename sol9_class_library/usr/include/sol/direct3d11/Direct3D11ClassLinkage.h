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
 *  Direct3D11ClassLinkage.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11DeviceChild.h>

namespace SOL {

class Direct3D11ClassLinkage : public Direct3D11DeviceChild {

   
public:
  Direct3D11ClassLinkage(__in ID3D11Device* device)
  {
    if (device) {
      ID3D11ClassLinkage* linkage = NULL;
      HRESULT hr = device -> CreateClassLinkage( 
              &linkage);
      if (SUCCEEDED(hr)) {
        set(linkage);
      } else {
        throw IException("Failed to CreateClassLinkage. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL");
    }
  }

  ~Direct3D11ClassLinkage()
  {
  }

  operator ID3D11ClassLinkage*()
  {
    return getLinkage();
  }
  
  ID3D11ClassLinkage* getLinkage()
  {
    ID3D11ClassLinkage* linkage = (ID3D11ClassLinkage*)getIUnknown();
    if (linkage) {
        return linkage;
    } else {
      throw IException("ID3D11ClassLinkage is NULL.");
    }
  }
  
 
  void getClassInstance( 
            __in  LPCSTR pClassInstanceName,
            __in  UINT instanceIndex,
            __out  ID3D11ClassInstance **ppInstance)
  {
    ID3D11ClassLinkage* linkage = getLinkage();
    HRESULT hr = linkage -> GetClassInstance( 
              pClassInstanceName,
              instanceIndex,
              ppInstance);
    if (FAILED(hr)) {
      throw IException("Failed to GetClassInstance. HRESULT(0x%lx)", hr); 
    }
  }
  
  
  void createClassInstance( 
            __in  LPCSTR pClassTypeName,
            __in  UINT constantBufferOffset,
            __in  UINT constantVectorOffset,
            __in  UINT textureOffset,
            __in  UINT samplerOffset,
            __out  ID3D11ClassInstance **ppInstance)
        
  {
    ID3D11ClassLinkage* linkage = getLinkage();
    HRESULT hr = linkage -> CreateClassInstance( 
                pClassTypeName,
                constantBufferOffset,
                constantVectorOffset,
                textureOffset,
                samplerOffset,
                ppInstance);
    if (FAILED(hr)) {
      throw IException("Failed to CreateClassInstance. HRESULT(0x%lx)", hr); 
    }
  }
    
};
  
  


}

