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
 *  Direct3DX10Object.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3DX10Object.h>

namespace SOL {

class Direct3DX10ImageInfo : public Direct3DX10Object {
private:
  D3DX10_IMAGE_INFO imageInfo;
  
public:
  Direct3DX10ImageInfo()
  :Direct3DX10Object()
  {
    memset(&imageInfo, 0, sizeof(imageInfo));
  }

  
public:
  //Constructor based on D3DX10GetImageInfoFromFile.  
  Direct3DX10ImageInfo(
      __in  LPCTSTR           pSrcFile,
      __in  ID3DX10ThreadPump *pPump,
      __in  D3DX10_IMAGE_INFO *pSrcInfo,
      __out HRESULT           *pHResult
      )
  :Direct3DX10Object()
  {
    memset(&imageInfo, 0, sizeof(imageInfo));
    HRESULT hr = D3DX10GetImageInfoFromFile(
          pSrcFile,
          pPump,
          &imageInfo,
          pHResult);
    if (SUCCEEDED(hr)) {
      ; //OK
    } else {
      throw IException("Failed to D3DX10GetImageInfoFromFile. HRESULT(0x%lx)", hr);
    }
  }
  
  //Constructor based on D3DX10GetImageInfoFromMemory.  
  Direct3DX10ImageInfo(
        __in LPCVOID           pSrcData,
        __in SIZE_T            srcDataSize,
        __in ID3DX10ThreadPump *pPump,
        __out  HRESULT           *pHResult
      )
  :Direct3DX10Object()
  {
    memset(&imageInfo, 0, sizeof(imageInfo));

    HRESULT hr = D3DX10GetImageInfoFromMemory(
        pSrcData,
        srcDataSize,
        pPump,
        &imageInfo,
        pHResult
      );
    if (SUCCEEDED(hr)) {
      ; //OK
    } else {
      throw IException("Failed to D3DX10GetImageInfoFromMemory. HRESULT(0x%lx)", hr);
    }    
  }
  
  //Constructor based on D3DX10GetImageInfoFromResource.
  Direct3DX10ImageInfo(
      __in  HMODULE           hSrcModule,
      __in  LPCTSTR           pSrcResource,
      __in  ID3DX10ThreadPump *pPump,
      __in  HRESULT           *pHResult
      )
  :Direct3DX10Object()
  {
    memset(&imageInfo, 0, sizeof(imageInfo));

    HRESULT hr = D3DX10GetImageInfoFromResource(
        hSrcModule,
        pSrcResource,
        pPump,
        &imageInfo,
        pHResult
      );
    if (SUCCEEDED(hr)) {
      ; //OK
    } else {
      throw IException("Failed to D3DX10GetImageInfoFromResource. HRESULT(0x%lx)", hr);
    }    
    
  }

  operator D3DX10_IMAGE_INFO*()
  {
    return &imageInfo;
  }
};


}


