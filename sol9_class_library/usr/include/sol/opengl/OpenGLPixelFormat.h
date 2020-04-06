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
 *  OpenGLPixelFormat.h
 *
 *****************************************************************************/

// 2015/07/22

#pragma once

#include <sol/Object.h>
#include <sol/ClientDC.h>
#include <sol/opengl/OpenGLObject.h>

namespace SOL {

class OpenGLPixelFormat :public OpenGLObject {
protected:
  PIXELFORMATDESCRIPTOR pfd;
  HDC hDC;

protected:
  static const DWORD DOUBLE_BUFFER = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
  static const DWORD SINGLE_BUFFER = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL; 

public:
  OpenGLPixelFormat(ClientDC* clientDC, DWORD flags = DOUBLE_BUFFER, BYTE pixelType=PFD_TYPE_RGBA, 
     BYTE colorBits=24, BYTE depthBits=16, BYTE alphaBits = 8)
  :hDC(NULL)
  {
    if (clientDC == NULL) {
      throw IException("Invalid argument: ClientDC is NULL");
    }
    hDC = clientDC -> get();
    
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize      = sizeof(pfd);
    pfd.nVersion   = 1;
    pfd.dwFlags    = flags; //FLAGS; //PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = pixelType;  //PFD_TYPE_RGBA;
    pfd.cColorBits = colorBits;  //24;
    pfd.cDepthBits = depthBits;  //16;
    pfd.cAlphaBits = alphaBits;  //8;
    pfd.iLayerType = PFD_MAIN_PLANE;  
  }

  void pixelType(BYTE pixelType)
  {
    pfd.iPixelType = pixelType; //PFD_TYPE_RGBA; 
  }

  void depthBits(BYTE bits)
  {
    pfd.cDepthBits = bits; //16;
  }

  void alphaBits(BYTE bits)
  {
    pfd.cAlphaBits = bits; //8;
  }

  void setLayerType(BYTE layerType)
  {
     pfd.iLayerType = layerType;
  }

  BOOL setPixelFormat()
  {
     int pixelFormat = chooseFormat();
     return setPixelFormat(pixelFormat);
  }


  int chooseFormat()
  {
    int  pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (pixelFormat == 0) {
      throw IException("Failed to ChoosePixel: Error(%s)", errorString());
    
    }
    return pixelFormat;
  }

  BOOL setPixelFormat(int pixelFormat)
  {
    BOOL rc = SetPixelFormat(hDC, pixelFormat, &pfd);
    if (rc == FALSE) {
      throw IException("Failed to SetPixelFormat: Error(%s)", errorString());
    }
    return rc;
  }

  int getPixelFormat()
  {
    return GetPixelFormat(hDC);
  }
  
  //2019/04/11
  
  int describePixelFormat(int pixelFormat, PIXELFORMATDESCRIPTOR& pfd)
  {
    BOOL rc = DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    if (rc == FALSE) {
      throw IException("Failed to DescribePixelFormat: Error(%s)", errorString());
    }
    return rc;
  }

};

}
