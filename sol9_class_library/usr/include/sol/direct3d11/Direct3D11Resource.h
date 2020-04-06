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
 *  Direct3D11Resource.h
 *
 *****************************************************************************/

// 2016/01/13

#pragma once

#include <sol/direct3d11/Direct3D11DeviceChild.h>

namespace SOL {

class Direct3D11Resource : public Direct3D11DeviceChild {
    
public:
  Direct3D11Resource()
  {
  }

  //Constructor
  Direct3D11Resource(ID3D11View *view)
   :Direct3D11DeviceChild()
  {
    ID3D11Resource *resource = NULL;
    view ->GetResource(&resource);
    set(resource);
  }
  
  Direct3D11Resource(ID3D11Resource *resource)
   :Direct3D11DeviceChild()
  {
    if (resource) {
      set(resource);
    } else {
      throw IException("Invalid argument. ID3D11Resource is NULL.");
    }
  }

  //Constructor based on D3DX11CreateTextureFromFile.
  Direct3D11Resource(
      __in ID3D11Device*            pDevice,
      __in LPCTSTR                  pSrcFile,
      __in D3DX11_IMAGE_LOAD_INFO*  loadInfo,
      __in ID3DX11ThreadPump*       pPump = NULL,
      __out HRESULT*                pHResult = NULL)
  :Direct3D11DeviceChild()
  {
    ID3D11Resource *resource = NULL;
    HRESULT hr = D3DX11CreateTextureFromFile(
        pDevice,
        pSrcFile,
        loadInfo,
        pPump,
        &resource,
        pHResult);
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX11CreateTextureFromFile. HRESULT(0x%lx)", hr)
    }
  }

public:
  //Constructor based on D3DX11CreateTextureFromFile
  Direct3D11Resource(
        __in ID3D11Device* pDevice,
        __in LPCTSTR       pSrcFile,
        __in DXGI_FORMAT   format,  // DXGI_FORMAT_R8G8B8A8_UNORM
        __in D3D11_USAGE   usage,   // D3D11_USAGE_STAGING;
        __in UINT          bindFlags, //  D3D11_USAGE_STAGING;
        __in UINT          cpuAccessFlags) //D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
  :Direct3D11DeviceChild()
  {
    D3DX11_IMAGE_LOAD_INFO  loadInfo;
    memset(&loadInfo, 0, sizeof(loadInfo));
    loadInfo.Usage          = usage; //D3D11_USAGE_STAGING;
    loadInfo.BindFlags      = bindFlags; //D3D11_BIND_SHADER_RESOURCE;
    loadInfo.CpuAccessFlags = cpuAccessFlags; //D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
    loadInfo.Format         = format; //DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    
    ID3D11Resource *resource = NULL;
    HRESULT hr = D3DX11CreateTextureFromFile(
        pDevice,
        pSrcFile,
        &loadInfo,
        NULL,
        &resource,
        NULL);
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX11CreateTextureFromFile. HRESULT(0x%lx)", hr)
    }
  }

  /*This is a simpler constructor than the above, which uses the following NULL parameters
      ID3DX11ThreadPump*        pPump = NULL,
      HRESULT*                 pHResult = NULL
   */
  //Constructor based on D3DX11CreateTextureFromFile.
  Direct3D11Resource(
        ID3D11Device*            pDevice,
        LPCTSTR                  pSrcFile)
  :Direct3D11DeviceChild()
  {
    D3DX11_IMAGE_LOAD_INFO  loadInfo;
    memset(&loadInfo, 0, sizeof(loadInfo));

    ID3D11Resource *resource = NULL;
    HRESULT hr = D3DX11CreateTextureFromFile(
        pDevice,
        pSrcFile,
        &loadInfo,
        NULL,
        &resource,
        NULL);
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX11CreateTextureFromFile. HRESULT(0x%lx)", hr)
    }
  }

  //Constructor based on D3DX11CreateTextureFromMemory.
  Direct3D11Resource(
        __in  ID3D11Device           *pDevice,
        __in  LPCVOID                pSrcData,
        __in  SIZE_T                 srcDataSize,
        __in  D3DX11_IMAGE_LOAD_INFO *pLoadInfo,
        __in  ID3DX11ThreadPump      *pPump,
        __out HRESULT                *pHResult
      )
  :Direct3D11DeviceChild()
  {
    ID3D11Resource *resource = NULL;
    HRESULT hr = D3DX11CreateTextureFromMemory(
        pDevice,
        pSrcData,
        srcDataSize,
        pLoadInfo,
        pPump,
        &resource,
        pHResult);
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX11CreateTextureFromMemory. HRESULT(0x%lx)", hr)
    }
  }
  
  //Constructor based on D3DX11CreateTextureFromResource.
  Direct3D11Resource(
          __in  ID3D11Device    *pDevice,
          __in HMODULE          hSrcModule,
          __in LPCTSTR           pSrcResource,
          __in  D3DX11_IMAGE_LOAD_INFO *pLoadInfo,
          __in  ID3DX11ThreadPump      *pPump,
          __out HRESULT                *pHResult
        )
  :Direct3D11DeviceChild()
  {
    ID3D11Resource *resource = NULL;
    HRESULT hr = D3DX11CreateTextureFromResource(
            pDevice,
            hSrcModule,
            pSrcResource,
            pLoadInfo,
            pPump,
            &resource,
            pHResult
          );
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX11CreateTextureFromResource. HRESULT(0x%lx)", hr)
    }
  }

  ~Direct3D11Resource()
  {
  }

  operator ID3D11Resource*()
  {
    return getResource();
  }
  
  ID3D11Resource* getResource()
  {
    ID3D11Resource* resource = (ID3D11Resource*)getIUnknown();
    if (resource) {
        return resource;
    } else {
      throw IException("ID3D11Resource is NULL.");
    }
  }
  
  void getType( 
            __out  D3D11_RESOURCE_DIMENSION *pResourceDimension)
  {
    ID3D11Resource* resource = getResource();
    resource -> GetType(pResourceDimension);
  }
         
  void setEvictionPriority( 
            __in  UINT evictionPriority)
  {
    ID3D11Resource* resource = getResource();
    resource -> SetEvictionPriority(evictionPriority);
  }
        
  UINT getEvictionPriority()
  {
    ID3D11Resource* resource = getResource();
    return resource -> GetEvictionPriority();
  }
};

}

