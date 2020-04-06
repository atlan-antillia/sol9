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


//readImageData and related methods is based on the following WICTextureLoader.cpp
// of the source files in https://github.com/Microsoft/DirectXTK12

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

//---------------------------------------------------------------------------------------
// 2015/10/10 Added a new read method to resize WICBitmap by WICBitmapScaler.
// 2016/01/15 Modified the first argument ID2D1HwndRenderTarget* of read method
//      to ID2D1RenderTarget*.

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
      frame = new WICBitmapFrameDecode(*this);// = NULL;

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
    
    
  //-------------------------------------------------------------------------
  // get a dxgi compatible wic format from another wic format
  WICPixelFormatGUID GetConvertToWICFormat(WICPixelFormatGUID& wicFormatGUID)
  {
    if (wicFormatGUID == GUID_WICPixelFormatBlackWhite) return GUID_WICPixelFormat8bppGray;
    else if (wicFormatGUID == GUID_WICPixelFormat1bppIndexed) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat2bppIndexed) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat4bppIndexed) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat8bppIndexed) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat2bppGray) return GUID_WICPixelFormat8bppGray;
    else if (wicFormatGUID == GUID_WICPixelFormat4bppGray) return GUID_WICPixelFormat8bppGray;
    else if (wicFormatGUID == GUID_WICPixelFormat16bppGrayFixedPoint) return GUID_WICPixelFormat16bppGrayHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppGrayFixedPoint) return GUID_WICPixelFormat32bppGrayFloat;
    else if (wicFormatGUID == GUID_WICPixelFormat16bppBGR555) return GUID_WICPixelFormat16bppBGRA5551;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppBGR101010) return GUID_WICPixelFormat32bppRGBA1010102;
    else if (wicFormatGUID == GUID_WICPixelFormat24bppBGR) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat24bppRGB) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppPBGRA) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppPRGBA) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat48bppRGB) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat48bppBGR) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppBGRA) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppPRGBA) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppPBGRA) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat48bppRGBFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat48bppBGRFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBAFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppBGRAFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBHalf) return GUID_WICPixelFormat64bppRGBAHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat48bppRGBHalf) return GUID_WICPixelFormat64bppRGBAHalf;
    else if (wicFormatGUID == GUID_WICPixelFormat128bppPRGBAFloat) return GUID_WICPixelFormat128bppRGBAFloat;
    else if (wicFormatGUID == GUID_WICPixelFormat128bppRGBFloat) return GUID_WICPixelFormat128bppRGBAFloat;
    else if (wicFormatGUID == GUID_WICPixelFormat128bppRGBAFixedPoint) return GUID_WICPixelFormat128bppRGBAFloat;
    else if (wicFormatGUID == GUID_WICPixelFormat128bppRGBFixedPoint) return GUID_WICPixelFormat128bppRGBAFloat;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBE) return GUID_WICPixelFormat128bppRGBAFloat;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppCMYK) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppCMYK) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat40bppCMYKAlpha) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat80bppCMYKAlpha) return GUID_WICPixelFormat64bppRGBA;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
    else if (wicFormatGUID == GUID_WICPixelFormat32bppRGB) return GUID_WICPixelFormat32bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppRGB) return GUID_WICPixelFormat64bppRGBA;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppPRGBAHalf) return GUID_WICPixelFormat64bppRGBAHalf;
#endif

    else return GUID_WICPixelFormatDontCare;
  }


  // get the dxgi format equivilent of a wic format
  DXGI_FORMAT GetDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID)
  {
    if (wicFormatGUID == GUID_WICPixelFormat128bppRGBAFloat) return DXGI_FORMAT_R32G32B32A32_FLOAT;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBAHalf) return DXGI_FORMAT_R16G16B16A16_FLOAT;
    else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBA) return DXGI_FORMAT_R16G16B16A16_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBA) return DXGI_FORMAT_R8G8B8A8_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppBGRA) return DXGI_FORMAT_B8G8R8A8_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppBGR) return DXGI_FORMAT_B8G8R8X8_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102XR) return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

    else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102) return DXGI_FORMAT_R10G10B10A2_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat16bppBGRA5551) return DXGI_FORMAT_B5G5R5A1_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat16bppBGR565) return DXGI_FORMAT_B5G6R5_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat32bppGrayFloat) return DXGI_FORMAT_R32_FLOAT;
    else if (wicFormatGUID == GUID_WICPixelFormat16bppGrayHalf) return DXGI_FORMAT_R16_FLOAT;
    else if (wicFormatGUID == GUID_WICPixelFormat16bppGray) return DXGI_FORMAT_R16_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat8bppGray) return DXGI_FORMAT_R8_UNORM;
    else if (wicFormatGUID == GUID_WICPixelFormat8bppAlpha) return DXGI_FORMAT_A8_UNORM;

    else return DXGI_FORMAT_UNKNOWN;
  }

  // get the number of bits per pixel for a dxgi format
  int GetDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat)
  {
    if (dxgiFormat == DXGI_FORMAT_R32G32B32A32_FLOAT) return 128;
    else if (dxgiFormat == DXGI_FORMAT_R16G16B16A16_FLOAT) return 64;
    else if (dxgiFormat == DXGI_FORMAT_R16G16B16A16_UNORM) return 64;
    else if (dxgiFormat == DXGI_FORMAT_R8G8B8A8_UNORM) return 32;
    else if (dxgiFormat == DXGI_FORMAT_B8G8R8A8_UNORM) return 32;
    else if (dxgiFormat == DXGI_FORMAT_B8G8R8X8_UNORM) return 32;
    else if (dxgiFormat == DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM) return 32;

    else if (dxgiFormat == DXGI_FORMAT_R10G10B10A2_UNORM) return 32;
    else if (dxgiFormat == DXGI_FORMAT_B5G5R5A1_UNORM) return 16;
    else if (dxgiFormat == DXGI_FORMAT_B5G6R5_UNORM) return 16;
    else if (dxgiFormat == DXGI_FORMAT_R32_FLOAT) return 32;
    else if (dxgiFormat == DXGI_FORMAT_R16_FLOAT) return 16;
    else if (dxgiFormat == DXGI_FORMAT_R16_UNORM) return 16;
    else if (dxgiFormat == DXGI_FORMAT_R8_UNORM) return 8;
    else if (dxgiFormat == DXGI_FORMAT_A8_UNORM) return 8;
  }

    
  void readImageData(const wchar_t* filenam, ImageInfo& imageInfo)  
  {

    bool imageConverted = false;
 	  WICBitmapScaler*      scaler  = NULL;
  	
    WICBitmapFrameDecode* frame   = NULL;
    WICBitmapDecoder* decoder = NULL;
    
    WICFormatConverter* converter = NULL;  

    try {

    //  getDestinationSize(frame, destWidth, destHeight);
     // scaler = new WICBitmapScaler(factory);
      
    //  scaler -> initialize(*frame, destWidth, destHeight, WICBitmapInterpolationModeCubic);
      decoder = new WICBitmapDecoder(*factory, filename, NULL, GENERIC_READ,  WICDecodeMetadataCacheOnLoad);
      

      frame = new WICBitmapFrameDecode(*decoder);

      WICPixelFormatGUID pixelFormat;
      frame -> getPixelFormat( &pixelFormat );

      WICPixelFormatGUID converterGUID;
      memcpy( &converterGUID, &pixelFormat, sizeof(pixelFormat) );
      
      UINT textureWidth;
      UINT textureHeight;
      frame -> getSize(&textureWidth, &textureHeight);


      // convert wic pixel format to dxgi pixel format
      DXGI_FORMAT dxgiFormat = GetDXGIFormatFromWICFormat(pixelFormat);

      // if the format of the image is not a supported dxgi format, try to convert it
      if (dxgiFormat == DXGI_FORMAT_UNKNOWN) {
        // get a dxgi compatible wic format from the current image format
        WICPixelFormatGUID convertToPixelFormat = GetConvertToWICFormat(pixelFormat);

        // return if no dxgi compatible format was found
        if (convertToPixelFormat == GUID_WICPixelFormatDontCare) {
          throw IException("Not found DXGIFormat");
        }
        
        // set the dxgi format
        dxgiFormat = GetDXGIFormatFromWICFormat(convertToPixelFormat);
            
        // create the format converter
        converter = new WICFormatConverter(factory);  

        // make sure we can convert to the dxgi compatible format
        BOOL canConvert = FALSE;
        converter->canConvert(pixelFormat, convertToPixelFormat, &canConvert);
        if (canConvert == FALSE) {
          throw IException("Converter cannot convert");
        }
        
        // do the conversion (wicConverter will contain the converted image)
        converter -> initialize(*frame, convertToPixelFormat, 
                                  WICBitmapDitherTypeErrorDiffusion, 0, 0, 
                                  WICBitmapPaletteTypeCustom);
        imageConverted = true;
    

      int bitsPerPixel = GetDXGIFormatBitsPerPixel(dxgiFormat); 
      int bytesPerRow = (textureWidth * bitsPerPixel + 7) / 8; 

      int imageSize = bytesPerRow * textureHeight; 

    // allocate enough memory for the raw image data, and set imageData to point to that memory
      BYTE* image=  new BYTE[imageSize];

    // copy (decoded) raw image data into the newly allocated memory (imageData)
      if (imageConverted) {
        // if image format needed to be converted, the wic converter will contain the converted image
        converter -> copyPixels(0, bytesPerRow, imageSize, *image);
      }  else {
        // no need to convert, just copy data from the wic frame
        frame -> copyPixels(0, bytesPerRow, imageSize, *image);
      }

      imageInfo.width         = textureWidth;
      imageInfo.height        = textureHeight;
      imageInfo.format        = dxgiFormat;
      
      imageInfo.rowBytes      = rowPitch;
      imageInfo.imageData     = image;
      imageInfo.imageDataSize = imageSize;
  }



};
  
}

  
