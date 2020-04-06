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
 *  OpenGLObject.h
 *
 *****************************************************************************/

//2016/07/01 Modified to include glew.h.

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

//#define GL_GLEXT_PROTOTYPES
//2016/07/01
#include <GL/glew.h>
#include <GL/wglew.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

namespace SOL {

class OpenGLObject : public Object {

public:
  OpenGLObject()
  {
  }
  
  GLenum getError()
  {
    return glGetError();
  }

  const char* errorString()
  {
    const char* errString = "";
    GLenum err = getError();
    if (err != GL_NO_ERROR) {
      errString = (const char*)gluErrorString(err);
    }
    return errString;
  }

  //2016/06/30
  void* load(const char* name)
  {
    void* address = NULL;
    if (name && strlen(name) > 0) {
      address =  wglGetProcAddress((LPCSTR)name);
      if (address == NULL) {
        throw IException("Failed to load function : %s", name);
      }
    } else {
      throw IException("Invalid argument.");
    }
    return address;
  }
  
  //2016/07/04
  void checkError()
  {
    GLenum err = getError();
    if (err != GL_NO_ERROR) {
      const char* errString = (const char*)gluErrorString(err);
      throw Exception((int)err, "OpenGL error: %s", errString);
    }
  }
};

}

