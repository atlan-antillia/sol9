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
 *  WICBitmapScaler.h
 *
 *****************************************************************************/

#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/wic/WICBitmapSource.h>

namespace SOL {
class WICBitmapScaler :public WICBitmapSource
{
  
public:
  WICBitmapScaler(IWICImagingFactory* factory)
  :WICBitmapSource()
  {
    IWICBitmapScaler* bitmapScaler = NULL;
    HRESULT hr = factory ->  CreateBitmapScaler( 
         &bitmapScaler);
    if (SUCCEEDED(hr)) {
       set(bitmapScaler);
    } else {
      throw IException("Failed to CreateBitmapScaler. HRESUL(0x%lx)", hr);  
    }
  }
  
  ~WICBitmapScaler()
  {
  }

  operator IWICBitmapScaler*()
  {
    return getBitmapScaler();
  }
  
  IWICBitmapScaler* getBitmapScaler()
  {
    IWICBitmapScaler* bitmapScaler = (IWICBitmapScaler*)getIUnknown();
    if (bitmapScaler) {
      return bitmapScaler;
    } else {
      throw IException("IWICBitmapScaler is NULL.");
    }
  }
  
  void initialize( 
            __in IWICBitmapSource *pISource,
            __in UINT uiWidth,
            __in UINT uiHeight,
            __in WICBitmapInterpolationMode mode)
  {
    IWICBitmapScaler* bitmapScaler = getBitmapScaler();
    HRESULT hr =bitmapScaler -> Initialize( 
            pISource,
            uiWidth,
            uiHeight,
            mode) ;    
    if (FAILED(hr)) {
      throw IException("Failed to Initialize. HRESUL(0x%lx)", hr);
    }
  }

};


}
