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
 *  OpenGLFrameBuffers.h
 *
 *****************************************************************************/


#pragma once

#ifdef GL_ARB_framebuffer_object

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLFrameBuffers :public OpenGLObject {

private:
  GLsizei size;
  GLuint* buffers;
  
protected:
  void generate(GLsizei size, GLuint* buffers)
  {
    static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
    if (glGenFramebuffers == NULL) {
      glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)load("glGenFramebuffers");
    }
    glGenFramebuffers(size, buffers);
  }
  
  void bind(GLenum target, GLuint buffer)
  {
    static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
    if (glBindFramebuffer == NULL) {
      glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)load("glBindFramebuffer");
    }
    glBindFramebuffer(target, buffer);
  }
  
  void destroy()
  {
    static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
    if (glDeleteFramebuffers == NULL) {
      glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)load("glDeleteFramebuffers");
    }
    glDeleteFramebuffers(size, buffers);  
  }

public:
  OpenGLFrameBuffers(GLsizei n)
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
  
  ~OpenGLFrameBuffers()
  {
    destroy();
    delete [] buffers;
    buffers = NULL;
  }
  
  void blit(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, 
                GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
  {
    static PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = NULL;
    if (glBlitFramebuffer == NULL) {
      glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)load("glBlitFramebuffer");
    }
    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, 
           dstX1, dstY1, mask, filter);
  }
  
  GLenum check(GLenum target)
  {
    static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
    if (glCheckFramebufferStatus == NULL) {
      glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load("glCheckFramebufferStatus");
    }
    return glCheckFramebufferStatus(target);
  }

  void attachRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
  {
    static PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = NULL;
    if (glFramebufferRenderbuffer == NULL) {
      glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)load("glFramebufferRenderbuffer");
    }
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
  }
  
  void detachRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget)
  {
    attachRenderbuffer(target, attachment, renderbuffertarget, 0);
  }

  void texture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
  {
    static PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = NULL;
    if (glFramebufferTexture1D == NULL) {
      glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)load("glFramebufferTexture1D");
    }
    glFramebufferTexture1D(target, attachment, textarget, texture, level);
  }

  void texture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
  {
    static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
    if (glFramebufferTexture2D == NULL) {
      glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)load("glFramebufferTexture2D"); 
    }
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
  }
    
  void texture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
  {
    static PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = NULL;
    if (glFramebufferTexture3D == NULL) {
      glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)load("glFramebufferTexture3D");
    }
    glFramebufferTexture3D(target, attachment, textarget, texture,level, zoffset);
  }

  void getAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
  {
    static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv = NULL;
    if (glGetFramebufferAttachmentParameteriv == NULL) {
      glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)load("glGetFramebufferAttachmentParameteriv");
    }
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
  }
    
  GLboolean isFramebuffer(GLuint buffer)
  {
    static PFNGLISFRAMEBUFFERPROC glIsFramebuffer = NULL;
    if (glIsFramebuffer == NULL) {
      glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)load("glIsFramebuffer");  
    }
    return glIsFramebuffer(buffer);
  }
 
  GLuint getNth(int n)
  {
    if (n >= 0 && n < size) {
      return buffers[n];
    } else {
      throw IException("Invalid index %d", n);
    }
  }
    
  void bindNth(GLenum target, int n)
  {
    if (n >= 0 && n < size) {
      bind(target, buffers[n]);
    } else {
      throw IException("Invalid index %d", n);
    }
  }
};

}

#endif
  
  