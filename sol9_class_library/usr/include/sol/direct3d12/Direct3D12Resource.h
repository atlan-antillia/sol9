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
 *  Direct3D12Resource.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Pageable.h>

namespace SOL {

class Direct3D12Resource : public Direct3D12Pageable {
    
public:
  Direct3D12Resource(
    __in ID3D12Pageable* resource=NULL)
  :Direct3D12Pageable(resource)
  {
  }
  
  ~Direct3D12Resource()
  { 
  }

  void createCommittedResource(__in ID3D12Device* device, 
              __in const D3D12_HEAP_PROPERTIES*  heapProp,
                   D3D12_HEAP_FLAGS              heapFlags,
              __in const D3D12_RESOURCE_DESC*    resDesc,
                   D3D12_RESOURCE_STATES         resState=D3D12_RESOURCE_STATE_GENERIC_READ,
              __in_opt  const D3D12_CLEAR_VALUE* clearValue = NULL)
  {
    ID3D12Resource* resource = NULL;
    HRESULT hr = device->CreateCommittedResource( 
        heapProp,
        heapFlags, //D3D12_HEAP_FLAG_NONE,
        resDesc,
        resState,
        nullptr,
        IID_PPV_ARGS(&resource));
       
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to CreateCommittedResource. HRESULT(0x%lx).", hr );
    }
  }
  
  operator ID3D12Resource*()
  {
    return getResource();
  }

  ID3D12Resource* getResource()
  {
    ID3D12Resource* resource = (ID3D12Resource*)getIUnknown();
    if (resource) {
        return resource;
    } else {
      throw IException("ID3D12Resource is NULL.");
    }
  }

  void map(UINT subresource,
            _In_opt_  const D3D12_RANGE *pReadRange,
            _Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData)
  {
    ID3D12Resource* resource = getResource();
    HRESULT hr = resource-> Map( 
            subresource,
            pReadRange,
            ppData);
    if (FAILED(hr)) {
      throw IException("Failed to Map.HRESULT(0x%lx)", hr);
    }
  }
  
  void unmap(UINT subresource,
            _In_opt_  const D3D12_RANGE *pWrittenRange)
  {
    ID3D12Resource* resource = getResource();
    resource->Unmap( 
            subresource,
            pWrittenRange);
  }
    
  D3D12_RESOURCE_DESC getDesc( )
  {
    ID3D12Resource* resource = getResource();
    return resource->GetDesc();
  }

  D3D12_GPU_VIRTUAL_ADDRESS getGPUVirtualAddress()
  {
    ID3D12Resource* resource = getResource();
    return resource-> GetGPUVirtualAddress();
  }
  
  void writeToSubresource( 
            UINT dstSubresource,
            _In_opt_  const D3D12_BOX *pDstBox,
            _In_  const void *pSrcData,
            UINT srcRowPitch,
            UINT srcDepthPitch)
  {
    ID3D12Resource* resource = getResource();
    HRESULT hr = resource-> WriteToSubresource( 
            dstSubresource,
            pDstBox,
            pSrcData,
            srcRowPitch,
            srcDepthPitch);
    if (FAILED(hr)) {
      throw IException("Failed to WriteToSubresource.HRESULT(0x%lx)", hr);
    }
  }
  
  void readFromSubresource( 
            _Out_  void *pDstData,
            UINT dstRowPitch,
            UINT dstDepthPitch,
            UINT srcSubresource,
            _In_opt_  const D3D12_BOX *pSrcBox)
  {
    ID3D12Resource* resource = getResource();
    HRESULT hr = resource -> ReadFromSubresource( 
            pDstData,
            dstRowPitch,
            dstDepthPitch,
            srcSubresource,
            pSrcBox);
    if (FAILED(hr)) {
      throw IException("Failed to ReadFromSubresource.HRESULT(0x%lx)", hr);
    }
  }
        
  void getHeapProperties( 
            _Out_opt_  D3D12_HEAP_PROPERTIES *pHeapProperties,
            _Out_opt_  D3D12_HEAP_FLAGS *pHeapFlags)
  {
    ID3D12Resource* resource = getResource();
    HRESULT hr = resource -> GetHeapProperties( 
            pHeapProperties,
            pHeapFlags);
    if (FAILED(hr)) {
      throw IException("Failed to ReadFromSubresource.HRESULT(0x%lx)", hr);
    }
  }
  
};

}
    
