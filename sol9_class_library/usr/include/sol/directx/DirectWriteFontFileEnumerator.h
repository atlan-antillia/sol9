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
 *  DirectWriteFontFileEnumerator.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteFontFileEnumerator : public ComIUnknown
{
public:
  DirectWriteFontFileEnumerator()
  {
  }

  DirectWriteFontFileEnumerator(IDWriteFactory* factory, IDWriteFontCollectionLoader* loader,
        __in void const* collectionKey,
        UINT32 collectionKeySize)
  :ComIUnknown()
  {
    IDWriteFontFileEnumerator* enumerator = NULL;
    HRESULT hr = loader -> CreateEnumeratorFromKey(
        factory,
         collectionKey,
        collectionKeySize,
        &enumerator
        );
    if (SUCCEEDED(hr)) {
      set(enumerator);
    } else {
      throw IException("Failed to CreateEnumeratorFromKey. HRESUL(0x%lx)", hr);
    }
  }
  
  ~DirectWriteFontFileEnumerator()
  {
  }

  operator IDWriteFontFileEnumerator*()
  {
    return getEnumerator();
  }

  IDWriteFontFileEnumerator* getEnumerator()
  {
    IDWriteFontFileEnumerator* enumerator = (IDWriteFontFileEnumerator*)getIUnknown();
    if (enumerator) {
      return enumerator;
    } else {
      throw IException("IDWriteFontFileEnumerator is NULL.");
    }
  }
  
  void moveNext(
        __out BOOL* hasCurrentFile
        )
  {
    IDWriteFontFileEnumerator* enumerator = getEnumerator();
    HRESULT hr = enumerator -> MoveNext(
        hasCurrentFile
        );
    if (FAILED(hr)) {
      throw IException("Failed to MoveNext. HRESUL(0x%lx)", hr);
    }
  }
  
  void getCurrentFontFile(
        __out IDWriteFontFile** fontFile
        )
  {
    IDWriteFontFileEnumerator* enumerator = getEnumerator();
    HRESULT hr = enumerator -> GetCurrentFontFile(
        fontFile
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetCurrentFontFile. HRESUL(0x%lx)", hr);
    }
  }

};



}
