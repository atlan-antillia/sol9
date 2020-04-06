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

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLFrameBuffersEXT :public OpenGLObject {

private:
  GLsizei size;
  GLuint* buffers;
  
protected:
  void generate(GLsizei size, GLuint* buffers)
  {
    static PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT = NULL;
    if (glGenFramebuffersEXT == NULL) {
      glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)load("glGenFramebuffersEXT");
    }
    glGenFramebuffersEXT(size, buffers);
  }
  
  void bind(GLenum target, GLuint buffer)
  {
    static PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT = NULL;
    if (glBindFramebufferEXT == NULL) {
      glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)load("glBindFramebufferEXT");
    }
    glBindFramebufferEXT(target, buffer);
  }
  
  void destroy()
  {
    static PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT = NULL;
    if (glDeleteFramebuffersEXT == NULL) {
      glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)load("glDeleteFramebuffersEXT");
    }
    glDeleteFramebuffersEXT(size, buffers);  
  }

public:
  OpenGLFrameBuffersEXT(GLsizei n)
  :OpenGLObject(),
  size(n),
  buffers(NULL)
  {
    if (size <= 0) {
      throw IException("Invalid size parameter. size=%d", size);
    }
    buffers = new GLuint[size];
    generate(size, buffers);
  }
  
  ~OpenGLFrameBuffersEXT()
  {
    destroy();
    delete [] buffers;
    buffers = NULL;
  }
  
  GLenum check(GLenum target)
  {
    static PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT = NULL;
    if (glCheckFramebufferStatusEXT == NULL) {
      glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)load("glCheckFramebufferStatusEXT");
    }
    return glCheckFramebufferStatusEXT(target);
  }

  //Modified method name to be attachRenderBuffer
  void attachRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
  {
    static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT = NULL;
    if (glFramebufferRenderbufferEXT == NULL) {
      glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)load("glFramebufferRenderbufferEXT");
    }
    glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer);
  }
  
  //2016/07/15
  void detachRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget)
  {
    static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT = NULL;
    if (glFramebufferRenderbufferEXT == NULL) {
      glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)load("glFramebufferRenderbufferEXT");
    }
    glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, 0);
  }
  
  void texture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
  {
    static PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT = NULL;
    if (glFramebufferTexture1DEXT == NULL) {
      glFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)load("glFramebufferRenderbufferEXT");
    }
    glFramebufferTexture1DEXT(target, attachment, textarget, texture, level);
  }

  void texture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
  {
    static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT = NULL;
    if (glFramebufferTexture2DEXT = NULL) {
      glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)load("glFramebufferTexture2DEXT"); 
    }
    glFramebufferTexture2DEXT(target, attachment, textarget, texture, level);
  }
    
  void texture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
  {
    static PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT = NULL;
    if (glFramebufferTexture3DEXT = NULL) {
      glFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)load("glFramebufferTexture3DEXT");
    }
    glFramebufferTexture3DEXT(target, attachment, textarget, texture,level, zoffset);
  }
    

  void getAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint* params)
  {
    static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT = NULL;
    if (glGetFramebufferAttachmentParameterivEXT == NULL) {
      glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)load("glGetFramebufferAttachmentParameterivEXT");
    }
    glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params);
  }
    
  GLboolean isFramebuffer(GLuint buffer)
  {
    static PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT = NULL;
    if (glIsFramebufferEXT == NULL) {
      glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC)load("glIsFramebufferEXT");  
    }
    return glIsFramebufferEXT(buffer);
  }
 
  GLuint getNth(int n)
  {
    if (n >= 0 && n > size) {
      return buffers[n];
    } else {
      throw IException("Invalid index %d", n);
    }
  }
    
  void bindNth(GLenum target, int n)
  {
    if (n >= 0 && n > size) {
      bind(target, buffers[n]);
    } else {
      throw IException("Invalid index %d", n);
    }
  }
};

}

#endif
  
  