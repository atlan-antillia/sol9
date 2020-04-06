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
 *  OpenGLLight.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>

namespace SOL {


class OpenGLLight :public OpenGLObject {
private:
  GLenum light;
  
public:
  OpenGLLight(GLenum light=GL_LIGHT0)
  :light(light)
  {
    //The light parameter will take GL_LIGHT0 to GL_LIGHT7
    glEnable(GL_LIGHTING);
    glEnable(light);    
  }
 
  void enable()
  {
    glEnable(light);    
  }

  void ambient(const GLfloat* values)
  {                                         
    assert(values);
    glLightfv(light, GL_AMBIENT, values);
  }

  void ambient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {                                         
    GLfloat values[] = {r, g, b, a};
    glLightfv(light, GL_AMBIENT, values);
  }

  void specular(const GLfloat* values)
  { 
    assert(values);
    glLightfv(this -> light,GL_SPECULAR, values);
  }

  void specular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  { 
    GLfloat values[] = {r, g, b, a};
    glLightfv(this -> light,GL_SPECULAR, values);
  }

  void diffuse(const GLfloat* values)
  {
    assert(values);
    glLightfv(this -> light, GL_DIFFUSE, values);
  }

  void diffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    GLfloat values[] = {r, g, b, a};
    glLightfv(this -> light, GL_DIFFUSE, values);
  }
  
  void position(const GLfloat* values)
  {
    glLightfv(this -> light,GL_POSITION, values);
  }

  void position(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
  {
    GLfloat values[] = {x, y, z, w};
    glLightfv(this -> light,GL_POSITION, values);
  }

  void spotDirection(const GLfloat* values)
  {
    assert(values);
    glLightfv(this -> light , GL_SPOT_DIRECTION , values); 
  }
  
  void spotDirection(GLfloat x, GLfloat y, GLfloat z)
  {
    GLfloat values[] = {x, y, z};
    glLightfv(this -> light , GL_SPOT_DIRECTION , values); 
  }
  
  void spotExponent(const GLfloat* values)
  {
    assert(values);
    glLightfv(this -> light , GL_SPOT_EXPONENT , values); 
  }
  
  void spotExponent(GLfloat v)
  {
    GLfloat values[] = {v};
    glLightfv(this -> light , GL_SPOT_EXPONENT , values); 
  }
  
  void spotCutoff(const GLfloat* value)
  {
    assert(value);
    glLightfv(this -> light , GL_SPOT_CUTOFF, value); 
  }
  
  void spotCutoff(GLfloat v)
  {
    GLfloat value[] = {v};
    glLightfv(this -> light , GL_SPOT_CUTOFF, value); 
  }

  void constantAttenuation(const GLfloat* value)
  {
    assert(value);
    glLightfv(this -> light , GL_CONSTANT_ATTENUATION, value); 
  }

  void constantAttenuation(GLfloat v)
  {
    GLfloat value[] = {v};
    glLightfv(this -> light , GL_CONSTANT_ATTENUATION, value); 
  }

  void linearAttenuation(const GLfloat* value)
  {
    assert(value);
    glLightfv(this -> light , GL_LINEAR_ATTENUATION, value); 
  }

  void linearAttenuation(GLfloat v)
  {
    GLfloat value[] = {v};
    glLightfv(this -> light , GL_LINEAR_ATTENUATION, value); 
  }

  void quadraticAttenuation(const GLfloat* value)
  {
    assert(value);
    glLightfv(this -> light , GL_QUADRATIC_ATTENUATION, value); 
  }

  void quadraticAttenuation(GLfloat v)
  {
    GLfloat value[] = {v};
    glLightfv(this -> light , GL_QUADRATIC_ATTENUATION, value); 
  }
};
}

