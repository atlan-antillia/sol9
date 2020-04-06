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
 *  D3D12CircularOrbit.h
 *
 *****************************************************************************/

#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace SOL {

  //Inner class starts,
class D3D12CircularOrbit {
private:
  static const int    CIRCLE_ANGLE = 360;
  float     radius;
  XMFLOAT3  vertices[CIRCLE_ANGLE];
  UINT      vcount;
      
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
    
public:
  D3D12CircularOrbit(float x, float y, float z, float r)
    :radius(r),
    vcount(CountOf(vertices))
  {
    for (UINT i = 0; i<vcount - 1; i += 2) {
      vertices[i    ] = XMFLOAT3(x + radius * COS(i    ), y + radius * SIN(i    ), z);
      vertices[i + 1] = XMFLOAT3(x + radius * COS(i + 1), y + radius * SIN(i + 1), z);
    }      
  }
        
  XMFLOAT3 getOrbitPosition(int pos)
  {      
    if (pos < 0) {
        pos = 0;
    }
    if (pos > CIRCLE_ANGLE) {
      pos -= CIRCLE_ANGLE;
    }
    return vertices[pos];          
  }   
};
  //
}
  