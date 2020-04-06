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
 *  Direct3D12IntermediateResource.h
 *
 *****************************************************************************/

// 2016/10/01

// This Direct3D12IntermediateResource class is based on Uploading Texture Data Through Buffers
// (https://msdn.microsoft.com/en-us/library/windows/desktop/dn899215.aspx).

#pragma once

#include <dxgi.h>
#include <sol/direct3d12/Direct3D12Resource.h>
#include <sol/direct3d12/Direct3D12Synchronizer.h>
#include <sol/direct3d12/Direct3D12CommandAllocator.h>

#include <sol/direct3d12/Direct3D12GraphicsCommandList.h>
#include <sol/direct3d12/Direct3D12CommandQueue.h>
#include <sol/direct3d12/D3D12ResourceBarrier.h>
#include <sol/direct3d12/Direct3D12Synchronizer.h>
#include <sol/direct3d12/D3D12SubresourceData.h>

namespace SOL {

class Direct3D12IntermediateResource : public Direct3D12Resource {
private:  
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT  layout;
  
  ID3D12Resource*          destinationTexture;
  D3D12_RESOURCE_DESC      destinationDesc;
  
public:
  Direct3D12IntermediateResource(
        ID3D12Device*    device, 
        ID3D12Resource*  destTexture,
        D3D12SubresourceData& imageResource)
  :Direct3D12Resource(),
  destinationTexture(destTexture)
  {
    memset(&layout, 0, sizeof(layout));

    destinationDesc = destinationTexture->GetDesc();
    
    if (destinationDesc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D) {
      throw IException("Destionation ResourceDesc.Dimensioon is invalid."); 
    }    
    UINT64 requiredSize    = 0;
    UINT   numRows         = 0;
    UINT64 rowSizesInBytes = 0; 
    device->GetCopyableFootprints(&destinationDesc, 0, 1, 0, 
               &layout, &numRows, &rowSizesInBytes, &requiredSize);

    //1 Define a heapProperites 
    D3D12_HEAP_PROPERTIES heapProp;
      memset(&heapProp, 0, sizeof(heapProp));
      heapProp.Type                 = D3D12_HEAP_TYPE_UPLOAD;   //UPLOAD
      heapProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
      heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
      heapProp.CreationNodeMask     = 1;
      heapProp.VisibleNodeMask      = 1;
 
    //2 Define a resourceDesc.
    D3D12_RESOURCE_DESC resDesc;
      memset(&resDesc, 0, sizeof(resDesc));
      resDesc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;   //BUFFER
      resDesc.Alignment          = 0;
      resDesc.Width              = requiredSize;
      resDesc.Height             = 1;
      resDesc.DepthOrArraySize   = 1;
      resDesc.MipLevels          = 1;
      resDesc.Format             = DXGI_FORMAT_UNKNOWN; //
      resDesc.SampleDesc.Count   = 1;
      resDesc.SampleDesc.Quality = 0;
      resDesc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
      resDesc.Flags              = D3D12_RESOURCE_FLAG_NONE;

    //3 Create an intermediateResource.
    ID3D12Resource* intermediateResource = NULL;
    
    HRESULT hr = device->CreateCommittedResource(
                &heapProp,        
                D3D12_HEAP_FLAG_NONE,  
                &resDesc,  
                D3D12_RESOURCE_STATE_GENERIC_READ, 
                nullptr,      
               IID_PPV_ARGS(&intermediateResource) );
    
    if (SUCCEEDED(hr)) {
      set(intermediateResource);
      copyBitmapToBuffer(device, numRows, 
        imageResource, destinationDesc.Format);
    } else {
      throw IException("Failed to CreateCommittedResource. HRESULT(0x%lx)", hr);
    }
  }
    
  void copyBitmapToBuffer(
      ID3D12Device*         device,
      UINT                  numRows,
      D3D12SubresourceData& imageResource,
      DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM )
  { 
    try {
      D3D12_SUBRESOURCE_DATA srcData = *imageResource;
      
      UINT8* image = nullptr;
      map(0, nullptr, (void**)&image);
      
      D3D12_MEMCPY_DEST destData = {};
      destData.pData      = image + layout.Offset;
      destData.RowPitch   = layout.Footprint.RowPitch;
      destData.SlicePitch = layout.Footprint.RowPitch * numRows;
      
      UINT rowPitch       = srcData.RowPitch;
      
      UINT numSlices      = layout.Footprint.Depth;
      
      for (UINT z = 0; z < numSlices; z++) {
        uint8_t* destSlice = (uint8_t*)destData.pData + destData.SlicePitch * z;
        uint8_t* srcSlice  = (uint8_t*)srcData.pData  + srcData.SlicePitch  * z;
      
        for (UINT y = 0; y < numRows; y++)  {
          //The following lines can be replaced with memcpy.
          for (UINT x = 0; x < rowPitch; x++) {
            uint8_t* dest = destSlice + destData.RowPitch * y + x;
            uint8_t* src  = srcSlice  + srcData.RowPitch  * y + x;
            *dest = *src;
          }
        }
      }      
      
      unmap(0, nullptr);
    }
    catch (Exception& ex) {
      ex.display();
    }
  }

  void upload(
        ID3D12GraphicsCommandList* graphicsCommandList)
  {
    try {
      D3D12_TEXTURE_COPY_LOCATION to;
      memset(&to, 0, sizeof(to));
      to.pResource        = destinationTexture; 
      to.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
      to.SubresourceIndex = 0;

      D3D12_TEXTURE_COPY_LOCATION from;
      memset(&from, 0, sizeof(from));
      from.pResource       = getResource();  //intermediateResource
      from.Type            = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
      from.PlacedFootprint = layout;
        
      graphicsCommandList->CopyTextureRegion(  
            &to,  
            0, 
            0, 
            0,  
            &from,  
            nullptr);
    } catch (Exception& ex) {
      ex.display();
    }
  }

  void upload(ID3D12GraphicsCommandList* graphicsCommandList,
            ID3D12CommandAllocator*    commandAllocator,
            ID3D12CommandQueue*        commandQueue,
            Direct3D12Synchronizer*    synchronizer)
  {
    commandAllocator->Reset();
    graphicsCommandList->Reset(commandAllocator, nullptr);

    D3D12ResourceBarrier barrier(destinationTexture,  D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
    barrier.startCopyTransition();

    graphicsCommandList->ResourceBarrier(1, barrier);
             
    this->upload(graphicsCommandList);
 
    barrier.endCopyTransition();
    graphicsCommandList->ResourceBarrier(1, barrier);

    graphicsCommandList->Close();
    ID3D12CommandList* list[] = { graphicsCommandList };
    commandQueue->ExecuteCommandLists(1, list);

    synchronizer->waitForCompletion();
  }
};

}
