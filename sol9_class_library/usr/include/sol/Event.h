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
 *  Event.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2012/09/24 Updated
// 2017/03/11 Added 'handled' menber variable.

#pragma once

#include <sol\Object.h>
#include <sol\Dimension.h>

namespace SOL {

class Event :public Object {
private:
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  void*  data;
  long   result;    // result value of event-handler
  bool   bhandled;

public:
  Event()
  :message(0),
  wParam(0),
  lParam(0),
  data(NULL),
  result(0),
  bhandled(false)
  {
  }

public:
  Event(UINT message1, WPARAM wParam1, LPARAM lParam1, void* clientData=NULL) 
  :message(message1),
  wParam(wParam1),
  lParam(lParam1),
  data(clientData),
  result(0),
  bhandled(false)
  {
  }

public:
  HWND getChild() 
  { 
    if(message == WM_NOTIFY) 
      return ((NMHDR*)lParam)->hwndFrom;
    else 
      return (HWND)lParam; 
  }

public:
  UINT_PTR getControlId()
  {
    if(message == WM_NOTIFY) 
      return ((NMHDR*)lParam)->idFrom;
    else 
      return LOWORD(wParam); 
  }

public:
  UINT getNotification()
  { 
    if(message == WM_NOTIFY) 
      return ((NMHDR*)lParam)->code;
    else
      return HIWORD(wParam);
  }

public:
  BOOL isMenuSelected()
  {
    BOOL  rc = FALSE;
  
    // if lParam == 0, then menu or accelarator
    if (lParam == 0) {
      if(HIWORD(wParam) == 0) {
        // menu selected;
        rc = TRUE;
      }
    }
    return rc;
  }

public:
  BOOL fromAccelerator()
  {
    BOOL rc = FALSE;
    // if lParam == 0, then menu or accelerator
    if (lParam == 0) {
      if(HIWORD(wParam) == 1) {
        rc = TRUE;
      }
    }
    return rc;
  }


  //2009/11/01
  WORD    getMenuId() { return LOWORD(wParam); }

  UINT    getMessage() { return message; }
  WPARAM  getWParam() { return wParam; }
  LPARAM  getLParam() { return lParam; }
  void*   getData()      { return data; }

  void   getMousePosition(int& x, int& y) {
      x = LOWORD(lParam);
      y = HIWORD(lParam);
  }
  void   getMousePosition(POINT* pt) {
      pt->x = LOWORD(lParam);
      pt->y = HIWORD(lParam);
  }

  void  getSize(int& w, int& h) {
      w = LOWORD(lParam);
      h = HIWORD(lParam);
  }
  void  getSize(Dimension& d) {
      d.set(LOWORD(lParam), HIWORD(lParam));
  }

  void  setData(void* data1)  { data = data1; }

  long  getResult() { return result; }
  
  void  setResult(long val) { result = val; }
  
  void handled(bool value=true)
  {
    bhandled = value;
  }
  
  //2017/03/30 Modified.
  bool isHandled()
  {
    return bhandled;
  }
  
 //2017/09/10
  int getIntData()
  {
    return to_integer(data);
  }
};

}


