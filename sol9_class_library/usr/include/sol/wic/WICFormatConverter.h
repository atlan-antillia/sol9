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
 *  WICFormatConverter.h
 *
 *****************************************************************************/

#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/wic/WICBitmapSource.h>

namespace SOL {

class  WICFormatConverter: public WICBitmapSource 
{

public:
  WICFormatConverter(IWICImagingFactory* factory)
  :WICBitmapSource()
  {
    IWICFormatConverter* converter = NULL;
    HRESULT hr = factory -> CreateFormatConverter( 
            &converter);
    if (SUCCEEDED(hr)) {
      set(converter);  
    } else {
      throw IException("Failed to CreateFormatConverter. HRESULT(0x%lx)", hr);
    }
  }

  ~WICFormatConverter()
  {
  }

  operator IWICFormatConverter*()
  {
    return getConverter();
  }

  IWICFormatConverter* getConverter()
  {
    IWICFormatConverter* converter = (IWICFormatConverter*)getIUnknown();
    if (converter) {
      return converter;
    } else {
      throw IException("IWICFormatConverter is NULL.");
    }
  }
  
  void initialize( 
            __in  IWICBitmapSource *pISource,
            __in  REFWICPixelFormatGUID dstFormat,
            __in WICBitmapDitherType dither,
            __in  IWICPalette *pIPalette,
            __in double alphaThresholdPercent,
            __in WICBitmapPaletteType paletteTranslate)
  {
    IWICFormatConverter* converter = getConverter();
    HRESULT hr = converter -> Initialize( 
            pISource,
            dstFormat,
            dither,
            pIPalette,
            alphaThresholdPercent,
            paletteTranslate);
    if (FAILED(hr)) {
      throw IException("Failed to Initialize. HRESULT(0x%lx)", hr);
    }
  }
        
  void  canConvert( 
            __in  REFWICPixelFormatGUID srcPixelFormat,
            __in  REFWICPixelFormatGUID dstPixelFormat,
            __out  BOOL *pfCanConvert)
  {
    IWICFormatConverter* converter = getConverter();
    HRESULT hr = converter -> CanConvert( 
            srcPixelFormat,
            dstPixelFormat,
            pfCanConvert);
    if (FAILED(hr)) {
      throw IException("Failed to CanConvert. HRESULT(0x%lx)", hr);
    }
  }
};
    
}
