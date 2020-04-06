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
 *  Direct3D11Device.h
 *
 *****************************************************************************/

// 2016/01/01

#pragma once
#include <DXGItype.h>

#include <sol/com/ComIUnknown.h>
#include <sol/direct3d11/Direct3D11DeviceContext.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <dxgi.h>

#include <d3dcompiler.h>
#include <xnamath.h>
#include <sol/direct3dcommon/XMColor.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")

namespace SOL {

class Direct3D11Device : public ComIUnknown {
private:
  D3D_FEATURE_LEVEL featureLevel;
    
public:
  Direct3D11Device(
    __in_opt IDXGIAdapter* pAdapter = NULL,
    __in_opt  D3D_DRIVER_TYPE    driverType = D3D_DRIVER_TYPE_HARDWARE,
    __in_opt  HMODULE            hmodule = NULL,
    __in_opt  UINT               flags   = D3D11_CREATE_DEVICE_BGRA_SUPPORT, // 0x20,
    __in_opt  UINT               sdkVersion = D3D11_SDK_VERSION)
  :ComIUnknown(),
  featureLevel( D3D_FEATURE_LEVEL_11_0)
  {

    D3D_FEATURE_LEVEL featureLevels[] =  {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3, 
        D3D_FEATURE_LEVEL_9_2, 
        D3D_FEATURE_LEVEL_9_1, 
    };
 
    D3D_DRIVER_TYPE driverTypes[] = {
      D3D_DRIVER_TYPE_UNKNOWN,
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_REFERENCE,
      D3D_DRIVER_TYPE_NULL,
      D3D_DRIVER_TYPE_SOFTWARE,
      D3D_DRIVER_TYPE_WARP

    };
    
    ID3D11Device* device = NULL;
    HRESULT hr = E_FAIL; 
    for (int i = 0;  i<CountOf(driverTypes); i++) {
       hr = D3D11CreateDevice(
        pAdapter,
        driverTypes[i],
        hmodule,
        flags,
        featureLevels,
        CountOf(featureLevels),
        sdkVersion,
        &device,
        &featureLevel,
        NULL );
    
      if (SUCCEEDED(hr)) {
        set(device);
        break;
      }
    }
    if (FAILED(hr)) {
      throw IException("Failed to D3D11CreateDevice. HRESULT(0x%lx)", hr);
    }
  }
  
  ~Direct3D11Device()
  { 
  }

   
  operator ID3D11Device*()
  {
    return getDevice();
  }

  ID3D11Device* getDevice()
  {
    ID3D11Device* device = (ID3D11Device*)getIUnknown();
    if (device) {
        return device;
    } else {
      throw IException("ID3D11Device is NULL.");
    }
  }


  void  createBuffer( 
            __in  const D3D11_BUFFER_DESC *pDesc,
            __in_opt  const D3D11_SUBRESOURCE_DATA *pInitialData,
            __out_opt  ID3D11Buffer **ppBuffer)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateBuffer( 
              pDesc,
              pInitialData,
              ppBuffer);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBuffer. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createTexture1D( 
            __in  const D3D11_TEXTURE1D_DESC *pDesc,
            __in  const D3D11_SUBRESOURCE_DATA *pInitialData,
            __out_opt  ID3D11Texture1D **ppTexture1D)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateTexture1D( 
              pDesc,
              pInitialData,
              ppTexture1D);
    if (FAILED(hr)) {
      throw IException("Failed to CreateTexture1D. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createTexture2D( 
            __in  const D3D11_TEXTURE2D_DESC *pDesc,
            __in  const D3D11_SUBRESOURCE_DATA *pInitialData,
            __out_opt  ID3D11Texture2D **ppTexture2D)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateTexture2D( 
              pDesc,
              pInitialData,
              ppTexture2D);
    if (FAILED(hr)) {
      throw IException("Failed to CreateTexture2D. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createTexture3D( 
            __in  const D3D11_TEXTURE3D_DESC *pDesc,
            __in  const D3D11_SUBRESOURCE_DATA *pInitialData,
            __out_opt  ID3D11Texture3D **ppTexture3D)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateTexture3D( 
              pDesc,
              pInitialData,
              ppTexture3D);
    if (FAILED(hr)) {
      throw IException("Failed to CreateTexture3D. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createShaderResourceView( 
            __in  ID3D11Resource *pResource,
            __in_opt  const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc,
            __out_opt  ID3D11ShaderResourceView **ppSRView)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateShaderResourceView( 
              pResource,
              pDesc,
              ppSRView);
    if (FAILED(hr)) {
      throw IException("Failed to CreateShaderResourceView. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createUnorderedAccessView( 
            __in  ID3D11Resource *pResource,
            __in_opt  const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc,
            __out_opt  ID3D11UnorderedAccessView **ppUAView)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateUnorderedAccessView( 
              pResource,
              pDesc,
              ppUAView);
    if (FAILED(hr)) {
      throw IException("Failed to CreateUnorderedAccessView. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createRenderTargetView( 
            __in  ID3D11Resource *pResource,
            __in_opt  const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
            __out_opt  ID3D11RenderTargetView **ppRTView)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateRenderTargetView( 
              pResource,
              pDesc,
              ppRTView);
    if (FAILED(hr)) {
      throw IException("Failed to CreateRenderTargetView. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createDepthStencilView( 
            __in  ID3D11Resource *pResource,
            __in_opt  const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc,
            __out_opt  ID3D11DepthStencilView **ppDepthStencilView)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateDepthStencilView( 
              pResource,
              pDesc,
              ppDepthStencilView);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDepthStencilView. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createInputLayout( 
            __in const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
            __in UINT numElements,
            __in  const void *pShaderBytecodeWithInputSignature,
            __in  SIZE_T bytecodeLength,
            __out_opt  ID3D11InputLayout **ppInputLayout)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateInputLayout( 
              pInputElementDescs,
              numElements,
              pShaderBytecodeWithInputSignature,
              bytecodeLength,
              ppInputLayout);
    if (FAILED(hr)) {
      throw IException("Failed to CreateInputLayout. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createVertexShader( 
            __in  const void *pShaderBytecode,
            __in  SIZE_T bytecodeLength,
            __in_opt  ID3D11ClassLinkage *pClassLinkage,
            __out_opt  ID3D11VertexShader **ppVertexShader)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateVertexShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              ppVertexShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateVertexShader. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createGeometryShader( 
            __in  const void *pShaderBytecode,
            __in  SIZE_T bytecodeLength,
            __in_opt  ID3D11ClassLinkage *pClassLinkage,
            __out_opt  ID3D11GeometryShader **ppGeometryShader)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateGeometryShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              ppGeometryShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateGeometryShader. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createGeometryShaderWithStreamOutput( 
            __in  const void *pShaderBytecode,
            __in  SIZE_T bytecodeLength,
            __in  const D3D11_SO_DECLARATION_ENTRY *pSODeclaration,
            __in  UINT numEntries,
            __in  const UINT *pBufferStrides,
            __in  UINT numStrides,
            __in  UINT rasterizedStream,
            __in_opt  ID3D11ClassLinkage *pClassLinkage,
            __out_opt  ID3D11GeometryShader **ppGeometryShader)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateGeometryShaderWithStreamOutput( 
              pShaderBytecode,
              bytecodeLength,
              pSODeclaration,
              numEntries,
              pBufferStrides,
              numStrides,
              rasterizedStream,
              pClassLinkage,
              ppGeometryShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateGeometryShaderWithStreamOutput. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createPixelShader( 
            __in  const void *pShaderBytecode,
            __in  SIZE_T bytecodeLength,
            __in_opt  ID3D11ClassLinkage *pClassLinkage,
            __out_opt  ID3D11PixelShader **ppPixelShader)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreatePixelShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              ppPixelShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreatePixelShader. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createHullShader( 
            __in  const void *pShaderBytecode,
            __in  SIZE_T bytecodeLength,
            __in_opt  ID3D11ClassLinkage *pClassLinkage,
            __out_opt  ID3D11HullShader **ppHullShader)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateHullShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              ppHullShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateHullShader. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createDomainShader( 
            __in  const void *pShaderBytecode,
            __in  SIZE_T bytecodeLength,
            __in_opt  ID3D11ClassLinkage *pClassLinkage,
            __out_opt  ID3D11DomainShader **ppDomainShader)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateDomainShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              ppDomainShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDomainShader. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createComputeShader( 
            __in  const void *pShaderBytecode,
            __in  SIZE_T bytecodeLength,
            __in_opt  ID3D11ClassLinkage *pClassLinkage,
            __out_opt  ID3D11ComputeShader **ppComputeShader)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateComputeShader( 
              pShaderBytecode,
              bytecodeLength,
              pClassLinkage,
              ppComputeShader);
    if (FAILED(hr)) {
      throw IException("Failed to CreateComputeShader. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createClassLinkage( 
            __out  ID3D11ClassLinkage **ppLinkage)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateClassLinkage( 
              ppLinkage);
    if (FAILED(hr)) {
      throw IException("Failed to CreateClassLinkage. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createBlendState( 
            __in  const D3D11_BLEND_DESC *pBlendStateDesc,
            __out_opt  ID3D11BlendState **ppBlendState)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateBlendState( 
              pBlendStateDesc,
              ppBlendState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateBlendState. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createDepthStencilState( 
            __in  const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc,
            __out_opt  ID3D11DepthStencilState **ppDepthStencilState)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateDepthStencilState( 
              pDepthStencilDesc,
              ppDepthStencilState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDepthStencilState. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createRasterizerState( 
            __in  const D3D11_RASTERIZER_DESC *pRasterizerDesc,
            __out_opt  ID3D11RasterizerState **ppRasterizerState)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateRasterizerState( 
              pRasterizerDesc,
              ppRasterizerState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateRasterizerState. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createSamplerState( 
            __in  const D3D11_SAMPLER_DESC *pSamplerDesc,
            __out_opt  ID3D11SamplerState **ppSamplerState)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateSamplerState( 
            pSamplerDesc,
            ppSamplerState);
    if (FAILED(hr)) {
      throw IException("Failed to CreateSamplerState. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createQuery( 
            __in  const D3D11_QUERY_DESC *pQueryDesc,
            __out_opt  ID3D11Query **ppQuery)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateQuery( 
              pQueryDesc,
              ppQuery);
    if (FAILED(hr)) {
      throw IException("Failed to CreateQuery. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createPredicate( 
            __in  const D3D11_QUERY_DESC *pPredicateDesc,
            __out_opt  ID3D11Predicate **ppPredicate)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreatePredicate( 
              pPredicateDesc,
              ppPredicate);
    if (FAILED(hr)) {
      throw IException("Failed to CreatePredicate. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createCounter( 
            __in  const D3D11_COUNTER_DESC *pCounterDesc,
            __out_opt  ID3D11Counter **ppCounter)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateCounter( 
              pCounterDesc,
              ppCounter);
    if (FAILED(hr)) {
      throw IException("Failed to CreateCounter. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  createDeferredContext( 
            UINT contextFlags,
            __out_opt  ID3D11DeviceContext **ppDeferredContext)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CreateDeferredContext( 
              contextFlags,
              ppDeferredContext);
    if (FAILED(hr)) {
      throw IException("Failed to CreateDeferredContext. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  openSharedResource( 
            __in  HANDLE hResource,
            __in  REFIID returnedInterface,
            __out_opt  void **ppResource)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> OpenSharedResource( 
              hResource,
              returnedInterface,
              ppResource);
    if (FAILED(hr)) {
      throw IException("Failed to OpenSharedResource. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  checkFormatSupport( 
            __in  DXGI_FORMAT format,
            __out  UINT *pFormatSupport)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CheckFormatSupport( 
              format,
              pFormatSupport);
    if (FAILED(hr)) {
      throw IException("Failed to CheckFormatSupport. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  checkMultisampleQualityLevels( 
            __in  DXGI_FORMAT format,
            __in  UINT sampleCount,
            __out  UINT *pNumQualityLevels)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CheckMultisampleQualityLevels( 
              format,
              sampleCount,
              pNumQualityLevels);
    if (FAILED(hr)) {
      throw IException("Failed to CheckMultisampleQualityLevels. HRESULT(0x%lx)", hr); 
    }
  }
        
  void checkCounterInfo( 
            __out  D3D11_COUNTER_INFO *pCounterInfo)
  {
    ID3D11Device* device = getDevice();
    device -> CheckCounterInfo( 
              pCounterInfo);
  }
        
  void  checkCounter( 
            __in  const D3D11_COUNTER_DESC *pDesc,
            __out  D3D11_COUNTER_TYPE *pType,
            __out  UINT *pActiveCounters,
            __out  LPSTR szName,
            __inout_opt  UINT *pNameLength,
            __out  LPSTR szUnits,
            __inout_opt  UINT *pUnitsLength,
            __out  LPSTR szDescription,
            __inout_opt  UINT *pDescriptionLength)
  {
    ID3D11Device* device = getDevice();
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
      throw IException("Failed to CheckCounter. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  checkFeatureSupport( 
            D3D11_FEATURE feature,
            __out  void *pFeatureSupportData,
            UINT featureSupportDataSize)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> CheckFeatureSupport( 
              feature,
              pFeatureSupportData,
              featureSupportDataSize);
    if (FAILED(hr)) {
      throw IException("Failed to CheckFeatureSupport. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  getPrivateData( 
            __in  REFGUID guid,
            __inout  UINT *pDataSize,
            __out void *pData)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> GetPrivateData( 
              guid,
              pDataSize,
              pData);
    if (FAILED(hr)) {
      throw IException("Failed to GetPrivateData. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  setPrivateData( 
            __in  REFGUID guid,
            __in  UINT dataSize,
            __in  const void *pData)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> SetPrivateData( 
              guid,
              dataSize,
              pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateData. HRESULT(0x%lx)", hr); 
    }
  }
        
  void  setPrivateDataInterface( 
            __in  REFGUID guid,
            __in_opt  const IUnknown *pData)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> SetPrivateDataInterface( 
              guid,
              pData);
    if (FAILED(hr)) {
      throw IException("Failed to SetPrivateDataInterface. HRESULT(0x%lx)", hr); 
    }
  }
        
  D3D_FEATURE_LEVEL getFeatureLevel()
  {
    ID3D11Device* device = getDevice();
    return device -> GetFeatureLevel();
  }
        
  UINT getCreationFlags()
  {
    ID3D11Device* device = getDevice();
    return device -> GetCreationFlags();
  }
        
  void getDeviceRemovedReason()
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> GetDeviceRemovedReason();
    if (FAILED(hr)) {
      throw IException("Failed to GetDeviceRemovedReason. HRESULT(0x%lx)", hr); 
    }
  }
      
  void  getImmediateContext( 
            __out  ID3D11DeviceContext **ppImmediateContext)
  {
    ID3D11Device* device = getDevice();
    device -> GetImmediateContext( 
              ppImmediateContext);
  }
        
  void setExceptionMode( 
            UINT raiseFlags)
  {
    ID3D11Device* device = getDevice();
    HRESULT hr = device -> SetExceptionMode( 
            raiseFlags);
    if (FAILED(hr)) {
      throw IException("Failed to SetExceptionMode. HRESULT(0x%lx)", hr); 
    }
  }
  
  UINT getExceptionMode()
  {
    ID3D11Device* device = getDevice();
    return  device -> GetExceptionMode();
  }
        
};


}
    

    