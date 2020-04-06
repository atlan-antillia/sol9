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
 *  OpenGLUniform.h
 *
 *****************************************************************************/

//2016/08/19 Updated for GL_VERSION_2_1

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl2/OpenGLProgram.h>

namespace SOL {

class OpenGLUniform :public OpenGLObject {

#ifdef GL_VERSION_2_0

private:
  GLint location;

public:

  OpenGLUniform(OpenGLProgram& program, const GLchar* name)
  :OpenGLObject(),
  location(INVALID_VALUE)
  {
    location = program.getUniformLocation(name);
    if (location == INVALID_VALUE) {
      throw IException("Failed to getUniformLocation %s", name); 
    }
  }
  
public:
  OpenGLUniform(GLint loc)
  :OpenGLObject(),
  location(loc)
  {
    if (location == INVALID_VALUE) {
      throw IException("Invalid location value %d", location); 
    }    
  }
  
  void set(GLfloat v0)
  {
    static PFNGLUNIFORM1FPROC      glUniform1f = NULL;
    if ( glUniform1f == NULL) {
      glUniform1f = (PFNGLUNIFORM1FPROC)load("glUniform1f");
    }
    glUniform1f(location, v0);
  }
  
  void set1fv(GLsizei count, const GLfloat* value)
  {
    static PFNGLUNIFORM1FVPROC     glUniform1fv = NULL; 
    if (glUniform1fv == NULL) {
      glUniform1fv = (PFNGLUNIFORM1FVPROC)load("glUniform1fv");
    }
    glUniform1fv(location, count, value);
  }
  
  void set(GLint v0)
  {
    static PFNGLUNIFORM1IPROC      glUniform1i = NULL;  
    if (glUniform1i == NULL) {
      glUniform1i = (PFNGLUNIFORM1IPROC)load("glUniform1");
    }
    glUniform1i(location, v0);
  }
  
  void set1iv(GLsizei count, const GLint* value)
  {
    static PFNGLUNIFORM1IVPROC     glUniform1iv = NULL;
    if (glUniform1iv == NULL) {
      glUniform1iv = (PFNGLUNIFORM1IVPROC)load("glUniform1iv");
    }
    glUniform1iv(location, count, value);
  }
  
  void set(GLfloat v0, GLfloat v1)
  {
    static PFNGLUNIFORM2FPROC      glUniform2f = NULL;   
    if (glUniform2f) {
      glUniform2f = (PFNGLUNIFORM2FPROC)load("glUniform2f");
    }
    glUniform2f(location, v0, v1);
  }
  
  void set2fv(GLsizei count, const GLfloat* value)
  {
    static PFNGLUNIFORM2FVPROC     glUniform2fv = NULL; 
    if (glUniform2fv == NULL) {
      glUniform2fv = (PFNGLUNIFORM2FVPROC)load("glUniform2fv");
    }
    glUniform2fv(location, count, value);
  }
  
  void set(GLint v0, GLint v1)
  {
    static PFNGLUNIFORM2IPROC      glUniform2i = NULL; 
    if (glUniform2i == NULL) {
      glUniform2i = (PFNGLUNIFORM2IPROC)load("glUniform2i");
    }
    glUniform2i(location, v0, v1);
  }
  
  void set2iv(GLsizei count, const GLint* value)
  {
    static PFNGLUNIFORM2IVPROC     glUniform2iv = NULL; 
    if (glUniform2iv == NULL) {
      glUniform2iv = (PFNGLUNIFORM2IVPROC)load("glUniform2iv");
    }
    glUniform2iv(location, count, value);
  }
  
  void set(GLfloat v0, GLfloat v1, GLfloat v2)
  {
    static PFNGLUNIFORM3FPROC      glUniform3f = NULL; 
    if (glUniform3f == NULL) {
      glUniform3f = (PFNGLUNIFORM3FPROC)load("glUniform3f");
    }
    glUniform3f(location, v0, v1, v2);
  }
  
  void set3fv(GLsizei count, const GLfloat* value)
  {
    static PFNGLUNIFORM3FVPROC     glUniform3fv = NULL; 
    if (glUniform3fv == NULL) {
      glUniform3fv = (PFNGLUNIFORM3FVPROC)load("glUniform3fv");
    }
    glUniform3fv(location, count, value);
  }
  
  void set(GLint v0, GLint v1, GLint v2)
  {
    static PFNGLUNIFORM3IPROC      glUniform3i = NULL;
    if (glUniform3i == NULL) {
      glUniform3i = (PFNGLUNIFORM3IPROC)load("glUniform3i");
    }
    glUniform3i(location, v0, v1, v2);
  }
  
  void set3iv(GLsizei count, const GLint* value)
  {
    static PFNGLUNIFORM3IVPROC     glUniform3iv = NULL; 
    if (glUniform3iv == NULL) {
      glUniform3iv = (PFNGLUNIFORM3IVPROC)load("glUniform3iv");
    }
    glUniform3iv(location, count, value);
  }
  
  void set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
  {
    static PFNGLUNIFORM4FPROC      glUniform4f = NULL;  
    if (glUniform4f == NULL) {
      glUniform4f = (PFNGLUNIFORM4FPROC)load("glUniform4f");
    }
    glUniform4f(location, v0, v1, v2, v3);
  }
  
  void set4fv(GLsizei count, const GLfloat* value)
  {
    static PFNGLUNIFORM4FVPROC     glUniform4fv = NULL; 
    if (glUniform4fv == NULL) {
      glUniform4fv = (PFNGLUNIFORM4FVPROC)load("glUniform4fv");
    }
    glUniform4fv(location, count, value);
  }
  
  void set(GLint v0, GLint v1, GLint v2, GLint v3)
  {
    static PFNGLUNIFORM4IPROC      glUniform4i = NULL;  
    if (glUniform4i == NULL) {
      glUniform4i = (PFNGLUNIFORM4IPROC)load("glUniform4");
    }
    glUniform4i(location, v0, v1, v2, v3);
  }
  
  void set4iv(GLsizei count, const GLint* value)
  {
    static PFNGLUNIFORM4IVPROC     glUniform4iv = NULL; 
    if (glUniform4iv == NULL) {
      glUniform4iv = (PFNGLUNIFORM4IVPROC)load("glUniform4iv");
    }
    glUniform4iv(location, count, value);
  }
  
public:
  void setMatrix2(GLsizei count, GLboolean transpose, const GLfloat* value)
  {
    static PFNGLUNIFORMMATRIX2FVPROC  glUniformMatrix2fv = NULL;
    if ( glUniformMatrix2fv == NULL) {
      glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)load("glUniformMatrix2fv");
    }
    glUniformMatrix2fv(location, count, transpose, value);
  }

  void setMatrix3(GLsizei count, GLboolean transpose, const GLfloat* value)
  {
    static PFNGLUNIFORMMATRIX3FVPROC  glUniformMatrix3fv = NULL;
    if (glUniformMatrix3fv == NULL) {
      glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)load("glUniformMatrix3fv");
    }
    glUniformMatrix3fv(location, count, transpose, value);
  }
  
  void setMatrix4(GLsizei count, GLboolean transpose, const GLfloat* value)
  {
    static PFNGLUNIFORMMATRIX4FVPROC  glUniformMatrix4fv = NULL;
    if (glUniformMatrix4fv = NULL) {
      glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)load("glUniformMatrix4fv");
    }
    glUniformMatrix4fv(location, count, transpose, value);
  }
#endif

#ifdef GL_VERSION_2_1
  
  void setMatrix2x3(GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    static PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = NULL;
    if (glUniformMatrix2x3fv == NULL) {
      glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)load("glUniformMatrix2x3fv");
    }
    glUniformMatrix2x3fv(location, count, transpose, value);
  }
  
  void setMatrix2x4(GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    static PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = NULL;
    if (glUniformMatrix2x4fv == NULL) {
      glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)load("glUniformMatrix2x4fv");
    }
    glUniformMatrix2x4fv(location, count, transpose, value);
  }
  
  void setMatrix3x2(GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    static PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = NULL;
    if (glUniformMatrix3x2fv == NULL) {
      glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)load("glUniformMatrix3x2fv");
    }
    glUniformMatrix3x2fv(location, count, transpose, value);
  }
  
  void setMatrix3x4(GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    static PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = NULL;
    if (glUniformMatrix3x4fv == NULL) {
      glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)load("glUniformMatrix3x4fv");
    }
    glUniformMatrix3x4fv(location, count, transpose, value);
  }
    
  void setMatrix4x2(GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    static PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = NULL;
    if (glUniformMatrix4x2fv == NULL) {
      glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)load("glUniformMatrix4x2fv");
    }
    glUniformMatrix4x2fv(location, count, transpose, value);
  }
  
  void setMatrix4x3(GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    static PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = NULL;
    if (glUniformMatrix4x3fv == NULL) {
      glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)load("glUniformMatrix4x3fv");
    }
    glUniformMatrix4x3fv(location, count, transpose, value);
  }
  
#endif
  
#ifdef GL_VERSION_3_0
    
  void set(GLuint v0)
  {
    static PFNGLUNIFORM1UIPROC glUniform1ui = NULL;
    if (glUniform1ui == NULL) {
      glUniform1ui = (PFNGLUNIFORM1UIPROC)load("glUniform1ui");
    }
    
    glUniform1ui(location, v0);
  }

  void set(GLsizei count, const GLuint* value)
  {
    if (count < 1 || count >4) {
      throw IException("Invalid count parameter.");
    }
    if (value == NULL) {
      throw IException("Invalid value parameter.");
    }
    switch(count) {
    case 1:
      set1uiv(count, value);
      break;
    case 2:
      set2uiv(count, value);
      break;
    case 3:
      set3uiv(count, value);
      break;
    case 4:
      set4uiv(count, value);
      break;
    }
  }

  void set1uiv(GLsizei count, const GLuint* value)
  {
    static PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
    if (glUniform1uiv == NULL) {
      glUniform1uiv = (PFNGLUNIFORM1UIVPROC)load("glUniform1uiv");
    }
    glUniform1uiv(location, count, value);
  }
  
  void set(GLuint v0, GLuint v1)
  {
    static PFNGLUNIFORM2UIPROC glUniform2ui = NULL;
    if (glUniform2ui == NULL) {
      glUniform2ui = (PFNGLUNIFORM2UIPROC)load("glUniform2ui");
    }
    glUniform2ui(location, v0, v1);
  }
  
  void set2uiv(GLsizei count, const GLuint* value)
  {
    static PFNGLUNIFORM2UIVPROC glUniform2uiv = NULL;
    if (glUniform2uiv == NULL) {
      glUniform2uiv = (PFNGLUNIFORM2UIVPROC)load("glUniform2uiv");
    }
    glUniform2uiv(location, count, value);
  }

  void set(GLuint v0, GLuint v1, GLuint v2)
  {
    static PFNGLUNIFORM3UIPROC glUniform3ui = NULL;
    if (glUniform3ui == NULL) {
      glUniform3ui = (PFNGLUNIFORM3UIPROC)load("glUniform3ui");
    }
    glUniform3ui(location, v0, v1, v2);
  }
  
  void set3uiv(GLsizei count, const GLuint* value)
  {
    static PFNGLUNIFORM3UIVPROC glUniform3uiv = NULL;
    if (glUniform3uiv == NULL) {
      glUniform3uiv = (PFNGLUNIFORM3UIVPROC)load("glUniform3uiv");
    }
    glUniform3uiv(location, count, value);
  }
  
  void set(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
  {
    static PFNGLUNIFORM4UIPROC glUniform4ui = NULL;
    if (glUniform4ui == NULL) {
      glUniform4ui = (PFNGLUNIFORM4UIPROC)load("glUniform4ui");
    }
    glUniform4ui(location, v0, v1, v2, v3);
  }
  
  void set4uiv(GLsizei count, const GLuint* value)
  {
    static PFNGLUNIFORM4UIVPROC glUniform4uiv = NULL;
    if (glUniform4uiv == NULL) {
      glUniform4uiv = (PFNGLUNIFORM4UIVPROC)load("glUniform4uiv");
    }
    
    glUniform4uiv(location, count, value);
  }

#endif
};

}

