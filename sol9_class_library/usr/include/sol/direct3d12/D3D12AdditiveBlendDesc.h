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
 *  D3D12AdditiveBlendDesc.h
 *
 *****************************************************************************/

// 2016/09/25

#include <sol/direct3d12/D3D12BlendDesc.h>

namespace SOL {

class D3D12AdditiveBlendDesc : public D3D12BlendDesc {

private:
  static  D3D12_RENDER_TARGET_BLEND_DESC getAdditiveBlendDesc()
  {
    static D3D12_RENDER_TARGET_BLEND_DESC rtbDesc;
    memset(&rtbDesc, 0, sizeof(rtbDesc));
      rtbDesc.BlendEnable = true;
      rtbDesc.SrcBlend       = D3D12_BLEND_SRC_ALPHA;
      rtbDesc.DestBlend      = D3D12_BLEND_ONE;
      rtbDesc.BlendOp        = D3D12_BLEND_OP_ADD;
      rtbDesc.SrcBlendAlpha  = D3D12_BLEND_ONE;
      rtbDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
      rtbDesc.BlendOpAlpha   = D3D12_BLEND_OP_ADD;
      rtbDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

    return rtbDesc;  
  }
        
public:
  D3D12AdditiveBlendDesc()
  :D3D12BlendDesc(getAdditiveBlendDesc())
  {
  }

};

}

