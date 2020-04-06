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
 *  OpenGLIndexedVertices.h 
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLGC.h>

namespace SOL {
    
class OpenGLIndexedVertices : public OpenGLObject {
public:
  OpenGLIndexedVertices()
  :OpenGLObject()
  {    
  }
  
  ~OpenGLIndexedVertices()
  {
  }
  
  virtual GLenum getInterleavedArraysFormat() = 0;

  virtual GLenum getPrimitiveType()   = 0;

  virtual GLfloat* getVertices()      = 0;

  virtual int getVerticesDataSize()   = 0;

  virtual int getNumberOfVertices()   = 0;

  virtual GLuint* getIndices()        = 0;

  virtual int getIndicesDataSize()    = 0;

  virtual int getNumberOfIndices()    = 0;
  
  virtual void draw(OpenGLGC* gc)     = 0;
};
  
}
  