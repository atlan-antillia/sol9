/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Direct2D1DeviceContext2.h
 *
 *****************************************************************************/


#pragma once


#include <sol/directx/Direct2D1DeviceContext1.h>


namespace SOL {
  
class Direct2D1DeviceContext2  : public Direct2D1DeviceContext1 {
public:
  Direct2D1DeviceContext2(
    __in IDXGISurface             *dxgiSurface,
    __in const D2D1_CREATION_PROPERTIES *creationProperties)
  :Direct2D1DeviceContext1()
  {
    ID2D1DeviceContext2* deviceContext2 = NULL;
    HRESULT hr = ::D2D1CreateDeviceContext(
                  dxgiSurface,
                  creationProperties,
                  (ID2D1DeviceContext**)&deviceContext2);
    if (SUCCEEDED(hr)) {
      set(deviceContext2);
    } else {
      throw IException("Failed to D2D1CreateDeviceContext. HRESULT(0x%lx)", hr);
    }
  }
  
  Direct2D1DeviceContext2(
    __in ID2D1Device2*     device,
    __in D2D1_DEVICE_CONTEXT_OPTIONS deviceOptions=D2D1_DEVICE_CONTEXT_OPTIONS_NONE) //2016/11/29
  :Direct2D1DeviceContext1()
  {
    ID2D1DeviceContext2* deviceContext2 = NULL;
    HRESULT hr = device->CreateDeviceContext(

      deviceOptions,
                  (ID2D1DeviceContext**)&deviceContext2);
    if (SUCCEEDED(hr)) {
      set(deviceContext2);
    } else {
      throw IException("Failed to CreateDeviceContext. HRESULT(0x%lx)", hr);
    }
  }
    
  operator ID2D1DeviceContext2*()
  {
    return getDeviceContext2();
  }
  
  ID2D1DeviceContext2* getDeviceContext2()
  {
    ID2D1DeviceContext2* deviceContext2 = (ID2D1DeviceContext2*)getIUnknown();
    if (deviceContext2) {
      return deviceContext2;
    } else {
      throw IException("ID2D1DeviceContext2 is NULL.");
    }
  }

  void createInk(
        __in CONST D2D1_INK_POINT *startPoint,
        __out ID2D1Ink **ink 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 -> CreateInk(
        startPoint,
        ink 
        );
  }
  
  void createInkStyle(
        __in_opt CONST D2D1_INK_STYLE_PROPERTIES *inkStyleProperties,
        __out ID2D1InkStyle **inkStyle 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 ->CreateInkStyle(
            inkStyleProperties,
          inkStyle 
        );
  }
  
  
  void createGradientMesh(
        __in CONST D2D1_GRADIENT_MESH_PATCH *patches,
        UINT32 patchesCount,
        __out ID2D1GradientMesh **gradientMesh 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 ->CreateGradientMesh(
            patches,
            patchesCount,
            gradientMesh 
        );
    
  }
  
  void createImageSourceFromWic(
        __in IWICBitmapSource *wicBitmapSource,
        D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions,
        D2D1_ALPHA_MODE alphaMode,
        __out ID2D1ImageSourceFromWic **imageSource 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 -> CreateImageSourceFromWic(
              wicBitmapSource,
              loadingOptions,
              alphaMode,
          imageSource 
        );
  }
   
  void createLookupTable3D(
        D2D1_BUFFER_PRECISION precision,
        __in CONST UINT32 *extents,
        __in CONST BYTE *data,
        UINT32 dataCount,
        __in CONST UINT32 *strides,
        __out ID2D1LookupTable3D **lookupTable 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 -> CreateLookupTable3D(
            precision,
            extents,
            data,
            dataCount,
            strides,
            lookupTable 
        );
  }
    
  void createImageSourceFromDxgi(
        __in IDXGISurface **surfaces,
        UINT32 surfaceCount,
        DXGI_COLOR_SPACE_TYPE colorSpace,
        D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS options,
        __out ID2D1ImageSource **imageSource 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 -> CreateImageSourceFromDxgi(
              surfaces,
              surfaceCount,
              colorSpace,
              options,
            imageSource 
        );
  }
    
  void  getGradientMeshWorldBounds(
        __in ID2D1GradientMesh *gradientMesh,
        __out D2D1_RECT_F *pBounds 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 -> GetGradientMeshWorldBounds(
            gradientMesh,
            pBounds 
        );
  }
    
  void drawInk(
        __in ID2D1Ink *ink,
        __in ID2D1Brush *brush,
        __in_opt ID2D1InkStyle *inkStyle 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    deviceContext2 -> DrawInk(
                ink,
                brush,
                inkStyle 
        );
  }
    
  void drawGradientMesh(
        __in ID2D1GradientMesh *gradientMesh 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    deviceContext2 -> DrawGradientMesh(
                gradientMesh 
        );
  }
    
  void drawGdiMetafile(
        __in ID2D1GdiMetafile *gdiMetafile,
        __in_opt CONST D2D1_RECT_F *destinationRectangle,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    deviceContext2 -> DrawGdiMetafile(
              gdiMetafile,
              destinationRectangle,
          sourceRectangle = NULL 
        );
  }
    
  //  using ID2D1DeviceContext::DrawGdiMetafile;
    
  void createTransformedImageSource(
        __in ID2D1ImageSource *imageSource,
        __in CONST D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES *properties,
        __out ID2D1TransformedImageSource **transformedImageSource 
        )
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 -> CreateTransformedImageSource(
              imageSource,
              properties,
              transformedImageSource 
        );
  }
    
  void  createInk(
        CONST D2D1_INK_POINT &startPoint,
        __out ID2D1Ink **ink 
        )  
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2 ->
     CreateInk(&startPoint, ink);
  }
    
  void  createInkStyle(
        CONST D2D1_INK_STYLE_PROPERTIES &inkStyleProperties,
        __out ID2D1InkStyle **inkStyle 
        )  
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2->CreateInkStyle(&inkStyleProperties, inkStyle);
  }
    
  void   createImageSourceFromWic(
        __in IWICBitmapSource *wicBitmapSource,
        D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions,
        __out ID2D1ImageSourceFromWic **imageSource 
        )  
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2->CreateImageSourceFromWic(wicBitmapSource, 
          loadingOptions, D2D1_ALPHA_MODE_UNKNOWN, imageSource);
  }
    
  void createImageSourceFromWic(
        __in IWICBitmapSource *wicBitmapSource,
        __out ID2D1ImageSourceFromWic **imageSource 
        )  
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    HRESULT hr = deviceContext2->CreateImageSourceFromWic(wicBitmapSource, 
      D2D1_IMAGE_SOURCE_LOADING_OPTIONS_NONE, D2D1_ALPHA_MODE_UNKNOWN, imageSource);
  }
    
  void drawGdiMetafile(
        __in ID2D1GdiMetafile *gdiMetafile,
        CONST D2D1_RECT_F &destinationRectangle,
        CONST D2D1_RECT_F &sourceRectangle 
        )  
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    deviceContext2->DrawGdiMetafile(gdiMetafile, &destinationRectangle, &sourceRectangle);
  }
    
  void drawGdiMetafile(
        __in ID2D1GdiMetafile *gdiMetafile,
        CONST D2D1_RECT_F &destinationRectangle,
        __in CONST D2D1_RECT_F *sourceRectangle = NULL 
        )  
  {
    ID2D1DeviceContext2* deviceContext2 = getDeviceContext2();
    deviceContext2->DrawGdiMetafile(gdiMetafile, &destinationRectangle, sourceRectangle);
  }
}; 
  
}
