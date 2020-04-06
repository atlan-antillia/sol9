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
 *  Primitive.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/23

#pragma once

#include <sol\View.h>

#include <sol\FileStream.h>
#include <sol\Application.h>
#include <sol\ClientDC.h>

namespace SOL {

class Primitive :public View {

private:
  static int stylesCount()
  {
      int count = 0;
      styles(&count);
      return count;
  }

  static Arg* styles(int* count = NULL) {
    static Arg _styles[] = {
    {XmNgroup,           WS_GROUP},
    {XmNdisabled,        WS_DISABLED},
    {XmNtabStop,         WS_TABSTOP},
    {XmNborderWidth,     WS_BORDER},
    };
    if (count) {
      *count = XtNumber(_styles);
    }
    return _styles;
  }

  static const int PRIMITIVE_STYLES = WS_GROUP|WS_TABSTOP;//|WS_BORDER;
  
  
private:
  WNDPROC   newProc;  
  WNDPROC   oldProc;  
 

protected:
  void resize(const TCHAR* label)
  {
    if(label && strlen(label)) {
      ClientDC cdc(this);
      HFONT hfont = NULL;
      Font* font = getFont();
      if (font) {
        hfont = (HFONT)cdc.select(font);
      }
      SIZE size;
      cdc.getTextExtent(label, (int)strlen(label), &size);
      int w = size.cx;
      int h = size.cy;
      int x, y;
      getLocation(x, y);
      h = cdc.getTextHeight();
      reshape(x, y, w+h*2, h+10);//h*7/4);
      if (hfont) {
        cdc.select(hfont);
      }
    }
  }
  
  
protected:
  LRESULT  defaultProc(Event& event)
  {
    if(oldProc) {
  
      return ::CallWindowProc(oldProc, 
             getWindow(), 
             event.getMessage(), 
             event.getWParam(),
             event.getLParam());
    }
    return View::defaultProc(event);
  }

protected:
  LRESULT discardInput(Event& event)
  {
    View* view = getParent();
    if(view) {
      HWND parent = view -> getWindow();

      POINT p;
      ::GetCursorPos(&p);
      ::ScreenToClient(parent, &p);

      switch(event.getMessage()) {

      case WM_KEYDOWN:
      case WM_KEYUP:
      case WM_SETFOCUS:
      case WM_CHAR:
        return 0L;

      case WM_MOUSEMOVE:
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
      case WM_LBUTTONDBLCLK:
        return view -> send(event.getMessage(), 0,
          MAKELONG(p.x, p.y));

      default:
        break;
      }
    }
    return Primitive::defaultProc(event);
  }
  
  WNDPROC    getNewProc() { return newProc; }

public:
  Primitive()
  :View()
  {
    newProc = NULL;
    oldProc = NULL;
  }

public:
  Primitive(View* parent, HWND hwnd)
  :View(parent)
  {
    newProc = NULL;
    oldProc = NULL;
    setWindow(hwnd);
    Application::add(hwnd, this);  
    setDestructable(FALSE);
  }

public:
  //2012/06/23
  Primitive(View* parent, const TCHAR* name, Args& args)
  :View()
  {
    newProc = NULL;
    oldProc = NULL;
    create(parent, name, args);
  }

public:
  ~Primitive()
  {
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    return View::create(parent, name,
        args.set(
              XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE|PRIMITIVE_STYLES ));
               //styles(), stylesCount())
              //.set(XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE));

  }


  virtual BOOL hasCallback() { return TRUE; }
  
  virtual const TCHAR* defaultCallbackName() { return NULL; }
  

  virtual void setSensitivity(BOOL flag) {
      disable();
  }


public:
  void layout(int x, int y, int w, int h)
  {
    reshape(x, y, w, h);
  }

public:
  void replaceWindowProc()
  {
    WNDPROC proc   = (WNDPROC)getWindowLongPtr(GWLP_WNDPROC);
    //Application& applet = Application::getApplet(NULL);

    //HINSTANCE hins = applet.getInstance();//Application::getInstance();
      
    if(newProc == NULL) {
      newProc = (WNDPROC)View::procedure;

      oldProc = proc;
      setWindowLongPtr(GWLP_WNDPROC, (LONG_PTR)newProc);
    }
  }


public:
  void restoreWindowProc()
  {
    if(oldProc) {
      setWindowLongPtr(GWLP_WNDPROC, (LONG_PTR)oldProc);
      oldProc = NULL;
      if(newProc) {
        newProc = NULL;
      }
    }
  }

public:
  //2012/04/08
  virtual void resize(int width, int height)
  {
    Window::resize(width, height);
  }

};

}


