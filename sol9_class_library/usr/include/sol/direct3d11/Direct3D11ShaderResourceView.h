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
 *  Direct3D11ShaderResourceView.h
 *
 *****************************************************************************/

// 2016/01/13
// This is base ond C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include

#pragma once

#include <sol/direct3d11/Direct3D11View.h>

namespace SOL {

class Direct3D11ShaderResourceView : public Direct3D11View{
public:
  //Constructor based on D3DX11CreateShaderResourceViewFromFile.
  Direct3D11ShaderResourceView(
      __in ID3D11Device* device,
      __in LPCTSTR       sourceFile,
      __in const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc,
      __in DXGI_FORMAT format   = DXGI_FORMAT_R8G8B8A8_UNORM
  ) 
  
  :Direct3D11View()
  {
    D3DX11_IMAGE_LOAD_INFO loadInfo;
    ZeroMemory(&loadInfo, sizeof(loadInfo));
    loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    loadInfo.Format    = format; //DXGI_FORMAT_R8G8B8A8_UNORM;
    ID3D11ShaderResourceView* resourceView = NULL;
    HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
        device, 
        sourceFile, 
        &loadInfo, 
        NULL, 
        &resourceView, 
        NULL);
    
    if (SUCCEEDED(hr)) {
      set(resourceView);
    } else {
      throw IException("Failed to D3DX11CreateShaderResourceViewFromFile. HRESULT(0x%lx)", hr);
    }
  }

  //Constructor based on D3DX10CreateShaderResourceViewFromFile.
  Direct3D11ShaderResourceView(
      __in ID3D11Device* device,
      __in LPCTSTR       sourceFile,
      __in const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc,
      __in D3DX11_IMAGE_LOAD_INFO* loadInfo)
  :Direct3D11View()
  {
    ID3D11ShaderResourceView* resourceView = NULL;
    HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
        device, 
        sourceFile, 
        loadInfo, 
        NULL, 
        &resourceView, 
        NULL);
    
    if (SUCCEEDED(hr)) {
      set(resourceView);
    } else {
      throw IException("Failed to D3DX11CreateShaderResourceViewFromFile. HRESULT(0x%lx)", hr);
    }
  }
 
public:
  Direct3D11ShaderResourceView(
        __in ID3D11Device* device,
        __in  ID3D11Resource *pResource,
        __in_opt  const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc)
  {
    ID3D11ShaderResourceView* srView = NULL;
    if (device) {
      HRESULT hr = device -> CreateShaderResourceView( 
              pResource,
              pDesc,
              &srView);
      if (SUCCEEDED(hr)) {
        set(srView);
      } else {
        throw IException("Failed to CreateShaderResourceView. HRESULT(0x%lx)", hr); 
      }
    } else {
      throw IException("Invalid argument. ID3D11Device is NULL.");
    }
  }
    
  //Constructor based on D3DX11CreateShaderResourceViewFromMemory.
  Direct3D11ShaderResourceView(
        __in  ID3D11Device            *pDevice,
        __in   LPCVOID                 pSrcData,
        __in  SIZE_T                   srcDataSize,
        __in  D3DX11_IMAGE_LOAD_INFO   *pLoadInfo,
        __in  ID3DX11ThreadPump        *pPump,
        __out  HRESULT                 *pHResult)
  :Direct3D11View()
  {
    ID3D11ShaderResourceView *resourceView = NULL;
  
    HRESULT hr = D3DX11CreateShaderResourceViewFromMemory(
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
      throw IException("Failed to D3DX11CreateShaderResourceViewFromMemory. HRESULT(0x%lx)", hr);
    }

  }
  
  //Constructor based on D3DX11CreateShaderResourceViewFromResource.
  Direct3D11ShaderResourceView(
        __in ID3D11Device             *pDevice,
        __in HMODULE                  hSrcModule,
        __in LPCTSTR                  pSrcResource,
        __in D3DX11_IMAGE_LOAD_INFO   *pLoadInfo,
        __in ID3DX11ThreadPump        *pPump,
        __out HRESULT                 *pHResult)

  :Direct3D11View()
  {
    ID3D11ShaderResourceView *resourceView = NULL;
    HRESULT hr = D3DX11CreateShaderResourceViewFromResource(
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
      throw IException("Failed to D3DX11CreateShaderResourceViewFromResource. HRESULT(0x%lx)", hr);
    }
  }

  ~Direct3D11ShaderResourceView()
  {
  }

  operator ID3D11ShaderResourceView*()
  {
    return getShaderResourceView();
  }
  
  ID3D11ShaderResourceView* getShaderResourceView()
  {
    ID3D11ShaderResourceView* view = (ID3D11ShaderResourceView*)getIUnknown();
    if (view) {
        return view;
    } else {
      throw IException("ID3D11ShaderResourceView is NULL.");
    }
  }
  
  void getDesc( 
            __out  D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc)
  {
    ID3D11ShaderResourceView* view = getShaderResourceView();
    view -> GetDesc(pDesc);
  }
};

}

