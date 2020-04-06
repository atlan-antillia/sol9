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
 *  Direct2D1EllipseGeometry.h
 *
 *****************************************************************************/

#pragma once


#include <sol/directx/Direct2D1Factory.h>
#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Geometry.h>


namespace SOL {

class Direct2D1EllipseGeometry : public Direct2D1Geometry
{
public:
  Direct2D1EllipseGeometry(ID2D1Factory* factory, __in CONST D2D1_ELLIPSE *ellipse)
  :Direct2D1Geometry()
  {
    ID2D1EllipseGeometry* geometry = NULL;
    HRESULT hr = factory -> CreateEllipseGeometry(
        ellipse,
        &geometry 
        );
    if (SUCCEEDED(hr)) {
      set(geometry);
    } else {
      throw IException("Failed to CreateEllipseGeometry. HRESULT(0x%lx)", hr);
    }
  }

  Direct2D1EllipseGeometry(ID2D1Factory* factory, __in CONST D2D1_ELLIPSE& ellipse)
  :Direct2D1Geometry()
  {
    ID2D1EllipseGeometry* geometry = NULL;
    HRESULT hr = factory -> CreateEllipseGeometry(
        ellipse,
        &geometry 
        );
    if (SUCCEEDED(hr)) {
      set(geometry);
    } else  {
      throw IException("Failed to CreateEllipseGeometry.HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct2D1EllipseGeometry()
  {
  }

  operator ID2D1EllipseGeometry*()
  {
    return getGeometry();
  }
  
  ID2D1EllipseGeometry* getGeometry()
  {
    ID2D1EllipseGeometry* geometry = (ID2D1EllipseGeometry*)getIUnknown();
    if (geometry) {
      return geometry;
    } else {
      throw IException("ID2D1EllipseGeometry is NULL.")
    }
  }


  void getEllipse(
        __out D2D1_ELLIPSE *ellipse 
        )
  {
    ID2D1EllipseGeometry* geometry = getGeometry();
    geometry -> GetEllipse(
        ellipse 
        );
  }
};
}

