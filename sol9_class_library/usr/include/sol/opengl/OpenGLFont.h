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
 *  OpenGLFont.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Font.h>
#include <sol/ClientDC.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLLists.h>

namespace SOL {

class OpenGLFont: public OpenGLObject {
protected:
  static const int CHAR_COUNT = 256;

  Font*        font;
  OpenGLLists* lists;

public:
  OpenGLFont(Font* f)
  :font(f),    //Shallow copy
   lists(NULL)
  {
    if (font == NULL) {
      throw IException("Invalid argument: Font is NULL");
    }
    lists = new OpenGLLists(CHAR_COUNT);
    if (lists == NULL) {
      throw IException("Failed to create OpenGLLists");
    }
  }

  ~OpenGLFont()
  {
    delete lists;
    lists = NULL;
  }

public:  

  static int getCharCount()
  {
    return CHAR_COUNT;  
  }

  GLuint getListsBase()
  {
    return lists -> getBase();
  }

  virtual void drawString(ClientDC* dc, const char* string)
  {
    if (string == NULL) {
      return;
    }
    HGDIOBJ prevFont = dc -> select(font);

    GLsizei size = strlen(string);
    lists -> call(size, GL_UNSIGNED_BYTE, (const GLvoid*)string );

    dc -> select(prevFont);  
  }
};
}
