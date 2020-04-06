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
 *  Direct3D10View.h
 *
 *****************************************************************************/

#pragma once
#include <sol/direct3d10/Direct3D10View.h>

namespace SOL {

class Direct3D10ShaderResourceView : public Direct3D10View {
public:
  //Constructor based on D3DX10CreateShaderResourceViewFromFile.
  Direct3D10ShaderResourceView(
      __in ID3D10Device* device,
      __in LPCTSTR       sourceFile,
      __in const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
      __in DXGI_FORMAT format   = DXGI_FORMAT_R8G8B8A8_UNORM
  ) 
  :Direct3D10View()
  {
    D3DX10_IMAGE_LOAD_INFO loadInfo;
    ZeroMemory(&loadInfo, sizeof(loadInfo));
    loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
    loadInfo.Format    = format; //DXGI_FORMAT_R8G8B8A8_UNORM;
    ID3D10ShaderResourceView* resourceView = NULL;
    HRESULT hr = D3DX10CreateShaderResourceViewFromFile(
        device, 
        sourceFile, 
        &loadInfo, 
        NULL, 
        &resourceView, 
        NULL);
    
    if (SUCCEEDED(hr)) {
      set(resourceView);
    } else {
      throw IException("Failed to D3DX10CreateShaderResourceViewFromFile. HRESULT(0x%lx)", hr);
    }
  }

  //Constructor based on D3DX10CreateShaderResourceViewFromFile.
  Direct3D10ShaderResourceView(
      __in ID3D10Device* device,
      __in LPCTSTR       sourceFile,
      __in const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
      __in D3DX10_IMAGE_LOAD_INFO* loadInfo)
  :Direct3D10View()
  {
    
    ID3D10ShaderResourceView* resourceView = NULL;
    HRESULT hr = D3DX10CreateShaderResourceViewFromFile(
        device, 
        sourceFile, 
        loadInfo, 
        NULL, 
        &resourceView, 
        NULL);
    
    if (SUCCEEDED(hr)) {
      set(resourceView);
    } else {
      throw IException("Failed to D3DX10CreateShaderResourceViewFromFile. HRESULT(0x%lx)", hr);
    }
  }

  //Constructor based on ID3D10Devie::D3DX10CreateShaderResourceView.
  Direct3D10ShaderResourceView(
      __in ID3D10Device* device,
      __in  ID3D10Resource *pResource,
      __in_opt  const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc) 
  :Direct3D10View()
  {
    ID3D10ShaderResourceView* resourceView = NULL;
    HRESULT  hr = device -> CreateShaderResourceView( 
        pResource,
        pDesc,
        &resourceView);
    if (SUCCEEDED(hr)) {
      set(resourceView);
    } else {
      throw IException("Failed to CreateShaderResourceView. HRESULT(0x%lx)", hr);
    }
  }

  //Constructor based on D3DX10CreateShaderResourceViewFromMemory.
  Direct3D10ShaderResourceView(
        __in  ID3D10Device            *pDevice,
        __in   LPCVOID                 pSrcData,
        __in  SIZE_T                   srcDataSize,
        __in  D3DX10_IMAGE_LOAD_INFO   *pLoadInfo,
        __in  ID3DX10ThreadPump        *pPump,
        __out  HRESULT                 *pHResult)
  :Direct3D10View()
  {
    ID3D10ShaderResourceView *resourceView = NULL;
  
    HRESULT hr = D3DX10CreateShaderResourceViewFromMemory(
          pDevice,
          pSrcData,
          srcDataSize,
          pLoadInfo,
          pPump,
          &resourceView,

          pHResult
       );
    if (SUCCEEDED(hr)) {
      set(resourceView);
    } else {
      throw IException("Failed to D3DX10CreateShaderResourceViewFromMemory. HRESULT(0x%lx)", hr);
    }

  }
  
  //Constructor based on D3DX10CreateShaderResourceViewFromResource.
  Direct3D10ShaderResourceView(
        __in ID3D10Device             *pDevice,
        __in HMODULE                  hSrcModule,
        __in LPCTSTR                  pSrcResource,
        __in D3DX10_IMAGE_LOAD_INFO   *pLoadInfo,
        __in ID3DX10ThreadPump        *pPump,
        __out HRESULT                 *pHResult)

  :Direct3D10View()
  {
    ID3D10ShaderResourceView *resourceView = NULL;
    HRESULT hr = D3DX10CreateShaderResourceViewFromResource(
          pDevice,
          hSrcModule,
          pSrcResource,
          pLoadInfo,
          pPump,
          &resourceView,
          pHResult
          );
    if (SUCCEEDED(hr)) {
      set(resourceView);
    } else {
      throw IException("Failed to D3DX10CreateShaderResourceViewFromResource. HRESULT(0x%lx)", hr);
    }

  }
    
  ~Direct3D10ShaderResourceView()
  {
  }

  operator ID3D10ShaderResourceView*()
  {
    return getResourceView();
  }

  ID3D10ShaderResourceView* getResourceView()
  {
    ID3D10ShaderResourceView* resourceView = (ID3D10ShaderResourceView*)getIUnknown();
    if (resourceView) {
      return resourceView;
    } else {
      throw IException("ID3D10ShaderResourceView is NULL.")
    }
  } 

  void getDesc( 
            __out  D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc)
  {
    ID3D10ShaderResourceView* resourceView = getResourceView();
    resourceView -> GetDesc( 
              pDesc);
  }
   
  void getDesc( 
            __out  D3D10_SHADER_RESOURCE_VIEW_DESC& desc)
  {
    ID3D10ShaderResourceView* resourceView = getResourceView();
    resourceView -> GetDesc( 
              &desc);
  }
};
}
