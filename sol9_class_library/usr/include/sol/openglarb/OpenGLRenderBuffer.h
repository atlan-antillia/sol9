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

#include <sol/openglarb/OpenGLRenderBuffers.h>

namespace SOL {

class OpenGLRenderBuffer :public OpenGLRenderBuffers {

private:
  GLenum target;
 
public:
  OpenGLRenderBuffer(GLenum target=GL_RENDERBUFFER)
  :OpenGLRenderBuffers(1),
  target(target)
  {
  }
  

  ~OpenGLRenderBuffer()
  {
  }
  
  operator GLuint()
  {
    return getNth(0);
  }
  
  void bind()
  {
     OpenGLRenderBuffers::bindNth(this->target, 0);
  }
  
  void unbind()
  {
     OpenGLRenderBuffers::bind(this->target, 0);
  }
  
  void getParameteriv(GLenum pname, GLint* params)
  {
    OpenGLRenderBuffers::getParameteriv(this->target, pname, params);
  }

  GLboolean isRenderbuffer()
  {
    GLuint buffer = getNth(0);
    return OpenGLRenderBuffers::isRenderbuffer(buffer);
  }

  void storage(GLenum internalformat, GLsizei width, GLsizei height)
  {
    OpenGLRenderBuffers::storage(this->target, internalformat, width, height);
  }
  
};

}
#endif
  
  