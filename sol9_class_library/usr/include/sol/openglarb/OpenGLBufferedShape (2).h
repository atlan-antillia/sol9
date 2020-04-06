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
 *  OpenGLBufferedShape.h 
 *
 *****************************************************************************/

#pragma once

#ifdef GL_ARB_vertex_buffer_object

#include <sol/opengl/OpenGLGC.h>
#include <sol/opengl/OpenGLLight.h>
#include <sol/opengl/OpenGLMaterial.h>
#include <sol/opengl/ColorNormalVertex.h>

#include <sol/opengl/OpenGLVertex3.h>
#include <sol/opengl/OpenGLClientState.h>
#include <sol/openglarb/OpenGLVertexBufferARB.h>
#include <sol/openglarb/OpenGLIndexBufferARB.h>

#include <sol/opengl2/OpenGLVertexAttribute.h>

namespace SOL {

class OpenGLBufferedShape :public OpenGLObject {
private:
  
  SmartPtr<OpenGLVertexBufferARB> vertexBuffer;
  SmartPtr<OpenGLIndexBufferARB>  indexBuffer;

  int numVertices;
  int numIndices;
 
public:
  OpenGLBufferedShape(void* vertices, size_t verticesDataSize, size_t verticesCount,
                         void* indices,  size_t indicesDataSize,  size_t indicesCount,
                         GLenum drawFlag = GL_STATIC_DRAW_ARB)
    
  :OpenGLObject(),
  numVertices(0),
  numIndices (0)
  {
    if (vertices != NULL && verticesDataSize > 0 && verticesCount > 0 &&
        indices  != NULL && indicesDataSize  > 0 && indicesCount  > 0) {
          
      create(vertices, verticesDataSize, verticesCount,
           indices,  indicesDataSize,  indicesCount);
    } else {
      throw IException("Invalid parameter.");    
    }
  }
  
  ~OpenGLBufferedShape()
  {
  }
  
  void create(void* vertices, size_t verticesDataSize, size_t verticesCount,
                         void* indices,  size_t indicesDataSize,  size_t indicesCount)
  {
     vertexBuffer = new OpenGLVertexBufferARB();

     numVertices = verticesCount;

     vertexBuffer -> bind();
     vertexBuffer -> data(verticesDataSize, vertices, drawFlag);
     vertexBuffer -> unbind();

     indexBuffer  = new OpenGLIndexBufferARB();

     numIndices  = indicesCount;

     indexBuffer -> bind();
     indexBuffer -> data(indicesDataSize, indices, drawFlag);
     indexBuffer -> unbind();
  }
  
  virtual void draw(OpenGLGC* gc) 
  {
  }
};
}

#endif

