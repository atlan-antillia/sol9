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
 *  OpenGLProgram.h
 *
 *****************************************************************************/

//2016/08/01 Added unuse method, and modified display method.
//2016/08/20 Updated for OpenGL 3.0


#pragma once


#include <sol/opengl/OpenGLObject.h>

namespace SOL {
  
class OpenGLProgram : public OpenGLObject {

#ifdef GL_VERSION_2_0
 
private:
  GLuint program;
   
public:
  OpenGLProgram()
  :OpenGLObject(),
  program(INVALID_VALUE)
  {
    program = create();
    if (program == 0) {
      throw IException("Failed to glCreateProgram.");
    }
    printf("create program %d\n", program);
  }
  
  ~OpenGLProgram()
  {
    use(0);
    if (program > 0) {
      destroy();
    }
    program = INVALID_VALUE;
  }
  
  operator GLuint()
  {
    return program;
  }

  
  void attachShader(GLuint shader) 
  {
    static PFNGLATTACHSHADERPROC  glAttachShader = NULL;
    if (glAttachShader == NULL) {
      glAttachShader       = (PFNGLATTACHSHADERPROC)load("glAttachShader");
    }
    glAttachShader(program, shader);
  }
  
  void bindAttributeLocation(GLuint index, const GLchar* name)
  {
    static PFNGLBINDATTRIBLOCATIONPROC  glBindAttribLocation = NULL; 
    if (glBindAttribLocation == NULL) {
      glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)load("glBindAttribLocation"); 
    }
    glBindAttribLocation(program, index, name);
  }

  GLuint create()
  {
    static PFNGLCREATEPROGRAMPROC  glCreateProgram = NULL; 
    if (glCreateProgram == NULL) {
      glCreateProgram  = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram"); 
    }
    return glCreateProgram();
  }

  void destroy()
  {
    static PFNGLDELETEPROGRAMPROC  glDeleteProgram = NULL; 
    if (glDeleteProgram == NULL) {
      glDeleteProgram  = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");
    }
    glDeleteProgram(program);
  }
  
  void detachShader(GLuint shader)
  {
    static PFNGLDETACHSHADERPROC  glDetachShader = NULL; 
    if (glDetachShader == NULL) {
      glDetachShader  = (PFNGLDETACHSHADERPROC)load("glDetachShader"); 
    }
    glDetachShader(program, shader);
  }

  void getActiveAttribute(GLuint index, GLsizei maxLength, 
          GLsizei* length, GLint* size, GLenum* type, GLchar* name)
  {
    static PFNGLGETACTIVEATTRIBPROC  glGetActiveAttrib = NULL; 
    if (glGetActiveAttrib == NULL) {
      glGetActiveAttrib  = (PFNGLGETACTIVEATTRIBPROC)load("glGetActiveAttrib"); 
    }
    glGetActiveAttrib(program, index, maxLength, length, size, type, name);
  }
  
  void getAttachedShaders(GLsizei maxCount, GLsizei* count, GLuint* shaders)
  {
    static PFNGLGETATTACHEDSHADERSPROC  glGetAttachedShaders = NULL; 
    if (glGetAttachedShaders == NULL) {
      glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)load("glGetAttachedShaders"); 
    }
    glGetAttachedShaders(program, maxCount, count, shaders);
  }
  
  GLint getAttributeLocation(const GLchar* name)
  {
    static PFNGLGETATTRIBLOCATIONPROC  glGetAttribLocation = NULL;
    if (glGetAttribLocation == NULL) {
      glGetAttribLocation  = (PFNGLGETATTRIBLOCATIONPROC)load("glGetAttribLocation");
    }
    GLint location = glGetAttribLocation(program, name);
    if (location == INVALID_VALUE) {
      throw IException("Failed to glGetAttribLocation %s", name); 
    }
    return location;
  }
  
  void getProgramInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)
  {
    static PFNGLGETPROGRAMINFOLOGPROC  glGetProgramInfoLog = NULL;
    if (glGetProgramInfoLog == NULL) {
      glGetProgramInfoLog  = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetProgramInfoLog"); 
    }
    glGetProgramInfoLog(program, bufSize, length, infoLog);
  }
  
  GLuint getProgram()
  {
    return program;
  }

  void getProgramiv(GLenum pname, GLint* param)
  {
    static PFNGLGETPROGRAMIVPROC  glGetProgramiv = NULL;
    if (glGetProgramiv == NULL) {
      glGetProgramiv  = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv"); 
    }
    glGetProgramiv(program, pname, param);
  }

  void getActiveAttributes(GLint* param)
  {  
    getProgramiv(GL_ACTIVE_ATTRIBUTES, param);
  }

  GLint getActiveAttributeMaxLength(GLint* param)
  {  
    GLint length = 0;
    getProgramiv(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
    return length;
  }

  void getActiveUniforms(GLint* param)
  {  
    getProgramiv(GL_ACTIVE_UNIFORMS, param);
  }

  void getActiveUniformMaxLength(GLint* param)
  {  
    getProgramiv(GL_ACTIVE_UNIFORM_MAX_LENGTH, param);
  }

  void getAttachedShaders(GLint* param)
  {  
    getProgramiv(GL_ATTACHED_SHADERS, param);
  }

  GLint getDeleteStatus()
  {  
    GLint status = 0;
    getProgramiv(GL_DELETE_STATUS, &status);
    return status;
  }

  GLint getInfoLogLength()
  {  
    GLint length = 0;
    getProgramiv(GL_INFO_LOG_LENGTH, &length);
    return length;
  }

  GLint getLinkStatus()
  {  
    GLint status = 0;
    getProgramiv(GL_LINK_STATUS, &status);
    return status;
  }

  GLint getValidateStatus()
  {  
    GLint status = 0;
    getProgramiv(GL_VALIDATE_STATUS, &status);
    return status;
  }

  
  GLint getUniformLocation(const GLchar* name)
  {
    static PFNGLGETUNIFORMLOCATIONPROC  glGetUniformLocation = NULL; 
    if (glGetUniformLocation == NULL) {
      glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load("glGetUniformLocation"); 
    }
    return glGetUniformLocation(program, name);
  }
  
  void getUniform(GLint location, GLfloat* params)
  {
    static PFNGLGETUNIFORMFVPROC  glGetUniformfv = NULL;
    if (glGetUniformfv == NULL) {
      glGetUniformfv   = (PFNGLGETUNIFORMFVPROC)load("glGetUniformfv"); 
    }
    glGetUniformfv(program, location, params);
  }
  
  void getUniform(GLint location, GLint* params)
  {
    static PFNGLGETUNIFORMIVPROC  glGetUniformiv = NULL;
    if (glGetUniformiv == NULL) {
      glGetUniformiv  = (PFNGLGETUNIFORMIVPROC)load("glGetUniformiv"); 
    }
    glGetUniformiv(program, location, params);
  }

  GLboolean isProgram()
  {
    static PFNGLISPROGRAMPROC  glIsProgram = NULL;
    if (glIsProgram == NULL) {
      glIsProgram   = (PFNGLISPROGRAMPROC)load("glIsProgram"); 
    }
    return glIsProgram(program);
  }

  void link()
  {
    static PFNGLLINKPROGRAMPROC  glLinkProgram = NULL;
    if (glLinkProgram == NULL) {
      glLinkProgram  = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
    }
    glLinkProgram(program);
    
    GLint linked = GL_FALSE;
    getProgramiv(GL_LINK_STATUS, &linked);
    if(linked == GL_FALSE) {
      throw IException("Failed to link.");
    }
  }
  
  void use()
  {
    use(this->program);
  }
  
  void use(GLuint program)
  {
    static PFNGLUSEPROGRAMPROC  glUseProgram = NULL;
    if (glUseProgram == NULL) {
      glUseProgram  = (PFNGLUSEPROGRAMPROC)load("glUseProgram");  
    }
    glUseProgram(program);
  }
  
  //2016/08/01
  void unuse()
  {
    use(0);
  }
  
  void validate()
  {
    static PFNGLVALIDATEPROGRAMPROC  glValidateProgram = NULL;
    if (glValidateProgram == NULL) {
      glValidateProgram  = (PFNGLVALIDATEPROGRAMPROC)load("glValidateProgram"); 
    }
    glValidateProgram(program);
  }
  
  void display()
  {
    GLsizei size;

    getProgramiv(GL_INFO_LOG_LENGTH , &size);

    if (size > 1) {
      GLchar* infoLog = (GLchar *)malloc(size);
      if (infoLog != NULL) {
        GLsizei length = 0;

        getProgramInfoLog(size, &length, infoLog);
//2016/08/01
#ifdef WIN32 
    MessageBoxA(NULL, (const char*)infoLog, "ProgramInfoLog", MB_OK);
#else
        printf("ProgramInfoLog:\n%s\n", infoLog);
#endif        
        free(infoLog);
      }
    }
  }

#endif

#ifdef GL_VERSION_3_0
    
  void getUniform(GLint location, GLuint* params)
  {
    static PFNGLGETUNIFORMUIVPROC glGetUniformuiv = NULL;
    if (glGetUniformuiv == NULL) {
      glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)load("glGetUniformuiv");
    }
    glGetUniformuiv(program, location, params);
  }
#endif
};
  
}


