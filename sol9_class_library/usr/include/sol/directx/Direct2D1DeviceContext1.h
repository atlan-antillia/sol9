/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Direct2D1DeviceContext1.h
 *
 *****************************************************************************/


#pragma once


#include <sol/directx/Direct2D1DeviceContext.h>


namespace SOL {

class Direct2D1DeviceContext1 : public Direct2D1DeviceContext {
protected:
  Direct2D1DeviceContext1()
  :Direct2D1DeviceContext()
  {
  }
  
public:
  Direct2D1DeviceContext1(
          __in IDXGISurface             *dxgiSurface,
          __in const D2D1_CREATION_PROPERTIES *creationProperties)
  :Direct2D1DeviceContext()
  {
    ID2D1DeviceContext1*  deviceContext1 = NULL;
    HRESULT hr = ::D2D1CreateDeviceContext(
                  dxgiSurface,
                  creationProperties,
                  (ID2D1DeviceContext**)&deviceContext1);
    if (SUCCEEDED(hr)) {
      set(deviceContext1);
    } else {
      throw IException("Failed to D2D1CreateDeviceContext. HRESULT(0x%lx)", hr);
    }
  }
  
  operator ID2D1DeviceContext1*()
  {
    return getDeviceContext1();
  }
  
  ID2D1DeviceContext1* getDeviceContext1()
  {
    ID2D1DeviceContext1* deviceContext1 = (ID2D1DeviceContext1*)getIUnknown();
    if (deviceContext1) {
      return deviceContext1;
    } else {
      throw IException("ID2D1DeviceContext1 is NULL.");
    }
  }
    
  void createFilledGeometryRealization(
        __in ID2D1Geometry *geometry,
        FLOAT flatteningTolerance,
        __out ID2D1GeometryRealization **geometryRealization 
        )
  {
     ID2D1DeviceContext1* deviceContext1 = getDeviceContext1();
     deviceContext1-> CreateFilledGeometryRealization(
            geometry,
            flatteningTolerance,
            geometryRealization 
        );     
  }
  
    
  void createStrokedGeometryRealization(
        __in ID2D1Geometry *geometry,
        FLOAT flatteningTolerance,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __out ID2D1GeometryRealization **geometryRealization 
        )
  {
     ID2D1DeviceContext1* deviceContext1 = getDeviceContext1();
     deviceContext1-> CreateStrokedGeometryRealization(
            geometry,
            flatteningTolerance,
            strokeWidth,
            strokeStyle,
            geometryRealization 
        );     
  }
  
    
  void drawGeometryRealization(
        __in ID2D1GeometryRealization *geometryRealization,
        __in ID2D1Brush *brush 
        ) 
  {
     ID2D1DeviceContext1* deviceContext1 = getDeviceContext1();
     deviceContext1-> DrawGeometryRealization(
          geometryRealization,
          brush 
        ); 
  }
};
}
        
        