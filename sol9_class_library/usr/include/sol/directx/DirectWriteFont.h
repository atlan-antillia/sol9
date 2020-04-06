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
 *  DirectWriteFont.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>


namespace SOL {

class DirectWriteFont : public ComIUnknown
{
public:
  DirectWriteFont(IDWriteFontCollection* collection,
        IDWriteFontFace* fontFace)
  :ComIUnknown()
  {
    IDWriteFont* font = NULL;
    HRESULT hr = collection -> GetFontFromFontFace(
        fontFace,
        &font
        );
    if (SUCCEEDED(hr)) {
      set(font);
    } else {
      throw IException("Failed to GetFontFromFontFace. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFont(IDWriteFontFamily* family,
        DWRITE_FONT_WEIGHT  weight,
        DWRITE_FONT_STRETCH stretch,
        DWRITE_FONT_STYLE   style)    
  :ComIUnknown()
  {
    IDWriteFont* font = NULL;
    HRESULT hr = family -> GetFirstMatchingFont(
        weight,
        stretch,
        style,
        &font
        );
    if (SUCCEEDED(hr)) {
      set(font);
    } else {
      throw IException("Failed to GetFirstMatchingFont. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFont(IDWriteFontList* list,
          UINT32 index)
  :ComIUnknown()
  {
    IDWriteFont* font = NULL;
    HRESULT hr = list -> GetFont(
        index, 
        &font
        );
    if (SUCCEEDED(hr)) {
      set(font);
    } else {
      throw IException("Failed to GetFont. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFont(IDWriteGdiInterop* interop,
      __in LOGFONTW const* logFont)
  :ComIUnknown()
  {
    IDWriteFont* font = NULL;
    HRESULT hr = interop -> CreateFontFromLOGFONT(
        logFont,
        &font
        );
    if (SUCCEEDED(hr)) {
      set(font);
    } else {
      throw IException("Failed to CreateFontFromLOGFONT. HRESULT(0x%lx)", hr);
    }
  }
  
  
  ~DirectWriteFont()
  {
  }

  operator IDWriteFont*()
  {
    return getFont();
  }

  IDWriteFont* getFont()
  {
    IDWriteFont* font = (IDWriteFont*)getIUnknown();
    if (font) {
      return font;
    } else {
      throw IException("IDWriteFont is NULL.");
    }
  }
  
  void getFontFamily(
        __out IDWriteFontFamily** fontFamily
        )
  {
    IDWriteFont* font = getFont();
    HRESULT hr = font -> GetFontFamily(
        fontFamily
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontFamily. HRESULT(0x%lx)", hr);
    }
  }

  DWRITE_FONT_WEIGHT getWeight()
  {
    IDWriteFont* font = getFont();
    font -> GetWeight();
  }

  DWRITE_FONT_STRETCH getStretch()
  {
    IDWriteFont* font = getFont();
    font -> GetStretch();
  }

  DWRITE_FONT_STYLE getStyle()
  {
    IDWriteFont* font = getFont();
    font -> GetStyle();
  }

  BOOL isSymbolFont()
  {
    IDWriteFont* font = getFont();
    font -> IsSymbolFont();
  }

  void getFaceNames(
        __out IDWriteLocalizedStrings** names
        )
  {
    IDWriteFont* font = getFont();
    font -> GetFaceNames(names);
  }

  void getInformationalStrings(
        DWRITE_INFORMATIONAL_STRING_ID informationalStringID,
        __out IDWriteLocalizedStrings** informationalStrings,
        __out BOOL* exists
        )
  {
    IDWriteFont* font = getFont();
    HRESULT hr = font -> GetInformationalStrings(
        informationalStringID,
        informationalStrings,
        exists
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetInformationalStrings. HRESULT(0x%lx)", hr);
    }
  }

  DWRITE_FONT_SIMULATIONS getSimulations()
  {
    IDWriteFont* font = getFont();
    font -> GetSimulations();
  }

  void getMetrics(
        __out DWRITE_FONT_METRICS* metrics 
        )
  {
    IDWriteFont* font = getFont();
    font -> GetMetrics(
        metrics
        );
  }
  
  void hasCharacter(
        UINT32 unicodeValue,
        __out BOOL* exists
        )
  {
    IDWriteFont* font = getFont();
    HRESULT hr = font -> HasCharacter(
        unicodeValue,
        exists
        );
    if (FAILED(hr)) {
      throw IException("Failed to HasCharacter. HRESULT(0x%lx)", hr);
    }
  }

  void createFontFace(
        __out IDWriteFontFace** fontFace
        )
  {
    IDWriteFont* font = getFont();
    HRESULT hr = font -> CreateFontFace(
        fontFace
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateFontFace. HRESULT(0x%lx)", hr);
    }
  }
};

}
