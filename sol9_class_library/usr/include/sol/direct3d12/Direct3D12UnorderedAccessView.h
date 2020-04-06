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
 *  Direct3D12UnorderedAccessView.h
 *
 *****************************************************************************/

// 2016/10/01

#pragma once

#include <sol/direct3d12/Direct3D12View.h>

namespace SOL {

class Direct3D12UnorderedAccessView : public Direct3D12View{
    
public:
  Direct3D12UnorderedAccessView(
      __in  ID3D12Device* device,
      __in  ID3D12Resource *pResource,
      __in_opt  const D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc)
  {
    if (device == nullptr) {
      throw IException("Invalid argument. ID3D11Device is NULL.");
    }
    
    ID3D12UnorderedAccessView* uaView = NULL;
    HRESULT hr = device -> CreateUnorderedAccessView( 
              pResource,
              pDesc,
              &uaView);
    if (SUCCEEDED(hr)) {
        set(uaView);
    } else {
      throw IException("Failed to CreateUnorderedAccessView. HRESULT(0x%lx)", hr); 
    }
  }

  ~Direct3D12UnorderedAccessView()
  {
  }

  operator ID3D12UnorderedAccessView*()
  {
    return getUnorderedAccessView();
  }
  
  ID3D12UnorderedAccessView* getUnorderedAccessView()
  {
    ID3D12UnorderedAccessView* view = (ID3D12UnorderedAccessView*)getIUnknown();
    if (view) {
        return view;
    } else {
      throw IException("ID3D11UnorderedAccessView is NULL.");
    }
  }
  
  void getDesc( 
            __out  D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc)
  {
    ID3D12UnorderedAccessView* view = getUnorderedAccessView();
    view -> GetDesc(pDesc);

  }
};

}

