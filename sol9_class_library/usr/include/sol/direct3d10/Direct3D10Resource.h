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
 *  Direct3D10Resource.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Pair.h>
#include <sol/StringT.h>
#include <sol/direct3d10/Direct3D10DeviceChild.h>

namespace SOL {

class Direct3D10Resource : public Direct3D10DeviceChild {
public:
  Direct3D10Resource()
   :Direct3D10DeviceChild()
  {
  }

  //Constructor
  Direct3D10Resource(ID3D10View *view)
   :Direct3D10DeviceChild()
  {
    ID3D10Resource *resource = NULL;
    view ->GetResource(&resource);
    set(resource);
  }
  
  Direct3D10Resource(ID3D10Resource *resource)
   :Direct3D10DeviceChild()
  {
    if (resource) {
      set(resource);
    } else {
      throw IException("Invalid argument. ID3D10Resource is NULL.");
    }
  }

  //Constructor based on D3DX10CreateTextureFromFile.
  Direct3D10Resource(
      __in ID3D10Device*            pDevice,
      __in LPCTSTR                  pSrcFile,
      __in D3DX10_IMAGE_LOAD_INFO*  loadInfo,
      __in ID3DX10ThreadPump*       pPump = NULL,
      __out HRESULT*                pHResult = NULL)
  :Direct3D10DeviceChild()
  {
    ID3D10Resource *resource = NULL;
    HRESULT hr = D3DX10CreateTextureFromFile(
        pDevice,
        pSrcFile,
        loadInfo,
        pPump,
        &resource,
        pHResult);
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX10CreateTextureFromFile. HRESULT(0x%lx)", hr)
    }
  }

public:
  //Constructor based on D3DX10CreateTextureFromFile
  Direct3D10Resource(
        __in ID3D10Device* pDevice,
        __in LPCTSTR       pSrcFile,
        __in DXGI_FORMAT   format,  // DXGI_FORMAT_R8G8B8A8_UNORM
        __in D3D10_USAGE   usage,   // D3D10_USAGE_STAGING;
        __in UINT          bindFlags, //  D3D10_USAGE_STAGING;
        __in UINT          cpuAccessFlags) //D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
  :Direct3D10DeviceChild()
  {
    D3DX10_IMAGE_LOAD_INFO  loadInfo;
    memset(&loadInfo, 0, sizeof(loadInfo));
    loadInfo.Usage          = usage; //D3D10_USAGE_STAGING;
    loadInfo.BindFlags      = bindFlags; //D3D10_BIND_SHADER_RESOURCE;
    loadInfo.CpuAccessFlags = cpuAccessFlags; //D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
    loadInfo.Format         = format; //DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    
    ID3D10Resource *resource = NULL;
    HRESULT hr = D3DX10CreateTextureFromFile(
        pDevice,
        pSrcFile,
        &loadInfo,
        NULL,
        &resource,
        NULL);
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX10CreateTextureFromFile. HRESULT(0x%lx)", hr)
    }
  }

  /*This is a simpler constructor than the above, which uses the following NULL parameters
      ID3DX10ThreadPump*        pPump = NULL,
      HRESULT*                 pHResult = NULL
   */
  //Constructor based on D3DX10CreateTextureFromFile.
  Direct3D10Resource(
        ID3D10Device*            pDevice,
        LPCTSTR                  pSrcFile)
  :Direct3D10DeviceChild()
  {
    D3DX10_IMAGE_LOAD_INFO  loadInfo;
    memset(&loadInfo, 0, sizeof(loadInfo));

    ID3D10Resource *resource = NULL;
    HRESULT hr = D3DX10CreateTextureFromFile(
        pDevice,
        pSrcFile,
        &loadInfo,
        NULL,
        &resource,
        NULL);
    if (SUCCEEDED(hr)) {
      set(resource);
    } else {
      throw IException("Failed to D3DX10CreateTextureFromFile. HRESULT(0x%lx)", hr)
    }
  }

  //Constructor based on D3DX10CreateTextureFromMemory.
  Direct3D10Resource(
        __in  ID3D10Device           *pDevice,
        __in  LPCVOID                pSrcData,
        __in  SIZE_T                 srcDataSize,
        __in  D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
        __in  ID3DX10ThreadPump      *pPump,
        __out HRESULT                *pHResult
      )
  :Direct3D10DeviceChild()
  {
    ID3D10Resource *resource = NULL;
    HRESULT hr = D3DX10CreateTextureFromMemory(
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
      throw IException("Failed to D3DX10CreateTextureFromMemory. HRESULT(0x%lx)", hr)
    }
  }
  
  //Constructor based on D3DX10CreateTextureFromResource.
  Direct3D10Resource(
          __in  ID3D10Device    *pDevice,
          __in HMODULE          hSrcModule,
          __in LPCTSTR           pSrcResource,
          __in  D3DX10_IMAGE_LOAD_INFO *pLoadInfo,
          __in  ID3DX10ThreadPump      *pPump,
          __out HRESULT                *pHResult
        )
  :Direct3D10DeviceChild()
  {
    ID3D10Resource *resource = NULL;
    HRESULT hr = D3DX10CreateTextureFromResource(
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
      throw IException("Failed to D3DX10CreateTextureFromResource. HRESULT(0x%lx)", hr)
    }
  }
  
  
  ~Direct3D10Resource()
  {
  }

  operator   ID3D10Resource*()
  {
    return getResource();
  }

  ID3D10Resource* getResource()
  {
    ID3D10Resource* resource = (ID3D10Resource*)getIUnknown();
    if (resource) {
        return resource;
    } else {
        throw IException("ID3D10Resource is NULL.")
    }
  }

  void getType( 
            __out  D3D10_RESOURCE_DIMENSION *rType)
  {
    ID3D10Resource* resource = getResource();
    resource -> GetType( 
        rType); 
  }      

  void setEvictionPriority( 
            __in  UINT evictionPriority)
  {
    ID3D10Resource* resource = getResource();
    resource -> SetEvictionPriority( 
        evictionPriority); 
  }      
        
  UINT  getEvictionPriority()
  {
    ID3D10Resource* resource = getResource();
    return resource -> GetEvictionPriority(); 
  }
  
  void loadTextureFromTexture(
        D3DX10_TEXTURE_LOAD_INFO *pLoadInfo,
      ID3D10Resource           *pDstTexture)
  {
    ID3D10Resource* resource = getResource();
    
    HRESULT hr = D3DX10LoadTextureFromTexture(
        resource,
        pLoadInfo,
        pDstTexture
      );
    if (FAILED(hr)) {
      throw IException("Failed to  D3DX10LoadTextureFromTexture. HRESULT(0x%lx)", hr);
    }
  }
  
  
  void saveToFile(
        const TCHAR* filename)
  {
    static const Pair<const TCHAR*, D3DX10_IMAGE_FILE_FORMAT> pairs[] = {
      {_T(".bmp"), D3DX10_IFF_BMP},
      {_T(".jpg"), D3DX10_IFF_JPG},
      {_T(".jpeg"), D3DX10_IFF_JPG},
      {_T(".png"),D3DX10_IFF_PNG},
      {_T(".dds"),D3DX10_IFF_DDS},
      {_T(".tif"),D3DX10_IFF_TIFF},
      {_T(".tiff"),D3DX10_IFF_TIFF},
      {_T(".gif"),D3DX10_IFF_GIF},
      {_T(".wmp"),D3DX10_IFF_WMP},
    };
    D3DX10_IMAGE_FILE_FORMAT format=D3DX10_IFF_PNG ;
    bool found = false;
    for (int i = 0; CountOf(pairs); i++) {
      if (StringT<TCHAR>::endsWithIgnoreCase(filename, pairs[i].first)) {
        format = pairs[i].second;
        found = true;
        break;
      }
    }
    if (found == false) {
      throw IException("Invalied filename.");
    }

    ID3D10Resource* resource = getResource();
    HRESULT hr = D3DX10SaveTextureToFile(
          resource,
          format,
          filename);
    if (FAILED(hr)) {
      throw IException("Failed to D3DX10SaveTextureToFile. HRESULT(0x%lx)", hr);
    }
  }
  
  void saveToMemory(
        __in  D3DX10_IMAGE_FILE_FORMAT destFormat,
        __out LPD3D10BLOB              *ppDestBuf,
        __in  UINT                     flags)
  {
    ID3D10Resource* resource = getResource();
    HRESULT hr = D3DX10SaveTextureToMemory(
            resource,
            destFormat,
            ppDestBuf,
            flags);
    if (FAILED(hr)) {
      throw IException("Failed to D3DX10SaveTextureToMemory. HRESULT(0x%lx)", hr);
    }
  }  
};

}