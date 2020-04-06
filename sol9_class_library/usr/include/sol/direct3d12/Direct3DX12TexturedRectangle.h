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
 *  Direct3DX12TexturedRectangle.h
 *
 *****************************************************************************/

//2016/02/10 Updated
//2016/12/20 Updated

#pragma once
#include <math.h>
#include <sol/direct3d12/Direct3DX12Shape.h>
#include <sol/direct3d12/D3D12Rectangle.h>


namespace SOL {

class Direct3DX12TexturedRectangle : public Direct3DX12Shape {
public:
  Direct3DX12TexturedRectangle(
        __in ID3D12Device* device, 
        __in float         width,   // = 1.0f, 
        __in float         height) // = 1.0f)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (width < 0.0f || height < 0.0f) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createTexturedRectangle(0.0f, 0.0f, 0.0f, width, height );  
  }

public:
  Direct3DX12TexturedRectangle(
        __in ID3D12Device* device,
        __in const D3D12Rectangle& rectangle)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (rectangle.width < 0.0f || rectangle.height < 0.0f) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createTexturedRectangle(rectangle.x, rectangle.y, rectangle.z, rectangle.width, rectangle.height );  
  }
  

  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosTexCoordDesc(count); 
  }

public:
  Direct3DX12TexturedRectangle(
        __in ID3D12Device* device,
        __in float         x,
        __in float         y,
        __in float         z,
        __in float         width, 
        __in float         height)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (width < 0.0f || height < 0.0f) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createTexturedRectangle(x, y, z, width, height );  
  }
  
  void createTexturedRectangle(float x, float y, float z,  float width, float height )
  { 
    try {
        
        D3D12PosTexCoordVertex vertices[] = {
        { XMFLOAT3( -1.0f * width + x,  1.0f * height + y, z ), XMFLOAT2( 0.0f, 0.0f ) }, 
        { XMFLOAT3(  1.0f * width + x,  1.0f * height + y, z ), XMFLOAT2( 1.0f, 0.0f ) }, 
        { XMFLOAT3( -1.0f * width + x, -1.0f * height + y, z ), XMFLOAT2( 0.0f, 1.0f ) }, 
        { XMFLOAT3(  1.0f * width + x, -1.0f * height + y, z ), XMFLOAT2( 1.0f, 1.0f ) }, 
        };
        //2016/11/15
        uint16_t indices[] = {
          0,1,2,
          2,1,3,
        };

      createVertexBuffer(vertices, sizeof(vertices), sizeof(D3D12PosTexCoordVertex), _countof(vertices));
      createIndexBuffer(indices, sizeof(indices), _countof(indices) );
    } catch (Exception& ex) {
        ex.display();
    }
  }


  ~Direct3DX12TexturedRectangle()
  {
  }
};

}

