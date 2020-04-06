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
 *  DirectWriteTypography.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteTypography : public ComIUnknown
{
public:
  DirectWriteTypography(IDWriteFactory* factory)
  :ComIUnknown()
  {
    IDWriteTypography* typography = NULL;
    HRESULT hr = factory -> CreateTypography(
        &typography
        );
    if (SUCCEEDED(hr)) {
      set(typography);
    } else {
      throw IException("Failed to CreateTypography. HRESULT(0x%lx)", hr);
    }
  }

public:
  DirectWriteTypography(IDWriteTextLayout* layout,
        UINT32 currentPosition,
        __out_opt DWRITE_TEXT_RANGE* textRange = NULL
        )
  :ComIUnknown()
  {
    IDWriteTypography* typography = NULL;
    HRESULT hr = layout -> GetTypography(
        currentPosition,
        &typography,
        textRange
        );
    if (SUCCEEDED(hr)) {
      set(typography);
    } else {
      throw IException("Failed to GetTypography. HRESULT(0x%lx)", hr);
    }
  }


  operator IDWriteTypography*()
  {
    return getTypography();
  }

  IDWriteTypography* getTypography()
  {
    IDWriteTypography* typography = (IDWriteTypography*)getIUnknown();
    if (typography) {
      return typography;
    } else {
      throw IException("IDWriteTypography is NULL.");
    }
  }
  
  void addFontFeature(
        DWRITE_FONT_FEATURE fontFeature
        )
  {
    IDWriteTypography* typography = getTypography();
    HRESULT hr = typography -> AddFontFeature(
        fontFeature
        );
    if (FAILED(hr)) {
      throw IException("Failed to AddFontFeature. HRESULT(0x%lx)", hr);
    }
  }
  
  UINT32 getFontFeatureCount()
  {
    IDWriteTypography* typography = getTypography();
    return typography -> GetFontFeatureCount();
  }

  void getFontFeature(
        UINT32 fontFeatureIndex,
        __out DWRITE_FONT_FEATURE* fontFeature
        )
  {
    IDWriteTypography* typography = getTypography();
    HRESULT hr = typography -> GetFontFeature(
        fontFeatureIndex,
        fontFeature
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontFeature. HRESULT(0x%lx)", hr);
    }
  }
};


}
