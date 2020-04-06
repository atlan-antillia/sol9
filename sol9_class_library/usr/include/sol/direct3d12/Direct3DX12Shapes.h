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

class Direct3DX12Shapes : public Direct3D12Object{
private:  
  ID3D12Device*                d3d12Device;         //Shallow copy
  size_t                       maxCont;
  sizet                        count;
  SmartPtr<Direct3DX12Shape>*  shapes;
  
  
public:
  Direct3DX12Shapes(ID3D12Device* device, size_t c)
  :Direct3D12Object(),
  d3d12Device(device),
  maxCount(c),
  count(0),
  shapes(nullptr)
  {
    if (device == nullptr || c < 1 ) {
      throw IException("Invalid argument."); 
    }
    shapes = new SmartPtr<Direct3DX12Shape>[maxCount]:
  }
  
  
  ~Direct3DX12Shape()
  {
    delete [] shapes;
  }
  
  void add(Direct3DX12Shhapes* shape)
  {
    if (count <maxCount) {
      shapes[count++] = shape; 
    }
  }
  
  void draw(ID3D12GraphicsCommangList* commandList)
  {
    for (int i = 0; i<count; i++) {
      shapes[i] -> draw(commandList); 
    }
  }
};

}

