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
 *  OpenGLDebugARB.h 
 *
 *****************************************************************************/

#pragma once

#ifdef GL_ARB_vertex_buffer_object

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLDebugARB :public OpenGLObject {

public:
  OpenGLBufferARB()
  {
  } 


public:
  ~OpenGLDebugARB()
  {
  }
  
public:
  void messageCallback(GLDEBUGPROCARB callback, const void *userParam)
  {
    static PFNGLDEBUGMESSAGECALLBACKARBPROC glCallbackProc= NULL;
    if (glCallbackProc == NULL) {
      glCallbackProc = (PFNGLDEBUGMESSAGECALLBACKARBPROC)load("glDebugMessageCallbackARB");
    }
    glCallbackProc(callback, userParam);
  }    
  
  void messageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
  {
    static PFNGLDEBUGMESSAGECONTROLARBPROC glMessageControlProc= NULL;
    if (glMessageControlProc == NULL) {
      glMessageControlProc = (PFNGLDEBUGMESSAGECALLBACKARBPROC)load("glDebugMessageControlARB");
      printf("create 2\n");
    }
    glMessageControlProc(source, type, severity, count, ids, enabled);
  }    

  void insert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf)
  {
    static PFNGLDEBUGMESSAGEINSERTARBPROC glInsertProc = NULL;
    if (glInsertProc == NULL) {
      glInsertProc = (PFNGLDEBUGMESSAGEINSERTARBPROC)load("glDebugMessageInsertARB");
    }
    glInsertProc(source, type, id, severity, length, buf);
  }
  
  GLuint getDebugMessageLog(GLuint count, GLsizei bufSize, GLenum* sources, 
      GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog)
  {
    static PFNGLGETDEBUGMESSAGELOGARBPROC glGetDebugMessageProc = NULL;
    if (glGetDebugMessageProc == NULL) {
      glGetDebugMessageProc = (PFNGLGETDEBUGMESSAGELOGARBPROC)load("glGetDebugMessageLogARB");
    }
    return glGetDebugMessageProc(count, bufSize, sources, 
        types, ids, severities, lengths, messageLog);
  }
  
};
}

#endif

