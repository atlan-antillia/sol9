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
 *  OpenGLMateria.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/Color4.h>
#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLMateria :public OpenGLObject {
private:
  GLenum   _face;
  Color4  _ambient;
  Color4  _diffuse;
  Color4  _specular;
  Color4  _emission;
  GLfloat _shininess;
  bool    _enabled;
  
public:
  static const int  AMBIENT   =0x00001;
  static const int  DIFFUSE   =0x00010;
  static const int  SPECULAR  =0x00100;
  static const int  EMISSION  =0x01000;
  static const int  SHININESS =0x10000;
  
  static const int ALL_MATERIAS = (AMBIENT|DIFFUSE|SPECULAR|EMISSION|SHININESS);
  
private:
  void  initialize()
  {
    _ambient  = {0.0f, 0.0f, 0.0f, 0.0f};
    _diffuse  = {0.0f, 0.0f, 0.0f, 0.0f};
    _specular = {0.0f, 0.0f, 0.0f, 0.0f};
    _emission = {0.0f, 0.0f, 0.0f, 0.0f};

    _shininess = 0.0f;
  }
  
public:
  OpenGLMateria(GLenum face=GL_FRONT)
  :_face(face),
  _enabled(false)
  {
    initialize();
  }
    
public:
  OpenGLMateria(GLenum face,  ////The parameter face will take CL_FRONT, CL_BACK, CL_FRONT_AND_BACK
      Color4& cambient, 
      Color4& cdiffuse, 
      Color4& cspecular,
      Color4& cemission,
      float   shininess)
  :_face(face),
  _enabled(true)
  {
    initialize();
    _ambient   = cambient;
    _diffuse   = cdiffuse;
    _specular  = cspecular;
    _emission = cemission;
    _shininess = shininess;
  }

  OpenGLMateria(const OpenGLMateria& mat)
  {
    initialize();
    _face      = mat._face;
    _ambient   = mat._ambient;
    _diffuse   = mat._diffuse;
    _specular  = mat._specular;
    _emission  = mat._emission;
    _shininess = mat._shininess;
    _enabled   = mat._enabled;
  }
  
  void enable()
  {
    _enabled = true;
  }
  
  void disable()
  {
    _enabled = false;
  }

  void face(GLenum face)
  {
    _face = face;
  }
  
  GLenum face()
  {
    return _face;
  }
  
  void ambient(Color4& color)
  {
    _ambient = color;
  }

  void ambient(const GLfloat* value, GLsizei size)
  {
    assert(value);
    assert(size==4);
    _ambient = {value[0], value[1], value[2], value[3]};
  }

  void ambient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    _ambient = {r, g, b, a};
  }

  void diffuse(Color4& color)
  {
    _diffuse = color;
  }

  void diffuse(const GLfloat* value, GLsizei size)
  {
    assert(value);
    assert(size == 4);
    _diffuse = {value[0], value[1], value[2], value[3]};
  }

  void diffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
   _diffuse = {r, g, b, a};
  }

  void specular(Color4& color)
  {
    _specular = color;
  }

  void specular(const GLfloat* value, GLsizei size)
  {
    assert(value);
    assert(size==4);
    _specular = {value[0], value[1], value[2], value[3]};
  }

  void specular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    _specular = {r, g, b, a};
  }

  void shininess(GLfloat shine)
  {
    _shininess = shine;
  }

  void emission(Color4& color)
  {
    _emission = color;
  }

  void emission(const GLfloat* value, GLsizei size)
  {
    assert(value);
    assert(size==4);
    _emission = {value[0], value[1], value[2], value[3]};
  }

  void emission(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    _emission = {r, g, b, a};
  }
  
  void materialize(OpenGLGC* gc, int flags=ALL_MATERIAS)
  {
    if (_enabled ) {
      if (flags &  AMBIENT) {
        GLfloat value[4] = {_ambient.r, _ambient.g, _ambient.b, _ambient.a};
        glMaterialfv(this -> _face , GL_AMBIENT , value); 
      }
      if (flags & DIFFUSE) {
        GLfloat value[4] = {_diffuse.r, _diffuse.g, _diffuse.b, _diffuse.a};
        glMaterialfv(this -> _face , GL_DIFFUSE, value); 
      }
      if (flags & SPECULAR) {
        GLfloat value[4] = {_specular.r, _specular.g, _specular.b, _specular.a};
        glMaterialfv(this -> _face , GL_SPECULAR, value); 
      }
      if (flags & EMISSION ) {
        GLfloat value[4] = {_emission.r, _emission.g, _emission.b, _emission.a};
        glMaterialfv(this -> _face , GL_EMISSION, value);    
      }
      if (flags & SHININESS) {
        GLfloat value[1] = {_shininess};
        glMaterialfv(this -> _face , GL_SHININESS, value); 
      }
    }
  }
};

}

  
