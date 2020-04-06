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
 *  DirectWriteGdiInterop.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteGdiInterop : public ComIUnknown
{
public:
  DirectWriteGdiInterop(IDWriteFactory* factory)
  :ComIUnknown()
  {
    IDWriteGdiInterop* interop = NULL;
    HRESULT hr = factory -> GetGdiInterop(
        &interop
        );
    if (SUCCEEDED(hr)) {
      set(interop);
    } else {
      throw IException("Failed to GetGdiInterop. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectWriteGdiInterop()
  {
  }

  operator IDWriteGdiInterop*()
  {
    return getInterop();
  }

  IDWriteGdiInterop* getInterop()
  {
    IDWriteGdiInterop* interop = (IDWriteGdiInterop*)getIUnknown();
    if (interop) {
      return interop;
    } else {
      throw IException("IDWriteGdiInterop is NULL.");
    }
  }

  void createFontFromLOGFONT(
        __in LOGFONTW const* logFont,
        __out IDWriteFont** font
        )
  {
    IDWriteGdiInterop* interop = getInterop();
    HRESULT hr = interop -> CreateFontFromLOGFONT(
        logFont,
        font
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateFontFromLOGFONT. HRESULT(0x%lx)", hr);
    }
  }
  
  void convertFontToLOGFONT(
        IDWriteFont* font,
        __out LOGFONTW* logFont,
        __out BOOL* isSystemFont
        )
  {
    IDWriteGdiInterop* interop = getInterop();
    HRESULT hr = interop -> ConvertFontToLOGFONT(
        font,
        logFont,
        isSystemFont
        );
    if (FAILED(hr)) {
      throw IException("Failed to ConvertFontToLOGFONT. HRESULT(0x%lx)", hr);
    }
  }

  void convertFontFaceToLOGFONT(
        IDWriteFontFace* font,
        __out LOGFONTW* logFont
        )
  {
    IDWriteGdiInterop* interop = getInterop();
    HRESULT hr = interop -> ConvertFontFaceToLOGFONT(
        font,
        logFont
        );
    if (FAILED(hr)) {
      throw IException("Failed to ConvertFontFaceToLOGFONT. HRESULT(0x%lx)", hr);
    }
  }

  void createFontFaceFromHdc(
        HDC hdc,
        __out IDWriteFontFace** fontFace
        )
  {
    IDWriteGdiInterop* interop = getInterop();
    HRESULT hr = interop -> CreateFontFaceFromHdc(
        hdc,
        fontFace
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateFontFaceFromHdc. HRESULT(0x%lx)", hr);
    }
  }

  void createBitmapRenderTarget(
        __in HDC hdc,
        UINT32 width,
        UINT32 height,
        __out IDWriteBitmapRenderTarget** renderTarget
        )
  {
    IDWriteGdiInterop* interop = getInterop();
    HRESULT hr = interop -> CreateBitmapRenderTarget(
        hdc,
        width,
        height,
        renderTarget
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

};

}
