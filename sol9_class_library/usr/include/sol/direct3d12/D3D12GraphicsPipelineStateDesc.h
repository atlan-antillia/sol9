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
 *  D3D12GraphicsPipelineStateDesc.h
 *
 *****************************************************************************/

//2016/10/01

#pragma once

#include <sol/direct3d12/Direct3D12Object.h>
#include <sol/BinaryFileReader.h>

/*
typedef struct D3D12_GRAPHICS_PIPELINE_STATE_DESC {
  ID3D12RootSignature                *pRootSignature;
  D3D12_SHADER_BYTECODE              VS;
  D3D12_SHADER_BYTECODE              PS;
  D3D12_SHADER_BYTECODE              DS;
  D3D12_SHADER_BYTECODE              HS;
  D3D12_SHADER_BYTECODE              GS;
  D3D12_STREAM_OUTPUT_DESC           StreamOutput;
  D3D12_BLEND_DESC                   BlendState;
  UINT                               SampleMask;
  D3D12_RASTERIZER_DESC              RasterizerState;
  D3D12_DEPTH_STENCIL_DESC           DepthStencilState;
  D3D12_INPUT_LAYOUT_DESC            InputLayout;
  D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue;
  D3D12_PRIMITIVE_TOPOLOGY_TYPE      PrimitiveTopologyType;
  UINT                               NumRenderTargets;
  DXGI_FORMAT                        RTVFormats[8];
  DXGI_FORMAT                        DSVFormat;
  DXGI_SAMPLE_DESC                   SampleDesc;
  UINT                               NodeMask;
  D3D12_CACHED_PIPELINE_STATE        CachedPSO;
  D3D12_PIPELINE_STATE_FLAGS         Flags;
} D3D12_GRAPHICS_PIPELINE_STATE_DESC;

*/

namespace SOL {

class D3D12GraphicsPipelineStateDesc {

private:
  BinaryFileReader* vertexShader;
  BinaryFileReader* pixelShader;
  
  
  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc;
  
public:
  D3D12GraphicsPipelineStateDesc(
        __in ID3D12RootSignature*           signature,
        __in D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
        __in DXGI_FORMAT                   rtvFormat = DXGI_FORMAT_R8G8B8A8_UNORM,//DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,  2016/11/03
        __in DXGI_FORMAT                   dsvFormat = DXGI_FORMAT_D32_FLOAT)
  :vertexShader(NULL),
   pixelShader(NULL)
  {
    if (signature == nullptr) {
      throw IException("RootSignature is NULL.");
    }
    memset(&desc, 0, sizeof(desc));
     
    //Set some default values.
    desc.DepthStencilState.DepthEnable   = TRUE;
    desc.DepthStencilState.StencilEnable = FALSE;
    desc.SampleMask                      = UINT_MAX;
    desc.PrimitiveTopologyType           = topologyType; 
    desc.NumRenderTargets                = 1;
    desc.RTVFormats[0]                   = rtvFormat; 
    
    desc.DSVFormat                       = dsvFormat; 
    desc.SampleDesc.Count                = 1;    
    
    desc.pRootSignature                  = signature;
 
    //Set a default depthStencilState
    //desc.DepthStencilState.StencilEnable    = FALSE;                            
    //desc.DepthStencilState.DepthEnable      = FALSE; //TRUE;                             
    
    desc.DepthStencilState.DepthFunc        = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    desc.DepthStencilState.DepthWriteMask   = D3D12_DEPTH_WRITE_MASK_ALL;
/////////////////////////
//    desc.DepthStencilState.StencilReadMask  = D3D12_DEFAULT_STENCIL_READ_MASK;
//    desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
/*
    desc.DepthStencilState.FrontFace.StencilFailOp      = D3D12_STENCIL_OP_KEEP;
    desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
    desc.DepthStencilState.FrontFace.StencilPassOp      = D3D12_STENCIL_OP_KEEP;
    desc.DepthStencilState.FrontFace.StencilFunc        = D3D12_COMPARISON_FUNC_ALWAYS;

    desc.DepthStencilState.BackFace.StencilFailOp      = D3D12_STENCIL_OP_KEEP;
    desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
    desc.DepthStencilState.BackFace.StencilPassOp      = D3D12_STENCIL_OP_KEEP;
    desc.DepthStencilState.BackFace.StencilFunc        = D3D12_COMPARISON_FUNC_ALWAYS;
    */
  }
  
  
  ~D3D12GraphicsPipelineStateDesc()
  {
    delete vertexShader;
    delete pixelShader;
  }
  
  operator D3D12_GRAPHICS_PIPELINE_STATE_DESC*()
  {
    return &desc;
  }
  
  void setInputLayput(const D3D12_INPUT_ELEMENT_DESC* inputElements, UINT count)
  {
    desc.InputLayout = {inputElements, count};
  }
  
  void setVertexShader(const TCHAR* filename)
  {
    vertexShader = new BinaryFileReader(filename);
    desc.VS = {vertexShader->getBuffer(), vertexShader->getSize()};
  }

  void setPixelShader(const TCHAR* filename)
  {
    pixelShader = new BinaryFileReader(filename);
    desc.PS = {pixelShader->getBuffer(), pixelShader->getSize()};
  }

  void setRasterizerState(const D3D12_RASTERIZER_DESC rsDesc)
  {
    desc.RasterizerState  = rsDesc;
  }
  
  void setBlendState(const D3D12_BLEND_DESC bsDesc)
  {
    desc.BlendState = bsDesc;
  }
  
};

}

