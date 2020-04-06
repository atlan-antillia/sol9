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
 *  OpenGLMeshedCube.h
 *
 *****************************************************************************/

//2017/02/15 

#pragma once
  
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/Vertex3.h>
#include <sol/opengl/OpenGLMeshedXYPlane.h>
#include <sol/opengl/OpenGLMeshedXZPlane.h>
#include <sol/opengl/OpenGLMeshedYZPlane.h>

namespace SOL {
  
// PRIMITIVE may take GL_TRIANGLE_STRIP, GL_QUAD_STRIP
 
template <GLenum PRIMITIVE, int WIDTH, size_t MESH_COUNT> 
class OpenGLMeshedCube {
protected:
  static const int  FACES=6;
  SmartPtr<OpenGLMeshedPlane<PRIMITIVE, WIDTH, MESH_COUNT> > faces[FACES]; 
  
public:
  OpenGLMeshedCube( )
  {
    int i = 0;
    faces[i++] = new OpenGLMeshedXZPlane<PRIMITIVE, WIDTH, MESH_COUNT>(0.0f);
    faces[i++] = new OpenGLMeshedXZPlane<PRIMITIVE, WIDTH, MESH_COUNT>((float)WIDTH);
    
    faces[i++] = new OpenGLMeshedXYPlane<PRIMITIVE, WIDTH, MESH_COUNT>(0.0f);
    faces[i++] = new OpenGLMeshedXYPlane<PRIMITIVE, WIDTH, MESH_COUNT>((float)WIDTH);

    faces[i++] = new OpenGLMeshedYZPlane<PRIMITIVE, WIDTH, MESH_COUNT>(0.0f);
    faces[i++] = new OpenGLMeshedYZPlane<PRIMITIVE, WIDTH, MESH_COUNT>((float)WIDTH);

  }
  
  virtual void draw(OpenGLGC* gc)
  {
    for (int i = 0; i<FACES; i++) {
      faces[i]->draw(gc);
    }
  }

 
};
}

