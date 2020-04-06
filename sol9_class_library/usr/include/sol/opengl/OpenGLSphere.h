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
 *  OpenGLSphere.h
 *
 *****************************************************************************/

//2017/02/20 Updated.

#pragma once

#include <sol/Exception.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLShape.h>
#include <math.h>

namespace SOL {

class OpenGLSphere :public OpenGLShape {
private:
  GLfloat radius;
  GLint slices;
  GLint stacks;
  
public:
  OpenGLSphere(OpenGLQuadric* quadric)
  :OpenGLShape(quadric),
  radius(1.0f),
  slices(20),
  stacks(20)
  {
  } 

public:
  OpenGLSphere(OpenGLQuadric* quadric, GLdouble r, GLint sl, GLint st)
  :OpenGLShape(quadric),
  radius(r),
  slices(sl),
  stacks(st)
  {
  } 

public:
  OpenGLSphere(OpenGLQuadric* quadric, OpenGLMateria& materia, 
        GLdouble r, GLint sl, GLint st)
  :OpenGLShape(quadric, materia),
  radius(r),
  slices(sl),
  stacks(st)
  {
  } 

  ~OpenGLSphere()
  {
  }
 
  void draw(GLdouble r, GLint sl, GLint st)
  {
    gluSphere(getQuadric(), 
                        r,
                        sl,
                        st);
  }

  void draw()  
  {
    gluSphere(getQuadric(),
                        this->radius,
                        this->slices,
                        this->stacks);
  }

  void draw(OpenGLGC* gc, GLfloat x, GLfloat y, GLfloat z)  
  {
    if (gc) {
      gc->pushMatrix();
      gc->translate(x, y, z);
      materialize(gc);
      gluSphere(getQuadric(),
                        this->radius,
                        this->slices,
                        this->stacks);
      gc->popMatrix();
    }
  }

};

}

