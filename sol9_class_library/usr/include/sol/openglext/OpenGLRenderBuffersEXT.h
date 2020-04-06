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
 *  OpenGLRenderBuffersEXT.h
 *
 *****************************************************************************/

#pragma once

#ifdef GL_EXT_framebuffer_object

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLRenderBuffersEXT :public OpenGLObject {

private:
  GLsizei size;
  GLuint*  buffers;

protected:
  void generate(GLsizei size, GLuint* buffers)
  {
    static PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT = NULL;
    if (glGenRenderbuffersEXT == NULL) {
      glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)load("glGenRenderbuffersEXT");
    }    
    glGenRenderbuffersEXT(size, buffers);
  }
  
  //destroy renderbuffer
  void destroy()
  {
    static PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT = NULL;
    if (glDeleteRenderbuffersEXT == NULL) {
      glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)load("glDeleteRenderbuffersEXT");
    }
    glDeleteRenderbuffersEXT(size, buffers);
  }

  void bind(GLenum target, GLuint buffer) 
  {
    static PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT = NULL;
    if (glBindRenderbufferEXT == NULL) {
      glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)load("glBindRenderbufferEXT");
    }
    glBindRenderbufferEXT(target, buffer);
  }
 
public:
  OpenGLRenderBuffersEXT(GLsizei n)
  :OpenGLObject(),
  size(n),
  buffers(NULL)
  {
    if (size < 1) {
      throw IException("Invalid parameters. size=%d", size);
    }
    buffers = new GLuint[size];
    
    generate(size, buffers);
  }
  

  ~OpenGLRenderBuffersEXT()
  {
    destroy();
    delete [] buffers;
    buffers = NULL;
  }
  
 
  GLuint getNth(int n)
  {
    if (n >= 0 && n < size) {
      return buffers[n]; 
    } else {
        throw IException("Invalid nth parameter %d", n);
    }    
  }
  
  void bindNth(GLenum target, int n)
  {
    if (n >= 0 && n < size) {
      bind(target, buffers[n]); 
    } else {
      throw IException("Invalid nth parameter %d", n);
    }
  }
  
  void getParameteriv(GLenum target, GLenum pname, GLint* params)
  {
    static PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT = NULL;
    if (glGetRenderbufferParameterivEXT == NULL) {
      glGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)load("glGetRenderbufferParameterivEXT");
    }
    glGetRenderbufferParameterivEXT(target, pname, params);
  }

  GLboolean isRenderbuffer(GLuint buffer)
  {
    static PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT = NULL;
    if (glIsRenderbufferEXT == NULL) {
      glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC)load("glIsRenderbufferEXT");
    }
    return glIsRenderbufferEXT(buffer);
  }

  void storage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
  {
    static PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT = NULL;
    if (glRenderbufferStorageEXT == NULL) {
      glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)load("glRenderbufferStorageEXT");
    }
    glRenderbufferStorageEXT(target, internalformat, width, height);
  }
  
};

}
#endif
  
  