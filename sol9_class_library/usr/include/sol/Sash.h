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
 *  Sash.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

#include <sol\Resource.h>
#include <sol\PaintDC.h>
#include <sol\ClientDC.h>
#include <sol\stdio.h>
#include <sol\StockObject.h>
#include <sol\Brush.h>
#include <sol\Stdio.h>

namespace SOL {

class Sash :public Primitive {
private:
  int    x, y;
  int    px, py;
  BOOL  capturing;
  int    thickness;
  int    direction;

public:
  static const int Sash::VERTICAL   = 0;
  static const int Sash::HORIZONTAL = 1;

private:

  long Sash::leftButtonDown(Event& event)
  {
    POINT p;
    capturing = TRUE;
    capture();
    ::GetCursorPos(&p);
    View* parent = getParent();

    parent -> toClient(&p);
//  y  = p.y;
//  py = p.y;

    RECT r;
    parent->getClientRect(&r);
    ClientDC cdc(parent);
    StockObject black(LTGRAY_BRUSH);
    StockObject pen(NULL_PEN);
    cdc.setROP2(R2_NOTXORPEN);
    cdc.select(&black);
    cdc.select(&pen);
    if (direction == VERTICAL) {
      y  = p.y;
      py = y;
      cdc.rectangle(0, y, r.right, y+thickness);
    }
    if (direction == HORIZONTAL) {
      x = p.x;
      px = x;
      cdc.rectangle(x, 0, x+thickness, r.bottom);
    }
    return NULL;
  }

private:
  long leftButtonUp(Event& event)
  {
    if(capturing) {
      //releaseCapture();
      View* parent = getParent();
      POINT p;
      getCursorPos(&p);
  
      parent -> toClient(&p);

      y = p.y;
      RECT r;
      parent->getClientRect(&r);
      ClientDC cdc(parent);
      StockObject black(LTGRAY_BRUSH);
      StockObject pen(NULL_PEN);
      cdc.setROP2(R2_NOTXORPEN);
      cdc.select(&black);
      cdc.select(&pen);
      RECT s;
      getClientRect(&s);
      Printf(_T("Moup px(%d %d)  newPos(%d %d)\r\n"), px, py, p.x, p.y);

      if (direction == VERTICAL) {
        y = p.y;
        cdc.rectangle(0, y, r.right, y+thickness);
        if(p.y <0) {
          setLocation(0, 0);
        }
        else if(p.y > r.bottom-s.bottom) {
          setLocation(0, r.bottom-s.bottom);
        }
        else {
          setLocation(0, p.y);
        }
      }
      if (direction == HORIZONTAL) {
        x = p.x;
        x = px;  //??
        //cdc.rectangle(x, 0, x+thickness, r.bottom);
        cdc.rectangle(x, 0, x+thickness,  r.bottom);
        if(p.x <0) {
          setLocation(0, 0);
        }
        else if(p.x > r.right-s.right) {
          setLocation(r.right-s.right, 0);
        }
        else {
          setLocation(p.x, 0);
        }
      }

      callCallback(XmNdragFinishedCallback,
        (Key)getWindow(), NULL, event);
      capturing = FALSE;

      //Moved here
      releaseCapture();
    }
    return NULL;
  }

private:
  long mouseMove(Event& event)
  {
    POINT p;
    getCursorPos(&p);
    View* parent = getParent();
    if(parent && capturing) {
      parent -> toClient(&p);

      RECT r;
      parent -> getClientRect(&r);
      ClientDC cdc(parent);
      StockObject black(LTGRAY_BRUSH);
      StockObject pen(NULL_PEN);
      cdc.setROP2(R2_NOTXORPEN);
      cdc.select(&black);
      cdc.select(&pen);
      Printf(_T("Move px(%d %d)  newPos(%d %d)\r\n"), px, py, p.x, p.y);

      if (direction == VERTICAL) {
        y = p.y;
        cdc.rectangle(0, py, r.right, py+thickness);
        cdc.rectangle(0, y,  r.right, y+thickness);
        py = y;
      }
      if (direction == HORIZONTAL) {
        x = p.x;
        cdc.rectangle(px, 0,  px+thickness, r.bottom);
        cdc.rectangle(x,  0,  x+thickness, r.bottom);
        px = x;
      }
    }
    return NULL;
  }

private:
  long paint(Event& event)
  {
    PaintDC pdc(this);

    RECT  rect;
    getClientRect(&rect);
    
    Brush  face(GetSysColor(COLOR_BTNFACE));
    Brush  shadow(GetSysColor(COLOR_BTNSHADOW));
    StockObject  pen(NULL_PEN);
    pdc.select(&pen);

    HGDIOBJ oldbrush = pdc.select(&face);
    pdc.rectangle(0, 1, rect.right+1, rect.bottom+1);

    pdc.select(&shadow);
    pdc.rectangle(0, rect.bottom-1, rect.right+1, rect.bottom+1);
    pdc.select(oldbrush);

    return NULL;
  }

public:
  Sash():Primitive() { }
  
public:
  //2012/06/25
  Sash(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
    args.set(XmNbackground, (LONG_PTR)(COLOR_BTNFACE+1))
        .set(XmNclassName, _T("Sash") ));
  
    capturing = FALSE;

    thickness = 3;   
    LONG_PTR val;
    if (args.get(XmNthickness, &val)) {
      thickness = (int)val;
    }
    direction = VERTICAL;
    if (args.get(XmNdirection, &val)) {
      direction = (int)val;
    }
    addEventHandler(WM_PAINT, this,
      (Handler)&Sash::paint, NULL);
    addEventHandler(WM_LBUTTONDOWN, this,
      (Handler)&Sash::leftButtonDown, NULL);
    addEventHandler(WM_MOUSEMOVE, this,
      (Handler)&Sash::mouseMove, NULL);
    addEventHandler(WM_LBUTTONUP, this,
      (Handler)&Sash::leftButtonUp, NULL);
    return rc;
  }

public:
  ~Sash() { }

public:
  void addCallback(const TCHAR* name, Object* object,
      Callback callback, void* data)
  {
    View::addCallback(name, (Key)getWindow(), object, 
      callback, data);
  }

  int    getThickness() { return thickness; }

  void  setThickness(int val) { thickness = val; }
  
};

}
