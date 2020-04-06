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
 *  OpenGLQuadric.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Exception.h>
//#include <sol/ArrayT.h>
#include <sol/opengl/OpenGLObject.h>
#include <math.h>

namespace SOL {


class OpenGLQuadric :public OpenGLObject {
private:
  GLUquadric* quadric;
 
public:
  OpenGLQuadric()
  :OpenGLObject(),
  quadric(NULL)
  {
    quadric = gluNewQuadric();
  } 

  ~OpenGLQuadric()
  {
    gluDeleteQuadric(quadric);
  }
 
  //2016/08/01
  operator   GLUquadric*()
  {
    return quadric;
  }
  
  GLUquadric* getQuadric()
  {
     return quadric;
  }

  void orientation(GLenum orientation)
  {
    //orientation will take GLU_OUTSIDE, and GLU_INSIDE
    gluQuadricOrientation(quadric, orientation);
  }

  void texture(GLboolean texture)
  {
    gluQuadricTexture(quadric, texture);
  }

  void drawStyle(GLenum style)
  {
    //style will take GLU_FILL, GLU_LINE, GLU_SILHOUETTE, and GLU_POINT. 
    gluQuadricDrawStyle(quadric, style);
  }

  void normals(GLenum normal)
  {
    //normal will take GLU_NONE, GLU_FLAT, and GLU_SMOOTH
    gluQuadricNormals(quadric, normal);
  }
};

}

