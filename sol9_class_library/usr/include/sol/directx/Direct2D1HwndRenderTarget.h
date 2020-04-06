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
 *  Direct2D1HwndRenderTarget.h
 *
 *****************************************************************************/

// 

#pragma once

#include <sol/directx/Direct2D1Factory.h>
#include <sol/directx/Direct2D1RenderTarget.h>

namespace SOL {
static const float DEFAULT_DPI = 96.f;

class Direct2D1HwndRenderTarget: public Direct2D1RenderTarget
{

public:
  Direct2D1HwndRenderTarget(ID2D1Factory* factory, HWND hwnd, float dpiX=DEFAULT_DPI, float dpiY=DEFAULT_DPI)
  :Direct2D1RenderTarget()
  {
    RECT rc;
    HRESULT hr = GetClientRect(hwnd, &rc);
    if (SUCCEEDED(hr)) {
    
      auto renderTargetProperties = D2D1::RenderTargetProperties();
      renderTargetProperties.dpiX = dpiX;
      renderTargetProperties.dpiY = dpiY;

      auto size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
      ID2D1HwndRenderTarget* target = NULL;
      hr = factory -> CreateHwndRenderTarget(
                renderTargetProperties,
                D2D1::HwndRenderTargetProperties(hwnd, size),
                &target
            );
      if (SUCCEEDED(hr)) {
        set(target);      
      } else {
     
       throw IException("Failed to CreateHwndRenderTarget. HRESULT(0x%lx)", hr);
     }
    } else {
      throw IException("Failed to GetClientRect. HRESULT(0x%lx)", hr);
    }
  }

public:
  Direct2D1HwndRenderTarget(ID2D1Factory* factory, 
       __in CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties,
       __in CONST D2D1_HWND_RENDER_TARGET_PROPERTIES &hwndRenderTargetProperties)
  :Direct2D1RenderTarget()  
  {
    ID2D1HwndRenderTarget* target = NULL;
    HRESULT hr = factory -> CreateHwndRenderTarget(
        renderTargetProperties,
        hwndRenderTargetProperties,
        &target
             );
    if (SUCCEEDED(hr)) {
      set(target);
    } else {
      throw IException("Failed to CreateHwndRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

public:
  ~Direct2D1HwndRenderTarget()
  {
  }

  operator ID2D1HwndRenderTarget*()
  {
    return getTarget();
  }

  virtual ID2D1HwndRenderTarget* getTarget()
  {
    ID2D1HwndRenderTarget* target = (ID2D1HwndRenderTarget*)getIUnknown();
    if (target) {
      return target;
    } else {
      throw IException("ID2D1HwndRenderTarget is NULL.");
    }
  }
  
  D2D1_WINDOW_STATE checkWindowState()
  {
    ID2D1HwndRenderTarget* target = getTarget();
    return target -> CheckWindowState();
  }
    
  void resize(__in CONST D2D1_SIZE_U *pixelSize )
  {
    ID2D1HwndRenderTarget* target = getTarget();
    HRESULT hr = target -> Resize(pixelSize );
    if (FAILED(hr)) {
      throw IException("Failed to Resize. HRESULT(0x%lx)", hr);
    }
  }
    
  HWND  getHwnd()
  {
    ID2D1HwndRenderTarget* target = getTarget();
    return target -> GetHwnd();
  }
    
  void resize(CONST D2D1_SIZE_U &pixelSize)
  {
    ID2D1HwndRenderTarget* target = getTarget();
    HRESULT hr = target -> Resize(pixelSize);
    if (FAILED(hr)) {
      throw IException("Failed to Resize. HRESULT(0x%lx)", hr);
    }
  }
};

}
