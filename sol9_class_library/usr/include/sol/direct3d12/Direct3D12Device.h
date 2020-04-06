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
 *  Direct3D12Device.h
 *
 *****************************************************************************/

// 2016/09/25
// 2016/11/14 Added a new constructer based on the followoing site.
// https://msdn.microsoft.com/ja-jp/library/windows/desktop/dn770336(v=vs.85).aspx

#pragma once

#include <sol/direct3d12/Direct3D12Object.h>

namespace SOL {

class Direct3D12Device : public Direct3D12Object {

private:
  static const D3D_FEATURE_LEVEL featureLevel =  D3D_FEATURE_LEVEL_11_0;
  
  void getHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter)
  {
    *ppAdapter = nullptr;
    for (UINT adapterIndex = 0; ; ++adapterIndex) {
      IDXGIAdapter1* pAdapter = nullptr;
      if (DXGI_ERROR_NOT_FOUND == pFactory->EnumAdapters1(adapterIndex, &pAdapter)) {
        break;
      } 

      if (SUCCEEDED(D3D12CreateDevice(pAdapter, featureLevel, _uuidof(ID3D12Device), nullptr))) {
        *ppAdapter = pAdapter;
        return;
      }
      pAdapter->Release();
    }
  }

public:
  Direct3D12Device(__in IDXGIFactory4* factory)
  :Direct3D12Object()
  {
    IDXGIAdapter1* adapter = NULL;
    getHardwareAdapter(factory, &adapter);
    
    ID3D12Device* device = NULL;
    HRESULT hr = D3D12CreateDevice(
        adapter,
        D3D_FEATURE_LEVEL_11_0, //minimumFeatureLevel,
        __uuidof(ID3D12Device), 
      (void**)&device );
    
    if (adapter) {
      adapter->Release();
    }
    if (FAILED(hr)) {
      throw IException("Failed to D3D12CreateDevice. hr=%lf", hr);
    } else {
      set(device);
    }
  }
  

public:
  Direct3D12Device(_In_opt_ IDXGIAdapter* pAdapter=nullptr,
        D3D_FEATURE_LEVEL minimumFeatureLevel = featureLevel)
  :Direct3D12Object()
  {
    ID3D12Device* device = NULL;
    HRESULT hr = D3D12CreateDevice(
        pAdapter,
        minimumFeatureLevel,
        __uuidof(ID3D12Device), 
      (void**)&device );
    if (FAILED(hr)) {
      throw IException("Failed to D3D12CreateDevice. hr=%lf", hr);
    } else {
      set(device);
    }
  }
  
  ~Direct3D12Device()
  { 
  }

   
  operator ID3D12Device*()
  {
    return getDevice();
  }

  ID3D12Device* getDevice()
  {
    ID3D12Device* device = (ID3D12Device*)getIUnknown();
    if (device) {
        return device;
    } else {
      throw IException("ID3D12Device is NULL.");
    }
  }
  
  UINT getNodeCount()
  {
    ID3D12Device* device = getDevice();
    return device -> GetNodeCount();
  }
        
  void createCommandQueue( 
            _In_  const D3D12_COMMAND_QUEUE_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppCommandQueue)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateCommandQueue( 
            pDesc,
            riid,
            ppCommandQueue);
    if (FAILED(hr)) {
      throw IException("Failed to CreateCommandQueue. HRESULT(0x%lx)", hr);
    }
  }
        
  void createCommandAllocator( 
            _In_  D3D12_COMMAND_LIST_TYPE type,
            REFIID riid,
            _COM_Outptr_  void **ppCommandAllocator)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateCommandAllocator( 
            type,
            riid,
            ppCommandAllocator);
    if (FAILED(hr)) {
      throw IException("Failed to CreateCommandAllocator. HRESULT(0x%lx)", hr);
    }
  }
        
  void createGraphicsPipelineState( 
            _In_  const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppPipelineState)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateGraphicsPipelineState( 
            pDesc,
            riid,
            ppPipelineState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateGraphicsPipelineState. HRESULT(0x%lx)", hr);
    }
  }
        
  void createComputePipelineState( 
            _In_  const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppPipelineState)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateComputePipelineState( 
            pDesc,
            riid,
            ppPipelineState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateComputePipelineState. HRESULT(0x%lx)", hr);
    }
  }
        
  void createCommandList( 
            _In_  UINT nodeMask,
            _In_  D3D12_COMMAND_LIST_TYPE type,
            _In_  ID3D12CommandAllocator *pCommandAllocator,
            _In_opt_  ID3D12PipelineState *pInitialState,
            REFIID riid,
            _COM_Outptr_  void **ppCommandList)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateCommandList( 
            nodeMask,
            type,
            pCommandAllocator,
            pInitialState,
            riid,
            ppCommandList);
    if (FAILED(hr)) {
      throw IException("Failed to CreateCommandList. HRESULT(0x%lx)", hr);
    }
  }
        
  void checkFeatureSupport( 
            D3D12_FEATURE feature,
            _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
            UINT featureSupportDataSize)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CheckFeatureSupport( 
            feature,
            pFeatureSupportData,
            featureSupportDataSize);
    if (FAILED(hr)) {
      throw IException("Failed to CheckFeatureSupport. HRESULT(0x%lx)", hr);
    }
  }
        
  void createDescriptorHeap( 
            _In_  const D3D12_DESCRIPTOR_HEAP_DESC *pDescriptorHeapDesc,
            REFIID riid,
            _COM_Outptr_  void **ppvHeap)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateDescriptorHeap( 
            pDescriptorHeapDesc,
            riid,
            ppvHeap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDescriptorHeap. HRESULT(0x%lx)", hr);
    }
  }
        
  UINT getDescriptorHandleIncrementSize( 
            _In_  D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType)
  {
    ID3D12Device* device = getDevice();
    return device -> GetDescriptorHandleIncrementSize( 
            descriptorHeapType);
  }
        
  void createRootSignature( 
            _In_  UINT nodeMask,
            _In_reads_(blobLengthInBytes)  const void *pBlobWithRootSignature,
            _In_  SIZE_T blobLengthInBytes,
            REFIID riid,
            _COM_Outptr_  void **ppvRootSignature)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateRootSignature( 
            nodeMask,
            pBlobWithRootSignature,
            blobLengthInBytes,
            riid,
            ppvRootSignature);
    if (FAILED(hr)) {
      throw IException("Failed to CreateRootSignature. HRESULT(0x%lx)", hr);
    }
  }
        
  void createConstantBufferView( 
            _In_opt_  const D3D12_CONSTANT_BUFFER_VIEW_DESC *pDesc,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor)
  {
    ID3D12Device* device = getDevice();
    device -> CreateConstantBufferView( 
            pDesc,
            destDescriptor);
  }
        
  void createShaderResourceView( 
            _In_opt_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_SHADER_RESOURCE_VIEW_DESC *pDesc,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor)
  {
    ID3D12Device* device = getDevice();
    device -> CreateShaderResourceView( 
            pResource,
            pDesc,
            destDescriptor);
  }
        
  void createUnorderedAccessView( 
            _In_opt_  ID3D12Resource *pResource,
            _In_opt_  ID3D12Resource *pCounterResource,
            _In_opt_  const D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor)
  {
    ID3D12Device* device = getDevice();
    device -> CreateUnorderedAccessView( 
            pResource,
            pCounterResource,
            pDesc,
            destDescriptor);
  }
        
  void createRenderTargetView( 
            _In_opt_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor)
  {
    ID3D12Device* device = getDevice();
    device -> CreateRenderTargetView( 
            pResource,
            pDesc,
            destDescriptor);
  }
        
  void createDepthStencilView( 
            _In_opt_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DEPTH_STENCIL_VIEW_DESC *pDesc,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor)
  {
    ID3D12Device* device = getDevice();
    device -> CreateDepthStencilView( 
            pResource,
            pDesc,
            destDescriptor);
  }
        
  void createSampler( 
            _In_  const D3D12_SAMPLER_DESC *pDesc,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor)
  {
    ID3D12Device* device = getDevice();
    device -> CreateSampler( 
            pDesc,
            destDescriptor);
  }
        
  void copyDescriptors( 
            _In_  UINT numDestDescriptorRanges,
            _In_reads_(numDestDescriptorRanges)  const D3D12_CPU_DESCRIPTOR_HANDLE *pDestDescriptorRangeStarts,
            _In_reads_opt_(numDestDescriptorRanges)  const UINT *pDestDescriptorRangeSizes,
            _In_  UINT numSrcDescriptorRanges,
            _In_reads_(numSrcDescriptorRanges)  const D3D12_CPU_DESCRIPTOR_HANDLE *pSrcDescriptorRangeStarts,
            _In_reads_opt_(NumSrcDescriptorRanges)  const UINT *pSrcDescriptorRangeSizes,
            _In_  D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapsType)
  {
    ID3D12Device* device = getDevice();
    device ->  CopyDescriptors( 
            numDestDescriptorRanges,
            pDestDescriptorRangeStarts,
            pDestDescriptorRangeSizes,
            numSrcDescriptorRanges,
            pSrcDescriptorRangeStarts,
            pSrcDescriptorRangeSizes,
            descriptorHeapsType);
  }
        
  void copyDescriptorsSimple( 
            _In_  UINT numDescriptors,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptorRangeStart,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE srcDescriptorRangeStart,
            _In_  D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapsType)
  {
    ID3D12Device* device = getDevice();
    device -> CopyDescriptorsSimple( 
            numDescriptors,
            destDescriptorRangeStart,
            srcDescriptorRangeStart,
            descriptorHeapsType);
  }
        
  D3D12_RESOURCE_ALLOCATION_INFO getResourceAllocationInfo( 
            _In_  UINT visibleMask,
            _In_  UINT numResourceDescs,
            _In_reads_(numResourceDescs)  const D3D12_RESOURCE_DESC *pResourceDescs)
  {
    ID3D12Device* device = getDevice();
    return device -> GetResourceAllocationInfo( 
            visibleMask,
            numResourceDescs,
            pResourceDescs);
  }
        
  D3D12_HEAP_PROPERTIES getCustomHeapProperties( 
            _In_  UINT nodeMask,
            D3D12_HEAP_TYPE heapType)
  {
    ID3D12Device* device = getDevice();
    return device -> GetCustomHeapProperties( 
            nodeMask,
            heapType);
  }
        
  void createCommittedResource( 
            _In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
            D3D12_HEAP_FLAGS heapFlags,
            _In_  const D3D12_RESOURCE_DESC *pDesc,
            D3D12_RESOURCE_STATES initialResourceState,
            _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            REFIID riidResource,
            _COM_Outptr_opt_  void **ppvResource)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateCommittedResource( 
            pHeapProperties,
            heapFlags,
            pDesc,
            initialResourceState,
            pOptimizedClearValue,
            riidResource,
            ppvResource);
    if (FAILED(hr)) {
      throw IException("Failed to CreateCommittedResource. HRESULT(0x%lx)", hr);
    }
  }
        
  void createHeap( 
            _In_  const D3D12_HEAP_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvHeap)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateHeap( 
            pDesc,
            riid,
            ppvHeap);
    if (FAILED(hr)) {
      throw IException("Failed to CreateHeap. HRESULT(0x%lx)", hr);
    }
  }
        
  void createPlacedResource( 
            _In_  ID3D12Heap *pHeap,
            UINT64 heapOffset,
            _In_  const D3D12_RESOURCE_DESC *pDesc,
            D3D12_RESOURCE_STATES initialState,
            _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvResource)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreatePlacedResource( 
            pHeap,
            heapOffset,
            pDesc,
            initialState,
            pOptimizedClearValue,
            riid,
            ppvResource);
    if (FAILED(hr)) {
      throw IException("Failed to CreatePlacedResource. HRESULT(0x%lx)", hr);
    }
  }
        
  void createReservedResource( 
            _In_  const D3D12_RESOURCE_DESC *pDesc,
            D3D12_RESOURCE_STATES initialState,
            _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvResource)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateReservedResource( 
            pDesc,
            initialState,
            pOptimizedClearValue,
            riid,
            ppvResource);
    if (FAILED(hr)) {
      throw IException("Failed to CreateReservedResource. HRESULT(0x%lx)", hr);
    }
  }
        
  void createSharedHandle( 
            _In_  ID3D12DeviceChild *pObject,
            _In_opt_  const SECURITY_ATTRIBUTES *pAttributes,
            DWORD access,
            _In_opt_  LPCWSTR name,
            _Out_  HANDLE *pHandle)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateSharedHandle( 
            pObject,
            pAttributes,
            access,
            name,
            pHandle);
    if (FAILED(hr)) {
      throw IException("Failed to CreateSharedHandle. HRESULT(0x%lx)", hr);
    }
  }
        
  void openSharedHandle( 
            _In_  HANDLE ntHandle,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvObj)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> OpenSharedHandle( 
            ntHandle,
            riid,
            ppvObj);
    if (FAILED(hr)) {
      throw IException("Failed to OpenSharedHandle. HRESULT(0x%lx)", hr);
    }
  }
        
  void openSharedHandleByName( 
            _In_  LPCWSTR name,
            DWORD access,
            _Out_  HANDLE *pNTHandle)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> OpenSharedHandleByName( 
            name,
            access,
            pNTHandle);
    if (FAILED(hr)) {
      throw IException("Failed to OpenSharedHandleByName. HRESULT(0x%lx)", hr);
    }
  }
        
  void makeResident( 
            UINT numObjects,
            _In_reads_(NumObjects)  ID3D12Pageable *const *ppObjects)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> MakeResident( 
            numObjects,
            ppObjects);
    if (FAILED(hr)) {
      throw IException("Failed to MakeResident. HRESULT(0x%lx)", hr);
    }
  }
        
  void evict( 
            UINT numObjects,
            _In_reads_(NumObjects)  ID3D12Pageable *const *ppObjects)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> Evict( 
            numObjects,
            ppObjects);
    if (FAILED(hr)) {
      throw IException("Failed to Evict. HRESULT(0x%lx)", hr);
    }
  }
        
  void createFence( 
            UINT64 initialValue,
            D3D12_FENCE_FLAGS flags,
            REFIID riid,
            _COM_Outptr_  void **ppFence)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateFence( 
            initialValue,
            flags,
            riid,
            ppFence);
    if (FAILED(hr)) {
      throw IException("Failed to CreateFence. HRESULT(0x%lx)", hr);
    }
  }
        
  void getDeviceRemovedReason()
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> GetDeviceRemovedReason();
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
        
  void getCopyableFootprints( 
            _In_  const D3D12_RESOURCE_DESC *pResourceDesc,
            _In_range_(0,D3D12_REQ_SUBRESOURCES)  UINT firstSubresource,
            _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource)  UINT numSubresources,
            UINT64 baseOffset,
            _Out_writes_opt_(NumSubresources)  D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
            _Out_writes_opt_(NumSubresources)  UINT *pNumRows,
            _Out_writes_opt_(NumSubresources)  UINT64 *pRowSizeInBytes,
            _Out_opt_  UINT64 *pTotalBytes)
  {
    ID3D12Device* device = getDevice();
    device -> GetCopyableFootprints( 
            pResourceDesc,
            firstSubresource,
            numSubresources,
            baseOffset,
            pLayouts,
            pNumRows,
            pRowSizeInBytes,
            pTotalBytes);
  }
        
  void createQueryHeap( 
            _In_  const D3D12_QUERY_HEAP_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvHeap)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateQueryHeap( 
            pDesc,
            riid,
            ppvHeap);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
        
  void setStablePowerState( 
            BOOL enable)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> SetStablePowerState( 
            enable);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
        
  void createCommandSignature( 
            _In_  const D3D12_COMMAND_SIGNATURE_DESC *pDesc,
            _In_opt_  ID3D12RootSignature *pRootSignature,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvCommandSignature)
  {
    ID3D12Device* device = getDevice();
    HRESULT hr = device -> CreateCommandSignature( 
            pDesc,
            pRootSignature,
            riid,
            ppvCommandSignature);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
        
  void getResourceTiling( 
            _In_  ID3D12Resource *pTiledResource,
            _Out_opt_  UINT *pNumTilesForEntireResource,
            _Out_opt_  D3D12_PACKED_MIP_INFO *pPackedMipDesc,
            _Out_opt_  D3D12_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
            _Inout_opt_  UINT *pNumSubresourceTilings,
            _In_  UINT firstSubresourceTilingToGet,
            _Out_writes_(*pNumSubresourceTilings)  D3D12_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips)
  {
    ID3D12Device* device = getDevice();
    device -> GetResourceTiling( 
            pTiledResource,
            pNumTilesForEntireResource,
            pPackedMipDesc,
            pStandardTileShapeForNonPackedMips,
            pNumSubresourceTilings,
            firstSubresourceTilingToGet,
            pSubresourceTilingsForNonPackedMips);
  }
        
  LUID getAdapterLuid()
  {
    ID3D12Device* device = getDevice();
    return device -> GetAdapterLuid();
  }
        
};

}
    
