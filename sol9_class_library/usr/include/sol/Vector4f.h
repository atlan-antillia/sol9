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
 *  Vector4f.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Vector.h>
#include <sol/Vertex.h>

namespace SOL {

#define DIM_FOUR (4)
  
class Vector4f : public Vector<float, DIM_FOUR> {

public:
  Vector4f()
  :Vector<float, DIM_FOUR>()
  {
  }
  
  Vector4f(float x, float y, float z, float w)
  :Vector<float, DIM_FOUR>()
  {
    float f[DIM_FOUR];
    f[0] = x;
    f[1] = y;
    f[2] = z;
    f[3] = w;
    set(f, CountOf(f));
  }
  
  Vector4f(const Vector<float, DIM_FOUR>& vec)
  :Vector<float, DIM_FOUR>(vec)
  {
  }

  Vector4f(const Vertex<4> vertex)
  :Vector<float, DIM_FOUR>()
  {
    float f[DIM_FOUR];
    for (int i = 0; i<DIM_FOUR; i++) {
      f[i] = vertex.value[i];
    }
    set(f, CountOf(f));
  }
};
  

}


