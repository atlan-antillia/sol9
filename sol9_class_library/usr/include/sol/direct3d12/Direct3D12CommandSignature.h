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
 *  Direct3D12CommandSignature.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12DeviceChild.h>

namespace SOL {

class Direct3D12CommandSignature : public Direct3D12Pageable {
    
public:
  
  Direct3D12CommandSignature(
      __in ID3D12Device*                       device,
      __in const D3D12_COMMAND_SIGNATURE_DESC* pDesc,
      __in_opt ID3D12RootSignature*           pRootSignature)
  :Direct3D12DeviceChild()
  {
    if (device == nullptr || pDesc == nullptr) {
      throw IException("Invalid parameters.");  
    }
    
    ID3D12CommandSignature* commandSignature = NULL;
    HRESULT hr = device->CreateCommandSignature(
                      pDesc,
                      pRootSignature,
      IID_PPV_ARGS(&commandSignature));
    
    if (SUCCEEDED(hr)) {
      set(commandSignature);
    } else {
      throw IException("Failed to CreateCommandSignature. HRESULT(0x%lx)", hr);
    }
  }

  Direct3D12CommandSignature(ID3D12CommandSignature* commandSignature)
  :Direct3D12DeviceChild(commandSignature)
  {
  }
  
  ~Direct3D12CommandSignature()
  { 
  }

  operator ID3D12CommandSignature*()
  {
    return getCommandSignature();
  }

  ID3D12CommandSignature* getCommandSignature()
  {
    ID3D12CommandSignature* commandSignature = (ID3D12CommandSignature*)getIUnknown();
    if (commandSignature) {
        return commandSignature;
    } else {
      throw IException("ID3D12CommandSignature is NULL.");
    }
  }
};

}
    
