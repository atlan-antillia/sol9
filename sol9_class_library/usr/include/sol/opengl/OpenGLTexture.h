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
 *  OpenGLTexture.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Exception.h>
//#include <sol/ArrayT.h>
#include <sol/opengl/OpenGLObject.h>
#include <math.h>
#include <sol/opengl/TextureCoord2Vertex3.h>

namespace SOL {

class OpenGLTexture :public OpenGLObject {
private:
  GLuint id;
  GLenum target;

public:
  OpenGLTexture(GLenum target = GL_TEXTURE_2D)
  :OpenGLObject(),
   target(target)
  {
/*
target must be one of 
  GL_TEXTURE_1D, 
  GL_TEXTURE_2D, 
  GL_TEXTURE_3D, 
  GL_TEXTURE_1D_ARRAY, 
  GL_TEXTURE_2D_ARRAY, 
  GL_TEXTURE_RECTANGLE, 
  GL_TEXTURE_CUBE_MAP, 
  GL_TEXTURE_CUBE_MAP_ARRAY, 
  GL_TEXTURE_BUFFER, 
  GL_TEXTURE_2D_MULTISAMPLE or 
  GL_TEXTURE_2D_MULTISAMPLE_ARRAY. 
*/
    glEnable(target);

    glGenTextures(1, &id);
  } 

  ~OpenGLTexture()
  {
    glDisable(target);
    glDeleteTextures(1, &id);
  }
  
  void bind()
  {
    glBindTexture(target, id);
  } 

  void unbind()
  {
    glBindTexture(target, 0);
  } 

  void parameter(GLenum name, GLenum value)
  {
    glTexParameterf(target, name, value);
  }

  //2016/07/15
  void parameter(GLenum pname, GLint param)
  {
    glTexParameteri(target, pname, param);
  }
  
  GLenum getTarget()
  {
    return target;
  }

  GLuint getTexture()
  {
    return id;
  }
  
  operator GLuint()
  {
    return id;
  }

  void env(GLenum name, GLenum value)
  {
    glTexEnvf(GL_TEXTURE_ENV, name, value);
  }

  void coord(GLdouble s)
  {
    glTexCoord1d(s);
  }
  
  void coord(GLfloat s)
  {
    glTexCoord1f(s);
  }
  
  void coord(GLint s)
  {
    glTexCoord1i(s);
  }
  
  void coord(GLshort s)
  {
    glTexCoord1s(s);
  }
  
  void coord(GLdouble s, GLdouble t)
  {
    glTexCoord2d(s, t);
  }
  
  void coord(GLfloat s, GLfloat t)
  {
    glTexCoord2f(s, t);
  }

  //2016/07/20
  void coordVertex(TextureCoord2Vertex3& cube)
  {
    glTexCoord2f(cube.coord.s, cube.coord.t);
    glVertex3f(cube.vertex.x, cube.vertex.y, cube.vertex.z);
  }

  //2016/07/20
  void coordVertex(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z)
  {
    glTexCoord2f(s, t);
    glVertex3f(x, y, z);
  }
  
  void coordi(GLint s, GLint t)
  {
    glTexCoord2i(s, t);
  }
  
  void coord(GLshort s, GLshort t)
  {
    glTexCoord2s(s, t);  
  }
  
  void coord(GLdouble s, GLdouble t, GLdouble r)
  {
    glTexCoord3d(s, t, r);
  }

  void coord(GLfloat s, GLfloat t, GLfloat r)
  {
    glTexCoord3f(s, t, r);
  }
  
  void coord(GLint s, GLint t, GLint r)
  {
    glTexCoord3i(s, t, r);
  }
    
  
  void coord(GLshort s, GLshort t, GLshort r)
  {
    glTexCoord3s(s, t, r);
  }
  

  void coord(GLdouble s, GLdouble t, GLdouble r, GLdouble q)
  {
    glTexCoord4d(s, t, r, q);
  }

  void coord(GLfloat s, GLfloat t, GLfloat r, GLfloat q)
  {
    glTexCoord4f(s, t, r, q);
  }  

  void coord(GLint s, GLint t, GLint r, GLint q)
  {
    glTexCoord4i(s, t, r, q);
  }
  
  void coord(GLshort s, GLshort t, GLshort r, GLshort q)
  {
    glTexCoord4s(s, t, r, q);
  }
  
  void coord(const GLdouble *v, size_t size)
  {
    assert(v);
    
    switch(size) {
    case 1: 
      glTexCoord1dv(v);
      break;
      
    case 2:
      glTexCoord2dv(v);
      break;
    case 3:
      glTexCoord3dv(v);
      break;
      
    case 4:
      glTexCoord4dv(v);
      break;
    }
  }
  
  void coord(const GLfloat *v, size_t size)
  {
    assert(v);
    
    switch(size) {
    case 1: 
      glTexCoord1fv(v);
      break;
      
    case 2:
      glTexCoord2fv(v);
      break;
    case 3:
      glTexCoord3fv(v);
      break;
      
    case 4:
      glTexCoord4fv(v);
      break;
    }
  }

  void coord(const GLshort *v, size_t size)
  {
    assert(v);
    
    switch(size) {
    case 1: 
      glTexCoord1sv(v);
      break;
      
    case 2:
      glTexCoord2sv(v);
      break;
    case 3:
      glTexCoord3sv(v);
      break;
      
    case 4:
      glTexCoord4sv(v);
      break;
    }
  }
  
  void coord(const GLint *v, size_t size)
  {
    assert(v);
    
    switch(size) {
    case 1: 
      glTexCoord1iv(v);
      break;
      
    case 2:
      glTexCoord2iv(v);
      break;
    case 3:
      glTexCoord3iv(v);
      break;
      
    case 4:
      glTexCoord4iv(v);
      break;
    }
  }
  
  //2016/07/16 The generation of texture coordinates
  void generate(GLenum coord, GLenum pname,  GLint param) 
  {
    glTexGeni(coord, pname, param); 
  }


  void generate(GLenum coord, GLenum pname, GLfloat param) 
  {
    glTexGenf(coord, pname, param); 
  }

  void generate(GLenum coord, GLenum pname, GLdouble param) 
  {
    glTexGend(coord, pname, param); 
  }
  
  void pixelStore(GLenum pname, GLint param)
  {
    glPixelStorei(pname, param);
  }
  
  void pixelStore(GLenum pname, GLfloat param)
  {
    glPixelStoref(pname, param);
  }
};
}

