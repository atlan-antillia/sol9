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
 *  OpenGLStrokeFont.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLFont.h>

namespace SOL {

class OpenGLStrokeFont :public OpenGLFont {

public:
  OpenGLStrokeFont(void* font = GLUT_STROKE_ROMAN)
  :OpenGLFont(font)
  {
     if (validate(font) == false) {
       throw IException("Invalid font");
     }
  }

  virtual bool validate(void* font)
  {
     // See /usr/include/GL/freeglut_std.h
     void* fonts[] = {
       GLUT_STROKE_ROMAN,               
       GLUT_STROKE_MONO_ROMAN,        
     };
     bool rc = false;
     for (int i = 0; i<CountOf(fonts); i++) {
       if (font == fonts[i]) {
         rc = true;
         break;
       }
     }
    return rc;
  }

  void strokeCharacter(int character)
  {
    glutStrokeCharacter(getFont(), character);
  }

  int  strokeWidth( int character)
  {
    return glutStrokeWidth(getFont(), character);
  }
 
  int  strokeLength(const unsigned char* string)
  {
    return glutStrokeLength(getFont(), string);
  }

  void drawString(const char* string)
  {
    if (string) {
      size_t len = strlen(string);
      for (size_t i = 0; i < len; i++) {
        strokeCharacter(string[i]);
      }
    }
  }
};

}

