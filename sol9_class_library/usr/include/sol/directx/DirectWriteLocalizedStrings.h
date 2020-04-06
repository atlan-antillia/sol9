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
 *  DirectWriteLocalizedStrings.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteLocalizedStrings : public ComIUnknown
{
public:
  DirectWriteLocalizedStrings(IDWriteFont* font)
  :ComIUnknown()
  {
    IDWriteLocalizedStrings* strings = NULL;
    HRESULT hr = font -> GetFaceNames(
        &strings
        );
    if (SUCCEEDED(hr)) {
      set(strings);
    } else {
      throw IException("Failed to GetFaceNames. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteLocalizedStrings(IDWriteFont* font,
        DWRITE_INFORMATIONAL_STRING_ID informationalStringID)
  :ComIUnknown()
  {
    IDWriteLocalizedStrings* strings = NULL;
    BOOL exists = FALSE;
    HRESULT hr = font -> GetInformationalStrings(
        informationalStringID,
        &strings,
        &exists
        );
    if (SUCCEEDED(hr) && exists) {
      set(strings);
    } else {
      throw IException("Failed to GetInformationalStrings. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteLocalizedStrings(IDWriteFontFamily* family)
  :ComIUnknown()
  {
    IDWriteLocalizedStrings* strings = NULL;
    
    HRESULT hr = family -> GetFamilyNames(
        &strings
        );
    if (SUCCEEDED(hr)) {
      set(strings);
    } else {
      throw IException("Failed to GetFamilyNames. HRESULT(0x%lx)", hr);
    }
  }
  
  operator IDWriteLocalizedStrings*()
  {
    return getStrings();
  }

  IDWriteLocalizedStrings* getStrings()
  {
    IDWriteLocalizedStrings* strings = (IDWriteLocalizedStrings*)getIUnknown();
    if (strings) {
      return strings;
    } else {
      throw IException("IDWriteLocalizedStrings is NULL.");
    }
  }
  
  UINT32 getCount()
  {
    IDWriteLocalizedStrings* strings = getStrings();
    return strings -> GetCount();
  }
  
  void findLocaleName(
        __in_z WCHAR const* localeName, 
        __out UINT32* index,
        __out BOOL* exists
        )
 {
    IDWriteLocalizedStrings* strings = getStrings();
    HRESULT hr = strings -> FindLocaleName(
        localeName, 
        index,
        exists
        );
    if (FAILED(hr)) {
      throw IException("Failed to FindLocaleName. HRESULT(0x%lx)", hr);
    }
  }
 
  void getLocaleNameLength(
        UINT32 index,
        __out UINT32* length
        )
 {
    IDWriteLocalizedStrings* strings = getStrings();
    HRESULT hr = strings -> GetLocaleNameLength(
        index,
        length
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLocaleNameLength. HRESULT(0x%lx)", hr);
    }
  }

  void getLocaleName(
        UINT32 index,
        __out WCHAR* localeName,
        UINT32 size
        )
 {
    IDWriteLocalizedStrings* strings = getStrings();
    HRESULT hr = strings -> GetLocaleName(
        index,
        localeName,
        size
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLocaleName. HRESULT(0x%lx)", hr);
    }
  }

  void getStringLength(
        UINT32 index,
        __out UINT32* length
        )
 {
    IDWriteLocalizedStrings* strings = getStrings();
    HRESULT hr = strings -> GetStringLength(
        index,
        length
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetStringLength. HRESULT(0x%lx)", hr);
    }
  }

  void getString(
        UINT32 index,
        __out WCHAR* stringBuffer,
        UINT32 size
        )
 {
    IDWriteLocalizedStrings* strings = getStrings();
    HRESULT hr = strings -> GetString(
        index,
        stringBuffer,
        size
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetString. HRESULT(0x%lx)", hr);
    }
  }
};

}
