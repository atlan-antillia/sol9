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
 *  OpenGLShape.h
 *
 *****************************************************************************/

//2017/02/20 Updated.

#pragma once

#include <sol/Exception.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLQuadric.h>
#include <sol/opengl/OpenGLMateria.h>
#include <math.h>

namespace SOL {

class OpenGLShape :public OpenGLObject {
private:
  OpenGLQuadric* quadric; //shallow copy
  OpenGLMateria  materia;
  
public:
  OpenGLShape(OpenGLQuadric* q)
  :OpenGLObject(),
  quadric(q)
  {
    if (q == NULL) {
      throw IException("Invalid argument");
    } 
  } 

  OpenGLShape(OpenGLQuadric* q, OpenGLMateria& mat)
  :OpenGLObject(),
  quadric(q),
  materia(mat)
  {
    if (q == NULL) {
      throw IException("Invalid argument");
    } 
  } 

  ~OpenGLShape()
  {
  }

  GLUquadric* getQuadric()
  {
    GLUquadric* q = NULL;
    if (quadric) {
      q = quadric->getQuadric();
    }
    return q;
  }
  
  void materialize(OpenGLGC* gc, int flags=OpenGLMateria::ALL_MATERIAS)
  {
    materia.materialize(gc, flags);
  }
  
  virtual void draw()  
  {
  }
  
  virtual void draw(OpenGLGC* gc)  
  {
  }

};

}

