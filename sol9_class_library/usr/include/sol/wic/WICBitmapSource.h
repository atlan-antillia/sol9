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
 *  WICBitmapSource.h
 *
 *****************************************************************************/

#pragma once

#include <sol/com/ComIUnknown.h>

namespace SOL {

class WICBitmapSource : public ComIUnknown
{
public:
  WICBitmapSource()
  :ComIUnknown()
  {
  }

public:
  WICBitmapSource(IWICBitmapSource* source)
  :ComIUnknown(source)
  {
  }
  
public:
  operator IWICBitmapSource*()
  {
    return getSource();
  }

public:
  IWICBitmapSource* getSource()
  {
    IWICBitmapSource* source = (IWICBitmapSource*)getIUnknown();
    if (source) {
      return source;
    } else {
      throw IException("IWCBitmapSource is NULL");
    }
  }
  
public:
  void getSize( 
            __out UINT *puiWidth,
            __out UINT *puiHeight)
  {
    IWICBitmapSource* source = getSource();
    HRESULT hr = source -> GetSize(
            puiWidth,
            puiHeight);
    if (FAILED(hr)) {
      throw IException("Failed to GetSize. HRESUL(0x%lx)", hr);
    }
  }
  
public:
  void getSize( 
            __out UINT& uiWidth,
            __out UINT& uiHeight)
  {
    IWICBitmapSource* source = getSource();
    HRESULT hr = source -> GetSize(
            &uiWidth,
            &uiHeight);
    if (FAILED(hr)) {
      throw IException("Failed to GetSize. HRESUL(0x%lx)", hr);
    }
  }
        
  void getPixelFormat( 
            __out WICPixelFormatGUID *pPixelFormat)
  {
    IWICBitmapSource* source = getSource();
    HRESULT hr = source -> GetPixelFormat( 
            pPixelFormat);
    if (FAILED(hr)) {
      throw IException("Failed to GetPixelFormat. HRESUL(0x%lx)", hr);
    }
  }
        
  void getResolution( 
            __out double *pDpiX,
            __out double *pDpiY) 
  {
    IWICBitmapSource* source = getSource();
    HRESULT hr = source -> GetResolution( 
            pDpiX,
            pDpiY);
    if (FAILED(hr)) {
      throw IException("Failed to GetResolution. HRESUL(0x%lx)", hr);
    }
  }
        
  void copyPalette( 
            __in IWICPalette *pIPalette)
  {
    IWICBitmapSource* source = getSource();
    HRESULT hr = source -> CopyPalette( 
            pIPalette);
    if (FAILED(hr)) {
      throw IException("Failed to GetResolution. HRESUL(0x%lx)", hr);
    }
  }
        
  void copyPixels( 
            __in const WICRect *prc,
            __in UINT cbStride,
            __in UINT cbBufferSize,
            __out BYTE *pbBuffer)
  {
    IWICBitmapSource* source = getSource();
    HRESULT hr = source -> CopyPixels( 
            prc,
            cbStride,
            cbBufferSize,
            pbBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to CopyPixels. HRESUL(0x%lx)", hr);
    }
  }
};
  
}
