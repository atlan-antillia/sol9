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
 *  Direct3D11DepthStencilView.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11View.h>

namespace SOL {

class Direct3D11DepthStencilView : public Direct3D11View{
    
public:
  Direct3D11DepthStencilView(
      __in ID3D11Device* device,
      __in  ID3D11Resource *pResource,
      __in_opt  const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc)
  {
    if (device) {
      ID3D11DepthStencilView* depthStencilView = NULL;
      HRESULT hr = device -> CreateDepthStencilView( 
              pResource,
              pDesc,
              &depthStencilView);
      if (SUCCEEDED(hr)) {
        set(depthStencilView);
      } else {
        throw IException("Failed to CreateDepthStencilView. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL"); 
    }
  }

  ~Direct3D11DepthStencilView()
  {
  }

  operator ID3D11DepthStencilView*()
  {
    return getDepthStencilView();
  }
  
  ID3D11DepthStencilView* getDepthStencilView()
  {
    ID3D11DepthStencilView* view = (ID3D11DepthStencilView*)getIUnknown();
    if (view) {
        return view;
    } else {
      throw IException("ID3D11DepthStencilView is NULL.");
    }
  }
  
  void getDesc( 
            __out  D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc)
  {
    ID3D11DepthStencilView* view = getDepthStencilView();
    view -> GetDesc(pDesc);
  }
  
  //clearFlags D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL
  void clear(UINT clearFlags = D3D11_CLEAR_DEPTH, 
      FLOAT depth = 1.0f, 
      UINT8 stencil = 0)
  {
    ID3D11Device* device = NULL;
    getDevice(&device);
    if (device) {
      ID3D11DeviceContext* immediateContext = NULL;
      device -> GetImmediateContext( 
              &immediateContext);
      if (immediateContext) {
        immediateContext -> ClearDepthStencilView(*this, clearFlags, depth, stencil);
        immediateContext -> Release();
      }
      device -> Release();
    }
  }
};

}

