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
 *  Direct2D1RenderTarget.h
 *
 *****************************************************************************/

#pragma once

#include <sol/wic/WICBitmap.h>
#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Bitmap.h>

namespace SOL {


class Direct2D1RenderTarget : public Direct2D1Resource
{
public:
  Direct2D1RenderTarget()
  :Direct2D1Resource()
  {
  }
  
public:
  Direct2D1RenderTarget(ID2D1Factory* factory,
        __in IWICBitmap *bitmap,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties)
  {
    ID2D1RenderTarget* target = NULL;
    HRESULT hr = factory ->  CreateWicBitmapRenderTarget(
        bitmap,
        renderTargetProperties,
        &target 
    );
    if (SUCCEEDED(hr)) {
      set(target);
    } else {
      throw IException("Failed to CreateWicBitmapRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

public:
  Direct2D1RenderTarget(ID2D1Factory* factory,
        __in IWICBitmap *bitmap,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties)
  {
    ID2D1RenderTarget* target = NULL;
    HRESULT hr = factory ->  CreateWicBitmapRenderTarget(
        bitmap,
        renderTargetProperties,
        &target 
        );
    if (SUCCEEDED(hr)) {
      set(target);
    } else {
      throw IException("Failed to CreateWicBitmapRenderTarget. HRESULT(0x%lx)", hr);
    }
  }
  

  Direct2D1RenderTarget(ID2D1Factory* factory,
         __in IDXGISurface *dxgiSurface,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties)
  {
    ID2D1RenderTarget* target = NULL;
    HRESULT hr = factory -> CreateDxgiSurfaceRenderTarget(
        dxgiSurface,
        renderTargetProperties,
        &target 
    );
    if (SUCCEEDED(hr)) {
      set(target);
    } else {
      throw IException("Failed to CreateWicBitmapRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  Direct2D1RenderTarget(ID2D1Factory* factory,
         __in IDXGISurface *dxgiSurface,
         __in CONST D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties)
  {
    ID2D1RenderTarget* target = NULL;
    HRESULT hr = factory -> CreateDxgiSurfaceRenderTarget(
        dxgiSurface,
        renderTargetProperties,
        &target 
    );
    if (SUCCEEDED(hr)) {
      set(target);
    } else {
      throw IException("Failed to CreateDxgiSurfaceRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct2D1RenderTarget()
  {
  }
  
  operator ID2D1RenderTarget*()
  {
    return getTarget();
  }
  
  virtual ID2D1RenderTarget* getTarget()
  {
    ID2D1RenderTarget* target = (ID2D1RenderTarget*)getIUnknown();
    if (target) {
      return target;
    } else {
      throw IException("ID2D1RenderTarget is NULL.");
    }
  }
  

  void createBitmap(
        D2D1_SIZE_U size,
        __in CONST void *srcData,
        UINT32 pitch,
        __in CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __out ID2D1Bitmap **bitmap 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmap(
        size,
        srcData,
        pitch,
        bitmapProperties,
        bitmap 
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmap. HRESULT(0x%lx)", hr);
    }
  }
  
  void createBitmapFromWicBitmap(
        __in IWICBitmapSource *wicBitmapSource,
        __in CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __out ID2D1Bitmap **bitmap 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmapFromWicBitmap(
        wicBitmapSource,
        bitmapProperties,
        bitmap
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFromWicBitmap. HRESULT(0x%lx)", hr);
    }
  }

  void createSharedBitmap(
        __in REFIID riid,
        __inout void *data,
        __in_opt CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __out ID2D1Bitmap **bitmap 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateSharedBitmap(
        riid,
        data,
        bitmapProperties,
        bitmap 
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateSharedBitmap. HRESULT(0x%lx)", hr);
    }
  }
    
  void createBitmapBrush(
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __out ID2D1BitmapBrush **bitmapBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmapBrush(
        bitmap,
        bitmapBrushProperties,
        brushProperties,
        bitmapBrush
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapBrush. HRESULT(0x%lx)", hr);
    }
  }


  void createSolidColorBrush(
        __in CONST D2D1_COLOR_F *color,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __out ID2D1SolidColorBrush **solidColorBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateSolidColorBrush(
        color,
        brushProperties,
        solidColorBrush
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateSolidColorBrush. HRESULT(0x%lx)", hr);
    }
  }
    
  void createGradientStopCollection(
        __in CONST D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount,
        D2D1_GAMMA colorInterpolationGamma,
        D2D1_EXTEND_MODE extendMode,
        __out ID2D1GradientStopCollection **gradientStopCollection 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateGradientStopCollection(
        gradientStops,
        gradientStopsCount,
        colorInterpolationGamma,
        extendMode,
        gradientStopCollection
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateGradientStopCollection. HRESULT(0x%lx)", hr);
    }
  }
    
  void createLinearGradientBrush(
        __in CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __out ID2D1LinearGradientBrush **linearGradientBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateLinearGradientBrush(
        linearGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        linearGradientBrush
        );
    
    if (FAILED(hr)) {
      throw IException("Failed to CreateLinearGradientBrush. HRESULT(0x%lx)", hr);
    }
  }
    
  void createRadialGradientBrush(
        __in CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __out ID2D1RadialGradientBrush **radialGradientBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateRadialGradientBrush(
        radialGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        radialGradientBrush
       );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRadialGradientBrush. HRESULT(0x%lx)", hr);
    }
  }
    
  void createCompatibleRenderTarget(
        __in_opt CONST D2D1_SIZE_F *desiredSize,        
        __in_opt CONST D2D1_SIZE_U *desiredPixelSize,
        __in_opt CONST D2D1_PIXEL_FORMAT *desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        __out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateCompatibleRenderTarget(
        desiredSize,        
        desiredPixelSize,
        desiredFormat,
        options,
        bitmapRenderTarget
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCompatibleRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createLayer(        
        __in_opt CONST D2D1_SIZE_F *size,
        __out ID2D1Layer **layer 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateLayer(        
        size,
        layer
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateLayer. HRESULT(0x%lx)", hr);
    }
  }
    
  void createMesh(
        __out ID2D1Mesh **mesh 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateMesh(
        mesh
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateMesh. HRESULT(0x%lx)", hr);
    }
  }
    
  void drawLine(
        D2D1_POINT_2F point0,
        D2D1_POINT_2F point1,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawLine(
        point0,
        point1,
        brush,
        strokeWidth,
        strokeStyle
    );
  }
    
  void drawRectangle(
        __in CONST D2D1_RECT_F *rect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawRectangle(
        rect,
        brush,
        strokeWidth,
        strokeStyle
    );
  }
    
  void fillRectangle(
        __in CONST D2D1_RECT_F *rect,
        __in ID2D1Brush *brush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillRectangle(
        rect,
        brush
    );
  }

  void drawRoundedRectangle(
        __in CONST D2D1_ROUNDED_RECT *roundedRect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawRoundedRectangle(
        roundedRect,
        brush,
        strokeWidth,
        strokeStyle 
    );
  }
    
  void fillRoundedRectangle(
        __in CONST D2D1_ROUNDED_RECT *roundedRect,
        __in ID2D1Brush *brush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillRoundedRectangle(
        roundedRect,
        brush
    );
  }
    
  void drawEllipse(
        __in CONST D2D1_ELLIPSE *ellipse,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawEllipse(
        ellipse,
        brush,
        strokeWidth,
        strokeStyle
    );
  }
    
  void fillEllipse(
        __in CONST D2D1_ELLIPSE *ellipse,
        __in ID2D1Brush *brush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillEllipse(
        ellipse,
        brush
    );
  }
    
  void drawGeometry(
        __in ID2D1Geometry *geometry,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawGeometry(
        geometry,
        brush,
        strokeWidth,
        strokeStyle
    );
  }
    
  void fillGeometry(
        __in ID2D1Geometry *geometry,
        __in ID2D1Brush *brush,
        __in_opt ID2D1Brush *opacityBrush = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillGeometry(
        geometry,
        brush,
        opacityBrush
    );
  }
    
    
  void fillMesh(
        __in ID2D1Mesh *mesh,
        __in ID2D1Brush *brush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillMesh(
        mesh,
        brush
    );
  }
    
    
  void fillOpacityMask(
        __in ID2D1Bitmap *opacityMask,
        __in ID2D1Brush *brush,
        D2D1_OPACITY_MASK_CONTENT content,
        __in_opt CONST D2D1_RECT_F *destinationRectangle = NULL,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillOpacityMask(
        opacityMask,
        brush,
        content,
        destinationRectangle,
        sourceRectangle
    );
  }
    
  void drawBitmap(
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_RECT_F *destinationRectangle = NULL,
        FLOAT opacity = 1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawBitmap(
        bitmap,
        destinationRectangle,
        opacity,
        interpolationMode,
        sourceRectangle 
    );
  }
        
  void drawText(
        __in CONST WCHAR *string,
        UINT stringLength,
        __in IDWriteTextFormat *textFormat,
        __in CONST D2D1_RECT_F *layoutRect,
        __in ID2D1Brush *defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE,
        DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawText(
        string,
        stringLength,
        textFormat,
        layoutRect,
        defaultForegroundBrush,
        options,
        measuringMode 
    );
  }
    
  void drawTextLayout(
        D2D1_POINT_2F origin,
        __in IDWriteTextLayout *textLayout,
        __in ID2D1Brush *defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawTextLayout(
        origin,
        textLayout,
        defaultForegroundBrush,
        options
    );
  }
    
  void drawGlyphRun(
        D2D1_POINT_2F baselineOrigin,
        __in CONST DWRITE_GLYPH_RUN *glyphRun,
        __in ID2D1Brush *foregroundBrush,
        DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawGlyphRun(
        baselineOrigin,
        glyphRun,
        foregroundBrush,
        measuringMode
    );
  }
    
  void setTransform(
        __in CONST D2D1_MATRIX_3X2_F *transform 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SetTransform(
        transform
    );
  }
    
  void getTransform(
        __out D2D1_MATRIX_3X2_F *transform 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> GetTransform(
        transform 
    );
  }
    
  void setAntialiasMode(
        D2D1_ANTIALIAS_MODE antialiasMode 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SetAntialiasMode(
        antialiasMode 
    );
  }
    
  D2D1_ANTIALIAS_MODE getAntialiasMode(
        )
  {
    ID2D1RenderTarget* target = getTarget();
    return target -> GetAntialiasMode();
  }

  void setTextAntialiasMode(
        D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SetTextAntialiasMode(
        textAntialiasMode 
    );
  }

  D2D1_TEXT_ANTIALIAS_MODE getTextAntialiasMode(
        ) 
  {
    ID2D1RenderTarget* target = getTarget();
    return target -> GetTextAntialiasMode();
  }

  void setTextRenderingParams(
        __in_opt IDWriteRenderingParams *textRenderingParams = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SetTextRenderingParams(
        textRenderingParams 
    );
  }

  void getTextRenderingParams(
        __out IDWriteRenderingParams **textRenderingParams 
        ) 
  {
    ID2D1RenderTarget* target = getTarget();
    target -> GetTextRenderingParams(
        textRenderingParams
    );
  }

    
  void setTags(
        D2D1_TAG tag1,
        D2D1_TAG tag2 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SetTags(
        tag1,
        tag2 
    );
  }

  void getTags(
        __out D2D1_TAG *tag1 = NULL,
        __out D2D1_TAG *tag2 = NULL 
        ) 
  {
    ID2D1RenderTarget* target = getTarget();
    target -> GetTags(
        tag1,
        tag2
    );
  }

    
  void pushLayer(
        __in CONST D2D1_LAYER_PARAMETERS *layerParameters,
        __in ID2D1Layer *layer 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> PushLayer(
        layerParameters,
        layer
    );
  }
    
    
  void popLayer(
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> PopLayer();
  }
    
  void flush(
        __out_opt D2D1_TAG *tag1 = NULL,
        __out_opt D2D1_TAG *tag2 = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> Flush(
        tag1,
        tag2
    );
    if (FAILED(hr) ) {
      throw IException("Failed to Flush. HRESULT(0x%lx)", hr);
    }
  }
    
  void saveDrawingState(
        __inout ID2D1DrawingStateBlock *drawingStateBlock 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SaveDrawingState(
        drawingStateBlock
    );
  }
    
  void restoreDrawingState(
        __in ID2D1DrawingStateBlock *drawingStateBlock 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> RestoreDrawingState(
        drawingStateBlock 
    );
  }

  void pushAxisAlignedClip(
        __in CONST D2D1_RECT_F *clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> PushAxisAlignedClip(
        clipRect,
        antialiasMode 
    );
  }
    
  void popAxisAlignedClip(
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> PopAxisAlignedClip();
  }
    
  void clear(
        __in CONST D2D1_COLOR_F *clearColor = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> Clear(
        clearColor 
    );
  }

  void beginDraw()
  {
    ID2D1RenderTarget* target = getTarget();
    target -> BeginDraw();
  }
    
    
  void endDraw(
        __out D2D1_TAG *tag1 = NULL,
        __out D2D1_TAG *tag2 = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> EndDraw(
          tag1,
          tag2 
          ) ;
    if (FAILED(hr))  {
      throw IException("Failed to EndDraw. HRESULT(0x%lx)", hr);
    }
  }

  void end()
  {
  	D2D1_TAG tag1 = 0;
  	D2D1_TAG tag2 = 0;
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> EndDraw(
          &tag1,
          &tag2 
          ) ;
    if (FAILED(hr))  {
      throw IException("Failed to EndDraw. HRESULT(0x%lx), tag1(0x%lx), tag2(0x%lx)", hr, tag1, tag2);
    }
  }

  D2D1_PIXEL_FORMAT getPixelFormat(
        )
  {
    ID2D1RenderTarget* target = getTarget();
    return target -> GetPixelFormat();
  }

    
  void setDpi(
        FLOAT dpiX,
        FLOAT dpiY 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SetDpi(
        dpiX,
        dpiY
    );
  }
    
  void getDpi(
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> GetDpi(
        dpiX,
        dpiY
    );
  }

  D2D1_SIZE_F getSize(
        )
  {
    ID2D1RenderTarget* target = getTarget();
    return target -> GetSize();
  }

  void getSize(UINT& width, UINT& height)
  {
    ID2D1RenderTarget* target = getTarget();
    D2D1_SIZE_F size = target -> GetSize();
    width  = static_cast<UINT>(size.width + .5f);
    height = static_cast<UINT>(size.height + .5f);


  	width  = (UINT)size.width;
  	height = (UINT)size.height;
  }

  void getSize(FLOAT& width, FLOAT& height)
  {
    ID2D1RenderTarget* target = getTarget();
    D2D1_SIZE_F size = target -> GetSize();
  	width = size.width;
  	height = size.height;
  }
	
    
  D2D1_SIZE_U getPixelSize(
        )
  {
    ID2D1RenderTarget* target = getTarget();
    return target -> GetPixelSize();
  }

  UINT32 getMaximumBitmapSize(
        )
  {
    ID2D1RenderTarget* target = getTarget();
    return target -> GetMaximumBitmapSize();
  }

  BOOL isSupported(
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties 
        ) 
  {
    ID2D1RenderTarget* target = getTarget();
    return target -> IsSupported( renderTargetProperties );
  }

  void createBitmap(
        D2D1_SIZE_U size,
        __in CONST void *srcData,
        UINT32 pitch,
        CONST D2D1_BITMAP_PROPERTIES &bitmapProperties,
        __out ID2D1Bitmap **bitmap 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmap(
        size,
        srcData,
        pitch,
        bitmapProperties,
        bitmap 
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmap. HRESULT(0x%lx)", hr);
    }
  }
        
  void createBitmap(
        D2D1_SIZE_U size,
        CONST D2D1_BITMAP_PROPERTIES &bitmapProperties,
        __out ID2D1Bitmap **bitmap 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmap(
        size,
        bitmapProperties,
        bitmap
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmap. HRESULT(0x%lx)", hr);
    }
  }
    
  void createBitmapFromWicBitmap(
        __in IWICBitmapSource *wicBitmapSource,
        CONST D2D1_BITMAP_PROPERTIES &bitmapProperties,
        __out ID2D1Bitmap **bitmap 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmapFromWicBitmap(
        wicBitmapSource,
        bitmapProperties,
        bitmap
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapFromWicBitmap. HRESULT(0x%lx)", hr);
    }
  }
    
  void createBitmapFromWicBitmap(
        __in IWICBitmapSource *wicBitmapSource,
        __out ID2D1Bitmap **bitmap 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmapFromWicBitmap(
          wicBitmapSource,
          bitmap 
        );
    if (FAILED(hr)) {
      throw IException("");
    }
  }

  void createBitmapBrush(
        __in ID2D1Bitmap *bitmap,
        __out ID2D1BitmapBrush **bitmapBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmapBrush(
        bitmap,
        bitmapBrush
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapBrush. HRESULT(0x%lx)", hr);
    }
  }
    
  void createBitmapBrush(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties,
        __out ID2D1BitmapBrush **bitmapBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmapBrush(
        bitmap,
        bitmapBrushProperties,
        bitmapBrush  
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapBrush. HRESULT(0x%lx)", hr);
    }
  }
        
   void createBitmapBrush(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __out ID2D1BitmapBrush **bitmapBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateBitmapBrush(
        bitmap,
        bitmapBrushProperties,
        brushProperties,
        bitmapBrush 
    ) ;
    if (FAILED(hr)) {
      throw IException("Failed to CreateBitmapBrush. HRESULT(0x%lx)", hr);
    }
  }
    
  void createSolidColorBrush(
        CONST D2D1_COLOR_F &color,
        __out ID2D1SolidColorBrush **solidColorBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateSolidColorBrush(
        color,
        solidColorBrush
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateSolidColorBrush. HRESULT(0x%lx)", hr);
    }
  }

  void createSolidColorBrush(
        CONST D2D1_COLOR_F &color,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __out ID2D1SolidColorBrush **solidColorBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateSolidColorBrush(
        color,
        brushProperties,
        solidColorBrush 
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateSolidColorBrush. HRESULT(0x%lx)", hr);
    }
  }

  void createGradientStopCollection(
        __in CONST D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount,
        __out ID2D1GradientStopCollection **gradientStopCollection 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateGradientStopCollection(
        gradientStops,
        gradientStopsCount,
        gradientStopCollection 
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateGradientStopCollection. HRESULT(0x%lx)", hr);
    }
  }

  void createLinearGradientBrush(
        CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __out ID2D1LinearGradientBrush **linearGradientBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateLinearGradientBrush(
        linearGradientBrushProperties,
        gradientStopCollection,
        linearGradientBrush
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateLinearGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

  void createLinearGradientBrush(
        CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __out ID2D1LinearGradientBrush **linearGradientBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateLinearGradientBrush(
        linearGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        linearGradientBrush 
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateLinearGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

  void createRadialGradientBrush(
        CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __out ID2D1RadialGradientBrush **radialGradientBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateRadialGradientBrush(
        radialGradientBrushProperties,
        gradientStopCollection,
        radialGradientBrush
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRadialGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

  void createRadialGradientBrush(
        CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __out ID2D1RadialGradientBrush **radialGradientBrush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateRadialGradientBrush(
        radialGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        radialGradientBrush 
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRadialGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

  void createCompatibleRenderTarget(
        __out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateCompatibleRenderTarget(
        bitmapRenderTarget
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCompatibleRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        __out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateCompatibleRenderTarget(
        desiredSize,
        bitmapRenderTarget
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCompatibleRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        D2D1_SIZE_U desiredPixelSize,
        __out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateCompatibleRenderTarget(
        desiredSize,
        desiredPixelSize,
        bitmapRenderTarget
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCompatibleRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        D2D1_SIZE_U desiredPixelSize,
        D2D1_PIXEL_FORMAT desiredFormat,
        __out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateCompatibleRenderTarget(
        desiredSize,
        desiredPixelSize,
        desiredFormat,
        bitmapRenderTarget
    ) ;
    if (FAILED(hr)) {
      throw IException("Failed to CreateCompatibleRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        D2D1_SIZE_U desiredPixelSize,
        D2D1_PIXEL_FORMAT desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        __out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateCompatibleRenderTarget(
        desiredSize,
        desiredPixelSize,
        desiredFormat,
        options,
        bitmapRenderTarget
    );
    if (FAILED(hr)) {
      throw IException("Failed to CreateCompatibleRenderTarget. HRESULT(0x%lx)", hr);
    }    
  }

  void createLayer(
        D2D1_SIZE_F size,
        __out ID2D1Layer **layer 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateLayer(
        size,
        layer
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateLayer. HRESULT(0x%lx)", hr);
    }
  }

  void createLayer(
        __out ID2D1Layer **layer 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    HRESULT hr = target -> CreateLayer(
        layer 
        );
    if (FAILED(hr) ) {
      throw IException("Failed to CreateLayer. HRESULT(0x%lx)", hr);
    }
  }

  void drawRectangle(
        CONST D2D1_RECT_F &rect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawRectangle(
        rect,
        brush,
        strokeWidth,
        strokeStyle 
        );
  }

  void fillRectangle(
        CONST D2D1_RECT_F &rect,
        __in ID2D1Brush *brush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillRectangle(
        rect,
        brush 
        );
  }

  void drawRoundedRectangle(
        CONST D2D1_ROUNDED_RECT &roundedRect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawRoundedRectangle(
        roundedRect,
        brush,
        strokeWidth,
        strokeStyle 
        );
  }

  void fillRoundedRectangle(
        CONST D2D1_ROUNDED_RECT &roundedRect,
        __in ID2D1Brush *brush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillRoundedRectangle(
        roundedRect,
        brush 
        );
  }

  void drawEllipse(
        CONST D2D1_ELLIPSE &ellipse,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawEllipse(
        ellipse,
        brush,
        strokeWidth,
        strokeStyle 
        );
  }

  void fillEllipse(
        CONST D2D1_ELLIPSE &ellipse,
        __in ID2D1Brush *brush 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillEllipse(
        ellipse,
        brush 
        );
  }

  void fillOpacityMask(
        __in ID2D1Bitmap *opacityMask,
        __in ID2D1Brush *brush,
        D2D1_OPACITY_MASK_CONTENT content,
        CONST D2D1_RECT_F &destinationRectangle,
        CONST D2D1_RECT_F &sourceRectangle 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> FillOpacityMask(
        opacityMask,
        brush,
        content,
        destinationRectangle,
        sourceRectangle 
        );
  }

  void drawBitmap(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_RECT_F &destinationRectangle,
        FLOAT opacity = 1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawBitmap(
        bitmap,
        destinationRectangle,
        opacity,
        interpolationMode,
        sourceRectangle 
        );
  }

  void drawBitmap(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_RECT_F &destinationRectangle,
        FLOAT opacity,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
        CONST D2D1_RECT_F &sourceRectangle 
        )
  {
    ID2D1RenderTarget* target = getTarget();
     target -> DrawBitmap(
        bitmap,
        destinationRectangle,
        opacity,
        interpolationMode,
        sourceRectangle 
        );
  }

  void setTransform(
        CONST D2D1_MATRIX_3X2_F &transform 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> SetTransform(
        transform 
        );
  }

  void pushLayer(
        CONST D2D1_LAYER_PARAMETERS &layerParameters,
        __in ID2D1Layer *layer 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> PushLayer(
        layerParameters,
        layer 
        );
  }

  void pushAxisAlignedClip(
        CONST D2D1_RECT_F &clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode 
        )
  {
    ID2D1RenderTarget* target = getTarget();
     target -> PushAxisAlignedClip(
        clipRect,
        antialiasMode 
        );
  }

    
  void clear(
        CONST D2D1_COLOR_F &clearColor 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> Clear(
        clearColor 
        );
  }

    
  void drawText(
        __in_ecount(stringLength) CONST WCHAR *string,
        UINT stringLength,
        __in IDWriteTextFormat *textFormat,
        CONST D2D1_RECT_F &layoutRect,
        __in ID2D1Brush *defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE,
        DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    target -> DrawText(
        string,
        stringLength,
        textFormat,
        layoutRect,
        defaultForegroundBrush,
        options,
        measuringMode 
        );
  }

  BOOL isSupported(
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties 
        )
  {
    ID2D1RenderTarget* target = getTarget();
    return  target -> IsSupported(
            renderTargetProperties 
            );
  }
};

}
 
