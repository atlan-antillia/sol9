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
 *  DirectXGIOutput.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/dxgi/DirectXGIObject.h>

namespace SOL {
  
class DirectXGIOutput : public DirectXGIObject {
public:
  DirectXGIOutput(IDXGISwapChain* chain,
            __out  BOOL *pFullscreen)
  :DirectXGIObject()
  {
    IDXGIOutput* output = NULL;
    HRESULT hr = chain -> GetFullscreenState( 
              pFullscreen,
              &output);
    if (SUCCEEDED(hr)) {
      set(output);
    } else {
      throw IException("Failed to GetFullscreenState. HRESULT(0x%lx)", hr)
    }
  }      
        

  DirectXGIOutput(IDXGISwapChain* chain)
  :DirectXGIObject()  
  {
    IDXGIOutput* output = NULL;
    HRESULT hr = chain -> GetContainingOutput( 
              &output);
    if (SUCCEEDED(hr)) {
      set(output);
    } else {
      throw IException("Failed to GetContainingOutput. HRESULT(0x%lx)", hr)
    }
  }      

  ~DirectXGIOutput() 
  {
  }
  
  operator IDXGIOutput*()
  {
    return getOutput();
  }
  
  IDXGIOutput* getOutput()
  {
    IDXGIOutput* output = (IDXGIOutput*)getIUnknown();
    if (output) {
      return output;
    } else {
      throw IException("IDXGIOutput is NULL.");
    }
  }
  
  void getDesc( 
            __out  DXGI_OUTPUT_DESC *pDesc)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> GetDesc( 
              pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDesc. HRESULT(0x%lx)", hr);
    }
  }
  
  void getDisplayModeList( 
            __in DXGI_FORMAT enumFormat,
            __in UINT flags,
            __inout  UINT *pNumModes,
            __out  DXGI_MODE_DESC *pDesc)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> GetDisplayModeList( 
              enumFormat,
              flags,
              pNumModes,
              pDesc);
    if (FAILED(hr)) {
      throw IException("Failed to GetDisplayModeList. HRESULT(0x%lx)", hr);
    }
  }
        
  void findClosestMatchingMode( 
            __in  const DXGI_MODE_DESC *pModeToMatch,
            __out  DXGI_MODE_DESC *pClosestMatch,
            __in_opt  IUnknown *pConcernedDevice)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> FindClosestMatchingMode( 
              pModeToMatch,
              pClosestMatch,
              pConcernedDevice);
    if (FAILED(hr)) {
      throw IException("Failed to FindClosestMatchingMode. HRESULT(0x%lx)", hr);
    }
  }
        
  void waitForVBlank()
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> WaitForVBlank();
    if (FAILED(hr)) {
      throw IException("Failed to WaitForVBlank. HRESULT(0x%lx)", hr);
    }
  }
        
  void takeOwnership( 
            __in  IUnknown *pDevice,
            BOOL exclusive)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> TakeOwnership( 
              pDevice,
              exclusive);
    if (FAILED(hr)) {
      throw IException("Failed to TakeOwnership. HRESULT(0x%lx)", hr);
    }
  }
        
  void releaseOwnership()
  {
    IDXGIOutput* output = getOutput();
    output -> ReleaseOwnership();
  }
        
  void getGammaControlCapabilities( 
            __out  DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> GetGammaControlCapabilities( 
              pGammaCaps);
    if (FAILED(hr)) {
      throw IException("Failed to GetGammaControlCapabilities. HRESULT(0x%lx)", hr);
    }
  }
        
  void setGammaControl( 
            __in  const DXGI_GAMMA_CONTROL *pArray)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> SetGammaControl( 
              pArray);
    if (FAILED(hr)) {
      throw IException("Failed to SetGammaControl. HRESULT(0x%lx)", hr);
    }
  }
        
  void getGammaControl( 
            __out  DXGI_GAMMA_CONTROL *pArray)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> GetGammaControl( 
              pArray);
    if (FAILED(hr)) {
      throw IException("Failed to GetGammaControl. HRESULT(0x%lx)", hr);
    }
  }
        
  void setDisplaySurface( 
            __in  IDXGISurface *pScanoutSurface)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> SetDisplaySurface( 
              pScanoutSurface);
    if (FAILED(hr)) {
      throw IException("Failed to SetDisplaySurface. HRESULT(0x%lx)", hr);
    }
  }
        
  void getDisplaySurfaceData( 
            __in  IDXGISurface *pDestination)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> GetDisplaySurfaceData( 
              pDestination);
    if (FAILED(hr)) {
      throw IException("Failed to GetDisplaySurfaceData. HRESULT(0x%lx)", hr);
    }
  }
        
  void getFrameStatistics( 
            __out  DXGI_FRAME_STATISTICS *pStats)
  {
    IDXGIOutput* output = getOutput();
    HRESULT hr = output -> GetFrameStatistics( 
              pStats);
    if (FAILED(hr)) {
      throw IException("Failed to GetFrameStatistics. HRESULT(0x%lx)", hr);
    }
  }
        
};

}
