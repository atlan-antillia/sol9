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
 *  OpenGLText.h
 *
 *****************************************************************************/

#pragma once

#include <sol/String.h> //2015/07/23

#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLFont.h>

namespace SOL {

class OpenGLText :public OpenGLObject {
private:
  String string;  

public:
  OpenGLText(const char* text)
  :string("")
  {
    if (text) {
      string = text;
    }
  }

  void draw(void* font = GLUT_STROKE_ROMAN)
  {
    draw(font, (const char*)string);
  }

public:
  void draw(void* font, const char* string)
  {
    if (string && font) {
      size_t len = strlen(string);
      if (isStrokeFont(font)) {
        for (size_t i = 0; i<len; i++) {
          glutStrokeCharacter(font, string[i]);
        }
      } else if (isBitmapFont(font)) {
        for (size_t i = 0; i<len; i++) {
          glutBitmapCharacter(font, string[i]);
        }
      } else {
        throw IException("Invalid font");
      }
    }
  }
  
  bool isStrokeFont(void* font)
  {
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

  bool isBitmapFont(void* font)
  {
     void* fonts[] = {
       GLUT_BITMAP_9_BY_15,
       GLUT_BITMAP_8_BY_13,
       GLUT_BITMAP_TIMES_ROMAN_10,
       GLUT_BITMAP_TIMES_ROMAN_24,
       GLUT_BITMAP_HELVETICA_10,
       GLUT_BITMAP_HELVETICA_12,
       GLUT_BITMAP_HELVETICA_18,
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
};

}

