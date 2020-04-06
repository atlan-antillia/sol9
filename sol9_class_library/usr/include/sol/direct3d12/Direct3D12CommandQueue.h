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
 *  Direct3D12CommandQueue.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Pageable.h>

namespace SOL {

class Direct3D12CommandQueue : public Direct3D12Pageable {
    
public:
  Direct3D12CommandQueue(
            __in ID3D12Device*             device,
            __in D3D12_COMMAND_LIST_TYPE   type = D3D12_COMMAND_LIST_TYPE_DIRECT,
            __in D3D12_COMMAND_QUEUE_FLAGS flags = D3D12_COMMAND_QUEUE_FLAG_NONE)
  :Direct3D12Pageable()
  {
    if (device == nullptr) {
      throw IException("Invalid parameter. device is NULL.");
    }
    
    ID3D12CommandQueue* commandQueue = NULL;
    D3D12_COMMAND_QUEUE_DESC desc;
      ZeroMemory(&desc, sizeof(desc) );
      desc.Type  = type; //D3D12_COMMAND_LIST_TYPE_DIRECT;
	    desc.Flags = flags; //D3D12_COMMAND_QUEUE_FLAG_NONE;
 
    HRESULT hr = device->CreateCommandQueue(
        &desc,
        IID_PPV_ARGS(&commandQueue));

    if (SUCCEEDED(hr)) {
      set(commandQueue);
    } else {
      throw IException("Failed to ID3D12Device::CreateCommandQueue. HRESULT(0x%lx)", hr);
    }
  }

  Direct3D12CommandQueue(
         __in ID3D12Device* device, 
         __in D3D12_COMMAND_QUEUE_DESC* desc)
    :Direct3D12Pageable()
  {
    ID3D12CommandQueue* commandQueue = NULL;
    if (device) {

      HRESULT hr = device->CreateCommandQueue(
          desc,
          __uuidof(ID3D12CommandQueue),
        (void**)&commandQueue);
      if (SUCCEEDED(hr)) {
        set(commandQueue);
      }
      else {
        throw IException("Failed to ID3D12Device::CreateCommandQueue. HRESULT(0x%lx)", hr);
      }
    }
    else {
      throw IException("Invalid parameter. device is NULL.");
    }
  }

  ~Direct3D12CommandQueue()
  { 
  }

   
  operator ID3D12CommandQueue*()
  {
    return getCommandQueue();
  }

  ID3D12CommandQueue* getCommandQueue()
  {
    ID3D12CommandQueue* commandQueue = (ID3D12CommandQueue*)getIUnknown();
    if (commandQueue) {
        return commandQueue;
    } else {
      throw IException("ID3D12CommandQueue is NULL.");
    }
  }
  void updateTileMappings( 
            _In_  ID3D12Resource *pResource,
            UINT numResourceRegions,
            _In_reads_opt_(numResourceRegions)  const D3D12_TILED_RESOURCE_COORDINATE *pResourceRegionStartCoordinates,
            _In_reads_opt_(numResourceRegions)  const D3D12_TILE_REGION_SIZE *pResourceRegionSizes,
            _In_opt_  ID3D12Heap *pHeap,
            UINT numRanges,
            _In_reads_opt_(numRanges)  const D3D12_TILE_RANGE_FLAGS *pRangeFlags,
            _In_reads_opt_(numRanges)  const UINT *pHeapRangeStartOffsets,
            _In_reads_opt_(numRanges)  const UINT *pRangeTileCounts,
            D3D12_TILE_MAPPING_FLAGS flags)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    commandQueue -> UpdateTileMappings( 
            pResource,
            numResourceRegions,
            pResourceRegionStartCoordinates,
            pResourceRegionSizes,
            pHeap,
            numRanges,
            pRangeFlags,
            pHeapRangeStartOffsets,
            pRangeTileCounts,
            flags);
  }
         
  void copyTileMappings( 
            _In_  ID3D12Resource *pDstResource,
            _In_  const D3D12_TILED_RESOURCE_COORDINATE *pDstRegionStartCoordinate,
            _In_  ID3D12Resource *pSrcResource,
            _In_  const D3D12_TILED_RESOURCE_COORDINATE *pSrcRegionStartCoordinate,
            _In_  const D3D12_TILE_REGION_SIZE *pRegionSize,
            D3D12_TILE_MAPPING_FLAGS flags)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    commandQueue -> CopyTileMappings( 
            pDstResource,
            pDstRegionStartCoordinate,
            pSrcResource,
            pSrcRegionStartCoordinate,
            pRegionSize,
            flags);
  }
     
  void executeCommandList(ID3D12CommandList* commandList)
  {
    ID3D12CommandList* lists[] = {commandList};      
    executeCommandLists(_countof(lists), lists);  
  }
  
  void executeCommandLists( 
            _In_  UINT numCommandLists,
            _In_reads_(numCommandLists)  ID3D12CommandList *const *ppCommandLists)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    commandQueue -> ExecuteCommandLists( 
            numCommandLists,
            ppCommandLists);
  }
        
  void setMarker( 
            UINT metadata,
            _In_reads_bytes_opt_(size)  const void *pData,
            UINT size)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    commandQueue -> SetMarker( 
            metadata,
            pData,
            size);
  }
        
  void beginEvent( 
            UINT metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT size)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    commandQueue -> BeginEvent( 
            metadata,
            pData,
            size);
  }
        
  void endEvent()
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    commandQueue -> EndEvent();
  }
        
  void signal( 
            ID3D12Fence *pFence,
            UINT64 value)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    HRESULT hr = commandQueue -> Signal( 
            pFence,
            value);
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12CommandQueue::Signal. HRESULT(0x%lx)", hr);
    }
  }
        
  void wait( 
            ID3D12Fence *pFence,
            UINT64 value)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    HRESULT hr = commandQueue -> Wait( 
            pFence,
            value);
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12CommandQueue::Wait. HRESULT(0x%lx)", hr);
    }
  }
        
  void getTimestampFrequency( 
            _Out_  UINT64 *pFrequency)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    HRESULT hr = commandQueue -> GetTimestampFrequency( 
            pFrequency);
    if (FAILED(hr)) {
      throw IException("Failed to ID3D12CommandQueue::GetTimestampFrequency. HRESULT(0x%lx)", hr);
    }
  }
        
  void getClockCalibration( 
            _Out_  UINT64 *pGpuTimestamp,
            _Out_  UINT64 *pCpuTimestamp)
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
		HRESULT hr = commandQueue-> GetClockCalibration(
			pGpuTimestamp,
			pCpuTimestamp);
		if (FAILED(hr)) {
			throw IException("Failed to ID3D12CommandQueue::GetClockCalibration. HRESULT(0x%lx)", hr)
	  }
  }
        
  D3D12_COMMAND_QUEUE_DESC getDesc()
  {
    ID3D12CommandQueue* commandQueue = getCommandQueue();
    return commandQueue -> GetDesc();
  }

};

}
    
