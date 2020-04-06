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
 *  DirectWriteBitmapRenderTarget.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteBitmapRenderTarget : public ComIUnknown
{
public:
  DirectWriteBitmapRenderTarget(IDWriteGdiInterop* interop,
        __in_opt HDC hdc,
        UINT32 width,
        UINT32 height,
        __out IDWriteBitmapRenderTarget** renderTarget
        )
  :ComIUnknown()
  {
    IDWriteBitmapRenderTarget* target = NULL;
    HRESULT hr = interop -> CreateBitmapRenderTarget(
        hdc,
        width,
        height,
        renderTarget
        );
    if (SUCCEEDED(hr)) {
      set(target);
    } else {
      throw IException("Failed to CreateBitmapRenderTarget. HRESULT(0x%lx)", hr); 
    }
  }
  
  ~DirectWriteBitmapRenderTarget()
  {
  }
  
  operator IDWriteBitmapRenderTarget*()
  {
    return getTarget();
  }
  
  IDWriteBitmapRenderTarget* getTarget()
  {
    IDWriteBitmapRenderTarget* target = (IDWriteBitmapRenderTarget*)getIUnknown();
    if (target) {
      return target;
    } else {
      throw IException("IDWriteBitmapRenderTarget is NULL.");
    }
  }
  
  void drawGlyphRun(
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        DWRITE_MEASURING_MODE measuringMode,
        __in DWRITE_GLYPH_RUN const* glyphRun,
        IDWriteRenderingParams* renderingParams,
        COLORREF textColor,
        __out RECT* blackBoxRect = NULL
        )
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    HRESULT hr = target -> DrawGlyphRun(
        baselineOriginX,
        baselineOriginY,
        measuringMode,
        glyphRun,
        renderingParams,
        textColor,
        blackBoxRect
        );
    if (FAILED(hr)) {
      throw IException("Failed to DrawGlyphRun. HRESULT(0x%lx)", hr);
    }
  }
  
  HDC getMemoryDC()
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    return target -> GetMemoryDC();
  }

  FLOAT getPixelsPerDip()
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    return target -> GetPixelsPerDip();
  }

  void setPixelsPerDip(
        FLOAT pixelsPerDip
        )
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    HRESULT hr = target -> SetPixelsPerDip(
        pixelsPerDip
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetPixelsPerDip. HRESULT(0x%lx)", hr);
    }
  }

  void getCurrentTransform(
        __out DWRITE_MATRIX* transform
        )
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    HRESULT hr = target -> GetCurrentTransform(
        transform
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetCurrentTransform. HRESULT(0x%lx)", hr);
    }
  }

  void setCurrentTransform(
        __in DWRITE_MATRIX const* transform
        )
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    HRESULT hr = target -> SetCurrentTransform(
        transform
        );
    if (FAILED(hr)) {
      throw IException("Failed to SetCurrentTransform. HRESULT(0x%lx)", hr);
    }
  }

  void getSize(
        __out SIZE* size
        )
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    HRESULT hr = target -> GetSize(
        size
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetSize. HRESULT(0x%lx)", hr);
    }
  }

  void resize(
        UINT32 width,
        UINT32 height
        )
  {
    IDWriteBitmapRenderTarget* target = getTarget();
    HRESULT hr = target -> Resize(
        width,
        height
        );
    if (FAILED(hr)) {
      throw IException("Failed to Resize. HRESULT(0x%lx)", hr);
    }
  }

};

}
