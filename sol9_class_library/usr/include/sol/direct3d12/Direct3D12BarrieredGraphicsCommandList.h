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
 *  Direct3D12BarrieredGraphicsCommandList.h
 *
 *****************************************************************************/

// 2016/10/30

#pragma once

#include <sol/direct3d12/Direct3D12GraphicsCommandList.h>
#include <sol/direct3d12/D3D12ResourceBarrier.h>

namespace SOL {

class Direct3D12BarrieredGraphicsCommandList : public Direct3D12GraphicsCommandList {

private:
  ID3D12CommandAllocator* allocator;
  D3D12ResourceBarrier    barrier;
  
public:
  Direct3D12BarrieredGraphicsCommandList(
      __in ID3D12Device* device,
      __in ID3D12CommandAllocator* commandAllocator,
      __in ID3D12PipelineState*    pipelineState=nullptr,
      __in UINT nodeMask = 0,
      __in bool closeOnStartup=true)
  :Direct3D12GraphicsCommandList(
          device,
          commandAllocator,
          pipelineState,
          nodeMask,
          closeOnStartup),
  allocator(commandAllocator)
  
  {
  }
  
  
  ~Direct3D12BarrieredGraphicsCommandList()
  { 
  }

 
  void startRendering(__in ID3D12Resource* resource)
  {
    allocator->Reset();
    reset(allocator, nullptr);
    
    barrier.setResource(resource);
    barrier.startRendering();
    
    this->resourceBarrier(1, barrier);
  }
  
  void endRendering()
  {
   // barrier.setResource(resource);
    barrier.endRendering();
    this->resourceBarrier(1, barrier);
    close();
  }

};

}
    
