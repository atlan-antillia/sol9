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
 *  Direct3D11On12Device.h
 *
 *****************************************************************************/

// 2016/09/25
// 2016/11/25 Updated construcotors to use QueryInterface to get ID3D11On12Device interface.

#pragma once

#include <d3d12.h>
#include <d3d11on12.h>

#include <sol/direct3d12/Direct3D12Object.h>

#pragma comment(lib, "d3d11.lib")

namespace SOL {
/*
  HRESULT WINAPI D3D11On12CreateDevice(
    _In_ IUnknown* pDevice,
    UINT Flags,
    _In_reads_opt_( FeatureLevels ) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    _In_reads_opt_( NumQueues ) IUnknown* CONST* ppCommandQueues,
    UINT NumQueues,
    UINT NodeMask,
    _COM_Outptr_opt_ ID3D11Device** ppDevice,
    _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext,
    _Out_opt_ D3D_FEATURE_LEVEL* pChosenFeatureLevel );
  */
  
class Direct3D11On12Device : public Direct3D12Object {
private:
  ID3D11DeviceContext* d3d11ImmediateContext;
  
public:
  //  
  Direct3D11On12Device(
    __in const ID3D12Device*        d3d12Device,
    __in const ID3D12CommandQueue*  commandQueue,       //Single commandQueue.

    __in UINT                       d3d11DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT,
    
    __in CONST D3D_FEATURE_LEVEL*   pFeatureLevels = nullptr,
    UINT                            featureLevels = 0,
    UINT                            nodeMask  = 0)
 
  :Direct3D12Object(),
  d3d11ImmediateContext(NULL)
  {
	  ID3D11Device*        d3d11Device = NULL;

    const ID3D12CommandQueue*  commandQueues[] = {commandQueue};

    HRESULT hr = D3D11On12CreateDevice(
      (IUnknown*)d3d12Device,
		    d3d11DeviceFlags,
		    pFeatureLevels,
		    featureLevels,
      (IUnknown**)commandQueues,
       _countof(commandQueues),
		    nodeMask,
		    &d3d11Device,
		    &d3d11ImmediateContext,
		    nullptr
		  );
		
    if (SUCCEEDED(hr)) {
	    ID3D11On12Device* d3d11On12Device = NULL;

      d3d11Device->QueryInterface(IID_ID3D11On12Device, (void**)&d3d11On12Device);
    
      d3d11Device->Release();
      
      set(d3d11On12Device);
    } else {
      d3d11Device->Release();
      throw IException("Failed to D3D11On12CreateDevice. hr=%lf", hr);
    }
  }
  

  Direct3D11On12Device(
    __in const ID3D12Device*         d3d12Device,
    __in const ID3D12CommandQueue**  commandQueues, //Array of commandQueues
    UINT                             numQueues,
    __in UINT                        d3d11DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT,
    
    __in CONST D3D_FEATURE_LEVEL*    pFeatureLevels = nullptr,
    UINT                             featureLevels = 0,
    UINT                             nodeMask  = 0)
 
  :Direct3D12Object(),
  d3d11ImmediateContext(NULL)
  {
	  ID3D11Device*        d3d11Device = NULL;
    
    HRESULT hr = D3D11On12CreateDevice(
        (IUnknown*)d3d12Device,
		    d3d11DeviceFlags,
		    pFeatureLevels,
		    featureLevels,
        (IUnknown**)commandQueues,
		    numQueues,
		    nodeMask,
		    &d3d11Device,
		    &d3d11ImmediateContext,
		    nullptr);
    
    if (SUCCEEDED(hr)) {
	    ID3D11On12Device* d3d11On12Device = NULL;

      d3d11Device->QueryInterface(IID_ID3D11On12Device, (void**)&d3d11On12Device);
    
      d3d11Device->Release();
      
      set(d3d11On12Device);
    } else {
      d3d11Device->Release();
      throw IException("Failed to D3D11On12CreateDevice. hr=%lf", hr);
    }
  }
  
  Direct3D11On12Device(
    __in ID3D11On12Device*       d3d11On12Device,
    __in ID3D11DeviceContext*    immediateContext)
  
  :Direct3D12Object(),
  d3d11ImmediateContext(NULL)
  {
    set(d3d11On12Device);
    d3d11ImmediateContext = immediateContext;
  }
  
  ~Direct3D11On12Device()
  { 
    if (d3d11ImmediateContext) {
      d3d11ImmediateContext->Release();
    }
  }

   
  operator ID3D11On12Device*()
  {
    return getD3D11On12Device();
  }

  ID3D11On12Device* getD3D11On12Device()
  {
    ID3D11On12Device* device = (ID3D11On12Device*)getIUnknown();
    if (device) {
        return device;
    } else {
      throw IException("ID3D11On12Device is NULL.");
    }
  }

  ID3D11DeviceContext* getImmediateContext()
  {
    return d3d11ImmediateContext;
  }
  

  void createWrappedResource( 
            _In_ ID3D12Resource* pResource12,
            _In_  const D3D11_RESOURCE_FLAGS *pFlags11,
            D3D12_RESOURCE_STATES inState,
            D3D12_RESOURCE_STATES outState,
            REFIID riid,
            _COM_Outptr_opt_  ID3D11Resource** ppResource11)
  {
    ID3D11On12Device* device = getD3D11On12Device();
    HRESULT hr = device->CreateWrappedResource( 
            (IUnknown*)pResource12,
            pFlags11,
            inState,
            outState,
            riid,
            (void**)ppResource11);
    if (FAILED(hr)) {
      throw IException("Failed to CreateWrappedResource. HRESULT(0x%lx)", hr);
    }
  }
  
  void releaseWrappedResource( 
            __in ID3D11Resource *resource)
          
  {
    ID3D11Resource *resources[] = {resource};
    ID3D11On12Device* device = getD3D11On12Device();
    device->ReleaseWrappedResources( 
            (ID3D11Resource **)resources,
      _countof(resources));
  }
  
  void releaseWrappedResources( 
            _In_reads_( numResources )  ID3D11Resource *const *ppResources,
            UINT numResources)
  {
    ID3D11On12Device* device = getD3D11On12Device();
    device->ReleaseWrappedResources( 
            ppResources,
            numResources);
  }

  void acquireWrappedResource( 
            __in  ID3D11Resource* resource)
  {
    ID3D11Resource* resources[] = {resource};
    ID3D11On12Device* device = getD3D11On12Device();
    device->AcquireWrappedResources( 
            resources,
            _countof(resources));
  }

  void acquireWrappedResources( 
            _In_reads_( numResources )  ID3D11Resource *const *ppResources,
            UINT numResources)
  {
    ID3D11On12Device* device = getD3D11On12Device();
    device->AcquireWrappedResources( 
            ppResources,
            numResources);
  }
  
  void flush()
  {    
    if (d3d11ImmediateContext) {
      d3d11ImmediateContext->Flush();
    }
  }
};

}
    
