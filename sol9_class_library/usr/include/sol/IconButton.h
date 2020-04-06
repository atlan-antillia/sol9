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
 *  IconButton.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/23

#pragma once

#include <sol\Button.h>

namespace SOL {

class IconButton :public Button {
private:
  BOOL  capturing;
  HICON  hicon;
  BOOL  deleteFlag; 
  
private:

  LRESULT defaultProc(Event& event)
  {
    View* view = getParent();
    if(view) {
      HWND parent = view -> getWindow();
    
      POINT p;
      getCursorPos(&p);
      ::ScreenToClient(parent, &p);

      switch(event.getMessage()) {

      case WM_KEYDOWN:
      case WM_KEYUP:
        
      case WM_KILLFOCUS:
      case WM_CHAR:
        return 0L;

      case WM_SETFOCUS:
        return 0L;

      case WM_MOUSEMOVE:
        {
          POINT p;
          RECT r;

          ::GetCursorPos(&p);
          getWindowRect(&r);

          if(capturing == TRUE) {
            if((p.x < r.left) || (p.y < r.top) ||
            (p.x > r.right) || (p.y > r.bottom)) {
               setState(FALSE);
            }
            else {
              setState(TRUE);
            }
          }
          if(capturing == FALSE) {
            view->send(WM_MOUSEMOVE, 
              event.getWParam(),  event.getLParam());

            if((p.x >= r.left+2) && (p.y >= r.top+2) &&
            (  p.x <= r.right-2) && (p.y <= r.bottom-2)) {
            ;
            }
            else {
              ;
            }
          }
        }
        break;

      case WM_LBUTTONDOWN:
        setState(TRUE);
        capturing = TRUE;
        capture();
        return 0;

      case WM_LBUTTONUP:
        if(capturing && getState()) {
          callCallback(XmNactivateCallback, (Key)getWindow(),
            NULL, event);
        }
        capturing = FALSE;
        setState(FALSE);
        ::ReleaseCapture();
        return 0;

      case WM_LBUTTONDBLCLK:
        return 0;

      default:
        break;
      }
    }
    return Primitive::defaultProc(event);
  }

public:
  IconButton()
  :hIcon(NULL),
  Button() { }

public:
  //2012/06/23
  IconButton(View* parent, const TCHAR* label, Args& args)
  :Button()
  {
    create(parent, label, args);
  }

public:    
  ~IconButton() 
  {
    ::ReleaseCapture();
    if(deleteFlag && hicon) {
      ::DeleteObject(hicon);
    }
  }

public:
  void addCallback(const TCHAR* name, Object* object,
      Callback callback, void* data)
  {
    View::addCallback(name, (Key)getWindow(), object, 
      callback, data);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = Button::create(parent, label, 
      args.set(XmNstyle, (LONG_PTR)(WS_TABSTOP|BS_ICON)));

    capturing = FALSE;
    replaceWindowProc();

    int  xsize = (int)args.get(XmNxImageSize);
    int  ysize = (int)args.get(XmNyImageSize);
    TCHAR* name = (TCHAR*)args.get(XmNimageName);
    HINSTANCE hInst = getInstanceHandle();

    hicon = (HICON)::LoadImage(hInst, name, IMAGE_ICON,
        xsize, ysize, LR_DEFAULTCOLOR);
    
    send(BM_SETIMAGE, TRUE, (LPARAM)hicon);

    deleteFlag = TRUE;

    return rc;
  }

};

}

