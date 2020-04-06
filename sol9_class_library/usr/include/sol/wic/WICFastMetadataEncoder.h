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
 *  WICFastMetadataEncoder.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICImagingFactory.h>

namespace SOL {
  
class WICFastMetadataEncoder: public ComIUnknown {
{
  
public:
  WICFastMetadataEncoder(IWICImagingFactory* factory, 
            __in IWICBitmapDecoder *pIDecoder)
  :ComIUnknown()
  {
    IWICFastMetadataEncoder* fastEncoder = NULL;
    HRESUL hr = factory -> CreateFastMetadataEncoderFromDecoder( 
            pIDecoder,
            &fastEncoder);
    if (SUCCEEDED(hr)) {
      set(fastEncoder);
    } else {
      throw IException("Failed to CreateFastMetadataEncoderFromDecoder. HRESULT(0x%lx)", hr);
    }
  }

  WICFastMetadataEncoder(WICImagingFactory* factory,
            __in IWICBitmapFrameDecode *pIFrameDecoder)
  :ComIUnknown()
  {
    IWICFastMetadataEncoder* fastEncoder = NULL;
    HRESUL hr = factory -> CreateFastMetadataEncoderFromFrameDecode( 
            pIFrameDecoder,
            &fastEncoder);
    if (SUCCEEDED(hr)) {
      set(fastEncoder);
    } else {  
      throw IException("Failed to CreateFastMetadataEncoderFromFrameDecode. HRESULT(0x%lx)", hr);
    }
  }
    
  ~WICFastMetadataEncoder()
  {
  }
  
  operator  IWICFastMetadataEncoder*()
  {
    return getEncoder();
  }

  IWICFastMetadataEncoder* getEncoder()
  {
    IWICFastMetadataEncoder* encoder = (IWICFastMetadataEncoder*) getIUnknown();
    if (encoder) {
      return encoder;
    } else {
      throw IException("IWICFastMetadataEncoder is NULL.");
    }
  }
  
  void commit( void)
  {
    IWICFastMetadataEncoder* encoder = getEncoder();
    HRESUL hr = encoder -> Commit();
    if (FAILED(hr)) {
      throw IException("Failed to Commit");
    }
  }
  
  void getMetadataQueryWriter( 
            __out IWICMetadataQueryWriter **ppIMetadataQueryWriter)
  {
    IWICFastMetadataEncoder* encoder = getEncoder();
    HRESUL hr = encoder -> GetMetadataQueryWriter( 
            ppIMetadataQueryWriter);
    if (FAILED(hr)) {
      throw IException("Failed to GetMetadatQueryWriter. HRESULT(0x%lx)", hr);
    }
  }

};

}
