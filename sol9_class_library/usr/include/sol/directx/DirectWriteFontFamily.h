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
 *  DirectWriteFontFamily.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/DirectWriteFontList.h>

namespace SOL {

class DirectWriteFontFamily : public DirectWriteFontList
{
public:
  DirectWriteFontFamily()
  :DirectWriteFontList()
  {
  }
  
public:
  DirectWriteFontFamily(IDWriteFont* font)
  :DirectWriteFontList()
  {
    IDWriteFontFamily* family = NULL;
    HRESULT hr = font -> GetFontFamily(
        &family
        );
    if (SUCCEEDED(hr)) {
      set(family);
    } else {
      throw IException("Failed to GetFontFamily. HRESULT(0x%lx)", hr);
    }
  }

public:
  DirectWriteFontFamily(IDWriteFontCollection* collection, UINT32 index)
  :DirectWriteFontList()
  {
    IDWriteFontFamily* family = NULL;
    HRESULT hr = collection -> GetFontFamily(
        index,
        &family
        );
    if (SUCCEEDED(hr)) {
      set(family);
    } else {
      throw IException("Failed to GetFontFamily. HRESULT(0x%lx)", hr);
    }
  }

public:
  ~DirectWriteFontFamily()
  {
  }

  operator IDWriteFontFamily*()
  {
    return getFamily();
  }

  IDWriteFontFamily* getFamily()
  {
    IDWriteFontFamily* family = (IDWriteFontFamily*)getIUnknown();
    if (family) {
      return family;
    } else {
      throw IException("IDWriteFontFamily is NULL.");
    }
  }
  
  void getFamilyNames(
        __out IDWriteLocalizedStrings** names
        )
  {
    IDWriteFontFamily* family = getFamily();
    HRESULT hr = family -> GetFamilyNames(
        names
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFamilyNames. HRESULT(0x%lx)", hr);
    }
  }
  
  void getFirstMatchingFont(
        DWRITE_FONT_WEIGHT  weight,
        DWRITE_FONT_STRETCH stretch,
        DWRITE_FONT_STYLE   style,
        __out IDWriteFont** matchingFont
        )
  {
    IDWriteFontFamily* family = getFamily();
    HRESULT hr = family -> GetFirstMatchingFont(
        weight,
        stretch,
        style,
        matchingFont
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFirstMatchingFont. HRESULT(0x%lx)", hr);
    }
  }

  void getMatchingFonts(
        DWRITE_FONT_WEIGHT      weight,
        DWRITE_FONT_STRETCH     stretch,
        DWRITE_FONT_STYLE       style,
        __out IDWriteFontList** matchingFonts
        )
  {
    IDWriteFontFamily* family = getFamily();
    HRESULT hr = family -> GetMatchingFonts(
        weight,
        stretch,
        style,
        matchingFonts
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetMatchingFonts. HRESULT(0x%lx)", hr);
    }
  }
};
}
