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
 *  Direct2D1RectangleGeometry.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Geometry.h>
#include <sol/directx/Direct2D1RenderTarget.h>


namespace SOL {

class Direct2D1RectangleGeometry : public Direct2D1Geometry
{
public:
  Direct2D1RectangleGeometry(ID2D1Factory* factory, __in D2D1_RECT_F* rectangle)
  {
    ID2D1RectangleGeometry* geometry = NULL;
    HRESULT hr = factory ->  CreateRectangleGeometry(
        rectangle,
        &geometry 
        );
    if (SUCCEEDED(hr)) {
      set(geometry);
    } else {
      throw IException("Faile to CreateRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }
  
  Direct2D1RectangleGeometry(ID2D1Factory* factory, CONST D2D1_RECT_F &rectangle)
  {
    ID2D1RectangleGeometry* geometry = NULL;
    HRESULT hr = factory ->  CreateRectangleGeometry(
        rectangle,
        &geometry 
        );
    if (SUCCEEDED(hr)) {
      set(geometry);
    } else {
      throw IException("Faile to CreateRectangleGeometry. HRESULT(0x%lx)", hr);
    }
  }
  
  
  ~Direct2D1RectangleGeometry()
  {
  }

  operator ID2D1RectangleGeometry*()
  {
    return getGeometry();
  }

  virtual ID2D1RectangleGeometry* getGeometry()
  {
    ID2D1RectangleGeometry* geometry = (ID2D1RectangleGeometry*)getIUnknown();
    if (geometry) {
      return geometry;
    } else {
      throw IException("ID2D1RectangleGeometry is NULL.");
    }
  }
  

  void getRect(
        __out D2D1_RECT_F *rect 
        )
  {
    ID2D1RectangleGeometry* geometry = getGeometry();
    geometry -> GetRect(
        rect 
        );
  }
};

}

