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
 *  Direct3D12GraphicsCommandList.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12CommandList.h>

namespace SOL {

class Direct3D12GraphicsCommandList : public Direct3D12CommandList {
private:
  D3D12_VIEWPORT viewPort;
  float          arx;
  float          ary;
  
public:
  Direct3D12GraphicsCommandList(
      __in ID3D12Device*           device,
      __in ID3D12CommandAllocator* commandAllocator,
      __in ID3D12PipelineState*    pipelineState=nullptr,
      __in UINT                    nodeMask = 0,
      __in bool                    closeOnStartup=true)
  :Direct3D12CommandList()
  {
    memset(&viewPort, 0, sizeof(viewPort));
    arx = 0.0f;
    ary = 0.0f;
    
    if (device == nullptr || commandAllocator == nullptr) {
      throw IException("Invalid paramter.");
    }
    
    ID3D12GraphicsCommandList* graphicsCommandList = NULL;

    HRESULT hr = device->CreateCommandList(
                nodeMask, 
                D3D12_COMMAND_LIST_TYPE_DIRECT, 
                commandAllocator,
                pipelineState,
                IID_PPV_ARGS(&graphicsCommandList) );
    if (SUCCEEDED(hr)) {
      set(graphicsCommandList);
      if (closeOnStartup) {
         close();
      }
    } else {
        throw IException("Failed to ID3D12Device::CreateCommandList. HRESULT(0x%lx)", hr);
    }
  }
  
  Direct3D12GraphicsCommandList(
    __in ID3D12GraphicsCommandList* graphicsCommandList)
  :Direct3D12CommandList(graphicsCommandList)
  {
  }
  
  ~Direct3D12GraphicsCommandList()
  { 
  }

  operator ID3D12GraphicsCommandList*()
  {
    return getGraphicsCommandList();
  }

  ID3D12GraphicsCommandList* getGraphicsCommandList()
  {
    ID3D12GraphicsCommandList* graphicsCommandList = (ID3D12GraphicsCommandList*)getIUnknown();
    if (graphicsCommandList) {
        return graphicsCommandList;
    } else {
      throw IException("ID3D12GraphicsCommandList is NULL.");
    }
  }

  void close()
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    HRESULT hr = graphicsCommandList -> Close(); 
    if (FAILED(hr)) {
      throw IException("Failed to Close. HRESULT(0x%lx)", hr);
    }
  }

  void reset( 
            _In_  ID3D12CommandAllocator *allocator,
            _In_opt_  ID3D12PipelineState *pInitialState=nullptr)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    HRESULT hr = graphicsCommandList -> Reset( 
            allocator,
            pInitialState);
    if (FAILED(hr)) {
        throw IException("Failed to Reset. HRESULT(0x%lx)", hr);
    }
  }
  

  void clearState( 
            _In_opt_  ID3D12PipelineState *pipelineState=nullptr)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ClearState( 
            pipelineState);
  }
        
  void drawInstanced( 
            _In_  UINT vertexCountPerInstance,
            _In_  UINT instanceCount,
            _In_  UINT startVertexLocation,
            _In_  UINT startInstanceLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> DrawInstanced( 
            vertexCountPerInstance,
            instanceCount,
            startVertexLocation,
            startInstanceLocation);
  }
        
  void drawIndexedInstanced( 
            _In_  UINT indexCountPerInstance,
            _In_  UINT instanceCount,
            _In_  UINT startIndexLocation,
            _In_  INT  baseVertexLocation,
            _In_  UINT startInstanceLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> DrawIndexedInstanced( 
            indexCountPerInstance,
            instanceCount,
            startIndexLocation,
            baseVertexLocation,
            startInstanceLocation);
  }
        
  void dispatch( 
            _In_  UINT threadGroupCountX,
            _In_  UINT threadGroupCountY,
            _In_  UINT threadGroupCountZ)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> Dispatch( 
            threadGroupCountX,
            threadGroupCountY,
            threadGroupCountZ);
  }
        
  void copyBufferRegion( 
            _In_  ID3D12Resource* pDstBuffer,
            UINT64                dstOffset,
            _In_  ID3D12Resource* pSrcBuffer,
            UINT64                srcOffset,
            UINT64                numBytes)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> CopyBufferRegion( 
            pDstBuffer,
            dstOffset,
            pSrcBuffer,
            srcOffset,
            numBytes);
  }
        
  void copyTextureRegion( 
            _In_  const D3D12_TEXTURE_COPY_LOCATION* pDst,
            UINT dstX,
            UINT dstY,
            UINT dstZ,
            _In_ const D3D12_TEXTURE_COPY_LOCATION *pSrc,
            _In_opt_  const D3D12_BOX *pSrcBox)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> CopyTextureRegion( 
            pDst,
            dstX,
            dstY,
            dstZ,
            pSrc,
            pSrcBox);
  }
        
  void copyResource( 
            _In_  ID3D12Resource *pDstResource,
            _In_  ID3D12Resource *pSrcResource)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> CopyResource( 
            pDstResource,
            pSrcResource);
  }
        
  void copyTiles( 
            _In_  ID3D12Resource*                        pTiledResource,
            _In_  const D3D12_TILED_RESOURCE_COORDINATE* pTileRegionStartCoordinate,
            _In_  const D3D12_TILE_REGION_SIZE*          pTileRegionSize,
            _In_  ID3D12Resource*                        pBuffer,
            UINT64                                       bufferStartOffsetInBytes,
            D3D12_TILE_COPY_FLAGS                        flags)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> CopyTiles( 
            pTiledResource,
            pTileRegionStartCoordinate,
            pTileRegionSize,
            pBuffer,
            bufferStartOffsetInBytes,
            flags);
  }
        
  void resolveSubresource( 
            _In_  ID3D12Resource*  pDstResource,
            _In_  UINT             dstSubresource,
            _In_  ID3D12Resource*  pSrcResource,
            _In_  UINT             srcSubresource,
            _In_  DXGI_FORMAT      format)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ResolveSubresource( 
            pDstResource,
            dstSubresource,
            pSrcResource,
            srcSubresource,
            format);
  }
        
  void setIAPrimitiveTopology( 
            _In_  D3D12_PRIMITIVE_TOPOLOGY primitiveTopology)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> IASetPrimitiveTopology( 
            primitiveTopology);
  }
  
  void setRSViewport(
            UINT x,
            UINT y,
            UINT width,
            UINT height)
  {
    D3D12_VIEWPORT viewPort;
    memset(&viewPort, 0, sizeof(viewPort));
    float w = (float)width;
    float h = (float)height;
    
    viewPort.TopLeftX = (float)x;
    viewPort.TopLeftY = (float)y;
    viewPort.Width    = w; //(float)width;
    viewPort.Height   = h; //(float)height;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> RSSetViewports( 
            1,
            &viewPort);
  }

  void setRSViewport(
            UINT width,
            UINT height)
  {
    setRSViewport(0, 0, width, height);
  }

  void setRSViewports( 
            _In_  UINT                 numViewports,
            _In_  const D3D12_VIEWPORT *pViewports)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> RSSetViewports( 
            numViewports,
            pViewports);
  }

  void setRSScissorRect(
            UINT x, 
            UINT y, 
            UINT width,
            UINT height)
  {    
    D3D12_RECT rect;  
      memset(&rect, 0, sizeof(rect));
      rect.left   = (LONG)x;
      rect.right  = rect.left + (LONG)width;
      rect.top    = (LONG)y;
      rect.bottom = rect.top  + (LONG)height;
    
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> RSSetScissorRects( 
            1,
            &rect);
  }

  void setRSScissorRect(
            UINT width,
            UINT height)
  {    
    setRSScissorRect(0, 0, width, height);
  }
  
  void setRSScissorRects( 
            _In_  UINT            numRects,
            _In_ const D3D12_RECT *pRects)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> RSSetScissorRects( 
            numRects,
            pRects);
  }
        
  void setOMBlendFactor( 
            _In_opt_  const FLOAT blendFactor[ 4 ])
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> OMSetBlendFactor( 
            blendFactor);
  }
        
  void setOMStencilRef( 
            _In_  UINT stencilRef)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> OMSetStencilRef( 
            stencilRef);
  }
        
  void setPipelineState( 
            _In_  ID3D12PipelineState *pPipelineState)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetPipelineState( 
            pPipelineState);
  }
        
  void resourceBarrier( 
            _In_  UINT                          numBarriers,
            _In_  const D3D12_RESOURCE_BARRIER *pBarriers)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ResourceBarrier( 
            numBarriers,
            pBarriers);
  }
        
  void executeBundle( 
            _In_  ID3D12GraphicsCommandList *pCommandList)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ExecuteBundle( 
            pCommandList);
  }
        
  void setDescriptorHeap( 
             __in ID3D12DescriptorHeap* heap)
  {
    ID3D12DescriptorHeap* heaps[] = { heap };
    
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetDescriptorHeaps( 
            _countof(heaps),
            heaps);
  }

  void setDescriptorHeaps( 
            _In_  UINT numDescriptorHeaps,
            _In_reads_(numDescriptorHeaps)  ID3D12DescriptorHeap *const *ppDescriptorHeaps)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetDescriptorHeaps( 
            numDescriptorHeaps,
            ppDescriptorHeaps);
  }
        
  void setComputeRootSignature( 
            _In_opt_  ID3D12RootSignature *pRootSignature)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetComputeRootSignature( 
            pRootSignature);
  }
        
  void setGraphicsRootSignature( 
            _In_opt_  ID3D12RootSignature *pRootSignature)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetGraphicsRootSignature( 
            pRootSignature);
  }
        
  void setComputeRootDescriptorTable( 
            _In_  UINT                        rootParameterIndex,
            _In_  D3D12_GPU_DESCRIPTOR_HANDLE baseDescriptor)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetComputeRootDescriptorTable( 
            rootParameterIndex,
            baseDescriptor);
  }
        
  void setGraphicsRootDescriptorTable( 
            _In_  UINT                        rootParameterIndex,
            _In_  D3D12_GPU_DESCRIPTOR_HANDLE baseDescriptor)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetGraphicsRootDescriptorTable( 
            rootParameterIndex,
            baseDescriptor);
  }
        
  void setComputeRoot32BitConstant( 
            _In_  UINT rootParameterIndex,
            _In_  UINT srcData,
            _In_  UINT destOffsetIn32BitValues)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetComputeRoot32BitConstant( 
            rootParameterIndex,
            srcData,
            destOffsetIn32BitValues);
  }
        
  void setGraphicsRoot32BitConstant( 
            _In_  UINT rootParameterIndex,
            _In_  UINT srcData,
            _In_  UINT destOffsetIn32BitValues)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetGraphicsRoot32BitConstant( 
            rootParameterIndex,
            srcData,
            destOffsetIn32BitValues);
  }
        
  void setComputeRoot32BitConstants( 
            _In_  UINT      rootParameterIndex,
            _In_  UINT      num32BitValuesToSet,
            _In_ const void *pSrcData,
            _In_  UINT      destOffsetIn32BitValues)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetComputeRoot32BitConstants( 
            rootParameterIndex,
            num32BitValuesToSet,
            pSrcData,
            destOffsetIn32BitValues);
  }
        
  void setGraphicsRoot32BitConstants( 
            _In_  UINT                      rootParameterIndex,
            _In_  UINT                      num32BitValuesToSet,
            _In_reads_(num32BitValuesToSet*sizeof(UINT))  const void *pSrcData,
            _In_  UINT                      destOffsetIn32BitValues)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetGraphicsRoot32BitConstants( 
            rootParameterIndex,
            num32BitValuesToSet,
            pSrcData,
            destOffsetIn32BitValues);
  }
        
  void setComputeRootConstantBufferView( 
            _In_  UINT                      rootParameterIndex,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetComputeRootConstantBufferView( 
            rootParameterIndex,
            bufferLocation);
  }
        
  void setGraphicsRootConstantBufferView( 
            _In_  UINT                      rootParameterIndex,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetGraphicsRootConstantBufferView( 
            rootParameterIndex,
            bufferLocation);
  }
        
  void setComputeRootShaderResourceView( 
            _In_  UINT                      rootParameterIndex,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetComputeRootShaderResourceView( 
            rootParameterIndex,
            bufferLocation);
  }
        
  void setGraphicsRootShaderResourceView( 
            _In_  UINT                      rootParameterIndex,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetGraphicsRootShaderResourceView( 
            rootParameterIndex,
            bufferLocation);
  }
        
  void setComputeRootUnorderedAccessView( 
            _In_  UINT                      rootParameterIndex,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetComputeRootUnorderedAccessView( 
            rootParameterIndex,
            bufferLocation);
  }
        
  void setGraphicsRootUnorderedAccessView( 
            _In_  UINT                      rootParameterIndex,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetGraphicsRootUnorderedAccessView( 
            rootParameterIndex,
            bufferLocation);
  }
        
  void setIAIndexBuffer( 
            _In_opt_  const D3D12_INDEX_BUFFER_VIEW *pView)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> IASetIndexBuffer( 
            pView);
  }
        
  void setIAVertexBuffers( 
            _In_  UINT startSlot,
            _In_  UINT numViews,
            _In_reads_opt_(numViews)  const D3D12_VERTEX_BUFFER_VIEW *pViews)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> IASetVertexBuffers( 
            startSlot,
            numViews,
            pViews);
  }
        
  void setSOTargets( 
            _In_  UINT startSlot,
            _In_  UINT numViews,
            _In_reads_opt_(numViews)  const D3D12_STREAM_OUTPUT_BUFFER_VIEW *pViews)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SOSetTargets( 
            startSlot,
            numViews,
            pViews);
  }
        
  void setOMRenderTargets( 
            _In_  UINT                                   numRenderTargetDescriptors,
            _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors,
            _In_  BOOL                                   rtsSingleHandleToDescriptorRange,
            _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> OMSetRenderTargets( 
            numRenderTargetDescriptors,
            pRenderTargetDescriptors,
            rtsSingleHandleToDescriptorRange,
            pDepthStencilDescriptor);
  }
   
  
  void clearDepthStencilView( 
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView,
            _In_  D3D12_CLEAR_FLAGS           clearFlags = D3D12_CLEAR_FLAG_DEPTH,
            _In_  FLOAT                       depth  = 1.0f,
            _In_  UINT8                       stencil = 0,
            _In_  UINT                        numRects = 0,
            _In_reads_(numRects)  const D3D12_RECT *pRects = nullptr)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ClearDepthStencilView( 
            depthStencilView,
            clearFlags,
            depth,
            stencil,
            numRects,
            pRects);
  }

  //2016/10/28
  void clearRenderTargetView( 
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView,
             float r,
             float g,
             float b,
             float a)
  {
    const FLOAT rgba[] = {r, g, b, a};
    
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ClearRenderTargetView( 
            renderTargetView,
            rgba,
            0,
            nullptr);
  }

  void clearRenderTargetView( 
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView,
            _In_  const FLOAT                 colorRGBA[ 4 ],
            _In_  UINT                        numRects = 0,
            _In_reads_(numRects)  const D3D12_RECT *pRects = nullptr)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ClearRenderTargetView( 
            renderTargetView,
            colorRGBA,
            numRects,
            pRects);
  }
        
  void clearUnorderedAccessViewUint( 
            _In_  D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle,
            _In_  ID3D12Resource*             pResource,
            _In_  const UINT                  values[ 4 ],
            _In_  UINT                        numRects,
            _In_reads_(NumRects)  const D3D12_RECT *pRects)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ClearUnorderedAccessViewUint( 
            viewGPUHandleInCurrentHeap,
            viewCPUHandle,
            pResource,
            values,
            numRects,
            pRects);
  }
        
  void clearUnorderedAccessViewFloat( 
            _In_  D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap,
            _In_  D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle,
            _In_  ID3D12Resource*             pResource,
            _In_  const FLOAT                 values[ 4 ],
            _In_  UINT                        numRects,
            _In_reads_(numRects)  const D3D12_RECT *pRects)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ClearUnorderedAccessViewFloat( 
            viewGPUHandleInCurrentHeap,
            viewCPUHandle,
            pResource,
            values,
            numRects,
            pRects);
  }
        
  void discardResource( 
            _In_  ID3D12Resource*                 pResource,
            _In_opt_  const D3D12_DISCARD_REGION* pRegion)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> DiscardResource( 
            pResource,
            pRegion);
  }
        
  void beginQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE type,
            _In_  UINT index)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> BeginQuery( 
            pQueryHeap,
            type,
            index);
  }
        
  void endQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE type,
            _In_  UINT index)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> EndQuery( 
            pQueryHeap,
            type,
            index);
  }
        
  void resolveQueryData( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE type,
            _In_  UINT startIndex,
            _In_  UINT numQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 alignedDestinationBufferOffset)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ResolveQueryData( 
            pQueryHeap,
            type,
            startIndex,
            numQueries,
            pDestinationBuffer,
            alignedDestinationBufferOffset);
  }
        
  void setPredication( 
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 alignedBufferOffset,
            _In_  D3D12_PREDICATION_OP operation)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetPredication( 
            pBuffer,
            alignedBufferOffset,
            operation);
  }
        
  void setMarker( 
            UINT metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT size)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> SetMarker( 
            metadata,
            pData,
            size);
  }
        
  void beginEvent( 
            UINT metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT size)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> BeginEvent( 
            metadata,
            pData,
            size); 
  }
        
  void endEvent()
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> EndEvent();
  }
        
  void executeIndirect( 
            _In_  ID3D12CommandSignature *pCommandSignature,
            _In_  UINT maxCommandCount,
            _In_  ID3D12Resource *pArgumentBuffer,
            _In_  UINT64 argumentBufferOffset,
            _In_opt_  ID3D12Resource *pCountBuffer,
            _In_  UINT64 countBufferOffset)
  {
    ID3D12GraphicsCommandList* graphicsCommandList = getGraphicsCommandList();
    graphicsCommandList -> ExecuteIndirect( 
            pCommandSignature,
            maxCommandCount,
            pArgumentBuffer,
            argumentBufferOffset,
            pCountBuffer,
            countBufferOffset);
  }

};

}
    
