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
 *  OpenGLCylinder.h
 *
 *****************************************************************************/

//2017/02/28 Updated.

#pragma once

#include <sol/Exception.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLShape.h>
#include <math.h>

namespace SOL {

class OpenGLCylinder :public OpenGLShape {
private:
  GLdouble base;  
  GLdouble top;  
  GLdouble height;  
  GLint    slices;  
  GLint    stacks;
  
public:
  OpenGLCylinder(OpenGLQuadric* quadric)
  :OpenGLShape(quadric),
  base(1.0),  
  top(1.0),  
  height(1.0),
  slices(40),  
  stacks(40)
  {
  } 

public:
  OpenGLCylinder(OpenGLQuadric* quadric, 
      GLdouble b,  GLdouble t, GLdouble h,  
      GLint    sl, GLint    st)
  :OpenGLShape(quadric),
  base(b),  
  top(t),  
  height(h),
  slices(sl),  
  stacks(st)
  {
  } 

public:
  OpenGLCylinder(OpenGLQuadric* quadric, OpenGLMateria& materia, 
      GLdouble b,  GLdouble t, GLdouble h,  
      GLint    sl, GLint    st)
  :OpenGLShape(quadric, materia),
  base(b),  
  top(t),  
  height(h),
  slices(sl),  
  stacks(st)
  {
  } 

  ~OpenGLCylinder()
  {
  }
 
  void draw(GLdouble b,  GLdouble t, GLdouble h,  
            GLint    sl, GLint    st)
  {
    gluCylinder(getQuadric(), 
                  b, t, h,
                  sl, st);
  }

  void draw()  
  {
    gluCylinder(getQuadric(),
          this->base,
          this->top,  
          this->height, 
          this->slices,  
          this->stacks);
  }

  void draw(OpenGLGC* gc, GLfloat x, GLfloat y, GLfloat z)  
  {
    if (gc) {
      gc->pushMatrix();
      gc->translate(x, y, z);
      materialize(gc);
      gluCylinder(getQuadric(),
          this->base,
          this->top,  
          this->height,  
          this->slices,  
          this->stacks);
      gc->popMatrix();
    }
  }

};

}

