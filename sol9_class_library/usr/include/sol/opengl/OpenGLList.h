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
 *  OpenGLDisplayList.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/Exception.h>

namespace SOL {

class OpenGLList :public OpenGLObject {
private:
  GLuint list;
  GLenum mode;

public:
  OpenGLList(GLuint list, GLenum mode)
  :list(list),
   mode(mode)
  {
    if (list <= 0) {
      throw IException("Invalid list id:%d", list);
    }

    if (glIsList(list) == GL_TRUE) {
      throw IException("Already used id:%d", list);
    } 

    if (mode == GL_COMPILE || mode == GL_COMPILE_AND_EXECUTE) {
      glNewList(list, mode);
    } else {
      throw IException("Invalid mode:%d", mode); 
    } 
  }

  OpenGLList(GLuint list)
  :list(list),
   mode(0)
  {
    if (list <= 0) {
      throw IException("Invalid list id:%d", list);
    }
    //Play displaylist 
  }

  ~OpenGLList()
  {
    if (mode != 0) {
      save();
    }
  }

  void save()
  {
    glEndList();
  }

  void call()
  {
    if (mode == 0) {
      glCallList(list);
    }
  }
};
}

