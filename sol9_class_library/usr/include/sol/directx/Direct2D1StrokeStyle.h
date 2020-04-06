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
 *  Direct2D1StrokeStyle.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Factory.h>


namespace SOL {

class Direct2D1StrokeStyle :public Direct2D1Resource
{
public:
  Direct2D1StrokeStyle(ID2D1Factory* factory,
        __in CONST D2D1_STROKE_STYLE_PROPERTIES *strokeStyleProperties,
        __in CONST FLOAT *dashes,
        UINT dashesCount)
  {
    ID2D1StrokeStyle* style = NULL;
    HRESULT hr = factory -> CreateStrokeStyle(
        strokeStyleProperties,
        dashes,
        dashesCount,
        &style 
        );
    if (SUCCEEDED(hr)) {
      set(style);
    } else {
      throw IException("Failed to CreateStrokeStyle. HRESULT(0x%lx)", hr);
    }
  }
  
public:
  Direct2D1StrokeStyle(ID2D1Factory* factory,
        __in CONST D2D1_STROKE_STYLE_PROPERTIES& strokeStyleProperties,
        __in CONST FLOAT *dashes,
        UINT dashesCount)
  {
    ID2D1StrokeStyle* style = NULL;
    HRESULT hr = factory -> CreateStrokeStyle(
        strokeStyleProperties,
        dashes,
        dashesCount,
        &style 
        );
    if (SUCCEEDED(hr)) {
      set(style);
    } else {     
      throw IException("Failed to CreateStrokeStyle. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct2D1StrokeStyle()
  {
  }

  operator ID2D1StrokeStyle*()
  {
    return getStyle();
  }
  
  ID2D1StrokeStyle* getStyle()
  {
    ID2D1StrokeStyle* style = (ID2D1StrokeStyle*)getIUnknown();
    if (style) {
      return style;
    } else {
      throw IException("ID2D1StrokeStyle is NULL.");
    }
  }
  
    
  D2D1_CAP_STYLE getStartCap(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetStartCap();
  }
  
  D2D1_CAP_STYLE getEndCap(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetEndCap();
  }
    
  D2D1_CAP_STYLE getDashCap(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetDashCap();
  }
    
  FLOAT getMiterLimit(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetMiterLimit();
  }
    
  D2D1_LINE_JOIN getLineJoin(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetLineJoin();
  }
    
  FLOAT getDashOffset(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetDashOffset();
  }
    
  D2D1_DASH_STYLE getDashStyle(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetDashStyle();
  }
    
  UINT32 getDashesCount(
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    return style ->  GetDashesCount();
  }
    
    
  void getDashes(
        __out FLOAT *dashes,
        UINT dashesCount 
        )
  {
    ID2D1StrokeStyle* style = getStyle();
    style ->  GetDashes(
        dashes,
        dashesCount 
        );
  }
}; 

}

