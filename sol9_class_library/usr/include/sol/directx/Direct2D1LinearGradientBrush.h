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
 *  Direct2D1LinearGradientBrush.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1RenderTarget.h>
#include <sol/directx/Direct2D1Brush.h>


namespace SOL {

class Direct2D1LinearGradientBrush : public Direct2D1Brush
{

public:
  Direct2D1LinearGradientBrush(ID2D1RenderTarget* target,
        __in CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection)
  :Direct2D1Brush()
  {
    ID2D1LinearGradientBrush* brush = NULL;
    HRESULT hr = target -> CreateLinearGradientBrush(
        linearGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        &brush);
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateLinearGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

public:
  Direct2D1LinearGradientBrush(ID2D1RenderTarget* target,
        __in CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection)
  :Direct2D1Brush()
  {
    ID2D1LinearGradientBrush* brush = NULL;
    HRESULT hr = target -> CreateLinearGradientBrush(
        linearGradientBrushProperties,
        brushProperties,
        gradientStopCollection,
        &brush);
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateLinearGradientBrush. HRESULT(0x%lx)", hr);
    }
  }


  Direct2D1LinearGradientBrush(ID2D1RenderTarget* target,
        CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection)
  :Direct2D1Brush()
  {
    ID2D1LinearGradientBrush* brush = NULL;
    HRESULT hr = target -> CreateLinearGradientBrush(
        linearGradientBrushProperties,
        gradientStopCollection,
        &brush);
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateLinearGradientBrush. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct2D1LinearGradientBrush()
  {
  }


  operator ID2D1LinearGradientBrush*()
  {
    return getBrush();
  }

  virtual ID2D1LinearGradientBrush* getBrush()
  {
    ID2D1LinearGradientBrush* brush = (ID2D1LinearGradientBrush*)getIUnknown();
    if (brush) {
      return brush;
    } else {
      throw IException("ID2D1LinearGradientBrush is NULL.");
    }
  }
  
  void setStartPoint(
        D2D1_POINT_2F startPoint 
        )
  {
    ID2D1LinearGradientBrush* brush = getBrush();
    brush -> SetStartPoint(
        startPoint 
        );
  }
  
    
  void setEndPoint(
        D2D1_POINT_2F endPoint 
        )
  {
    ID2D1LinearGradientBrush* brush = getBrush();
    brush -> SetEndPoint(
        endPoint 
        );
  }
    
  D2D1_POINT_2F getStartPoint(
        )
  {
    ID2D1LinearGradientBrush* brush = getBrush();
    return brush -> GetStartPoint();
  }
    
  D2D1_POINT_2F getEndPoint(
        ) 
  {
    ID2D1LinearGradientBrush* brush = getBrush();
    return brush -> GetEndPoint();
  }
    
  void getGradientStopCollection(
        __out ID2D1GradientStopCollection **gradientStopCollection 
        )
  {
    ID2D1LinearGradientBrush* brush = getBrush();
    brush -> GetGradientStopCollection(
        gradientStopCollection 
        );
  }
 
}; 

}

