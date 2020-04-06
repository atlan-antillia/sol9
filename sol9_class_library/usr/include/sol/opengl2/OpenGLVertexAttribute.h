/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OpenGLVertexAttribute.h
 *
 *****************************************************************************/

#pragma once


#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl2/OpenGLProgram.h>

namespace SOL {

class OpenGLVertexAttribute : public OpenGLObject {

#ifdef GL_VERSION_2_0

private:
  GLuint index;
  bool   enable;
  
public:
  OpenGLVertexAttribute(GLuint in, bool onoff=true)
  :OpenGLObject(),
  index(in),
  enable(onoff)
  {
    if (index < 0) {
      throw IException("Invalid attribute index:%d", index); 
    }
    if (enable) {
      enableArray();
    }
  }
  
  ~OpenGLVertexAttribute()
  {
    if (enable) {
      disableArray();
    }
  }
  
  
public:
  void disableArray()
  {
    static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL; 
    if (glDisableVertexAttribArray == NULL) {
      glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)load("glDisableVertexAttribArray");
    }
    glDisableVertexAttribArray(index);
  }
        
  //PFNGLDRAWBUFFERSPROC              GlewBuffers::glDrawBuffers; //(GLsizei n, const GLenum* bufs);
  void enableArray()
  {
    static PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray = NULL; 
    if (glEnableVertexAttribArray == NULL) {
      glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
    }
    glEnableVertexAttribArray(index);
  }

  void getPointer(GLenum pname, void** pointer)
  {
    if (pointer == NULL) {
      throw IException("Invalid pointer parameter.");
    }
    static PFNGLGETVERTEXATTRIBPOINTERVPROC  glGetVertexAttribPointerv = NULL; 
    if (glGetVertexAttribPointerv == NULL) {
      glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)load("glGetVertexAttribPointerv");
    }  
    glGetVertexAttribPointerv(index, pname, pointer); 
  }
  
  void get(GLenum pname, GLdouble* params)
  {
    if (params == NULL) {
      throw IException("Invalid parameter.");
    }

    static PFNGLGETVERTEXATTRIBDVPROC   glGetVertexAttribdv = NULL;
    if (glGetVertexAttribdv == NULL) {
      glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)load("glGetVertexAttribdv");
    }
    glGetVertexAttribdv(index, pname, params);
  }  
    
  void get(GLenum pname, GLfloat* params)
  {
    if (params == NULL) {
      throw IException("Invalid parameter.");
    }

    static PFNGLGETVERTEXATTRIBFVPROC   glGetVertexAttribfv = NULL;
    if (glGetVertexAttribfv == NULL) {
      glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)load("glGetVertexAttribfv");
    }
    glGetVertexAttribfv(index, pname, params);
  }
  
  void get(GLenum pname, GLint* params)
  {
    if (params == NULL) {
      throw IException("Invalid parameter.");
    }

    static PFNGLGETVERTEXATTRIBIVPROC  glGetVertexAttribiv = NULL; 
    if (glGetVertexAttribiv == NULL) {
      glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)load("glGetVertexAttribiv");
    }
    glGetVertexAttribiv(index, pname, params);
  }
  
  void set(GLdouble x)
  {
    static PFNGLVERTEXATTRIB1DPROC   glVertexAttrib1d = NULL; 
    if (glVertexAttrib1d == NULL) {
      glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)load("glVertexAttrib1d");
    }
    glVertexAttrib1d(index, x);
  }
  
  //<added date="2016/08/20"> 
  void set(const GLdouble* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    if (size < 1 || size > 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 1:
      set1(v);
      break;
    case 2:
      set2(v);
      break;
    case 3:
      set3(v);
      break;
    case 4:
      set4(v);
      break;
    }
  }
  
  void set(const GLfloat* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    if (size < 1 || size > 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 1:
      set1(v);
      break;
    case 2:
      set2(v);
      break;
    case 3:
      set3(v);
      break;
    case 4:
      set4(v);
      break;
    }
  }

  void set(const GLbyte* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }    
    switch(size) {
    case 4:
      set4(v);
      break;
    }
  }

  void set(const GLubyte* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }    
    switch(size) {
    case 4:
      set4(v);
      break;
    }
  }
  
  void set(const GLushort* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 4:
      set4(v);
      break;
    }
  }
 
  
  void set(const GLshort* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    if (size < 1 || size > 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 1:
      set1(v);
      break;
    case 2:
      set2(v);
      break;
    case 3:
      set3(v);
      break;
    case 4:
      set4(v);
      break;
    }
  }

  void set(const GLint* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }
    
    switch(size) {
    case 4:
      set4(v);
      break;
    }
  }
  //</added>
  
  void set1(const GLdouble* v)
  {
    static PFNGLVERTEXATTRIB1DVPROC  glVertexAttrib1dv = NULL; 
    if (glVertexAttrib1dv == NULL) {
      glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)load("glVertexAttrib1dv");
    }
    glVertexAttrib1dv(index, v);
  }
  
  void set(GLfloat x)
  {
    static PFNGLVERTEXATTRIB1FPROC  glVertexAttrib1f = NULL; 
    if (glVertexAttrib1f == NULL) {
      glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)load("glVertexAttrib1f");
    }
    glVertexAttrib1f(index, x);
  }
  
  void set1(const GLfloat* v)
  {
    static PFNGLVERTEXATTRIB1FVPROC  glVertexAttrib1fv = NULL;
    if (glVertexAttrib1fv == NULL) {
      glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)load("glVertexAttrib1fv");
    }
    glVertexAttrib1fv(index, v);
  }
  
  void set(GLshort x)
  {
    static PFNGLVERTEXATTRIB1SPROC  glVertexAttrib1s = NULL;   
    if (glVertexAttrib1s == NULL) {
      glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)load("glVertexAttrib1s");
    }
    glVertexAttrib1s(index, x);
  }
  
  void set1(const GLshort* v)
  {
    static PFNGLVERTEXATTRIB1SVPROC  glVertexAttrib1sv = NULL; 
    if (glVertexAttrib1sv == NULL) {
      glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)load("glVertexAttrib1sv");
    }
    glVertexAttrib1sv(index, v);
  }
  
  void set(GLdouble x, GLdouble y)
  {
    static PFNGLVERTEXATTRIB2DPROC  glVertexAttrib2d = NULL; 
    if (glVertexAttrib2d == NULL) {
      glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)load("glVertexAttrib2d");
    }
    glVertexAttrib2d(index, x, y);
  }
  
  void set2(const GLdouble* v)
  {
    static PFNGLVERTEXATTRIB2DVPROC  glVertexAttrib2dv = NULL; 
    if (glVertexAttrib2dv == NULL) {
      glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)load("glVertexAttrib2dv");
    }
    glVertexAttrib2dv(index, v);
  }
  
  void set(GLfloat x, GLfloat y)
  {
    static PFNGLVERTEXATTRIB2FPROC  glVertexAttrib2f = NULL; 
    if (glVertexAttrib2f = NULL) {
      glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)load("glVertexAttrib2f");
    }
    glVertexAttrib2f(index, x, y);
  }
  
  void set2(const GLfloat* v)
  {
    static PFNGLVERTEXATTRIB2FVPROC  glVertexAttrib2fv = NULL; 
    if (glVertexAttrib2fv == NULL) {
      glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)load("glVertexAttrib2fv");
    }
    glVertexAttrib2fv(index, v);
  }
  
  void set(GLshort x, GLshort y)
  {
    static PFNGLVERTEXATTRIB2SPROC  glVertexAttrib2s = NULL;  
    if (glVertexAttrib2s == NULL) {
      glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)load("glVertexAttrib2s");
    }
    glVertexAttrib2s(index, x, y);
  }
  
  void set2(const GLshort* v)
  {
    static PFNGLVERTEXATTRIB2SVPROC  glVertexAttrib2sv = NULL; 
    if (glVertexAttrib2sv == NULL) {
      glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)load("glVertexAttrib2sv");
    }
    glVertexAttrib2sv(index, v);
  }
  
  void set(GLdouble x, GLdouble y, GLdouble z)
  {
    static PFNGLVERTEXATTRIB3DPROC  glVertexAttrib3d = NULL;  
    if (glVertexAttrib3d == NULL) {
      glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)load("glVertexAttrib3d");
    }
    glVertexAttrib3d(index, x, y, z);
  }
  
  void set3(const GLdouble* v)
  {
    static PFNGLVERTEXATTRIB3DVPROC  glVertexAttrib3dv = NULL; 
    if (glVertexAttrib3dv == NULL) {
      glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)load("glVertexAttrib3dv");
    }
    glVertexAttrib3dv(index, v);
  }
  
  void set(GLfloat x, GLfloat y, GLfloat z)
  {
    static PFNGLVERTEXATTRIB3FPROC  glVertexAttrib3f = NULL;  
    if (glVertexAttrib3f == NULL) {
      glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)load("glVertexAttrib3f");
    }
    glVertexAttrib3f(index, x, y, z);
  }
  
  void set3(const GLfloat* v)
  {
    static PFNGLVERTEXATTRIB3FVPROC  glVertexAttrib3fv = NULL; 
    if (glVertexAttrib3fv == NULL) {
      glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)load("glVertexAttrib3fv");
    }
    glVertexAttrib3fv(index, v);
  }
  
  void set(GLshort x, GLshort y, GLshort z)
  {
    static PFNGLVERTEXATTRIB3SPROC  glVertexAttrib3s = NULL;  
    if (glVertexAttrib3s == NULL) {
      glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)load("glVertexAttrib3s");
    }
    glVertexAttrib3s(index, x, y, z);
  }
  
  void set3(const GLshort* v)
  {
    static PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = NULL; 
    if (glVertexAttrib3sv == NULL) {
      glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)load("glVertexAttrib3sv");
    }
    glVertexAttrib3sv(index, v);
  }
  
  void set4N(const GLbyte* v)
  {
    static PFNGLVERTEXATTRIB4NBVPROC  glVertexAttrib4Nbv = NULL; 
    if (glVertexAttrib4Nbv == NULL) {
      glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)load("glVertexAttrib4Nbv");
    }
    glVertexAttrib4Nbv(index, v);
  }
  
  void set4N(const GLint* v)
  {
    static PFNGLVERTEXATTRIB4NIVPROC  glVertexAttrib4Niv = NULL; 
    if (glVertexAttrib4Niv == NULL) {
      glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)load("glVertexAttrib4Niv");
    }
    glVertexAttrib4Niv(index, v);
  }
  
  void set4N(const GLshort* v)
  {
    static PFNGLVERTEXATTRIB4NSVPROC  glVertexAttrib4Nsv = NULL; 
    if (glVertexAttrib4Nsv == NULL) {
      glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)load("glVertexAttrib4Nsv");
    }
    glVertexAttrib4Nsv(index, v);
  }
  
  void set(GLubyte x, GLubyte y, GLubyte z, GLubyte w)
  {
    static PFNGLVERTEXATTRIB4NUBPROC  glVertexAttrib4Nub = NULL; 
    if (glVertexAttrib4Nub == NULL) {
      glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)load("glVertexAttrib4Nub");
    }
    glVertexAttrib4Nub(index, x, y, z, w);
  }
  
  void set4N(const GLubyte* v)
  {
    static PFNGLVERTEXATTRIB4NUBVPROC  glVertexAttrib4Nubv = NULL;
    if (glVertexAttrib4Nubv == NULL) {
      glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)load("glVertexAttrib4Nubv");
    }
    glVertexAttrib4Nubv(index, v);
  }
  
  void set4N(const GLuint* v)
  {
    static PFNGLVERTEXATTRIB4NUIVPROC  glVertexAttrib4Nuiv = NULL; 
    if (glVertexAttrib4Nuiv == NULL) {
      glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)load("glVertexAttrib4Nuiv");
    }
    glVertexAttrib4Nuiv(index, v);
  }
  
  void set4N(const GLushort* v)
  {
    static PFNGLVERTEXATTRIB4NUSVPROC  glVertexAttrib4Nusv = NULL; 
    if (glVertexAttrib4Nusv == NULL) {
      glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)load("glVertexAttrib4Nusv");
    }
    glVertexAttrib4Nusv(index, v);
  }
  
  void set4(const GLbyte* v)
  {
    static PFNGLVERTEXATTRIB4BVPROC  glVertexAttrib4bv = NULL;
    if (glVertexAttrib4bv == NULL) {
      glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)load("glVertexAttrib4bv");
    }
    glVertexAttrib4bv(index, v);
  }
 
  void set(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
  {
    static PFNGLVERTEXATTRIB4DPROC  glVertexAttrib4d = NULL;    
    if (glVertexAttrib4d == NULL) {
      glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)load("glVertexAttrib4d");
    }
    glVertexAttrib4d(index, x, y, z, w);
  }
  
  void set4(const GLdouble* v)
  {
    static PFNGLVERTEXATTRIB4DVPROC  glVertexAttrib4dv = NULL;   
    if (glVertexAttrib4dv == NULL) {
      glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)load("glVertexAttrib4dv");
    }
    glVertexAttrib4dv(index, v);
  }
  
  void set(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
  {
    static PFNGLVERTEXATTRIB4FPROC  glVertexAttrib4f = NULL;
    if (glVertexAttrib4f == NULL) {
      glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)load("glVertexAttrib4f");
    }
    glVertexAttrib4f(index, x, y, z, w);
  }
  
  void set4(const GLfloat* v)
  {
    static PFNGLVERTEXATTRIB4FVPROC  glVertexAttrib4fv = NULL;
    if (glVertexAttrib4fv == NULL) {
      glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)load("glVertexAttrib4fv");
    }
    glVertexAttrib4fv(index, v);
  }
  
  void set4(const GLint* v)
  {
    static PFNGLVERTEXATTRIB4IVPROC  glVertexAttrib4iv = NULL;   
    if (glVertexAttrib4iv == NULL) {
      glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)load("glVertexAttrib4iv");
    }
    glVertexAttrib4iv(index, v);
  }
 
  
  void set(GLshort x, GLshort y, GLshort z, GLshort w)
  {
    static PFNGLVERTEXATTRIB4SPROC  glVertexAttrib4s = NULL;
    if (glVertexAttrib4s == NULL) {
      glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)load("glVertexAttrib4s");
    }
    glVertexAttrib4s(index, x, y, z, w);
  }
  
  void set4(const GLshort* v)
  {
    static PFNGLVERTEXATTRIB4SVPROC  glVertexAttrib4sv = NULL;   
    if (glVertexAttrib4sv == NULL) {
      glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)load("glVertexAttrib4sv");
    }
    glVertexAttrib4sv(index, v);
  }
 
  
  void set4(const GLubyte* v)
  {
    static PFNGLVERTEXATTRIB4UBVPROC  glVertexAttrib4ubv = NULL;  
    if (glVertexAttrib4ubv == NULL) {
      glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)load("glVertexAttrib4ubv");
    }
    glVertexAttrib4ubv(index, v);
  }
  
  void set4(const GLuint* v)
  {
    static PFNGLVERTEXATTRIB4UIVPROC  glVertexAttrib4uiv = NULL;  
    if (glVertexAttrib4uiv == NULL) {
      glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)load("glVertexAttrib4uiv");
    }
    glVertexAttrib4uiv(index, v);
  }
  
  void set4(const GLushort* v)
  {
    static PFNGLVERTEXATTRIB4USVPROC  glVertexAttrib4usv = NULL;  
    if (glVertexAttrib4usv == NULL) {
      glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)load("glVertexAttrib4usv");
    }
    glVertexAttrib4usv(index, v);
  }
 
  void setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
  {
    static PFNGLVERTEXATTRIBPOINTERPROC  glVertexAttribPointer = NULL; 
    if (glVertexAttribPointer == NULL) {
      glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
    }
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  }
#endif

//<added date="2016/08/20">
#ifdef GL_VERSION_3_0

  void getI(GLenum pname, GLint* params)
  {
    static PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = NULL;
    if (glGetVertexAttribIiv == NULL) {
      glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)load("glGetVertexAttribIiv");
    }
    glGetVertexAttribIiv(index, pname, params);
  }
  
  void getI(GLenum pname, GLuint* params)
  {
    static PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = NULL;
    if (glGetVertexAttribIuiv == NULL) {
      glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)load("glGetVertexAttribIuiv");
    }
    glGetVertexAttribIuiv(index, pname, params);
  }
  
  
  void setI(const GLint* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    
    if (size <= 0 || size >4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 1:
      setI1(v);
      break;
    case 2:
      setI2(v);
      break;
    case 3:
      setI3(v);
      break;
    case 4:
      setI4(v);
      break;
    default:
      break;
    }
  }
  
  void setI(const GLuint* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    
    if (size <= 0 || size >4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 1:
      setI1(v);
      break;
    case 2:
      setI2(v);
      break;
    case 3:
      setI3(v);
      break;
    case 4:
      setI4(v);
      break;
    default:
      break;
    }
  }

  void setI(const GLushort* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 4:
      setI4(v);
      break;
    default:
      break;
    }
  }

  void setI(const GLshort* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 4:
      setI4(v);
      break;
    default:
      break;
    }
  }

  void setI(const GLubyte* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 4:
      setI4(v);
      break;
    default:
      break;
    }
  }

    void setI(const GLbyte* v, size_t size)
  {
    if (v == NULL) {
      throw IException("Invalid value parameter.");
    }
    
    if (size != 4) {
      throw IException("Invalid size parameter.");
    }
    switch(size) {
    case 4:
      setI4(v);
      break;
    default:
      break;
    }
  }

  void setI1(GLint v0)
  {
    static PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = NULL;
    if (glVertexAttribI1i == NULL) {
      glVertexAttribI1i =  (PFNGLVERTEXATTRIBI1IPROC)load("glVertexAttribI1i");
    }
    glVertexAttribI1i(index, v0);
  }
  
  void setI1(const GLint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = NULL;
    if (glVertexAttribI1iv == NULL) {
      glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)load("glVertexAttribI1iv");
    }
    glVertexAttribI1iv(index, v0);
  }
  
  void setI1(GLuint v0)
  {
    static PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = NULL;
    if (glVertexAttribI1ui == NULL) {
      glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)load("glVertexAttribI1ui");
    }
    glVertexAttribI1ui(index, v0);
  }
  
  void setI1(const GLuint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = NULL;
    if (glVertexAttribI1uiv == NULL) {
      glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)load("glVertexAttribI1uiv");
    }
    glVertexAttribI1uiv(index, v0);
  }
  
  void setI2(GLint v0, GLint v1)
  {
    static PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = NULL;
    if (glVertexAttribI2i == NULL) {
      glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)load("glVertexAttribI2i");
    }
    glVertexAttribI2i(index, v0, v1);
  }
  
  void setI2(const GLint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = NULL;
    if (glVertexAttribI2iv == NULL) {
      glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)load("glVertexAttribI2iv");
    }
    glVertexAttribI2iv(index, v0);
  }
  
  void setI2(GLuint v0, GLuint v1)
  {
    static PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2u = NULL;
    if (glVertexAttribI2u == NULL) {
      glVertexAttribI2u = (PFNGLVERTEXATTRIBI2UIPROC)load("glVertexAttribI2u");
    }
    glVertexAttribI2u(index, v0, v1);
  }
  
  void setI2(const GLuint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = NULL;
    if (glVertexAttribI2uiv == NULL) {
      glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)load("glVertexAttribI2uiv");
    }
    glVertexAttribI2uiv(index, v0);
  }
  
  void setI3(GLint v0, GLint v1, GLint v2)
  {
    static PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = NULL;
    if (glVertexAttribI3i == NULL) {
      glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)load("glVertexAttribI3i");
    }
    glVertexAttribI3i(index, v0, v1, v2);
  }
  
  void setI3(const GLint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = NULL;
    if (glVertexAttribI3iv == NULL) {
      glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)load("glVertexAttribI3iv");
    }
    glVertexAttribI3iv(index, v0);
  }
  
  void setI3(GLuint v0, GLuint v1, GLuint v2)
  {
    static PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = NULL;
    if (glVertexAttribI3ui == NULL) {
      glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)load("glVertexAttribI3ui");
    }
    glVertexAttribI3ui(index, v0, v1, v2);
  }
  
  void setI3(const GLuint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = NULL;
    if (glVertexAttribI3uiv == NULL) {
      glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)load("glVertexAttribI3uiv");
    }
    glVertexAttribI3uiv(index, v0);
  }
  
  void setI4(const GLbyte* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = NULL;
    if (glVertexAttribI4bv == NULL) {
      glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)load("glVertexAttribI4bv");
    }
    glVertexAttribI4bv(index, v0);
  }
  
  void setI4(GLint v0, GLint v1, GLint v2, GLint v3)
  {
    static PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = NULL;
    if (glVertexAttribI4i == NULL) {
      glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)load("glVertexAttribI4i");
    }
    glVertexAttribI4i(index, v0, v1, v2, v3);
  }
  
  void setI4(const GLint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = NULL;
    if (glVertexAttribI4iv == NULL) {
      glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)load("glVertexAttribI4iv");
    }
    glVertexAttribI4iv(index, v0);
  }
  
  void setI4(const GLshort* v0)
  {
    static PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = NULL;
    if (glVertexAttribI4sv == NULL) {
      glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)load("glVertexAttribI4sv");
    }
    glVertexAttribI4sv(index, v0);
  }
  
  void setI4(const GLubyte* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }

    static PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = NULL;
    if (glVertexAttribI4ubv == NULL) {
      glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)load("glVertexAttribI4ubv");
    }
    glVertexAttribI4ubv(index, v0);
  }
  
  void setI4(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
  {
    static PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = NULL;
    if (glVertexAttribI4ui == NULL) {
      glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)load("glVertexAttribI4ui");
    }
    glVertexAttribI4ui(index, v0, v1, v2, v3);
  }
  
  void setI4(const GLuint* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }
\
    static PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = NULL;
    if (glVertexAttribI4uiv == NULL) {
      glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)load("glVertexAttribI4uiv");
    }
    glVertexAttribI4uiv(index, v0);
  }
  
  void setI4(const GLushort* v0)
  {
    if (v0 == NULL) {
      throw IException("Invalid value parameter.");
    }
    static PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = NULL;
    if (glVertexAttribI4usv == NULL) {
      glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)load("glVertexAttribI4usv");
    }
    glVertexAttribI4usv(index, v0);
  }
  
  void setPointer(GLint size, GLenum type, GLsizei stride, const void* pointer)
  {
    if (pointer == NULL) {
      throw IException("Invalid pointer parameter.");
    }
    
    static PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = NULL;
    if (glVertexAttribIPointer == NULL) {
      glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)load("glVertexAttribIPointer");
    }
    glVertexAttribIPointer(index, size, type, stride, pointer);
  }
//</added>


#endif
#ifdef GL_VERSION_3_3
  void divisor(GLuint div)
  {
    static PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = NULL;
    if (glVertexAttribDivisor == NULL) {
      glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)load("glVertexAttribDivisor");
    }
    glVertexAttribDivisor(index, div);
  }
#endif
};

}


