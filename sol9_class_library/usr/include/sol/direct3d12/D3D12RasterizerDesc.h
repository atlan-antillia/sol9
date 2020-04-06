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
 *  D3D12RasterizerDesc.h
 *
 *****************************************************************************/

// 2016/09/25
#pragma once

namespace SOL {

class D3D12RasterizerDesc {

private:
  D3D12_RASTERIZER_DESC rasterDesc;
/*
typedef struct D3D12_RASTERIZER_DESC {
  D3D12_FILL_MODE                       FillMode;
  D3D12_CULL_MODE                       CullMode;
  BOOL                                  FrontCounterClockwise;
  INT                                   DepthBias;
  FLOAT                                 DepthBiasClamp;
  FLOAT                                 SlopeScaledDepthBias;
  BOOL                                  DepthClipEnable;
  BOOL                                  MultisampleEnable;
  BOOL                                  AntialiasedLineEnable;
  UINT                                  ForcedSampleCount;
  D3D12_CONSERVATIVE_RASTERIZATION_MODE ConservativeRaster;
} D3D12_RASTERIZER_DESC;
  */
public:
  D3D12RasterizerDesc(
          D3D12_FILL_MODE  fillMode = D3D12_FILL_MODE_SOLID,
          D3D12_CULL_MODE  cullMode = D3D12_CULL_MODE_NONE,
          BOOL ccWise   = false)
  {
    //Default rasterizer desc.
    memset(&rasterDesc, 0, sizeof(rasterDesc));
    rasterDesc.FillMode              = fillMode; 
    rasterDesc.CullMode              = cullMode; 
    rasterDesc.FrontCounterClockwise = ccWise ;  
    rasterDesc.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
    rasterDesc.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
    rasterDesc.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
    rasterDesc.DepthClipEnable       = true;
    rasterDesc.MultisampleEnable     = false;
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.ForcedSampleCount     = 0;
    rasterDesc.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
  }

  operator D3D12_RASTERIZER_DESC()
  {
    return rasterDesc;
  }   
  
  void setDepthBias(INT depthBias)
  {
    rasterDesc.DepthBias = depthBias;
  }
  
  void setDepthBiasClamp(FLOAT depthBiasClamp)
  {
    rasterDesc.DepthBiasClamp = depthBiasClamp;
  }
  
  void setSlopeScaledDepthBias(FLOAT slopeScaledDepthBias)
  {
    rasterDesc.SlopeScaledDepthBias = slopeScaledDepthBias;
  }
  void setDepthClipEnable(BOOL enable) 
  {
    rasterDesc.DepthClipEnable = enable;
  }
  
  void setMultisampleEnable(BOOL enable)
  {
    rasterDesc.MultisampleEnable = enable;
  }
  
  void setAntialiasedLineEnable(BOOL enable)
  {
    rasterDesc.AntialiasedLineEnable = enable;
  }
  void setForcedSampleCount(UINT count)
  {
    rasterDesc.ForcedSampleCount = count;
  }
  
  void setConservativeRaster(D3D12_CONSERVATIVE_RASTERIZATION_MODE mode)
  {
    rasterDesc.ConservativeRaster = mode;
  }
};

}

    