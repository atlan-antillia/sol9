
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
 *  D3D10RasterizerDesc.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10DeviceChild.h>

/*
typedef struct D3D10_RASTERIZER_DESC
    {
    D3D10_FILL_MODE FillMode;
    D3D10_CULL_MODE CullMode;
    BOOL FrontCounterClockwise;
    INT DepthBias;
    FLOAT DepthBiasClamp;
    FLOAT SlopeScaledDepthBias;
    BOOL DepthClipEnable;
    BOOL ScissorEnable;
    BOOL MultisampleEnable;
    BOOL AntialiasedLineEnable;
    }   D3D10_RASTERIZER_DESC;
 */
 
namespace SOL {


class D3D10RasterizerDesc {
private:
  D3D10_RASTERIZER_DESC desc;
  
public:
  D3D10RasterizerDesc()
  {
    memset(&desc, 0, sizeof(desc));
  }
  

  operator D3D10_RASTERIZER_DESC*()
  {
    return &desc;
  }
  
  void fillMode(D3D10_FILL_MODE mode)
  {
    desc.FillMode = mode;
  }
  
  void cullMode(D3D10_CULL_MODE mode)
  {
    desc.CullMode = mode;
  }
  
  void frontCounterClockwise(BOOL frontCounterClockwise)
  {
    desc.FrontCounterClockwise =  frontCounterClockwise;
  }
    
  void depthBias(INT depthBias)
  {
    desc.DepthBias = depthBias;
  }

};

}
