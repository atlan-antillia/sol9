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
 *  DirectWriteFontList.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteFontList : public ComIUnknown
{
public:
  DirectWriteFontList()
	:ComIUnknown()
  {
  }
	
  DirectWriteFontList(IDWriteFontFamily* family,
        DWRITE_FONT_WEIGHT      weight,
        DWRITE_FONT_STRETCH     stretch,
        DWRITE_FONT_STYLE       style)

  :ComIUnknown()
  {
    IDWriteFontList* list = NULL;
    HRESULT hr = family -> GetMatchingFonts(
        weight,
        stretch,
        style,
        &list
        );
    if (SUCCEEDED(hr)) {
      set(list);
    } else {
      throw IException("Failed to GetMatchingFonts. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectWriteFontList()
  {
  }

  operator IDWriteFontList*()
  {
    return getList();
  }

  IDWriteFontList* getList()
  {
    IDWriteFontList* list = (IDWriteFontList*)getIUnknown();
    if (list) {
      return list;
    } else {
      throw IException("IDWriteFontList is NULL.");
    }
  }
  
  void getFontCollection(
        __out IDWriteFontCollection** fontCollection
        )
  {
    IDWriteFontList* list = getList();
    HRESULT hr = list -> GetFontCollection(
        fontCollection
        );
    if (FAILED(hr)) {
      throw IException("Faield to GetFontCollection. HRESULT(0x%lx)", hr);
    }
  }
  
  UINT32 GetFontCount()
  {
    IDWriteFontList* list = getList();
    return list -> GetFontCount();
  }

  void getFont(
        UINT32 index, 
        __out IDWriteFont** font
        )
  {
    IDWriteFontList* list = getList();
    HRESULT hr = list -> GetFont(
        index, 
        font
        );
    if (FAILED(hr)) {
      throw IException("Faield to GetFont. HRESULT(0x%lx)", hr);
    }
  }

};

}
