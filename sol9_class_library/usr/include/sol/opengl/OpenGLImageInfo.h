/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OpenGLImageInfo.h
 *
 *****************************************************************************/

#pragma once

#include <stdint.h>
#include <sol/Object.h>
#include <sol/SmartPtrs.h>

//The following values are taken from gl.h
#ifndef GL_RGBA
#define GL_RGBA          0x1908
#endif

#ifndef GL_BGRA
#define GL_BGRA	         0x80E1
#endif

#ifndef GL_UNSIGNED_BYTE
#define GL_UNSIGNED_BYTE 0x1401
#endif

namespace SOL {

class OpenGLImageInfo :public Object {

public:
  int    depth;           //Image depth

  int    channels;        //Image depth

  int    xformat;         //X11 XImage format

  int    internalFormat;  //OpenGL internal pixel format GL_RGB, ....

  int    width;

  int    height;

  int    format;           //OpenGL pixel format 

  int    type;             //OpenGL type

  int    widthStep;  

  int    imageSize;       

  SmartPtrs<uint32_t>  imageData;

public:
 OpenGLImageInfo(int xinternal = GL_RGBA, 
                 int xformat   = GL_BGRA, 
                 int xtype     = GL_UNSIGNED_BYTE)
  :depth(0)
  ,xformat(0)
  ,internalFormat(xinternal)
  ,width(0)
  ,height(0)
  ,format(xformat)
  ,type(xtype)
  ,widthStep(0)
  ,imageSize(0) 
  {
  }

};

}


