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
 *  Direct3DX12Shape.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d12/D3D12InputElements.h>

#include <sol/direct3d12/Direct3D12Device.h>
#include <sol/direct3d12/Direct3D12GraphicsCommandList.h>

#include <sol/direct3d12/Direct3D12Object.h>
#include <sol/direct3d12/Direct3DBlob.h>


#include <sol/direct3d12/Direct3D12VertexBuffer.h>
#include <sol/direct3d12/Direct3D12IndexBuffer.h>

#include <sol/direct3d12/D3D12InputElements.h>
#include <sol/direct3d12/D3D12PosNormalVertex.h>
#include <sol/direct3d12/D3D12PosColorVertex.h>
#include <sol/direct3d12/D3D12PosTexCoordVertex.h>

namespace SOL {

class Direct3DX12Shape : public Direct3D12Object{
private:  
  ID3D12Device*               d3d12Device;         //Shallow copy
    
  Direct3D12VertexBuffer*             vertexBuffer;
  Direct3D12IndexBuffer*             indexBuffer;

  UINT                          vertexStride;
  int                           vertexCount;
  DXGI_FORMAT                   dxgiFormat;
  int                           indexCount;
  
public:
  Direct3DX12Shape(ID3D12Device* device)//, Direct3D12GraphicsCommandList* list)
  :Direct3D12Object(),
  d3d12Device(device),
  vertexBuffer(NULL),
  indexBuffer(NULL),
  vertexCount(0),
  indexCount(0)
  {
    if (device == NULL ) {
      throw IException("Invalid argument."); 
    }
  }
  
  
  ~Direct3DX12Shape()
  {
    delete vertexBuffer;
    delete indexBuffer;
  }
  
  //Default getInputElmentDesc,
  //If needed, please define your one getInputElementDesc in a subclass derived from this class,
  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosNormalDesc(count); 
  }
  
  virtual void createVertexBuffer(D3D12PosNormalVertex* vertices,  size_t bytes, size_t vertexCount)
  {
    createVertexBuffer((const void*)vertices, bytes, sizeof(D3D12PosNormalVertex), vertexCount);
  }
  
  /*virtual void createVertexBuffer(D3D12PosTexCoordVertex* vertices,  size_t bytes, size_t vertexCount)
  {
    createVertexBuffer((const void*)vertices, bytes, sizeof(D3D12PosTexCoordVertex), vertexCount);
  }
  
  virtual void createVertexBuffer(D3D12PosColorVertex* vertices,  size_t bytes, size_t vertexCount)
  {
    createVertexBuffer((const void*)vertices, bytes, sizeof(D3D12PosColorVertex), vertexCount);
  }
  */
  void createVertexBuffer(const void* vertices, size_t bytes, size_t stride, size_t vertCount)
  {
    try {
      //1 Create a vertex buffer for the vertex from the above parameters.
      vertexBuffer = new Direct3D12VertexBuffer(d3d12Device, vertices, stride, bytes);
      
      vertexCount = vertCount;
      vertexStride  = stride;
      
    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  
  virtual void createIndexBuffer(UINT* indices, size_t bytes, size_t inCount)
  {
    createIndexBuffer((const void*)indices,  DXGI_FORMAT_R32_UINT, bytes, inCount);
  }
    
  //This is the case that indices is an array of WORDs. 
  virtual void createIndexBuffer(WORD* indices, size_t bytes, size_t inCount)
  {
    createIndexBuffer((const void*)indices, DXGI_FORMAT_R16_UNORM, bytes, inCount);
  }
   
  void createIndexBuffer(const void* indices, DXGI_FORMAT format, size_t bytes, size_t inCount)
  {
    try {
      indexCount = inCount;
      dxgiFormat     = format;
      // Create an indexBuffer from above parameters.
      indexBuffer= new Direct3D12IndexBuffer(d3d12Device, indices, bytes);

    } catch (Exception& ex) {
      ex.display();
    }
  }
  

  ID3D12Device* getD3D12Device()
  {
    return d3d12Device;
  }
        

  Direct3D12VertexBuffer*  getVertexBuffer()
  {
    return vertexBuffer;
  }
  
  Direct3D12IndexBuffer* getIndexBuffer()
  {
    return indexBuffer;
  }
   
  int getVertexCount()
  {
    return vertexCount;
  }
  
  int getIndexCount()
  {
    return indexCount;
  }


  //Define your own method in your subclass derived from this class.
  virtual void draw(Direct3D12GraphicsCommandList* graphicsCommandList)
  {
  
    //Call drawSomething method of Direct3D12GraphicsCommandList 
  }
  
  virtual void drawIndexedInstanced(Direct3D12GraphicsCommandList* graphicsCommandList)
  {
    graphicsCommandList->setIAPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    graphicsCommandList->setIAVertexBuffers(0, 1, *vertexBuffer);
        
    graphicsCommandList->setIAIndexBuffer(*indexBuffer);
        
    graphicsCommandList->drawIndexedInstanced(getIndexCount(), 1, 0, 0, 0);
  }
  
   virtual void drawInstanced(Direct3D12GraphicsCommandList* graphicsCommandList)
  {
    graphicsCommandList->setIAPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    graphicsCommandList->setIAVertexBuffers(0, 1, *vertexBuffer);
        
    graphicsCommandList->setIAIndexBuffer(*indexBuffer);
        
    graphicsCommandList-> drawInstanced( getVertexCount(), 1, 0, 0 );
  }
  
  
    float SIN(int degree)
    {
      float radian = (float)degree * MATH_PI / 180.0f;
      return (float)sin(radian);
    }
  
    float COS(int degree)
    { 
      float radian = (float)degree * MATH_PI / 180.0f;
      return (float)cos(radian);
    }
};

}

