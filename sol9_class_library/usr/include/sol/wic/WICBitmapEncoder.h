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
 *  WICBitmapEncoder.h
 *
 *****************************************************************************/

#pragma once

#include <sol/com/ComIUnknown.h>
#include <sol/wic/WICImagingFactory.h>

namespace SOL {

class WICBitmapEncoder: public ComIUnknown
{
public:
  WICBitmapEncoder()
  :ComIUnknown()
  {
  }
	
public:
  WICBitmapEncoder(IWICImagingFactory* factory,
            __in  REFGUID guidContainerFormat,
            __in const GUID *pguidVendor)
  :ComIUnknown()
  {
    IWICBitmapEncoder* encoder = NULL;
   
    HRESULT hr =  factory -> CreateEncoder( 
            guidContainerFormat,
            pguidVendor,
            &encoder);
	if (SUCCEEDED(hr)) {
      set(encoder);
    } else {
      throw IException("Failed to CreateEncoder. HRESULT(0x%lx)", hr);  
    }
  }

  ~WICBitmapEncoder()
  {
  }

  operator IWICBitmapEncoder*()
  {
    return getEncoder();
  }
  
  IWICBitmapEncoder* getEncoder()
  {
    IWICBitmapEncoder* encoder = (IWICBitmapEncoder*)getIUnknown();
    if (encoder) {
      return encoder;
    } else {
      throw IException("IWICBitmapEncoder is NULL");
    }
  }
  
public:
  void initialize( 
            __in  IStream *pIStream,
            __in WICBitmapEncoderCacheOption cacheOption)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> Initialize( 
            pIStream,
            cacheOption);
    if (FAILED(hr)) {
      throw IException("Failed to Initialize. HRESULT(0x%lx)", hr);
    }
  }
  
  void getContainerFormat( 
            __out  GUID *pguidContainerFormat)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> GetContainerFormat( 
            pguidContainerFormat);
    if (FAILED(hr)) {
      throw IException("Failed to GetContainerFormat. HRESULT(0x%lx)", hr);
    }
  }
        
  void getEncoderInfo( 
            __out IWICBitmapEncoderInfo **ppIEncoderInfo)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> GetEncoderInfo( 
            ppIEncoderInfo);
    if (FAILED(hr)) {
      throw IException("Failed to GetEncoderInfo. HRESULT(0x%lx)", hr);
    }
  }
        
  void setColorContexts( 
            __in UINT cCount,
            __in IWICColorContext **ppIColorContext)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> SetColorContexts( 
            cCount,
            ppIColorContext);
    if (FAILED(hr)) {
      throw IException("Failed to SetColorContexts. HRESULT(0x%lx)", hr);
    }
  }
        
  void setPalette( 
            __in  IWICPalette *pIPalette)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder ->  SetPalette( 
            pIPalette);
    if (FAILED(hr)) {
      throw IException("Failed to SetPalette. HRESULT(0x%lx)", hr);
    }
  }
        
  void setThumbnail( 
            __in  IWICBitmapSource *pIThumbnail)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> SetThumbnail(pIThumbnail
            );
    if (FAILED(hr)) {
      throw IException("Failed to SetThumbnail. HRESULT(0x%lx)", hr);
    }
  }
        
  void setPreview( 
            __in  IWICBitmapSource *pIPreview)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> SetPreview( 
            pIPreview);
    if (FAILED(hr)) {
      throw IException("Failed to SetPreview. HRESULT(0x%lx)", hr);
    }
  }
        
  void createNewFrame( 
            __out IWICBitmapFrameEncode **ppIFrameEncode,
            __inout IPropertyBag2 **ppIEncoderOptions)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    
    HRESULT hr= encoder -> CreateNewFrame( 
            ppIFrameEncode,
            ppIEncoderOptions);
    if (FAILED(hr)) {
      throw IException("Failed to CreateNewFrame. HRESULT(0x%lx)", hr);
    }
  }
        
  void commit()
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> Commit();
    if (FAILED(hr)) {
      throw IException("Failed to Commit. HRESULT(0x%lx)", hr);
    }
  }
        
  void getMetadataQueryWriter( 
            __out IWICMetadataQueryWriter **ppIMetadataQueryWriter)
  {
    IWICBitmapEncoder* encoder = getEncoder();
    HRESULT hr= encoder -> GetMetadataQueryWriter( 
            ppIMetadataQueryWriter);
    if (FAILED(hr)) {
      throw IException("Failed to GetMetadataQueryWriter. HRESULT(0x%lx)", hr);
    }
  }     
};

}


