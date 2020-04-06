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
 *  OpenGLColorMaterial.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLColorMaterial :public OpenGLObject {
private:
  GLenum face;
  GLenum mode;
public:
  OpenGLColorMaterial(GLenum face, GLenum mode)
  :face(face),
   mode(mode)
  {
    glEnable(GL_COLOR_MATERIAL);

    //The parameter face will take CL_FRONT, CL_BACK, CL_FRONT_AND_BACK 
   
    //The parameter mode will take GL_EMISSION, GL_AMBIENT, GL_DIFFUSE, 
    //GL_SPECULAR, and GL_AMBIENT_AND_DIFFUSE. 
    // The initial value is GL_AMBIENT_AND_DIFFUSE. 

    glColorMaterial(face, mode);
  }

  ~OpenGLColorMaterial()
  {
    glDisable(GL_COLOR_MATERIAL);
  }

};

}

  
