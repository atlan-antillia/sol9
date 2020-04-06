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
 *  Direct3DX12TexturedFace.h
 *
 *****************************************************************************/

//2016/12/20

#pragma once
#include <math.h>
#include <sol/direct3d12/Direct3DX12Shape.h>


namespace SOL {

class Direct3DX12TexturedFace : public Direct3DX12Shape {
public:
  Direct3DX12TexturedFace(
        __in ID3D12Device*           device,
             D3D12PosTexCoordVertex* vertices, 
             size_t                  sizeOfVertices,
             size_t                  sizeOfVertex, //
             size_t                  countOfVertices,
             uint16_t*               indices,
             size_t                  sizeOfIndice,
             size_t                  countOfIndices)
  :Direct3DX12Shape(device)
  {
    if (device == NULL) {
      throw IException("Invalid devie.");
    }
    
    createTexturedFace(vertices, 
                       sizeOfVertices,
                       countOfVertices,
                       indices,
                       sizeOfIndice,
                       countOfIndices);    
  }

  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosTexCoordDesc(count); 
  }

  void createTexturedFace(D3D12PosTexCoordVertex* vertices, 
                          size_t                  sizeOfVertices,
                          size_t                  countOfVertices,
                          uint16_t*               indices,
                          size_t                  sizeOfIndices,
                          size_t                  countOfIndices)
  { 
    try {
      createVertexBuffer(vertices, sizeOfVertices, sizeof(D3D12PosTexCoordVertex), countOfVertices);
      createIndexBuffer(indices, sizeOfIndices, countOfIndices );
    } catch (Exception& ex) {
        ex.display();
    }
  }

  ~Direct3DX12TexturedFace()
  {
  }
};

}

