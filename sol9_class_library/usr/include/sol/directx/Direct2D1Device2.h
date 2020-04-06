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
 *  Direct2D1Device2.h
 *
 *****************************************************************************/

//2016/11/25 Added the following constructor.
//  Direct2D1Device2(
//        __in ID2D1Factory3* factory,
//        __in IDXGIDevice1*  dxgiDevice)
        
#pragma once


#include <sol/directx/Direct2D1Device1.h>


namespace SOL {

class Direct2D1Device2  : public Direct2D1Device1 {
public:
  //2016/11/25 Added the following constructor.
  Direct2D1Device2(
        __in ID2D1Factory3* factory,
        __in IDXGIDevice1*  dxgiDevice)
  :Direct2D1Device1()
  {
    ID2D1Device2 *d2d1Device2 = NULL;
    HRESULT hr = factory->CreateDevice(
            dxgiDevice,
            
      (ID2D1Device**)&d2d1Device2);
    if (SUCCEEDED(hr)) {
      set(d2d1Device2);
    } else {
      throw IException("Failed to D2D1CreateDevice. HRESULT(0x%lx)", hr);
    }    
  }
  
public:
  Direct2D1Device2(
        __in IDXGIDevice *dxgiDevice,
        __in CONST D2D1_CREATION_PROPERTIES* creationProperties)
  :Direct2D1Device1()
  {
    ID2D1Device2 *d2d1Device2 = NULL;
    HRESULT hr = ::D2D1CreateDevice(
            dxgiDevice,
            creationProperties,
      (ID2D1Device**)&d2d1Device2);
    if (SUCCEEDED(hr)) {
      set(d2d1Device2);
    } else {
      throw IException("Failed to D2D1CreateDevice. HRESULT(0x%lx)", hr);
    }    
  }

  operator ID2D1Device2*()
  {
    return getDevice2();
  }
  ID2D1Device2* getDevice2()
  {
    ID2D1Device2* d2d1Device2 = (ID2D1Device2*)getIUnknown();
    if (d2d1Device2) {
      return d2d1Device2;
    }
    else {
      throw IException("ID2D1Device2 is NULL.")
    }
  }

/*  
//    using ID2D1Device1::CreateDeviceContext;  
//    using ID2D1Device::CreateDeviceContext;
 */   

  void flushDeviceContexts(
        _In_ ID2D1Bitmap *bitmap 
        )
  {
    ID2D1Device2 *device2 = getDevice2();
    device2 -> FlushDeviceContexts(
          bitmap 
        );
  }
  
  void getDxgiDevice(
        __out IDXGIDevice **dxgiDevice 
        )
  {
    ID2D1Device2 *device2 = getDevice2();

    HRESULT hr = device2->GetDxgiDevice(
            dxgiDevice 
        );
  }
}; 
}
