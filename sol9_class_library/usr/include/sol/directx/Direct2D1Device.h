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
 *  Direct2D1Device.h
 *
 *****************************************************************************/


#pragma once

#include <sol/directx/Direct2D1Resource.h>

namespace SOL {

class Direct2D1Device  : public Direct2D1Resource {
  
protected:
  Direct2D1Device()
  :Direct2D1Resource()
  {
  }
  
public:
  Direct2D1Device(
        __in IDXGIDevice *dxgiDevice,
        __in CONST D2D1_CREATION_PROPERTIES* creationProperties)
  :Direct2D1Resource()
  {
    ID2D1Device *d2d1Device = NULL;
    HRESULT hr = D2D1CreateDevice(
        dxgiDevice,
        creationProperties,
        &d2d1Device
        );
    if (SUCCEEDED(hr)) {
      set(d2d1Device); 
    } else {
      throw IException("Failed to D2D1CreateDevice. HRESULT(0x%lx)", hr);
    }
  }
  
  operator ID2D1Device*()
  {
    return getDevice();
  }
  
  ID2D1Device* getDevice()
  {
    ID2D1Device* device = (ID2D1Device*)getIUnknown();
    if (device) {
      return device;
    } else {
      throw IException("ID2D1Device is NULL.");
    }
  }
    
  void  createDeviceContext(
        D2D1_DEVICE_CONTEXT_OPTIONS options,
        __out ID2D1DeviceContext **deviceContext 
        )
  {
    ID2D1Device* device = getDevice();
    HRESULT hr = device -> CreateDeviceContext(
          options,
          deviceContext 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreateDeviceContext. HRESULT(0x%lx)", hr);
    }
  }
  
  void createPrintControl(
        __in IWICImagingFactory *wicFactory,
        __in IPrintDocumentPackageTarget *documentTarget,
        __in_opt CONST D2D1_PRINT_CONTROL_PROPERTIES *printControlProperties,
        __out ID2D1PrintControl **printControl 
        )
  {
    ID2D1Device* device = getDevice();
    HRESULT hr = device ->CreatePrintControl(
            wicFactory,
            documentTarget,
            printControlProperties,
          printControl 
        );
    if (FAILED(hr)) {
      throw IException("Failed to CreatePrintControl. HRESULT(0x%lx)", hr);
    }    
  }
  
  void setMaximumTextureMemory(
        UINT64 maximumInBytes 
        )
  {
    ID2D1Device* device = getDevice();
    device ->SetMaximumTextureMemory(
        maximumInBytes 
        );
  }
    
  UINT64 getMaximumTextureMemory()
  {
    ID2D1Device* device = getDevice();
    return device ->GetMaximumTextureMemory();
  }
  
  void clearResources(
        UINT32 millisecondsSinceUse = 0 
        )
  {
    ID2D1Device* device = getDevice();
    device -> ClearResources(
          millisecondsSinceUse 
        );   
  }
  
    
  void createPrintControl(
        __in IWICImagingFactory *wicFactory,
        __in IPrintDocumentPackageTarget *documentTarget,
        CONST D2D1_PRINT_CONTROL_PROPERTIES &printControlProperties,
        __out ID2D1PrintControl **printControl 
        )  
    {
    ID2D1Device* device = getDevice();
    HRESULT hr = device ->
        CreatePrintControl(wicFactory, documentTarget, &printControlProperties, printControl);
    }
};

}

