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
 *  WICBitmapDecoder.h
 *
 *****************************************************************************/

#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/wic/WICBitmapFrameDecode.h>

namespace SOL {

class WICBitmapDecoder: public ComIUnknown
{

public:
  WICBitmapDecoder(IWICImagingFactory* factory,
            __in LPCWSTR wzFilename,
            __in const GUID *pguidVendor,
            __in DWORD dwDesiredAccess,
            __in WICDecodeOptions metadataOptions)
  :ComIUnknown()
  {
    IWICBitmapDecoder* decoder = NULL;
    HRESULT hr = factory -> CreateDecoderFromFilename( 
            wzFilename,
            pguidVendor,
            dwDesiredAccess,
            metadataOptions,
            &decoder);
    if (SUCCEEDED(hr)) {
      set(decoder);  
    } else {
      throw IException("Failed to CreateDecoderFromFilename. HRESULT(0x%lx)", hr);  
    }
  } 
    
  WICBitmapDecoder(IWICImagingFactory* factory,
            __in IStream *pIStream,
            __in const GUID *pguidVendor,
            __in WICDecodeOptions metadataOptions)
  :ComIUnknown()
  {
    IWICBitmapDecoder* decoder = NULL;
    HRESULT hr = factory -> CreateDecoderFromStream( 
            pIStream,
            pguidVendor,
            metadataOptions,
            &decoder);
    if (SUCCEEDED(hr)) {
      set(decoder);
    } else {    
      throw IException("Failed to CreateDecoderFromStream. HRESULT(0x%lx)", hr);  
    }
  }
    
  WICBitmapDecoder(IWICImagingFactory* factory,
            __in ULONG_PTR hFile,
            __in const GUID *pguidVendor,
            __in WICDecodeOptions metadataOptions)
  :ComIUnknown()
  {
    IWICBitmapDecoder* decoder = NULL;
    HRESULT hr = factory -> CreateDecoderFromFileHandle( 
            hFile,
            pguidVendor,
            metadataOptions,
            &decoder);
    if (SUCCEEDED(hr)) {
      set(decoder);
    } else {
      throw IException("Failed to CreateDecoderFromFileHanlde. HRESULT(0x%lx)", hr);  
    }
  }
    
  WICBitmapDecoder(IWICImagingFactory* factory,
            __in  REFGUID guidContainerFormat,
            __in const GUID *pguidVendor)
  :ComIUnknown()
  {
    IWICBitmapDecoder* decoder = NULL;
    HRESULT hr = factory -> CreateDecoder( 
            guidContainerFormat,
            pguidVendor,
            &decoder);
    if (SUCCEEDED(hr)) {
      set(decoder);
    } else {
      throw IException("Failed to CreateDecoder. HRESULT(0x%lx)", hr);  
    }
  }
    
  ~WICBitmapDecoder()
  {
  }

  operator IWICBitmapDecoder*()
  {
    return getDecoder();
  }

  IWICBitmapDecoder* getDecoder()
  {
    IWICBitmapDecoder* decoder = (IWICBitmapDecoder*)getIUnknown();
    if (decoder) {
      return decoder;
    } else {
      throw IException("IWICBitmapDecoder is NULL.");
    }
  }
  
  void queryCapability( 
            __in  IStream *pIStream,
            __out  DWORD *pdwCapability)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> QueryCapability( 
            pIStream,
            pdwCapability);
    if (FAILED(hr)) {
        throw IException("Failed to QueryCapability. HRESULT(0x%lx)", hr);
    }
  }

  
  void initialize( 
            __in  IStream *pIStream,
            __in WICDecodeOptions cacheOptions)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> Initialize( 
                pIStream,
                cacheOptions);
    if (FAILED(hr)) {
      throw IException("Failed to Initialize. HRESULT(0x%lx)", hr)
    }
  }
  
  void  getContainerFormat( 
            __out GUID *pguidContainerFormat)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetContainerFormat( 
         pguidContainerFormat);
    if (FAILED(hr)) {
      throw IException("Failed to GetContainerFormat. HRESULT(0x%lx)", hr);
    }
  }

  void  getDecoderInfo( 
            __out IWICBitmapDecoderInfo **ppIDecoderInfo)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetDecoderInfo(ppIDecoderInfo);
    if (FAILED(hr)) {
      throw IException("Failed to GetDecoderInfo. HRESULT(0x%lx)", hr);
    }
  }
  
  void copyPalette( 
            __in IWICPalette *pIPalette)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> CopyPalette(pIPalette);
    if (FAILED(hr)) {
      throw IException("Failed to CopyPalette. HRESULT(0x%lx)", hr);
    }
  }

  void getMetadataQueryReader( 
            __out IWICMetadataQueryReader **ppIMetadataQueryReader)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetMetadataQueryReader( 
               ppIMetadataQueryReader);
    if (FAILED(hr)) {
      throw IException("Failed to GetMetadataQueryReader. HRESULT(0x%lx)", hr);
    }
  }
        
  void  getPreview( 
            __out IWICBitmapSource **ppIBitmapSource)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetPreview( 
        ppIBitmapSource);
    if (FAILED(hr)) {
      throw IException("Failed to GetPreview. HRESULT(0x%lx)", hr);
    }
  }
  
  void getColorContexts( 
            __in UINT cCount,
            __inout IWICColorContext **ppIColorContexts,
            __out  UINT *pcActualCount)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetColorContexts( 
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
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetThumbnail( 
                 ppIThumbnail);
    if (FAILED(hr)) {
        throw IException("Failed to GetThumbnail. HRESULT(0x%lx)", hr);
    }
  }
  
         
  void getFrameCount( 
            __out  UINT *pCount)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetFrameCount( 
                pCount);
    if (FAILED(hr)) {
      throw IException("Failed to GetFrameCount. HRESULT(0x%lx)", hr);
    }
  }
  
  void getFrame( 
            __in UINT index,
            __out IWICBitmapFrameDecode **ppIBitmapFrame)
  {
    IWICBitmapDecoder* decoder = getDecoder();
    HRESULT hr = decoder -> GetFrame( 
            index,
            ppIBitmapFrame);
    if (FAILED(hr)) {
      throw IException("Failed to GetFrame. HRESULT(0x%lx)", hr);
    }
  }
  
};

}

