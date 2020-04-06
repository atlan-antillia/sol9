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
 *  Direct2D1BitmapRenderTarget.h
 *
 *****************************************************************************/

#pragma once

#include <sol/wic/WICFormatConverter.h>
#include <sol/directx/Direct2D1RenderTarget.h>
#include <sol/directx/Direct2D1Bitmap.h>
#include <sol/directx/Direct2D1RenderTarget.h>

namespace SOL {

class Direct2D1BitmapRenderTarget: public Direct2D1RenderTarget
{
public:
  Direct2D1BitmapRenderTarget(ID2D1RenderTarget* target,
        __in CONST D2D1_SIZE_F *desiredSize,
        __in CONST D2D1_SIZE_U *desiredPixelSize,
        __in CONST D2D1_PIXEL_FORMAT *desiredFormat,
        __in D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options)
  {
    ID2D1BitmapRenderTarget* brTarget = NULL;
    HRESULT hr = target -> CreateCompatibleRenderTarget(
           desiredSize,
           desiredPixelSize,
           desiredFormat,
           options,
           &brTarget 
        );
    if (SUCCEEDED(hr)) {
      set(brTarget);    
    } else {
      throw IException("Failed to CreateCompatibleRenderTarget. HRESULT(0x%lx)", hr);
    }
  }
   
  ~Direct2D1BitmapRenderTarget()
  {
  }

  operator ID2D1BitmapRenderTarget*()
  {
    return getTarget();
  }

  ID2D1BitmapRenderTarget* getTarget()
  {
    ID2D1BitmapRenderTarget* target = (ID2D1BitmapRenderTarget*)getIUnknown();
    if (target) {
      return target;
    } else {
      throw IException("ID2D1BitmapRenderTarget is NULL.");
    }
  }
  
 
  void getBitmap(__out ID2D1Bitmap **bitmap)
  {
    ID2D1BitmapRenderTarget* target = getTarget();
    HRESULT hr = target -> GetBitmap(bitmap);
    if (FAILED(hr)) {
      throw IException("Failed to GetBitmap. HRESULT(0x%lx)", hr);
    }
  }
}; 

}


