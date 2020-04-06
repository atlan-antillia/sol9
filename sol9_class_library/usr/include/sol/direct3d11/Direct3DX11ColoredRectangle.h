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
 *  Direct3DX11ColoredRectangle.h
 *
 *****************************************************************************/

//2016/01/20


#pragma once
#include <math.h>
#include <sol/direct3d11/Direct3DX11Shape.h>


namespace SOL {

class Direct3DX11ColoredRectangle : public Direct3DX11Shape {
public:
  Direct3DX11ColoredRectangle(
        __in Direct3D11Device*        device, 
        __in Direct3D11DeviceContext* context,
        __in float width  = 1.0f, 
        __in float height = 1.0f)
  :Direct3DX11Shape(device,  context)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    if (context == NULL ) {
      throw IException("Invalid devieContex.t");
    }
    
    if (width < 0.0f || height < 0.0f) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createColoredRectangle( width, height );

  }

public:
  Direct3DX11ColoredRectangle(
        __in Direct3D11Device*        device, 
        __in Direct3D11DeviceContext* context,
        __in Direct3D11Blob*          vertexShaderBlob,
        __in float width  = 1.0f, 
        __in float height = 1.0f)
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
    if (width < 0.0f || height < 0.0f) {
      throw IException("Invalid parameter"); 
    }
    // Create a vertexBuffer and an indexBuffer
    createColoredRectangle( width, height );

    createInputLayout(vertexShaderBlob); 
  }

  virtual const D3D11_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D11InputElements::getPosColorDesc(count); 
  }
  
  void createColoredRectangle( float width, float height )
  { 
    try {
        Direct3D11Device* d3d11Device = getD3D11Device();
        Direct3D11DeviceContext* d3d11DeviceContext = getD3D11DeviceContext();
        
        D3D11PosColorVertex vertices[] = {
        { XMFLOAT3( -1.0f * width,  1.0f * height, 0.0f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f) }, 
        { XMFLOAT3(  1.0f * width,  1.0f * height, 0.0f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f) }, 
        { XMFLOAT3( -1.0f * width, -1.0f * height, 0.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f) }, 
        { XMFLOAT3(  1.0f * width, -1.0f * height, 0.0f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f) }, 
        };
        
        UINT indices[] = {
          0,1,2,
          2,1,3,
        };

      createVertexBuffer(vertices, sizeof(vertices), CountOf(vertices));
      createIndexBuffer(indices, sizeof(indices), CountOf(indices) );
    } catch (Exception& ex) {
        ex.display();
    }
  }


  ~Direct3DX11ColoredRectangle()
  {
  }
};

}

