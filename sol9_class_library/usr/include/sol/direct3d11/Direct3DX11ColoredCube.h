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
 *  Direct3DX11ColoredCube.h
 *
 *****************************************************************************/

//2016/02/10

#pragma once
#include <math.h>
#include <sol/direct3d11/Direct3DX11Shape.h>
#include <sol/direct3d11/D3D11PosColorVertex.h>

namespace SOL {

class Direct3DX11ColoredCube : public Direct3DX11Shape {
public:
  Direct3DX11ColoredCube(
        __in Direct3D11Device*        device, 
        __in Direct3D11DeviceContext* context,
        __in float                    size = 1.0f)
  :Direct3DX11Shape(device,  context)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (context == NULL ) {
      throw IException("Invalid devieContex.t");
    }
    // Create a vertexBuffer and an indexBuffer
    createColoredCube(size);
    
  }

public:
  Direct3DX11ColoredCube(
        __in Direct3D11Device*           device, 
        __in Direct3D11DeviceContext*    context,
        __in Direct3D11Blob*             vertexShaderBlob, 
        __in float size = 1.0f)
  :Direct3DX11Shape(device,  context)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (context == NULL ) {
      throw IException("Invalid devieContex.t");
    }
    if (vertexShaderBlob == NULL) {
      throw IException("Invalid vertexShaderBlob");
    }       
    // Create a vertexBuffer and an indexBuffer
    createColoredCube(size);
    
    createInputLayout(vertexShaderBlob); 
  }

  
  virtual const D3D11_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D11InputElements::getPosColorDesc(count); 
  }
  
  void createColoredCube(float size)
  {
    try {
        Direct3D11Device* d3d11Device = getD3D11Device();
        Direct3D11DeviceContext* d3d11DeviceContext = getD3D11DeviceContext();
        
        D3D11PosColorVertex vertices[] = {
          { XMFLOAT3( -1.0f * size,  1.0f * size, -1.0f * size ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * size,  1.0f * size, -1.0f * size ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * size,  1.0f * size,  1.0f * size ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
          { XMFLOAT3( -1.0f * size,  1.0f * size,  1.0f * size ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
          { XMFLOAT3( -1.0f * size, -1.0f * size, -1.0f * size ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * size, -1.0f * size, -1.0f * size ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * size, -1.0f * size,  1.0f * size ), XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f ) },
          { XMFLOAT3( -1.0f * size, -1.0f * size,  1.0f * size ), XMFLOAT4( 0.0f, 0.0f, 0.0f, 1.0f ) },
        };
        
        UINT indices[] = {
          3,1,0,  2,1,3,
          0,5,4,  1,5,0,
          3,4,7,  0,4,3,
          1,6,5,  2,6,1,
          2,7,6,  3,7,2,
          6,4,5,  7,4,6,
        };  
        createVertexBuffer(vertices, sizeof(vertices), CountOf(vertices));
        createIndexBuffer(indices, sizeof(indices), CountOf(indices));

      } catch (Exception& ex) {
        ex.display();
      }    
  }


  ~Direct3DX11ColoredCube()
  {
  }
  
};

}

