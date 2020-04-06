/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED. 
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
 *  OpenGLMeshedXYPlane.h
 *
 *****************************************************************************/

//2017/02/15 

#pragma once
  
#include <sol/opengl/OpenGLMeshedPlane.h>

namespace SOL {
  
// PRIMITIVE may take GL_TRIANGLE_STRIP, GL_QUAD_STRIP
 
template <GLenum PRIMITIVE, int WIDTH, size_t MESH_COUNT> 
  
class OpenGLMeshedYZPlane: public OpenGLMeshedPlane<PRIMITIVE, WIDTH, MESH_COUNT> {

public:
  OpenGLMeshedYZPlane(float x)
  {
    float fsize = (float)WIDTH;

    for (int i = 0; i<MESH_COUNT-1; i++) {
      
      for (int j = 0; j<MESH_COUNT; j++) {
        int k = j*MESH_COUNT;
        float fy = (float)i;
        float fz = (float)j;
        OpenGLMeshedPlane<PRIMITIVE, WIDTH, MESH_COUNT>::put(i    + k,   x, fy/fsize,  fz/fsize);
        OpenGLMeshedPlane<PRIMITIVE, WIDTH, MESH_COUNT>::put(i +1 + k,   x, fy/fsize,  fz/fsize);
      }
    }
  }
};
}

