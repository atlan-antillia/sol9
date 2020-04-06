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
 *  Direct3D12Device1.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Device.h>

namespace SOL {

class Direct3D12Device1 : public Direct3D12Device {
    
public:
  Direct3D12Device1(_In_opt_ IUnknown* pAdapter,
    D3D_FEATURE_LEVEL minimumFeatureLevel)
  :Direct3D12Device()
  {
    ID3D12Device1* device1 = NULL;
    HRESULT hr = D3D12CreateDevice(
        pAdapter,
        minimumFeatureLevel,
        IID_ID3D12Device1,
        &device1 );
    if (FAILED(hr)) {
      throw IException("Failed to D3D12CreateDevice. HRESULT(0x%lx)", hr);
    } else {
      set(device1);
    }
  }
  
  ~Direct3D12Device1()
  { 
  }

   
  operator ID3D12Device1*()
  {
    return getDevice1();
  }

  ID3D12Devic1e* getDevice1()
  {
    ID3D12Device1* device = (ID3D12Device1*)getIUnknown();
    if (device) {
        return device;
    } else {
      throw IException("ID3D12Device1 is NULL.");
    }
  }

  void createPipelineLibrary( 
            _In_reads_(blobLength)  const void *pLibraryBlob,
            SIZE_T blobLength,
            REFIID riid,
            _COM_Outptr_  void **ppPipelineLibrary)
  {
    ID3D12Device1* device1 = getDevice1();
    HRESULT hr = device1 ->CreatePipelineLibrary( 
            pLibraryBlob,
            blobLength,
            riid,
            ppPipelineLibrary);
    if (FAILED(hr)) {
      throw IException("Failed to CreatePipelineLibrary. HRESULT(0x%lx)", hr);
    }
  }
        
  void setEventOnMultipleFenceCompletion( 
            _In_reads_(numFences)  ID3D12Fence *const *ppFences,
            _In_reads_(numFences)  const UINT64 *pFenceValues,
            UINT numFences,
            D3D12_MULTIPLE_FENCE_WAIT_FLAGS flags,
            HANDLE hEvent)
  {
    ID3D12Device1* device1 = getDevice1();
      HRESULT hr = device1 -> SetEventOnMultipleFenceCompletion( 
            ppFences,
            pFenceValues,
            numFences,
            flags,
            hEvent);
    if (FAILED(hr)) {
      throw IException("Failed to SetEventOnMultipleFenceCompletion. HRESULT(0x%lx)", hr);
    }
  }
        
  void setResidencyPriority( 
            UINT numObjects,
            _In_reads_(numObjects)  ID3D12Pageable *const *ppObjects,
            _In_reads_(numObjects)  const D3D12_RESIDENCY_PRIORITY *pPriorities)
  {
    ID3D12Device1* device1 = getDevice1();
    HRESULT hr = SetResidencyPriority( 
            numObjects,
            ppObjects,
            pPriorities);
    if (FAILED(hr)) {
      throw IException("Failed to SetResidencyPriority. HRESULT(0x%lx)", hr);
    }
  }

};

}
    
