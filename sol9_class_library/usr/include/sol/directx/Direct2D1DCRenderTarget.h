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
 *  Direct2D1DCRenderTarget.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1RenderTarget.h>


namespace SOL {

class Direct2D1DCRenderTarget : public Direct2D1RenderTarget
{
public:
  Direct2D1DCRenderTarget(ID2D1Factory* factory,
          __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties)
  :Direct2D1RenderTarget()
  {
    ID2D1DCRenderTarget* target = NULL;
    HRESULT hr = factory -> CreateDCRenderTarget(
        renderTargetProperties,
        &target 
        );
    if (SUCCEEDED(hr)) {
      set(target);
    } else {
      throw IException("Failed to CreateDCRenderTarget. HRESULT(0x%lx)", hr);
    }
  }
  
  
  ~Direct2D1DCRenderTarget()
  {
  }

  operator ID2D1DCRenderTarget*()
  {
    return getTarget();
  }

  virtual ID2D1DCRenderTarget* getTarget()
  {
    ID2D1DCRenderTarget* target = (ID2D1DCRenderTarget*)getIUnknown();
    if (target) {
      return target;
    } else {
      throw IException("ID2D1DCRenderTarget is NULL.");
    }
  }
  

   void bindDC(
        __in CONST HDC hDC,
        __in CONST RECT *pSubRect 
        )
  {
    ID2D1DCRenderTarget* target = getTarget();
    HRESULT hr = target -> BindDC(
        hDC,
        pSubRect 
        );
    if (FAILED(hr)) {
      throw IException("Failed to BindDC. HRESULT(0x%lx)", hr);
    }
  }

}; 
  
}

