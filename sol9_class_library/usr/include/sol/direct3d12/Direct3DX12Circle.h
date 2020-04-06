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
 *  Direct3DX12Circle.h
 *
 *****************************************************************************/

//2016/12/25 Updated

#pragma once

#include <sol/direct3d12/Direct3DX12Shape.h>
#include <sol/direct3d12/D3D12PosVertex.h>

namespace SOL {

class Direct3DX12Circle : public Direct3DX12Shape {
private:
  static const UINT CIRCLE_ANGLE = 360;
  
  D3D12PosVertex  vertices[CIRCLE_ANGLE];
  
public:
  Direct3DX12Circle(
        __in ID3D12Device*  device, 
        __in float          px = 0.0f, 
        __in float          py = 0.0f, 
        __in float          pz = 0.5f,
        __in float          radius  = 1.0f)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid device.");
    }

    if (radius < 0.0f) {
      throw IException("Invalid parameter."); 
    }
    // Create a vertexBuffer and an indexBuffer
    createCircle(px, py, pz, radius);    
  }

  
  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosColorDesc(count); 
  }
  
  void createCircle(float px, float py, float pz, float radius)
  {
    UINT vertexCount = CIRCLE_ANGLE;
 
    for (UINT i = 0; i<vertexCount - 1; i += 2) {
        vertices[i    ].pos = XMFLOAT3(px + radius * COS(i    ), py + radius * SIN(i    ), pz);
        vertices[i + 1].pos = XMFLOAT3(px + radius * COS(i + 1), py + radius * SIN(i + 1), pz);
    }
    UINT sizeInByte = sizeof(vertices);
      
    UINT strideInByte = sizeof(D3D12PosVertex);

    createVertexBuffer(vertices,  sizeInByte, strideInByte, vertexCount);
  }

  XMFLOAT3 getOrbitPosition(int angle)
  {      
    if (angle > CIRCLE_ANGLE) {
      angle -= CIRCLE_ANGLE;
    }
    if (angle < 0) {
        angle = 0;
    }
    return vertices[angle].pos;          
  }   
  
  virtual void drawInstanced(Direct3D12GraphicsCommandList* graphicsCommandList)
  {
    graphicsCommandList->setIAPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
    
    Direct3D12VertexBuffer*  vertexBuffer = getVertexBuffer();

    graphicsCommandList->setIAVertexBuffers(0, 1, *vertexBuffer);

    graphicsCommandList->drawInstanced(getVertexCount(), 1, 0, 0);
  }
  
};

}
