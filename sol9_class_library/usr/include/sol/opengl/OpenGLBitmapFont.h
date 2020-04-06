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
 *  OpenGLBitmapFont.h
 *
 *****************************************************************************/

#pragma once

#include <sol/opengl/OpenGLFont.h>

namespace SOL {

class OpenGLBitmapFont :public OpenGLFont {

public:
  OpenGLBitmapFont(ClientDC* dc, Font* font)
  :OpenGLFont(font)
  {
    if (dc == NULL || font == NULL) {
      throw IException("Invalid argument");
    }

    HGDIOBJ prevFont = dc -> select(font);

    //See https://msdn.microsoft.com/en-us/library/windows/desktop/dd374392(v=vs.85).aspx
    BOOL rc = wglUseFontBitmaps( dc -> get(), 0, getCharCount(), getListsBase());

    dc -> select(prevFont);
    if (rc == FALSE) {
      throw IException("Failed to wglUseFontBitmaps");
    }
  }

  virtual void drawString(ClientDC* dc, int x, int y, const char* string)
  {
    glRasterPos2i(x, y);
    OpenGLFont::drawString(dc, string);
  }
};

}
