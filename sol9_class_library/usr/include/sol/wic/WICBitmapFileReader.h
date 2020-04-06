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
 *  WICBitmapFileReader.h
 *
 *****************************************************************************/
//2016/11/20 Added the following method to read pixel data from a wchar_t fileName

//  void read(int destWidth, int destHeight, 
//        D3D12_SUBRESOURCE_DATA& subresource)
// The following three method used in the above method are based on WICTextureLoader.cpp
//  
// convertWICToDXGIFormat
// getWICNearestFormat
// wicBitsPerPixel

//--------------------------------------------------------------------------------------
// File: WICTextureLoader.cpp
//
// Function for loading a WIC image and creating a Direct3D runtime texture for it
// (auto-generating mipmaps if possible)
//
// Note: Assumes application has already called CoInitializeEx
//
// Note these functions are useful for images created as simple 2D textures. For
// more complex resources, DDSTextureLoader is an excellent light-weight runtime loader.
// For a full-featured DDS file reader, writer, and texture processing pipeline see
// the 'Texconv' sample and the 'DirectXTex' library.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

// We could load multi-frame images (TIFF/GIF) into a texture array.
// For now, we just load the first frame (note: DirectXTex supports multi-frame images)


#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/wic/WICBitmapDecoder.h>
#include <sol/wic/WICBitmapFrameDecode.h>

#include <sol/wic/WICBitmapScaler.h>
#include <sol/wic/WICFormatConverter.h>

#include <sol/directx/Direct2D1Bitmap.h>

namespace SOL {

class WICBitmapFileReader : public WICBitmapDecoder {
private:
  IWICImagingFactory* factory;

public:
  WICBitmapFileReader(IWICImagingFactory* factory, const wchar_t* filename)
  :WICBitmapDecoder(factory, filename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand),
  factory(factory)
  {
    
  }

  //This will return an instance of Direct2D1Bitmap class, or NULL on failed. 
  Direct2D1Bitmap* read(ID2D1RenderTarget* renderTarget)
  {
    WICBitmapFrameDecode* frame   = NULL;

    WICFormatConverter* converter = NULL;  

    Direct2D1Bitmap* bitmap = NULL;
  
    try {
      frame = new WICBitmapFrameDecode(*this);

      converter = new WICFormatConverter(factory);  
      converter -> initialize(
                *frame,                          
                GUID_WICPixelFormat32bppPBGRA,  
                WICBitmapDitherTypeNone,        
                NULL,                         
                0.f,                             
                WICBitmapPaletteTypeCustom
                );
      bitmap = new Direct2D1Bitmap(renderTarget, 
                       *converter);
    } catch (Exception& ex) {
      ex.display();
    }
    
    delete frame;
    delete converter;
  	
    return bitmap;
  }
//2016/12/05 Added #ifdef WIN10 as shown below.
#ifdef WIN10
  //2016/11/20 Experimental code. 
  void read(int destWidth, int destHeight, 
        D3D12_SUBRESOURCE_DATA& subresource)
 
  {
  	WICBitmapScaler*      scaler  = NULL;
  	
    WICBitmapFrameDecode* frame   = NULL;

    WICFormatConverter* converter = NULL;  
  
    try {
      frame = new WICBitmapFrameDecode(*this);

      getDestinationSize(frame, (UINT&)destWidth, (UINT&)destHeight);
      scaler = new WICBitmapScaler(factory);
      
      scaler -> initialize(*frame, destWidth, destHeight, WICBitmapInterpolationModeCubic);
    	
      WICPixelFormatGUID pixelFormat;
      frame -> getPixelFormat( &pixelFormat );

      WICPixelFormatGUID convertGUID;
      memcpy( &convertGUID, &pixelFormat, sizeof(pixelFormat) );

      size_t bitsPerPixel = 0;
      
      DXGI_FORMAT format = convertWICToDXGIFormat(pixelFormat);
      if (format == DXGI_FORMAT_UNKNOWN) {
        getWICNearestFormat(pixelFormat, convertGUID, format, bitsPerPixel);
      }
      else {
        bitsPerPixel = wicBitsPerPixel(pixelFormat);
      }
            
      converter = new WICFormatConverter(factory);  
      converter -> initialize(
                *scaler,                          
                GUID_WICPixelFormat32bppPRGBA, 
                WICBitmapDitherTypeErrorDiffusion,        
                NULL, 
                0.0f, 
                WICBitmapPaletteTypeCustom
                );
      UINT twidth       = destWidth;
      UINT theight      = destHeight;

      size_t rowPitch  = ( twidth * bitsPerPixel + 7 ) / 8;
     
      size_t imageSize = rowPitch * theight;
      
      uint8_t* image = new uint8_t[imageSize];
      
      converter -> copyPixels( 0, rowPitch, imageSize , image );  
      
      subresource.pData      = image;
      subresource.RowPitch   = rowPitch;
      subresource.SlicePitch = imageSize;
      
    } catch (Exception& ex) {
      ex.display();
    }
    delete scaler;
    delete frame;
    delete converter;
  	
  }
#endif  
  //This will return an instance of Direct2D1Bitmap class, or NULL on failed. 
  Direct2D1Bitmap* read(ID2D1RenderTarget* renderTarget, UINT destWidth, UINT destHeight)
  {
  	WICBitmapScaler*      scaler  = NULL;
  	
    WICBitmapFrameDecode* frame   = NULL;

    WICFormatConverter* converter = NULL;  

    Direct2D1Bitmap* bitmap = NULL;
  
    try {
      frame = new WICBitmapFrameDecode(*this);

      getDestinationSize(frame, destWidth, destHeight);
      scaler = new WICBitmapScaler(factory);
      scaler -> initialize(*frame, destWidth, destHeight, WICBitmapInterpolationModeCubic);
    	
      converter = new WICFormatConverter(factory);  
      converter -> initialize(
                *scaler,                          
                GUID_WICPixelFormat32bppPBGRA,  
                WICBitmapDitherTypeNone,        
                NULL,                         
                0.f,                             
                WICBitmapPaletteTypeCustom
                );
      bitmap = new Direct2D1Bitmap(renderTarget, 
                       *converter);
    } catch (Exception& ex) {
      ex.display();
    }
    delete scaler;
    delete frame;
    delete converter;
  	
    return bitmap;
  }

  
  void getDestinationSize(WICBitmapSource* source, __inout UINT& destWidth, __inout UINT& destHeight)
  {
     UINT width  = 0;
     UINT height = 0;
     source -> getSize(width, height);
 
    if (destWidth > 0 || destHeight > 0) {
      if (destWidth == 0) {
      	float scaler = (float)destHeight / (float)height;
      	destWidth = (UINT) (scaler * (float)width);
      } else if (destHeight == 0) {
        float scaler = (float)destWidth / (float)width;
    	destHeight = (UINT)(scaler * (float)height);
     }
    }
  }

#ifdef WIN10  
  //-------------------------------------------------------------------------------------
  // WIC Pixel Format Translation Data
  //-------------------------------------------------------------------------------------
  DXGI_FORMAT convertWICToDXGIFormat(const GUID& guid)
  {
    struct WICTranslate {
      GUID                wic;
      DXGI_FORMAT         format;
    };

    const WICTranslate wicFormats[] =
    {
      { GUID_WICPixelFormat128bppRGBAFloat,       DXGI_FORMAT_R32G32B32A32_FLOAT },

      { GUID_WICPixelFormat64bppRGBAHalf,         DXGI_FORMAT_R16G16B16A16_FLOAT },
      { GUID_WICPixelFormat64bppRGBA,             DXGI_FORMAT_R16G16B16A16_UNORM },

      { GUID_WICPixelFormat32bppRGBA,             DXGI_FORMAT_R8G8B8A8_UNORM },
      { GUID_WICPixelFormat32bppBGRA,             DXGI_FORMAT_B8G8R8A8_UNORM },
      { GUID_WICPixelFormat32bppBGR,              DXGI_FORMAT_B8G8R8X8_UNORM },

      { GUID_WICPixelFormat32bppRGBA1010102XR,    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM },
      { GUID_WICPixelFormat32bppRGBA1010102,      DXGI_FORMAT_R10G10B10A2_UNORM },

      { GUID_WICPixelFormat16bppBGRA5551,         DXGI_FORMAT_B5G5R5A1_UNORM },
      { GUID_WICPixelFormat16bppBGR565,           DXGI_FORMAT_B5G6R5_UNORM },

      { GUID_WICPixelFormat32bppGrayFloat,        DXGI_FORMAT_R32_FLOAT },
      { GUID_WICPixelFormat16bppGrayHalf,         DXGI_FORMAT_R16_FLOAT },
      { GUID_WICPixelFormat16bppGray,             DXGI_FORMAT_R16_UNORM },
      { GUID_WICPixelFormat8bppGray,              DXGI_FORMAT_R8_UNORM },

      { GUID_WICPixelFormat8bppAlpha,             DXGI_FORMAT_A8_UNORM },

      { GUID_WICPixelFormat96bppRGBFloat,         DXGI_FORMAT_R32G32B32_FLOAT },
    };

    for (size_t i = 0; i < _countof(wicFormats); ++i) {
      if (memcmp(&wicFormats[i].wic, &guid, sizeof(GUID)) == 0)
        return wicFormats[i].format;
    }

    return DXGI_FORMAT_UNKNOWN;
  }



  void getWICNearestFormat(
    WICPixelFormatGUID& pixelFormat,
    WICPixelFormatGUID& convertGUID,
    DXGI_FORMAT& format,
    size_t& bpp)
  {
    //-------------------------------------------------------------------------------------
    // WIC Pixel Format nearest conversion table
    //-------------------------------------------------------------------------------------

    struct WICConvert {
      GUID        source;
      GUID        target;
    };

    const WICConvert wicConvert[] =
    {
      // Note target GUID in this conversion table must be one of those directly supported formats (above).

      { GUID_WICPixelFormatBlackWhite,            GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM

      { GUID_WICPixelFormat1bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
      { GUID_WICPixelFormat2bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
      { GUID_WICPixelFormat4bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
      { GUID_WICPixelFormat8bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 

      { GUID_WICPixelFormat2bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 
      { GUID_WICPixelFormat4bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 

      { GUID_WICPixelFormat16bppGrayFixedPoint,   GUID_WICPixelFormat16bppGrayHalf }, // DXGI_FORMAT_R16_FLOAT 
      { GUID_WICPixelFormat32bppGrayFixedPoint,   GUID_WICPixelFormat32bppGrayFloat }, // DXGI_FORMAT_R32_FLOAT 

      { GUID_WICPixelFormat16bppBGR555,           GUID_WICPixelFormat16bppBGRA5551 }, // DXGI_FORMAT_B5G5R5A1_UNORM

      { GUID_WICPixelFormat32bppBGR101010,        GUID_WICPixelFormat32bppRGBA1010102 }, // DXGI_FORMAT_R10G10B10A2_UNORM

      { GUID_WICPixelFormat24bppBGR,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
      { GUID_WICPixelFormat24bppRGB,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
      { GUID_WICPixelFormat32bppPBGRA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
      { GUID_WICPixelFormat32bppPRGBA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 

      { GUID_WICPixelFormat48bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
      { GUID_WICPixelFormat48bppBGR,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
      { GUID_WICPixelFormat64bppBGRA,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
      { GUID_WICPixelFormat64bppPRGBA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
      { GUID_WICPixelFormat64bppPBGRA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM

      { GUID_WICPixelFormat48bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
      { GUID_WICPixelFormat48bppBGRFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
      { GUID_WICPixelFormat64bppRGBAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
      { GUID_WICPixelFormat64bppBGRAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
      { GUID_WICPixelFormat64bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
      { GUID_WICPixelFormat64bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
      { GUID_WICPixelFormat48bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 

      { GUID_WICPixelFormat128bppPRGBAFloat,      GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
      { GUID_WICPixelFormat128bppRGBFloat,        GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
      { GUID_WICPixelFormat128bppRGBAFixedPoint,  GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
      { GUID_WICPixelFormat128bppRGBFixedPoint,   GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
      { GUID_WICPixelFormat32bppRGBE,             GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 

      { GUID_WICPixelFormat32bppCMYK,             GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
      { GUID_WICPixelFormat64bppCMYK,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
      { GUID_WICPixelFormat40bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
      { GUID_WICPixelFormat80bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM

      { GUID_WICPixelFormat32bppRGB,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
      { GUID_WICPixelFormat64bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
      { GUID_WICPixelFormat64bppPRGBAHalf,        GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT

      { GUID_WICPixelFormat96bppRGBFixedPoint,   GUID_WICPixelFormat96bppRGBFloat }, // DXGI_FORMAT_R32G32B32_FLOAT

                                                                                     // We don't support n-channel formats
    };

    for (size_t i = 0; i < _countof(wicConvert); ++i)
    {
      if (memcmp(&wicConvert[i].source, &pixelFormat, sizeof(WICPixelFormatGUID)) == 0)
      {
        memcpy(&convertGUID, &wicConvert[i].target, sizeof(WICPixelFormatGUID));

        format = convertWICToDXGIFormat(wicConvert[i].target);

        bpp = wicBitsPerPixel(convertGUID);
        break;
      }
    }

    if (format == DXGI_FORMAT_UNKNOWN) {
      throw IException("Unsupported format.");
    }
  }

  //---------------------------------------------------------------------------------
  size_t wicBitsPerPixel(REFGUID targetGuid)
  {
    UINT bpp = 0;
   // size_t bpp = 0;

    IWICComponentInfo*   cinfo = NULL;
    IWICPixelFormatInfo* pfinfo = NULL;
    try {
      if (factory->CreateComponentInfo(targetGuid, &cinfo))
        throw 0;

      WICComponentType type;
      if (cinfo->GetComponentType(&type))
        throw 0;

      if (type != WICPixelFormat)
        throw 0;

      if (FAILED(cinfo->QueryInterface(IID_PPV_ARGS(&pfinfo))))
        throw 0;

      if (FAILED(pfinfo->GetBitsPerPixel(&bpp)))
        throw 0;

    }
    catch (...) {
      //Ignore
    }

    if (cinfo)
      cinfo->Release();
    if (pfinfo)
      pfinfo->Release();

  	return (size_t)bpp;
  }
#endif
};
  
}

  
