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
 *  Direct2D1Factory3.h
 *
 *****************************************************************************/

#pragma once

#include <sol/directx/Direct2D1Factory2.h>
#include <d2d1_2.h>
#include <d2d1_3.h>

namespace SOL {
  
class Direct2D1Factory3: public Direct2D1Factory2  {

public:
  Direct2D1Factory3()
  :Direct2D1Factory2()
  {
    ID2D1Factory3* factory3 = NULL;
    //D2D1_DEVICE_CONTEXT_OPTIONS deviceOptions = D2D1_DEVICE_CONTEXT_OPTIONS_NONE;

    HRESULT hr = D2D1CreateFactory(
                D2D1_FACTORY_TYPE_SINGLE_THREADED, 
              __uuidof(ID2D1Factory3), 
             // &deviceOptions, 
              (void**)&factory3);
    
    if (SUCCEEDED(hr)) {
      set(factory3);
    } else {
      throw IException("Failed  to D2D1CreateFactory. HRESULT(0x%lx)", hr);
    } 
  }

  ~Direct2D1Factory3()
  {
  }

  operator ID2D1Factory3*()
  {
    return getFactory3();
  }

  
  ID2D1Factory3* getFactory3()
  {
    ID2D1Factory3* factory = (ID2D1Factory3*)getIUnknown();
    if (factory) {
      return factory;
    } else {
      throw IException("ID2D1Factory3 is NULL.");
    }
  }
  
/*
  void createDevice(
        _In_ IDXGIDevice*           dxgiDevice,
        _COM_Outptr_ ID2D1Device2** d2dDevice2)
  {
    ID2D1Factory3* factory3 = getFactory3();
    HRESULT hr = factory3 -> CreateDevice)(
              dxgiDevice,
              d2dDevice2);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDevice. HRESULT(0x%lx)", hr);
    }
  }
 */ 
};
  
}
