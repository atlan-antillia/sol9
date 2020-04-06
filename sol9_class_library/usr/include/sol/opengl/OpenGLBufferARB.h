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
 *  OpenGLBufferARB.h 
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLClientState.h>

namespace SOL {

class OpenGLBufferARB :public OpenGLObject {
private:
  GLuint id;
  GLenum target;
  GLsizei size;
public:
  OpenGLBufferARB(GLenum target = GL_ARRAY_BUFFER_ARB)
  :OpenGLObject(),
  id(0),
  target(0),
   size(0)
  {
    glGenBuffersARB(1, &id);
    this -> target = target;
    size  = 0;
  } 


public:
  ~OpenGLBufferARB()
  {
    glDeleteBuffersARB(1, &id);
  }

  void bind() 
  {
      //this -> target = target;
     glBindBufferARB(this -> target, id);
  } 

  void unbind() 
  {
     // this -> target = target;
     glBindBufferARB(this -> target, 0);
  } 

  void data(GLsizei sizei, const void* data, GLenum usage=GL_DYNAMIC_DRAW_ARB)
  {
    if (sizei > 0 && data != NULL) {
      printf("data set\n");
      this -> size = sizei;
       glBufferDataARB(this -> target, size, data, usage);
    }
  }

  void subData(GLint offset, GLsizei sizei, void* data)
  {  
    if (offset > 0 && sizei > 0 && data != NULL) {
       glBufferSubDataARB(this ->target, offset, sizei, data);
    }
  }
  
  
  void drawArray(GLenum style)
  {
    bind();
    OpenGLClientState state(GL_VERTEX_ARRAY);
    state.enable();
    GLuint vertexNum = 3;
    
    glVertexPointer(vertexNum, GL_FLOAT, 0, 0);
  
    int dataNum = this -> size / (3*sizeof(GLfloat));
    printf("dataNum %d\n", dataNum);
    glDrawArrays(style, 0 , dataNum);
    state.disable();
    
    unbind();
   }
};
}

