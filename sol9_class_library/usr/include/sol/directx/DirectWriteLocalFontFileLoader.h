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
 *  DirectWriteLocalFontFileLoader.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>
#include <sol/directx/DirectWriteFontFileLoader.h>

namespace SOL {

class DirectWriteLocalFontFileLoader : public DirectWriteFontFileLoader
{
public:
  DirectWriteLocalFontFileLoader()
  :DirectWriteFontFileLoader()
  {
  }

  ~DirectWriteLocalFontFileLoader()
  {
  }


  operator  IDWriteLocalFontFileLoader*()
  {
    return getLoader();
  }

  IDWriteLocalFontFileLoader* getLoader()
  {
    IDWriteLocalFontFileLoader* loader = (IDWriteLocalFontFileLoader*)getIUnknown();
    if (loader) {
      return loader;
    } else {
      throw IException("IDWriteLocalFontFileLoader is NULL.");
    }
  }
  
  void getFilePathLengthFromKey(
        __in void const* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        __out UINT32* filePathLength
        )
  {
    IDWriteLocalFontFileLoader* loader = getLoader();
    HRESULT hr = loader -> GetFilePathLengthFromKey(
        fontFileReferenceKey,
        fontFileReferenceKeySize,
        filePathLength
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFilePathLengthFromKey. HRESULT(0x%lx)", hr);
    }
  }
  
  void getFilePathFromKey(
        __in void const* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        __out WCHAR* filePath,
        UINT32 filePathSize
        )
  {
    IDWriteLocalFontFileLoader* loader = getLoader();
    HRESULT hr = loader -> GetFilePathFromKey(
        fontFileReferenceKey,
        fontFileReferenceKeySize,
        filePath,
        filePathSize
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFilePathFromKey. HRESULT(0x%lx)", hr);
    }
  }

  void getLastWriteTimeFromKey(
        __in void const* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        __out FILETIME* lastWriteTime
        )
  {
    IDWriteLocalFontFileLoader* loader = getLoader();
    HRESULT hr = loader -> GetLastWriteTimeFromKey(
        fontFileReferenceKey,
        fontFileReferenceKeySize,
        lastWriteTime
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLastWriteTimeFromKey. HRESULT(0x%lx)", hr);
    }
  }

};

}
