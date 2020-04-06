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
 *  OpenGLTexturedCube.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/opengl/OpenGLTexture2D.h>
#include <sol/opengl/TextureCoord2Vertex3.h>
#include <sol/opengl/TextureCoordTriangularCube.h>

namespace SOL {

class OpenGLTexturedCube : public OpenGLTexture2D {
private:
  SmartPtr<TextureCoordTriangularCube> ttc;
  
public:
  OpenGLTexturedCube(GLfloat size=1.0f)
  :OpenGLTexture2D()
  {
    ttc = new TextureCoordTriangularCube(size);
  }

public:
  OpenGLTexturedCube(const char* filename, GLfloat size=1.0f)
  :OpenGLTexture2D()
  {
    ttc = new TextureCoordTriangularCube(size);
    
    load(filename);
  }

  ~OpenGLTexturedCube()
  {
  }
  
  virtual void load(const char* filename)
  {
    bind();

    pixelStore(GL_UNPACK_ALIGNMENT, 4);
    
    parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    env(GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
    generate(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    generate(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

    parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
    try {
      imageFromFile(filename);
    } catch (Exception& ex) {
      ex.display();
    }
    
    unbind();
  }
  
    
  public:
    virtual void draw(OpenGLGC* gc)
    {      
      TextureCoord2Vertex3* cube = ttc->getData();
      
      int numElements = ttc->getNumberOfElements();
      
      if (gc) {
        bind();
        
        gc -> enable(GL_NORMALIZE);
       
        gc -> begin(GL_TRIANGLES);
        
        for (int i = 0; i<numElements; i++) {
          coordVertex(cube[i]);
        }
        gc -> end();
        unbind();
      }
    }
 
 };
}
 