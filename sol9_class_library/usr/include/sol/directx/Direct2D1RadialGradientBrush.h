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
 *  Direct2D1RadialGradientBrush.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1RenderTarget.h>
#include <sol/directx/Direct2D1Brush.h>

namespace SOL {

class Direct2D1RadialGradientBrush : public Direct2D1Brush
{
public:
  Direct2D1RadialGradientBrush(ID2D1RenderTarget* target,
        __in CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection
        )    
  {
    ID2D1RadialGradientBrush* brush = NULL;
    HRESULT hr = target -> CreateRadialGradientBrush(
        radialGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        &brush 
        );
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateRadialGradientBrush. HRESULT(0x%lx)", hr);
    }
  }
  
  Direct2D1RadialGradientBrush(ID2D1RenderTarget* target,
        CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection
        )    
  {
    ID2D1RadialGradientBrush* brush = NULL;
    HRESULT hr = target -> CreateRadialGradientBrush(
        radialGradientBrushProperties,
        gradientStopCollection,
        &brush 
        );
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateRadialGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

  Direct2D1RadialGradientBrush(ID2D1RenderTarget* target,
        CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection
        )    
  {
    ID2D1RadialGradientBrush* brush = NULL;
    HRESULT hr = target -> CreateRadialGradientBrush(
        radialGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        &brush 
        );
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateRadialGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct2D1RadialGradientBrush()
  {
  }

  operator ID2D1RadialGradientBrush*()
  {
    return getBrush();
  }
  
  virtual ID2D1RadialGradientBrush* getBrush()
  {
    ID2D1RadialGradientBrush* brush = (ID2D1RadialGradientBrush*)getIUnknown();
    if (brush) {
      return brush;
    } else {
      throw IException("ID2D1RadialGradientBrush is NULL.");
    }
  }
  

  void setCenter(
        D2D1_POINT_2F center 
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    brush -> SetCenter(
        center 
        );
  }
  
  void setGradientOriginOffset(
        D2D1_POINT_2F gradientOriginOffset 
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    brush -> SetGradientOriginOffset(
        gradientOriginOffset 
        );
  }
    
  void setRadiusX(
        FLOAT radiusX 
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    brush -> SetRadiusX(
        radiusX 
        );
  }
    
  void setRadiusY(
        FLOAT radiusY 
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    brush -> SetRadiusY(
        radiusY 
        );
  }
    
  D2D1_POINT_2F getCenter(
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    return brush -> GetCenter();
  }
    
  D2D1_POINT_2F getGradientOriginOffset(
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    return brush -> GetGradientOriginOffset();
  }
    
  FLOAT getRadiusX(
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    return brush -> GetRadiusX();
  }
    
  FLOAT getRadiusY(
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    return brush -> GetRadiusY();
  }   

  void getGradientStopCollection(
        __out ID2D1GradientStopCollection **gradientStopCollection 
        )
  {
    ID2D1RadialGradientBrush* brush = getBrush();
    brush -> GetGradientStopCollection(
        gradientStopCollection 
        );
  }
 
}; 

}

