/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this context of conditions, and the following disclaimer.
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
 *  Direct3D11DeferredContext.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11DeviceContext.h>

namespace SOL {

class Direct3D11DeferredContext : public Direct3D11DeviceContext {

public:
  Direct3D11DeferredContext(__in ID3D11Device* device, UINT contextFlags = 0)
  :Direct3D11DeviceContext()
  {
    if (device) {
      ID3D11DeviceContext* deferredContext = NULL;
      HRESULT hr = device -> CreateDeferredContext( 
              contextFlags,
              &deferredContext);
      if (SUCCEEDED(hr)) {
        set(deferredContext);
      } else {
        throw IException("Failed to CreateDeferredContext. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL.");
    }
  }

  ~Direct3D11DeferredContext()
  {
  }

  operator ID3D11DeviceContext*()
  {
    return getDeviceContext();
  }
  
  ID3D11DeviceContext* getDeviceContext()
  {
    ID3D11DeviceContext* context = (ID3D11DeviceContext*)getIUnknown();
    if (context) {
        return context;
    } else {
      throw IException("ID3D11DeviceContext is NULL.");
    }
  }
  
 
};

}

