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
 *  DirectXGIDevice.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIObject.h>
#include <d3d10_1.h>
#include <d3d11.h>
#ifdef WIN10
#include <d3d12.h>
#endif
namespace SOL {

class DirectXGIDevice : public DirectXGIObject {
public:
  DirectXGIDevice() 
  :DirectXGIObject()
  {

  }


  DirectXGIDevice(ID3D10Device* d3d10Device) 
  :DirectXGIObject()
  {
    IDXGIDevice* device = NULL;
    HRESULT hr = d3d10Device ->QueryInterface(__uuidof(IDXGIDevice), 
      (void **)&device);
    if (SUCCEEDED(hr)){
      set(device);
    } else {
      throw IException("Failed to QueryInterface. HRESULT(0x%lx)", hr);
    }
  }

  DirectXGIDevice(ID3D11Device* d3d11Device)
	  :DirectXGIObject()
  {
	  IDXGIDevice* device = NULL;
	  HRESULT hr = d3d11Device->QueryInterface(__uuidof(IDXGIDevice),
		  (void **)&device);
	  if (SUCCEEDED(hr)) {
		  set(device);
	  }
	  else {
		  throw IException("Failed to QueryInterface. HRESULT(0x%lx)", hr);
	  }
  }
#ifdef WIN10
  DirectXGIDevice(ID3D12Device* d3d12Device)
	  :DirectXGIObject()
  {
	  IDXGIDevice* device = NULL;
	  HRESULT hr = d3d12Device->QueryInterface(__uuidof(IDXGIDevice),
		  (void **)&device);
	  if (SUCCEEDED(hr)) {
		  set(device);
	  }
	  else {
		  throw IException("Failed to QueryInterface. HRESULT(0x%lx)", hr);
	  }
  }
#endif

  ~DirectXGIDevice() 
  {
  }  

  operator  IDXGIDevice*()
  {
    return getDevice();
  }

  IDXGIDevice* getDevice()
  {
    IDXGIDevice* device = (IDXGIDevice*)getIUnknown();
    if (device) {
      return device;
    } else {
      throw IException("IDXGIDevice is NULL.")
    }
  }

  void getAdapter( 
            __out  IDXGIAdapter **pAdapter)
  {
    IDXGIDevice* device = getDevice();
    HRESULT hr = device -> GetAdapter( 
            pAdapter);
    if (FAILED(hr)) {
      throw IException("Failed to GetAdapter. HRESULT(0x%lx)", hr);
    }
  }      

  void createSurface( 
            __in  const DXGI_SURFACE_DESC *pDesc,
            __in UINT numSurfaces,
            __in DXGI_USAGE usage,
            __in_opt  const DXGI_SHARED_RESOURCE *pSharedResource,
            __out  IDXGISurface **ppSurface)
  {
    IDXGIDevice* device = getDevice();
    IDXGISurface *surface = NULL;
    HRESULT hr = device -> CreateSurface( 
              pDesc,
              numSurfaces,
              usage,
            pSharedResource,
            &surface) ;
    if (FAILED(hr)) {
      throw IException("Failed to CreateSurface. HRESULT(0x%lx)", hr)
    }
  }

  void queryResourceResidency( 
            __in  IUnknown *const *ppResources,
            __out  DXGI_RESIDENCY *pResidencyStatus,
            __in UINT numResources)
  {
    IDXGIDevice* device = getDevice();
    HRESULT hr = device -> QueryResourceResidency( 
              ppResources,
              pResidencyStatus,
              numResources);
    if (FAILED(hr)) {
      throw IException("Failed to QueryResourceResidency. HRESULT(0x%lx)", hr);
    }
  }      
      
  void setGPUThreadPriority( 
            __in INT priority)
  {
    IDXGIDevice* device = getDevice();
    HRESULT hr = device -> SetGPUThreadPriority( 
            priority);
    if (FAILED(hr)) {
      throw IException("Failed to SetGPUThreadPriority. HRESULT(0x%lx)", hr);
    }
  }      
        
  void getGPUThreadPriority( 
            __out  INT *pPriority)
  {
    IDXGIDevice* device = getDevice();
    HRESULT hr = device -> GetGPUThreadPriority( 
            pPriority);
    if (FAILED(hr)) {
      throw IException("Failed to GetGPUThreadPriority. HRESULT(0x%lx)", hr);
    }
  }
};
}
