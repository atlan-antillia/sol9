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
 *  Direct2D1BitmapBrush.h
 *
 *****************************************************************************/

#pragma once
#include <sol/directx/Direct2D1RenderTarget.h>

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Brush.h>


namespace SOL {

class Direct2D1BitmapBrush : public Direct2D1Brush 
{
public:
  Direct2D1BitmapBrush(ID2D1RenderTarget* target,
        __in ID2D1Bitmap *bitmap,
        __in CONST D2D1_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties,
        __in CONST D2D1_BRUSH_PROPERTIES *brushProperties)
  :Direct2D1Brush()
  {
    ID2D1BitmapBrush*  brush = NULL;
    HRESULT hr= target -> CreateBitmapBrush(
                    bitmap,
                    bitmapBrushProperties,
                    brushProperties,
                    &brush);
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateBitmapBrush. HRESULT(0x%lx)", hr);
    }
  }


  Direct2D1BitmapBrush(ID2D1RenderTarget* target,
        __in ID2D1Bitmap *bitmap)
  :Direct2D1Brush()
  {
    ID2D1BitmapBrush*  brush = NULL;
    HRESULT hr= target -> CreateBitmapBrush(
                    bitmap,
                    &brush);
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateBitmapBrush. HRESULT(0x%lx)", hr);
    }
  }

public:
  Direct2D1BitmapBrush(ID2D1RenderTarget* target,
        __in ID2D1Bitmap* bitmap,
        __in CONST D2D1_BITMAP_BRUSH_PROPERTIES& bitmapBrushProperties)
  :Direct2D1Brush()
  {
    ID2D1BitmapBrush*  brush = NULL;
	//target->CreateBitmapBrush(
    HRESULT hr= target -> CreateBitmapBrush(
                    bitmap,
                    bitmapBrushProperties,
                    &brush );
    if (SUCCEEDED(hr)) {
      set(brush);
    } else {
      throw IException("Failed to CreateBitmapBrush. HRESULT(0x%lx)", hr);
    }
  }

  operator ID2D1BitmapBrush*()
  {
    return getBrush();
  }

  ID2D1BitmapBrush* getBrush()
  {
    ID2D1BitmapBrush* brush = (ID2D1BitmapBrush*)getIUnknown();
    if (brush) {
      return brush;
    } else {
      throw IException("ID2D1BitmapBrush is NULL.");
    }
  }

  void setExtendModeX(
        D2D1_EXTEND_MODE extendModeX 
        )
  {
    ID2D1BitmapBrush* brush = getBrush();
    brush -> SetExtendModeX(
        extendModeX 
        );
  }
    

  void setExtendModeY(
        D2D1_EXTEND_MODE extendModeY 
        )
  {
    ID2D1BitmapBrush* brush = getBrush();
    brush -> SetExtendModeY(
        extendModeY 
        );
  }

    
  void setInterpolationMode(
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode 
        )
  {
    ID2D1BitmapBrush* brush = getBrush();
    brush -> SetInterpolationMode(
          interpolationMode 
        );
  }

    
  void setBitmap(
        __in ID2D1Bitmap *bitmap 
        )
  {
    ID2D1BitmapBrush* brush = getBrush();
    brush -> SetBitmap(
        bitmap 
        );
  }
    
  D2D1_EXTEND_MODE getExtendModeX(
        ) 
  {
    ID2D1BitmapBrush* brush = getBrush();
    return brush -> GetExtendModeX();
  }

  D2D1_EXTEND_MODE getExtendModeY(
        ) 
  {
    ID2D1BitmapBrush* brush = getBrush();
    return brush -> GetExtendModeY();
  }

  D2D1_BITMAP_INTERPOLATION_MODE getInterpolationMode(
        ) 
  {
    ID2D1BitmapBrush* brush = getBrush();
    return brush -> GetInterpolationMode();
  }

  void getBitmap(
        __out ID2D1Bitmap **bitmap 
        ) 
  {
    ID2D1BitmapBrush* brush = getBrush();
    brush -> GetBitmap(
        bitmap 
        );
  }
};

}

