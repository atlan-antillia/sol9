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
 *  WICBitmapEncode.h
 *
 *****************************************************************************/

#pragma once

#include <sol/com/ComIUnknown.h>
#include <sol/wic/WICImagingFactory.h>

namespace SOL {
 
class WICBitmapFrameEncode : public ComIUnknown
{
public:
  WICBitmapFrameEncode(IWICBitmapEncoder* encoder, __inout IPropertyBag2 **ppIEncoderOptions=NULL)
  :ComIUnknown()
  {
    IWICBitmapFrameEncode* encode = NULL;
    HRESULT hr= encoder -> CreateNewFrame( 
            &encode,
            ppIEncoderOptions);
    if (SUCCEEDED(hr)) {
      set(encode);
    }
    if (FAILED(hr)) {
      throw IException("Failed to CreateNewFrame. HRESULT(0x%lx)", hr);
    }
  }
  
public:
  ~WICBitmapFrameEncode()
  {
  }
  
  operator IWICBitmapFrameEncode*()
  {
    return getEncode();
  }

  IWICBitmapFrameEncode* getEncode()
  {
    IWICBitmapFrameEncode* encode = (IWICBitmapFrameEncode*)getIUnknown();
    if (encode) {
      return encode;
    } else {
      throw IException("IWICBitmapFrameEncode is NULL.");
    }
  }
  

  void initialize( 
            __in IPropertyBag2 *pIEncoderOptions)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> Initialize( 
            pIEncoderOptions);
    if (FAILED(hr)) {
      throw IException("Failed to Initialize. HRESULT(0x%lx)", hr);
    }
  }
  
  void setSize( 
            __in UINT uiWidth,
            __in UINT uiHeight)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> SetSize( 
            uiWidth,
            uiHeight);
    if (FAILED(hr)) {
      throw IException("Failed to SetSize. HRESULT(0x%lx)", hr);
    }
  }
  
  void setResolution( 
            __in double dpiX,
            __in double dpiY)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> SetResolution( 
            dpiX,
            dpiY);
    if (FAILED(hr)) {
      throw IException("Failed to SetResolution. HRESULT(0x%lx)", hr);
    }
  }
        
  void setPixelFormat( 
            __inout WICPixelFormatGUID *pPixelFormat)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> SetPixelFormat( 
            pPixelFormat);
    if (FAILED(hr)) {
      throw IException("Failed to SetPixelFormat. HRESULT(0x%lx)", hr);
    }
  }
        
  void setColorContexts( 
            __in UINT cCount,
            __in IWICColorContext **ppIColorContext)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> SetColorContexts( 
            cCount,
            ppIColorContext);
    if (FAILED(hr)) {
      throw IException("Failed to SetColorContexts. HRESULT(0x%lx)", hr);
    }
  }
        
  void setPalette( 
            __in IWICPalette *pIPalette)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> SetPalette( 
            pIPalette);
    if (FAILED(hr)) {
      throw IException("Failed to SetPalette. HRESULT(0x%lx)", hr);
    }
  }
        
  void setThumbnail( 
            __in IWICBitmapSource *pIThumbnail)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> SetThumbnail( 
            pIThumbnail);
    if (FAILED(hr)) {
      throw IException("Failed to SetThumbnail. HRESULT(0x%lx)", hr);
    }
  }
        
  void writePixels( 
            __in UINT lineCount,
            __in UINT cbStride,
            __in UINT cbBufferSize,
            __in BYTE *pbPixels)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> WritePixels( 
            lineCount,
            cbStride,
            cbBufferSize,
            pbPixels);
    if (FAILED(hr)) {
      throw IException("Failed to WritePixels. HRESULT(0x%lx)", hr);
    }
  }
        
  void writeSource( 
            __in IWICBitmapSource *pIBitmapSource,
            __in WICRect *prc)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> WriteSource( 
            pIBitmapSource,
            prc);
    if (FAILED(hr)) {
      throw IException("Failed to WriteSource. HRESULT(0x%lx)", hr);
    }
  }
        
  void commit()
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> Commit();
    if (FAILED(hr)) {
      throw IException("Failed to Commit. HRESULT(0x%lx)", hr);
    }
  }
        
  void getMetadataQueryWriter( 
            __out IWICMetadataQueryWriter **ppIMetadataQueryWriter)
  {
    IWICBitmapFrameEncode* encode = getEncode();
    HRESULT hr = encode -> GetMetadataQueryWriter( 
          ppIMetadataQueryWriter);
    if (FAILED(hr)) {
      throw IException("Failed to GetMetadataQueryWriter. HRESULT(0x%lx)", hr);
    }
  }
        
};

}

