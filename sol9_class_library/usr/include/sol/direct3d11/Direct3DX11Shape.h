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
 *  Direct3DX11Shape.h
 *
 *****************************************************************************/

// Updated 2016/02/21
// Updated 2016/03/01

#pragma once

#include <sol/direct3d11/D3D11InputElements.h>

#include <sol/direct3d11/Direct3D11Device.h>
#include <sol/direct3d11/Direct3D11DeviceContext.h>

#include <sol/direct3d11/Direct3DX11Object.h>
#include <sol/direct3d11/Direct3D11Blob.h>

#include <sol/direct3d11/Direct3D11InputLayout.h>
#include <sol/direct3d11/Direct3D11ShaderResourceView.h>
#include <sol/direct3d11/Direct3D11SamplerState.h>

#include <sol/direct3d11/Direct3D11Buffer.h>
#include <sol/direct3d11/D3D11InputElements.h>
#include <sol/direct3d11/D3D11PosNormalVertex.h>
#include <sol/direct3d11/D3D11PosColorVertex.h>
#include <sol/direct3d11/D3D11PosTexCoordVertex.h>

namespace SOL {

class Direct3DX11Shape : public Direct3DX11Object{
private:  
  Direct3D11Device*             d3d11Device;         //Shallow copy
  Direct3D11DeviceContext*      d3d11DeviceContext;  //Shallow copy
    
  Direct3D11Buffer*             vertexBuffer;
  Direct3D11Buffer*             indexBuffer;

  Direct3D11InputLayout*        inputLayout;
  
  Direct3D11ShaderResourceView* shaderResourceView;
  
  Direct3D11SamplerState*       samplerState;

  UINT                          vertexStride;
  int                           vertexCount;
  DXGI_FORMAT                   dxgiFormat;
  int                           indexCount;
  
public:
  Direct3DX11Shape(Direct3D11Device* device, Direct3D11DeviceContext* context)
  :Direct3DX11Object(),
  d3d11Device(device),
  d3d11DeviceContext(context),
  vertexBuffer(NULL),
  indexBuffer(NULL),
  inputLayout(NULL),
  shaderResourceView(NULL),
  samplerState(NULL),
  vertexCount(0),
  indexCount(0)
  {
    if (device == NULL || context == NULL) {
      throw IException("Invalid argument."); 
    }
  }
  
  
  ~Direct3DX11Shape()
  {
    delete samplerState;
    delete shaderResourceView;
    delete inputLayout;
    delete vertexBuffer;
    delete indexBuffer;
  }
  
  //Default getInputElmentDesc,
  //If needed, please define your one getInputElementDesc in a subclass derived from this class,
  virtual const D3D11_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D11InputElements::getPosNormalDesc(count); 
  }
  
  virtual void createVertexBuffer(D3D11PosNormalVertex* vertices,  size_t bytes, size_t vertexCount)
  {
    createVertexBuffer((const void*)vertices, bytes, sizeof(D3D11PosNormalVertex), vertexCount);
  }
  
  virtual void createVertexBuffer(D3D11PosTexCoordVertex* vertices,  size_t bytes, size_t vertexCount)
  {
    createVertexBuffer((const void*)vertices, bytes, sizeof(D3D11PosTexCoordVertex), vertexCount);
  }
  
  virtual void createVertexBuffer(D3D11PosColorVertex* vertices,  size_t bytes, size_t vertexCount)
  {
    createVertexBuffer((const void*)vertices, bytes, sizeof(D3D11PosColorVertex), vertexCount);
  }

  void createVertexBuffer(const void* vertices, size_t bytes, UINT stride, size_t vertCount)
  {
    try {
      D3D11_BUFFER_DESC bufferDesc;
      memset(&bufferDesc, 0, sizeof(bufferDesc));
      bufferDesc.Usage = D3D11_USAGE_DEFAULT;
      bufferDesc.ByteWidth = bytes;     //Set the byte size for veritces.
      bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      //bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED ; //2016/02/20
    
      D3D11_SUBRESOURCE_DATA subResource;
      memset(&subResource, 0, sizeof(subResource));
      subResource.pSysMem = vertices;
      
      //1 Create a vertex buffer for the vertex from the above parameters.
      vertexBuffer = new Direct3D11Buffer(*d3d11Device, &bufferDesc, &subResource);
      
      vertexCount = vertCount;
      vertexStride  = stride;
      
      setVertexBuffers();

    } catch (Exception& ex) {
      ex.display();
    }
  }

  virtual void setVertexBuffers()
  {
    if (vertexBuffer) {
      try {
        ID3D11Buffer* buffers[1];
        buffers[0] = *vertexBuffer;
      
        UINT offset = 0;
        d3d11DeviceContext -> setIAVertexBuffers( 0, 1, buffers, &vertexStride, &offset );
        
      } catch (Exception& ex) {
        ex.display();
      }
    }
  }
  
  virtual void setVertexBuffers(Direct3D11DeviceContext* d3d11DeviceContext)
  {
    if (vertexBuffer) {
      try {
        ID3D11Buffer* buffers[1];
        buffers[0] = *vertexBuffer;
      
        UINT offset = 0;
        d3d11DeviceContext -> setIAVertexBuffers( 0, 1, buffers, &vertexStride, &offset );
        
      } catch (Exception& ex) {
        ex.display();
      }
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
      D3D11_BUFFER_DESC indexBufferDesc;
      memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));
      indexBufferDesc.Usage     = D3D11_USAGE_DEFAULT;
      indexBufferDesc.ByteWidth = bytes; 
      indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
      //indexBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED ; //2016/02/20
      
      indexCount = inCount;
      dxgiFormat     = format;

      D3D11_SUBRESOURCE_DATA indexData;
      memset(&indexData, 0, sizeof(indexData));
      indexData.pSysMem = indices;

      // Create an indexBuffer from above parameters.
      indexBuffer= new Direct3D11Buffer(*d3d11Device, &indexBufferDesc, &indexData);

      setIndexBuffer();

    } catch (Exception& ex) {
      ex.display();
    }
  }
  
  virtual void setIndexBuffer()
  {
    if (indexBuffer) {

      try {
        d3d11DeviceContext -> setIAIndexBuffer(*indexBuffer, dxgiFormat, 0 );

        //Set a primitiveTopology
        d3d11DeviceContext -> setIAPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
      
      } catch (Exception& ex) {
        ex.display();
      }
    }
  }

  virtual void setIndexBuffer(Direct3D11DeviceContext* d3d11DeviceContext)
  {
    if (indexBuffer) {

      try {
        d3d11DeviceContext -> setIAIndexBuffer(*indexBuffer, dxgiFormat, 0 );

        //Set a primitiveTopology
        d3d11DeviceContext -> setIAPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
      
      } catch (Exception& ex) {
        ex.display();
      }
    }
  }


  virtual void createInputLayout(Direct3D11Blob* vertexShaderBlob)
  {
      size_t count = 0;
      const D3D11_INPUT_ELEMENT_DESC* layout = getInputElementDesc(count); 
      if (vertexShaderBlob == NULL) {
        throw IException("Invalid parameter.");
      }
    
      try {
        Direct3D11Device* d3d11Device = getD3D11Device();
        Direct3D11DeviceContext* d3d11DeviceContext = getD3D11DeviceContext();
        
        inputLayout = new Direct3D11InputLayout(
              *d3d11Device, 
              layout, 
              count, 
              vertexShaderBlob->getBufferPointer(),
              vertexShaderBlob->getBufferSize());

        d3d11DeviceContext -> setIAInputLayout(*inputLayout);

      } catch (Exception& ex) {
        ex.display();
      }
  }
  
  
  virtual void setInputLayout()
  {    
    if (inputLayout) {
      try {
        Direct3D11DeviceContext* d3d11DeviceContext = getD3D11DeviceContext();
        
        d3d11DeviceContext -> setIAInputLayout(*inputLayout);

      } catch (Exception& ex) {
        ex.display();
      }
    }
  }

  virtual void setInputLayout(Direct3D11DeviceContext* d3d11DeviceContext)
  {    
    if (inputLayout) {
      try {
        //Direct3D11DeviceContext* d3d11DeviceContext = getD3D11DeviceContext();
        
        d3d11DeviceContext -> setIAInputLayout(*inputLayout);

      } catch (Exception& ex) {
        ex.display();
      }
    }
  }

  virtual  void createShaderResourceView(const TCHAR* fullpath)
  {
    try {
      Direct3D11Device* d3d11Device = getD3D11Device();
      shaderResourceView = new Direct3D11ShaderResourceView(
            *d3d11Device,
            fullpath,
            NULL,   //D3D10_SHADER_RESOURCE_VIEW_DESC *desc
            NULL);  //D3DX10_IMAGE_LOAD_INFO* loadInfo

    } catch(Exception& ex) {
      ex.display(); 
    }
  }

  virtual void setShaderResources()
  {
    if (shaderResourceView) {
      try {
        Direct3D11DeviceContext* d3d11DeviceContext = getD3D11DeviceContext();
        ID3D11ShaderResourceView* resourceView = *shaderResourceView;
        d3d11DeviceContext -> setPSShaderResources( 0, 1, &resourceView );
      } catch (Exception& ex) {
        ex.display();
      }
    }
  }

  virtual void setShaderResources(Direct3D11DeviceContext* d3d11DeviceContext)
  {
    if (shaderResourceView) {
      try {
        ID3D11ShaderResourceView* resourceView = *shaderResourceView;
        d3d11DeviceContext -> setPSShaderResources( 0, 1, &resourceView );
      } catch (Exception& ex) {
        ex.display();
      }
    }
  }

  virtual void createSamplerState()
  {
    try {
      Direct3D11Device* d3d11Device = getD3D11Device();

      D3D11_SAMPLER_DESC sampDesc;
      ZeroMemory( &sampDesc, sizeof(sampDesc) );
      sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
      sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
      sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
      sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
      sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
      sampDesc.MinLOD = 0;
      sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
      samplerState = new Direct3D11SamplerState(*d3d11Device, &sampDesc);
    } catch (Exception& ex) {
      ex.display();
    }
  }

  virtual void setSamplers()
  {
    if (samplerState) {
      try {
        Direct3D11DeviceContext* d3d11DeviceContext = getD3D11DeviceContext();
        ID3D11SamplerState*      state = *samplerState;
        d3d11DeviceContext -> setPSSamplers( 0, 1, &state);
      } catch (Exception& ex) {
        ex.display();
      }
    }
  }
  
  virtual void setSamplers(Direct3D11DeviceContext* d3d11DeviceContext)
  {
    if (samplerState) {
      try {
        ID3D11SamplerState*      state = *samplerState;
        d3d11DeviceContext -> setPSSamplers( 0, 1, &state);
      } catch (Exception& ex) {
        ex.display();
      }
    }
  }
  
  virtual Direct3D11InputLayout* getInputLayout()
  {
     return inputLayout;
  }
  

  Direct3D11Device* getD3D11Device()
  {
    return d3d11Device;
  }
        
  Direct3D11DeviceContext* getD3D11DeviceContext()
  {
    return d3d11DeviceContext;
  }

  Direct3D11Buffer*  getVertexBuffer()
  {
    return vertexBuffer;
  }
  
  Direct3D11Buffer* getIndexBuffer()
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

  virtual void setBuffers()
  {
    setVertexBuffers();
    setIndexBuffer();
  }

  virtual void setBuffers(Direct3D11DeviceContext* d3d11DeviceContext)
  {
    setVertexBuffers(d3d11DeviceContext);
    setIndexBuffer(d3d11DeviceContext);
  }

  virtual void drawIndexed()
  {
    d3d11DeviceContext -> drawIndexed( getIndexCount(), 0, 0 );
  }
  
  virtual void drawIndexed(Direct3D11DeviceContext* d3d11DeviceContext)
  {
    d3d11DeviceContext -> drawIndexed( getIndexCount(), 0, 0 );
  }

};

}

