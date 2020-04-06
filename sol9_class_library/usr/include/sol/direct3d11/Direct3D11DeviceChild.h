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
 *  Direct3D11DeviceChild.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/com/ComIUnknown.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <dxgi.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")

namespace SOL {

class Direct3D11DeviceChild : public ComIUnknown {

public:
  Direct3D11DeviceChild()
  {
  }
  
  ~Direct3D11DeviceChild()
  { 
  }

  
  operator ID3D11DeviceChild*()
  {
    return getDeviceChild();
  }

  ID3D11DeviceChild* getDeviceChild()
  {
    ID3D11DeviceChild* device = (ID3D11DeviceChild*)getIUnknown();
    if (device) {
        return device;
    } else {
      throw IException("ID3D11DeviceChild is NULL.");
    }
  }
  
  void getDevice( 
            __out  ID3D11Device **ppDevice)
  {
    ID3D11DeviceChild* child = getDeviceChild();
    child -> GetDevice(ppDevice);  
  }
        
  void getPrivateData( 
            __in  REFGUID guid,
            __inout  UINT *pDataSize,
            __out void *pData)
  {
    ID3D11DeviceChild* child = getDeviceChild();
    HRESULT hr = child -> GetPrivateData( 
            guid,
            pDataSize,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetPrivateData. HRESULT(0x%lx)", hr);
    }
  }
          
  void setPrivateData( 
            __in  REFGUID guid,
            __in  UINT dataSize,
            __in  const void *pData)
  {
    ID3D11DeviceChild* child = getDeviceChild();
    HRESULT hr = child -> SetPrivateData( 
            guid,
            dataSize,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateData. HRESULT(0x%lx)", hr);
    }
  }
          
  void setPrivateDataInterface( 
            __in  REFGUID guid,
            __in_opt  const IUnknown *pData)
  {
    ID3D11DeviceChild* child = getDeviceChild();
    HRESULT hr = child -> SetPrivateDataInterface( 
            guid,
            pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateDataInterface. HRESULT(0x%lx)", hr);
    }
  }

};

}
    

    