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
 *  OpenGLFrameBuffersEXT.h
 *
 *****************************************************************************/


#pragma once

#ifdef GL_EXT_framebuffer_object

#include <sol/openglext/OpenGLFrameBuffersEXT.h>

namespace SOL {

class OpenGLFrameBufferEXT :public OpenGLFrameBuffersEXT {

private:
  GLenum target;

public:
  OpenGLFrameBufferEXT(GLenum target=GL_FRAMEBUFFER_EXT)
  :OpenGLFrameBuffersEXT(1),
  target(target)
  {
  }
  
  ~OpenGLFrameBufferEXT()
  {
  }
  
  operator GLuint()
  {
    return getNth(0);
  }
  
  GLenum check()
  {
    OpenGLFrameBuffersEXT::check(this->target);
  }
  
  void bind()
  {
    GLuint buffer = getNth(0);
    OpenGLFrameBuffersEXT::bind(this->target, buffer);
  }
  
  void unbind()
  {
    OpenGLFrameBuffersEXT::bind(this->target, 0);
  }
  
  void attachRenderbuffer(GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
  {
    OpenGLFrameBuffersEXT::attachRenderbuffer(this->target, attachment, renderbuffertarget, renderbuffer);
  }
  
  void texture1D(GLenum attachment, GLenum textarget, GLuint texture, GLint level)
  {
    OpenGLFrameBuffersEXT::texture1D(this->target, attachment, textarget, texture, level);
  }

  void texture2D(GLenum attachment, GLenum textarget, GLuint texture, GLint level)
  {
    OpenGLFrameBuffersEXT::texture2D(this->target, attachment, textarget, texture, level);
  }
    
  void texture3D(GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
  {
    OpenGLFrameBuffersEXT::texture3D(this->target, attachment, textarget, texture, level, zoffset);
  }
    
  void getAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint* params)
  {
    OpenGLFrameBuffersEXT::getAttachmentParameterivEXT(this->target, attachment, pname, params);
  }
    
  GLboolean isFramebuffer()
  {
    GLuint buffer = getNth(0);
    return OpenGLFrameBuffersEXT::isFramebuffer(buffer);
  }
};

}

#endif
  
  