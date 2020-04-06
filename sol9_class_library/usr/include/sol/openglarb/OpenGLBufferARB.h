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

#ifdef GL_ARB_vertex_buffer_object

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLClientState.h>

namespace SOL {

class OpenGLBufferARB :public OpenGLObject {
private:
  GLuint id;
  GLenum target;
  GLsizei size;
  
private:
  void bind(GLenum target, GLuint id)
  {
    static PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;
    if (glBindBufferARB == NULL) {
      glBindBufferARB = (PFNGLBINDBUFFERARBPROC)load("glBindBufferARB");
    }
    glBindBufferARB(target, id);
  }

public:
  OpenGLBufferARB(GLenum target = GL_ARRAY_BUFFER_ARB)
  :OpenGLObject(),
  id(0),
  target(0),
   size(0)
  {
    
    this -> target = target;
    size  = 0;
    create(1, &id);
   
    printf("OpenGLBufferARB id %d\n", id);
    if (id <=0 ) {
      throw IException("Failed to create OpenGLBufferARB"); 
    }
  } 


public:
  ~OpenGLBufferARB()
  {
    destroy();
  }
  
public:
  void create(GLsizei size, GLuint* id)
  {
    printf("create 1\n");
    static  PFNGLGENBUFFERSARBPROC  glGenBuffersARB = NULL;
    if (glGenBuffersARB == NULL) {
      glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)load("glGenBuffersARB");
      printf("create 2\n");
    }
    glGenBuffersARB(size, id);
  }

public:
  void destroy()
  {
    static PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;
    if (glDeleteBuffersARB == NULL) {
      glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)load("glDeleteBuffersARB");
    }
    glDeleteBuffersARB(size, &id);
  }

public:
  void bind() 
  {
    bind(this -> target, this->id);
  } 

public:
  void unbind() 
  {
    bind(this->target, 0);
  } 

  void getBufferParameter(GLenum pname, GLint* params)
  {
    static PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB = NULL;
    if (glGetBufferParameterivARB == NULL ) {
      glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)load("glGetBufferParameterivARB");
    }
    glGetBufferParameterivARB(this -> target, pname, params);
  }
  
  void getBufferPointer(GLenum pname, void** params)
  {
    static  PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB = NULL;
    if (glGetBufferPointervARB == NULL) {
      glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC)load("glGetBufferPointervARB");
    }
    glGetBufferPointervARB(this -> target, pname, params);
  }
    
  void data(GLsizei sizei, const void* data, GLenum usage=GL_DYNAMIC_DRAW_ARB)
  {
    static PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;
    if (glBufferDataARB == NULL) {
      glBufferDataARB = (PFNGLBUFFERDATAARBPROC)load("glBufferDataARB");
    }
    if (sizei > 0 && data != NULL) {
      printf("data set\n");
      this -> size = sizei;
       glBufferDataARB(this -> target, size, data, usage);
    }
  }

  void subData(GLint offset, GLsizei sizei, void* data)
  { 
    static PFNGLGETBUFFERSUBDATAARBPROC glBufferSubDataARB = NULL;
    if (glBufferSubDataARB == NULL) {
      glBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)load("glBufferSubDataARB");
    }
    if (offset > 0 && sizei > 0 && data != NULL) {
       glBufferSubDataARB(this ->target, offset, sizei, data);
    }
  }
  
  void getBufferSubData(GLintptrARB offset, GLsizeiptrARB size, void *data)
  {
    static PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB = NULL;
    if (glGetBufferSubDataARB == NULL) {
      glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)load("glGetBufferSubDataARB");
    }
    glGetBufferSubDataARB(this -> target, offset, size, data);
  }
  
  GLboolean isBuffer()
  {
    static PFNGLISBUFFERARBPROC glIsBufferARB = NULL; 
    if (glIsBufferARB == NULL) {
      glIsBufferARB = (PFNGLISBUFFERARBPROC)load("glIsBufferARB");
    }
    return glIsBufferARB(id);
  }
  
  
  void map(GLenum access)
  {
    static PFNGLMAPBUFFERARBPROC glMapBufferARB = NULL;
    if (glMapBufferARB == NULL) {
      glMapBufferARB = (PFNGLMAPBUFFERARBPROC)load("glMapBufferARB");
    }
    glMapBufferARB(target, access);
  }
  
  GLboolean unmap()
  {
    static PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB = NULL;
    if (glUnmapBufferARB = NULL) {
      glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)load("glUnmapBufferARB");
    }
    return glUnmapBufferARB(target);
  }
  
#ifdef GL_ARB_draw_buffers
  void drawBuffers(GLsizei n, const GLenum* bufs)
  {
    bind();
    OpenGLClientState state(GL_VERTEX_ARRAY);
    state.enable();

    static PFNGLDRAWBUFFERSARBPROC glDrawBuffersARB = NULL;
    if (glDrawBuffersARB == NULL) {
      glDrawBuffersARB = (PFNGLDRAWBUFFERSARBPROC)load("glDrawBuffersARB");
    }
    glDrawBuffersARB(n, bufs); 
    state.disable();
    unbind();
  }
  
#endif
  
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

#endif

