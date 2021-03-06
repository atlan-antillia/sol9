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
 *  Direct3D11UnorderedAccessView.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11View.h>

namespace SOL {

class Direct3D11UnorderedAccessView : public Direct3D11View{
    
public:
  Direct3D11UnorderedAccessView(
      __in  ID3D11Device* device,
      __in  ID3D11Resource *pResource,
      __in_opt  const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc)
  {
    if (device) {
      ID3D11UnorderedAccessView* uaView = NULL;
      HRESULT hr = device -> CreateUnorderedAccessView( 
              pResource,
              pDesc,
              &uaView);
      if (SUCCEEDED(hr)) {
        set(uaView);
      } else {
        throw IException("Failed to CreateUnorderedAccessView. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL.");
    }
  }

  ~Direct3D11UnorderedAccessView()
  {
  }

  operator ID3D11UnorderedAccessView*()
  {
    return getUnorderedAccessView();
  }
  
  ID3D11UnorderedAccessView* getUnorderedAccessView()
  {
    ID3D11UnorderedAccessView* view = (ID3D11UnorderedAccessView*)getIUnknown();
    if (view) {
        return view;
    } else {
      throw IException("ID3D11UnorderedAccessView is NULL.");
    }
  }
  
  void getDesc( 
            __out  D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc)
  {
    ID3D11UnorderedAccessView* view = getUnorderedAccessView();
    view -> GetDesc(pDesc);

  }
};

}

