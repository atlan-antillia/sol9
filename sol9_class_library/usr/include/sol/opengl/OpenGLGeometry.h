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
 *  OpenGLGeometry.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLMateria.h>

#include <GL/glut.h>

namespace SOL {

class OpenGLGeometry :public OpenGLObject {
private:
  OpenGLMateria  materia;
  
public:
  OpenGLGeometry()
  {
  }
public:
  OpenGLGeometry(const OpenGLMateria& mat)
  :materia(mat)
  {
  }

  virtual void draw(OpenGLGC* gc, GLfloat x, GLfloat y, GLfloat z)
  {
  }
  
  void  wireCube( GLdouble size )
  {
  	glutWireCube(size);
  }

  void  solidCube( GLdouble size )
  {
    glutSolidCube(size);
  }

  void  wireSphere( GLdouble radius, GLint slices, GLint stacks )
  {
    glutWireSphere(radius, slices, stacks);
  }

  void  solidSphere( GLdouble radius, GLint slices, GLint stacks )
  {
    glutSolidSphere(radius, slices, stacks);
  }

  void  wireCone( GLdouble base, GLdouble height, 
       GLint slices, GLint stacks )
  {
    glutWireCone(base, height, slices, stacks);
  }

  void  solidCone( GLdouble base, GLdouble height, GLint slices, GLint stacks )
  {
    glutSolidCone(base, height, slices, stacks);
  }

  void  wireTorus( GLdouble innerRadius, GLdouble outerRadius, 
       GLint sides, GLint rings )
  {
    glutWireTorus(innerRadius, outerRadius, sides, rings);
  }

  void  solidTorus( GLdouble innerRadius, GLdouble outerRadius, 
       GLint sides, GLint rings )
  {
    glutSolidTorus(innerRadius, outerRadius, sides, rings);
  }

  void  wireTeapot(GLdouble value)
  {
    glutWireTeapot(value);
  }

  void  solidTeapot(GLdouble value) 
  {
    glutSolidTeapot(value);
  }
  
  void materialize(OpenGLGC* gc, int flags=OpenGLMateria::ALL_MATERIAS)
  {
    materia.materialize(gc, flags);
  }
  
  void ambient(Color4& color)
  {
    materia.ambient(color);
  }

  void ambient(const GLfloat* value, GLsizei size)
  {
    materia.ambient(value, size);
  }

  void ambient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    materia.ambient(r, g, b, a);
  }

  void diffuse(Color4& color)
  {
    materia.diffuse(color);
  }

  void diffuse(const GLfloat* value, GLsizei size)
  {
    materia.diffuse(value, size);
  }

  void diffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    materia.diffuse(r, g, b, a);
  }

  void specular(Color4& color)
  {
    materia.specular(color);
  }

  void specular(const GLfloat* value, GLsizei size)
  {
    materia.specular(value, size);
  }

  void specular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    materia.specular(r, g, b, a);
  }

  void shininess(GLfloat shine)
  {
    shininess(shine);
  }

  void emission(Color4& color)
  {
    materia.emission(color);
  }

  void emission(const GLfloat* value, GLsizei size)
  {
    materia.emission(value, size);
  }

  void emission(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    materia.emission(r, g, b, a);
  }
  
};

}

