/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  StatusBar.h
 *
 *****************************************************************************/

// SOL9
// 2008/12/12
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

namespace SOL {

class StatusBar :public Primitive {

public:
  StatusBar(): Primitive() { }  

public:
  //2012/06/25
  StatusBar(View* parent, TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }  

public:

  virtual Boolean create(View* parent, TCHAR* name, Args& args)
  {
    return Primitive::create(parent, name,
        args.set(XmNpredefined, TRUE)
          .set(XmNclassName, (LONG_PTR)STATUSCLASSNAME));
  }

public:
  int getHeight()
  {
    RECT r;
    getWindowRect(&r);
    return r.bottom - r.top;
  }

  LRESULT    getText(int part, TCHAR* text) {
      return send(SB_GETTEXT, part, (LPARAM)text);
  }
  void   setText(int part, int type, const TCHAR* text) {
      send(SB_SETTEXT, part|type, (LPARAM)text);
  }
  LRESULT     getTextLength() {
      return send(SB_GETTEXTLENGTH, 0, 0);
  }

   void  setParts(int num, int* array) {
      send(SB_SETPARTS, num, (LPARAM)array);
  }
  void   getParts(int numParts, int* array) {
      send(SB_GETPARTS, numParts, (LPARAM)array);
  }
     BOOL  getBorders(int* array) {
      return (BOOL)send(SB_GETBORDERS, 0, (LPARAM)array);
  }  

  void   setMinHeight(int height) {
      send(SB_SETMINHEIGHT, height, 0);
  }
  void   simple(BOOL flag) {    
      send(SB_SIMPLE, (WPARAM)flag, 0);
  }
  void   getRect(int part, RECT* rect) {
      send(SB_GETRECT, part, (LPARAM)rect);
  }

public:
  
  //2008/12/12
  void  setText(const TCHAR* text) {
    Window::setText(text);
  }
#ifndef _UNICODE
  void  setText(const wchar_t* text) {
    Window::setText(text);
  }
#endif

};

}
