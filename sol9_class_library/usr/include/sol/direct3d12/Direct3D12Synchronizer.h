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
 *  Direct3D12Synchronizer.h
 *
 *****************************************************************************/

// 2016/10/10

#pragma once

#include <sol/direct3d12/Direct3D12Device.h>

#include <sol/direct3d12/Direct3D12CommandQueue.h>
#include <sol/direct3d12/Direct3D12Fence.h>

namespace SOL {

class Direct3D12Synchronizer {
private:
  ID3D12CommandQueue*  commandQueue;  //Shallow copy
  ID3D12Fence*         fence;         
  UINT64               fenceValue;
  HANDLE               fenceEvent;
  
public:
  Direct3D12Synchronizer(
       __in ID3D12Device*       device,
       __in ID3D12CommandQueue* queue)
  :commandQueue(queue),
  fence(NULL),
  fenceValue(1),
  fenceEvent(nullptr)
  {
    HRESULT hr = device -> CreateFence( 
            0,
             D3D12_FENCE_FLAG_NONE,
            IID_PPV_ARGS(&fence));
    if (FAILED(hr)) {
      throw IException("Failed to CreateFence. HRESULT(0x%lx)", hr);
    }
    fenceEvent =  CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);
    if (fenceEvent == nullptr) {
      throw IException("Failed to CreateEvent.");
    }
  }
  
  
  ~Direct3D12Synchronizer()
  {
    CloseHandle(fenceEvent);
    fence->Release();
  }
  
  void waitForCompletion()
  {
    UINT64 value = fenceValue++;
    HRESULT hr = commandQueue->Signal(fence,  value);
    if (FAILED(hr)) {
      throw IException("Failed to Signal. HRESULT(0x%lx)", hr);
    }
    
    if (fence ->GetCompletedValue() < value) {
      hr = fence->SetEventOnCompletion(value, fenceEvent);
      
      if (FAILED(hr)) {
        throw IException("Failed to SetEventOnCompletion. HRESULT(0x%lx)", hr);
      }
      WaitForSingleObject(fenceEvent, INFINITE);
    }
  } 
};
}


