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
 *  DirectWriteFontCollection.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteFontCollection : public ComIUnknown
{
public:
  DirectWriteFontCollection(IDWriteFactory* factory, BOOL checkForUpdates = FALSE)
  {
    IDWriteFontCollection* collection = NULL;
    HRESULT hr = factory -> GetSystemFontCollection(
        &collection,
        checkForUpdates
        );
    if (SUCCEEDED(hr)) {
      set(collection);
    } else {
      throw IException("Failed to GetSystemFontCollection. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFontCollection(IDWriteFactory* factory,
    IDWriteFontCollectionLoader* collectionLoader,
        __in void const* collectionKey,
        UINT32 collectionKeySize)
  {
    IDWriteFontCollection* collection = NULL;
    HRESULT hr = factory -> CreateCustomFontCollection(
        collectionLoader,
        collectionKey,
        collectionKeySize,
        &collection
        );
    if (SUCCEEDED(hr)) {
      set(collection);
    } else {
      throw IException("Failed to CreateCustomFontCollection. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFontCollection(IDWriteFontList* list)
  {
    IDWriteFontCollection* collection = NULL;
    HRESULT hr = list -> GetFontCollection(
        &collection
        );
    if (SUCCEEDED(hr)) {
      set(collection);
    } else {
      throw IException("Failed to GetFontCollection. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFontCollection(IDWriteTextFormat* format)
  {
    IDWriteFontCollection* collection = NULL;
    HRESULT hr = format -> GetFontCollection(
        &collection
        );
    if (SUCCEEDED(hr)) {
      set(collection);
    } else {
      throw IException("Failed to GetFontCollection. HRESULT(0x%lx)", hr);
    }
  }
  
  DirectWriteFontCollection(IDWriteTextLayout* layout,
        UINT32 currentPosition,
        __out DWRITE_TEXT_RANGE* textRange = NULL)
  {
    IDWriteFontCollection* collection = NULL;
    HRESULT hr = layout -> GetFontCollection(
        currentPosition,
        &collection,
        textRange
        );
    if (SUCCEEDED(hr)) {
      set(collection);
    } else {
      throw IException("Failed to GetFontCollection. HRESULT(0x%lx)", hr);
    }
  }
  
  ~DirectWriteFontCollection()
  {
  }

  operator IDWriteFontCollection*()
  {
    return getCollection();
  }

  IDWriteFontCollection* getCollection()
  {
    IDWriteFontCollection* collection = (IDWriteFontCollection*)getIUnknown();
    if (collection) {
      return collection;
    } else {
      throw IException("IDWriteFontCollection is NULL.");
    }
  }
  
  
  UINT32 getFontFamilyCount()
  {
    IDWriteFontCollection* collection = getCollection();
    return collection -> GetFontFamilyCount();
  }
  
  void getFontFamily(
        UINT32 index,
        __out IDWriteFontFamily** fontFamily
        )
  {
    IDWriteFontCollection* collection = getCollection();
    HRESULT hr = collection -> GetFontFamily(
        index,
        fontFamily
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontFamily. HRESULT(0x%lx)", hr);
    }
  }

  void findFamilyName(
        __in_z WCHAR const* familyName,
        __out UINT32* index,
        __out BOOL* exists
        )
  {
    IDWriteFontCollection* collection = getCollection();
    HRESULT hr = collection -> FindFamilyName(
        familyName,
        index,
        exists
        );
    if (FAILED(hr)) {
      throw IException("Failed to FindFamilyName. HRESULT(0x%lx)", hr);
    }
  }

  void getFontFromFontFace(
        IDWriteFontFace* fontFace,
        __out IDWriteFont** font
        )
  {
    IDWriteFontCollection* collection = getCollection();
    HRESULT hr = collection -> GetFontFromFontFace(
        fontFace,
        font
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFontFromFontFace. HRESULT(0x%lx)", hr);
    }
  }

};


}
