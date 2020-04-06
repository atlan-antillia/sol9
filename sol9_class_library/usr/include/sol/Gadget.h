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
 *  Gadget.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\View.h>
#include <sol\DC.h>

#include <sol\Layoutable.h>


namespace SOL {

class Gadget :public Object, public Layoutable {
private:
  int  x;
  int  y;
  int  width;
  int  height;
  View*  parent;
  int  margin;

public:
  Gadget() { }

public:
  //2012/06/22
  Gadget(View* view, const TCHAR* label, Args& args)
  {
    create(view, label, args);
  }


public:
  ~Gadget()
  {
  //
  }

public:
  virtual Boolean create(View* view, const TCHAR* label, Args& args)
  {
    Boolean rc = False;
    if (view) {
      rc = True;
    }
    parent  = view;
    x     = (int) args.get(XmNx);
    y     = (int) args.get(XmNy);
    width  = (int) args.get(XmNwidth);
    height  = (int) args.get(XmNheight);
    return rc;
  }


public:
  virtual void draw(DC* dc)
  {
    // Do nothing here.
  }

public:
  virtual void draw(DC* dc, int x, int y)
  {
    // Do nothing here.
  }


public:
  virtual void layout(int x, int y, int w, int h)
  {
    reshape(x, y, w, h);
  }


public:
  void reshape(int x1, int y1, int width1, int height1)
  {
    x   = x1;
    y   = y1;
    width  = width1;
    height  = height1;
    RECT r;
    ::SetRect(&r, x, y, width, height);
    if(parent) {
      parent -> update(&r);
    }  
  }


public:
  void getRect(RECT* r) 
  {
    r->left = x; 
    r->top  = y;
    r ->right  = x + width;
    r ->bottom = y + height;
  }


public:
  void setRect(RECT* r) 
  {
    x = r->left; 
    y = r->top;
    width  = r->right  - r->left;
    height = r->bottom - r->top;
  }


public:
  View*  getParent() { 
    return parent; 
  }

public:
  void  getLocation(int& x1, int& y1) {
      x1 = this->x;
      y1 = this->y;
  }

public:
  void  getSize(int& w, int& h) { 
    w = this->width; 
    h = this->height;
  }

public:
  void  setLocation(int x1, int y1) {
    this->x = x1;
    this->y = y1;
  }

public:
  void  setSize(int w, int h) { 
    this->width = w; 
    this->height = h;
  }

public:
  void  setMargin(int m) {
    this->margin = m;
  }

public:
  int    getMargin() {
    return this->margin;
  }

};

}

