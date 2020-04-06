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
 *  Direct2D1Bitmap1.h
 *
 *****************************************************************************/


#pragma once

//#include <sol/wic/WICFormatConverter.h>

#include <sol/directx/Direct2D1Bitmap.h>


namespace SOL {

class Direct2D1Bitmap1 :public Direct2D1Bitmap {

public:
  Direct2D1Bitmap1(
      ID2D1DeviceContext* deviceContext,
      IDXGISurface*       dxgiSurface,
      FLOAT dpiX,
      FLOAT dpiY)
    :Direct2D1Bitmap()
  {
    const D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
        D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        dpiX,
        dpiY
      );
    ID2D1Bitmap1* bitmap = nullptr; 

    HRESULT hr = deviceContext->CreateBitmapFromDxgiSurface(
				    dxgiSurface,
				    bitmapProperties,
				    &bitmap
				  );        
    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else {
      throw IException("Failed to CreateBitmapFromDxgiSurface. HRESULT(0x%lx)", hr);
    }
  }
    
  Direct2D1Bitmap1( ID2D1Bitmap1* bitmap)
  :Direct2D1Bitmap()
  {
    set(bitmap);
  }
  
  ~Direct2D1Bitmap1()
  {
  }
  
  operator ID2D1Bitmap1*()
  {
    return getID2D1Bitmap1();
  }
  
  ID2D1Bitmap1* getID2D1Bitmap1()
  {
    
    ID2D1Bitmap1* bitmap = (ID2D1Bitmap1*)getIUnknown();
    if (bitmap) {
      return bitmap;
    } else {
      throw IException("ID2D1Bitmap1 is NULL");
    }
  }
  
  void getColorContext(
        __out ID2D1ColorContext **colorContext 
        )
  {
    ID2D1Bitmap1* bitmap1 = getID2D1Bitmap1();
    bitmap1 -> GetColorContext(colorContext);
  }
  
  D2D1_BITMAP_OPTIONS getOptions()
  {
    ID2D1Bitmap1* bitmap1 = getID2D1Bitmap1();
    return bitmap1 -> GetOptions();
  }  
  void GetSurface(
        __out IDXGISurface **dxgiSurface 
        )
  {
    ID2D1Bitmap1* bitmap1 = getID2D1Bitmap1();
    bitmap1 -> GetSurface(dxgiSurface );
  }
  
  void map(
        D2D1_MAP_OPTIONS options,
        __out D2D1_MAPPED_RECT *mappedRect 
        )
  {
    ID2D1Bitmap1* bitmap1 = getID2D1Bitmap1();
    bitmap1 -> Map(
        options,
        mappedRect 
        );  
  }
  
  void unmap()
  {
    ID2D1Bitmap1* bitmap1 = getID2D1Bitmap1();
    bitmap1 -> Unmap();   
  }

};

}

