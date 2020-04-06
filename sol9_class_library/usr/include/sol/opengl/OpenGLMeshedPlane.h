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
 *  OpenGLMeshedPlane.h
 *
 *****************************************************************************/

//2017/03/01 

#pragma once
  
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/Vertex3.h>

namespace SOL {
  
// PRIMITIVE may take GL_TRIANGLE_STRIP, GL_QUAD_STRIP
 
template <GLenum PRIMITIVE, int WIDTH, size_t MESH_COUNT> 
class OpenGLMeshedPlane {
protected:
 SmartPtr<Vertex3> mesh; 
 size_t  ELEMENT_COUNT;

public:
  OpenGLMeshedPlane( )
  {
    mesh = new Vertex3[MESH_COUNT*MESH_COUNT];
    ELEMENT_COUNT = MESH_COUNT*MESH_COUNT;
  }

  void put(size_t i, float x, float y, float z)
  {
    if (i >= 0 && i < ELEMENT_COUNT) {
      mesh[i].x = x; 
      mesh[i].y = y;
      mesh[i].z = z;
    } else {
      throw IException("Invalid index %d", i);
    }
  }

  void draw(OpenGLGC* gc)
  {
    float fsize = (float)WIDTH;
    for (int i = 0; i <MESH_COUNT-1; i++) {
      gc-> begin(PRIMITIVE);

      for (int j = 0; j<MESH_COUNT; j++) {
        int k = j*MESH_COUNT;
        glVertex3f(mesh[i   + k].x,  mesh[i   + k ].y, mesh[i   + k ].z);
        glVertex3f(mesh[i+1 + k].x,  mesh[i+1 + k ].y, mesh[i+1 + k ].z); 
      }
      gc->end();
    }
  }
};
}

