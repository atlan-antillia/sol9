/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Direct3D10Device.h
 *
 *****************************************************************************/

#pragma once

#include <sol/com/ComIUnknown.h>
#include <sol/Exception.h>

#include <d3d10_1.h>
#include <d3dx10.h>
#include <dxgi.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d10.lib")
#pragma comment(lib,"d3dx10.lib")

namespace SOL {

class Direct3D10Device :public ComIUnknown {

public:
  Direct3D10Device(
    __in_opt  IDXGIAdapter*      adapter = NULL,
    __in_opt  HMODULE            hmodule = NULL,
    __in_opt  UINT               flags   = 0,
    __in_opt UINT               sdkVersion = D3D10_SDK_VERSION)
  :ComIUnknown()
  {
    D3D10_DRIVER_TYPE driverTypes[] ={
      D3D10_DRIVER_TYPE_HARDWARE,
      D3D10_DRIVER_TYPE_REFERENCE,
    };
    
    ID3D10Device* device = NULL;
    
    HRESULT hr = E_FAIL;
    for(int i = 0; i<CountOf(driverTypes); i++) {
       hr = D3D10CreateDevice(
          adapter,
          driverTypes[i],
          hmodule,
          flags,
          sdkVersion,
          &device);
      if (SUCCEEDED(hr))  {
        set(device);
        break;
      }
    }
    if( FAILED( hr ) )  {
      throw IException("Failed to D3D10CreateDevice. HRESULT(0x%lx)", hr);
    }
  }

public:
  Direct3D10Device(IDXGIAdapter   *pAdapter,
    D3D10_DRIVER_TYPE    driverType,
    HMODULE              software,
    UINT                 flags,
    UINT                 sdkVersion,
    DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
    IDXGISwapChain      **ppSwapChain)
  :ComIUnknown()
  {
    ID3D10Device* device = NULL;
    HRESULT hr = D3D10CreateDeviceAndSwapChain(
         pAdapter,
        driverType,
        software,
        flags,
        sdkVersion,
        pSwapChainDesc,
         ppSwapChain,
         &device);
    
    if (SUCCEEDED(hr)) {
      set(device);
    } else {
      throw IException("Failed to D3D10CreateDeviceAndSwapChain. HRESULT(0x%lx)", hr);
    }
  }
  
public:
  Direct3D10Device(
    __in  DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
    __out IDXGISwapChain       **ppSwapChain)

  :ComIUnknown()
  {
    ID3D10Device* device = NULL;
    HRESULT hr = D3D10CreateDeviceAndSwapChain(
         NULL, 
        D3D10_DRIVER_TYPE_HARDWARE,
        NULL, 
        0, 
        D3D10_SDK_VERSION, 
        pSwapChainDesc, 
         ppSwapChain, 
        &device);
    
    if (SUCCEEDED(hr)) {
      set(device);
    } else {
      throw IException("Failed to D3D10CreateDeviceAndSwapChain. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct3D10Device()
  {
  }
 
  operator ID3D10Device*()
  {
    return getDevice();
  }

  ID3D10Device* getDevice()
  {
    ID3D10Device* device = (ID3D10Device*)getIUnknown();
    if (device) {
        return device;
    } else {
      throw IException("ID3D10Device is NULL.");
    }
  }

public:
  void setVSConstantBuffers( 
    __in  UINT startSlot,
    __in  UINT numBuffers,
    __in  ID3D10Buffer *const *ppConstantBuffers)
  {
    ID3D10Device* device = getDevice();
    device -> VSSetConstantBuffers( 
        startSlot,
        numBuffers,
        ppConstantBuffers);
  }  

  void setPSShaderResources( 
    __in  UINT startSlot,
    __in  UINT numViews,
    __in  ID3D10ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D10Device* device = getDevice();
    device -> PSSetShaderResources( 
        startSlot,
        numViews,
        ppShaderResourceViews);
  }  
  
  void setPSShader( 
    __in_opt  ID3D10PixelShader *pPixelShader)
  {
    ID3D10Device* device = getDevice();
    device -> PSSetShader( 
        pPixelShader);
  }  
  
  void setPSSamplers( 
    __in  UINT startSlot,
    __in  UINT numSamplers,
    __in  ID3D10SamplerState *const *ppSamplers)
  {
    ID3D10Device* device = getDevice();
    device -> PSSetSamplers( 
        startSlot,
        numSamplers,
        ppSamplers);
  }  
  
  void setVSShader( 
    __in_opt  ID3D10VertexShader *pVertexShader)
  {
    ID3D10Device* device = getDevice();
    device -> VSSetShader( 
        pVertexShader);
  }  
  
  void drawIndexed( 
    __in  UINT indexCount,
    __in  UINT startIndexLocation,
    __in  INT baseVertexLocation)
  {
    ID3D10Device* device = getDevice();
    device -> DrawIndexed( 
        indexCount,
        startIndexLocation,
        baseVertexLocation);
  }  
  
  void draw( 
    __in  UINT vertexCount,
    __in  UINT startVertexLocation)
  {
    ID3D10Device* device = getDevice();
    device -> Draw( 
        vertexCount,
        startVertexLocation);
  }  
  
  void setPSConstantBuffers( 
    __in  UINT startSlot,
    __in  UINT numBuffers,
    __in  ID3D10Buffer *const *ppConstantBuffers)
  {
    ID3D10Device* device = getDevice();
    device -> PSSetConstantBuffers( 
        startSlot,
        numBuffers,
        ppConstantBuffers);
  }  
  
  void setIAInputLayout( 
    __in_opt  ID3D10InputLayout *pInputLayout)
  {
    ID3D10Device* device = getDevice();
    device -> IASetInputLayout( 
        pInputLayout);
  }  
  
  void setIAVertexBuffers( 
    __in  UINT startSlot,
    __in  UINT numBuffers,
    __in  ID3D10Buffer *const *ppVertexBuffers,
    __in  const UINT *pStrides,
    __in  const UINT *pOffsets)
  {
    ID3D10Device* device = getDevice();
    device -> IASetVertexBuffers( 
        startSlot,
        numBuffers,
        ppVertexBuffers,
        pStrides,
        pOffsets);
  }  
  
  void setIAIndexBuffer( 
    __in_opt  ID3D10Buffer *pIndexBuffer,
    __in  DXGI_FORMAT format,
    __in  UINT offset)
  {
    ID3D10Device* device = getDevice();
    device -> IASetIndexBuffer( 
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
    ID3D10Device* device = getDevice();
    device -> DrawIndexedInstanced( 
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
    ID3D10Device* device = getDevice();
    device -> DrawInstanced( 
        vertexCountPerInstance,
        instanceCount,
        startVertexLocation,
        startInstanceLocation);
  }  
  
  void setGSConstantBuffers( 
    __in  UINT startSlot,
    __in  UINT numBuffers,
    __in  ID3D10Buffer *const *ppConstantBuffers)
  {
    ID3D10Device* device = getDevice();
    device -> GSSetConstantBuffers( 
        startSlot,
        numBuffers,
        ppConstantBuffers);
  }  
  
  void setGSShader( 
    __in  ID3D10GeometryShader *pShader)
  {
    ID3D10Device* device = getDevice();
    device -> GSSetShader( 
        pShader);
  }  
  
  void setIAPrimitiveTopology( 
    __in  D3D10_PRIMITIVE_TOPOLOGY topology)
  {
    ID3D10Device* device = getDevice();
    device -> IASetPrimitiveTopology( 
        topology);
  }  
  
  void setVSShaderResources( 
    __in  UINT startSlot,
    __in  UINT numViews,
    __in  ID3D10ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D10Device* device = getDevice();
    device -> VSSetShaderResources( 
        startSlot,
        numViews,
        ppShaderResourceViews);
  }  
  
  void setVSSamplers( 
    __in  UINT startSlot,
    __in  UINT numSamplers,
    __in  ID3D10SamplerState *const *ppSamplers)
  {
    ID3D10Device* device = getDevice();
    device -> VSSetSamplers( 
        startSlot,
        numSamplers,
        ppSamplers);
  }  
  
  void setPredication( 
    __in  ID3D10Predicate *pPredicate,
    __in  BOOL predicateValue)
  {
    ID3D10Device* device = getDevice();
    device -> SetPredication( 
        pPredicate,
        predicateValue);
  }  
  
  void setGSShaderResources( 
    __in  UINT startSlot,
    __in  UINT numViews,
    __in  ID3D10ShaderResourceView *const *ppShaderResourceViews)
  {
    ID3D10Device* device = getDevice();
    device ->  GSSetShaderResources( 
        startSlot,
        numViews,
        ppShaderResourceViews);
  }  
  
  void setGSSamplers( 
    __in  UINT startSlot,
    __in  UINT numSamplers,
    __in  ID3D10SamplerState *const *ppSamplers)
  {
    ID3D10Device* device = getDevice();
    device -> GSSetSamplers( 
        startSlot,
        numSamplers,
        ppSamplers);
  }  
  
  void setOMRenderTargets( 
    __in  UINT numViews,
    __in  ID3D10RenderTargetView *const *ppRenderTargetViews,
    __in  ID3D10DepthStencilView *pDepthStencilView)
  {
    ID3D10Device* device = getDevice();
    device -> OMSetRenderTargets( 
        numViews,
        ppRenderTargetViews,
        pDepthStencilView);
  }  
  
  void setOMBlendState( 
    __in_opt  ID3D10BlendState *pBlendState,
    __in  const FLOAT blendFactor[ 4 ],
    __in  UINT sampleMask)
  {
    ID3D10Device* device = getDevice();
    device -> OMSetBlendState( 
        pBlendState,
        blendFactor,
        sampleMask);
  }  
  
  void setOMDepthStencilState( 
    __in  ID3D10DepthStencilState *pDepthStencilState,
    __in  UINT stencilRef)
  {
    ID3D10Device* device = getDevice();
    device -> OMSetDepthStencilState( 
        pDepthStencilState,
        stencilRef);
  }  
  
  void setSOTargets( 
    __in  UINT numBuffers,
    __in  ID3D10Buffer *const *ppSOTargets,
    __in  const UINT *pOffsets)
  {
    ID3D10Device* device = getDevice();
    device -> SOSetTargets( 
        numBuffers,
        ppSOTargets,
        pOffsets);
  }  
  
  void drawAuto()
  {
    ID3D10Device* device = getDevice();
    device -> DrawAuto();
  }  
  
  void setRSState( 
    __in  ID3D10RasterizerState *pRasterizerState)
  {
    ID3D10Device* device = getDevice();
    device -> RSSetState( 
        pRasterizerState);
  }  
  
  void setRSViewports( 
    __in  UINT numViewports,
    __in  const D3D10_VIEWPORT *pViewports)
  {
    ID3D10Device* device = getDevice();
    device -> RSSetViewports( 
        numViewports,
        pViewports);
  }  
  
  void setRSScissorRects( 
    __in  UINT numRects,
    __in  const D3D10_RECT *pRects)
  {
    ID3D10Device* device = getDevice();
    device -> RSSetScissorRects( 
        numRects,
        pRects);
  }  
  
  void copySubresourceRegion( 
    __in  ID3D10Resource *pDstResource,
    __in  UINT dstSubresource,
    __in  UINT dstX,
    __in  UINT dstY,
    __in  UINT dstZ,
    __in  ID3D10Resource *pSrcResource,
    __in  UINT srcSubresource,
    __in  const D3D10_BOX *pSrcBox)
  {
    ID3D10Device* device = getDevice();
    device -> CopySubresourceRegion( 
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
    __in  ID3D10Resource *pDstResource,
    __in  ID3D10Resource *pSrcResource)
  {
    ID3D10Device* device = getDevice();
    device -> CopyResource( 
        pDstResource,
        pSrcResource);
  }  
  
  void updateSubresource( 
    __in  ID3D10Resource *pDstResource,
    __in  UINT dstSubresource,
    __in_opt  const D3D10_BOX *pDstBox,
    __in  const void *pSrcData,
    __in  UINT srcRowPitch,
    __in  UINT srcDepthPitch)
  {
    ID3D10Device* device = getDevice();
    device -> UpdateSubresource( 
        pDstResource,
        dstSubresource,
        pDstBox,
        pSrcData,
        srcRowPitch,
        srcDepthPitch);
  }  

  void clear( 
    __in  ID3D10RenderTargetView *pRenderTargetView,
    __in  const FLOAT colorRGBA[ 4 ])
  {
    ID3D10Device* device = getDevice();
    device -> ClearRenderTargetView( 
        pRenderTargetView,
        colorRGBA);
  }  
  
  void clear( 
    __in  ID3D10DepthStencilView *pDepthStencilView,
    __in  UINT clearFlags,
    __in  FLOAT depth,
    __in  UINT8 stencil)
  {
    ID3D10Device* device = getDevice();
    device -> ClearDepthStencilView( 
        pDepthStencilView,
        clearFlags,
        depth,
        stencil);
  }  

  void clearRenderTargetView( 
    __in  ID3D10RenderTargetView *pRenderTargetView,
    __in  const FLOAT colorRGBA[ 4 ])
  {
    ID3D10Device* device = getDevice();
    device -> ClearRenderTargetView( 
        pRenderTargetView,
        colorRGBA);
  }  
  
  void clearDepthStencilView( 
    __in  ID3D10DepthStencilView *pDepthStencilView,
    __in  UINT clearFlags,
    __in  FLOAT depth,
    __in  UINT8 stencil)
  {
    ID3D10Device* device = getDevice();
    device -> ClearDepthStencilView( 
        pDepthStencilView,
        clearFlags,
        depth,
        stencil);
  }  
  
  void generateMips( 
    __in  ID3D10ShaderResourceView *pShaderResourceView)
  {
    ID3D10Device* device = getDevice();
    device -> GenerateMips( 
        pShaderResourceView);
  }  
  
  void resolveSubresource( 
    __in  ID3D10Resource *pDstResource,
    __in  UINT dstSubresource,
    __in  ID3D10Resource *pSrcResource,
    __in  UINT srcSubresource,
    __in  DXGI_FORMAT Format)
  {
    ID3D10Device* device = getDevice();
    device -> ResolveSubresource( 
        pDstResource,
        dstSubresource,
        pSrcResource,
        srcSubresource,
        Format);
  }  
  
  void getConstantBuffers( 
    __in  UINT startSlot,
    __in  UINT numBuffers,
    __out  ID3D10Buffer **ppConstantBuffers)
  {
    ID3D10Device* device = getDevice();
    device -> VSGetConstantBuffers( 
        startSlot,
        numBuffers,
        ppConstantBuffers);
  }  
  
  void getShaderResources( 
    __in  UINT startSlot,
    __in  UINT numViews,
    __out  ID3D10ShaderResourceView **ppShaderResourceViews)
  {
    ID3D10Device* device = getDevice();
    device -> PSGetShaderResources( 
        startSlot,
        numViews,
        ppShaderResourceViews);
  }  
  
  void getPSShader( 
    __out  ID3D10PixelShader **ppPixelShader)
  {
    ID3D10Device* device = getDevice();
    device -> PSGetShader( 
        ppPixelShader);
  }  
  
  void getPSSamplers( 
    __in  UINT startSlot,
    __in  UINT numSamplers,
    __out  ID3D10SamplerState **ppSamplers)
  {
    ID3D10Device* device = getDevice();
    device -> PSGetSamplers( 
        startSlot,
        numSamplers,
        ppSamplers);
  }  
  
  void getVSShader( 
    __out  ID3D10VertexShader **ppVertexShader)
  {
    ID3D10Device* device = getDevice();
    device -> VSGetShader( 
        ppVertexShader);
  }  
  
  void getPSConstantBuffers( 
    __in  UINT startSlot,
    __in  UINT numBuffers,
    __out ID3D10Buffer **ppConstantBuffers)
  {
    ID3D10Device* device = getDevice();
    device -> PSGetConstantBuffers( 
        startSlot,
        numBuffers,
        ppConstantBuffers);
  }  
  
  void getIAInputLayout( 
    __out  ID3D10InputLayout **ppInputLayout)
  {
    ID3D10Device* device = getDevice();
    device -> IAGetInputLayout( 
        ppInputLayout);
  }  
  
  void getIAVertexBuffers( 
    __in UINT startSlot,
    __in  UINT numBuffers,
    __in  ID3D10Buffer **ppVertexBuffers,

    __out UINT *pStrides,
    __out UINT *pOffsets)
  {
    ID3D10Device* device = getDevice();
    device -> IAGetVertexBuffers( 
        startSlot,
        numBuffers,
        ppVertexBuffers,
        pStrides,
        pOffsets);
  }  
  
  void getIAIndexBuffer( 
    __out_opt  ID3D10Buffer **pIndexBuffer,
    __out_opt  DXGI_FORMAT *format,
    __out_opt  UINT *offset)
  {
    ID3D10Device* device = getDevice();
    device -> IAGetIndexBuffer( 
        pIndexBuffer,
        format,
        offset);
  }  
  
  void getGSConstantBuffers( 
    __in  UINT startSlot,
    __in  UINT numBuffers,
    __out  ID3D10Buffer **ppConstantBuffers)
  {
    ID3D10Device* device = getDevice();
    device -> GSGetConstantBuffers( 
        startSlot,
        numBuffers,
        ppConstantBuffers);
  }  
  
  void getGSShader( 
    __out  ID3D10GeometryShader **ppGeometryShader)
  {
    ID3D10Device* device = getDevice();
    device -> GSGetShader( 
        ppGeometryShader);
  }  
  
  void getIAPrimitiveTopology( 
    __out  D3D10_PRIMITIVE_TOPOLOGY *pTopology)
  {
    ID3D10Device* device = getDevice();
    device -> IAGetPrimitiveTopology( 
        pTopology);
  }  
  
  void getVSShaderResources( 
    __in  UINT startSlot,
    __in  UINT numViews,
    __out ID3D10ShaderResourceView **ppShaderResourceViews)
  {
    ID3D10Device* device = getDevice();
    device -> VSGetShaderResources( 
        startSlot,
        numViews,
        ppShaderResourceViews);
  }  
  
  void getVSSamplers( 
    __in  UINT startSlot,
    __in  UINT numSamplers,
    __out ID3D10SamplerState **ppSamplers)
  {
    ID3D10Device* device = getDevice();
    device -> VSGetSamplers( 
        startSlot,
        numSamplers,
        ppSamplers);
  }  
  
  void getPredication( 
    __out_opt  ID3D10Predicate **ppPredicate,
    __out_opt  BOOL *pPredicateValue)
  {
    ID3D10Device* device = getDevice();
    device -> GetPredication( 
        ppPredicate,
        pPredicateValue);
  }  
  
  void getGSShaderResources( 
    __in  UINT startSlot,
    __in  UINT numViews,
    __out  ID3D10ShaderResourceView **ppShaderResourceViews)
  {
    ID3D10Device* device = getDevice();
    device -> GSGetShaderResources( 
        startSlot,
        numViews,
        ppShaderResourceViews);
  }  
  
  void getGSSamplers( 
    __in  UINT startSlot,
    __in UINT numSamplers,
    __out  ID3D10SamplerState **ppSamplers)
  {
    ID3D10Device* device = getDevice();
    device -> GSGetSamplers( 
        startSlot,
        numSamplers,
        ppSamplers);
  }  
  
  void getOMRenderTargets( 
    __in UINT numViews,
    __out  ID3D10RenderTargetView **ppRenderTargetViews,
    __out_opt  ID3D10DepthStencilView **ppDepthStencilView)
  {
    ID3D10Device* device = getDevice();
    device -> OMGetRenderTargets( 
        numViews,
        ppRenderTargetViews,
        ppDepthStencilView);
  }  
  
  void getOMBlendState( 
    __out_opt  ID3D10BlendState **ppBlendState,
    __out_opt  FLOAT blendFactor[ 4 ],
    __out_opt  UINT *pSampleMask)
  {
    ID3D10Device* device = getDevice();
    device -> OMGetBlendState( 
        ppBlendState,
        blendFactor,
        pSampleMask);
  }  
  
  void getOMDepthStencilState( 
    __out_opt  ID3D10DepthStencilState **ppDepthStencilState,
    __out_opt  UINT *pStencilRef)
  {
    ID3D10Device* device = getDevice();
    device -> OMGetDepthStencilState( 
        ppDepthStencilState,
        pStencilRef);
  }  
  
  void getSOTargets( 
    __in  UINT numBuffers,
    __out  ID3D10Buffer **ppSOTargets,
    __out  UINT *pOffsets)
  {
    ID3D10Device* device = getDevice();
    device -> SOGetTargets( 
        numBuffers,
        ppSOTargets,
        pOffsets);
  }  
  
  void getRSState( 
    __out  ID3D10RasterizerState **ppRasterizerState)
  {
    ID3D10Device* device = getDevice();
    device -> RSGetState( 
        ppRasterizerState);
  }  
  
  void getRSViewports( 
    __inout   UINT *numViewports,
    __out D3D10_VIEWPORT *pViewports)
  {
    ID3D10Device* device = getDevice();
    device -> RSGetViewports( 
        numViewports,
        pViewports);
  }  
  
  void getRSScissorRects( 
    __inout    UINT *numRects,
    __out D3D10_RECT *pRects)
  {
    ID3D10Device* device = getDevice();
    device -> RSGetScissorRects( 
        numRects,
        pRects);
  }  
  
  void  getDeviceRemovedReason()
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> GetDeviceRemovedReason();
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr)
    }
  }  
  
  void  setExceptionMode( 
    UINT raiseFlags)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> SetExceptionMode( 
        raiseFlags);
    if (FAILED(hr)) {
      throw IException("Failed to SetExceptionMode. HRESULT(0x%lx)", hr)
    }
  }  
  
  UINT getExceptionMode()
  {
    ID3D10Device* device = getDevice();
    return device -> GetExceptionMode();
  }  
  
  void  getPrivateData( 
    __in  REFGUID guid,
    __inout  UINT *pDataSize,
    __out void *pData)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> GetPrivateData( 
        guid,
        pDataSize,
        pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetPrivateData. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  setPrivateData( 
    __in  REFGUID guid,
    __in  UINT dataSize,
    __in  const void *pData)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> SetPrivateData( 
        guid,
        dataSize,
        pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateData. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  setPrivateDataInterface( 
    __in  REFGUID guid,
    __in_opt  const IUnknown *pData)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> SetPrivateDataInterface( 
        guid,
        pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateDataInterface. HRESULT(0x%lx)", hr)
    }
  }  
  
  void clearState()
  {
    ID3D10Device* device = getDevice();
    device -> ClearState();
  }  
  
  void flush()
  {
    ID3D10Device* device = getDevice();
    device -> Flush();
  }  
  
 HRESULT  createBuffer( 
    __in  const D3D10_BUFFER_DESC *pDesc,
    __in_opt  const D3D10_SUBRESOURCE_DATA *pInitialData,
    __out_opt  ID3D10Buffer **ppBuffer)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateBuffer( 
        pDesc,
        pInitialData,
        ppBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBuffer. HRESULT(0x%lx)", hr)
    }
  }  
  
  void   createTexture1D( 
    __in  const D3D10_TEXTURE1D_DESC *pDesc,
    __in  const D3D10_SUBRESOURCE_DATA *pInitialData,
    __out  ID3D10Texture1D **ppTexture1D)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateTexture1D( 
        pDesc,
        pInitialData,
        ppTexture1D);
    if (FAILED(hr)) {
      throw IException("Failed to CreateTexture1D. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createTexture2D( 
    __in  const D3D10_TEXTURE2D_DESC *pDesc,
    __in  const D3D10_SUBRESOURCE_DATA *pInitialData,
    __out  ID3D10Texture2D **ppTexture2D)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateTexture2D( 
        pDesc,
        pInitialData,
        ppTexture2D);
    if (FAILED(hr)) {
      throw IException("Failed to CreateTexture2D. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createTexture3D( 
    __in  const D3D10_TEXTURE3D_DESC *pDesc,
    __in  const D3D10_SUBRESOURCE_DATA *pInitialData,
    __out  ID3D10Texture3D **ppTexture3D)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateTexture3D( 
        pDesc,
        pInitialData,
        ppTexture3D);
    if (FAILED(hr)) {
      throw IException("Failed to CreateTexture3D. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createShaderResourceView( 
    __in  ID3D10Resource *pResource,
    __in_opt  const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
    __out_opt  ID3D10ShaderResourceView **ppSRView)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateShaderResourceView( 
        pResource,
        pDesc,
        ppSRView);
    if (FAILED(hr)) {
      throw IException("Failed to CreateShaderResourceView. HRESULT(0x%lx)", hr)
    }
  }  
  
   void  createRenderTargetView( 
    __in  ID3D10Resource *pResource,
    __in_opt  const D3D10_RENDER_TARGET_VIEW_DESC *pDesc,
    __out_opt  ID3D10RenderTargetView **ppRTView)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateRenderTargetView( 
        pResource,
        pDesc,
        ppRTView);
    if (FAILED(hr)) {
      throw IException("Failed to CreateRenderTargetView. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createDepthStencilView( 
    __in  ID3D10Resource *pResource,
    __in_opt  const D3D10_DEPTH_STENCIL_VIEW_DESC *pDesc,
    __out_opt  ID3D10DepthStencilView **ppDepthStencilView)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateDepthStencilView( 
        pResource,
        pDesc,
        ppDepthStencilView) ;
    if (FAILED(hr)) {
      throw IException("Failed to CreateDepthStencilView. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createInputLayout( 
    __in  const D3D10_INPUT_ELEMENT_DESC *pInputElementDescs,
    __in  UINT numElements,
    __in  const void *pShaderBytecodeWithInputSignature,
    __in  SIZE_T bytecodeLength,
    __out_opt  ID3D10InputLayout **ppInputLayout)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateInputLayout( 
        pInputElementDescs,
        numElements,
        pShaderBytecodeWithInputSignature,
        bytecodeLength,
        ppInputLayout);
    if (FAILED(hr)) {
      throw IException("Failed to CreateInputLayout. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createVertexShader( 
    __in  const void *pShaderBytecode,
    __in  SIZE_T bytecodeLength,
    __out_opt  ID3D10VertexShader **ppVertexShader)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateVertexShader( 
        pShaderBytecode,
        bytecodeLength,
        ppVertexShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateVertexShader. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createGeometryShader( 
    __in  const void *pShaderBytecode,
    __in  SIZE_T bytecodeLength,
    __out_opt  ID3D10GeometryShader **ppGeometryShader)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateGeometryShader( 
        pShaderBytecode,
        bytecodeLength,
        ppGeometryShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateGeometryShader. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createGeometryShaderWithStreamOutput( 
    __in  const void *pShaderBytecode,
    __in  SIZE_T bytecodeLength,
    __in  const D3D10_SO_DECLARATION_ENTRY *pSODeclaration,
    __in  UINT numEntries,
    __in  UINT outputStreamStride,
    __out_opt  ID3D10GeometryShader **ppGeometryShader)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateGeometryShaderWithStreamOutput( 
        pShaderBytecode,
        bytecodeLength,
        pSODeclaration,
        numEntries,
        outputStreamStride,
        ppGeometryShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateGeometryShaderWithStreamOutput. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createPixelShader( 
    __in  const void *pShaderBytecode,
    __in  SIZE_T bytecodeLength,
    __out_opt  ID3D10PixelShader **ppPixelShader)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreatePixelShader( 
        pShaderBytecode,
        bytecodeLength,
        ppPixelShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreatePixelShader. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createBlendState( 
    __in  const D3D10_BLEND_DESC *pBlendStateDesc,
    __out_opt  ID3D10BlendState **ppBlendState)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateBlendState( 
        pBlendStateDesc,
        ppBlendState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBlendState. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createDepthStencilState( 
    __in  const D3D10_DEPTH_STENCIL_DESC *pDepthStencilDesc,
    __out_opt  ID3D10DepthStencilState **ppDepthStencilState)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateDepthStencilState( 
        pDepthStencilDesc,
        ppDepthStencilState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDepthStencilState. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createRasterizerState( 
    __in  const D3D10_RASTERIZER_DESC *pRasterizerDesc,
    __out_opt  ID3D10RasterizerState **ppRasterizerState)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateRasterizerState( 
        pRasterizerDesc,
        ppRasterizerState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateRasterizerState. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createSamplerState( 
    __in  const D3D10_SAMPLER_DESC *pSamplerDesc,
    __out_opt  ID3D10SamplerState **ppSamplerState)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateSamplerState( 
        pSamplerDesc,
        ppSamplerState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateSamplerState. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createQuery( 
    __in  const D3D10_QUERY_DESC *pQueryDesc,
    __out_opt  ID3D10Query **ppQuery)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateQuery( 
        pQueryDesc,
        ppQuery);
    if (FAILED(hr)) {
      throw IException("Failed to CreateQuery. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createPredicate( 
    __in  const D3D10_QUERY_DESC *pPredicateDesc,
    __out_opt  ID3D10Predicate **ppPredicate)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreatePredicate( 
        pPredicateDesc,
        ppPredicate);
    if (FAILED(hr)) {
      throw IException("Failed to CreatePredicate. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  createCounter( 
    __in  const D3D10_COUNTER_DESC *pCounterDesc,
    __out_opt  ID3D10Counter **ppCounter)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CreateCounter( 
        pCounterDesc,
        ppCounter);
    if (FAILED(hr)) {
      throw IException("Failed to CreateCounter. HRESULT(0x%lx)", hr)
    }
  }  
  
  void  checkFormatSupport( 
    __in  DXGI_FORMAT Format,
    __out  UINT *pFormatSupport)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CheckFormatSupport( 
        Format,
        pFormatSupport);
    if (FAILED(hr)) {
      throw IException("Failed to CheckFormatSupport. HRESULT(0x%lx)", hr)
    }
  }  
  
  void   checkMultisampleQualityLevels( 
    __in  DXGI_FORMAT format,
    __in  UINT sampleCount,
    __out  UINT *pNumQualityLevels)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CheckMultisampleQualityLevels( 
        format,
        sampleCount,
        pNumQualityLevels);
    if (FAILED(hr)) {
      throw IException("Failed to CheckMultisampleQualityLevels. HRESULT(0x%lx)", hr)
    }
  }  
  
  void checkCounterInfo( 
    __out  D3D10_COUNTER_INFO *pCounterInfo)
  {
    ID3D10Device* device = getDevice();
    device -> CheckCounterInfo( 
        pCounterInfo);
  }  
  
  void  checkCounter( 
    __in  const D3D10_COUNTER_DESC *pDesc,
    __out  D3D10_COUNTER_TYPE *pType,
    __out  UINT *pActiveCounters,
    __out  LPSTR szName,
    __inout_opt  UINT *pNameLength,
    __out  LPSTR szUnits,
    __inout_opt  UINT *pUnitsLength,
    __out  LPSTR szDescription,
    __inout_opt  UINT *pDescriptionLength)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> CheckCounter( 
        pDesc,
        pType,
        pActiveCounters,
        szName,
        pNameLength,
        szUnits,
        pUnitsLength,
        szDescription,
        pDescriptionLength);
    if (FAILED(hr)) {
      throw IException("Failed to CheckCounter. HRESULT(0x%lx)", hr)
    }
  }  
  
  UINT  getCreationFlags()
  {
    ID3D10Device* device = getDevice();
    return device -> GetCreationFlags();
  }  
  
  void  openSharedResource( 
    __in  HANDLE hResource,
    __in  REFIID returnedInterface,
    __out_opt  void **ppResource)
  {
    ID3D10Device* device = getDevice();
    HRESULT hr = device -> OpenSharedResource( 
        hResource,
        returnedInterface,
        ppResource);
    if (FAILED(hr)) {
      throw IException("Failed to OpenSharedResource. HRESULT(0x%lx)", hr)
    }
  }  
  
  void setTextFilterSize( 
    __in  UINT width,
    __in  UINT height)
  {
    ID3D10Device* device = getDevice();
    device -> SetTextFilterSize( 
        width,
        height);
  }  
  
  void getTextFilterSize( 
    __out_opt  UINT *pWidth,
    __out_opt  UINT *pHeight)
  {
    ID3D10Device* device = getDevice();
    device -> GetTextFilterSize( 
        pWidth,
        pHeight);
  }  
  
  void draw(ID3D10EffectTechnique* technique, UINT vertexCount) 
  {
    if (technique) {  
      D3D10_TECHNIQUE_DESC techDesc;
      technique -> GetDesc(&techDesc);
       
      for( UINT i = 0; i < techDesc.Passes; i++ ) {
         technique -> GetPassByIndex(i) -> Apply(0);
         this -> draw(vertexCount, 0);
      }
    }
  }
  
  void drawIndexed(ID3D10EffectTechnique* technique, UINT vertexCount) 
  {
    if (technique) {  
      D3D10_TECHNIQUE_DESC techDesc;
      technique -> GetDesc(&techDesc);
       
      for( UINT i = 0; i < techDesc.Passes; i++ ) {
         technique -> GetPassByIndex(i) -> Apply(0);
         this -> drawIndexed(vertexCount, 0, 0);
      }
    }
  }
};
  
}

 
