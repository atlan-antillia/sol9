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
 *  WICImagingFactory.h
 *
 *****************************************************************************/


#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>
#include <sol/com/ComIUnknown.h>

//2016/12/05
#ifdef WIN10
#include <dxgi1_4.h>
#endif

#include <wincodec.h>

#pragma comment(lib, "windowscodecs.lib")


namespace SOL {

class WICImagingFactory: public ComIUnknown 
{
  
public:
  WICImagingFactory()
  :ComIUnknown()
  {
    IWICImagingFactory* factory = NULL;
    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&factory) );
    
    if (SUCCEEDED(hr)) {
      set(factory);
    } else {
      throw IException("Failed to CoCreateInstance. HRESUL(0x%lx)", hr);
    }
  }

  ~WICImagingFactory()
  {
  }

  operator IWICImagingFactory*() 
  {
    return getFactory();
  }

  IWICImagingFactory* getFactory()
  {
    IWICImagingFactory* factory = (IWICImagingFactory*)getIUnknown();
    if (factory) {
      return factory;
    } else {
      throw IException("IWICImagingFactory is NULL");
    }
  }
  
public:
  void  createDecoderFromFilename( 
            __in  LPCWSTR wzFilename,
            __in const GUID *pguidVendor,
            __in DWORD dwDesiredAccess,
            __in WICDecodeOptions metadataOptions,
            __out IWICBitmapDecoder **ppIDecoder)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateDecoderFromFilename( 
            wzFilename,
            pguidVendor,
            dwDesiredAccess,
            metadataOptions,
            ppIDecoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDecoderFromFilename. HRESULT(0x%lx)", hr);
    }
  }
  
  void  createDecoderFromStream( 
            __in IStream *pIStream,
            __in const GUID *pguidVendor,
            __in WICDecodeOptions metadataOptions,
            __out  IWICBitmapDecoder **ppIDecoder)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateDecoderFromStream( 
            pIStream,
            pguidVendor,
            metadataOptions,
            ppIDecoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDecoderFromStream. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createDecoderFromFileHandle( 
            __in ULONG_PTR hFile,
            __in const GUID *pguidVendor,
            __in WICDecodeOptions metadataOptions,
            __out  IWICBitmapDecoder **ppIDecoder)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateDecoderFromFileHandle( 
            hFile,
            pguidVendor,
            metadataOptions,
            ppIDecoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDecoderFromFileHandle. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createComponentInfo( 
            __in  REFCLSID clsidComponent,
            __out IWICComponentInfo **ppIInfo)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateComponentInfo( 
            clsidComponent,
            ppIInfo);
    if (FAILED(hr)) {
      throw IException("Failed to CreateComponentInfo. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createDecoder( 
            __in  REFGUID guidContainerFormat,
            __in  const GUID *pguidVendor,
            __out IWICBitmapDecoder **ppIDecoder)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateDecoder( 
            guidContainerFormat,
            pguidVendor,
            ppIDecoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDecoder. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createEncoder( 
            __in  REFGUID guidContainerFormat,
            __in const GUID *pguidVendor,
            __out IWICBitmapEncoder **ppIEncoder)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateEncoder( 
            guidContainerFormat,
            pguidVendor,
            ppIEncoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateEncoder. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createPalette( 
            __out IWICPalette **ppIPalette)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreatePalette( 
            ppIPalette);
    if (FAILED(hr)) {
      throw IException("Failed to CreatePalette. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createFormatConverter( 
            __out IWICFormatConverter **ppIFormatConverter)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateFormatConverter( 
            ppIFormatConverter);
    if (FAILED(hr)) {
      throw IException("Failed to CreateFormatConverter. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapScaler( 
            __out  IWICBitmapScaler **ppIBitmapScaler)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapScaler( 
            ppIBitmapScaler);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapScaler. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapClipper( 
            __out IWICBitmapClipper **ppIBitmapClipper)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapClipper( 
            ppIBitmapClipper);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapClipper. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapFlipRotator( 
            __out IWICBitmapFlipRotator **ppIBitmapFlipRotator)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapFlipRotator( 
            ppIBitmapFlipRotator);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFlipRotator. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createStream( 
            __out IWICStream **ppIWICStream)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateStream( 
            ppIWICStream);
    if (FAILED(hr)) {
      throw IException("Failed to CreateStream. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createColorContext( 
            __out IWICColorContext **ppIWICColorContext)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateColorContext( 
            ppIWICColorContext);
    if (FAILED(hr)) {
      throw IException("Failed to CreateColorContext. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createColorTransformer( 
            __out IWICColorTransform **ppIWICColorTransform)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateColorTransformer(
         ppIWICColorTransform);
    if (FAILED(hr)) {
      throw IException("Failed to CreateColorTransformer. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmap( 
            __in UINT uiWidth,
            __in UINT uiHeight,
            __in  REFWICPixelFormatGUID pixelFormat,
            __in WICBitmapCreateCacheOption option,
            __out IWICBitmap **ppIBitmap)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmap( 
            uiWidth,
            uiHeight,
            pixelFormat,
            option,
            ppIBitmap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmap. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapFromSource( 
            __in IWICBitmapSource *pIBitmapSource,
            __in WICBitmapCreateCacheOption option,
            __out IWICBitmap **ppIBitmap)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapFromSource( 
            pIBitmapSource,
            option,
            ppIBitmap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFromSource. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapFromSourceRect( 
            __in IWICBitmapSource *pIBitmapSource,
            __in UINT x,
            __in UINT y,
            __in UINT width,
            __in UINT height,
            __out IWICBitmap **ppIBitmap)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapFromSourceRect( 
            pIBitmapSource,
            x,
            y,
            width,
            height,
            ppIBitmap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFromSourceRect. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapFromMemory( 
            __in UINT uiWidth,
            __in UINT uiHeight,
            __in REFWICPixelFormatGUID pixelFormat,
            __in UINT cbStride,
            __in UINT cbBufferSize,
            __in  BYTE *pbBuffer,
            __out IWICBitmap **ppIBitmap)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapFromMemory( 
            uiWidth,
            uiHeight,
            pixelFormat,
            cbStride,
            cbBufferSize,
            pbBuffer,
            ppIBitmap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFromMemory. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapFromHBITMAP( 
            __in  HBITMAP hBitmap,
            __in HPALETTE hPalette,
            __in WICBitmapAlphaChannelOption options,
            __out  IWICBitmap **ppIBitmap)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapFromHBITMAP( 
            hBitmap,
            hPalette,
            options,
            ppIBitmap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFromHBITMAP. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createBitmapFromHICON( 
            __in  HICON hIcon,
            __out  IWICBitmap **ppIBitmap)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateBitmapFromHICON( 
            hIcon,
            ppIBitmap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFromHICON. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createComponentEnumerator( 
            __in DWORD componentTypes,
            __in DWORD options,
            __out  IEnumUnknown **ppIEnumUnknown)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateComponentEnumerator( 
            componentTypes,
            options,
            ppIEnumUnknown);
    if (FAILED(hr)) {
      throw IException("Failed to CreateComponentEnumerator. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createFastMetadataEncoderFromDecoder( 
            __in IWICBitmapDecoder *pIDecoder,
            __out IWICFastMetadataEncoder **ppIFastEncoder)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateFastMetadataEncoderFromDecoder( 
            pIDecoder,
            ppIFastEncoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateFastMetadataEncoderFromDecoder. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createFastMetadataEncoderFromFrameDecode( 
            __in IWICBitmapFrameDecode *pIFrameDecoder,
            __out  IWICFastMetadataEncoder **ppIFastEncoder)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateFastMetadataEncoderFromFrameDecode( 
            pIFrameDecoder,
            ppIFastEncoder);
    if (FAILED(hr)) {
      throw IException("Failed to CreateFastMetadataEncoderFromFrameDecode. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createQueryWriter( 
            __in  REFGUID guidMetadataFormat,
            __in const GUID *pguidVendor,
            __out  IWICMetadataQueryWriter **ppIQueryWriter)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateQueryWriter( 
            guidMetadataFormat,
            pguidVendor,
            ppIQueryWriter);
    if (FAILED(hr)) {
      throw IException("Failed to CreateQueryWriter. HRESULT(0x%lx)", hr);
    }
  }
        
  void  createQueryWriterFromReader( 
            __in IWICMetadataQueryReader *pIQueryReader,
            __in const GUID *pguidVendor,
            __out  IWICMetadataQueryWriter **ppIQueryWriter)
  {
    IWICImagingFactory* factory = getFactory();
    HRESULT hr = factory -> CreateQueryWriterFromReader( 
            pIQueryReader,
            pguidVendor,
            ppIQueryWriter);
    if (FAILED(hr)) {
      throw IException("Failed to CreateQueryWriterFromReader. HRESULT(0x%lx)", hr);
    }
  }
         
};

}
