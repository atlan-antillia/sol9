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
 *  DirectXGISwapChain2.h
 *
 *****************************************************************************/
 
#pragma once

#include <dxgi1_3.h>

#include <sol/dxgi/DirectXGISwapChain1.h>

namespace SOL {

class DirectXGISwapChain2 : public DirectXGISwapChain1 {
  
public:
  DirectXGISwapChain2()
  :DirectXGISwapChain1()
  {
  }

  DirectXGISwapChain2(IDXGISwapChain2* chain)
  :DirectXGISwapChain1(chain)
  {
  }


  ~DirectXGISwapChain2()
  {
  }
  
  operator IDXGISwapChain2*()
  {
    return getSwapChain2();
  }

  IDXGISwapChain2* getSwapChain2()
  {
    IDXGISwapChain2* chain = (IDXGISwapChain2*)getIUnknown();
    if (chain) {
      return chain;
    } else {
      throw IException("IDXGISwapChain2 is NULL.")
    }
  }

  //
  void setSourceSize( 
            UINT width,
            UINT height)
  {
    IDXGISwapChain2* chain2 = getSwapChain2();
    HRESULT hr = chain2->SetSourceSize( 
              width,
              height);
    if (FAILED(hr)) {
      throw IException("Failed to SetSourceSize. HRESULT(0x%lx)", hr);
    }
  }
  
  void getSourceSize( 
            _Out_  UINT *pWidth,
            _Out_  UINT *pHeight)
  {
    IDXGISwapChain2* chain2 = getSwapChain2();
    HRESULT hr = chain2->GetSourceSize( 
            pWidth,
            pHeight);
    if (FAILED(hr)) {
      throw IException("Failed to GetSourceSize. HRESULT(0x%lx)", hr);
    }
  }
        
  void setMaximumFrameLatency( 
            UINT maxLatency)
  {
    IDXGISwapChain2* chain2 = getSwapChain2();
    HRESULT hr = chain2->SetMaximumFrameLatency( 
            maxLatency);
    if (FAILED(hr)) {
      throw IException("Failed to . HRESULT(0x%lx)", hr);
    }
  }
        
  void getMaximumFrameLatency( 
            _Out_  UINT *pMaxLatency)
  {
    IDXGISwapChain2* chain2 = getSwapChain2();
    HRESULT hr = chain2->GetMaximumFrameLatency( 
            pMaxLatency);
    if (FAILED(hr)) {
      throw IException("Failed to GetMaximumFrameLatency. HRESULT(0x%lx)", hr);
    }
  }
        
  HANDLE getFrameLatencyWaitableObject()
  {
    IDXGISwapChain2* chain2 = getSwapChain2();
    return chain2->GetFrameLatencyWaitableObject();
  }
        
  void setMatrixTransform( 
            const DXGI_MATRIX_3X2_F *pMatrix)
  {
    IDXGISwapChain2* chain2 = getSwapChain2();
    HRESULT hr = chain2->SetMatrixTransform( 
            pMatrix);
    if (FAILED(hr)) {
      throw IException("Failed to SetMatrixTransform. HRESULT(0x%lx)", hr);
    }
  }
        
  void getMatrixTransform( 
            _Out_  DXGI_MATRIX_3X2_F *pMatrix)
  {
    IDXGISwapChain2* chain2 = getSwapChain2();
    HRESULT hr = chain2->GetMatrixTransform( 
            pMatrix);
    if (FAILED(hr)) {
      throw IException("Failed to GetMatrixTransform. HRESULT(0x%lx)", hr);
    }
  }


};
}
