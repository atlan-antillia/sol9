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
 *  DirectWriteFontFileLoader.h
 *
 *****************************************************************************/

#pragma once
#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d2d1.h>
#include <dwrite.h>

namespace SOL {

class DirectWriteFontFileLoader : public ComIUnknown
{
public:
  DirectWriteFontFileLoader()
  :ComIUnknown()
  {
  }
	
  DirectWriteFontFileLoader(IDWriteFontFile* file)
  :ComIUnknown()
  {
    IDWriteFontFileLoader* loader = NULL;
    HRESULT hr  = file -> GetLoader(
        &loader
        );
    if (SUCCEEDED(hr)) {
      set(loader);
    } else {
      throw IException("Failed to GetLoader. HRESULT(0x%lx)", hr);
    }
  }

  ~DirectWriteFontFileLoader()
  {
  }

  operator IDWriteFontFileLoader*()
  {
    return getLoader();
  }

  IDWriteFontFileLoader* getLoader()
  {
    IDWriteFontFileLoader* loader = (IDWriteFontFileLoader*)getIUnknown();
    if (loader) {
      return loader;
    } else {
      throw IException("IDWriteFontFileLoader is NULL.");
    }
  }
  
  void createStreamFromKey(
        __in void const* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        __out IDWriteFontFileStream** fontFileStream
        )
  {
    IDWriteFontFileLoader* loader = getLoader();
    HRESULT hr = loader -> CreateStreamFromKey(
        fontFileReferenceKey,
        fontFileReferenceKeySize,
        fontFileStream
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateStreamFromKey. HRESULT(0x%lx)", hr);
      
    }
  }
  
};
}
