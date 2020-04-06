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
 *  Direct2D1Bitmap.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICFormatConverter.h>

#include <sol/directx/Direct2D1RenderTarget.h>
#include <sol/directx/Direct2D1Resource.h>


namespace SOL {

class Direct2D1Bitmap :public Direct2D1Resource 
{
protected:
  Direct2D1Bitmap()
  :Direct2D1Resource()
  {
  }
  
  
  
public:
  Direct2D1Bitmap(ID2D1RenderTarget* renderTarget,
         __in IWICBitmapSource *wicBitmapSource,
        __in CONST D2D1_BITMAP_PROPERTIES *bitmapProperties)
  :Direct2D1Resource()
  {
    ID2D1Bitmap* bitmap = NULL;
    HRESULT hr = renderTarget -> CreateBitmapFromWicBitmap(
        wicBitmapSource,
        bitmapProperties,
        &bitmap);
    
    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else  {
      throw IException("Failed to CreateBitmapFromWicBitmap. HRESULT(0x%lx)", hr); 
    }
  }

public:
  Direct2D1Bitmap(ID2D1RenderTarget* renderTarget,
         __in IWICBitmapSource *wicBitmapSource)
  :Direct2D1Resource()
  {
    ID2D1Bitmap* bitmap = NULL;
    HRESULT hr = renderTarget -> CreateBitmapFromWicBitmap(
        wicBitmapSource,
        &bitmap);
    
    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else  {
      throw IException("Failed to CreateBitmapFromWicBitmap. HRESULT(0x%lx)", hr); 
    }
  }

public:
  Direct2D1Bitmap(ID2D1RenderTarget* renderTarget,
         __in REFIID riid,
        __inout void *data,
        __in_opt CONST D2D1_BITMAP_PROPERTIES *bitmapProperties)
  :Direct2D1Resource()
  {
    ID2D1Bitmap* bitmap = NULL;
    HRESULT hr = renderTarget -> CreateSharedBitmap(
        riid,
        data,
        bitmapProperties,
        &bitmap 
    );
    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else  {
      throw IException("Failed to CreateSharedBitmap. HRESULT(0x%lx)", hr); 
    }
  }
  
  ~Direct2D1Bitmap()
  {
  }

  operator ID2D1Bitmap*()
  {
    return getBitmap();
  }

  ID2D1Bitmap* getBitmap()
  {
    ID2D1Bitmap* bitmap = (ID2D1Bitmap*)getIUnknown();
    if (bitmap) {
      return bitmap;
    } else {
      throw IException("ID2D1Bitmap is NULL.");
    }
  }
  

  D2D1_SIZE_F getSize()
  {
    ID2D1Bitmap* bitmap = getBitmap();
    return bitmap -> GetSize();
  }
  
    
  D2D1_SIZE_U getPixelSize()
  {
    ID2D1Bitmap* bitmap = getBitmap();
    return bitmap -> GetPixelSize();
  }
  
  D2D1_PIXEL_FORMAT getPixelFormat()
  {
    ID2D1Bitmap* bitmap = getBitmap();
    return bitmap -> GetPixelFormat();
  }
    
    
  void getDpi(
        __out FLOAT *dpiX,
        __out FLOAT *dpiY )
  {
    ID2D1Bitmap* bitmap = getBitmap();
    bitmap -> GetDpi(
        dpiX,
        dpiY );
  }
  
    
  void copyFromBitmap(
        __in CONST D2D1_POINT_2U *destPoint,
        __in ID2D1Bitmap *inbitmap,
        __in CONST D2D1_RECT_U *srcRect)
  {
    ID2D1Bitmap* bitmap = getBitmap();
    HRESULT hr = bitmap -> CopyFromBitmap(
        destPoint,
        inbitmap,
        srcRect);
    if (FAILED(hr)) {
      throw IException("Failed to CopyFromBitmap. HRESULT(0x%lx)", hr);
    }
  }
    
  void copyFromRenderTarget(
        __in CONST D2D1_POINT_2U *destPoint,
        __in ID2D1RenderTarget *renderTarget,
        __in CONST D2D1_RECT_U *srcRect) 
  {
    ID2D1Bitmap* bitmap = getBitmap();
    HRESULT hr =  bitmap -> CopyFromRenderTarget(
        destPoint,
        renderTarget,
        srcRect);
    if (FAILED(hr)) {
      throw IException("Failed to CopyFromRenderTarget. HRESULT(0x%lx)", hr);
    }
  }
    
  void copyFromMemory(
        __in CONST D2D1_RECT_U *dstRect,
        __in CONST void *srcData,
        UINT32 pitch )
  {
    ID2D1Bitmap* bitmap = getBitmap();
    HRESULT hr = bitmap -> CopyFromMemory(
        dstRect,
        srcData,
        pitch );
    if (FAILED(hr)) {
      throw IException("Failed to CopyFromMemory. HRESULT(0x%lx)", hr);
    }
  }
};

}

