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
 *  OpenGLShader.h
 *
 *****************************************************************************/

//2016/07/30 Added a new constructor OpenGLShader(GLenum type, const char* filename)
//2016/08/01 Added some methods to get shader object information.

#pragma once

#ifdef GL_VERSION_2_0

#include <sol/StringT.h>
#include <sol/ModuleFilename.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/CharFileReader.h>

namespace SOL {

class OpenGLShader :public OpenGLObject {
private:
  GLuint shader;
  
public:
  OpenGLShader(GLenum type)
  :OpenGLObject(),
  shader(INVALID_VALUE)
  {
    shader = create(type);
    if (shader == 0) {
      throw IException("Failed to createShader: %d", (int)type); 
    }
  }
  
  //2016/07/30
  OpenGLShader(GLenum type, const char* filename)
  :OpenGLObject(),
  shader(INVALID_VALUE)
  {
    shader = create(type);
    if (shader == 0) {
      throw IException("Failed to createShader: %d", (int)type); 
    }
 
    char  fullpath[MAX_PATH];
 
    ModuleFileName moduleFileName;
    const char* drive = moduleFileName.getDrive();
    const char* dir   = moduleFileName.getDir();
      
    sprintf(fullpath,   "%s%s%s", drive, dir, filename);
    shaderSource(fullpath);
    
    //Do compile automatically.
    compile();
  }

public:
  
  ~OpenGLShader()
  {
    destroy();
  }

  operator GLuint()
  {
    return shader;
  }

  GLuint create(GLenum type)
  {
    /*static PFNGLCREATESHADERPROC   glCreateShader = NULL;
    if (glCreateShader == NULL) {
      glCreateShader  = (PFNGLCREATESHADERPROC)load("glCreateShader"); 
    }
    */
    return glCreateShader(type);
  }

  void  compile()
  {
    static PFNGLCOMPILESHADERPROC  glCompileShader = NULL;    
    if (glCompileShader == NULL) {
      glCompileShader   = (PFNGLCOMPILESHADERPROC)load("glCompileShader"); 
    }
    glCompileShader(shader);
    GLint compile_ok = GL_FALSE;
    getShader(GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
      destroy();
      throw IException("Failed to compile a shader");
    }
  }
  
  void destroy()
  {
    static PFNGLDELETESHADERPROC  glDeleteShader = NULL;
    if (glDeleteShader == NULL) {
      glDeleteShader   = (PFNGLDELETESHADERPROC)load("glDeleteShader"); 
    }
    if (shader > 0) {
      glDeleteShader(shader);
    }
    shader = INVALID_VALUE;
  }
  
  void getInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)
  {
    static PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog = NULL; 
    if (glGetShaderInfoLog == NULL) {
      glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog"); 
    }
    glGetShaderInfoLog(shader, bufSize, length, infoLog);
  }
  
  void getShaderSource(GLsizei maxLength, GLsizei* length, GLchar* source)
  {
    static PFNGLGETSHADERSOURCEPROC   glGetShaderSource  = NULL;
    if (glGetShaderSource == NULL) {
      glGetShaderSource  = (PFNGLGETSHADERSOURCEPROC)load("glGetShaderSource"); 
    }
    glGetShaderSource(shader, maxLength, length, source);
  }
  
  
  /**
  pname takes one of the following values:
   GL_SHADER_TYPE,
   GL_DELETE_STATUS
   GL_COMPILE_STATUS
   GL_INFO_LOG_LENGTH
   GL_SHADER_SOURCE_LENGTH
   */
  void getShader(GLenum pname, GLint* param)
  {
    static PFNGLGETSHADERIVPROC   glGetShaderiv = NULL;      
    if (glGetShaderiv == NULL) {
      glGetShaderiv   = (PFNGLGETSHADERIVPROC)load("glGetShaderiv"); 
    }
    glGetShaderiv(shader, pname, param);
  }
  
  //<added date="2016/08/01">
  int getShaderType()
  {
    GLint value = 0;
    getShader(GL_SHADER_TYPE, &value);
    return value;
  }
  
  int getDeleteStatus()
  {
    GLint value = 0;
    getShader(GL_DELETE_STATUS, &value);
    return value;
  }

  int getCompileStatus()
  {
    GLint value = 0;
    getShader(GL_COMPILE_STATUS, &value);
    return value;
  }

  int getInfoLogLength()
  {
    GLint value = 0;
    getShader(GL_INFO_LOG_LENGTH, &value);
    return value;
  }

  int getShaderSourceLength()
  {
    GLint value = 0;
    getShader(GL_SHADER_SOURCE_LENGTH, &value);
    return value;
  }
  //</added>
  
  void shaderSource(GLsizei count, const GLchar *const* string, const GLint* length)
  {
    static PFNGLSHADERSOURCEPROC   glShaderSource = NULL;     
    if (glShaderSource == NULL) {
      glShaderSource  = (PFNGLSHADERSOURCEPROC)load("glShaderSource"); 
    }
    glShaderSource(shader, count, string, length);
  }
  
  void shaderSource(const char* filename)
  {
    CharFileReader reader(filename);
    const char* string = reader.getData();
    shaderSource(1, (const GLchar *const*)&string, NULL);
  }

  GLboolean isShader()
  {
    static PFNGLISSHADERPROC  glIsShader = NULL;
    if (glIsShader == NULL) {
      glIsShader   = (PFNGLISSHADERPROC)load("glIsShader"); 
    }
    return glIsShader(shader);
  }
  
  void getSource(StringT<char>& shaderSource)
  {
    GLuint maxLength = getShaderSourceLength();
    GLchar* source = new GLchar[maxLength+1];
    memset(source, 0, maxLength + 1);
    GLsizei length = 0;
    getShaderSource(maxLength, &length, source);
    shaderSource.shallowCopy(source);
  }

  void displaySource()
  {
    GLuint maxLength = getShaderSourceLength();
    GLchar* source = new GLchar[maxLength+1];
    memset(source, 0, maxLength + 1);
    GLsizei length = 0;
    getShaderSource(maxLength, &length, source);
    
#ifdef WIN32 
    MessageBoxA(NULL, (const char*)source, "ShaderSource", MB_OK);
#else
    ::printf("ShaderSource: %s\n", (const char*)source);
#endif
    delete [] source;
  }

  void getLogInfo(StringT<char>& logInfo)
  {
    GLuint maxLength = getInfoLogLength();
    GLchar* info = new GLchar[maxLength+1];
    memset(info, 0, maxLength + 1);
    GLsizei length = 0;
    getInfoLog(maxLength, &length, info);
    logInfo.shallowCopy(info);
  }

  void displayLogInfo()
  {
    GLuint maxLength = getInfoLogLength();
    GLchar* info = new GLchar[maxLength+1];
    memset(info, 0, maxLength + 1);
    GLsizei length = 0;
    getInfoLog(maxLength, &length, info);
    
#ifdef WIN32 
    MessageBoxA(NULL, (const char*)info, "ShaderLogInfo", MB_OK);
#else
    ::printf("ShaderLogInfo: %s\n", (const char*)info);
#endif
    delete [] info;
  }


};

}

#endif

