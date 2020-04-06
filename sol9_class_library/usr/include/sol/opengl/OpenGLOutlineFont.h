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
 *  OpenGLOutlineFont.h
 *
 *****************************************************************************/

// Note:

// The wglUseFontOutlines function works with TrueType fonts only.
// See https://msdn.microsoft.com/en-us/library/windows/desktop/dd374393(v=vs.85).aspx

#pragma once

#include <sol/opengl/OpenGLFont.h>

namespace SOL {

class OpenGLOutlineFont :public OpenGLFont {

private:
  GLYPHMETRICSFLOAT gmf[CHAR_COUNT];

public:
  OpenGLOutlineFont(ClientDC* dc, Font* font, FLOAT deviation = 0.0f, FLOAT extrusion = 0.1f)
  :OpenGLFont(font)
  {
    if (dc == NULL || font == NULL) {
      throw IException("Invalid argument");
    }

    HGDIOBJ prevFont = dc -> select(font);

    //See https://msdn.microsoft.com/en-us/library/windows/desktop/dd374393(v=vs.85).aspx

    BOOL rc = wglUseFontOutlines(dc -> get(), 0, getCharCount(),  getListsBase(),
        deviation, extrusion, WGL_FONT_POLYGONS, gmf);

    dc -> select(prevFont);
    if (rc == FALSE) {
      throw IException("Failed to wglUseFontOutlines: Error(%s)", errorString());
    }
  }
};
}
