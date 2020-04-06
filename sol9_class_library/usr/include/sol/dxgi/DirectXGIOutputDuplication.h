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
 *  DirectXGIOutputDuplication.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIObject.h>
#include <dxgi1_2.h>

namespace SOL {
  
class DirectXGIOutputDuplication : public DirectXGIObject {
public:
  DirectXGIOutputDuplication(IDXGISwapChain* chain,
            __out  BOOL *pFullscreen)
  :DirectXGIObject()
  {
    IDXGIOutputDuplication* output = NULL;
    HRESULT hr = chain -> GetFullscreenState( 
              pFullscreen,
              &output);
    if (SUCCEEDED(hr)) {
      set(output);
    } else {
      throw IException("Failed to GetFullscreenState. HRESULT(0x%lx)", hr)
    }
  }      
        

  DirectXGIOutputDuplication(IDXGISwapChain* chain)
  :DirectXGIObject()  
  {
    IDXGIOutputDuplication* output = NULL;
    HRESULT hr = chain -> GetContainingOutput( 
              &output);
    if (SUCCEEDED(hr)) {
      set(output);
    } else {
      throw IException("Failed to GetContainingOutput. HRESULT(0x%lx)", hr)
    }
  }      

  ~DirectXGIOutputDuplication() 
  {
  }
  
  operator IDXGIOutputDuplicationDuplication*()
  {
    return getOutput();
  }
  
  IDXGIOutputDuplicationDuplication* getOutput()
  {
    IDXGIOutputDuplicationDuplication* output = (IDXGIOutputDuplicationDuplication*)getIUnknown();
    if (output) {
      return output;
    } else {
      throw IException("IDXGIOutputDuplication is NULL.");
    }
  }
  
  void GetDesc( 
            _Out_  DXGI_OUTDUPL_DESC *pDesc)
  {
    IDXGIOutputDuplication* output = getOutput();
    output -> GetDesc( 
            _pDesc);
  }
        
  void acquireNextFrame( 
            _In_  UINT timeoutInMilliseconds,
            _Out_  DXGI_OUTDUPL_FRAME_INFO *pFrameInfo,
            _COM_Outptr_  IDXGIResource **ppDesktopResource)
  {
    IDXGIOutputDuplication* output = getOutput();
    HRESULT hr = output -> AcquireNextFrame( 
              timeoutInMilliseconds,
              pFrameInfo,
              ppDesktopResource);
    if (FAILED(hr)) {
      throw IException("Faield to AcquireNextFrame. HRESUL(0x%lx)", hr);
    }
  }
        
  HRESULT GetFrameDirtyRects( 
            _In_  UINT dirtyRectsBufferSize,
            _Out_writes_bytes_to_(dirtyRectsBufferSize, *pDirtyRectsBufferSizeRequired)  RECT *pDirtyRectsBuffer,
            _Out_  UINT *pDirtyRectsBufferSizeRequired)
  {
    IDXGIOutputDuplication* output = getOutput();
    HRESULT hr = output -> GetFrameDirtyRects( 
            dirtyRectsBufferSize,
            pDirtyRectsBuffer,
            pDirtyRectsBufferSizeRequired);
    if (FAILED(hr)) {
      throw IException("Faield to GetFrameDirtyRects. HRESUL(0x%lx)", hr);
    }
  }
        
  void getFrameMoveRects( 
            _In_  UINT moveRectsBufferSize,
            _Out_writes_bytes_to_(moveRectsBufferSize, *pMoveRectsBufferSizeRequired)  DXGI_OUTDUPL_MOVE_RECT *pMoveRectBuffer,
            _Out_  UINT *pMoveRectsBufferSizeRequired)
  {
    IDXGIOutputDuplication* output = getOutput();
    HRESULT hr = output -> GetFrameMoveRects( 
            moveRectsBufferSize,
            pMoveRectBuffer,
            pMoveRectsBufferSizeRequired);
    if (FAILED(hr)) {
      throw IException("Faield to GetFrameMoveRects. HRESUL(0x%lx)", hr);
    }
  }
        
  void getFramePointerShape( 
            _In_  UINT pointerShapeBufferSize,
            _Out_writes_bytes_to_(pointerShapeBufferSize, *pPointerShapeBufferSizeRequired)  void *pPointerShapeBuffer,
            _Out_  UINT *pPointerShapeBufferSizeRequired,
            _Out_  DXGI_OUTDUPL_POINTER_SHAPE_INFO *pPointerShapeInfo)
  {
    IDXGIOutputDuplication* output = getOutput();
    HRESULT hr = output -> GetFramePointerShape( 
            pointerShapeBufferSize,
            pPointerShapeBuffer,
            pPointerShapeBufferSizeRequired,
            pPointerShapeInfo);
    if (FAILED(hr)) {
      throw IException("Faield to GetFramePointerShape. HRESUL(0x%lx)", hr);
    }
  }
        
  void mapDesktopSurface( 
            _Out_  DXGI_MAPPED_RECT *pLockedRect)
  {
    IDXGIOutputDuplication* output = getOutput();
    HRESULT hr = output -> MapDesktopSurface( 
            pLockedRect);
    if (FAILED(hr)) {
      throw IException("Faield to MapDesktopSurface. HRESUL(0x%lx)", hr);
    }
  }
        
  void unMapDesktopSurface()
  {
    IDXGIOutputDuplication* output = getOutput();
    HRESULT hr = output -> UnMapDesktopSurface();
    if (FAILED(hr)) {
      throw IException("Faield to UnMapDesktopSurface. HRESUL(0x%lx)", hr);
    }
  }
        
  void releaseFrame()
  {
    IDXGIOutputDuplication* output = getOutput();
    HRESULT hr = output -> ReleaseFrame();
    if (FAILED(hr)) {
      throw IException("Faield to ReleaseFrame. HRESUL(0x%lx)", hr);
    }
  }
        
};

}
