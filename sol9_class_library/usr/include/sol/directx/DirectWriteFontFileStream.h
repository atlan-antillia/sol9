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
 *  DirectWriteFontFileStream.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>


namespace SOL {

class DirectWriteFontFileStream : public ComIUnknown
{
public:
  DirectWriteFontFileStream(IDWriteFontFileLoader* loader,
        __in void const* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize)
  :ComIUnknown()
  {
    IDWriteFontFileStream* stream = NULL;
    HRESULT hr = loader ->  CreateStreamFromKey(
        fontFileReferenceKey,
        fontFileReferenceKeySize,
        &stream
        );
    if (SUCCEEDED(hr)) {
      set(stream);
    } else  {
      throw IException("Failed to CreateStreamFromKey. HRESULT(0x%lx)", hr);
      
    }
  }

  ~DirectWriteFontFileStream()
  {
  }

  operator IDWriteFontFileStream*()
  {
    return getStream();
  }

  IDWriteFontFileStream* getStream()
  {
    IDWriteFontFileStream* stream = (IDWriteFontFileStream*)getIUnknown();
    if (stream) {
      return stream;
    } else {
      throw IException("IDWriteFontFileStream is NULL.");
    }
  }
  
  void readFileFragment(
        __out void const** fragmentStart,
        UINT64 fileOffset,
        UINT64 fragmentSize,
        __out void** fragmentContext
        )
  {
    IDWriteFontFileStream* stream = getStream();
    HRESULT hr = stream -> ReadFileFragment(
        fragmentStart,
        fileOffset,
        fragmentSize,
        fragmentContext
        );
    if (FAILED(hr)) {
      throw IException("Failed to ReadFileFragment. HRESULT(0x%lx)", hr);
    }
  }

  void releaseFileFragment(
        void* fragmentContext
        )
  {
    IDWriteFontFileStream* stream = getStream();
    stream -> ReleaseFileFragment(
        fragmentContext
        );
  }

  void getFileSize(
        __out UINT64* fileSize
        )
  {
    IDWriteFontFileStream* stream = getStream();
    HRESULT hr = stream -> GetFileSize(
        fileSize
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetFileSize. HRESULT(0x%lx)", hr);
    }
  }

  void getLastWriteTime(
        __out UINT64* lastWriteTime
        )
  {
    IDWriteFontFileStream* stream = getStream();
    HRESULT hr = stream -> GetLastWriteTime(
        lastWriteTime
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetLastWriteTime. HRESULT(0x%lx)", hr);
    }
  }

};

}
