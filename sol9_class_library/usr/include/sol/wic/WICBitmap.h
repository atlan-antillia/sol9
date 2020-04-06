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
 *  WICBitmap.h
 *
 *****************************************************************************/

#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/wic/WICBitmapSource.h>

namespace SOL {

class WICBitmap: public WICBitmapSource
{
  
public:
  WICBitmap(IWICImagingFactory* factory, 
            __in UINT uiWidth,
            __in UINT uiHeight,
            __in  REFWICPixelFormatGUID pixelFormat,
            __in WICBitmapCreateCacheOption option)
  :WICBitmapSource()
  {
    IWICBitmap* bitmap = NULL;
    HRESULT hr = factory -> CreateBitmap( 
            uiWidth,
            uiHeight,
            pixelFormat,
            option,
            &bitmap);

    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else {
      throw IException("Failded to CreateBitmap. HRESULT(0x%lx)", hr);
    }
  }

  WICBitmap(IWICImagingFactory* factory,
            __in IWICBitmapSource *pIBitmapSource,
            __in WICBitmapCreateCacheOption option)
  :WICBitmapSource()
  {
    IWICBitmap* bitmap = NULL;
    HRESULT hr = factory -> CreateBitmapFromSource( 
            pIBitmapSource,
            option,
            &bitmap);
    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else {
      throw IException("Failed to CreateBitmapFromSource. HRESULT(0x%lx)", hr);
    }
  }
  
  WICBitmap(IWICImagingFactory* factory, 
            __in IWICBitmapSource *pIBitmapSource,
            __in UINT x,
            __in UINT y,
            __in UINT width,
            __in UINT height)
  :WICBitmapSource()
  {
    IWICBitmap* bitmap = NULL;
    HRESULT hr = factory -> CreateBitmapFromSourceRect( 
            pIBitmapSource,
            x,
            y,
            width,
            height,
            &bitmap);
    if (SUCCEEDED(hr)) {
      set(bitmap);
    }else {
      throw IException("CreateBitmapFromSourceRect. HRESULT(0x%lx)", hr);
    }  
  }
  
  WICBitmap(IWICImagingFactory* factory,
            __in UINT uiWidth,
            __in UINT uiHeight,
            __in REFWICPixelFormatGUID pixelFormat,
            __in UINT cbStride,
            __in UINT cbBufferSize,
            __in  BYTE *pbBuffer)
  :WICBitmapSource()
  {
    IWICBitmap* bitmap = NULL;
    HRESULT hr = factory -> CreateBitmapFromMemory( 
            uiWidth,
            uiHeight,
            pixelFormat,
            cbStride,
            cbBufferSize,
            pbBuffer,
            &bitmap);
    if (SUCCEEDED(hr)) {
      set(bitmap);
    }
    else {
      throw IException("CreateBitmapFromMemory. HRESULT(0x%lx)", hr);
    }  
  }
  
  WICBitmap(IWICImagingFactory* factory,
            __in  HBITMAP hBitmap,
            __in HPALETTE hPalette,
            __in WICBitmapAlphaChannelOption options)
  :WICBitmapSource()
  {
    IWICBitmap* bitmap = NULL;
    HRESULT hr = factory -> CreateBitmapFromHBITMAP( 
            hBitmap,
            hPalette,
            options,
            &bitmap);
    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else {
      throw IException("CreateBitmapFromHBITMAP. HRESULT(0x%lx)", hr);
    }          
  }
  
  
  WICBitmap(IWICImagingFactory* factory,
         __in  HICON hIcon)
  :WICBitmapSource()
  {
    IWICBitmap* bitmap = NULL;
    HRESULT hr = factory -> CreateBitmapFromHICON( 
            hIcon,
           &bitmap);
    if (SUCCEEDED(hr)) {
      set(bitmap);
    } else {
      throw IException("CreateBitmapFromHICON. HRESULT(0x%lx)", hr);
    }          
  }
  
  ~WICBitmap()
  {
  }
  operator IWICBitmap*()
  {
    return getBitmap();
  }

  IWICBitmap* getBitmap()
  {
    IWICBitmap* bitmap = (IWICBitmap*)getIUnknown();
    if (bitmap) {
      return bitmap;
    } else {
      throw IException("IWICBitmap is NULL");
    }
  }
  

  void  lock( 
            __in  const WICRect *prcLock,
            __in DWORD flags,
            __out IWICBitmapLock **ppILock)
  {
    IWICBitmap* bitmap = getBitmap();
    HRESULT hr = bitmap -> Lock( 
            prcLock,
            flags,
            ppILock);
    if (FAILED(hr)) {
      throw IException("Failed to Lock. HRESULT(0x%lx)", hr);
    }
  }
  
  void  setPalette( 
            __in  IWICPalette *pIPalette)
  {
    IWICBitmap* bitmap = getBitmap();
    HRESULT hr = bitmap -> SetPalette( 
            pIPalette);
    if (FAILED(hr)) {
      throw IException("Failed to SetPalette. HRESULT(0x%lx)", hr);
    }
  }
    
  void  setResolution( 
            __in double dpiX,
            __in double dpiY)
  {
    IWICBitmap* bitmap = getBitmap();
    HRESULT hr = bitmap ->  SetResolution( 
                dpiX,
                dpiY);
    if (FAILED(hr)) {
      throw IException("Failed to SetResolution.  HRESULT(0x%lx)", hr);
    }
  }

};

}
