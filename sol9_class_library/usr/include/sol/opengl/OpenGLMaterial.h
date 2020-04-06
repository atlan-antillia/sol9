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
 *  OpenGLMaterial.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLMaterial :public OpenGLObject {
private:
  GLenum face;

public:
  OpenGLMaterial(GLenum face)
  :face(face)
  {
    //The parameter face will take CL_FRONT, CL_BACK, CL_FRONT_AND_BACK 
  }

  void ambient(const GLfloat* values)
  {
    assert(values);
    glMaterialfv(this -> face , GL_AMBIENT , values); 
  }

  void ambient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    GLfloat values[] = {r, g, b, a};
    glMaterialfv(this -> face , GL_AMBIENT , values); 
  }

  void diffuse(const GLfloat* values)
  {
    assert(values);
    glMaterialfv(this -> face , GL_DIFFUSE, values); 
  }

  void diffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    GLfloat values[] = {r, g, b, a};
    glMaterialfv(this -> face , GL_DIFFUSE, values); 
  }

  void specular(const GLfloat* values)
  {
    assert(values);
    glMaterialfv(this -> face , GL_SPECULAR, values); 
  }

  void specular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    GLfloat values[] = {r, g, b, a};
    glMaterialfv(this -> face , GL_SPECULAR, values); 
  }

  void shininess(const GLfloat* values)
  {
    assert(values);
    glMaterialfv(this -> face , GL_SHININESS, values); 
  }

  void shininess(GLfloat shine)
  {
    GLfloat values[] = {shine};
    glMaterialfv(this -> face , GL_SHININESS, values); 
  }

  void emission(const GLfloat* values)
  {
    assert(values);
    glMaterialfv(this -> face , GL_EMISSION, values); 
  }

  void emission(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    GLfloat values[] = {r, g, b, a};
    glMaterialfv(this -> face , GL_EMISSION, values); 
  }
  
  
  void ambientAndDiffuse(const GLfloat* values)
  {
    assert(values);
    glMaterialfv(this -> face , GL_AMBIENT_AND_DIFFUSE, values); 
  }

  void colorIndexes(const GLfloat* values)
  {
    assert(values);
    glMaterialfv(this -> face , GL_COLOR_INDEXES, values); 
  }

  void colorIndexes(GLfloat r, GLfloat g, GLfloat b)
  {
    GLfloat values[] = {r, g, b}; 
    glMaterialfv(this -> face , GL_COLOR_INDEXES, values); 
  }

};

}

  
