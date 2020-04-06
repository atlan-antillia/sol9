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
 *  Direct3D11DepthStencilState.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11DeviceChild.h>


namespace SOL {

class Direct3D11DepthStencilState : public Direct3D11DeviceChild {
public:
  Direct3D11DepthStencilState(
        __in ID3D11Device* device,
        __in  const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc)
  {
    if (device) {
      ID3D11DepthStencilState* depthStencilState = NULL;
      HRESULT hr = device -> CreateDepthStencilState( 
              pDepthStencilDesc,
              &depthStencilState);
      if (SUCCEEDED(hr)) {
        set(depthStencilState);
      } else {
        throw IException("Failed to CreateDepthStencilState. HRESULT(0x%lx)", hr); 
      }
      
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL");
    }
  }
  
  ~Direct3D11DepthStencilState()
  {
  }
  
  operator ID3D11DepthStencilState*()
  {
    return getState(); 
  }
  
  ID3D11DepthStencilState* getState()
  {
    ID3D11DepthStencilState* state = (ID3D11DepthStencilState*)getIUnknown();
    if (state) {
        return state;
    } else {
      throw IException("ID3D11DepthStencilState is NULL.");
    }
  }
  
  void getDesc( 
            __out  D3D11_DEPTH_STENCIL_DESC *pDesc)
  {
    ID3D11DepthStencilState* state = getState();
    
    state -> GetDesc(pDesc);
  }
        
};

}

