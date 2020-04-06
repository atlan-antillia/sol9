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
 *  OpenGLRegularPolygon.h
 *
 *****************************************************************************/

//2017/02/20 Updated.

#pragma once

#include <sol/Exception.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLQuadric.h>
#include <sol/opengl/Vertex3.h>
#include <math.h>

namespace SOL {

class OpenGLRegularPolygon :public OpenGLObject {
private:
  GLuint   number;
  GLenum   primitive;
  SmartPtrs<Vertex3> polygon;
  
public:
  OpenGLRegularPolygon(GLuint n, GLenum p=GL_TRIANGLE_FAN, float z=0.0f)
  :OpenGLObject(),
  number(n),
  primitive(p),
  polygon(NULL)
  {
    float delta = 2.0 * MATH_PI / (float)n;
    polygon = new Vertex3[n+1];
    for (int i = 0; i<=n; i++) {
     polygon[i].x = cos(delta * i);
     polygon[i].y = sin(delta * i);
     polygon[i].z = z; 
    }
  }
  
  ~OpenGLRegularPolygon()
  {
  }
  
  void draw(OpenGLGC* gc)
  {
    gc-> begin(primitive);
    
    if (primitive == GL_TRIANGLE_FAN) {
      gc -> vertex(0.0f, 0.0f, 0.0f);
    }
  
    for (int i= 0; i<= number; i++) {
      gc->vertex(polygon[i].x, polygon[i].y, polygon[i].z);
    }
    
    gc->end();
  }
 
};

}

