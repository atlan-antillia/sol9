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
 *  OpenGLVertexArray.h
 *
 *****************************************************************************/

//2016/07/04 VertexArray of size = 1.

#pragma once

#ifdef GL_ARB_vertex_array_object

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLVertexArray : public OpenGLObject {
private:
  GLuint*  ids;
  GLsizei size;
  
protected:
  void destroy(GLsizei s, GLuint* a)
  {
    static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
    if (glDeleteVertexArrays == NULL) {
      glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load("glDeleteVertexArrays");
    }
    glDeleteVertexArrays(s, a);
  }

private:
  void create(GLsizei s, GLuint* ids) 
  {
    static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
    if (glGenVertexArrays == NULL) {
      glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load("glGenVertexArrays");
    }
    glGenVertexArrays(s, ids);
  }
  
protected:
  void bind(GLuint n)
  {
    static PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
    if (glBindVertexArray == NULL) {
      glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
    }
    glBindVertexArray(n);
  }

protected:
  OpenGLVertexArray(GLsizei s)
  :ids(NULL),
  size(s)
  {
    if (s < 1) {
      throw IException("Invalid size parameter.");
    }
    ids = new GLuint[s];
    memset(ids, 0, s);
    //Create uninitialized vertexArrays of size.
    create(size, ids);
  }
  
public:
  OpenGLVertexArray()
  :ids(NULL),
  size(1)
  {
    this->ids = new GLuint[this->size];
    memset(this->ids, 0, this->size);
    //Create an uninitialized vertexArray of size.
    create(this->size, this->ids);
  }
  
  ~OpenGLVertexArray()
  {
    destroy(this -> size, this->ids);
    delete [] this->ids;
    this->ids = NULL;
  }
  
  GLuint getNth(int i)
  {
    if (i >= 0 && i < size) {
      return ids[i];
    } else {
      throw IException("Invalid argument %d", i); 
    }
    
  }
  
  GLsizei getSize()
  {
    return size;
  }
  
  void bind()
  {
    bind(this->ids[0]);
  }

  void unbind()
  {
    bind(0);
  }

  GLboolean isVertexArray(GLuint n)
  {
    static PFNGLISVERTEXARRAYPROC glIsVertexArray = NULL;
    if (glIsVertexArray == NULL) {
      glIsVertexArray = (PFNGLISVERTEXARRAYPROC)load("glIsVertexArray");
    }
    return glIsVertexArray(n);
  }

  GLboolean isVertexArray()
  {
    static PFNGLISVERTEXARRAYPROC glIsVertexArray = NULL;
    if (glIsVertexArray == NULL) {
      glIsVertexArray = (PFNGLISVERTEXARRAYPROC)load("glIsVertexArray");
    }
    return glIsVertexArray(this->ids[0]);
  }

};

}

#endif

