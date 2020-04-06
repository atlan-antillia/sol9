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
 *  Direct2D1Factory.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>
#include <sol/com/ComIUnknown.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

namespace SOL {
  
class Direct2D1Factory: public ComIUnknown  {

public:
  Direct2D1Factory()
  :ComIUnknown()
  {
    ID2D1Factory* factory = NULL;

    //D2D1_DEVICE_CONTEXT_OPTIONS deviceOptions = D2D1_DEVICE_CONTEXT_OPTIONS_NONE;

    HRESULT hr = D2D1CreateFactory(
              D2D1_FACTORY_TYPE_SINGLE_THREADED,
              __uuidof( ID2D1Factory ),
              //&deviceOptions,
              (void**)&factory
              );
    
    if (SUCCEEDED(hr)) {
      set(factory);
    } else {
      throw IException("Failed  to D2D1CreateFactory. HRESULT(0x%lx)", hr);
    } 
  }

  ~Direct2D1Factory()
  {
  }

  operator ID2D1Factory*()
  {
    return getFactory();
  }

  
  ID2D1Factory* getFactory()
  {
    ID2D1Factory* factory = (ID2D1Factory*)getIUnknown();
    if (factory) {
      return factory;
    } else {
      throw IException("ID2D1Factory is NULL.");
    }
  }

  
  void reloadSystemMetrics()
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> ReloadSystemMetrics();
    if (FAILED(hr)) {
      throw IException("Failed to ReloadSystemMetrics. HRESULT(0x%lx)", hr);
    }
  }
  
   void getDesktopDpi(
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        )
  {
    ID2D1Factory* factory = getFactory();
    factory -> GetDesktopDpi(
                      dpiX,
                      dpiY 
                      );
  }

  void createRectangleGeometry(
        __in CONST D2D1_RECT_F *rectangle,
        __out ID2D1RectangleGeometry **rectangleGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateRectangleGeometry(
        rectangle,
        rectangleGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createRoundedRectangleGeometry(
        __in CONST D2D1_ROUNDED_RECT *roundedRectangle,
        __out ID2D1RoundedRectangleGeometry **roundedRectangleGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateRoundedRectangleGeometry(
        roundedRectangle,
        roundedRectangleGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRoundedRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createEllipseGeometry(
        __in CONST D2D1_ELLIPSE *ellipse,
        __out ID2D1EllipseGeometry **ellipseGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateEllipseGeometry(
        ellipse,
        ellipseGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateEllipseGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createGeometryGroup(
        D2D1_FILL_MODE fillMode,
        __in_ecount(geometriesCount) ID2D1Geometry **geometries,
        UINT geometriesCount,
        __out ID2D1GeometryGroup **geometryGroup 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateGeometryGroup(
        fillMode,
        geometries,
        geometriesCount,
        geometryGroup 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateGeometryGroup. HRESULT(0x%lx)", hr);
    }
  }

  void createTransformedGeometry(
        __in ID2D1Geometry *sourceGeometry,
        __in CONST D2D1_MATRIX_3X2_F *transform,
        __out ID2D1TransformedGeometry **transformedGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateTransformedGeometry(
        sourceGeometry,
        transform,
        transformedGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateTransformedGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createPathGeometry(
        __out ID2D1PathGeometry **pathGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreatePathGeometry(
        pathGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreatePathGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createStrokeStyle(
        __in CONST D2D1_STROKE_STYLE_PROPERTIES *strokeStyleProperties,
        __in_ecount_opt(dashesCount) CONST FLOAT *dashes,
        UINT dashesCount,
        __out ID2D1StrokeStyle **strokeStyle 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateStrokeStyle(
        strokeStyleProperties,
        dashes,
        dashesCount,
        strokeStyle 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateStrokeStyle. HRESULT(0x%lx)", hr);
    }
  }

  void createDrawingStateBlock(
        __in CONST D2D1_DRAWING_STATE_DESCRIPTION *drawingStateDescription,
        __in IDWriteRenderingParams *textRenderingParams,
        __out ID2D1DrawingStateBlock **drawingStateBlock 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateDrawingStateBlock(
        drawingStateDescription,
        textRenderingParams,
        drawingStateBlock 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateDrawingStateBlock. HRESULT(0x%lx)", hr);
    }
  }

  void createWicBitmapRenderTarget(
        __in IWICBitmap *target,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __out ID2D1RenderTarget **renderTarget 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateWicBitmapRenderTarget(
        target,
        renderTargetProperties,
        renderTarget 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateWicBitmapRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createHwndRenderTarget(
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __in CONST D2D1_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties,
        __out ID2D1HwndRenderTarget **hwndRenderTarget 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateHwndRenderTarget(
        renderTargetProperties,
        hwndRenderTargetProperties,
        hwndRenderTarget 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateHwndRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createDxgiSurfaceRenderTarget(
        __in IDXGISurface *dxgiSurface,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __out ID2D1RenderTarget **renderTarget 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateDxgiSurfaceRenderTarget(
            dxgiSurface,
            renderTargetProperties,
            renderTarget 
            );
    if (FAILED(hr)) {
      throw IException("Failed to CreateDxgiSurfaceRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void CreateDCRenderTarget(
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __out ID2D1DCRenderTarget **dcRenderTarget 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateDCRenderTarget(
        renderTargetProperties,
        dcRenderTarget 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateDCRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createRectangleGeometry(
        CONST D2D1_RECT_F &rectangle,
        __out ID2D1RectangleGeometry **rectangleGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateRectangleGeometry(
        rectangle,
        rectangleGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createRoundedRectangleGeometry(
        CONST D2D1_ROUNDED_RECT &roundedRectangle,
        __out ID2D1RoundedRectangleGeometry **roundedRectangleGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateRoundedRectangleGeometry(
        roundedRectangle,
        roundedRectangleGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateRoundedRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createEllipseGeometry(
        CONST D2D1_ELLIPSE &ellipse,
        __out ID2D1EllipseGeometry **ellipseGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateEllipseGeometry(
       ellipse,
       ellipseGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateEllipseGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createTransformedGeometry(
        __in ID2D1Geometry *sourceGeometry,
        CONST D2D1_MATRIX_3X2_F &transform,
        __out ID2D1TransformedGeometry **transformedGeometry 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateTransformedGeometry(
        sourceGeometry,
        transform,
        transformedGeometry 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateTransformedGeometry. HRESULT(0x%lx)", hr);
    }
  }

  void createStrokeStyle(
        CONST D2D1_STROKE_STYLE_PROPERTIES &strokeStyleProperties,
        __in_ecount(dashesCount) CONST FLOAT *dashes,
        UINT dashesCount,
        __deref_out ID2D1StrokeStyle **strokeStyle 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateStrokeStyle(
        strokeStyleProperties,
        dashes,
        dashesCount,
        strokeStyle 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateStrokeStyle. HRESULT(0x%lx)", hr);
    }
  }

  void createDrawingStateBlock(
        CONST D2D1_DRAWING_STATE_DESCRIPTION &drawingStateDescription,
        __out ID2D1DrawingStateBlock **drawingStateBlock 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateDrawingStateBlock(
        drawingStateDescription,
        drawingStateBlock 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateDrawingStateBlock. HRESULT(0x%lx)", hr);
    }
  }

  void createDrawingStateBlock(
        __out ID2D1DrawingStateBlock **drawingStateBlock 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateDrawingStateBlock(
        drawingStateBlock 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateDrawingStateBlock.");
    }
  }

  void createWicBitmapRenderTarget(
        __in IWICBitmap *target,
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties,
        __out ID2D1RenderTarget **renderTarget 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateWicBitmapRenderTarget(
        target,
        renderTargetProperties,
        renderTarget 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateWicBitmapRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createHwndRenderTarget(
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties,
        CONST D2D1_HWND_RENDER_TARGET_PROPERTIES &hwndRenderTargetProperties,
        __out ID2D1HwndRenderTarget **hwndRenderTarget 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory ->  CreateHwndRenderTarget(
        renderTargetProperties,
        hwndRenderTargetProperties,
        hwndRenderTarget 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateHwndRenderTarget. HRESULT(0x%lx)", hr);
    }
  }

  void createDxgiSurfaceRenderTarget(
        __in IDXGISurface *dxgiSurface,
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties,
        __deref_out ID2D1RenderTarget **renderTarget 
        )
  {
    ID2D1Factory* factory = getFactory();
    HRESULT hr = factory -> CreateDxgiSurfaceRenderTarget(
        dxgiSurface,
        renderTargetProperties,
        renderTarget 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateDxgiSurfaceRenderTarget. HRESULT(0x%lx)", hr);
    }
  }
};
  
}
