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
 *  Direct2D1DeviceContext.h
 *
 *****************************************************************************/


#pragma once


#include <sol/directx/Direct2D1RenderTarget.h>


namespace SOL {


class Direct2D1DeviceContext: public Direct2D1RenderTarget {
public:
  Direct2D1DeviceContext()
  :Direct2D1RenderTarget()
  {
  }
  
public:
  Direct2D1DeviceContext(
        __in IDXGISurface             *dxgiSurface,
        __in const D2D1_CREATION_PROPERTIES *creationProperties)
  :Direct2D1RenderTarget()
  {
    ID2D1DeviceContext*  d2dDeviceContext = NULL;
    HRESULT hr = ::D2D1CreateDeviceContext(
                  dxgiSurface,
                  creationProperties,
                  &d2dDeviceContext);
    if (SUCCEEDED(hr)) {
      set(d2dDeviceContext);
    } else {
      throw IException("Failed to D2D1CreateDeviceContext. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct2D1DeviceContext()
  {
  }

  operator ID2D1DeviceContext*()
  {
    return getID2D1DeviceContext();
  }
  
  ID2D1DeviceContext* getID2D1DeviceContext()
  {
    ID2D1DeviceContext* context = (ID2D1DeviceContext* )getIUnknown();
    if (context) {
      return context;
    } else {
      throw IException("ID2D1DeviceContext is NULL.");
    }
  }
  
/*    
    using ID2D1RenderTarget::CreateBitmap;
    
    using ID2D1RenderTarget::CreateBitmapFromWicBitmap;
*/
  
  void createColorContext(
        D2D1_COLOR_SPACE space,
        __in_opt CONST BYTE *profile,
        UINT32 profileSize,
        __out ID2D1ColorContext **colorContext 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> CreateColorContext(
        space,
        profile,
        profileSize,
        colorContext 
        );
  }
  
  void createColorContextFromFilename(
        __in PCWSTR filename,
        __out ID2D1ColorContext **colorContext 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> CreateColorContextFromFilename(
          filename,
          colorContext 
        );
  }
    
  void createColorContextFromWicColorContext(
        __in IWICColorContext *wicColorContext,
        __out ID2D1ColorContext **colorContext 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> CreateColorContextFromWicColorContext(
          wicColorContext,
          colorContext 
        );
  }
    
  void createBitmapFromDxgiSurface(
        __in IDXGISurface *surface,
        __in_opt CONST D2D1_BITMAP_PROPERTIES1 *bitmapProperties,
        __out ID2D1Bitmap1 **bitmap 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> CreateBitmapFromDxgiSurface(
          surface,
          bitmapProperties,
          bitmap 
        );
  }
    
  void createEffect(
        __in REFCLSID effectId,
        __out ID2D1Effect **effect 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> CreateEffect(
        effectId,
        effect 
        );
  }

/*    
    using ID2D1RenderTarget::CreateGradientStopCollection;
 */   

  void createImageBrush(
        __in_opt ID2D1Image *image,
        __in CONST D2D1_IMAGE_BRUSH_PROPERTIES *imageBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __out ID2D1ImageBrush **imageBrush 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> CreateImageBrush(
          image,
          imageBrushProperties,
          brushProperties,
          imageBrush 
        );
  }

/*    
    using ID2D1RenderTarget::CreateBitmapBrush;
 */    

  void createCommandList(
        __out ID2D1CommandList **commandList 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> CreateCommandList(
        commandList 
        );
  }
    
  BOOL isDxgiFormatSupported(
        DXGI_FORMAT format 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    return context -> IsDxgiFormatSupported(
        format 
        );
  }
    
  BOOL isBufferPrecisionSupported(
        D2D1_BUFFER_PRECISION bufferPrecision 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    return context -> IsBufferPrecisionSupported(
          bufferPrecision 
        );
  }
    
  void getImageLocalBounds(
        __in ID2D1Image *image,
        __out D2D1_RECT_F *localBounds 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetImageLocalBounds(
          image,
          localBounds 
        );
  }
    
  void getImageWorldBounds(
        __in ID2D1Image *image,
        __out D2D1_RECT_F *worldBounds 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetImageWorldBounds(
          image,
          worldBounds 
        );
  }
    
  void getGlyphRunWorldBounds(
        D2D1_POINT_2F baselineOrigin,
        __in CONST DWRITE_GLYPH_RUN *glyphRun,
        DWRITE_MEASURING_MODE measuringMode,
        __out D2D1_RECT_F *bounds 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetGlyphRunWorldBounds(
          baselineOrigin,
          glyphRun,
          measuringMode,
          bounds 
        );
  }
    
  void getDevice(
        __out ID2D1Device** device 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetDevice(
          device 
        );
  }
    
  void setTarget(
        __in ID2D1Image *image 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> SetTarget(image);
  }
  
  void getTarget(
        __out ID2D1Image **image 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetTarget(
        image 
        );
  }
    
  void setRenderingControls(
        __in CONST D2D1_RENDERING_CONTROLS* renderingControls
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> SetRenderingControls(
        renderingControls 
        );
  }
    
  void getRenderingControls(
        __out D2D1_RENDERING_CONTROLS* renderingControls
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetRenderingControls(
        renderingControls 
        );
  }
    
  void setPrimitiveBlend(
        D2D1_PRIMITIVE_BLEND primitiveBlend 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> SetPrimitiveBlend(
        primitiveBlend 
        );
  }
    
  D2D1_PRIMITIVE_BLEND getPrimitiveBlend()
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    return context -> GetPrimitiveBlend();
  }
    
  void setUnitMode(
        D2D1_UNIT_MODE unitMode 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> SetUnitMode(
        unitMode 
        );
  }
    
  D2D1_UNIT_MODE getUnitMode()
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    return context -> GetUnitMode( );
  }
    
/*
  using ID2D1RenderTarget::DrawGlyphRun;
  */  

 void drawImage(
        __in ID2D1Image *image,
        __in_opt CONST D2D1_POINT_2F *targetOffset = NULL,
        __in_opt CONST D2D1_RECT_F *imageRectangle = NULL,
        D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawImage(
          image,
          targetOffset,
          imageRectangle,
          interpolationMode,
          compositeMode 
        );
  }
    
  void drawGdiMetafile(
        __in ID2D1GdiMetafile *gdiMetafile,
        __in_opt CONST D2D1_POINT_2F *targetOffset = NULL 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawGdiMetafile(
          gdiMetafile,
          targetOffset
        );
  }

  /*    
    using ID2D1RenderTarget::DrawBitmap;
    
    using ID2D1RenderTarget::PushLayer;
  */  

  void invalidateEffectInputRectangle(
        __in ID2D1Effect *effect,
        UINT32 input,
        __in CONST D2D1_RECT_F *inputRectangle 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> InvalidateEffectInputRectangle(
          effect,
          input,
          inputRectangle 
        );
  }
    
  void getEffectInvalidRectangleCount(
        __in ID2D1Effect *effect,
        __out UINT32 *rectangleCount 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetEffectInvalidRectangleCount(
          effect,
          rectangleCount 
        );
  }
    
  void getEffectInvalidRectangles(
        __in ID2D1Effect *effect,
        __out D2D1_RECT_F *rectangles,
        UINT32 rectanglesCount 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetEffectInvalidRectangles(
          effect,
          rectangles,
          rectanglesCount 
        );
  }
    
  void getEffectRequiredInputRectangles(
        __in ID2D1Effect *renderEffect,
        __in_opt CONST D2D1_RECT_F *renderImageRectangle,
        __in  CONST D2D1_EFFECT_INPUT_DESCRIPTION *inputDescriptions,
        __out D2D1_RECT_F *requiredInputRects,
        UINT32 inputCount 
        )
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> GetEffectRequiredInputRectangles(
          renderEffect,
          renderImageRectangle,
          inputDescriptions,
          requiredInputRects,
          inputCount 
        );
  }
    
/*
  using ID2D1RenderTarget::FillOpacityMask;
 */   
  void  createBitmap(
        D2D1_SIZE_U size,
        __in_opt CONST void *sourceData,
        UINT32 pitch,
        CONST D2D1_BITMAP_PROPERTIES1 &bitmapProperties,
        __out ID2D1Bitmap1 **bitmap 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();

    HRESULT hr = context -> CreateBitmap(size, sourceData, pitch, &bitmapProperties, bitmap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmap.");
    }
  }
    
  void createBitmapFromWicBitmap(
        __in IWICBitmapSource *wicBitmapSource,
        CONST D2D1_BITMAP_PROPERTIES1 &bitmapProperties,
        __out ID2D1Bitmap1 **bitmap 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();

    HRESULT hr = context -> CreateBitmapFromWicBitmap(wicBitmapSource, &bitmapProperties, bitmap);
    
  }
    
  void  createBitmapFromWicBitmap(
        __in IWICBitmapSource *wicBitmapSource,
        __out ID2D1Bitmap1 **bitmap 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    HRESULT hr = context -> CreateBitmapFromWicBitmap(wicBitmapSource, NULL, bitmap);
  }
    
  void  createBitmapFromDxgiSurface(
        __in IDXGISurface *surface,
        CONST D2D1_BITMAP_PROPERTIES1 &bitmapProperties,
        __out ID2D1Bitmap1 **bitmap 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    HRESULT hr = context -> CreateBitmapFromDxgiSurface(surface, &bitmapProperties, bitmap);
  }
    
  void  createImageBrush(
        __in_opt ID2D1Image *image,
        CONST D2D1_IMAGE_BRUSH_PROPERTIES &imageBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __out ID2D1ImageBrush **imageBrush 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    HRESULT hr = context -> CreateImageBrush(image, &imageBrushProperties, &brushProperties, imageBrush);
  }
    
  void  createImageBrush(
        __in_opt ID2D1Image *image,
        CONST D2D1_IMAGE_BRUSH_PROPERTIES &imageBrushProperties,
        __out ID2D1ImageBrush **imageBrush 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    HRESULT hr = context -> CreateImageBrush(image,&imageBrushProperties, NULL, imageBrush);
  }
    
  void  createBitmapBrush(
        __in_opt ID2D1Bitmap *bitmap,
        __out ID2D1BitmapBrush1 **bitmapBrush 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    HRESULT hr = context -> CreateBitmapBrush(bitmap, NULL, NULL, bitmapBrush);
  }
    
  void createBitmapBrush(
        __in_opt ID2D1Bitmap *bitmap,
        CONST D2D1_BITMAP_BRUSH_PROPERTIES1 &bitmapBrushProperties,
        __out ID2D1BitmapBrush1 **bitmapBrush 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    HRESULT hr = context -> CreateBitmapBrush(bitmap, &bitmapBrushProperties, NULL, bitmapBrush);
  }
    
  void createBitmapBrush(
        __in_opt ID2D1Bitmap *bitmap,
        CONST D2D1_BITMAP_BRUSH_PROPERTIES1 &bitmapBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __out ID2D1BitmapBrush1 **bitmapBrush 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
  
    HRESULT hr = context -> CreateBitmapBrush(bitmap, &bitmapBrushProperties, &brushProperties, bitmapBrush);
  }
    
  void drawImage(
        __in ID2D1Effect *effect,
        __in_opt CONST D2D1_POINT_2F *targetOffset = NULL,
        __in_opt CONST D2D1_RECT_F *imageRectangle = NULL,
        D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    ;
    ID2D1Image *output = NULL;
    effect->GetOutput(&output);
    context -> DrawImage(output, targetOffset, imageRectangle, interpolationMode, compositeMode);
        output->Release();
  }
    
  void drawImage(
        __in ID2D1Image *image,
        D2D1_INTERPOLATION_MODE interpolationMode,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawImage(image, NULL, NULL, interpolationMode, compositeMode);
  }
    
  void drawImage(
        __in ID2D1Effect *effect,
        D2D1_INTERPOLATION_MODE interpolationMode,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawImage(effect, NULL, NULL, interpolationMode, compositeMode);
  }
    
  void drawImage(
        __in ID2D1Image *image,
        D2D1_POINT_2F targetOffset,
        D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawImage(image, &targetOffset, NULL, interpolationMode, compositeMode);
  }
    
  void drawImage(
        __in ID2D1Effect *effect,
        D2D1_POINT_2F targetOffset,
        D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawImage(effect, &targetOffset, NULL, interpolationMode, compositeMode);
  }
    
  void drawImage(
        __in ID2D1Image *image,
        D2D1_POINT_2F targetOffset,
        CONST D2D1_RECT_F &imageRectangle,
        D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawImage(image, &targetOffset, &imageRectangle, interpolationMode, compositeMode);
  }
    
  void drawImage(
        __in ID2D1Effect *effect,
        D2D1_POINT_2F targetOffset,
        CONST D2D1_RECT_F &imageRectangle,
        D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
        D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawImage(effect, &targetOffset, &imageRectangle, interpolationMode, compositeMode);
  }
    
  void pushLayer(
        CONST D2D1_LAYER_PARAMETERS1 &layerParameters,
        __in_opt ID2D1Layer *layer 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> PushLayer(&layerParameters, layer);
  }
    
  void drawGdiMetafile(
        __in ID2D1GdiMetafile *gdiMetafile,
        D2D1_POINT_2F targetOffset 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawGdiMetafile(gdiMetafile, &targetOffset);
  }
    
  void drawBitmap(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_RECT_F &destinationRectangle,
        FLOAT opacity,
        D2D1_INTERPOLATION_MODE interpolationMode,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL,
        __in_opt CONST D2D1_MATRIX_4X4_F *perspectiveTransform = NULL 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform);
  }
    
  void drawBitmap(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_RECT_F &destinationRectangle,
        FLOAT opacity,
        D2D1_INTERPOLATION_MODE interpolationMode,
        CONST D2D1_RECT_F &sourceRectangle,
        __in_opt CONST D2D1_MATRIX_4X4_F *perspectiveTransform = NULL 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle, perspectiveTransform);
  }
    
  void drawBitmap(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_RECT_F &destinationRectangle,
        FLOAT opacity,
        D2D1_INTERPOLATION_MODE interpolationMode,
        CONST D2D1_RECT_F &sourceRectangle,
        CONST D2D1_MATRIX_4X4_F &perspectiveTransform 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle, &perspectiveTransform);
  }
    
  void fillOpacityMask(
        __in ID2D1Bitmap *opacityMask,
        __in ID2D1Brush *brush,
        CONST D2D1_RECT_F &destinationRectangle,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> FillOpacityMask(opacityMask, brush, &destinationRectangle, sourceRectangle);
  }
    
  void fillOpacityMask(
        __in ID2D1Bitmap *opacityMask,
        __in ID2D1Brush *brush,
        CONST D2D1_RECT_F &destinationRectangle,
        CONST D2D1_RECT_F &sourceRectangle 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> FillOpacityMask(opacityMask, brush, &destinationRectangle, &sourceRectangle);
  }
    
  void setRenderingControls(
        CONST D2D1_RENDERING_CONTROLS &renderingControls 
        )  
  {
    ID2D1DeviceContext* context = getID2D1DeviceContext();
    context -> SetRenderingControls(&renderingControls);
  }
}; 

}

