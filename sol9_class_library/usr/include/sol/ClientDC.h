/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ClientDC.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
#pragma once

//#include <sol\View.h>
#include <sol\Window.h>

#include <sol\DC.h>

namespace SOL {

class ClientDC :public DC {
private:
  HWND hwnd;

  
public:  
  ClientDC(Window* view=nullptr)
    :hwnd(NULL)
  {
    if(view) {
      hwnd = view -> getWindow();
    } else {
      hwnd = GetDesktopWindow();
    }
    set(::GetDC(hwnd));
  }
  
public:
  ClientDC(Window* view, HRGN clipRgn, DWORD flags)
    :hwnd(NULL)
  {
    if(view) {
      hwnd  = view -> getWindow();
    } else {
      hwnd  = GetDesktopWindow();
    }
    set(::GetDCEx(hwnd, clipRgn, flags));
    
  }

public:
  ~ClientDC() 
  {
    ::ReleaseDC(hwnd, get());
  }
  
  
public:
  //2015/07/22
  void swapBuffer()
  {
    SwapBuffers(get());
  }
  
public:
  operator HWND()
  {
    return hwnd;
  }
  
  HWND getWindow()
  {
    return hwnd;
  }
};

}


