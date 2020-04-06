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
 *  WICStream.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/com/Stream.h>

namespace SOL {
  
class WICStream: public Stream
{
  
public:
  WICStream()
  :Stream()
  {
  }
  
  WICStream(IWICImagingFactory* factory)
  :Stream()
  {
    IWICStream* stream = NULL;
    HRESULT hr = factory -> CreateStream( 
           &stream);
    if (SUCCEEDED(hr)) {
      set(stream);
    } else {
      throw IException("Failed to CreateStream. HRESULT(0x%lx)", hr);  
    }
  }

  ~WICStream()
  {
  }

  operator IWICStream*()
  {
    return getWICStream();
  }

  IWICStream* getWICStream()
  {
    IWICStream* stream = (IWICStream*)getIUnknown();
    if (stream) {
      return stream;
    } else {
      throw IException("IWICStream is NULL.");
    }
  }
  
  void initializeFromIStream( 
            __in IStream *pIStream)
  {
    IWICStream* stream = getWICStream();
    HRESULT hr = stream -> InitializeFromIStream( 
         pIStream);    
    if (FAILED(hr)) {
      throw IException("Failed to InitializeFromIStream. HRESULT(0x%lx)", hr);
    }
  }
  
  void initializeFromFilename( 
            __in  LPCWSTR wzFileName,
            __in DWORD dwDesiredAccess)
  {
    IWICStream* stream = getWICStream();
    HRESULT hr = stream -> InitializeFromFilename( 
            wzFileName,
            dwDesiredAccess);
    if (FAILED(hr)) {
      throw IException("Failed to IntializeFromFilename. HRESULT(0x%lx)", hr);
    }
  }
  
        
  void initializeFromMemory( 
            __in WICInProcPointer pbBuffer,
            __in DWORD cbBufferSize)
  {
    IWICStream* stream = getWICStream();
    HRESULT hr = stream -> InitializeFromMemory( 
            pbBuffer,
            cbBufferSize);
    if (FAILED(hr)) {
      throw IException("Failed to InitializeFromMemory. HRESULT(0x%lx)", hr);
    }
  }
  
  void  initializeFromIStreamRegion( 
            __in IStream *pIStream,
            __in ULARGE_INTEGER ulOffset,
            __in ULARGE_INTEGER ulMaxSize)
  {
    IWICStream* stream = getWICStream();
    HRESULT hr = stream -> InitializeFromIStreamRegion( 
            pIStream,
            ulOffset,
            ulMaxSize);
    if (FAILED(hr)) {
      throw IException("InitializeFromIStreamRegion. HRESULT(0x%lx)", hr);
    }
  }
};

}

