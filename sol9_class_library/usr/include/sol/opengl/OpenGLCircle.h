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
 *  OpenGLCircle.h
 *
 *****************************************************************************/

//2017/02/15

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLGC.h>
#include <sol/opengl/OpenGLArrayBuffer.h>
#include <sol/opengl/Vertex3.h>

namespace SOL {

class OpenGLCircle : public OpenGLObject {
private:
  static const int CIRCLE_ANGLE = 360;
  
  SmartPtr<OpenGLArrayBuffer> vertexBuffer;
  
  Vertex3  vertices[CIRCLE_ANGLE];
  GLuint   indices[CIRCLE_ANGLE];
  
public:
  OpenGLCircle(
        __in float          px = 0.0f, 
        __in float          py = 0.0f, 
        __in float          pz = 0.5f,
        __in float          radius  = 1.0f)
  :OpenGLObject()
  {
    if (radius < 0.0f) {
      throw IException("Invalid parameter."); 
    }
    // Create a vertexBuffer and an indexBuffer
    createCircle(px, py, pz, radius);    
  }

    
  void createCircle(float px, float py, float pz, float radius)
  {
    int vertexCount = CIRCLE_ANGLE;
 
    for (int i = 0; i<vertexCount - 1; i += 2) {
        vertices[i    ].x = px + radius * COS(i    );
        vertices[i    ].y = py + radius * SIN(i    );
        vertices[i    ].z = pz;
        vertices[i + 1].x = px + radius * COS(i + 1);
        vertices[i + 1].y = py + radius * SIN(i + 1);
        vertices[i + 1].z = pz;
    }

    for (int i = 0; i<CIRCLE_ANGLE ; i++) {
      indices[i] = i;
    }
    vertexBuffer = new OpenGLArrayBuffer();
    vertexBuffer->bind();
    vertexBuffer->data(sizeof(vertices), CountOf(vertices), 3, vertices);
    vertexBuffer->unbind();
  }

  Vertex3 getOrbitPosition(int angle)
  {      
    if (angle > CIRCLE_ANGLE) {
      angle -= CIRCLE_ANGLE;
    }
    if (angle < 0) {
        angle = 0;
    }
    return vertices[angle];          
  }   
  
  virtual void draw(OpenGLGC* gc)
  {
    vertexBuffer->drawArray(gc, GL_LINE_LOOP);
  }
  
};

}
