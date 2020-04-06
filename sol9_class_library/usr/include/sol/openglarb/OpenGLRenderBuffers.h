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
 *  OpenGLRenderBuffer.h
 *
 *****************************************************************************/

#pragma once

#ifdef GL_ARB_framebuffer_object

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLRenderBuffers :public OpenGLObject {

private:
  GLsizei size;
  GLuint*  buffers;

protected:
  void generate(GLsizei size, GLuint* buffers)
  {
    static PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = NULL;
    if (glGenRenderbuffers == NULL) {
      glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)load("glGenRenderbuffers");
    }    
    glGenRenderbuffers(size, buffers);
  }
  
  //destroy renderbuffer
  void destroy()
  {
    static PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = NULL;
    if (glDeleteRenderbuffers == NULL) {
      glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)load("glDeleteRenderbuffers");
    }
    glDeleteRenderbuffers(size, buffers);
  }

  void bind(GLenum target, GLuint buffer) 
  {
    static PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = NULL;
    if (glBindRenderbuffer == NULL) {
      glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)load("glBindRenderbuffer");
    }
    glBindRenderbuffer(target, buffer);
  }
 
public:
  OpenGLRenderBuffers(GLsizei n)
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
  

  ~OpenGLRenderBuffers()
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
    static PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = NULL;
    if (glGetRenderbufferParameteriv == NULL) {
      glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)load("glGetRenderbufferParameteriv");
    }
    glGetRenderbufferParameteriv(target, pname, params);
  }

  GLboolean isRenderbuffer(GLuint buffer)
  {
    static PFNGLISRENDERBUFFERPROC glIsRenderbuffer = NULL;
    if (glIsRenderbuffer == NULL) {
      glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)load("glIsRenderbuffer");
    }
    return glIsRenderbuffer(buffer);
  }

  void storage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
  {
    static PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = NULL;
    if (glRenderbufferStorage == NULL) {
      glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)load("glRenderbufferStorage");
    }
    glRenderbufferStorage(target, internalformat, width, height);
  }
  
};

}
#endif
  
  