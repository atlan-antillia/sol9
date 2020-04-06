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
 *  OpenGLFog.h
 *
 *****************************************************************************/


#pragma once

#include <sol/Exception.h>
#include <sol/opengl/OpenGLObject.h>
#include <math.h>

namespace SOL {

class OpenGLFog :public OpenGLObject {
 
public:
  OpenGLFog()
  :OpenGLObject()
  {
    glEnable(GL_FOG);
  } 

  ~OpenGLFog()
  {
    glDisable(GL_FOG);
  }
 
  //mode = GL_LINEARr, AGL_EXP, AGL_EXP2 
  void mode(GLfloat mode = GL_LINEAR)
  {
    glFogi(GL_FOG_MODE, mode);
  }

  void density(GLfloat value)
  {
    glFogf(GL_FOG_DENSITY, value);
  }

  //Specify start position for GL_LINEAR mode
  void start(GLfloat value)
  {
    glFogf(GL_FOG_START, value);
  }
  
  //Specify end position for GL_LINEAR mode
  void end(GLfloat value)
  {
    glFogf(GL_FOG_END, value);
  }
  
  //Specify color index
  void index(GLfloat value)
  {
    glFogf(GL_FOG_INDEX, value);    
  }
  
  //Specify color index
  void color(GLfloat* value)
  {
    assert(value);
    glFogfv(GL_FOG_COLOR, value);    
  }

  void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    GLfloat value[] = {r, g, b, a};
    glFogfv(GL_FOG_COLOR, value);
  }

  void color(GLint* value)
  {
    assert(value);
    glFogiv(GL_FOG_COLOR, value);
  }
};
}

