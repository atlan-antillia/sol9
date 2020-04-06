/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this context of conditions, and the following disclaimer.
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
 *  Direct3D11DeviceContext.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once

#include <sol/direct3d11/Direct3D11DeviceChild.h>

namespace SOL {

class Direct3D11DeviceContext : public Direct3D11DeviceChild {

protected:
  Direct3D11DeviceContext()
  :Direct3D11DeviceChild()
  {
  }

public:
  ~Direct3D11DeviceContext()
  {
  }

  operator ID3D11DeviceContext*()
  {
    return getDeviceContext();
  }
  
  ID3D11DeviceContext* getDeviceContext()
  {
    ID3D11DeviceContext* context = (ID3D11DeviceContext*)getIUnknown();
    if (context) {
        return context;
    } else {
      throw IException("ID3D11DeviceContext is NULL.");
    }
  }  
 
  void setVSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSSetConstantBuffers( 
            startSlot,
            numBuffers,
            ppConstantBuffers);
  }
  
  void setPSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __in ID3D11ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSSetShaderResources( 
            startSlot,
            numViews,
            ppShaderResourceViews);
  }
        
  void setPSShader( 
            __in_opt  ID3D11PixelShader *pPixelShader,
            __in ID3D11ClassInstance *const *ppClassInstances,
            UINT numClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSSetShader( 
            pPixelShader,
            ppClassInstances,
            numClassInstances);
  }
        
  void setPSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __in ID3D11SamplerState *const *ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSSetSamplers( 
            startSlot,
            numSamplers,
            ppSamplers);
  }
        
  void setVSShader( 
            __in_opt  ID3D11VertexShader *pVertexShader,
            __in  ID3D11ClassInstance *const *ppClassInstances,
            UINT  numClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSSetShader( 
            pVertexShader,
            ppClassInstances,
            numClassInstances);
  }
        
  void drawIndexed( 
            __in  UINT indexCount,
            __in  UINT startIndexLocation,
            __in  INT baseVertexLocation)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DrawIndexed( 
            indexCount,
            startIndexLocation,
            baseVertexLocation);
  }
        
  void draw( 
            __in  UINT vertexCount,
            __in  UINT startVertexLocation)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> Draw( 
            vertexCount,
            startVertexLocation);
  }
        
  void map( 
            __in  ID3D11Resource *pResource,
            __in  UINT subresource,
            __in  D3D11_MAP mapType,
            __in  UINT mapFlags,
            __out  D3D11_MAPPED_SUBRESOURCE *pMappedResource)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    HRESULT hr = context -> Map( 
                pResource,
                subresource,
                mapType,
                mapFlags,
            pMappedResource);
    if (FAILED(hr)) {
      throw IException("Failed to Map. HRESULT(0x%lx)", hr); 
    }
  }

  void unmap( 
            __in  ID3D11Resource *pResource,
            __in  UINT subresource)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> Unmap( 
            pResource,
            subresource);
  }
        
  void setPSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSSetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void setIAInputLayout( 
            __in_opt  ID3D11InputLayout *pInputLayout)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IASetInputLayout( 
            pInputLayout);
  }
        
  void setIAVertexBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppVertexBuffers,
            __in const UINT *pStrides,
            __in const UINT *pOffsets)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IASetVertexBuffers( 
              startSlot,
              numBuffers,
              ppVertexBuffers,
              pStrides,
              pOffsets);
  }
        
  void setIAIndexBuffer( 
            __in_opt  ID3D11Buffer *pIndexBuffer,
            __in  DXGI_FORMAT format,
            __in  UINT offset)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IASetIndexBuffer( 
              pIndexBuffer,
              format,
              offset);
  }
        
  void drawIndexedInstanced( 
            __in  UINT indexCountPerInstance,
            __in  UINT instanceCount,
            __in  UINT startIndexLocation,
            __in  INT baseVertexLocation,
            __in  UINT startInstanceLocation)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DrawIndexedInstanced( 
              indexCountPerInstance,
              instanceCount,
              startIndexLocation,
              baseVertexLocation,
              startInstanceLocation);
  }
        
  void drawInstanced( 
            __in  UINT vertexCountPerInstance,
            __in  UINT instanceCount,
            __in  UINT startVertexLocation,
            __in  UINT startInstanceLocation)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DrawInstanced( 
              vertexCountPerInstance,
              instanceCount,
              startVertexLocation,
              startInstanceLocation);
  }
        
  void setGSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSSetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void setGSShader( 
            __in_opt  ID3D11GeometryShader *pShader,
            __in ID3D11ClassInstance *const *ppClassInstances,
            UINT numClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSSetShader( 
              pShader,
              ppClassInstances,
              numClassInstances);
  }
        
  void setIAPrimitiveTopology( 
            __in  D3D11_PRIMITIVE_TOPOLOGY topology)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IASetPrimitiveTopology( 
            topology);
  }
        
  void setVSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __in ID3D11ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSSetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void setVSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __in ID3D11SamplerState *const *ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSSetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void begin( 
            __in  ID3D11Asynchronous *pAsync)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> Begin( 
              pAsync);
  }
        
  void end( 
            __in  ID3D11Asynchronous *pAsync)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> End(pAsync);
  }
        
  void getData( 
            __in  ID3D11Asynchronous *pAsync,
            __out void *pData,
            __in  UINT dataSize,
            __in  UINT getDataFlags)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    HRESULT hr = context -> GetData( 
              pAsync,
              pData,
              dataSize,
              getDataFlags);
    if (FAILED(hr)) {
      throw IException("Failed to GetData. HRESULT(0x%lx)", hr); 
    }
  }

  void setPredication( 
            __in_opt  ID3D11Predicate *pPredicate,
            __in  BOOL predicateValue)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> SetPredication( 
              pPredicate,
              predicateValue);
  }
        
  void setGSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __in ID3D11ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSSetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void setGSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __in ID3D11SamplerState *const *ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSSetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void setOMRenderTargets( 
            __in UINT numViews,
            __in ID3D11RenderTargetView *const *ppRenderTargetViews,
            __in_opt  ID3D11DepthStencilView *pDepthStencilView)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMSetRenderTargets( 
              numViews,
              ppRenderTargetViews,
              pDepthStencilView);
  }
        
  void setOMRenderTargetsAndUnorderedAccessViews( 
            __in UINT numRTVs,
            __in ID3D11RenderTargetView *const *ppRenderTargetViews,
            __in_opt  ID3D11DepthStencilView *pDepthStencilView,
            __in UINT uAVStartSlot,
            __in UINT numUAVs,
            __in ID3D11UnorderedAccessView *const *ppUnorderedAccessViews,
            __in const UINT *pUAVInitialCounts)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMSetRenderTargetsAndUnorderedAccessViews( 
              numRTVs,
              ppRenderTargetViews,
              pDepthStencilView,
              uAVStartSlot,
              numUAVs,
              ppUnorderedAccessViews,
              pUAVInitialCounts);
  }
        
  void setOMBlendState( 
            __in_opt  ID3D11BlendState *pBlendState,
            __in_opt  const FLOAT blendFactor[ 4 ],
            __in  UINT sampleMask)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMSetBlendState( 
              pBlendState,
              blendFactor,
              sampleMask);
  }
        
  void setOMDepthStencilState( 
            __in_opt  ID3D11DepthStencilState *pDepthStencilState,
            __in  UINT stencilRef)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMSetDepthStencilState( 
              pDepthStencilState,
              stencilRef);
  }
        
  void setSOTargets( 
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppSOTargets,
            __in const UINT *pOffsets)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> SOSetTargets( 
              numBuffers,
              ppSOTargets,
              pOffsets);
  }
        
  void drawAuto()
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DrawAuto();
  }
        
  void drawIndexedInstancedIndirect( 
            __in  ID3D11Buffer *pBufferForArgs,
            __in  UINT alignedByteOffsetForArgs)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DrawIndexedInstancedIndirect( 
              pBufferForArgs,
              alignedByteOffsetForArgs);
  }
        
  void drawInstancedIndirect( 
            __in  ID3D11Buffer *pBufferForArgs,
            __in  UINT alignedByteOffsetForArgs)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DrawInstancedIndirect( 
              pBufferForArgs,
              alignedByteOffsetForArgs);
  }
        
  void dispatch( 
            __in  UINT threadGroupCountX,
            __in  UINT threadGroupCountY,
            __in  UINT threadGroupCountZ)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> Dispatch( 
              threadGroupCountX,
              threadGroupCountY,
              threadGroupCountZ);
  }
        
  void dispatchIndirect( 
            __in  ID3D11Buffer *pBufferForArgs,
            __in  UINT alignedByteOffsetForArgs)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DispatchIndirect( 
              pBufferForArgs,
              alignedByteOffsetForArgs);
  }
        
  void setRSState( 
            __in_opt  ID3D11RasterizerState *pRasterizerState)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> RSSetState( 
              pRasterizerState);
  }
        
  void setRSViewports( 
            __in UINT numViewports,
            __in const D3D11_VIEWPORT *pViewports)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> RSSetViewports( 
              numViewports,
              pViewports);
  }
        
  void setRSScissorRects( 
            __in UINT numRects,
            __in const D3D11_RECT *pRects)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> RSSetScissorRects( 
              numRects,
              pRects);
  }
        
  void copySubresourceRegion( 
            __in  ID3D11Resource *pDstResource,
            __in  UINT dstSubresource,
            __in  UINT dstX,
            __in  UINT dstY,
            __in  UINT dstZ,
            __in  ID3D11Resource *pSrcResource,
            __in  UINT srcSubresource,
            __in_opt  const D3D11_BOX *pSrcBox)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CopySubresourceRegion( 
              pDstResource,
              dstSubresource,
              dstX,
              dstY,
              dstZ,
              pSrcResource,
              srcSubresource,
              pSrcBox);
  }
        
  void copyResource( 
            __in  ID3D11Resource *pDstResource,
            __in  ID3D11Resource *pSrcResource)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CopyResource( 
              pDstResource,
              pSrcResource);
  }
        
  void updateSubresource( 
            __in  ID3D11Resource *pDstResource,
            __in  UINT dstSubresource,
            __in_opt  const D3D11_BOX *pDstBox,
            __in  const void *pSrcData,
            __in  UINT srcRowPitch,
            __in  UINT srcDepthPitch)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> UpdateSubresource( 
              pDstResource,
              dstSubresource,
              pDstBox,
              pSrcData,
              srcRowPitch,
              srcDepthPitch);
  }
        
  void copyStructureCount( 
            __in  ID3D11Buffer *pDstBuffer,
            __in  UINT dstAlignedByteOffset,
            __in  ID3D11UnorderedAccessView *pSrcView)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CopyStructureCount( 
              pDstBuffer,
              dstAlignedByteOffset,
              pSrcView);
  }
        
  void clearRenderTargetView( 
            __in  ID3D11RenderTargetView *pRenderTargetView,
            __in  const FLOAT colorRGBA[ 4 ])
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearRenderTargetView( 
              pRenderTargetView,
              colorRGBA);
  }

  void clearUnorderedAccessViewUint( 
            __in  ID3D11UnorderedAccessView *pUnorderedAccessView,
            __in  const UINT values[ 4 ])
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearUnorderedAccessViewUint( 
              pUnorderedAccessView,
              values);
  }
        
  void clearUnorderedAccessViewFloat( 
            __in  ID3D11UnorderedAccessView *pUnorderedAccessView,
            __in  const FLOAT values[ 4 ])
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearUnorderedAccessViewFloat( 
              pUnorderedAccessView,
              values);
  }
        
  void clearDepthStencilView( 
            __in  ID3D11DepthStencilView *pDepthStencilView,
            __in INT clearFlags = D3D11_CLEAR_DEPTH, 
            __in FLOAT depth = 1.0f, 
            __in UINT8 stencil = 0)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearDepthStencilView( 
              pDepthStencilView,
              clearFlags,
              depth,
              stencil);
  }
  
//
  void clear( 
            __in  ID3D11RenderTargetView *pRenderTargetView,
            __in  const FLOAT colorRGBA[ 4 ])
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearRenderTargetView( 
              pRenderTargetView,
              colorRGBA);
  }

  void clear( 
            __in  ID3D11UnorderedAccessView *pUnorderedAccessView,
            __in  const UINT values[ 4 ])
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearUnorderedAccessViewUint( 
              pUnorderedAccessView,
              values);
  }
        
  void clear( 
            __in  ID3D11UnorderedAccessView *pUnorderedAccessView,
            __in  const FLOAT values[ 4 ])
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearUnorderedAccessViewFloat( 
              pUnorderedAccessView,
              values);
  }
        
  void clear( 
            __in  ID3D11DepthStencilView *pDepthStencilView,
            __in INT clearFlags = D3D11_CLEAR_DEPTH, 
            __in FLOAT depth = 1.0f, 
            __in UINT8 stencil = 0)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearDepthStencilView( 
              pDepthStencilView,
              clearFlags,
              depth,
              stencil);
  }
  //
  
  void generateMips( 
            __in  ID3D11ShaderResourceView *pShaderResourceView)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GenerateMips( 
              pShaderResourceView);
  }
        
  void setResourceMinLOD( 
            __in  ID3D11Resource *pResource,
            FLOAT minLOD)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> SetResourceMinLOD( 
              pResource,
              minLOD);
  }
        
  FLOAT getResourceMinLOD( 
            __in  ID3D11Resource *pResource)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GetResourceMinLOD( 
              pResource);
  }
        
  void resolveSubresource( 
            __in  ID3D11Resource *pDstResource,
            __in  UINT dstSubresource,
            __in  ID3D11Resource *pSrcResource,
            __in  UINT srcSubresource,
            __in  DXGI_FORMAT format)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ResolveSubresource( 
              pDstResource,
              dstSubresource,
              pSrcResource,
              srcSubresource,
              format);
  }
        
  void executeCommandList( 
            __in  ID3D11CommandList *pCommandList,
            BOOL restoreContextState)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ExecuteCommandList( 
              pCommandList,
              restoreContextState);
  }
        
  void setHSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __in ID3D11ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSSetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void setHSShader( 
            __in_opt  ID3D11HullShader *pHullShader,
            __in ID3D11ClassInstance *const *ppClassInstances,
            UINT numClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSSetShader( 
              pHullShader,
              ppClassInstances,
              numClassInstances);
  }
        
  void setHSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __in ID3D11SamplerState *const *ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSSetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void setHSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSSetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void setDSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __in ID3D11ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSSetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void setDSShader( 
            __in_opt  ID3D11DomainShader *pDomainShader,
            __in ID3D11ClassInstance *const *ppClassInstances,
            UINT numClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSSetShader( 
              pDomainShader,
              ppClassInstances,
              numClassInstances);
  }
        
  void setDSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __in ID3D11SamplerState *const *ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSSetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void setDSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSSetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void setCSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __in ID3D11ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSSetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void setCSUnorderedAccessViews( 
            __in UINT startSlot,
            __in UINT numUAVs,
            __in ID3D11UnorderedAccessView *const *ppUnorderedAccessViews,
            __in const UINT *pUAVInitialCounts)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSSetUnorderedAccessViews( 
              startSlot,
              numUAVs,
              ppUnorderedAccessViews,
              pUAVInitialCounts);
  }
        
  void setCSShader( 
            __in_opt  ID3D11ComputeShader *pComputeShader,
            __in ID3D11ClassInstance *const *ppClassInstances,
            UINT numClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSSetShader( 
              pComputeShader,
              ppClassInstances,
              numClassInstances);
  }
        
  void setCSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __in ID3D11SamplerState *const *ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSSetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void setCSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __in ID3D11Buffer *const *ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSSetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void getVSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __out ID3D11Buffer **ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSGetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void getPSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __out ID3D11ShaderResourceView **ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSGetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void getPSShader( 
            __out  ID3D11PixelShader **ppPixelShader,
            __out  ID3D11ClassInstance **ppClassInstances,
            __inout_opt  UINT *pNumClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSGetShader( 
              ppPixelShader,
              ppClassInstances,
              pNumClassInstances);
  }
        
  void getPSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __out ID3D11SamplerState **ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSGetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void getVSShader( 
            __out  ID3D11VertexShader **ppVertexShader,
            __out  ID3D11ClassInstance **ppClassInstances,
            __inout_opt  UINT *pNumClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSGetShader( 
              ppVertexShader,
              ppClassInstances,
              pNumClassInstances);
  }
        
  void getPSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __out ID3D11Buffer **ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> PSGetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void getIAInputLayout( 
            __out  ID3D11InputLayout **ppInputLayout)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IAGetInputLayout( 
              ppInputLayout);
  }
        
  void getIAVertexBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __out ID3D11Buffer **ppVertexBuffers,
            __out UINT *pStrides,
            __out UINT *pOffsets)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IAGetVertexBuffers( 
              startSlot,
              numBuffers,
              ppVertexBuffers,
              pStrides,
              pOffsets);
  }
        
  void getIAIndexBuffer( 
            __out_opt  ID3D11Buffer **pIndexBuffer,
            __out_opt  DXGI_FORMAT *format,
            __out_opt  UINT *offset)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IAGetIndexBuffer( 
              pIndexBuffer,
              format,
              offset);
  }
        
  void getGSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __out ID3D11Buffer **ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSGetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void getGSShader( 
            __out ID3D11GeometryShader **ppGeometryShader,
            __out ID3D11ClassInstance **ppClassInstances,
            __inout_opt  UINT *pNumClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSGetShader( 
              ppGeometryShader,
              ppClassInstances,
              pNumClassInstances);
  }
        
  void getIAPrimitiveTopology( 
            __out  D3D11_PRIMITIVE_TOPOLOGY *pTopology)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> IAGetPrimitiveTopology( 
              pTopology);
  }
        
  void getVSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __out ID3D11ShaderResourceView **ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSGetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void getVSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __out ID3D11SamplerState **ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> VSGetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void getPredication( 
            __out_opt  ID3D11Predicate **ppPredicate,
            __out_opt  BOOL *pPredicateValue)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GetPredication( 
              ppPredicate,
              pPredicateValue);
  }
        
  void getGSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __out ID3D11ShaderResourceView **ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSGetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void getGSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __out ID3D11SamplerState **ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> GSGetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void getOMRenderTargets( 
            __in UINT numViews,
            __out ID3D11RenderTargetView **ppRenderTargetViews,
            __out_opt  ID3D11DepthStencilView **ppDepthStencilView)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMGetRenderTargets( 
              numViews,
              ppRenderTargetViews,
              ppDepthStencilView);
  }
        
  void getOMRenderTargetsAndUnorderedAccessViews( 
            __in UINT numRTVs,
            __out ID3D11RenderTargetView **ppRenderTargetViews,
            __out_opt ID3D11DepthStencilView **ppDepthStencilView,
            __in UINT uAVStartSlot,
            __in UINT numUAVs,
            __out ID3D11UnorderedAccessView **ppUnorderedAccessViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMGetRenderTargetsAndUnorderedAccessViews( 
              numRTVs,
              ppRenderTargetViews,
              ppDepthStencilView,
              uAVStartSlot,
              numUAVs,
              ppUnorderedAccessViews);
  }
        
  void getOMBlendState( 
            __out_opt  ID3D11BlendState **ppBlendState,
            __out_opt  FLOAT blendFactor[ 4 ],
            __out_opt  UINT *pSampleMask)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMGetBlendState( 
              ppBlendState,
              blendFactor,
              pSampleMask);
  }
        
  void getOMDepthStencilState( 
            __out_opt  ID3D11DepthStencilState **ppDepthStencilState,
            __out_opt  UINT *pStencilRef)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> OMGetDepthStencilState( 
            ppDepthStencilState,
            pStencilRef);
  }
        
  void getSOTargets( 
            __in UINT numBuffers,
            __out ID3D11Buffer **ppSOTargets)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> SOGetTargets( 
              numBuffers,
              ppSOTargets);
  }
        
  void getRSState( 
            __out  ID3D11RasterizerState **ppRasterizerState)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> RSGetState( 
              ppRasterizerState);
  }
        
  void getRSViewports( 
            __inout  UINT *pNumViewports,
            __out  D3D11_VIEWPORT *pViewports)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> RSGetViewports( 
              pNumViewports,
              pViewports);
  }
        
  void getRSScissorRects( 
            __inout  UINT *pNumRects,
            __out  D3D11_RECT *pRects)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> RSGetScissorRects( 
              pNumRects,
              pRects);
  }
        
  void getHSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __out ID3D11ShaderResourceView **ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSGetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void getHSShader( 
            __out  ID3D11HullShader **ppHullShader,
            __out  ID3D11ClassInstance **ppClassInstances,
            __inout_opt  UINT *pNumClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSGetShader( 
              ppHullShader,
              ppClassInstances,
              pNumClassInstances);
  }
        
  void getHSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __out ID3D11SamplerState **ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSGetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void getHSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __out  ID3D11Buffer **ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> HSGetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void getDSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __out ID3D11ShaderResourceView **ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSGetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void getDSShader( 
            __out  ID3D11DomainShader **ppDomainShader,
            __out  ID3D11ClassInstance **ppClassInstances,
            __inout_opt  UINT *pNumClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSGetShader( 
              ppDomainShader,
              ppClassInstances,
              pNumClassInstances);
  }
        
  void getDSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __out ID3D11SamplerState **ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSGetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void getDSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __out ID3D11Buffer **ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> DSGetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void getCSShaderResources( 
            __in UINT startSlot,
            __in UINT numViews,
            __out ID3D11ShaderResourceView **ppShaderResourceViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSGetShaderResources( 
              startSlot,
              numViews,
              ppShaderResourceViews);
  }
        
  void getCSUnorderedAccessViews( 
            __in UINT startSlot,
            __in UINT numUAVs,
            __out ID3D11UnorderedAccessView **ppUnorderedAccessViews)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSGetUnorderedAccessViews( 
              startSlot,
              numUAVs,
              ppUnorderedAccessViews);
  }
        
  void getCSShader( 
            __out  ID3D11ComputeShader **ppComputeShader,
            __out  ID3D11ClassInstance **ppClassInstances,
            __inout_opt  UINT *pNumClassInstances)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSGetShader( 
              ppComputeShader,
              ppClassInstances,
              pNumClassInstances);
  }
        
  void getCSSamplers( 
            __in UINT startSlot,
            __in UINT numSamplers,
            __out ID3D11SamplerState **ppSamplers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSGetSamplers( 
              startSlot,
              numSamplers,
              ppSamplers);
  }
        
  void getCSConstantBuffers( 
            __in UINT startSlot,
            __in UINT numBuffers,
            __out ID3D11Buffer **ppConstantBuffers)
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> CSGetConstantBuffers( 
              startSlot,
              numBuffers,
              ppConstantBuffers);
  }
        
  void clearState()
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> ClearState();
  }
        
  void flush()
  {
    ID3D11DeviceContext* context = getDeviceContext();
    context -> Flush();
  }
        
  D3D11_DEVICE_CONTEXT_TYPE getType()
  {
    ID3D11DeviceContext* context = getDeviceContext();
    return context -> GetType();
  }
        
  UINT getContextFlags()
  {
    ID3D11DeviceContext* context = getDeviceContext();
    return context -> GetContextFlags();
  }
        
  void finishCommandList( 
            BOOL restoreDeferredContextState,
            __out_opt  ID3D11CommandList **ppCommandList)
        
  {
    ID3D11DeviceContext* context = getDeviceContext();
    HRESULT hr = context -> FinishCommandList( 
              restoreDeferredContextState,
              ppCommandList);
    if (FAILED(hr)) {
      throw IException("Failed to FinishCommandList. HRESULT(0x%lx)", hr); 
    }
  }

};

}

