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
 *  Direct3D12DeviceChild.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Object.h>
#include <d3d12.h>

namespace SOL {

class Direct3D12DeviceChild : public Direct3D12Object {

public:
  Direct3D12DeviceChild(
    __in ID3D12DeviceChild* deviceChild=NULL)
  :Direct3D12Object(deviceChild)
  {
  }
  
  ~Direct3D12DeviceChild()
  { 
  }

   
  operator ID3D12DeviceChild*()
  {
    return getDeviceChild();
  }

  ID3D12DeviceChild* getDeviceChild()
  {
    ID3D12DeviceChild* deviceChild = (ID3D12DeviceChild*)getIUnknown();
    if (deviceChild) {
        return deviceChild;
    } else {
      throw IException("ID3D12DeviceChild is NULL.");
    }
  }

  void getDevice(REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice)
  {
    ID3D12DeviceChild* deviceChild = getDeviceChild();
    HRESULT hr = deviceChild->GetDevice(
            riid,
            ppvDevice);
          
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12DeviceChild::GetDevice. hr=%ld", hr);
    }
  }
};

}
    
