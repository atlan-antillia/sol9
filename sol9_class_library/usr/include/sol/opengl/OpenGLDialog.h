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
 *  OpenGLDialog.h
 *
 *****************************************************************************/


//2015/08/2 This class depends on win32 MessageBox API.

#pragma once

#include <sol/View.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/opengl/OpenGLMainView.h>

namespace SOL {

class OpenGLDialog: OpenGLObject {
private:
  View* view;

public:
  OpenGLDialog()
  :view(NULL)
  {
  }

  OpenGLDialog(View* view)
  :view(view)
  {
  }

public:

  HWND getWindow()
  {
    HWND hwnd = NULL;
    if (view) {
      hwnd = view->getWindow();
    }
    return hwnd;
  }

  void activateOwner()
  {
    if (view) {
      view -> activate();
    }
  }
  
  int error(const char* format, ...)
  {
    HWND hwnd = getWindow();

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    va_list pos;
    va_start(pos, format);
    _vsnprintf(buffer, sizeof(buffer), format, pos);
    va_end(pos);

    MessageBeep(MB_ICONHAND);
    activateOwner();
    return MessageBox(hwnd, buffer, "Error", MB_OK|MB_ICONHAND);
  }

  int warn(const char* format, ...)
  {
    HWND hwnd = getWindow();
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    va_list pos;
    va_start(pos, format);
    _vsnprintf(buffer, sizeof(buffer), format, pos);
    va_end(pos);

    MessageBeep(MB_ICONHAND);
    activateOwner();
    return MessageBox(hwnd, buffer, "Warning", MB_OK|MB_ICONWARNING);
  }

  int confirm(const char* format, ...)
  {
    HWND hwnd = getWindow();
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    va_list pos;
    va_start(pos, format);
    _vsnprintf(buffer, sizeof(buffer), format, pos);
    va_end(pos);

    MessageBeep(MB_ICONHAND);
    activateOwner();
    return MessageBox(hwnd, buffer, "Confirmation", MB_OKCANCEL|MB_ICONQUESTION);
  }

  int info(const char* format, ...)
  {
    HWND hwnd = getWindow();
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    va_list pos;
    va_start(pos, format);
    _vsnprintf(buffer, sizeof(buffer), format, pos);
    va_end(pos);

    MessageBeep(MB_ICONHAND);
    activateOwner();
    return MessageBox(hwnd, buffer, "Information", MB_OK|MB_ICONINFORMATION);
  }
};

}
