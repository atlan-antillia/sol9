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
 *  OpenGLRenderContext.h
 *
 *****************************************************************************/

// 2015/07/22
// 2016/07/01 Modified to use glewInit in OpenGLContext constructor.

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/ClientDC.h>

namespace SOL {

class OpenGLRenderContext :public OpenGLObject {
private:
  HDC    hDC;
  HGLRC  hGLRC;  //Handle to an OpengGL Render Context

public:
  //Modified to pass majorVersion and minorVersion of OpenGL
  OpenGLRenderContext(ClientDC* clientDC, int majorVersion=3, int minorVersion=1)
  :hDC(NULL),
  hGLRC(NULL)
  {
    if (clientDC == NULL) {
      throw IException("Invalid argument: ClientDC is NULL");  
    }
    hDC = clientDC -> get();
    
    if (hDC) {
      hGLRC = wglCreateContext(hDC);
      if (hGLRC == NULL) {
        throw IException("Failed to wglCreateContext: Error(%s)", errorString() );
      }
    } else {
      throw IException("Invalid argument: HDC is NULL");
    }
    makeCurrent();
    
    //<added date~"2016/07/01">
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
      throw IException("Failed to glewInit");
    }
    
    int attributes[] = {  
      WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
      WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
      WGL_CONTEXT_FLAGS_ARB,         0,
      0,      
    };
    
    if (wglewIsSupported("WGL_ARB_create_context") == GL_TRUE) {
#ifdef SDEBUG
      char text[256];
      sprintf_s(text, sizeof(text), "Call WGL_ARB_create_context: majorVersion=%d, minorVersion=%d",
          majorVersion, minorVersion);
      MessageBox(NULL, text, "Debug", MB_OK);
#endif
      HGLRC  hNewRC = wglCreateContextAttribsARB(hDC, NULL, attributes); 
      if (hNewRC == NULL) {
      
        throw IException("Failed to WGL_ARB_create_context: majorVersion=%d, minorVersion=%d",
             majorVersion, minorVersion);
      }
      HGLRC  hPrevRC = hGLRC;
      wglMakeCurrent(hDC, NULL);  
      hGLRC = hNewRC; 
      makeCurrent();
      wglDeleteContext(hPrevRC);
    } else {
      MessageBox(NULL, "WGL_ARB_create_context is not supported", "Warning", MB_OK);
    }
    //</added>
  }

  ~OpenGLRenderContext()
  {
     wglMakeCurrent(hDC, NULL);
     wglDeleteContext(hGLRC);

     hDC   = NULL;
     hGLRC = NULL;
  }

  void makeCurrent()
  {
    if (wglMakeCurrent(hDC, hGLRC) == FALSE) {
      throw IException("Failed to wglMakeCurrent: Error(%s)", errorString());
    }
  }
  
  void activate()
  {
    if (wglMakeCurrent(hDC, hGLRC) == FALSE) {
      throw IException("Failed to wglMakeCurrent: Error(%s)", errorString());
    }
  }
  void unactivate()
  {
    if (wglMakeCurrent(NULL, NULL) == FALSE) {
      throw IException("Failed to wglMakeCurrent: Error(%s)", errorString());
    }
  }
  
};

}
