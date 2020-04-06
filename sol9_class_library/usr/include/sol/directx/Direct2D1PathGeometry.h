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
 *  Direct2D1PathGeometry.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Resource.h>
#include <sol/directx/Direct2D1Geometry.h>

namespace SOL {

class Direct2D1PathGeometry : public Direct2D1Geometry
{
public:
  Direct2D1PathGeometry(ID2D1Factory* factory)
  :Direct2D1Geometry()
  {
    ID2D1PathGeometry* geometry = NULL;
    HRESULT hr = factory -> CreatePathGeometry(
        &geometry 
    );
    if (SUCCEEDED(hr)) {
      set(geometry);
    } else {
      throw IException("Failed to CreatePathGeometry. HRESULT(0x%lx)", hr);
    }
  }
  
  
  ~Direct2D1PathGeometry()
  {
  }

  operator ID2D1PathGeometry*()
  {
    return getGeometry();
  }

  virtual ID2D1PathGeometry* getGeometry()
  {
    ID2D1PathGeometry* geometry = (ID2D1PathGeometry*)getIUnknown();
    if (geometry) {
      return geometry;
    } else {
      throw IException("ID2D1PathGeometry is NULL.");
    }
  }
    

  void open(
        __out ID2D1GeometrySink **geometrySink 
        )
  {
    ID2D1PathGeometry* geometry = getGeometry();
    HRESULT hr = geometry -> Open(
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Open. HRESULT(0x%lx)", hr);
    }
  }
    
    
  void stream(
        __in ID2D1GeometrySink *geometrySink 
        )
  {
    ID2D1PathGeometry* geometry = getGeometry();
    HRESULT hr = geometry -> Stream(
        geometrySink 
        );
    if (FAILED(hr)) {
      throw IException("Failed to Stream. HRESULT(0x%lx)", hr);
    }
  }
    
  void getSegmentCount(
        __out UINT32 *count 
        )
  {
    ID2D1PathGeometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetSegmentCount(
        count 
        );
    if (FAILED(hr)) {
      throw IException("Failed to GetSegmentCount. HRESULT(0x%lx)", hr);
    }
  }
    
  void getFigureCount(
        __out UINT32 *count 
        )
  {
    ID2D1PathGeometry* geometry = getGeometry();
    HRESULT hr = geometry -> GetFigureCount(
        count 
        );
    if (FAILED (hr)) {
      throw IException("Failed to GetFigureCount. HRESULT(0x%lx)", hr);
    }
  }
}; 

}


