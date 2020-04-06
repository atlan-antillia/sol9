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
 *  Direct3D11On12WrappedResource.h
 *
 *****************************************************************************/

// 2016/11/26
#pragma once

#include <sol/direct3d12/Direct3D11On12Device.h>


namespace SOL {
  
class Direct3D11On12WrappedResource : public Direct3D12Object {
private:
  ID3D11On12Device*                d3d11On12Device;
  
public:
  Direct3D11On12WrappedResource(
            __in ID3D11On12Device*            device,
            __in ID3D12Resource*              resource12,
            __in  const D3D11_RESOURCE_FLAGS* flags11  = nullptr,
            D3D12_RESOURCE_STATES             inState  = D3D12_RESOURCE_STATE_RENDER_TARGET,
            D3D12_RESOURCE_STATES             outState = D3D12_RESOURCE_STATE_PRESENT )
  :Direct3D12Object(),
  d3d11On12Device(device)
  {
    if (d3d11On12Device == nullptr || resource12 == nullptr) {
      throw IException("Invalid parameter."); 
    }
    D3D11_RESOURCE_FLAGS flags = { D3D11_BIND_RENDER_TARGET };
    if (flags11 == nullptr) {
      flags11 = &flags;
    }
    ID3D11Resource* resource11 = NULL;
    HRESULT hr = d3d11On12Device -> CreateWrappedResource( 
                (IUnknown*)resource12,
                flags11,
                inState,
                outState,
                IID_ID3D11Resource,
                (void**)&resource11);
    if (FAILED(hr)) {
      throw IException("Failed to CreateWrappedResource. HRESULT(0x%lx)", hr);
    } else {
      set(resource11);
    }
  }

  operator ID3D11Resource*()
  {
    return getID3D11Resource();
  }
  
  ID3D11Resource* getID3D11Resource()
  {
    ID3D11Resource* resource = (ID3D11Resource*)getIUnknown();
    if (resource) {
      return resource;
    } else {
      throw IException("ID3D11Resource is NULL");
    }
  }
  
  void acquire()
  {
    
    ID3D11Resource* resources[] = {*this};
    d3d11On12Device->AcquireWrappedResources( 
            resources,
            _countof(resources));
  }

  void release()
  {
    ID3D11Resource *resources[] = {*this};
    d3d11On12Device->ReleaseWrappedResources( 
            (ID3D11Resource **)resources,
             _countof(resources));
  }
};

}
    
