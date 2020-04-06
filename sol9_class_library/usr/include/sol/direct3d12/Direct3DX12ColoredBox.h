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
 *  Direct3DX12ColoredBox.h
 *
 *****************************************************************************/

//2016/12/25 Updated constructor to specify a position in a 3d-space.

#pragma once
#include <math.h>
#include <sol/direct3d12/Direct3DX12Shape.h>
#include <sol/direct3d12/D3D12PosColorVertex.h>

namespace SOL {

class Direct3DX12ColoredBox : public Direct3DX12Shape {
//private:
//  UINT indicesCount;
  
public:
  Direct3DX12ColoredBox(
        __in ID3D12Device*  device, 
        __in float          width  = 0.5f,
        __in float          height = 0.7f,
        __in float          depth  = 0.9f,
        __in float          x = 0.0f,
        __in float          y = 0.0f,
        __in float          z = 0.0f)
  :Direct3DX12Shape(device)
  {
    // Create a vertexBuffer and an indexBuffer
    createColoredCube(width, height, depth, x, y, z);
    
  }

  
  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosColorDesc(count); 
  }
  
  void createColoredCube(float width, float height, float depth, float x, float y, float z)
  {
    try {
  
        D3D12PosColorVertex vertices[] = {      
          { XMFLOAT3(-1.0f * width + x, -1.0f * height + y, -1.0f * depth + z), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
          { XMFLOAT3(-1.0f * width + x, -1.0f * height + y,  1.0f * depth + z), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
          { XMFLOAT3(-1.0f * width + x,  1.0f * height + y, -1.0f * depth + z), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
          { XMFLOAT3(-1.0f * width + x,  1.0f * height + y,  1.0f * depth + z), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
          { XMFLOAT3( 1.0f * width + x, -1.0f * height + y, -1.0f * depth + z), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
          { XMFLOAT3( 1.0f * width + x, -1.0f * height + y,  1.0f * depth + z), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
          { XMFLOAT3( 1.0f * width + x,  1.0f * height + y, -1.0f * depth + z), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
          { XMFLOAT3( 1.0f * width + x,  1.0f * height + y,  1.0f * depth + z), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },      
          };
      
        uint16_t indices[] = {
          0,2,1,  1,2,3,
          4,5,6,  5,7,6,
          0,1,5,  0,5,4,
          2,6,7,  2,7,3,
          0,4,6,  0,6,2,
          1,3,7, 1,7,5,
        };  
        
        createVertexBuffer(vertices, sizeof(vertices), sizeof(D3D12PosColorVertex), _countof(vertices));
        createIndexBuffer(indices, sizeof(indices), _countof(indices));
      
       // indicesCount = _countof(indices);
      
      } catch (Exception& ex) {
        ex.display();
      }    
  }


  ~Direct3DX12ColoredBox()
  {
  }
 

};

}

