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
 *  OpenGLTexturedSphere.h
 *
 *****************************************************************************/

//2017/02/20 Updated.
//2017/09/10 Updated.

#pragma once
#include <sol/opengl/OpenGLQuadric.h>
#include <sol/opengl/OpenGLTexture2D.h>
#include <sol/opengl/OpenGLSphere.h>
#include <sol/opengl/OpenGLImageInfo.h>

#include <math.h>

namespace SOL {

class OpenGLTexturedSphere :public OpenGLTexture2D {
private:
  SmartPtr<OpenGLQuadric> quadric;
  SmartPtr<OpenGLSphere>  sphere;
public:
  OpenGLTexturedSphere(const char* filename)
  :OpenGLTexture2D()
  {
    quadric = new OpenGLQuadric();
    sphere = new OpenGLSphere(quadric);
    //2019/04/13
    GLuint tex = getTexture();
    quadric->texture(tex);

    load(filename);
    drawStyle(GLU_FILL);
  } 

public:
  OpenGLTexturedSphere(const char* filename, 
            GLdouble r, GLint sl, GLint st)
  :OpenGLTexture2D()
  {
    quadric = new OpenGLQuadric();
    sphere = new OpenGLSphere(quadric, r, sl, st);
    //2019/04/13
    GLuint tex = getTexture();
    quadric->texture(tex);

    load(filename);
    drawStyle(GLU_FILL);
  } 

public:
  //2017/09/10
  OpenGLTexturedSphere(OpenGLImageInfo& imageInfo, 
            GLdouble r, GLint sl, GLint st)
  :OpenGLTexture2D()
  {
    quadric = new OpenGLQuadric();
    sphere = new OpenGLSphere(quadric, r, sl, st);
    //2019/04/13
    GLuint tex = getTexture();
    quadric->texture(tex);

    setImageInfo(imageInfo);
    drawStyle(GLU_FILL);
  } 
  
public:
  OpenGLTexturedSphere(const char* filename, OpenGLMateria& materia, 
        GLdouble r, GLint sl, GLint st)
  :OpenGLTexture2D()
  {
    quadric = new OpenGLQuadric();
    sphere = new OpenGLSphere(quadric, materia, r, sl, st);
    //2019/04/13
    GLuint tex = getTexture();
    quadric->texture(tex);

    load(filename);
    drawStyle(GLU_FILL);
  } 

  ~OpenGLTexturedSphere()
  {
  }

  void drawStyle(GLenum style)
  {
    //style will take GLU_FILL, GLU_LINE, GLU_SILHOUETTE, and GLU_POINT. 
    quadric->drawStyle(style);    
  }
  
  void orientation(GLenum orientation)
  {
    //orientation will take GLU_OUTSIDE, and GLU_INSIDE
    quadric->orientation(orientation);
  }
 
  void normals(GLenum normal)
  {
    //normal will take GLU_NONE, GLU_FLAT, and GLU_SMOOTH
    quadric->normals(normal);
  }
  
  virtual void load(const char* filename)
  {
    bind();

    pixelStore(GL_UNPACK_ALIGNMENT, 4);
    
    parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //env(GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
   // generate(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
   // generate(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

    parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
 
    try {
      imageFromFile(filename);
    } catch (Exception& ex) {
      ex.display();
    }
    
    unbind();
  }
    
  //2017/09/10
  virtual void setImageInfo(OpenGLImageInfo& imageInfo)
  {
    bind();

    pixelStore(GL_UNPACK_ALIGNMENT, 4);
    
    parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //env(GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
   // generate(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
   // generate(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

    parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
 
    try {
      image(imageInfo);
    } catch (Exception& ex) {
      ex.display();
    }    
    unbind();
  } 
  
  void draw(GLdouble r, GLint sl, GLint st)
  {
    bind();
    sphere->draw();
    gluSphere(quadric->getQuadric(), 
                        r,
                        sl,
                        st);
    unbind();
  }

  void draw(OpenGLGC* gc)  
  {
    if (gc) {
      gc->enable(GL_NORMALIZE);
      gc->enable(GL_COLOR_MATERIAL);
      bind();
      sphere->draw(gc, 0.0f, 0.0f, 0.0f);
      unbind();
    }
  }

  void draw(OpenGLGC* gc, GLfloat x, GLfloat y, GLfloat z)  
  {
    if (gc) {
      gc->enable(GL_NORMALIZE);
      gc->enable(GL_COLOR_MATERIAL);
      bind();
      sphere->draw(gc, x, y, z );
      unbind();
    }
  }

};

}

