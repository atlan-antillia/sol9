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
 *  Direct3D12CommandList.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12DeviceChild.h>

namespace SOL {

class Direct3D12CommandList : public Direct3D12DeviceChild {
    
public:
  Direct3D12CommandList()
  :Direct3D12DeviceChild()
  {
  }
  
  Direct3D12CommandList(
            __in ID3D12Device* device,
            __in  UINT nodeMask,
            __in  D3D12_COMMAND_LIST_TYPE type,
            __in  ID3D12CommandAllocator *pCommandAllocator,
            __in  ID3D12PipelineState *pInitialState)
  :Direct3D12DeviceChild()
  {
    if (device) {
      ID3D12CommandList* commandList = NULL;
      HRESULT hr = device -> CreateCommandList( 
            nodeMask,
            type,
            pCommandAllocator,
            pInitialState,
            IID_PPV_ARGS(&commandList));
      if (SUCCEEDED(hr)) {
        set(commandList);
      } else {
        throw IException("Failed to ID3D12Device::CreateCommandList. HRESULT(0x%lx)", hr);
      }
    } else {
      throw IException("ID3D12Device is NULL.");
    }
  }
  
  Direct3D12CommandList(
    __in ID3D12CommandList* commandList)
  :Direct3D12DeviceChild(commandList)
  {
  }
  
  ~Direct3D12CommandList()
  { 
  }

   
  operator ID3D12CommandList*()
  {
    return getCommandList();
  }

  ID3D12CommandList* getCommandList()
  {
    ID3D12CommandList* commandList = (ID3D12CommandList*)getIUnknown();
    if (commandList) {
        return commandList;
    } else {
      throw IException("ID3D12CommandList is NULL.");
    }
  }


  D3D12_COMMAND_LIST_TYPE getType()
  {
    ID3D12CommandList* commandList = getCommandList();
    return commandList->GetType();
  
  }
  
};

}
    
