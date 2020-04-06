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
 *  Direct3D12PipelineState.h
 *
 *****************************************************************************/

// 2016/09/25
// 2017/01/10 Added a new constructor.

#pragma once

#include <sol/direct3d12/D3D12RasterizerDesc.h>
#include <sol/direct3d12/D3D12BlendDesc.h>

#include <sol/direct3d12/Direct3D12Pageable.h>
#include <sol/direct3d12/D3D12GraphicsPipelineStateDesc.h>

namespace SOL {

class Direct3D12PipelineState : public Direct3D12Pageable {
    
public:
  Direct3D12PipelineState(
        __in ID3D12Device*                   device,
        __in ID3D12RootSignature*            rootSignature,
        __in const D3D12_INPUT_ELEMENT_DESC* inputElements,
        __in const int                       countOfInputElements,
        __in D3D12RasterizerDesc             rasterDesc,
        __in D3D12BlendDesc                  blendDesc,
        __in const TCHAR*                    vertexShaderFullpath,
        __in const TCHAR*                    pixelShaderFullpath)
  :Direct3D12Pageable()
  {
    if (device               == nullptr || 
        rootSignature        == nullptr ||
        inputElements        == nullptr  ||
        vertexShaderFullpath == nullptr ||
        pixelShaderFullpath  == nullptr ) {
      throw IException("Invalid paramters");
    }
    
    //Create a graphicPipelineStateDes.
    D3D12GraphicsPipelineStateDesc graphicsPipelineStateDesc(rootSignature);
        
    graphicsPipelineStateDesc.setInputLayput(inputElements, countOfInputElements);
      
    graphicsPipelineStateDesc.setRasterizerState(rasterDesc);
    graphicsPipelineStateDesc.setBlendState(blendDesc);
      
    graphicsPipelineStateDesc.setVertexShader(vertexShaderFullpath);
    graphicsPipelineStateDesc.setPixelShader(pixelShaderFullpath);

    ID3D12PipelineState* pipelineState = NULL;
    HRESULT hr = device -> CreateGraphicsPipelineState( 
            graphicsPipelineStateDesc,
            IID_PPV_ARGS(&pipelineState) );
    if (SUCCEEDED(hr)) {
      set(pipelineState);
    } else {
      throw IException("Failed to CreateGraphicsPipelineState. HRESULT(0x%lx)", hr);
    }
  }
  
public:
  Direct3D12PipelineState(
        __in ID3D12Device*  device,
        __in const D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc)
  :Direct3D12Pageable()
  {
    if (device == nullptr || desc == nullptr) {
      throw IException("Invalid paramters");
    }
    
    ID3D12PipelineState* pipelineState = NULL;
    HRESULT hr = device -> CreateGraphicsPipelineState( 
            desc,
            IID_PPV_ARGS(&pipelineState) );
    if (SUCCEEDED(hr)) {
      set(pipelineState);
    } else {
      throw IException("Failed to CreateGraphicsPipelineState. HRESULT(0x%lx)", hr);
    }
  }
  
  Direct3D12PipelineState(
    __in ID3D12PipelineState* pipelineState)
  :Direct3D12Pageable(pipelineState)
  {
  }
  
  ~Direct3D12PipelineState()
  { 
  }

  operator ID3D12PipelineState*()
  {
    return getPipelineState();
  }

  ID3D12PipelineState* getPipelineState()
  {
    ID3D12PipelineState* pipelineState = (ID3D12PipelineState*)getIUnknown();
    if (pipelineState) {
        return pipelineState;
    } else {
      throw IException("ID3D12PipelineState is NULL.");
    }
  }

  void getCachedBlob(_COM_Outptr_  ID3DBlob **ppBlob)
  {
    ID3D12PipelineState* pipelineState = getPipelineState();
    HRESULT hr = pipelineState->GetCachedBlob(ppBlob);
    if (FAILED(hr)) {
      throw IException("Failed to GetCachedBlob. HRESULT(0x%lx)", hr);
    }
  }

};

}
    
