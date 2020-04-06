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
 *  Direct3DX12MultiTexturedBox.h
 *
 *****************************************************************************/

//2016/12/25 Updated.

#pragma once
#include <sol/direct3d12/D3D12Box.h>

#include <sol/direct3d12/Direct3DX12MultiTexturedShape.h>
#include <sol/direct3d12/Direct3DX12TexturedFace.h>


namespace SOL {

#define NUMBER_OF_BOX_FACES 6

class Direct3DX12MultiTexturedBox : public Direct3DX12MultiTexturedShape<NUMBER_OF_BOX_FACES> {

public:
  Direct3DX12MultiTexturedBox(ID3D12Device* device,
                            int& width,
                            int& height,
                            
                            const wchar_t* filenames[],
                            size_t         countOfFilenames,
                            
                            D3D12Box box)
  :Direct3DX12MultiTexturedShape<NUMBER_OF_BOX_FACES>(device,
              width,
              height,
              filenames,
              countOfFilenames)
  {
    createTexturedShape(device, box);
  }
 
        
  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosTexCoordDesc(count); 
  }

  virtual void createTexturedShape(ID3D12Device* device, D3D12Box box)
  {
    createTexturedShape(device, box.x, box.y, box.z, box.width, box.height, box.depth);
  }

  void createTexturedShape(ID3D12Device* device, float x, float y, float z, 
      float width, float height, float depth)
  {
    try {
        
        D3D12PosTexCoordVertex vertices[NUMBER_OF_BOX_FACES][4] = {
        { //face1
          { XMFLOAT3( -1.0f * width + x,  1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 1.0f, 0.0f ) },
          { XMFLOAT3(  1.0f * width + x,  1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 0.0f, 0.0f ) },
          { XMFLOAT3(  1.0f * width + x,  1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 0.0f, 1.0f ) },
          { XMFLOAT3( -1.0f * width + x,  1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 1.0f, 1.0f ) },
        },
        { //face2
          { XMFLOAT3( -1.0f * width + x, -1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 0.0f, 0.0f ) },
          { XMFLOAT3(  1.0f * width + x, -1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 1.0f, 0.0f ) },
          { XMFLOAT3(  1.0f * width + x, -1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 1.0f, 1.0f ) },
          { XMFLOAT3( -1.0f * width + x, -1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 0.0f, 1.0f ) },
        },
        { //face3
          { XMFLOAT3( -1.0f * width + x, -1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 0.0f, 1.0f ) },
          { XMFLOAT3( -1.0f * width + x, -1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 1.0f, 1.0f ) },
          { XMFLOAT3( -1.0f * width + x,  1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 1.0f, 0.0f ) },
          { XMFLOAT3( -1.0f * width + x,  1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 0.0f, 0.0f ) },
        },
        { //face4
          { XMFLOAT3(  1.0f * width + x, -1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 1.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * width + x, -1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 0.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * width + x,  1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 0.0f, 0.0f ) },
          { XMFLOAT3(  1.0f * width + x,  1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 1.0f, 0.0f ) },
        },
        { //face5
          { XMFLOAT3( -1.0f * width + x, -1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 0.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * width + x, -1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 1.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * width + x,  1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 1.0f, 0.0f ) },
          { XMFLOAT3( -1.0f * width + x,  1.0f * height + y, -1.0f * depth + z ), XMFLOAT2( 0.0f, 0.0f ) },
        },
        { //face6
          { XMFLOAT3( -1.0f * width + x, -1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 1.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * width + x, -1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 0.0f, 1.0f ) },
          { XMFLOAT3(  1.0f * width + x,  1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 0.0f, 0.0f ) },
          { XMFLOAT3( -1.0f * width + x,  1.0f * height + y,  1.0f * depth + z ), XMFLOAT2( 1.0f, 0.0f ) },
          }
        };
        
       
        uint16_t indices[NUMBER_OF_BOX_FACES][6] = {
          //face1
          {3, 1, 0,    2, 1, 3},
          //face2
          {2, 0, 1,    3, 0, 2}, 
          //face3
          {3, 1, 0,    2, 1, 3}, 
          //fac4
          {2, 0, 1,    3, 0, 2}, 
          //face5
          {3, 1, 0,    2, 1, 3}, 
          //face6
          {2, 0, 1,    3, 0, 2}, 
        };  
        
        for (size_t i = 0; i<NUMBER_OF_BOX_FACES; i++) {
          faces[i] = new Direct3DX12TexturedFace(device, 
                                      vertices[i], 
                                      sizeof(vertices[i]), 
                                      sizeof(D3D12PosTexCoordVertex),
                                      _countof(vertices[i]),
                                      indices[i], 
                                      sizeof(indices[i]), 
                                      _countof(indices[i]));
        }
        
    } catch (Exception& ex) {
        ex.display();
    }
  }    
};

}
        