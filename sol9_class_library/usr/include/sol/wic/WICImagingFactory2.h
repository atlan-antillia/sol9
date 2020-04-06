/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WICImagingFactory2.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICImagingFactory.h>

#pragma comment(lib, "windowscodecs.lib")


namespace SOL {

class WICImagingFactory2: public WICImagingFactory 
{
  
public:
  WICImagingFactory2()
  :WICImagingFactory()
  {
    IWICImagingFactory2* factory = NULL;
    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory2,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&factory) );
 
    if (SUCCEEDED(hr)) {
      set(factory);
    } else {
      throw IException("Failed to CoCreateInstance. HRESUL(0x%lx)", hr);
    }
  }

  ~WICImagingFactory2()
  {
  }

  operator IWICImagingFactory2*() 
  {
    return getFactory();
  }

  IWICImagingFactory2* getFactory()
  {
    IWICImagingFactory2* factory = (IWICImagingFactory2*)getIUnknown();
    if (factory) {
      return factory;
    } else {
      throw IException("IWICImagingFactory2 is NULL");
    }
  }
  
public:
  void createImageEncoder( 
            /* [in] */ ID2D1Device *pD2DDevice,
            /* [out] */ IWICImageEncoder **ppWICImageEncoder)
  {
    IWICImagingFactory2* factory = getFactory();
    HRESULT hr = factory -> CreateImageEncoder( 
            pD2DDevice,
            ppWICImageEncoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateImageEncoder. HRESULT(0x%lx)", hr);
    }
        
  }
};

}
