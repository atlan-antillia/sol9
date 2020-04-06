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
 *  Direct3D10DepthStencilView.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10View.h>

namespace SOL {

class Direct3D10DepthStencilView : public Direct3D10View {
public:
  Direct3D10DepthStencilView( 
    __in  ID3D10Device* device,
    __in  ID3D10Resource *pResource,
    __in_opt  const D3D10_DEPTH_STENCIL_VIEW_DESC *pDesc)
  :Direct3D10View()
  {
    ID3D10DepthStencilView* stencilView = NULL;
     HRESULT  hr = device -> CreateDepthStencilView( 
        pResource,
        pDesc,
        &stencilView);
     if (SUCCEEDED(hr)) {
       set(stencilView);
     } else {
       throw IException("Failed to CreateDepthStencilView. HRESULT(0x%lx)", hr)
     }
   }

  operator ID3D10DepthStencilView*()
  {
    return getStencilView();
  }

  ID3D10DepthStencilView* getStencilView()
  {
    ID3D10DepthStencilView* stencilView = (ID3D10DepthStencilView* )getIUnknown();
    if (stencilView) {
      return stencilView;
    } else {
      throw IException("D3D10DepthStencilView is NULL.")
    }
  }
  
  void  getDesc( 
            __out  D3D10_DEPTH_STENCIL_VIEW_DESC *pDesc)
  {
    ID3D10DepthStencilView* stencilView = getStencilView();
    stencilView -> GetDesc( 
            pDesc);
  }     
  
  void  getDesc( 
            __out  D3D10_DEPTH_STENCIL_VIEW_DESC& desc)
  {
    ID3D10DepthStencilView* stencilView = getStencilView();
    stencilView -> GetDesc( 
            &desc);
  }     
  
  //2015/11/20
  void clear(UINT clearFlags = D3D10_CLEAR_DEPTH, FLOAT depth = 1.0f, UINT8 stencil = 0)
  {
    ID3D10Device* device = NULL;
    getDevice(&device);
    if (device) {
      device -> ClearDepthStencilView(*this, clearFlags, depth, stencil);
      device -> Release(); //2016/01/10
    }
  }
};

}
    
