/******************************************************************************
 *
 * Copyright (c) 2014 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Vector3f.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Vector.h>
#include <sol/Vertex.h>

namespace SOL {

#define DIM_THREE (3)
  
class Vector3f : public Vector<float, DIM_THREE> {

public:
  Vector3f()
  :Vector<float, DIM_THREE>()
  {
  }
  
  Vector3f(float x, float y, float z)
  :Vector<float, DIM_THREE>()
  {
    float f[DIM_THREE];
    f[0] = x;
    f[1] = y;
    f[2] = z;
    set(f, 3);
  }

  Vector3f(const Vertex<3>& vertex)
  :Vector<float, DIM_THREE>()
  {
    float f[DIM_THREE];
    for (int i = 0; i<DIM_THREE; i++) {
      f[i] = vertex.value[i];
    }
    set(f, 3);
  }

  static Vector3f crossProduct(const Vector<float, DIM_THREE>& v1, const Vector<float, DIM_THREE>& v2)
  {
    return Vector3f(
      v1[1] * v2[2] - v1[2] * v2[1], 
      v1[2] * v2[0] - v1[0] * v2[2], 
      v1[0] * v2[1] - v1[1] * v2[0]);
  }

  static Vector3f crossProduct(const Vector3f& v1, const Vector3f& v2)
  {
    return Vector3f(
      v1[1] * v2[2] - v1[2] * v2[1], 
      v1[2] * v2[0] - v1[0] * v2[2], 
      v1[0] * v2[1] - v1[1] * v2[0]);
  }
  
  Vector3f crossProduct(const Vector<float, DIM_THREE> &vec) const
  {
    return crossProduct(*this, vec);
  }

};

}


