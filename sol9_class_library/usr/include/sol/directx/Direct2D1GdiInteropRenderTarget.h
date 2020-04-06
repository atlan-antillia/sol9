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
 *  Direct2D1GdiInteropRenderTarget.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>


namespace SOL {

class Direct2D1GdiInteropRenderTarget : public ComIUnknown
{
public:
  Direct2D1GdiInteropRenderTarget()
  :ComIUnknown()
  {  
  }
  
  ~Direct2D1GdiInteropRenderTarget()
  {  
  }
  
  operator ID2D1GdiInteropRenderTarget*()
  {
    return getTarget();
  }

  ID2D1GdiInteropRenderTarget* getTarget()
  {
    ID2D1GdiInteropRenderTarget* target = (ID2D1GdiInteropRenderTarget*)getIUnknown();
    if (target) {
      return target;
    } else {
      throw IException("ID2D1GdiInteropRenderTarget is NULL.");
    }
  }
  
     
  void getDC(
        D2D1_DC_INITIALIZE_MODE mode,
        __out HDC *hdc 
        )
  {
    ID2D1GdiInteropRenderTarget* target = getTarget();
    HRESULT hr = target -> GetDC(
        mode,
        hdc 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetDC. HRESULT(0x%lx)", hr);
    }
  }
  
  void releaseDC(
        __in_opt CONST RECT *update 
        )
  {
    ID2D1GdiInteropRenderTarget* target = getTarget();
    HRESULT hr = target -> ReleaseDC(
        update 
        );
    if (FAILED(hr)) {
      throw IException("Failed to ReleaseDC. HRESULT(0x%lx)", hr);
    }
  }
};

}
