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
 *  OpenGLWireTorus.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLGeometry.h>

namespace SOL {

class OpenGLWireTorus :public OpenGLGeometry {
private:
  GLdouble innerRadius;
  GLdouble outerRadius; 
  GLint    sides;
  GLint    rings;
  
public:
  OpenGLWireTorus(const OpenGLMateria& mat, GLdouble inner, GLdouble outer, 
       GLint si, GLint ri)
  :OpenGLGeometry(mat),
  innerRadius(inner),
  outerRadius(outer),
  sides(si),
  rings(ri)
  {
  }
  
  void draw(OpenGLGC* gc, GLfloat x, GLfloat y, GLfloat z)
  {
    gc->pushMatrix();
    gc->translate(x, y, z);
    materialize(gc);
    wireTorus(innerRadius, outerRadius, 
       sides, rings );
    gc->popMatrix();
  }
  
};

}

