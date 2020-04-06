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
 *  Direct2D1SolidColorBrush.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>

#include <sol/directx/Direct2D1Brush.h>


namespace SOL {

class Direct2D1SolidColorBrush : public Direct2D1Brush
{
public:
  Direct2D1SolidColorBrush(ID2D1RenderTarget* target,
         __in CONST D2D1_COLOR_F *color,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties)
  :Direct2D1Brush()
  {
    ID2D1SolidColorBrush* brush = NULL;
    HRESULT hr = target -> CreateSolidColorBrush(
        color,
        brushProperties,
        &brush );
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateSolidColorBrush. HRESULT(0x%lx)", hr);
    }
  }

  Direct2D1SolidColorBrush(ID2D1RenderTarget* target,
         CONST D2D1_COLOR_F &color)
  :Direct2D1Brush()
  {
    ID2D1SolidColorBrush* brush = NULL;
    HRESULT hr = target -> CreateSolidColorBrush(
        color,
        &brush);
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateSolidColorBrush. HRESULT(0x%lx)", hr);
    }
  }

  operator ID2D1SolidColorBrush*()
  {
    return getBrush();
  }

  virtual ID2D1SolidColorBrush* getBrush()
  {
    ID2D1SolidColorBrush* brush = (ID2D1SolidColorBrush*)getIUnknown();
    if (brush) {
      return brush;
    } else {
      throw IException("ID2D1SolidColorBrush is NULL.");
    }
  }
  
  void setColor(
        __in CONST D2D1_COLOR_F *color 
        )
  {
    ID2D1SolidColorBrush* brush = getBrush();
    brush -> SetColor(
        color 
        );
  }
  
  D2D1_COLOR_F getColor(
        )
  {
    ID2D1SolidColorBrush* brush = getBrush();
    return brush -> GetColor();
  }

    
  void setColor(
        CONST D2D1_COLOR_F &color 
        )
  {
    ID2D1SolidColorBrush* brush = getBrush();
    brush -> SetColor(
        color 
        );
  }

};

}


