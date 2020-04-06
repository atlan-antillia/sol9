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
 *  Direct3D10DepthStencilState.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10DeviceChild.h>

namespace SOL {

class Direct3D10DepthStencilState : public Direct3D10DeviceChild {
    
public:
  Direct3D10DepthStencilState(
      __in  ID3D10Device* device,
      __in  const D3D10_DEPTH_STENCIL_DESC* pDepthStencilDesc)
  {
    ID3D10DepthStencilState* stencilState = NULL;
    HRESULT hr = device -> CreateDepthStencilState( 
        pDepthStencilDesc,
        &stencilState);
    if (SUCCEEDED(hr)) {
      set(stencilState);
    } else {
      throw IException("Failed to CreateDepthStencilState. HRESULT(0x%lx)", hr)
    }
  }

  operator ID3D10DepthStencilState*() 
  {
    return getStencilState();
  }
  
  ID3D10DepthStencilState* getStencilState() 
  {
    ID3D10DepthStencilState* stencilState = (ID3D10DepthStencilState*)getIUnknown();
    if (stencilState) {
      return stencilState;
    } else {
      throw IException("ID3D10DepthStencilState is NULL.");
    }
  }
  
  void getDesc( 
            __out  D3D10_DEPTH_STENCIL_DESC *pDesc)
  {
    ID3D10DepthStencilState* stencilState = getStencilState();
    stencilState ->  GetDesc( 
            pDesc);
  }
  
  void getDesc( 
            __out  D3D10_DEPTH_STENCIL_DESC& desc)
  {
    ID3D10DepthStencilState* stencilState = getStencilState();
    stencilState ->  GetDesc( 
            &desc);
  }
        
};
}

