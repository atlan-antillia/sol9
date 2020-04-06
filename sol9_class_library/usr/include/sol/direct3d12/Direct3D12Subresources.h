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

// 2016/11/10

#pragma once

//UpdateSubresources API used here is based on Microsoft d3dx12.h

//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************


#include <sol/direct3d12/Direct3D12Object.h>
#include <sol/direct3d12/Direct3D12Resource.h>

#include <sol/direct3d12/Direct3D12Synchronizer.h>

//The following lines have been taken from #include <d3dx12.h>
//------------------------------------------------------------------------------------------------
struct CD3DX12_BOX : public D3D12_BOX
{
    CD3DX12_BOX()
    {}
    explicit CD3DX12_BOX( const D3D12_BOX& o ) :
        D3D12_BOX( o )
    {}
    explicit CD3DX12_BOX(
        LONG Left,
        LONG Right )
    {
        left = Left;
        top = 0;
        front = 0;
        right = Right;
        bottom = 1;
        back = 1;
    }
    explicit CD3DX12_BOX(
        LONG Left,
        LONG Top,
        LONG Right,
        LONG Bottom )
    {
        left = Left;
        top = Top;
        front = 0;
        right = Right;
        bottom = Bottom;
        back = 1;
    }
    explicit CD3DX12_BOX(
        LONG Left,
        LONG Top,
        LONG Front,
        LONG Right,
        LONG Bottom,
        LONG Back )
    {
        left = Left;
        top = Top;
        front = Front;
        right = Right;
        bottom = Bottom;
        back = Back;
    }
    ~CD3DX12_BOX() {}
    operator const D3D12_BOX&() const { return *this; }
};
inline bool operator==( const D3D12_BOX& l, const D3D12_BOX& r )
{
    return l.left == r.left && l.top == r.top && l.front == r.front &&
        l.right == r.right && l.bottom == r.bottom && l.back == r.back;
}
inline bool operator!=( const D3D12_BOX& l, const D3D12_BOX& r )
{ return !( l == r ); }

//------------------------------------------------------------------------------------------------
struct CD3DX12_TEXTURE_COPY_LOCATION : public D3D12_TEXTURE_COPY_LOCATION
{ 
    CD3DX12_TEXTURE_COPY_LOCATION()
    {}
    explicit CD3DX12_TEXTURE_COPY_LOCATION(const D3D12_TEXTURE_COPY_LOCATION &o) :
        D3D12_TEXTURE_COPY_LOCATION(o)
    {}
    CD3DX12_TEXTURE_COPY_LOCATION(ID3D12Resource* pRes) { pResource = pRes; }
    CD3DX12_TEXTURE_COPY_LOCATION(ID3D12Resource* pRes, D3D12_PLACED_SUBRESOURCE_FOOTPRINT const& Footprint)
    {
        pResource = pRes;
        Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        PlacedFootprint = Footprint;
    }
    CD3DX12_TEXTURE_COPY_LOCATION(ID3D12Resource* pRes, UINT Sub)
    {
        pResource = pRes;
        Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        SubresourceIndex = Sub;
    }
}; 

//

namespace SOL {
  
//Intermediate upload resource, which will be create in this class.
  
class Direct3D12Subresources :public Direct3D12Resource {

private:
  ID3D12Resource* destinationResource; //Shallow copy for texture2DResource.

public:
  //
  // Constructor
  //
  Direct3D12Subresources(
      __in ID3D12Device* device,
      __in ID3D12Resource* resource) //Destination texture2D resource.
  :Direct3D12Resource(),
    destinationResource(resource)
  {
  	
    if (device == nullptr || resource == nullptr) {
      throw IException("Invalid parameter.");
    }

    //Define a heap properites for the intermediate upload resource. 
    D3D12_HEAP_PROPERTIES props = {
            D3D12_HEAP_TYPE_UPLOAD,
            D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
            D3D12_MEMORY_POOL_UNKNOWN,
            1,
            1
    };

    D3D12_RESOURCE_DESC resDesc = resource->GetDesc();
    UINT64 requiredSize = 0;
    
    device->GetCopyableFootprints(&resDesc, 0, 1, 0, nullptr, nullptr, nullptr, &requiredSize);
    
    //Define an upload resource descripter for the intermediate upload resource. 
        
    D3D12_RESOURCE_DESC uploadDesc = {
            D3D12_RESOURCE_DIMENSION_BUFFER,
            0,
            requiredSize,
            1,
            1,
            1,
            DXGI_FORMAT_UNKNOWN,
            1, 
            0,
            D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
            D3D12_RESOURCE_FLAG_NONE
    };
  
    
   ID3D12Resource* intermediateResource = NULL;
   //Createa the intermediate resource.
    HRESULT hr = device->CreateCommittedResource(
            &props,
            D3D12_HEAP_FLAG_NONE,
            &uploadDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&intermediateResource));
    if (SUCCEEDED(hr)) {
      set(intermediateResource);
    } else {
      throw IException("Failed to CreateCommittedResource. HRESULT(0x%lx)", hr);
    }
  }
  
public:

  ~Direct3D12Subresources()
  {
  }
  
 
  UINT64 update(
        __in ID3D12GraphicsCommandList* graphicsCommandList,
        __in UINT                        firstSubResource,
        __in UINT                        subResourceCount,
        __in D3D12_SUBRESOURCE_DATA*     sourceData
      ) 
  {
    if (graphicsCommandList == nullptr || 
        sourceData == nullptr ) {
          throw IException("Invalid parameter.");
    }
    
    ID3D12Resource*  intermediateResource = getResource();

    UINT64 intermediateOffset = 0;

    UINT64 result = UpdateSubresources( 
        graphicsCommandList,
        destinationResource,
      
        intermediateResource,
        intermediateOffset,
        firstSubResource,
        subResourceCount,
        sourceData );
    if (result <= 0) {
      throw IException("Failed to UpdateSubresources. Result(%lld)", result)
    }
    return result;
  }

  void update(ID3D12GraphicsCommandList* graphicsCommandList,
            ID3D12CommandAllocator*    commandAllocator,
            ID3D12CommandQueue*        commandQueue,
        __in D3D12_SUBRESOURCE_DATA*     sourceData,
    
            Direct3D12Synchronizer*    synchronizer)
  {
    commandAllocator->Reset();
    graphicsCommandList->Reset(commandAllocator, nullptr);

    D3D12ResourceBarrier barrier(destinationResource,  D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
    barrier.startCopyTransition();

    graphicsCommandList->ResourceBarrier(1, barrier);
             
    ID3D12Resource*  intermediateResource = getResource();

    UINT64 intermediateOffset = 0;

    UINT64 result = UpdateSubresources( 
        graphicsCommandList,
        destinationResource,
      
        intermediateResource,
        intermediateOffset,
        0,
        1,
        sourceData );
    if (result <= 0) {
      throw IException("Failed to UpdateSubresources. Result(%lld)", result)
    }
 
    barrier.endCopyTransition();
    graphicsCommandList->ResourceBarrier(1, barrier);

    graphicsCommandList->Close();
    ID3D12CommandList* list[] = { graphicsCommandList };
    commandQueue->ExecuteCommandLists(1, list);

    synchronizer->waitForCompletion();
  }  
  //------------------------------------------------------------------------------------------------
  // Row-by-row memcpy
  void MemcpySubresource(
    _In_ const D3D12_MEMCPY_DEST* pDest,
    _In_ const D3D12_SUBRESOURCE_DATA* pSrc,
    SIZE_T RowSizeInBytes,
    UINT NumRows,
    UINT NumSlices)
  {
    for (UINT z = 0; z < NumSlices; ++z)
    {
        BYTE* pDestSlice = reinterpret_cast<BYTE*>(pDest->pData) + pDest->SlicePitch * z;
        const BYTE* pSrcSlice = reinterpret_cast<const BYTE*>(pSrc->pData) + pSrc->SlicePitch * z;
        for (UINT y = 0; y < NumRows; ++y)
        {
            memcpy(pDestSlice + pDest->RowPitch * y,
                   pSrcSlice + pSrc->RowPitch * y,
                   RowSizeInBytes);
        }
    }
  }

  //------------------------------------------------------------------------------------------------
  // Returns required size of a buffer to be used for data upload
  UINT64 GetRequiredIntermediateSize(
    _In_ ID3D12Resource* pDestinationResource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources)
  {
    D3D12_RESOURCE_DESC Desc = pDestinationResource->GetDesc();
    UINT64 RequiredSize = 0;
    
    ID3D12Device* pDevice;
    pDestinationResource->GetDevice(__uuidof(*pDevice), reinterpret_cast<void**>(&pDevice));
    pDevice->GetCopyableFootprints(&Desc, FirstSubresource, NumSubresources, 0, nullptr, nullptr, nullptr, &RequiredSize);
    pDevice->Release();
    
    return RequiredSize;
  }

  //------------------------------------------------------------------------------------------------
  // All arrays must be populated (e.g. by calling GetCopyableFootprints)
  UINT64 UpdateSubresources(
    _In_ ID3D12GraphicsCommandList* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    UINT64 RequiredSize,
    _In_reads_(NumSubresources) const D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
    _In_reads_(NumSubresources) const UINT* pNumRows,
    _In_reads_(NumSubresources) const UINT64* pRowSizesInBytes,
    _In_reads_(NumSubresources) const D3D12_SUBRESOURCE_DATA* pSrcData)
  {
    // Minor validation
    D3D12_RESOURCE_DESC IntermediateDesc = pIntermediate->GetDesc();
    D3D12_RESOURCE_DESC DestinationDesc = pDestinationResource->GetDesc();
    if (IntermediateDesc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER || 
        IntermediateDesc.Width < RequiredSize + pLayouts[0].Offset || 
        RequiredSize > (SIZE_T)-1 || 
        (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER && 
            (FirstSubresource != 0 || NumSubresources != 1)))
    {
        return 0;
    }
    
    BYTE* pData;
    HRESULT hr = pIntermediate->Map(0, NULL, reinterpret_cast<void**>(&pData));
    if (FAILED(hr))
    {
        return 0;
    }
    
    for (UINT i = 0; i < NumSubresources; ++i)
    {
        if (pRowSizesInBytes[i] > (SIZE_T)-1) return 0;
        D3D12_MEMCPY_DEST DestData = { pData + pLayouts[i].Offset, pLayouts[i].Footprint.RowPitch, pLayouts[i].Footprint.RowPitch * pNumRows[i] };
        MemcpySubresource(&DestData, &pSrcData[i], (SIZE_T)pRowSizesInBytes[i], pNumRows[i], pLayouts[i].Footprint.Depth);
    }
    pIntermediate->Unmap(0, NULL);
    
    if (DestinationDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
    {
        CD3DX12_BOX SrcBox( UINT( pLayouts[0].Offset ), UINT( pLayouts[0].Offset + pLayouts[0].Footprint.Width ) );
        pCmdList->CopyBufferRegion(
            pDestinationResource, 0, pIntermediate, pLayouts[0].Offset, pLayouts[0].Footprint.Width);
    }
    else
    {
        for (UINT i = 0; i < NumSubresources; ++i)
        {
            CD3DX12_TEXTURE_COPY_LOCATION Dst(pDestinationResource, i + FirstSubresource);
            CD3DX12_TEXTURE_COPY_LOCATION Src(pIntermediate, pLayouts[i]);
            pCmdList->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);
        }
    }
    return RequiredSize;
  }

  //------------------------------------------------------------------------------------------------
  // Heap-allocating UpdateSubresources implementation
  UINT64 UpdateSubresources( 
    _In_ ID3D12GraphicsCommandList* pCmdList,
    _In_ ID3D12Resource* pDestinationResource,
    _In_ ID3D12Resource* pIntermediate,
    UINT64 IntermediateOffset,
    _In_range_(0,D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource) UINT NumSubresources,
    _In_reads_(NumSubresources) D3D12_SUBRESOURCE_DATA* pSrcData)
  {
    UINT64 RequiredSize = 0;
    UINT64 MemToAlloc = static_cast<UINT64>(sizeof(D3D12_PLACED_SUBRESOURCE_FOOTPRINT) + sizeof(UINT) + sizeof(UINT64)) * NumSubresources;
    if (MemToAlloc > SIZE_MAX)
    {
       return 0;
    }
    void* pMem = HeapAlloc(GetProcessHeap(), 0, static_cast<SIZE_T>(MemToAlloc));
    if (pMem == NULL)
    {
       return 0;
    }
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts = reinterpret_cast<D3D12_PLACED_SUBRESOURCE_FOOTPRINT*>(pMem);
    UINT64* pRowSizesInBytes = reinterpret_cast<UINT64*>(pLayouts + NumSubresources);
    UINT* pNumRows = reinterpret_cast<UINT*>(pRowSizesInBytes + NumSubresources);
    
    D3D12_RESOURCE_DESC Desc = pDestinationResource->GetDesc();
    ID3D12Device* pDevice;
    pDestinationResource->GetDevice(__uuidof(*pDevice), reinterpret_cast<void**>(&pDevice));
    pDevice->GetCopyableFootprints(&Desc, FirstSubresource, NumSubresources, IntermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &RequiredSize);
    pDevice->Release();
    
    UINT64 Result = UpdateSubresources(pCmdList, pDestinationResource, pIntermediate, FirstSubresource, NumSubresources, RequiredSize, pLayouts, pNumRows, pRowSizesInBytes, pSrcData);
    HeapFree(GetProcessHeap(), 0, pMem);
    return Result;
  }
};

}

