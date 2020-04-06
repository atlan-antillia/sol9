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
 *  Direct2D1RoundedRectangleGeometry.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1RenderTarget.h>
#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Geometry.h>


namespace SOL {

class Direct2D1RoundedRectangleGeometry :public Direct2D1Geometry 
{
public:
  Direct2D1RoundedRectangleGeometry(ID2D1Factory* factory, __in CONST D2D1_ROUNDED_RECT *roundedRectangle)
  :Direct2D1Geometry()
  {
    ID2D1RoundedRectangleGeometry* geometry = NULL;
    HRESULT hr = factory -> CreateRoundedRectangleGeometry(
        roundedRectangle,
        &geometry 
        );
    if (SUCCEEDED(hr)) {
      set(geometry);
    } else {
      throw IException("Failed to CreateRoundedRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }

public:
  Direct2D1RoundedRectangleGeometry(ID2D1Factory* factory, CONST D2D1_ROUNDED_RECT &roundedRectangle)
  :Direct2D1Geometry()

  {
    ID2D1RoundedRectangleGeometry* geometry = NULL;
    HRESULT hr = factory -> CreateRoundedRectangleGeometry(
        roundedRectangle,
        &geometry 
        );
    if (SUCCEEDED(hr)) {
      set(geometry);
    } else {
      throw IException("Failed to CreateRoundedRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }


  ~Direct2D1RoundedRectangleGeometry()
  {
  }

  operator ID2D1RoundedRectangleGeometry*()
  {
    return getGeometry();
  }

  ID2D1RoundedRectangleGeometry* getGeometry()
  {
    ID2D1RoundedRectangleGeometry* geometry = (ID2D1RoundedRectangleGeometry*)getIUnknown();
    if (geometry) {
      return geometry;
    } else {
      throw IException("ID2D1RoundedRectangleGeometry is NULL.");
    }
  }
  

  void getRoundedRect(
        __out D2D1_ROUNDED_RECT *roundedRect 
        ) 
  {
    ID2D1RoundedRectangleGeometry* geometry = getGeometry();
    geometry -> GetRoundedRect(
        roundedRect 
        );
  } 
}; 

}

