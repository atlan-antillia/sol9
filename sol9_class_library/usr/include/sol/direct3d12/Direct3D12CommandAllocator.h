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
 *  Direct3D12CommandAllocator.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Pageable.h>

namespace SOL {

class Direct3D12CommandAllocator : public Direct3D12Pageable {
    
public:
  Direct3D12CommandAllocator(
    __in ID3D12Device* device,
    __in D3D12_COMMAND_LIST_TYPE type=D3D12_COMMAND_LIST_TYPE_DIRECT)
  :Direct3D12Pageable()
  {
    ID3D12CommandAllocator* commandAllocator = NULL;
    if (device) {
      HRESULT hr = device -> CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator));
      if (SUCCEEDED(hr)) {
        set(commandAllocator);
      } else {
        throw IException("Failed to ID3D12Device::CreateCommandAllocator. HRESULT(0x%lx)", hr);
      }
    } else {
      throw IException("ID3D12Device is NULL")
    }
  }

  Direct3D12CommandAllocator(
    __in ID3D12CommandAllocator* commandAllocator)
  :Direct3D12Pageable(commandAllocator)
  {
  }
  
  ~Direct3D12CommandAllocator()
  { 
  }

   
  operator ID3D12CommandAllocator*()
  {
    return getCommandAllocator();
  }

  ID3D12CommandAllocator* getCommandAllocator()
  {
    ID3D12CommandAllocator* commandAllocator = (ID3D12CommandAllocator*)getIUnknown();
    if (commandAllocator) {
        return commandAllocator;
    } else {
      throw IException("ID3D12CommandAllocator is NULL.");
    }
  }

  void reset()
  {
    ID3D12CommandAllocator* commandAllocator = getCommandAllocator();
    commandAllocator->Reset();
  }
};

}
    
