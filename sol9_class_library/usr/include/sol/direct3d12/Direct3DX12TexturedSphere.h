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
 *  Direct3DX12TexturedSphere.h
 *
 *****************************************************************************/

//2016/11/28
//This is based on MakeSphere function in the following code.
// C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.cpp


#pragma once
#include <math.h>
#include <sol/direct3d12/Direct3DX12Sphere.h>
#include <sol/direct3d12/D3D12PosTexCoord3Vertex.h>

namespace SOL {

class Direct3DX12TexturedSphere : public Direct3DX12Sphere {
public:
  Direct3DX12TexturedSphere(
        __in ID3D12Device*        device, 
        __in float fRadius  = 1.0f, 
        __in UINT uSlices   = 8, 
        __in UINT uStacks   = 8)
  :Direct3DX12Sphere(device, 
          fRadius, 
          uSlices, 
          uStacks)
  {
  }


  ~Direct3DX12TexturedSphere()
  {
  }

  virtual const D3D12_INPUT_ELEMENT_DESC* getInputElementDesc(size_t& count)
  {
    return D3D12InputElements::getPosTexCoordDesc(count); 
  }
};

}

