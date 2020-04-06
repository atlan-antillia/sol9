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
 *  Direct3DX12ColoredTriangle.h
 *
 *****************************************************************************/

//2016/01/20


#pragma once
#include <math.h>
#include <sol/direct3d12/Direct3DX12Shape.h>
#include <sol/direct3d12/D3D12PosColorVertex.h>

namespace SOL {

class Direct3DX12ColoredTriangle : public Direct3DX12Shape {
public:
  Direct3DX12ColoredTriangle(
        __in ID3D12Device*        device, 
        __in float width  = 1.0f,
        __in float height = 1.0f)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    // Create a vertexBuffer and an indexBuffer
    createColoredTriangle(width, height);
    
  }

  
  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosColorDesc(count); 
  }
  
  void createColoredTriangle(float width, float height)
  {
    try {
        
        D3D12PosColorVertex vertices[] = {
          {XMFLOAT3( 0.0f * width,  1.0f * height, 0.0f),  XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f) },
          {XMFLOAT3( 1.0f * width, -1.0f * height, 0.0f),  XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f) }, 
          {XMFLOAT3(-1.0f * width, -1.0f * height, 0.0f),  XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f) }, 
        };
        
        uint16_t indices[] = { 0, 1, 2, };  
    
        UINT strideInByte = sizeof(D3D12PosColorVertex);
        
        createVertexBuffer(vertices, sizeof(vertices), strideInByte, _countof(vertices));

        createIndexBuffer(indices, sizeof(indices), _countof(indices));

      } catch (Exception& ex) {
        ex.display();
      }    
  }


  ~Direct3DX12ColoredTriangle()
  {
  }
  
};

}

