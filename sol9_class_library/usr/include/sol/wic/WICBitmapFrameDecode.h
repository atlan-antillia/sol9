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
 *  WICBitmapFrameDecode.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/wic/WICBitmapSource.h>

namespace SOL {

class WICBitmapFrameDecode: public WICBitmapSource {
  
public:
  WICBitmapFrameDecode(IWICBitmapDecoder* decoder)
  :WICBitmapSource()
  {
    IWICBitmapFrameDecode* source =NULL; 
    HRESULT hr = decoder -> GetFrame(0, &source);
    if (SUCCEEDED(hr)) {
      set(source);
    } else {
      throw IException("Failed to GetFrame. HRESULT(0x%lx)", hr); 
    }
  }

  ~WICBitmapFrameDecode()
  {
  }

  operator IWICBitmapFrameDecode*()
  {
    return getBitmapFrameDecode();
  }

  IWICBitmapFrameDecode* getBitmapFrameDecode()
  {
    IWICBitmapFrameDecode* decode = (IWICBitmapFrameDecode*)getIUnknown();
    if (decode) {
      return decode;
    } else {
      throw IException("IWICBitmapFrameDecode is NULL.");
    }
  }
  
  void getMetadataQueryReader( 
            __out IWICMetadataQueryReader **ppIMetadataQueryReader)
  {
    IWICBitmapFrameDecode* decode = getBitmapFrameDecode();
    HRESULT hr = decode -> GetMetadataQueryReader( 
            ppIMetadataQueryReader);
    if (FAILED(hr)) {
      throw IException("Failed to GetMetadataQueryReader. HRESULT(0x%lx)", hr);
    }
  }
  
  void getColorContexts( 
            UINT cCount,
            __inout IWICColorContext **ppIColorContexts,
            __out UINT *pcActualCount)
  {
    IWICBitmapFrameDecode* decode = getBitmapFrameDecode();
    HRESULT hr = decode -> GetColorContexts( 
            cCount,
            ppIColorContexts,
            pcActualCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetColorContexts. HRESULT(0x%lx)", hr);
    }
  }
        
  void getThumbnail( 
            __out IWICBitmapSource **ppIThumbnail)
  {
    IWICBitmapFrameDecode* decode = getBitmapFrameDecode();
    HRESULT hr = decode -> GetThumbnail( 
            ppIThumbnail);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
};

}
