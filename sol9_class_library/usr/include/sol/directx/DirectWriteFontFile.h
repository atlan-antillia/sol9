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
 *  DirectWriteFontFile.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteFontFile : public ComIUnknown
{
public:
  DirectWriteFontFile()
  :ComIUnknown()
  {
  }

public:
  DirectWriteFontFile(IDWriteFactory* factory,
        __in_z WCHAR const* filePath,
        __in FILETIME const* lastWriteTime)
  :ComIUnknown()
  {
    IDWriteFontFile* file = NULL;
    HRESULT hr = factory -> CreateFontFileReference(
        filePath,
        lastWriteTime,
        &file
        );
    if (SUCCEEDED(hr)) {
      set(file);
    } else {
      throw IException("Failed to CreateFontFileReference. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFontFile(IDWriteFactory* factory,
        __in void const* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        IDWriteFontFileLoader* fontFileLoader)
  :ComIUnknown()
  {
    IDWriteFontFile* file = NULL;
  
    HRESULT hr = factory -> CreateCustomFontFileReference(
        fontFileReferenceKey,
        fontFileReferenceKeySize,
        fontFileLoader,
        &file
        );
    if (SUCCEEDED(hr)) {
      set(file);
    } else {
      throw IException("Failed to CreateCustomFontFileReference. HRESULT(0x%lx)", hr);
    }
  }

  DirectWriteFontFile(IDWriteFontFileEnumerator* enumerator)
  :ComIUnknown()
  {
    IDWriteFontFile* file = NULL;
    HRESULT hr = enumerator -> GetCurrentFontFile(
        &file
        );
    if (SUCCEEDED(hr)) {
      set(file);
    } else {
      throw IException("Failed to GetCurrentFontFile. HRESULT(0x%lx)", hr);
    }
  }


  ~DirectWriteFontFile()
  {
  }

  operator IDWriteFontFile*()
  {
    return getFile();
  }

  IDWriteFontFile* getFile()
  {
    IDWriteFontFile* file = (IDWriteFontFile* )getIUnknown();
    if (file) {
      return file;
    } else {
      throw IException("IDWriteFontFile is NULL.");
    }
  }
  
  void getReferenceKey(
        __out void const** fontFileReferenceKey,
        __out UINT32* fontFileReferenceKeySize
        )
  {
    IDWriteFontFile* file = getFile();
    HRESULT hr = file -> GetReferenceKey(
        fontFileReferenceKey,
        fontFileReferenceKeySize
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetReferenceKey. HRESULT(0x%lx)", hr);
    }
  }
  
  void getLoader(
        __out IDWriteFontFileLoader** fontFileLoader
        )
  {
    IDWriteFontFile* file = getFile();
    HRESULT hr = file -> GetLoader(
        fontFileLoader
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLoader. HRESULT(0x%lx)", hr);
    }
  }

  void analyze(
        __out BOOL* isSupportedFontType,
        __out DWRITE_FONT_FILE_TYPE* fontFileType,
        __out DWRITE_FONT_FACE_TYPE* fontFaceType,
        __out UINT32* numberOfFaces
        )
  {
    IDWriteFontFile* file = getFile();
    HRESULT hr = file -> Analyze(
        isSupportedFontType,
        fontFileType,
        fontFaceType,
        numberOfFaces
        );
    if (FAILED(hr)) {
      throw IException("Failed to Analyze. HRESULT(0x%lx)", hr);
    }
  }

};


}
