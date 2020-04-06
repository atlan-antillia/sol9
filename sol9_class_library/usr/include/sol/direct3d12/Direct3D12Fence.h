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
 *  Direct3D12Fence.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Pageable.h>

namespace SOL {

class Direct3D12Fence : public Direct3D12Pageable {
    
public:
  Direct3D12Fence(
        __in ID3D12Device* device,
        UINT64 initialValue = 0,
        D3D12_FENCE_FLAGS flags = D3D12_FENCE_FLAG_NONE)
  :Direct3D12Pageable()
  {
   if (device) {
      ID3D12Fence* fence = NULL;
      HRESULT hr = device -> CreateFence( 
            initialValue,
            flags,
            IID_PPV_ARGS(&fence));
      if (SUCCEEDED(hr)) {
        set(fence);
      } else {
        throw IException("Failed to ID3D12Device::CreateFence. HRESULT(0x%lx)", hr);
      }
   }
   else {
     throw IException("ID3D12Device is NULL.");
   }
  }
  
  Direct3D12Fence(__in ID3D12Fence* fence)
  :Direct3D12Pageable(fence)
  {
  }
  
  ~Direct3D12Fence()
  { 
  }
 
  operator ID3D12Fence*()
  {
    return getFence();
  }

  ID3D12Fence* getFence()
  {
    ID3D12Fence* fence = (ID3D12Fence*)getIUnknown();
    if (fence) {
        return fence;
    } else {
      throw IException("ID3D12Fence is NULL.");
    }
  }

  UINT64 getCompletedValue()
  {
    ID3D12Fence* fence = getFence();
    return fence->GetCompletedValue();
  }

  void setEventOnCompletion( 
            UINT64 value,
            HANDLE hEvent)
  {
    ID3D12Fence* fence = getFence();
    HRESULT hr = fence->SetEventOnCompletion( 
            value,
            hEvent);
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12Fence::SetEventOnCompletion. HRESULT(0x%lx)", hr);
    }
  }

  void signal( 
            UINT64 value)
  {
    ID3D12Fence* fence = getFence();
    HRESULT hr = fence->Signal( 
            value);
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12Fence::Signal. HRESULT(0x%lx)", hr);
    }
  }
};
}
